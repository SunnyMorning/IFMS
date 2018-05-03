#ifndef QOTDRMODULE_H
#define QOTDRMODULE_H

#include <QObject>
#include <QSerialPort>
#include <QString>
#include <QMutex>
#include <QFileSystemWatcher>
#include <QMap>
#include <QThread>
#include <QRunnable>
#include <QThreadPool>
#include <QDebug>

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

    explicit QOTDRModule(QObject *parent = nullptr, qint8 index = 0);

    ~QOTDRModule();
    int     _keeprunning;
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

    QByteArray generateOTDRTrapData(qint16 channel);

    void sendCommandWithResponse(QString cmdline, QByteArray *data);

    void sendStateCommand();
    void sendScanCommand();
    void sendGetSorCommand();

    bool isIdling(){
        return (getOTDRModuleState() == STATE_IDLING);
    }

    bool isMeasured(){
        return (getOTDRModuleState() == STATE_MEASURED);
    }

    bool isMeasuring(){
        return (getOTDRModuleState() == STATE_MEASURING);
    }

    bool isGettingSOR(){
        return ((getOTDRModuleState()>= STATE_GETINGSOR)&&(getOTDRModuleState()< STATE_GOTSOR4));
    }

    void setProgress(qint16 progress);

    class Sender: public QRunnable{
    public:
        Sender(QOTDRModule  *client){
            _client = client;
            _progress = 0;
        }
        ~Sender(){
        }

        void run(){
            _client->sendScanCommand();

            do{
                QThread::msleep(1500);
                qDebug() << "state:" <<_client->getModuleIndex() << ":" << _client->getOTDRModuleState() << endl;

                if(_client->isIdling()){
                    _client->setProgress(90);
                    _client->sendGetSorCommand();
                    QThread::msleep(1000);
                }
                else if(_client->isMeasured())
                {
                    _client->setProgress(100);
                    _client->sendScanCommand();
                }
                else if(_client->isMeasuring())
                {
                    _progress += 10;
                    if(_progress >= 80){
                        _progress = 80;
                    }
                    _client->setProgress(_progress);
                    _client->sendStateCommand();
                }
                else if(_client->isGettingSOR())
                {
                    _progress = 90;
                    _client->setProgress(_progress);
                }

            }while(_client->_keeprunning == 1);

        }
    private:
        QOTDRModule *_client;
        qint16       _progress;
    };

signals:
    void sigCatchException(const QString& info);
    void sigRecvResponse(QString &cmdline, QByteArray &data);
    void sigSendCommand(QString &cmdline);
    void sigSetProgress(qint16 progress);
    void sigOTDRChanged(qint16 channel);
    void sigOTDRTrap(QByteArray &data);

public slots:
    void onCatchException(const QString& info);
    void onRecvResponse(QString &cmdline, QByteArray &data);
    void onFileChanged(QString filename);
    void onSendCommand(QString &cmdline);
    void onSetProgress(qint16 progress);
    void onOTDRChanged(qint16 channel);

private:
    qint8               _moduleIndex;
    QSerialPort         *_pSerialPort;
    OTDRModuleState     _state;
    QMutex              _mutex;
    QFileSystemWatcher  _watcher;
    QStringList         _fileList;
    IFMSChannels_t      _MeasuredChannels;

    QMap<QString, QFingerData*>  _OldFingers;
    QMap<QString, QFingerData*>  _NewFingers;
};

#endif // QOTDRMODULE_H
