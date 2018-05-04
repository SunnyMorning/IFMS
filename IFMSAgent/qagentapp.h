#ifndef QAGENTAPP_H
#define QAGENTAPP_H

#include <QObject>
#include <QCoreApplication>
#include <QString>
#include <QStringList>

#include <map>
#include <vector>
#include <string>

#include "qotdrmodule.h"
#include "qcommander.h"
#include "qpst.h"

using namespace std;

class QAgentApp : public QCoreApplication
{
    Q_OBJECT
public:
    explicit QAgentApp(int &argc, char **argv);
    virtual ~QAgentApp();

    void showStatusMessage(const QString &msg, int ModuleIndex, int time);
    void showStatusMessage(const QStringList &msgList, int ModuleIndex, int time);
    void showProperties(const QStringList &files);

		struct  pstSystemBasicManagement
		{
				string	devName;
				string	devIpAddr;
				string	devGateway;
				string  devNetMask;
				long	saveCurrentConfiguration;
				long	reset2Factory;
				long	reboot;
		}m_pstSystemBasicManagement;
		
		struct  pstSystemVerInfo
		{
				string pstHwVer;
				string pstSwVer;
				string pstFwVer;
				string pstModel;
				string pstSn;
				string devMacAddress;
		}m_pstSystemVerInfo;  

    struct  pstSystemTrapInfo
    {

        qint8 pstSystemTrapFuncEn;
        qint8 pstSystemTrapCount;
        qint32  getsize();
        struct pstSystemTrapTargetEntry{
            string  pstSystemTrapTargetName;
            string  pstSystemTrapTargetIpAddr;
            string  pstSystemTrapTargetCommunity;
            long  pstSystemTrapTargetTrapVersion;
            long  pstSystemTrapTargetRowStatus;
        };

        vector<pstSystemTrapTargetEntry>   pstSystemTrapTargetTable;
    }m_pstSystemTrapInfo;
    
    struct  pstSystemStatus
    {
    		long pstSystemFanTotalNum;
    		long pstSystemPowerTotalNum;
    		
        struct pstSystemFanEntry{
            long  pstSystemFanIndex;
            long  pstSystemFanStatus;
            long  pstSystemFanSpeed;
        };
        struct pstSystemPowerEntry{
            long  pstSystemPowerIndex;
            long  pstSystemPowerStatus;
            string pstSystemPowerVoltage;
            string pstSystemPowerCurrent;
        };    		
    		vector<pstSystemFanEntry>	pstSystemFanTable;
    		vector<pstSystemPowerEntry> pstSystemPowerTable;
    		
    		string pstSystemTemperature;
    }m_pstSystemStatus;
    
    struct pstSystemOnlineUpgrade
    {
    		string pstSystemFtpSrvIp;
    		string pstSystemFtpUserName;
    		string pstSystemFtpUserPwd;
    		string pstSystemFtpFileName;
    		long	 pstSystemUpgFileType;
    		long	 pstSystemUpgDstSlot;
    		long	 pstSystemUpgAction;
    		long	 pstSystemUpgStatus;
    		string pstSystemUpgResultInfo;   
    }m_pstSystemOnlineUpgrade;
    
    struct pstSystemProductInfo
    {
    		long pstSystemProductType;
    }m_pstSystemProductInfo;

		struct pstIFMS1000PortInfoEntry
			{
				long pstIFMS1000PortNum;
				string pstIFMS1000PortRxPwr;
				string pstIFMS1000PortTxPwr;
				long pstIFMS1000PortWorkMode;
				long pstIFMS1000PortActive;
				long pstIFMS1000PortFiberAppType;
				long pstIFMS1000PortRunningStatus;
			};
		struct pstIFMS1000MeasureEntry
			{
				long pstIFMS1000MTPortNum;
				string pstIFMS1000MeasureStartPosition;
				string pstIFMS1000MeasureEndPosition;
				string pstIFMS1000MeasureRefIndex;
				string pstIFMS1000MeasureResolution;
				long pstIFMS1000MeasureStatus;
				long pstIFMS1000MeasureAction;
				string pstIFMS1000MeasureResultFile;
				string pstIFMS1000MeasureResultRawDataFile;
				long pstIFMS1000MeasureProgressStatus;
				string pstIFMS1000MeasureResultRawPointFile;
			};
		struct pstIFMS1000FingerEntry
			{
				long pstIFMS1000FTPortNum;
				string pstIFMS1000FingerStartPosition;
				string pstIFMS1000FingerEndPosition;
				string pstIFMS1000FingerRefIndex;
				string pstIFMS1000FingerResolution;
				string pstIFMS1000FingerCreateTime;
				long pstIFMS1000FingerFileStatus;
				long pstIFMS1000FingerAction;
				long pstIFMS1000FingerActionStatus;
				string pstIFMS1000FingerSavedFileName;
				string pstIFMS1000FingerCurrentFileName;
			};
		struct pstIFMS1000DiffTotalEntry
			{
				long pstIFMS1000DtPortNum;
				long pstIFMS1000DtTotalNum;
			};
		struct pstIFMS1000DiffInfoEntry
			{
				long pstIFMS1000DiffInfoPortNum;
				long pstIFMS1000DiffInfoPortItemIndex;
				string pstIFMS1000DiffInfoDistance;
				string pstIFMS1000DiffInfoNVal;
				string pstIFMS1000DiffInfodBVal;
				long pstIFMS1000DiffInfoDiffType;
				unsigned long pstIFMS1000DiffInfoPointId;
			};

