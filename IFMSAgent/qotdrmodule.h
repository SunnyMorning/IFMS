#ifndef QOTDRMODULE_H
#define QOTDRMODULE_H

#include <QObject>
#include <QSerialPort>
#include <QTcpSocket>
#include <QString>
#include <QMutex>
#include <QFileSystemWatcher>
#include <QMap>
#include <QThread>
#include <QRunnable>
#include <QThreadPool>
#include <QDateTime>
#include <QTimer>
#include <QMetaType>
#include <QDebug>

#include    "qfingerdata.h"

#define  WAIT_WRITE_TIMEOUT     1000
#define  WAIT_READ_TIMEOUT      4000

#define  UART_OF_MODULE1        "/dev/ttyO2"
#define  UART_OF_MODULE2        "/dev/ttyO3"

#define  ADDRESS_OF_MODULE1     "172.16.1.101"
#define  ADDRESS_OF_MODULE2     "172.16.1.102"

#define  PORT_OF_MODULE1        6000
#define  PORT_OF_MODULE2        6000

#define  TCP_CONNECT_TIMEOUT	10000
#define  KEEP_ALIVE_TIMEOUT     30000

#define  OTDR_WORK_MODE_AUTO    0
#define  OTDR_WORK_MODE_SINGLE  1
#define  OTDR_WORK_MODE_STOP    2

class QOTDRModule : public QThread
{
    Q_OBJECT
public:
    // 模块的状态
    enum OTDRModuleState
    {
        STATE_IDLING = 0,                   // 空闲状态
        STATE_MEASURING = 1,                // 测量状态
        STATE_MEASURED  = 2,                //
        STATE_GETINGSOR = 3,                // 正在获取SOR文件
        STATE_GETINGSOR1 = 4,                // 正在获取SOR文件
        STATE_GETINGSOR2 = 5,                // 正在获取SOR文件
        STATE_GETINGSOR3 = 6,                // 正在获取SOR文件
        STATE_GETINGSOR4 = 7,                // 正在获取SOR文件
        STATE_GOTSOR1 = 8,                // 正在获取SOR文件
        STATE_GOTSOR2 = 9,                // 正在获取SOR文件
        STATE_GOTSOR3 = 10,                // 正在获取SOR文件
        STATE_GOTSOR4 = 11,                // 正在获取SOR文件
        STATE_GETINGWAVELET = 12,            // 正在获取wavelet文件
        STATE_GETINGWAVELET1 = 13,            // 正在获取wavelet文件
        STATE_GETINGWAVELET2 = 14,            // 正在获取wavelet文件
        STATE_GETINGWAVELET3 = 15,            // 正在获取wavelet文件
        STATE_GETINGWAVELET4 = 16,            // 正在获取wavelet文件
        STATE_GOTWAVELET1 = 17,            // 正在获取wavelet文件
        STATE_GOTGWAVELET2 = 18,            // 正在获取wavelet文件
        STATE_GOTWAVELET3 = 19,            // 正在获取wavelet文件
        STATE_GOTWAVELET4 = 20,            // 正在获取wavelet文件
        STATE_DOWNLOADING = 21               // 下载状态
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

    enum TCPConnectionState
    {
        STATE_TCP_INIT = 0,             // 初始状态
        STATE_TCP_CONNECTING,           // 正在进行TCP连接
        STATE_TCP_CONNECTED,            // TCP连接成功
        STATE_TCP_DISCONNECTING,        // 正在断开TCP连接
        STATE_TCP_DISCONNECTED,         // TCP连接断开
        STATE_TCP_CONNECT_ERROR,        // TCP连接错误
    };

    explicit QOTDRModule(QObject *parent = nullptr, qint8 index = 0);

    ~QOTDRModule();
    int     _keeprunning;
    void    setKeepRunning(int running);
    int     getKeepRunning();
    void    setModuleIndex(qint8 index);
    qint8   getModuleIndex();
    void    initFingerBinFile(QString filename);
    void    initModuleFingerData();
    void    initTcpConnection();
    void    setConnections();

    OTDRModuleState getOTDRModuleState();
    void setOTDRModuleState(OTDRModuleState state);

    bool setSerialPortParam(QString serialPort, QSerialPort::BaudRate baudrate = QSerialPort::Baud115200 \
                                         , QSerialPort::DataBits databits = QSerialPort::Data8 \
                                         , QSerialPort::StopBits stopbits = QSerialPort::OneStop \
                                         , QSerialPort::Parity parity = QSerialPort::NoParity \
                                         , QSerialPort::FlowControl fctrl = QSerialPort::NoFlowControl);

    QByteArray generateOTDRTrapData(quint16 module, qint16 channel);

    void sendCommandWithResponse(quint16 module, QString cmdline, QByteArray *data);
    void recvResponse(quint16 module, QString &cmdline, QByteArray &data);
	void sendCommand(quint16 module, QString & cmdline);

    void sendStateCommand();
    void sendScanCommand();
    void sendGetSorCommand();

    bool isIdling(){
        return (getOTDRModuleState() == STATE_IDLING);
    }

    bool isMeasured(){
        return ((getOTDRModuleState() == STATE_MEASURED) ||(getOTDRModuleState() == STATE_GOTSOR4));
    }

    bool isMeasuring(){
        return (getOTDRModuleState() == STATE_MEASURING);
    }

    bool isGetSOR(){
        return (getOTDRModuleState() == STATE_GETINGSOR);
    }

    bool isGettingSOR(){
        return ((getOTDRModuleState()>= STATE_GETINGSOR)&&(getOTDRModuleState()< STATE_GOTSOR4));
    }

    void setProgress(qint16 progress);
    qint16  getProgress(){return _progress;}

    void run();

signals:
    void sigCatchException(quint16 module, const QString& info);
    void sigRecvResponse(quint16 module, QString &cmdline, QByteArray &data);
    void sigSendCommand(quint16 module, QString &cmdline);
    void sigSetProgress(quint16 module, quint16 progress);
    void sigOTDRChanged(quint16 module, quint16 channel);
    void sigOTDRTrap(quint16 module, QByteArray &data);
    void sigOTDRSetMode(quint16 mode);

public slots:
    void onCatchException(quint16 module, const QString& info);
    void onFileChanged(quint16 module, QString filename);
    void onSendCommand(quint16 module, QString &cmdline);
    void onSetProgress(quint16 module, quint16 progress);
    void onOTDRChanged(quint16 module, quint16 channel);
    void onSigOTDRSetMode(quint16 mode);

    void onSocketError(QAbstractSocket::SocketError  socketError);
    void onSocketConnected();
    void onSocketDisconnected();
    void onTcpSocketAutoConnect();

private:
    qint8               _moduleIndex;
    QSerialPort         *_pSerialPort;
    QTcpSocket          *_pTcpSocket;
    QIODevice           *_pIODevice;
    OTDRModuleState     _state;
    TCPConnectionState  _tcpState;
    QDateTime           _lastScanTime;
    QDateTime           _lastGetSorTime;
    QFileSystemWatcher  _watcher;
    QStringList         _fileList;
    IFMSChannels_t      _MeasuredChannels;
    quint16             _progress;
    QMap<QString, QFingerData*>  _OldFingers;
    QMap<QString, QFingerData*>  _NewFingers;

    QTimer              *_timerTCPKeepAlive;

    quint32             _measureCount;
    quint16             _moduleMode;
};

#endif // QOTDRMODULE_H
