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

#include <iostream>
#include "qotdrmodule.h"
#include "qagentapp.h"
#include "qsorfilebase.h"

#define  WAIT_WRITE_TIMEOUT     1000
#define  WAIT_READ_TIMEOUT      8000

static QMutex   mutex;


QOTDRModule::QOTDRModule(QObject *parent, qint8 index) : QObject(parent)
{
    _pSerialPort = new QSerialPort(this);
    _state  = STATE_MEASURED;
    _MeasuredChannels.OTDRModule.channels = 0;
    _moduleIndex = index;
    _keeprunning = 1;
}

QOTDRModule::~QOTDRModule()
{
    if(_pSerialPort != NULL){
        delete _pSerialPort;
        _pSerialPort = NULL;
    }
    _state  = STATE_IDLING;
    _keeprunning = 0;
}

void QOTDRModule::setModuleIndex(qint8 index)
{
    _moduleIndex = index;
}

qint8 QOTDRModule::getModuleIndex()
{
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
        _watcher.addPath(QAgentApp::getCacheDir());
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


void QOTDRModule::setConnections()
{
    connect(this, SIGNAL(sigCatchException(const QString&)), this, SLOT(onCatchException(const QString&)),Qt::DirectConnection);
    connect(this, SIGNAL(sigRecvResponse(QString&,QByteArray&)), this, SLOT(onRecvResponse(QString&, QByteArray&)),Qt::DirectConnection);
    connect(this, SIGNAL(sigSendCommand(QString&)), this, SLOT(onSendCommand(QString&)),Qt::DirectConnection);
    connect(this, SIGNAL(sigSetProgress(qint16)), this, SLOT(onSetProgress(qint16)),Qt::DirectConnection);
    connect(this, SIGNAL(sigOTDRChanged(qint16)), this, SLOT(onOTDRChanged(qint16)),Qt::DirectConnection);

//  connect(&_watcher, SIGNAL(fileChanged(const QString)), this, SLOT(onFileChanged(QString)));
    connect(&_watcher, SIGNAL(directoryChanged(const QString)), this, SLOT(onFileChanged(QString)));

    QThreadPool *thread_pool = QThreadPool::globalInstance();
    QOTDRModule::Sender *thread = new QOTDRModule::Sender(this);
    thread_pool->start(thread);
}

QOTDRModule::OTDRModuleState QOTDRModule::getOTDRModuleState()
{
    QMutexLocker locker(&mutex);
    return _state;
}

void QOTDRModule::setOTDRModuleState(OTDRModuleState state)
{
    QMutexLocker locker(&mutex);
    _state = state;
}

bool QOTDRModule::setSerialPortParam(QString serialPort, QSerialPort::BaudRate baudrate, QSerialPort::DataBits databits \
                                     ,QSerialPort::StopBits stopbits, QSerialPort::Parity parity, QSerialPort::FlowControl fctrl)
{
    bool ret = false;
    _pSerialPort->setPortName(serialPort);
    _pSerialPort->setBaudRate(baudrate);
    _pSerialPort->setDataBits(databits);
    _pSerialPort->setStopBits(stopbits);
    _pSerialPort->setFlowControl(fctrl);

    ret = _pSerialPort->open(QIODevice::ReadWrite);
    if(ret!= true){
        QAgentApp::error(QString("Failed to open port %1, error: %2").arg(serialPort).arg(_pSerialPort->error()));
    }
    return ret;
}

void QOTDRModule::sendCommandWithResponse(QString cmdline, QByteArray *data)
{
    printf("[0x%x] QOTDRModule", QThread::currentThreadId());
    QMutexLocker locker(&_mutex);
    QAgentApp::message(cmdline, QString(QChar(_moduleIndex)));

    _pSerialPort->write(cmdline.toLatin1());
    if(_pSerialPort->waitForBytesWritten(WAIT_WRITE_TIMEOUT))
    {
        if(_pSerialPort->waitForReadyRead(WAIT_READ_TIMEOUT)){
            QByteArray response = _pSerialPort->readAll();
            while(_pSerialPort->waitForReadyRead(50)){
                response += _pSerialPort->readAll();
            }
            *data = response;
            emit sigRecvResponse(cmdline, response);
        }
         else
        {
            emit sigCatchException("waitForReadyRead timeout");
            QAgentApp::warning(QString("waitForReadyRead timeout"));
            return;
        }
    }
    else
    {
        emit sigCatchException("waitForBytesWritten timeout");
        QAgentApp::warning(QString("waitForBytesWritten timeout"));
        return;
    }
}

void QOTDRModule::sendStateCommand()
{
// 如果在获取SOR或WAVELET数据的时候不要发任何东西了。
    QString cmdline = QString("STATE?\r\n");
    if(getOTDRModuleState() < STATE_GETINGSOR ){
        emit    this->sigSendCommand(cmdline);
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
if(getOTDRModuleState() == STATE_IDLING ){
    if(_moduleIndex == 0){
        if(_MeasuredChannels.OTDRModule.I.ch1 == 0){
            QString cmdline = QString("getsor? %1\r\n").arg(0);
            emit this->sigSendCommand(cmdline);
            setOTDRModuleState(STATE_GETINGSOR1);
        }
        if(_MeasuredChannels.OTDRModule.I.ch2 == 0){
            QString cmdline = QString("getsor? %1\r\n").arg(1);
            emit this->sigSendCommand(cmdline);
            setOTDRModuleState(STATE_GETINGSOR2);
        }
        if(_MeasuredChannels.OTDRModule.I.ch3 == 0){
            QString cmdline = QString("getsor? %1\r\n").arg(2);
            emit this->sigSendCommand(cmdline);
            setOTDRModuleState(STATE_GETINGSOR3);
        }
        if(_MeasuredChannels.OTDRModule.I.ch4 == 0){
            QString cmdline = QString("getsor? %1\r\n").arg(3);
            emit this->sigSendCommand(cmdline);
            setOTDRModuleState(STATE_GETINGSOR4);
        }
    }
    if(_moduleIndex == 1){
        if(_MeasuredChannels.OTDRModule.I.ch5 == 0){
            QString cmdline = QString("getsor? %1\r\n").arg(0);
            emit this->sigSendCommand(cmdline);
            setOTDRModuleState(STATE_GETINGSOR1);
        }
        if(_MeasuredChannels.OTDRModule.I.ch6 == 0){
            QString cmdline = QString("getsor? %1\r\n").arg(1);
            emit this->sigSendCommand(cmdline);
            setOTDRModuleState(STATE_GETINGSOR2);
        }
        if(_MeasuredChannels.OTDRModule.I.ch7 == 0){
            QString cmdline = QString("getsor? %1\r\n").arg(2);
            emit this->sigSendCommand(cmdline);
            setOTDRModuleState(STATE_GETINGSOR3);
        }
        if(_MeasuredChannels.OTDRModule.I.ch8 == 0){
            QString cmdline = QString("getsor? %1\r\n").arg(3);
            emit this->sigSendCommand(cmdline);
            setOTDRModuleState(STATE_GETINGSOR4);
        }
    }
 }
}

void QOTDRModule::sendScanCommand()
{
// 如果在获取SOR或WAVELET数据的时候不要发任何东西了。
    QString cmdline = QString("SCAN\r\n");
    if(/*(getOTDRModuleState() == STATE_IDLING)||*/(getOTDRModuleState() == STATE_MEASURED)){
        emit    this->sigSendCommand(cmdline);
        setOTDRModuleState(STATE_MEASURING);
    }
}

void QOTDRModule::setProgress(qint16 progress)
{
    if(isIdling()){
        emit this->sigSetProgress(100);
    }
    else
    {
        emit this->sigSetProgress(progress);
    }
}

QByteArray QOTDRModule::generateOTDRTrapData(qint16 channel)
{
    QByteArray  data = QString("Traped on %1").arg(channel).toLatin1();
    QString     filename = QFingerData::getIFMSFingerFileName(channel);
    QFingerData    *oldFingerData = _OldFingers.value(filename);
    QFingerData    *newFingerData = _NewFingers.value(filename);

// TODO: 通过比较oldFingerDate和newFingerData生成trap数据包内容。
    return data;
}
//===============

void QOTDRModule::onSendCommand(QString &cmdline)
{
    QByteArray  data;
// 如果在获取SOR或WAVELET数据的时候不要发任何东西了。
    if((getOTDRModuleState() != STATE_GETINGSOR ) && (getOTDRModuleState() != STATE_GETINGWAVELET)){
        sendCommandWithResponse(cmdline, &data);
    }
}


void QOTDRModule::onSetProgress(qint16 progress)
{

}

void QOTDRModule::onCatchException(const QString& info)
{

}

void QOTDRModule::onRecvResponse(QString &cmdline, QByteArray &data)
{
// TODO: 获取到sorfile之后转变成fingerdata[channel]
    QSorFileBase    sorfile;
    QString         filename;

    QString         responseString = QString(data);
    if((responseString.contains("STATE"))&&(data.size() >=7)&&(data.at(6) == '0')){
        setOTDRModuleState(STATE_IDLING);
    }
    if((responseString.contains("STATE"))&&(data.size() >=7)&&(data.at(6) == '1'))
    {
        setOTDRModuleState(STATE_MEASURING);
    }

    QStringList     qcmdlist = cmdline.split(" ", QString::SkipEmptyParts);

    int cmdcount = qcmdlist.size();
    if(qcmdlist.contains(QString("getsor?"))){ // 获取SOR文件
        if(cmdcount == 2){
            QString channel = qcmdlist.at(1);
            qint16 ch = channel.toShort();
            sorfile._channel = _moduleIndex*4+ch;
            filename = QFingerData::getIFMSFingerFileName(sorfile._channel);
//TODO: 从串口获取的sor头四个字节是长度信息，需要摘除之后再处理
            int  OSRLen = 0;
            memcpy(&OSRLen, data.left(4).data(), sizeof(OSRLen));

            QByteArray  OSRRawData = data.mid(4);

            if(sorfile.parseData(OSRRawData.data(), OSRLen) == true){
                _OldFingers.swap(_NewFingers);
                QFingerData *p = sorfile.toFingerData();
                _NewFingers.insert(filename,p);
                emit this->sigOTDRChanged(sorfile._channel);
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

void QOTDRModule::onFileChanged(QString filename)
{

}

void QOTDRModule::onOTDRChanged(qint16 channel)
{
    QAgentApp::message(QString("OTDR channel %1 changed!").arg(channel));

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

    QByteArray  data = generateOTDRTrapData(channel);
    emit this->sigOTDRTrap(data);
}
