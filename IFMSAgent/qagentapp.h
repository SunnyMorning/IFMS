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
#include "qfingerdata.h"

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
				long	  saveCurrentConfiguration;
				long	  reset2Factory;
				long		reboot;
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

    static QString getAppName();
    static QString getConfigDir();
    static QString getCacheDir();
    static QString getDataDir();
    static QString getConfigFile();

    static void message(const QString &text, const QString &title = QString(), QObject *parent = NULL);
    static void warning(const QString &text, const QString &title = QString(), QObject *parent = NULL);
    static void error(const QString &text, const QString &title = QString(), QObject *parent = NULL);

    static bool confirm(const QString &text, const QString &title = QString(), QObject *parent = NULL);
    static void message(const QString &text, QObject *parent);
    static void warning(const QString &text, QObject *parent);
    static bool confirm(const QString &text, QObject *parent);

    static void msg(const QString &title, const QString &text);
    static bool ask(const QString &title, const QString &text);


    QOTDRModule                 *m_module1;
    QOTDRModule                 *m_module2;
    QAgentApp         *app() { return m_app; }
    bool   startSession(int &argc, char **argv);
    void   stopSession();
    bool   sendCommandToModule(QString cmdline, int moduleIndex = 0);

protected:
    void    initAppData();
    void    initFingerBin(QString filename, qint16 ch);

signals:
    void settingsChanged();
    void statusMessage(const QString &msg, int ModuleIndex, int time);
    void statusMessage(const QStringList &msgList, int ModuleIndex, int time);

public slots:
    void onOTDRTrap(QByteArray  &data);


private:
    QAgentApp                   *m_app;
};

#endif // QAGENTAPP_H
