#ifndef QOTDRMODULE_H
#define QOTDRMODULE_H

#include <QObject>
#include <QSerialPort>
#include <QTcpSocket>
#include <QString>
#include <QMutex>
#include <QFileSystemWatcher>
#include <QMap>
#include <QHash>
#include <QThread>
#include <QRunnable>
#include <QThreadPool>
#include <QDateTime>
#include <QTimer>
#include <QMetaType>
#include <QDebug>

#include    "qfingerdata.h"

#define  DUMP_MESSAGE 1
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

#define  OTDR_WORK_MODE_UNKNOWN	0
#define  OTDR_WORK_MODE_AUTO    1
#define  OTDR_WORK_MODE_STOP    2
#define  OTDR_WORK_MODE_SINGLE  3
#define  OTDR_WORK_MODE_UPDATE  4

#define  OTDR_MEASURE_STATUS_IDLE    			0
#define  OTDR_MEASURE_STATUS_AUTO_RUNNING    	1
#define  OTDR_MEASURE_STATUS_SINGLE_RUNNING		2
#define  OTDR_MEASURE_STATUS_SINGLE_DONE  		3
#define  OTDR_MEASURE_STATUS_FAIL				4

#define  OTDR_TRAP_SOURCE_NORMAL				1
#define  OTDR_TRAP_SOURCE_CONNECTION			2
#define  OTDR_TRAP_SOURCE_LENGTH				3
#define  OTDR_TRAP_SOURCE_RESERVE0				4
#define  OTDR_TRAP_SOURCE_EEMAIN				5
#define  OTDR_TRAP_SOURCE_EEMINOR				6
#define  OTDR_TRAP_SOURCE_RESERVE1				7
#define  OTDR_TRAP_SOURCE_RESERVE2				8
#define  OTDR_TRAP_SOURCE_EDISAPPER				9
#define  OTDR_TRAP_SOURCE_ENEWCRITICAL			10
#define  OTDR_TRAP_SOURCE_ENEWMAIN				11
#define  OTDR_TRAP_SOURCE_ENEWMINOR				12
#define  OTDR_TRAP_SOURCE_RESERVE3				13
#define  OTDR_TRAP_SOURCE_RESERVE4				14
#define  OTDR_TRAP_SOURCE_ECHANGECRITICAL		15
#define  OTDR_TRAP_SOURCE_ECHANGEMAIN			16
#define  OTDR_TRAP_SOURCE_ECHANGEMINOR			17
#define  OTDR_TRAP_SOURCE_RESERVE5				18
#define  OTDR_TRAP_SOURCE_POWER1				19	 	// STA
#define  OTDR_TRAP_SOURCE_POWER2				20
#define  OTDR_TRAP_SOURCE_POWER3				21
#define  OTDR_TRAP_SOURCE_POWER4				22
#define  OTDR_TRAP_SOURCE_POWER5				23
#define  OTDR_TRAP_SOURCE_POWER6				24
#define  OTDR_TRAP_SOURCE_POWER7				25
#define  OTDR_TRAP_SOURCE_POWER8				26
#define  OTDR_TRAP_SOURCE_RESERVE6				27
#define  OTDR_TRAP_SOURCE_RESERVE7				28
#define  OTDR_TRAP_SOURCE_TEMPERATURE			29		// STA
#define  OTDR_TRAP_SOURCE_FAN					30		// FAN
#define  OTDR_TRAP_SOURCE_WSORL					31		// WRONG LENGTH (1~400km) 
#define  OTDR_TRAP_SOURCE_WSOREE				32		// WRONG ENDtoEND(0~80db)
#define  OTDR_TRAP_SOURCE_WSOREVENT				33		// WRONG EVENT (0~10db) 