		struct pstIFMS1000PortLedEntry
			{
				long pstIFMS1000PortLedPortNum;
				long pstIFMS1000PortLedStatus;
				
			};

		vector<pstIFMS1000PortInfoEntry> m_pstIFMS1000PortInfoTable;
		vector<pstIFMS1000MeasureEntry> m_pstIFMS1000MeasureTable;
		vector<pstIFMS1000FingerEntry> pstIFMS1000FingerTable;
		struct pstIFMS1000DiffInfo
			{
				vector<pstIFMS1000DiffTotalEntry> pstIFMS1000DiffTotalTable;
				vector<pstIFMS1000DiffInfoEntry> pstIFMS1000DiffInfoTable;
			}m_pstIFMS1000DiffInfo;

	struct pstIFMS1000LedStatus
		{
        struct _pstIFMS1000SystemLed
			{
				long pstIFMS1000SysLedPW1;
				long pstIFMS1000SysLedPW2;
				long pstIFMS1000SysLedStatus;
            }pstIFMS1000SystemLed;
	
			vector<pstIFMS1000PortLedEntry> pstIFMS1000PortLedTable;
		}m_pstIFMS1000LedStatus;

    static QString getAppName();
    static QString getConfigDir();
    static QString getCacheDir();
    static QString getDataDir();
    static QString getConfigFile();

    static void message(quint16 module, const QString &text, const QString &title = QString(), QObject *parent = NULL);
    static void warning(quint16 module, const QString &text, const QString &title = QString(), QObject *parent = NULL);
    static void error(quint16 module, const QString &text, const QString &title = QString(), QObject *parent = NULL);

    static bool confirm(quint16 module, const QString &text, const QString &title = QString(), QObject *parent = NULL);
    static void message(quint16 module, const QString &text, QObject *parent);
    static void warning(quint16 module, const QString &text, QObject *parent);
    static bool confirm(quint16 module, const QString &text, QObject *parent);

    static void msg(quint16 module, const QString &title, const QString &text);
    static bool ask(quint16 module, const QString &title, const QString &text);

    QAgentApp         *app() { return m_app; }
    bool   startSession(int &argc, char **argv);
    void   stopSession();

protected:
    void    initAppData();
    void    initFingerBin(QString filename, qint16 ch);

signals:
    void settingsChanged();
    void statusMessage(const QString &msg, int ModuleIndex, int time);
    void statusMessage(const QStringList &msgList, int ModuleIndex, int time);
    void sigSendCommandToModule(quint16 module, QString& cmdline);
    // for debug only
    void sigModuleRecvResponse(quint16 module ,QString& cmdline, QByteArray& data);
    void sigModuleStartMonitor(quint16 module);
    void sigModuleStopMonitor(quint16 module);
public slots:
    void onSigExit(qint32 num);
    void onSwitchModule(quint16 module);
    void onSigSendCommandToModule(quint16 module, QString& cmdline);

// for debug only
    void onSigModuleRecvResponse(quint16 module, QString& cmdline, QByteArray& data);
    void onSigModuleStartMonitor(quint16 module);
    void onSigModuleStopMonitor(quint16 module);

private:
    QAgentApp                   *m_app;
    QCommander                  *command_thread;
    QPST                        *pstThread ;

    QOTDRModule                 *_module1;
    QOTDRModule                 *_module2;
};

#endif // QAGENTAPP_H
