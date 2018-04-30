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
}

QOTDRModule::~QOTDRModule()
{
    if(_pSerialPort != NULL){
        delete _pSerialPort;
        _pSerialPort = NULL;
    }
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
//    connect(&_watcher, SIGNAL(fileChanged(const QString)), this, SLOT(onFileChanged(QString)));
    connect(&_watcher, SIGNAL(directoryChanged(const QString)), this, SLOT(onFileChanged(QString)));
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

void QOTDRModule::onCatchException(const QString& info)
{

}

void QOTDRModule::onRecvResponse(QString &cmdline, QByteArray &data)
{
// TODO: 获取到sorfile之后转变成fingerdata[channel]
    QSorFileBase    sorfile;
    QString         filename;
    QStringList     qcmdlist = cmdline.split(" ", QString::SkipEmptyParts);

    int cmdcount = qcmdlist.size();
    if(qcmdlist.contains(QString("getsor?"))){
        if(cmdcount == 2){
            QString channel = qcmdlist.at(1);
            qint16 ch = channel.toShort();
            sorfile._channel = _moduleIndex*4+ch;
            filename = QFingerData::getIFMSFingerFileName(sorfile._channel);

        }
    }

    if(sorfile.parseData(data.data(), data.length()) == true){
        sorfile.toFingerData()->toIFMSFingerFile();
    }
}

void QOTDRModule::onFileChanged(QString filename)
{

}
