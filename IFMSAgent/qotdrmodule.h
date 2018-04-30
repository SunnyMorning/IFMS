#ifndef QOTDRMODULE_H
#define QOTDRMODULE_H

#include <QObject>
#include <QSerialPort>
#include <QString>
#include <QMutex>
#include <QFileSystemWatcher>
#include <QMap>

#include    "qfingerdata.h"

class QOTDRModule : public QObject
{
    Q_OBJECT
public:
    // 模块的状态
    enum OTDRModuleState
    {
        STATE_IDLING = 0,                   // 空闲状态
        STATE_MEASURING = 1,                // 测量状态
        STATE_GETINGSOR = 2,                // 正在获取SOR文件
        STATE_GETINGWAVELET = 3,            // 正在获取wavelet文件
        STATE_DOWNLOADING = 4               // 下载状态
    };

    // OTDR模块的错误类别
    enum OTDRError
    {
        ERR0    = 0,                        // Normal Response
        ERR20   = 20,                       // command or query in format is illegal
        ERR21   = 21,                       // Illegal parameter value
        ERR22   = 22,                       // Illegal command or query
        ERR40   = 40,                       // Received command or query are OK, but no action
        ERR41   = 41,                       // Received command or query during the process of software update
        ERR42   = 42,                       // Received command“TRANSF”for updating software during the OTDR mode
        ERR43   = 43                        // Received command“UPDATE” while the download file has not been accepted
    };

    explicit QOTDRModule(QObject *parent = nullptr, qint8 index = 0);

    ~QOTDRModule();

    void    setModuleIndex(qint8 index);
    qint8   getModuleIndex();
    void    initFingerBinFile(QString filename);
    void    initModuleFingerData();
    void    setConnections();

    OTDRModuleState getOTDRModuleState();
    void setOTDRModuleState(OTDRModuleState state);

    bool setSerialPortParam(QString serialPort, QSerialPort::BaudRate baudrate = QSerialPort::Baud115200 \
                                         , QSerialPort::DataBits databits = QSerialPort::Data8 \
                                         , QSerialPort::StopBits stopbits = QSerialPort::OneStop \
                                         , QSerialPort::Parity parity = QSerialPort::NoParity \
                                         , QSerialPort::FlowControl fctrl = QSerialPort::NoFlowControl);


    void sendCommandWithResponse(QString cmdline, QByteArray *data);

signals:
    void sigCatchException(const QString& info);
    void sigRecvResponse(QString &cmdline, QByteArray &data);

public slots:
    void onCatchException(const QString& info);
    void onRecvResponse(QString &cmdline, QByteArray &data);
    void onFileChanged(QString filename);

public:

private:
    qint8               _moduleIndex;
    QSerialPort         *_pSerialPort;
    OTDRModuleState     _state;
    QMutex              _mutex;
    QFileSystemWatcher          _watcher;
    QStringList         _fileList;

    QMap<QString, QFingerData*>  _OldFingers;
    QMap<QString, QFingerData*>  _NewFingers;
};

#endif // QOTDRMODULE_H