class QOTDRModule : public QThread
{
    Q_OBJECT
public:
    // 模块的状态
    enum ModuleState
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
        STATE_UPDATE_READY = 21,
        STATE_UPDATE_UPDATING = 22,
        STATE_UPDATE_SUCCESS = 23,             // update status
        STATE_UPDATE_FAILED = 24,
    };

    // OTDR模块的错误类别
    enum ModuleError
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

    quint16 getModuleMode(quint16 module);

    void    initModuleData();
    void    initTcpConnection();
    void    setConnections();
    int     isChannelActive(quint16 channel);
    QString      getIFMSFingerFileName(quint16 channel);
    QString      getIFMSSorFileName(quint16 channel);
	bool  		 storeCurrentSOR(quint16 channel);
    ModuleState getModuleState();
    void setModuleState(ModuleState state);

    bool setSerialPortParam(QString serialPort, QSerialPort::BaudRate baudrate = QSerialPort::Baud115200 \
                                         , QSerialPort::DataBits databits = QSerialPort::Data8 \
                                         , QSerialPort::StopBits stopbits = QSerialPort::OneStop \
                                         , QSerialPort::Parity parity = QSerialPort::NoParity \
                                         , QSerialPort::FlowControl fctrl = QSerialPort::NoFlowControl);

    QStringList generateTrapData(quint16 module, quint16 channel);

    void sendCommandWithResponse(quint16 module, QString cmdline, QByteArray *data);
    void recvResponse(quint16 module, QString &cmdline, QByteArray &data);
	void sendCommand(quint16 module, QString & cmdline);

    void sendStateCommand();
    void sendScanCommand();
    void sendGetSorCommand();

    bool isIdling(){
        return (getModuleState() == STATE_IDLING);
    }

    bool isMeasured(){
        return ((getModuleState() == STATE_MEASURED) ||(getModuleState() == STATE_GOTSOR4));
    }

    bool isMeasuring(){
        return (getModuleState() == STATE_MEASURING);
    }

    bool isGetSOR(){
        return (getModuleState() == STATE_GETINGSOR);
    }

    bool isGettingSOR(){
        return ((getModuleState()>= STATE_GETINGSOR)&&(getModuleState()< STATE_GOTSOR4));
    }

    void setProgress(quint16 channel, quint16 progress);
    void setProgress(quint16 progress);
    quint16  getProgress();
	quint16  getProgress(quint16 channel);
	void increaseMeasuredCount(quint16 channel, quint32 count);
	quint32	getMeasuredCount(quint16 channel);
	void increaseMeasuredSORFiles(quint16 channel, quint32 count);
	quint32	getMeasuredSORFiles(quint16 channel);
    void OTDRChanged(quint16 module, quint16 channel);
    void setModuleMode(quint16 module, quint16 mode);
    void setMeasuringStaus(quint16 channel, quint32 status);
    void updateModule(quint16 module);

    void run();

signals:
    void sigCatchException(quint16 module, const QString& info);
    void sigRecvResponse(quint16 module, QString &cmdline, QByteArray &data);
    void sigSendCommand(quint16 module, QString &cmdline);
    void sigSetProgress(quint16 module, quint16 progress);
	void sigSetMeasuredCount(quint16  channel, quint32 count);
    void sigOTDRTrap(quint16 module, QString &data);
    void sigOTDRSetMode(quint16 module, quint16 mode);
    void sigOTDRSetMeasuringStatus(quint16 channel, quint32 status);
    void sigOTDRUpdateStatus(quint16 module, int stauts);

public slots:
    void onCatchException(quint16 module, const QString& info);
    void onFileChanged(quint16 module, QString filename);
    void onSendCommand(quint16 module, QString &cmdline);
    void onSocketError(QAbstractSocket::SocketError  socketError);
    void onSocketConnected();
    void onSocketDisconnected();
    void onTcpSocketAutoConnect();

private:
    qint8               _moduleIndex;
    QSerialPort         *_pSerialPort;
    QTcpSocket          *_pTcpSocket;
    QIODevice           *_pIODevice;
    ModuleState     	_state;
    TCPConnectionState  _tcpState;
    QDateTime           _lastScanTime;
    QDateTime           _lastGetSorTime;
//    QFileSystemWatcher  _watcher;
//    QStringList         _fileList;
    IFMSChannels_t      _MeasuredChannels;

    QMap<quint16, QFingerData*>  _OldFingers;
    QMap<quint16, QFingerData*>  _NewFingers;
    QMap<quint16, quint16>      _PortActives;
    QMap<quint16, quint32>      _MeasuringStatus;
    QMap<quint16, quint32>      _MeasuredCounts;
    QMap<quint16, quint32>      _MeasuredSORFiles;
    QMap<quint16, quint32>      _MeasuringProgresss;
    QMap<quint16, QString>      _SingleSORs;				//  Single SOR of Manual - IFMS_CHx_SOR_Single.bin
    QMap<quint16, QString>      _SingleFingers; 			//  Single finger of Manual - IFMS_CHx_finger_Single.bin
    QMap<quint16, QString>      _CurrentSORs;			//  Current SOR of Auto - IFMS_CHx_SOR_Current.bin
    QMap<quint16, QString>      _CurrentFingers;			//  Current finger of Auto - IFMS_CHx_finger_Current.bin
    QMap<quint16, QString>      _FirstSORs;				//  First SOR of Auto - IFMS_CHx_SOR_First.bin
    QMap<quint16, QString>      _FirstFingers;			//  First finger of Auto - IFMS_CHx_finger_First.bin
    
    QMap<quint16, QString>      _StoredSORs;				//  Save to Flash - IFMS_CHx_SOR_n.bin

    quint16                     _progress;

    QTimer                      *_timerTCPKeepAlive;
    quint16                     _moduleMode;
// TRAP PARAMS
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
//    double pstIFMS1000MeasureTempHighThreshold;
//    double pstIFMS1000MeasureTempLowThreshold;
    QMap<quint16, bool>     _SORsChanged;
};

#endif // QOTDRMODULE_H
