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
        _PortActives.insert(i, 0);
        _MeasuringStatus.insert(i, 0);
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

quint16 QOTDRModule::getModuleMode(quint16 module)
{
    QMutexLocker locker(&gOTDRModule_mutex);

    return _moduleMode;
}

void QOTDRModule::initModuleData()
{
    QPST *pst   = QPST::getInstance();
    int i = 0;
    int channel = 0;
	QString		single_finger_filename;
	QString		single_sor_filename;
	QString		first_finger_name;
	QString		first_sor_name;
	QString		current_finger_filename;
	QString		current_sor_filename;
	QString		stored_sor_name;
	
    for(i=0;i< CHANNELS_PER_MODULE; i++){
        channel = _moduleIndex*CHANNELS_PER_MODULE+i+1;
        single_finger_filename = QAgentApp::getCacheDir() + QString("IFMS_CH%1_finger_Single.bin").arg(channel);
		single_sor_filename = QAgentApp::getCacheDir() + QString("IFMS_CH%1_SOR_Single.bin").arg(channel);
		first_finger_name = QAgentApp::getCacheDir() + QString("IFMS_CH%1_finger_First.bin").arg(channel);
		first_sor_name = QAgentApp::getCacheDir() + QString("IFMS_CH%1_SOR_First.bin").arg(channel);
        current_finger_filename = QAgentApp::getCacheDir() + QString("IFMS_CH%1_finger_Current.bin").arg(channel);
		current_sor_filename =QAgentApp::getCacheDir() + QString("IFMS_CH%1_SOR_Current.bin").arg(channel);
		
        _PortActives[channel] = pst->m_product->m_pstIFMS1000.get_pstIFMS1000PortActive(channel);

        _OldFingers.insert(channel, new QFingerData());
        _NewFingers.insert(channel, new QFingerData());

		_SingleFingers.insert(channel, single_finger_filename);
		_SingleSORs.insert(channel, single_sor_filename);
		_FirstFingers.insert(channel, first_finger_name);
		_FirstSORs.insert(channel, first_sor_name);
		_CurrentFingers.insert(channel, current_finger_filename);
		_CurrentSORs.insert(channel, current_sor_filename);
    }
    // _watcher.addPath(QAgentApp::getCacheDir());
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

//                _pTcpSocket->abort();
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

            if(getModuleMode(_moduleIndex) == OTDR_WORK_MODE_STOP){
				setMeasuringStaus( _moduleIndex, OTDR_MEASURE_STATUS_IDLE);
                return;
            }
			else if(getModuleMode(_moduleIndex) == OTDR_WORK_MODE_AUTO)
			{
                setMeasuringStaus( _moduleIndex, OTDR_MEASURE_STATUS_AUTO_RUNNING);
			}
			else if(getModuleMode(_moduleIndex) == OTDR_WORK_MODE_SINGLE)
			{
                setMeasuringStaus( _moduleIndex, OTDR_MEASURE_STATUS_SINGLE_RUNNING);
			}
				
				
            sendScanCommand();

            do{
                qDebug() << "\n["<<QThread::currentThreadId() <<"] OTDR Module[" << _moduleIndex << "] P:" << _progress << "S:"<< getModuleState() << endl;
                if(getModuleState() == STATE_GOTSOR4){
                    setModuleState(STATE_MEASURED);
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
                          setModuleState(STATE_GETINGSOR);
                    }
                }
                else if(isGettingSOR())
                {
                    if(_lastGetSorTime.addSecs(60) < QDateTime::currentDateTimeUtc())
                    {
                          setModuleState(STATE_MEASURED);
                          _MeasuredChannels.OTDRModule.channels = 0;
                    }
                    _progress += 9;
                    if(_progress >= 90){
                        _progress = 90;
                    }
                    setProgress(_progress);
                }

            }while(((_moduleMode == OTDR_WORK_MODE_SINGLE)&&(isMeasured()== false)) || (_moduleMode == OTDR_WORK_MODE_AUTO)||(getKeepRunning() == 1));
            setModuleState(STATE_MEASURED);
            qDebug() << "\n Stop Monitoring on module: " << _moduleIndex << endl;
            setProgress(0);
            if(_moduleIndex == 0){
                _MeasuredChannels.OTDRModule.channels &= 0x0F;
            }
            else
            {
                _MeasuredChannels.OTDRModule.channels &= 0xF0;
            }
            setModuleMode(_moduleIndex, OTDR_WORK_MODE_STOP);
			
			setMeasuringStaus(_moduleIndex, OTDR_MEASURE_STATUS_SINGLE_DONE);
            if(_pTcpSocket!=NULL){
                _pTcpSocket->close();
                delete _pTcpSocket;
                _pTcpSocket = NULL;
            }
            exit(0);
}

