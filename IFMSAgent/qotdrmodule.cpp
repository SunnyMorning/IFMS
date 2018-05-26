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
    _measureCount = 0;
    _moduleMode = OTDR_WORK_MODE_STOP;
    _pSerialPort = new QSerialPort();
    _pTcpSocket = new QTcpSocket();
    if(_moduleIndex == 0){
        setSerialPortParam(QString(UART_OF_MODULE1));
    }
    else
    {
        setSerialPortParam(QString(UART_OF_MODULE2));
    }

    _timerTCPKeepAlive = new QTimer();
    _timerTCPKeepAlive->setInterval(KEEP_ALIVE_TIMEOUT);
    _timerTCPKeepAlive->start();
    _tcpState = STATE_TCP_INIT;
}

QOTDRModule::~QOTDRModule()
{
    if(_pSerialPort != NULL){
        delete _pSerialPort;
        _pSerialPort = NULL;
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
        filename = QFingerData::getIFMSFingerFileName(1);
        initFingerBinFile(filename);
         _OldFingers.insert(filename, new QFingerData(this));
         _NewFingers.insert(filename, new QFingerData(this));

         filename = QFingerData::getIFMSFingerFileName(2);
         initFingerBinFile(filename);
          _OldFingers.insert(filename, new QFingerData(this));
          _NewFingers.insert(filename, new QFingerData(this));

          filename = QFingerData::getIFMSFingerFileName(3);
          initFingerBinFile(filename);
           _OldFingers.insert(filename, new QFingerData(this));
           _NewFingers.insert(filename, new QFingerData(this));

           filename = QFingerData::getIFMSFingerFileName(4);
           initFingerBinFile(filename);
            _OldFingers.insert(filename, new QFingerData(this));
            _NewFingers.insert(filename, new QFingerData(this));
    }

    if(getModuleIndex() == 1 ){
        filename = QFingerData::getIFMSFingerFileName(5);
        initFingerBinFile(filename);
         _OldFingers.insert(filename, new QFingerData(this));
         _NewFingers.insert(filename, new QFingerData(this));

         filename = QFingerData::getIFMSFingerFileName(6);
         initFingerBinFile(filename);
          _OldFingers.insert(filename, new QFingerData(this));
          _NewFingers.insert(filename, new QFingerData(this));

          filename = QFingerData::getIFMSFingerFileName(7);
          initFingerBinFile(filename);
           _OldFingers.insert(filename, new QFingerData(this));
           _NewFingers.insert(filename, new QFingerData(this));

           filename = QFingerData::getIFMSFingerFileName(8);
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
                qDebug() << "Failed to connect to " << host << "in " << TCP_CONNECT_TIMEOUT <<"seconds\n" << endl;

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
                //qDebug() << "Failed to connect to " << host << "in " << timeout <<"seconds\n" << endl;

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
//    connect(this, SIGNAL(sigRecvResponse(quint16, QString&,QByteArray&)), this, SLOT(onRecvResponse(quint16, QString&, QByteArray&)),Qt::DirectConnection);

    connect(_pTcpSocket, SIGNAL(connected()), this, SLOT(onSocketConnected()));
    connect(_pTcpSocket, SIGNAL(disconnected()),this, SLOT(onSocketDisconnected()));
    connect(_pTcpSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(onSocketError(QAbstractSocket::SocketError)));
    connect(_timerTCPKeepAlive, SIGNAL(timeout()), this, SLOT(onTcpSocketAutoConnect()));

//  connect(&_watcher, SIGNAL(fileChanged(const QString)), this, SLOT(onFileChanged(QString)));
//  connect(&_watcher, SIGNAL(directoryChanged(const QString)), this, SLOT(onFileChanged(QString)));
    initTcpConnection();
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
    qDebug() << "["<< QThread::currentThreadId() << "] sendCommandWithResponse"<<endl;
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
    else
    {
        _pIODevice = _pSerialPort;
    }

    _pIODevice->write(cmdData);
    if(_pIODevice->waitForBytesWritten(WAIT_WRITE_TIMEOUT))
    {
        if(_pIODevice->waitForReadyRead(WAIT_READ_TIMEOUT)){
            QByteArray response = _pIODevice->readAll();
            while(_pIODevice->waitForReadyRead(50)){
                response += _pIODevice->readAll();
            }
//            *data = response;
//            emit sigRecvResponse(_moduleIndex,cmdline, response);
            onRecvResponse(_moduleIndex,cmdline, response);
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

void QOTDRModule::sendStateCommand()
{
// 如果在获取SOR或WAVELET数据的时候不要发任何东西了。
    QString cmdline = QString("STATE?");
    if(getOTDRModuleState() < STATE_GETINGSOR ){
        emit    this->sigSendCommand(_moduleIndex,cmdline);
    }
}

void QOTDRModule::sendGetSorCommand()
{
//    int i = 0;
//    for(i=0;i<4;i++){
//        QString cmdline = QString("getsor? %1\r\n").arg(i);
//        if(getOTDRModuleState() == STATE_IDLING ){
//                emit this->sigSendCommand(cmdline);
//                setOTDRModuleState(STATE_GETINGSOR);
//        }
//        QThread::sleep(10);
//    }
if((getOTDRModuleState() == STATE_IDLING)||(getOTDRModuleState() == STATE_GETINGSOR)){
    if(_moduleIndex == 0){
        if(_MeasuredChannels.OTDRModule.I.ch1 == 0){
            QString cmdline = QString("getsor? %1").arg(0);
            emit this->sigSendCommand(_moduleIndex,cmdline);
            _lastGetSorTime = QDateTime::currentDateTimeUtc();
            setOTDRModuleState(STATE_GETINGSOR1);
        }
        if((_MeasuredChannels.OTDRModule.I.ch2 == 0)&&(getOTDRModuleState()==STATE_GETINGSOR1)){
            QString cmdline = QString("getsor? %1").arg(1);
            emit this->sigSendCommand(_moduleIndex,cmdline);
            setOTDRModuleState(STATE_GETINGSOR2);
        }
        if((_MeasuredChannels.OTDRModule.I.ch3 == 0)&&(getOTDRModuleState()==STATE_GETINGSOR2)){
            QString cmdline = QString("getsor? %1").arg(2);
            emit this->sigSendCommand(_moduleIndex,cmdline);
            setOTDRModuleState(STATE_GETINGSOR3);
        }
        if((_MeasuredChannels.OTDRModule.I.ch4 == 0)&&(getOTDRModuleState()==STATE_GETINGSOR3)){
            QString cmdline = QString("getsor? %1").arg(3);
            emit this->sigSendCommand(_moduleIndex,cmdline);
            setOTDRModuleState(STATE_GETINGSOR4);
        }
    }
    if(_moduleIndex == 1){
        if(_MeasuredChannels.OTDRModule.I.ch5 == 0){
            QString cmdline = QString("getsor? %1").arg(0);
            emit this->sigSendCommand(_moduleIndex,cmdline);
            _lastGetSorTime = QDateTime::currentDateTimeUtc();
            setOTDRModuleState(STATE_GETINGSOR1);
        }
        if(_MeasuredChannels.OTDRModule.I.ch6 == 0){
            QString cmdline = QString("getsor? %1").arg(1);
            emit this->sigSendCommand(_moduleIndex,cmdline);
            setOTDRModuleState(STATE_GETINGSOR2);
        }
        if(_MeasuredChannels.OTDRModule.I.ch7 == 0){
            QString cmdline = QString("getsor? %1").arg(2);
            emit this->sigSendCommand(_moduleIndex,cmdline);
            setOTDRModuleState(STATE_GETINGSOR3);
        }
        if(_MeasuredChannels.OTDRModule.I.ch8 == 0){
            QString cmdline = QString("getsor? %1").arg(3);
            emit this->sigSendCommand(_moduleIndex,cmdline);
            setOTDRModuleState(STATE_GETINGSOR4);
        }
    }
 }
}

void QOTDRModule::sendScanCommand()
{
    _lastScanTime = QDateTime::currentDateTimeUtc();
// 如果在获取SOR或WAVELET数据的时候不要发任何东西了。
    QString cmdline = QString("SCAN");
    if(/*(getOTDRModuleState() == STATE_IDLING)||*/(getOTDRModuleState() == STATE_MEASURED)){
        emit    this->sigSendCommand(_moduleIndex,cmdline);
        setOTDRModuleState(STATE_MEASURING);
    }
}

void QOTDRModule::setProgress(qint16 progress)
{
    if(isIdling()){
        emit this->sigSetProgress(_moduleIndex,100);
    }
    else
    {
        emit this->sigSetProgress(_moduleIndex,progress);
    }
}

QByteArray QOTDRModule::generateOTDRTrapData(quint16 module, qint16 channel)
{
    QByteArray  data = QString("Traped on %1").arg(channel).toLatin1();
    QString     filename = QFingerData::getIFMSFingerFileName(channel);
    QFingerData    *oldFingerData = _OldFingers.value(filename);
    QFingerData    *newFingerData = _NewFingers.value(filename);

// TODO: 通过比较oldFingerDate和newFingerData生成trap数据包内容。
    return data;
}
//===============

void QOTDRModule::onSendCommand(quint16 module, QString &cmdline)
{
    QByteArray  data;
// 如果在获取SOR或WAVELET数据的时候不要发任何东西了。
//    if((getOTDRModuleState() != STATE_GETINGSOR ) && (getOTDRModuleState() != STATE_GETINGWAVELET)){
        sendCommandWithResponse(module ,cmdline, &data);
//    }
}


void QOTDRModule::onSetProgress(quint16 module, quint16 progress)
{
    QMutexLocker    locker(&gOTDRModule_mutex);
    _progress = progress;
}

void QOTDRModule::onCatchException(quint16 module, const QString& info)
{

}

void QOTDRModule::onRecvResponse(quint16 module, QString &cmdline, QByteArray &data)
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
//    QString qcmd = qcmdlist.at(0);

    cmdcount = qcmdlist.count();
   if(cmdline.contains("GETSOR?",Qt::CaseInsensitive)){ // 获取SOR文件
        qDebug() << "getsor? command" << endl;
        if(cmdcount == 2){
            QString channel = qcmdlist.at(1);
            qint16 ch = channel.toShort()+1;
            sorfile._channel = _moduleIndex*4+ch;
            filename = QFingerData::getIFMSFingerFileName(sorfile._channel);
//TODO: 从串口获取的sor头四个字节是长度信息，需要摘除之后再处理
            quint32  OSRLen = length - 4;
//            memcpy(&OSRLen, data.mid(1,4).data(), sizeof(OSRLen));

            QByteArray  OSRRawData = data.mid(4);

            QString sorfilename = QFingerData::getIFMSSorFileName(sorfile._channel);
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
                p->toIFMSFingerFile();
            }
            if(ch == 0 ){
                setOTDRModuleState(STATE_GOTSOR1);
            }
            if(ch == 1 ){
                setOTDRModuleState(STATE_GOTSOR2);
            }
            if(ch == 2 ){
                setOTDRModuleState(STATE_GOTSOR3);
            }
            if(ch == 3 ){
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
//    emit this->sigOTDRTrap(module, data);
    emit QPST::getInstance()->sigOTDRTrap(module, data);
}

void QOTDRModule::onSigOTDRSetMode(quint16 mode)
{
    QMutexLocker    locker(&gOTDRModule_mutex);
    _moduleMode = mode;
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
