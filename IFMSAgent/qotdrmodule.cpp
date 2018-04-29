#include <QSerialPort>
#include <QDebug>
#include <QMutexLocker>
#include <QMutex>

#include "qotdrmodule.h"

#define  WAIT_WRITE_TIMEOUT     1000
#define  WAIT_READ_TIMEOUT      5000


QOTDRModule::QOTDRModule(QObject *parent) : QObject(parent)
{
    _pSerialPort = new QSerialPort(this);
    _state  = STATE_IDLING;
}

QOTDRModule::~QOTDRModule()
{
    if(_pSerialPort != NULL){
        delete _pSerialPort;
        _pSerialPort = NULL;
    }
}

void QOTDRModule::setConnections()
{
    connect(this, SIGNAL(sigCatchException(const QString&)), this, SLOT(onCatchException(const QString&)));
    connect(this, SIGNAL(sigRecvResponse(QString&,QByteArray&)), this, SLOT(onRecvResponse(QString&, QByteArray&)));
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
        qDebug() << QObject::tr("Failed to open port %1, error: %2")
                                  .arg(serialPort).arg(_pSerialPort->error()) << endl;
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
            qDebug() << "waitForReadyRead timeout";
            return;
        }
    }
    else
    {
        emit sigCatchException("waitForBytesWritten timeout");
        qDebug() << "waitForBytesWritten timeout";
        return;
    }
}

void QOTDRModule::onCatchException(const QString& info)
{

}

void QOTDRModule::onRecvResponse(QString& cmdline, QByteArray& data)
{

}
