#include <QSerialPort>
#include <QDebug>
#include <QMutexLocker>
#include <QMutex>
#include <QFile>
#include <QFileInfo>
#include <QDataStream>
#include <QIODevice>
#include <QThread>
#include <QString>
#include <QStringList>
#include <QChar>
#include <QByteArray>

#include <iostream>
#include "qotdrmodule.h"
#include "qagentapp.h"
#include "qsorfilebase.h"
#include "qpst.h"

static QMutex   gOTDRModule_mutex;


QOTDRModule::QOTDRModule(QObject *parent, qint8 index) : QThread(parent)
{
    _state  = STATE_MEASURED;
    _MeasuredChannels.OTDRModule.channels = 0;
    _moduleIndex = index;
    _keeprunning = 1;
    _progress = 0;
	for(quint16 i =0; i<= 8; i++){
    	_MeasuredCounts.insert(i,0);
		_MeasuredSORFiles.insert(i, 0);
		_MeasuringProgresss.insert(i, 0);
		}
    _moduleMode = OTDR_WORK_MODE_STOP;
	_pIODevice = NULL;

   	_pSerialPort = new QSerialPort();
	if(_moduleIndex == 0){
		setSerialPortParam(QString(UART_OF_MODULE1));
	}
	else
	{
		setSerialPortParam(QString(UART_OF_MODULE2));
	}	
}

QOTDRModule::~QOTDRModule()
{
    if(_pSerialPort != NULL){
        delete _pSerialPort;
        _pSerialPort = NULL;
    }
    if(_pTcpSocket != NULL){
        _pTcpSocket->close();
        delete _pTcpSocket;
        _pTcpSocket = NULL;
    }
     exit(0);
     wait(1000);
    _state  = STATE_IDLING;
    _keeprunning = 0;
}

void QOTDRModule::setKeepRunning(int running)
{
     QMutexLocker locker(&gOTDRModule_mutex);
    _keeprunning = running;
}

int QOTDRModule::getKeepRunning(){
     QMutexLocker locker(&gOTDRModule_mutex);
     return _keeprunning;
}

void QOTDRModule::setModuleIndex(qint8 index)
{
    QMutexLocker locker(&gOTDRModule_mutex);
    _moduleIndex = index;
}

qint8 QOTDRModule::getModuleIndex()
{
    QMutexLocker locker(&gOTDRModule_mutex);
    return _moduleIndex;
}

void QOTDRModule::initModuleFingerData()
{
    QString filename;
    if(getModuleIndex() == 0){
        filename = getIFMSFingerFileName(1);
        initFingerBinFile(filename);
         _OldFingers.insert(filename, new QFingerData(this));
         _NewFingers.insert(filename, new QFingerData(this));

         filename = getIFMSFingerFileName(2);
         initFingerBinFile(filename);
          _OldFingers.insert(filename, new QFingerData(this));
          _NewFingers.insert(filename, new QFingerData(this));

          filename = getIFMSFingerFileName(3);
          initFingerBinFile(filename);
           _OldFingers.insert(filename, new QFingerData(this));
           _NewFingers.insert(filename, new QFingerData(this));

           filename = getIFMSFingerFileName(4);
           initFingerBinFile(filename);
            _OldFingers.insert(filename, new QFingerData(this));
            _NewFingers.insert(filename, new QFingerData(this));
    }

    if(getModuleIndex() == 1 ){
        filename = getIFMSFingerFileName(5);
        initFingerBinFile(filename);
         _OldFingers.insert(filename, new QFingerData(this));
         _NewFingers.insert(filename, new QFingerData(this));

         filename = getIFMSFingerFileName(6);
         initFingerBinFile(filename);
          _OldFingers.insert(filename, new QFingerData(this));
          _NewFingers.insert(filename, new QFingerData(this));

          filename = getIFMSFingerFileName(7);
          initFingerBinFile(filename);
           _OldFingers.insert(filename, new QFingerData(this));
           _NewFingers.insert(filename, new QFingerData(this));

           filename = getIFMSFingerFileName(8);
           initFingerBinFile(filename);
            _OldFingers.insert(filename, new QFingerData(this));
            _NewFingers.insert(filename, new QFingerData(this));
    }
//        _watcher.addPath(QAgentApp::getCacheDir());
}

