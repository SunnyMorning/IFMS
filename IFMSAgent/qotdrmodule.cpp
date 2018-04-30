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
#define  WAIT_READ_TIMEOUT      5000


QOTDRModule::QOTDRModule(QObject *parent, qint8 index) : QObject(parent)
{
    _pSerialPort = new QSerialPort(this);
    _state  = STATE_IDLING;
    _moduleIndex = index;
    _keeprunning = 1;
}

QOTDRModule::~QOTDRModule()
{
    if(_pSerialPort != NULL){
        delete _pSerialPort;
        _pSerialPort = NULL;
    }

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
    connect(this, SIGNAL(sigCatchException(const QString&)), this, SLOT(onCatchException(const QString&)));
    connect(this, SIGNAL(sigRecvResponse(QString&,QByteArray&)), this, SLOT(onRecvResponse(QString&, QByteArray&)));
    connect(this, SIGNAL(sigSendCommand(QString&)), this, SLOT(onSendCommand(QString&)));
    connect(this, SIGNAL(sigSetProgress(qint16)), this, SLOT(onSetProgress(qint16)));
    connect(this, SIGNAL(sigOTDRChanged(qint16)), this, SLOT(onOTDRChanged(qint16)));

//  connect(&_watcher, SIGNAL(fileChanged(const QString)), this, SLOT(onFileChanged(QString)));
    connect(&_watcher, SIGNAL(directoryChanged(const QString)), this, SLOT(onFileChanged(QString)));

    QThreadPool *thread_pool = QThreadPool::globalInstance();
    QOTDRModule::Sender *thread = new QOTDRModule::Sender(this);
    thread_pool->start(thread);
}

QOTDRModule::OTDRModuleState QOTDRModule::getOTDRModuleState()
{
    return _state;
}

void QOTDRModule::setOTDRModuleState(OTDRModuleState state)
{
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
    QMutexLocker locker(&_mutex);
    QAgentApp::message(cmdline, QString(QChar(_moduleIndex)));
    if(cmdline.startsWith(QString("getsor")), Qt::CaseInsensitive)
    {
        _state = STATE_GETINGSOR;
    }
    if(cmdline.startsWith((QString("waveform")),Qt::CaseInsensitive)){
        _state = STATE_GETINGWAVELET;
    }
    if(cmdline.startsWith((QString("scan")),Qt::CaseInsensitive)){
        _state = STATE_MEASURING;
    }
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
//            QAgentApp::warning(QString("waitForReadyRead timeout"));
            return;
        }
    }
    else
    {
        emit sigCatchException("waitForBytesWritten timeout");
//        QAgentApp::warning(QString("waitForBytesWritten timeout"));
        return;
    }
}

void QOTDRModule::sendStateCommand()
{
// 如果在获取SOR或WAVELET数据的时候不要发任何东西了。
    QString cmdline = QString("STATE?");
    if((_state != STATE_GETINGSOR ) && (_state != STATE_GETINGWAVELET)){
        emit    this->onSendCommand(cmdline);
    }
}


void QOTDRModule::sendScanCommand()
{
// 如果在获取SOR或WAVELET数据的时候不要发任何东西了。
    QString cmdline = QString("SCAN");
    if(_state == STATE_IDLING){
        emit    this->onSendCommand(cmdline);
        _state = STATE_MEASURING;
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
    if((_state != STATE_GETINGSOR ) && (_state != STATE_GETINGWAVELET)){
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
    if(QString::compare(responseString, QString("STATE 0")), Qt::CaseInsensitive){
        _state = STATE_IDLING;
    }
    else
    {
        _state = STATE_MEASURING;
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
            if(sorfile.parseData(data.data(), data.length()) == true){
                _OldFingers.swap(_NewFingers);
                QFingerData *p = sorfile.toFingerData();
                _NewFingers.insert(filename,p);
                emit this->sigOTDRChanged(sorfile._channel);
                p->toIFMSFingerFile();
            }
            _state  =  STATE_MEASURING;
         }
    }

}

void QOTDRModule::onFileChanged(QString filename)
{

}

void QOTDRModule::onOTDRChanged(qint16 channel)
{
    QAgentApp::message(QString("OTDR channel %1 changed!").arg(channel));
    QByteArray  data = generateOTDRTrapData(channel);
    emit this->sigOTDRTrap(data);
}
