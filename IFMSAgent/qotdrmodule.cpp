#include <QSerialPort>
#include <QDebug>
#include <QMutexLocker>
#include <QMutex>
#include <QFile>
#include <QDir>
#include <QFileInfo>
#include <QDataStream>
#include <QIODevice>
#include <QThread>
#include <QString>
#include <QStringList>
#include <QChar>
#include <QByteArray>

#include <math.h>
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
        _SORsChanged.insert(i,false);
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
        single_sor_filename = QAgentApp::getCacheDir() + QString("IFMS_CH%1_SOR_Single.sor").arg(channel);
		first_finger_name = QAgentApp::getCacheDir() + QString("IFMS_CH%1_finger_First.bin").arg(channel);
        first_sor_name = QAgentApp::getCacheDir() + QString("IFMS_CH%1_SOR_First.sor").arg(channel);
        current_finger_filename = QAgentApp::getCacheDir() + QString("IFMS_CH%1_finger_Current.bin").arg(channel);
        current_sor_filename =QAgentApp::getCacheDir() + QString("IFMS_CH%1_SOR_Current.sor").arg(channel);
		
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
            _progress = 0;
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

            sendScanCommand();

            do{
                qDebug() << "\n["<<QThread::currentThreadId() <<"] OTDR Module[" << _moduleIndex << "] P:" << _progress << "S:"<< getModuleState() << endl;
                if(getModuleState() == STATE_GOTSOR4){
                    setModuleState(STATE_MEASURED);
                }

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
            if(getModuleMode(_moduleIndex) == OTDR_WORK_MODE_SINGLE){
                setMeasuringStaus(_moduleIndex, OTDR_MEASURE_STATUS_SINGLE_DONE);
            }
            else if(getModuleMode(_moduleIndex) == OTDR_WORK_MODE_AUTO)
            {
                setMeasuringStaus(_moduleIndex, OTDR_MEASURE_STATUS_IDLE);
            }
            setModuleMode(_moduleIndex, OTDR_WORK_MODE_STOP);
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

//    fprintf(stderr, "=>");
//    quint16 i = 0;
//    for(i = 0; i< cmdData.length(); i++){
//       fprintf(stderr, " %02X", cmdData.at(i));
//       fflush(stderr);
//    }
    qDebug()<< "=>" << cmdline << endl;



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
    _progress = progress;
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

bool  QOTDRModule::storeCurrentSOR(quint16 channel)
{
        bool 	ret = false;
        QString srcFile;
        if(getMeasuredCount(channel) <= 1){
            srcFile = _FirstSORs.value(channel);
        }
        else
        {
            srcFile = _CurrentSORs.value(channel);
        }
        QString	 dstFile = QAgentApp::getCacheDir() +QString("IFMS_CH%1_%2.sor").arg(channel).arg(getMeasuredCount(channel));

		ret = QFile::exists(srcFile);
		if(ret == false){
			return ret;
		}
		else
		{
			QDir *createfile = new QDir;
			bool isExist = createfile->exists(dstFile);
			if(isExist){
				createfile->remove(dstFile);
			}

			ret = QFile::copy(srcFile, dstFile);
			if(ret == false)
			{
				return ret;
			}
			else
			{
				increaseMeasuredSORFiles(channel, 1);
				return true;
			}
		}

	return ret;
}


QStringList QOTDRModule::generateTrapData(quint16 module, quint16 channel)
{
    QStringList  data;
	QString		 trap = QString("");
    quint16		oldEventNums;
    quint16		newEventNums;
    float oldTotalLength;
    float newTotalLength;
    float point1EndtoEndLoss;
    float oldEndtoEndLoss;
	float newEndtoEndLoss;
    float oldEventPosition;
    float newEventPosition;
    float oldEventLoss;
    float newEventLoss;

    float pstIFMS1000MeasureFiberLengthChangeThreshold;
    float pstIFMS1000MeasureEndToEndLossHighThreshold;
    float pstIFMS1000MeasureEndToEndLossMiddleThreshold;
    float pstIFMS1000MeasureEndToEndLossLowThreshold;
    float pstIFMS1000MeasureNewLossCriticalThreshold;
    float pstIFMS1000MeasureNewLossMajorThreshold;
    float pstIFMS1000MeasureNewLossMinorThreshold;
    float pstIFMS1000MeasureOldLossCriticalThreshold;
    float pstIFMS1000MeasureOldLossMajorThreshold;
    float pstIFMS1000MeasureOldLossMinorThreshold;
    QFingerData    *oldFingerData = _OldFingers.value(channel);
    QFingerData    *newFingerData = _NewFingers.value(channel);
	if((oldFingerData == NULL) || (newFingerData == NULL))
	{
		data.append(trap);
		return data;
	}
	QPST		   *pst = QPST::getInstance();

    float pstIFMS1000MeasureRefIndex = pst->m_product->m_pstIFMS1000.get_pstIFMS1000MeasureRefIndex(channel).toFloat();

    pstIFMS1000MeasureFiberLengthChangeThreshold = pst->m_product->m_pstIFMS1000.get_pstIFMS1000MeasureFiberLengthChangeThreshold(channel).toFloat();
    pstIFMS1000MeasureEndToEndLossHighThreshold = pst->m_product->m_pstIFMS1000.get_pstIFMS1000MeasureEndToEndLossHighThreshold(channel).toFloat();
    pstIFMS1000MeasureEndToEndLossMiddleThreshold = pst->m_product->m_pstIFMS1000.get_pstIFMS1000MeasureEndToEndLossMiddleThreshold(channel).toFloat();
    pstIFMS1000MeasureEndToEndLossLowThreshold = pst->m_product->m_pstIFMS1000.get_pstIFMS1000MeasureEndToEndLossLowThreshold(channel).toFloat();
    pstIFMS1000MeasureNewLossCriticalThreshold = pst->m_product->m_pstIFMS1000.get_pstIFMS1000MeasureNewLossCriticalThreshold(channel).toFloat();
    pstIFMS1000MeasureNewLossMajorThreshold = pst->m_product->m_pstIFMS1000.get_pstIFMS1000MeasureNewLossMajorThreshold(channel).toFloat();
    pstIFMS1000MeasureNewLossMinorThreshold = pst->m_product->m_pstIFMS1000.get_pstIFMS1000MeasureNewLossMinorThreshold(channel).toFloat();
    pstIFMS1000MeasureOldLossCriticalThreshold = pst->m_product->m_pstIFMS1000.get_pstIFMS1000MeasureOldLossCriticalThreshold(channel).toFloat();
    pstIFMS1000MeasureOldLossMajorThreshold = pst->m_product->m_pstIFMS1000.get_pstIFMS1000MeasureOldLossMajorThreshold(channel).toFloat();
    pstIFMS1000MeasureOldLossMinorThreshold = pst->m_product->m_pstIFMS1000.get_pstIFMS1000MeasureOldLossMinorThreshold(channel).toFloat();
    oldTotalLength = oldFingerData->getLength() *( C_LIGHT_SPEED/(pstIFMS1000MeasureRefIndex * pow(10.0,13)));
    newTotalLength = newFingerData->getLength() *( C_LIGHT_SPEED/(pstIFMS1000MeasureRefIndex * pow(10.0,13)));

	oldEventNums = oldFingerData->mIFMSFingerData.NumberOfEvents;
	newEventNums = newFingerData->mIFMSFingerData.NumberOfEvents;

    float delta = qAbs(newTotalLength - oldTotalLength);
	
    if ( delta >= pstIFMS1000MeasureFiberLengthChangeThreshold/1000)
	{
		// TODO: 光纤长度变化
		trap = QString("CH%1,A,%2,%3,%4,%5,%6").arg(channel).arg(\
											OTDR_TRAP_SOURCE_LENGTH).arg(\
											getMeasuredCount(channel)).arg(\
                                            oldTotalLength).arg(\
                                            newTotalLength).arg(0);
		data.append(trap);
        _SORsChanged[channel] = true;
	}
//	else  // 光纤长度变化没有超过阈值
	{
		// TODO: 比较端到端损耗
        oldEndtoEndLoss = (float)oldFingerData->mIFMSFingerData.EndtoEndLoss/1000;
        newEndtoEndLoss = (float)newFingerData->mIFMSFingerData.EndtoEndLoss/1000;
        point1EndtoEndLoss = newTotalLength/10;
        if(qAbs(oldEndtoEndLoss - newEndtoEndLoss ) >= qMin(pstIFMS1000MeasureEndToEndLossHighThreshold , point1EndtoEndLoss))
		{
			trap = QString("CH%1,B,%2,%3,%4,%5,%6").arg(channel).arg(\
											OTDR_TRAP_SOURCE_EEMAIN).arg(\
											getMeasuredCount(channel)).arg(\
											oldEndtoEndLoss).arg(\
											newEndtoEndLoss).arg(0);
			data.append(trap);
            _SORsChanged[channel] = true;

        }
        else if((qAbs(oldEndtoEndLoss - newEndtoEndLoss) >= pstIFMS1000MeasureEndToEndLossMiddleThreshold)&&(qAbs(oldEndtoEndLoss - newEndtoEndLoss) < qMin(pstIFMS1000MeasureEndToEndLossHighThreshold , point1EndtoEndLoss)))
		{
			trap = QString("CH%1,C,%2,%3,%4,%5,%6").arg(channel).arg(\
											OTDR_TRAP_SOURCE_EEMINOR).arg(\
											getMeasuredCount(channel)).arg(\
											oldEndtoEndLoss).arg(\
											newEndtoEndLoss).arg(0);
			data.append(trap);
            _SORsChanged[channel] = true;

        }
		
		// TODO: 事件消失, 新增, 变化
		int i = 0;
		int j = 0;
        int k = 0;
        for(i=0; i < oldEventNums; i++){
			oldFingerData->mIFMSFingerData.vIFMSEvents[i].EventType = EVENT_TYPE_OLD;
			oldFingerData->mIFMSFingerData.vIFMSEvents[i].EventType |= EVENT_TYPE_DISAPPEAR;

            for(j=k; j< newEventNums-1; j++)
				{
				newFingerData->mIFMSFingerData.vIFMSEvents[j].EventType = EVENT_TYPE_NEW;
                oldEventPosition = (float)oldFingerData->mIFMSFingerData.vIFMSEvents[i].EventPosition * ( C_LIGHT_SPEED/(pstIFMS1000MeasureRefIndex * pow(10.0,13)));
                newEventPosition = (float)newFingerData->mIFMSFingerData.vIFMSEvents[j].EventPosition * ( C_LIGHT_SPEED/(pstIFMS1000MeasureRefIndex * pow(10.0,13)));

                oldEventLoss = (float)oldFingerData->mIFMSFingerData.vIFMSEvents[i].EventLoss/1000;
                newEventLoss = (float)newFingerData->mIFMSFingerData.vIFMSEvents[j].EventLoss/1000;

                if(qAbs(newEventPosition - oldEventPosition ) < 0.1f)
					{
						oldFingerData->mIFMSFingerData.vIFMSEvents[i].EventType &= (~EVENT_TYPE_DISAPPEAR);     // 旧的没有消失
						newFingerData->mIFMSFingerData.vIFMSEvents[j].EventType &= (~EVENT_TYPE_NEW); // 新的不是新增
						oldFingerData->mIFMSFingerData.vIFMSEvents[i].EventType |= EVENT_TYPE_CHANGE_LITTLE; // 旧的有变化，暂时未知，比较增益

                        if(qAbs(newEventLoss - oldEventLoss) >= pstIFMS1000MeasureOldLossCriticalThreshold)
						{
							// 变化，紧急
						oldFingerData->mIFMSFingerData.vIFMSEvents[i].EventType |= EVENT_TYPE_CHANGE_CRITICAL;
						trap = QString("CH%1,A,%2,%3,%4,%5,%6").arg(channel).arg(\
														OTDR_TRAP_SOURCE_ECHANGECRITICAL).arg(\
														getMeasuredCount(channel)).arg(\
                                                        oldEventPosition).arg(\
                                                        oldEventLoss).arg(\
                                                        newEventLoss);
						data.append(trap);
                        _SORsChanged[channel] = true;

                        }
                        else if(qAbs(newEventLoss - oldEventLoss) >= pstIFMS1000MeasureOldLossMajorThreshold)
						{
							// 变化，主要
						oldFingerData->mIFMSFingerData.vIFMSEvents[i].EventType |= EVENT_TYPE_CHANGE_MAIN;
                        trap = QString("CH%1,B,%2,%3,%4,%5,%6").arg(channel).arg(\
														OTDR_TRAP_SOURCE_ECHANGEMAIN).arg(\
														getMeasuredCount(channel)).arg(\
                                                        oldEventPosition).arg(\
                                                        oldEventLoss).arg(\
                                                        newEventLoss);
						data.append(trap);
                        _SORsChanged[channel] = true;

                        }
                        else if(qAbs(newEventLoss - oldEventLoss) >= pstIFMS1000MeasureOldLossMinorThreshold)
						{
							// 变化，次要
						oldFingerData->mIFMSFingerData.vIFMSEvents[i].EventType |= EVENT_TYPE_CHANGE_MINOR;
                        trap = QString("CH%1,C,%2,%3,%4,%5,%6").arg(channel).arg(\
														OTDR_TRAP_SOURCE_ECHANGEMINOR).arg(\
														getMeasuredCount(channel)).arg(\
                                                        oldEventPosition).arg(\
                                                        oldEventLoss).arg(\
                                                        newEventLoss);
						data.append(trap);
                        _SORsChanged[channel] = true;

                        }
                        k++;
//                        break;
					}

				}
		}
		// 检查消失的

        for(i=0;i<oldEventNums-1;i++)
		{
            oldEventPosition = (float)oldFingerData->mIFMSFingerData.vIFMSEvents[i].EventPosition * ( C_LIGHT_SPEED/(pstIFMS1000MeasureRefIndex * pow(10.0,13)));
            if(oldFingerData->mIFMSFingerData.vIFMSEvents[i].EventType == (EVENT_TYPE_OLD | EVENT_TYPE_DISAPPEAR))
			{
                trap = QString("CH%1,D,%2,%3,%4,%5,%6").arg(channel).arg(\
												OTDR_TRAP_SOURCE_EDISAPPER).arg(\
												getMeasuredCount(channel)).arg(\
                                                oldEventPosition).arg(0).arg(0);
				data.append(trap);
                _SORsChanged[channel] = true;

            }
		}
		// 检查新增的
        for(i=0;i<newEventNums-1;i++)
		{
            newEventPosition = (float)newFingerData->mIFMSFingerData.vIFMSEvents[i].EventPosition * ( C_LIGHT_SPEED/(pstIFMS1000MeasureRefIndex * pow(10.0,13)));
            newEventLoss = (float)newFingerData->mIFMSFingerData.vIFMSEvents[i].EventLoss/1000;
            if(newFingerData->mIFMSFingerData.vIFMSEvents[i].EventType == EVENT_TYPE_NEW)
			{
                if(newEventLoss >= pstIFMS1000MeasureNewLossCriticalThreshold )
					{
					newFingerData->mIFMSFingerData.vIFMSEvents[i].EventType |= EVENT_TYPE_NEW_CRITICAL;
					trap = QString("CH%1,A,%2,%3,%4,%5,%6").arg(channel).arg(\
													OTDR_TRAP_SOURCE_ENEWCRITICAL).arg(\
													getMeasuredCount(channel)).arg(\
                                                    newEventPosition).arg(\
                                                    newEventLoss).arg(0);
					data.append(trap);
                    _SORsChanged[channel] = true;

					}
                else if(newEventLoss >= pstIFMS1000MeasureNewLossMajorThreshold )
					{
					newFingerData->mIFMSFingerData.vIFMSEvents[i].EventType |= EVENT_TYPE_NEW_MAIN;
                    trap = QString("CH%1,B,%2,%3,%4,%5,%6").arg(channel).arg(\
													OTDR_TRAP_SOURCE_ENEWMAIN).arg(\
													getMeasuredCount(channel)).arg(\
                                                    newEventPosition).arg(\
                                                    newEventLoss).arg(0);
					data.append(trap);
                    _SORsChanged[channel] = true;

                    }
                else if(newEventLoss >= pstIFMS1000MeasureNewLossMinorThreshold )
					{
					newFingerData->mIFMSFingerData.vIFMSEvents[i].EventType |= EVENT_TYPE_NEW_MINOR;
                    trap = QString("CH%1,C,%2,%3,%4,%5,%6").arg(channel).arg(\
													OTDR_TRAP_SOURCE_ENEWMINOR).arg(\
													getMeasuredCount(channel)).arg(\
                                                    newEventPosition).arg(\
                                                    newEventLoss).arg(0);
					data.append(trap);
                    _SORsChanged[channel] = true;

                    }
			}
		}
		
	}
    if(_SORsChanged.value(channel) == false){
        trap = QString("CH%1,E,%2,%3,0,0,0").arg(channel).arg(OTDR_TRAP_SOURCE_NORMAL).arg(getMeasuredCount(channel));
        data.append(trap);
    }
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
    QString trap;
    bool    flag;
    int i;
    quint32     MaxStoredSORNumber;
    QAgentApp::message(module, QString("OTDR channel %1 changed!").arg(channel));
    QPST *pst = QPST::getInstance();
    MaxStoredSORNumber = pst->m_product->m_pstIFMS1000.get_pstIFMS1000MeasureNumberSORStoredEachChannel(channel).toInt();

    QStringList  data = generateTrapData(module, channel);
    flag =  _SORsChanged.value(channel);

    if((flag == true)&&(getMeasuredSORFiles(channel)< MaxStoredSORNumber)){
        storeCurrentSOR(channel);
        _SORsChanged[channel] = false;
    }

    for(i=0;i<data.size();i++){
        trap = data.at(i);
        emit sigOTDRTrap(module, trap);
    }
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
                                    increaseMeasuredCount(ch, 1);
                                    if(getMeasuredCount(ch) == 1){
                                        // TODO: verify the sor data
										_OldFingers.insert(ch, p);
                                        storeCurrentSOR(ch);
									}
									_NewFingers.insert(ch,p);
                                    if(getMeasuredCount(ch) > 1){
                                       OTDRChanged(_moduleIndex, ch);
                                    }
//                                    increaseMeasuredCount(ch, 1);
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