void QOTDRModule::initFingerBinFile(QString filename)
{
    QFile   ch_file(filename);
    if( !ch_file.open( QIODevice::WriteOnly ) )
      return;

    QDataStream stream(&ch_file );
    stream.setVersion( QDataStream::Qt_DefaultCompiledVersion);
    stream << 0;
    ch_file.flush();
    ch_file.close();
    _fileList.insert(_fileList.count(),filename);
//    _watcher.addPath(filename);
}

void QOTDRModule::initTcpConnection()
{
    QMutexLocker    locker(&gOTDRModule_mutex);

    if(_moduleIndex == 0){
        if((_pTcpSocket->state() != QAbstractSocket::ConnectingState)
                &&(_pTcpSocket->state() != QAbstractSocket::ConnectedState)){
            QString host = QString(ADDRESS_OF_MODULE1);
            quint16 port = 6000;
             _pTcpSocket->connectToHost(host, port);
            if(false == _pTcpSocket->waitForConnected(TCP_CONNECT_TIMEOUT)){
                qDebug() << "Failed to connect to " << host << "in " << TCP_CONNECT_TIMEOUT <<"microseconds\n" << endl;

                _pTcpSocket->abort();
            }
            else
            {
                _tcpState = STATE_TCP_CONNECTED;
            }
        }
    }
    else
    {
        if((_pTcpSocket->state() != QAbstractSocket::ConnectingState)
                &&(_pTcpSocket->state() != QAbstractSocket::ConnectedState)){
            _tcpState = STATE_TCP_CONNECTING;
            _pTcpSocket->connectToHost(QString(ADDRESS_OF_MODULE2), PORT_OF_MODULE2);
            if(false == _pTcpSocket->waitForConnected(6*1000)){
                qDebug() << "Failed to connect to " << ADDRESS_OF_MODULE2 << "in " << TCP_CONNECT_TIMEOUT <<"microseconds\n" << endl;
                _pTcpSocket->abort();
            }
            else
            {
                _tcpState = STATE_TCP_CONNECTED;
            }
        }
    }

}

void QOTDRModule::setConnections()
{
    connect(this, SIGNAL(sigCatchException(quint16, const QString&)), this, SLOT(onCatchException(quint16, const QString&)),Qt::DirectConnection);
}