QOTDRModule::ModuleState QOTDRModule::getModuleState()
{
    QMutexLocker locker(&gOTDRModule_mutex);
    return _state;
}

void QOTDRModule::setModuleState(ModuleState state)
{
    QMutexLocker locker(&gOTDRModule_mutex);
    _state = state;
}

void QOTDRModule::setModuleMode(quint16 module, quint16 mode)
{
    QMutexLocker    locker(&gOTDRModule_mutex);
    if(module == _moduleIndex){
        _moduleMode = mode;
       emit sigOTDRSetMode(_moduleIndex, mode);
    }
}

void QOTDRModule::setMeasuringStaus(quint16 module, quint32 status)
{
	quint16  i;
	quint16 channel;
    QMutexLocker    locker(&gOTDRModule_mutex);
	for(i = 0; i < CHANNELS_PER_MODULE; i ++)
		{
			channel = _moduleIndex * CHANNELS_PER_MODULE + i + 1;
			if(isChannelActive(channel)){
				_MeasuringStatus[channel] = status;
			}
			else
			{
                _MeasuringStatus[channel] = OTDR_MEASURE_STATUS_FAIL;
			}

            emit sigOTDRSetMeasuringStatus(channel, _MeasuringStatus[channel]);

		}

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
    if(getModuleState() < STATE_GETINGSOR ){
        sendCommand(_moduleIndex,cmdline);
    }
}

void QOTDRModule::sendGetSorCommand()
{
if((getModuleState() == STATE_IDLING)||(getModuleState() == STATE_GETINGSOR)){
    if(_moduleIndex == 0){
        if(_MeasuredChannels.OTDRModule.I.ch1 == 0){
            QString cmdline = QString("getsor? %1").arg(0);
            setModuleState(STATE_GETINGSOR1);
            sendCommand(_moduleIndex,cmdline);
            _lastGetSorTime = QDateTime::currentDateTimeUtc();
        }
        if((_MeasuredChannels.OTDRModule.I.ch2 == 0)&&(getModuleState()==STATE_GOTSOR1)){
            QString cmdline = QString("getsor? %1").arg(1);
            setModuleState(STATE_GETINGSOR2);
            sendCommand(_moduleIndex,cmdline);

        }
        if((_MeasuredChannels.OTDRModule.I.ch3 == 0)&&(getModuleState()==STATE_GOTSOR2)){
            QString cmdline = QString("getsor? %1").arg(2);
            setModuleState(STATE_GETINGSOR3);
            sendCommand(_moduleIndex,cmdline);

        }
        if((_MeasuredChannels.OTDRModule.I.ch4 == 0)&&(getModuleState()==STATE_GOTSOR3)){
            QString cmdline = QString("getsor? %1").arg(3);
            setModuleState(STATE_GETINGSOR4);
            sendCommand(_moduleIndex,cmdline);

        }
    }
    if(_moduleIndex == 1){
        if(_MeasuredChannels.OTDRModule.I.ch5 == 0){
            QString cmdline = QString("getsor? %1").arg(0);
            setModuleState(STATE_GETINGSOR1);
            sendCommand(_moduleIndex,cmdline);
            _lastGetSorTime = QDateTime::currentDateTimeUtc();

        }
        if((_MeasuredChannels.OTDRModule.I.ch6 == 0)&&(getModuleState() == STATE_GOTSOR1)){
            QString cmdline = QString("getsor? %1").arg(1);
            setModuleState(STATE_GETINGSOR2);
            sendCommand(_moduleIndex,cmdline);

        }
        if((_MeasuredChannels.OTDRModule.I.ch7 == 0)&&(getModuleState()== STATE_GOTSOR2)){
            QString cmdline = QString("getsor? %1").arg(2);
            setModuleState(STATE_GETINGSOR3);
            sendCommand(_moduleIndex,cmdline);

        }
        if((_MeasuredChannels.OTDRModule.I.ch8 == 0)&&(getModuleState()==STATE_GOTSOR3)){
            QString cmdline = QString("getsor? %1").arg(3);
            setModuleState(STATE_GETINGSOR4);
            sendCommand(_moduleIndex,cmdline);

        }
    }
 }
}

void QOTDRModule::sendScanCommand()
{
    _lastScanTime = QDateTime::currentDateTimeUtc();

    QString cmdline = QString("SCAN");
    if(/*(getModuleState() == STATE_IDLING)||*/(getModuleState() == STATE_MEASURED)){
        setModuleState(STATE_MEASURING);
        sendCommand(_moduleIndex, cmdline);
    }
    if(_moduleIndex == 0){
        _MeasuredChannels.OTDRModule.channels &= 0x0F;
    }
    else
    {
        _MeasuredChannels.OTDRModule.channels &= 0xF0;
    }
}