void QOTDRModule::run()
{
            qDebug() << QThread::currentThreadId() << "\n start Monitoring on module: " << _moduleIndex << " " << _progress << endl;
            qRegisterMetaType<QAbstractSocket::SocketError>("QAbstractSocket::SocketError");

            _pTcpSocket = new QTcpSocket();

            _timerTCPKeepAlive = new QTimer();
            _timerTCPKeepAlive->setInterval(KEEP_ALIVE_TIMEOUT);
            _timerTCPKeepAlive->start();
            _tcpState = STATE_TCP_INIT;

            connect(_pTcpSocket, SIGNAL(connected()), this, SLOT(onSocketConnected()));
            connect(_pTcpSocket, SIGNAL(disconnected()),this, SLOT(onSocketDisconnected()));
            connect(_pTcpSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(onSocketError(QAbstractSocket::SocketError)));
            connect(_timerTCPKeepAlive, SIGNAL(timeout()), this, SLOT(onTcpSocketAutoConnect()));

            initTcpConnection();

            if(_moduleMode == OTDR_WORK_MODE_STOP){
                return;
            }
            sendScanCommand();

            do{
                qDebug() << "\n["<<QThread::currentThreadId() <<"] Monitoring on module[" << _moduleIndex << "] P:" << _progress << "S:"<< getOTDRModuleState() << endl;
                if(getOTDRModuleState() == STATE_GOTSOR4){
                    setOTDRModuleState(STATE_MEASURED);
                }
                QThread::msleep(5000);
                if(isIdling()||isGetSOR()){

                    setProgress(80);
                    sendGetSorCommand();
                    QThread::msleep(300);
                }
                else if(isMeasured())
                {
                    setProgress(100);
                    if(_moduleMode == OTDR_WORK_MODE_AUTO){
                        sendScanCommand();
                    }
                    setProgress(0);
                }
                else if(isMeasuring())
                {
                    _progress += 9;
                    if(_progress >= 70){
                        _progress = 70;
                    }
                    setProgress(_progress);
                    sendStateCommand();
                    if(_lastScanTime.addSecs(300) < QDateTime::currentDateTimeUtc())
                    {
                          setOTDRModuleState(STATE_GETINGSOR);
                    }
                }
                else if(isGettingSOR())
                {
                    if(_lastGetSorTime.addSecs(60) < QDateTime::currentDateTimeUtc())
                    {
                          setOTDRModuleState(STATE_MEASURED);
                          _MeasuredChannels.OTDRModule.channels = 0;
                    }
                    _progress += 9;
                    if(_progress >= 90){
                        _progress = 90;
                    }
                    setProgress(_progress);
                }

            }while(((_moduleMode == OTDR_WORK_MODE_SINGLE)&&(isMeasured()== false)) || (_moduleMode == OTDR_WORK_MODE_AUTO)||(getKeepRunning() == 1));
            setOTDRModuleState(STATE_MEASURED);
            qDebug() << "\n Stop Monitoring on module: " << _moduleIndex << endl;
            setProgress(0);
            _MeasuredChannels.OTDRModule.channels = 0;
            emit sigOTDRSetMode(_moduleIndex, OTDR_WORK_MODE_STOP);
            if(_pTcpSocket!=NULL){
                _pTcpSocket->close();
                delete _pTcpSocket;
                _pTcpSocket = NULL;
            }
            exit(0);
}

QOTDRModule::OTDRModuleState QOTDRModule::getOTDRModuleState()
{
    QMutexLocker locker(&gOTDRModule_mutex);
    return _state;
}

void QOTDRModule::setOTDRModuleState(OTDRModuleState state)
{
    QMutexLocker locker(&gOTDRModule_mutex);
    _state = state;
}

bool QOTDRModule::setSerialPortParam(QString serialPort, QSerialPort::BaudRate baudrate, QSerialPort::DataBits databits \
                                     ,QSerialPort::StopBits stopbits, QSerialPort::Parity parity, QSerialPort::FlowControl fctrl)
{
    QMutexLocker locker(&gOTDRModule_mutex);
    bool ret = false;

    _pSerialPort->setPortName(serialPort);
    _pSerialPort->setBaudRate(baudrate);
    _pSerialPort->setDataBits(databits);
    _pSerialPort->setStopBits(stopbits);
    _pSerialPort->setFlowControl(fctrl);

    ret = _pSerialPort->open(QIODevice::ReadWrite);
    if(ret!= true){
        QAgentApp::error(_moduleIndex, QString("Failed to open port %1, error: %2").arg(serialPort).arg(_pSerialPort->error()));
    }

    return ret;
}

void QOTDRModule::sendCommandWithResponse(quint16 module, QString cmdline, QByteArray *data)
{
//    QMutexLocker locker(&gOTDRModule_mutex);
    qDebug() << "["<< QThread::currentThreadId() << "] sendCommandWithResponse to "<< module << endl;
    QByteArray  cmdData = cmdline.toLatin1();
    cmdData.append(0x0D);
    cmdData.append(0x0A);
    cmdData.append(0x20);

    fprintf(stderr, "=>");
    quint16 i = 0;
    for(i = 0; i< cmdData.length(); i++){
       fprintf(stderr, " %02X", cmdData.at(i));
       fflush(stderr);
    }
    qDebug()<<endl;



    if(((_pTcpSocket!=NULL))&&(_pTcpSocket->state() == QAbstractSocket::ConnectedState)){
        _pIODevice = _pTcpSocket;
    }
    else if(_pSerialPort!=NULL)
    {
        _pIODevice = _pSerialPort;
    }

	if(_pIODevice != NULL){
	    _pIODevice->write(cmdData);
		
	    if(_pIODevice->waitForBytesWritten(WAIT_WRITE_TIMEOUT))
	    {
	        if(_pIODevice->waitForReadyRead(WAIT_READ_TIMEOUT)){
	            QByteArray response = _pIODevice->readAll();
	            while(_pIODevice->waitForReadyRead(50)){
	                response += _pIODevice->readAll();
	            }
	//            *data = response;
	            recvResponse(_moduleIndex,cmdline, response);
	        }
	         else
	        {
	            emit sigCatchException(_moduleIndex,"waitForReadyRead timeout");
	            QAgentApp::warning(_moduleIndex, QString("waitForReadyRead timeout"));
	            return;
	        }
	    }
	    else
	    {
	        emit sigCatchException(_moduleIndex,"waitForBytesWritten timeout");
	        QAgentApp::warning(_moduleIndex, QString("waitForBytesWritten timeout"));
	        return;
	    }
	}
}

void QOTDRModule::sendStateCommand()
{
// 如果在获取SOR或WAVELET数据的时候不要发任何东西了。
    QString cmdline = QString("STATE?");
    if(getOTDRModuleState() < STATE_GETINGSOR ){
        sendCommand(_moduleIndex,cmdline);
    }
}

void QOTDRModule::sendGetSorCommand()
{
if((getOTDRModuleState() == STATE_IDLING)||(getOTDRModuleState() == STATE_GETINGSOR)){
    if(_moduleIndex == 0){
        if(_MeasuredChannels.OTDRModule.I.ch1 == 0){
            QString cmdline = QString("getsor? %1").arg(0);
            setOTDRModuleState(STATE_GETINGSOR1);
            sendCommand(_moduleIndex,cmdline);
            _lastGetSorTime = QDateTime::currentDateTimeUtc();
        }
        if((_MeasuredChannels.OTDRModule.I.ch2 == 0)&&(getOTDRModuleState()==STATE_GOTSOR1)){
            QString cmdline = QString("getsor? %1").arg(1);
            setOTDRModuleState(STATE_GETINGSOR2);
            sendCommand(_moduleIndex,cmdline);

        }
        if((_MeasuredChannels.OTDRModule.I.ch3 == 0)&&(getOTDRModuleState()==STATE_GOTSOR2)){
            QString cmdline = QString("getsor? %1").arg(2);
            setOTDRModuleState(STATE_GETINGSOR3);
            sendCommand(_moduleIndex,cmdline);

        }
        if((_MeasuredChannels.OTDRModule.I.ch4 == 0)&&(getOTDRModuleState()==STATE_GOTSOR3)){
            QString cmdline = QString("getsor? %1").arg(3);
            setOTDRModuleState(STATE_GETINGSOR4);
            sendCommand(_moduleIndex,cmdline);

        }
    }
    if(_moduleIndex == 1){
        if(_MeasuredChannels.OTDRModule.I.ch5 == 0){
            QString cmdline = QString("getsor? %1").arg(0);
            setOTDRModuleState(STATE_GETINGSOR1);
            sendCommand(_moduleIndex,cmdline);
            _lastGetSorTime = QDateTime::currentDateTimeUtc();

        }
        if((_MeasuredChannels.OTDRModule.I.ch6 == 0)&&(getOTDRModuleState() == STATE_GOTSOR1)){
            QString cmdline = QString("getsor? %1").arg(1);
            setOTDRModuleState(STATE_GETINGSOR2);
            sendCommand(_moduleIndex,cmdline);

        }
        if((_MeasuredChannels.OTDRModule.I.ch7 == 0)&&(getOTDRModuleState()== STATE_GOTSOR2)){
            QString cmdline = QString("getsor? %1").arg(2);
            setOTDRModuleState(STATE_GETINGSOR3);
            sendCommand(_moduleIndex,cmdline);

        }
        if((_MeasuredChannels.OTDRModule.I.ch8 == 0)&&(getOTDRModuleState()==STATE_GOTSOR3)){
            QString cmdline = QString("getsor? %1").arg(3);
            setOTDRModuleState(STATE_GETINGSOR4);
            sendCommand(_moduleIndex,cmdline);

        }
    }
 }
}