void QOTDRModule::setProgress(quint16 channel, quint16 progress)
{
//    QMutexLocker    locker(&gOTDRModule_mutex);
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
    int i = 0;
    for(i = 0; i <( _moduleIndex+1)*CHANNELS_PER_MODULE; i++){
            setProgress(i+1, progress);
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
    QPST *pst = QPST::getInstance();

    quint32  temp = getMeasuredCount(channel);
    temp += count;
	_MeasuredCounts[channel]=temp;

    emit this->sigSetMeasuredCount(channel,temp);
}

quint32	QOTDRModule::getMeasuredCount(quint16 channel)
{
	return  _MeasuredCounts.value(channel, 0);
}

void QOTDRModule::increaseMeasuredSORFiles(quint16 channel, quint32 count)
{
		QMutexLocker	locker(&gOTDRModule_mutex);
		quint32  temp = getMeasuredSORFiles(channel);
		temp += count;
		_MeasuredSORFiles[channel]=temp;
}
quint32 QOTDRModule::getMeasuredSORFiles(quint16 channel)
{
	return  _MeasuredSORFiles.value(channel, 0);
}


QByteArray QOTDRModule::generateTrapData(quint16 module, quint16 channel)
{
    QByteArray  data = QString("Traped on %1").arg(channel).toLatin1();

    QFingerData    *oldFingerData = _OldFingers.value(channel);
    QFingerData    *newFingerData = _NewFingers.value(channel);

// TODO: 通过比较oldFingerDate和newFingerData生成trap数据包内容。
    return data;
}

void QOTDRModule::sendCommand(quint16 module, QString &cmdline)
{
    QByteArray  data;
    sendCommandWithResponse(module ,cmdline, &data);
}

int QOTDRModule::isChannelActive(quint16 channel)
{
    QPST *pst = QPST::getInstance();
    if(pst!=NULL){
        return pst->m_product->m_pstIFMS1000.get_pstIFMS1000PortActive(channel);;
    }
    else // not active
    {
        return 0;
    }
}

QString QOTDRModule::getIFMSFingerFileName(quint16 channel)
{
    QString     filename = QString("");
	QString		emptyfile = QString("");
	quint32		count = getMeasuredCount(channel);
	quint16		mode = getModuleMode(channel);
	if(mode == OTDR_WORK_MODE_AUTO)	{
		if(count == 0){
			filename = _FirstFingers.value(channel, emptyfile);
			}
		else
			{
			filename = _CurrentFingers.value(channel, emptyfile);
			}
	}
	else if(mode == OTDR_WORK_MODE_SINGLE)	{
        filename = _SingleFingers.value(channel, emptyfile);
		}

    return filename;
}


QString QOTDRModule::getIFMSSorFileName(quint16 channel)
{
    QString     filename = QString("");
	QString		emptyfile = QString("");
	quint32		count = getMeasuredCount(channel);
	quint16		mode = getModuleMode(channel);
	if(mode == OTDR_WORK_MODE_AUTO)	{
		if(count == 0){
			filename = _FirstSORs.value(channel, emptyfile);
			}
		else
			{
			filename = _CurrentSORs.value(channel, emptyfile);
			}
	}
	else if(mode == OTDR_WORK_MODE_SINGLE)	{
        filename = _SingleSORs.value(channel, emptyfile);
		}

    return filename;

}

void QOTDRModule::OTDRChanged(quint16 module, quint16 channel)
{
    QAgentApp::message(module, QString("OTDR channel %1 changed!").arg(channel));

    QByteArray  data = generateTrapData(module, channel);
// TODO: if finger data changed, store the sor to DATA_DIR of NAND Flash 	

// TODO: if inger data not changed, trap normal 
    emit sigOTDRTrap(module, data);
}

void QOTDRModule::recvResponse(quint16 module, QString &cmdline, QByteArray &data)
{
    QSorFileBase    sorfile;
    QString         filename;
    int cmdcount = 0;
    quint32  length = data.length();

#ifdef	DUMP_MESSAGE 
	fprintf(stderr, "<=");
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
#endif

    if(length < 32){
        QString         responseString = QString(data);
        if(responseString.contains("state 0",Qt::CaseInsensitive)){
            setModuleState(STATE_IDLING);
        }
        if(responseString.contains("state 1",Qt::CaseInsensitive)){
            setModuleState(STATE_MEASURING);
        }
    }

    QStringList     qcmdlist = cmdline.split(" ", QString::SkipEmptyParts);
    cmdcount = qcmdlist.count();
	
   if(cmdline.contains("GETSOR?",Qt::CaseInsensitive)){ // 获取SOR文件
        qDebug() << "getsor? command" << endl;
        if(cmdcount == 2){
            QString channel = qcmdlist.at(1);
            quint16 ch = _moduleIndex*4 + channel.toShort()+1;
            sorfile._channel = ch;
//TODO: 从串口获取的sor头四个字节是长度信息，需要摘除之后再处理
            quint32  OSRLen = length - 4;
//          memcpy(&OSRLen, data.mid(1,4).data(), sizeof(OSRLen));

            QByteArray  OSRRawData = data.mid(4);
			if(isChannelActive(ch)){
	            QString sorfilename = getIFMSSorFileName(ch);
	            QString fingername = getIFMSFingerFileName(ch);

	            if(!sorfilename.isEmpty()){
	                qDebug() << "write sor to " << sorfilename << endl;

	                QFile   file(sorfilename);
	                if(file.open(QIODevice::WriteOnly)){
	                    file.write(OSRRawData);
	                    file.flush();
	                    file.close();
	                }
	                qDebug() << "write finger to " << fingername << endl;

					if(sorfile.parseData(OSRRawData.data(), OSRLen) == true){
					//		_OldFingers.swap(_NewFingers);
							QFingerData *p = sorfile.toFingerData();
                            if(getModuleMode(_moduleIndex) == OTDR_WORK_MODE_AUTO ){
									if(getMeasuredCount(ch) == 0){
										_OldFingers.insert(ch, p);
									}
									_NewFingers.insert(ch,p);
									
									increaseMeasuredCount(ch, 1);
								
									OTDRChanged(_moduleIndex, ch);
								}
							p->toIFMSFingerFile(fingername);
					}
	            }
				//TODO: emit measuringstatus
				/*
				pstIFMS1000MeasureStatus:
				0. Idle. The port is idle now. 
				1. Auto measurement is running. 
				2. Single OTDR measurement is running. 
				3. Single OTDR measurement is done. 
				4. Measurement Failure. 
				*/
			}
            else
            {
                qDebug() << "Channel " << ch << "is not active!!" << endl;
                setMeasuringStaus(ch, OTDR_MEASURE_STATUS_FAIL);
            }

            if((ch-1)%CHANNELS_PER_MODULE == 0 ){
                setModuleState(STATE_GOTSOR1);
            }
            if((ch-1)%CHANNELS_PER_MODULE == 1 ){
                setModuleState(STATE_GOTSOR2);
            }
            if((ch-1)%CHANNELS_PER_MODULE == 2 ){
                setModuleState(STATE_GOTSOR3);
            }
            if((ch-1)%CHANNELS_PER_MODULE == 3 ){
                (STATE_GOTSOR4);
            }

            if(ch == 1){
                _MeasuredChannels.OTDRModule.I.ch1 = 1;
            }
            if(ch == 2){
                _MeasuredChannels.OTDRModule.I.ch2 = 1;
            }
            if(ch == 3){
                _MeasuredChannels.OTDRModule.I.ch3 = 1;
            }
            if(ch == 4){
                _MeasuredChannels.OTDRModule.I.ch4 = 1;
            }
            if(ch == 5){
                _MeasuredChannels.OTDRModule.I.ch5 = 1;
            }
            if(ch == 6){
                _MeasuredChannels.OTDRModule.I.ch6 = 1;
            }
            if(ch == 7){
                _MeasuredChannels.OTDRModule.I.ch7 = 1;
            }
            if(ch == 8){
                _MeasuredChannels.OTDRModule.I.ch8 = 1;
            }
			
			if(_moduleIndex == 0){
				if(_MeasuredChannels.OTDRModule.channels == 0xF0){
			
				 setModuleState(STATE_MEASURED);
				_MeasuredChannels.OTDRModule.channels = 0;
				}
			}
			if(_moduleIndex == 1){
				if(_MeasuredChannels.OTDRModule.channels == 0x0F){
				setModuleState(STATE_MEASURED);
				_MeasuredChannels.OTDRModule.channels = 0;
				}
			}
        }
   }

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

void QOTDRModule::onCatchException(quint16 module, const QString& info)
{

}

void QOTDRModule::onFileChanged(quint16 module, QString filename)
{

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
//    if((_tcpState != STATE_TCP_CONNECTED)&&(_tcpState != STATE_TCP_CONNECTING)){
        qDebug() << "auto connect to module" << _moduleIndex << " with state " << _tcpState << "." << endl;
        initTcpConnection();
//    }
}