void QOTDRModule::sendScanCommand()
{
    _lastScanTime = QDateTime::currentDateTimeUtc();

    QString cmdline = QString("SCAN");
    if(/*(getOTDRModuleState() == STATE_IDLING)||*/(getOTDRModuleState() == STATE_MEASURED)){
        setOTDRModuleState(STATE_MEASURING);
        sendCommand(_moduleIndex, cmdline);
    }
}

void QOTDRModule::setProgress(quint16 channel, quint16 progress)
{
    QMutexLocker    locker(&gOTDRModule_mutex);
    _MeasuringProgresss[channel] = progress;
	if(isMeasured()){
        emit this->sigSetProgress(channel,100);
    }
    else
    {
        emit this->sigSetProgress(channel,progress);
    }
}

void QOTDRModule::setProgress(quint16 progress)
{
    if(isMeasured()){
        emit this->sigSetProgress(_moduleIndex,100);
    }
    else
    {
        emit this->sigSetProgress(_moduleIndex,progress);
    }
}

quint16 QOTDRModule::getProgress(quint16 channel)
{
	return _MeasuringProgresss.value(channel,0);
}

quint16 QOTDRModule::getProgress()
{
	return _progress;
}

void QOTDRModule::increaseMeasuredCount(quint16 channel, quint32 count)
{
    QMutexLocker    locker(&gOTDRModule_mutex);
	QPST *pst = QPST::getInstance();
//	long	MaxCount = pst->m_product->m_pstIFMS1000.get_pstIFMS1000MeasureNumberSORStoredEachChannel(channel);
	quint32  temp = getMeasuredCount(channel);
	temp += count;
	_MeasuredCounts[channel]=temp;
	if(isMeasured()){
        emit this->sigSetMeasuredCount(channel,temp);
    }
}
quint32	QOTDRModule::getMeasuredCount(quint16 channel)
{
	return  _MeasuredCounts.value(channel, 0);
}

void QOTDRModule::increaseMeasuredSORFiles(quint16 channel, quint32 count)
{
		QMutexLocker	locker(&gOTDRModule_mutex);
	//	QPST *pst = QPST::getInstance();
	//	long	MaxCount = pst->m_product->m_pstIFMS1000.get_pstIFMS1000MeasureNumberSORStoredEachChannel(channel);
		quint32  temp = getMeasuredSORFiles(channel);
		temp += count;
		_MeasuredSORFiles[channel]=temp;
}
quint32 QOTDRModule::getMeasuredSORFiles(quint16 channel)
{
	return  _MeasuredSORFiles.value(channel, 0);
}


QByteArray QOTDRModule::generateOTDRTrapData(quint16 module, qint16 channel)
{
    QByteArray  data = QString("Traped on %1").arg(channel).toLatin1();
    QString     filename = getIFMSFingerFileName(channel);
    QFingerData    *oldFingerData = _OldFingers.value(filename);
    QFingerData    *newFingerData = _NewFingers.value(filename);

// TODO: 通过比较oldFingerDate和newFingerData生成trap数据包内容。
    return data;
}

void QOTDRModule::sendCommand(quint16 module, QString &cmdline)
{
    QByteArray  data;
    sendCommandWithResponse(module ,cmdline, &data);
}


QString QOTDRModule::getIFMSFingerFileName(qint16 channel)
{
    QString     filename = QAgentApp::getCacheDir()+QString("wrong");
    if(channel == 0){
            filename = QAgentApp::getCacheDir()+QString(CH1_FINGER_FILE);
    }
    if(channel == 1){
            filename = QAgentApp::getCacheDir()+QString(CH2_FINGER_FILE);
    }
    if(channel == 2){
            filename = QAgentApp::getCacheDir()+QString(CH3_FINGER_FILE);
    }
    if(channel == 3){
            filename = QAgentApp::getCacheDir()+QString(CH4_FINGER_FILE);
    }
    if(channel == 4){
            filename = QAgentApp::getCacheDir()+QString(CH5_FINGER_FILE);
    }
    if(channel == 5){
            filename = QAgentApp::getCacheDir()+QString(CH6_FINGER_FILE);
    }
    if(channel == 6){
            filename = QAgentApp::getCacheDir()+QString(CH7_FINGER_FILE);
    }
    if(channel == 7){
            filename = QAgentApp::getCacheDir()+QString(CH8_FINGER_FILE);
    }

    return filename;
}


QString QOTDRModule::getIFMSSorFileName(qint16 channel)
{
    QString     filename = QAgentApp::getCacheDir()+QString("wrong");
    if(channel == 0){
            filename = QAgentApp::getCacheDir()+QString(CH1_SOR_FILE);
    }
    if(channel == 1){
            filename = QAgentApp::getCacheDir()+QString(CH2_SOR_FILE);
    }
    if(channel == 2){
            filename = QAgentApp::getCacheDir()+QString(CH3_SOR_FILE);
    }
    if(channel == 3){
            filename = QAgentApp::getCacheDir()+QString(CH4_SOR_FILE);
    }
    if(channel == 4){
            filename = QAgentApp::getCacheDir()+QString(CH5_SOR_FILE);
    }
    if(channel == 5){
            filename = QAgentApp::getCacheDir()+QString(CH6_SOR_FILE);
    }
    if(channel == 6){
            filename = QAgentApp::getCacheDir()+QString(CH7_SOR_FILE);
    }
    if(channel == 7){
            filename = QAgentApp::getCacheDir()+QString(CH8_SOR_FILE);
    }

    return filename;
}


//=============================SLOTS====================================================

void QOTDRModule::onSendCommand(quint16 module, QString &cmdline)
{
    QByteArray  data;

    if(_moduleMode == OTDR_WORK_MODE_STOP){
        sendCommandWithResponse(module ,cmdline, &data);
    }
    else
    {
        qDebug() << "It's busy now, please try later..." << endl;
    }
}
//
//
//void QOTDRModule::onSetProgress(quint16 module, quint16 progress)
//{
//
//}

void QOTDRModule::onCatchException(quint16 module, const QString& info)
{

}

void QOTDRModule::recvResponse(quint16 module, QString &cmdline, QByteArray &data)
{
// TODO: 获取到sorfile之后转变成fingerdata[channel]
//    QString  command = cmdline;

    QSorFileBase    sorfile;
    QString         filename;
    int cmdcount = 0;

    fprintf(stderr, "<=");
    quint32  length = data.length();
    quint32  count = length;
    if(count > 64){
        count = 64;
    }
    quint16 i = 0;
    for(i = 0; i< count; i++){
       fprintf(stderr, " %02X", data.at(i));
       fflush(stderr);
    }
    qDebug()<<endl;

    if(length < 32){
        QString         responseString = QString(data);
        if(responseString.contains("state 0",Qt::CaseInsensitive)){
            setOTDRModuleState(STATE_IDLING);
        }
        if(responseString.contains("state 1",Qt::CaseInsensitive)){
            setOTDRModuleState(STATE_MEASURING);
        }
    }

    QStringList     qcmdlist = cmdline.split(" ", QString::SkipEmptyParts);

    cmdcount = qcmdlist.count();
   if(cmdline.contains("GETSOR?",Qt::CaseInsensitive)){ // 获取SOR文件
        qDebug() << "getsor? command" << endl;
        if(cmdcount == 2){
            QString channel = qcmdlist.at(1);
            qint16 ch = channel.toShort();
            sorfile._channel = _moduleIndex*4+ch;
            filename = getIFMSFingerFileName(sorfile._channel);
//TODO: 从串口获取的sor头四个字节是长度信息，需要摘除之后再处理
            quint32  OSRLen = length - 4;
//            memcpy(&OSRLen, data.mid(1,4).data(), sizeof(OSRLen));

            QByteArray  OSRRawData = data.mid(4);

            QString sorfilename = getIFMSSorFileName(sorfile._channel);
            QString fingername = getIFMSFingerFileName(sorfile._channel);
            qDebug() << "write sor to " << sorfilename << endl;

            if(!sorfilename.isEmpty()){
                QFile   file(sorfilename);
                if(file.open(QIODevice::WriteOnly)){
                    file.write(OSRRawData);
                    file.flush();
                    file.close();
                }
            }

            if(sorfile.parseData(OSRRawData.data(), OSRLen) == true){
                _OldFingers.swap(_NewFingers);
                QFingerData *p = sorfile.toFingerData();
                _NewFingers.insert(filename,p);
                emit this->sigOTDRChanged(_moduleIndex, sorfile._channel);
                increaseMeasuredCount(sorfile._channel, 1);
                p->toIFMSFingerFile(fingername);
            }
            if(ch == 1 ){
                setOTDRModuleState(STATE_GOTSOR1);
            }
            if(ch == 2 ){
                setOTDRModuleState(STATE_GOTSOR2);
            }
            if(ch == 3 ){
                setOTDRModuleState(STATE_GOTSOR3);
            }
            if(ch == 4 ){
                setOTDRModuleState(STATE_GOTSOR4);
            }
        }
   }

}

void QOTDRModule::onFileChanged(quint16 module, QString filename)
{

}

void QOTDRModule::onOTDRChanged(quint16 module, quint16 channel)
{
    QAgentApp::message(module, QString("OTDR channel %1 changed!").arg(channel));

    if(channel == 1){
        _MeasuredChannels.OTDRModule.I.ch1 = 1;
    }
    if(channel == 2){
        _MeasuredChannels.OTDRModule.I.ch2 = 1;
    }
    if(channel == 3){
        _MeasuredChannels.OTDRModule.I.ch3 = 1;
    }
    if(channel == 4){
        _MeasuredChannels.OTDRModule.I.ch4 = 1;
    }
    if(channel == 5){
        _MeasuredChannels.OTDRModule.I.ch5 = 1;
    }
    if(channel == 6){
        _MeasuredChannels.OTDRModule.I.ch6 = 1;
    }
    if(channel == 7){
        _MeasuredChannels.OTDRModule.I.ch7 = 1;
    }
    if(channel == 8){
        _MeasuredChannels.OTDRModule.I.ch8 = 1;
    }
    if(_moduleIndex == 0){
        if(_MeasuredChannels.OTDRModule.channels == 0xF0){

         setOTDRModuleState(STATE_MEASURED);
        _MeasuredChannels.OTDRModule.channels = 0;
        }
    }
    if(_moduleIndex == 1){
        if(_MeasuredChannels.OTDRModule.channels == 0x0F){
        setOTDRModuleState(STATE_MEASURED);
        _MeasuredChannels.OTDRModule.channels = 0;
        }
    }

    QByteArray  data = generateOTDRTrapData(module, channel);
    emit sigOTDRTrap(module, data);
}

void QOTDRModule::onSigOTDRSetMode(quint16 module, quint16 mode)
{
    QMutexLocker    locker(&gOTDRModule_mutex);
    if(module == _moduleIndex){
        _moduleMode = mode;
    }
}

void QOTDRModule::onSocketError(QAbstractSocket::SocketError  socketError)
{
    _tcpState = STATE_TCP_CONNECT_ERROR;
//    if(_pTcpSocket!=NULL){
//        _pTcpSocket->close();
//    }
//    qDebug() << "onSocketError" <<  socketError << " ." << endl;
}

void QOTDRModule::onSocketConnected()
{
    _tcpState = STATE_TCP_CONNECTED;
    qDebug() << "onSocketConnected" << endl;
}

void QOTDRModule::onSocketDisconnected()
{
    qDebug() << "onSocketDisconnected" << endl;
    _tcpState = STATE_TCP_DISCONNECTED;
}

void QOTDRModule::onTcpSocketAutoConnect()
{
    if((_tcpState != STATE_TCP_CONNECTED)&&(_tcpState != STATE_TCP_CONNECTING)){
//        qDebug() << "auto connect to module" << _moduleIndex << " with state " << _tcpState << "." << endl;
        initTcpConnection();
    }
}
