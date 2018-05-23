#ifndef QPSTSYSTEMPRIVATE_H
#define QPSTSYSTEMPRIVATE_H

#include <QObject>
#include <QSettings>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>

#define NUMBER_OF_FANS				4
#define NUMBER_OF_POWERS			8
#define NUMBER_OF_TRAPTARGETS		2
#define NNN							32

using namespace std;

typedef struct  _pstSystemBasicManagement
{
    char*	devName;
    char*	devIpAddr;
    char*	devGateway;
    char*  devNetMask;
    long	saveCurrentConfiguration;
    long	reset2Factory;
    long	reboot;
}pstSystemBasicManagement;

typedef struct  _pstSystemVerInfo
{
        char* pstHwVer;
        char* pstSwVer;
        char* pstFwVer;
        char* pstModel;
        char* pstSn;
        char* devMacAddress;
}pstSystemVerInfo;

typedef struct pstSystemTrapTargetTable_entry{
		/* Index values */
		char pstSystemTrapTargetName[NNN];
		size_t pstSystemTrapTargetName_len;
	
		/* Column values */
		in_addr_t pstSystemTrapTargetIpAddr;
		in_addr_t old_pstSystemTrapTargetIpAddr;
		char pstSystemTrapTargetCommunity[NNN];
		size_t pstSystemTrapTargetCommunity_len;
		char old_pstSystemTrapTargetCommunity[NNN];
		size_t old_pstSystemTrapTargetCommunity_len;
		long pstSystemTrapTargetTrapVersion;
		long old_pstSystemTrapTargetTrapVersion;
		long pstSystemTrapTargetRowStatus;
		long old_pstSystemTrapTargetRowStatus;
	
		int   valid;
}pstSystemTrapTargetEntry;


typedef struct _pstSystemTrapInfo
{
    long pstSystemTrapFuncEn;
    long pstSystemTrapCount;
    vector<pstSystemTrapTargetEntry>   pstSystemTrapTargetTable;
}pstSystemTrapInfo;

typedef struct pstSystemFanTable_entry{
    /* Index values */
//    long pstSystemFanIndex;

    /* Column values */
    long pstSystemFanIndex;
    long pstSystemFanStatus;
    long pstSystemFanSpeed;

    int   valid;
}pstSystemFanEntry;

typedef struct pstSystemPowerTable_entry {
		 /* Index values */
//		 long pstSystemPowerIndex;
	 
		 /* Column values */
		 long pstSystemPowerIndex;
		 long pstSystemPowerStatus;
		 char pstSystemPowerVoltage[NNN];
		 size_t pstSystemPowerVoltage_len;
		 char pstSystemPowerCurrent[NNN];
		 size_t pstSystemPowerCurrent_len;
	 
		 int   valid;
}pstSystemPowerEntry;

typedef struct  _pstSystemStatus
{
    long pstSystemFanTotalNum;
    long pstSystemPowerTotalNum;

    vector<pstSystemFanEntry>	pstSystemFanTable;
    vector<pstSystemPowerEntry> pstSystemPowerTable;

    char* pstSystemTemperature;
}pstSystemStatus;

typedef struct _pstSystemOnlineUpgrade
{
    char* pstSystemFtpSrvIp;
    char* pstSystemFtpUserName;
    char* pstSystemFtpUserPwd;
    char* pstSystemFtpFileName;
    long	 pstSystemUpgFileType;
    long	 pstSystemUpgDstSlot;
    long	 pstSystemUpgAction;
    long	 pstSystemUpgStatus;
    char*    pstSystemUpgResultInfo;
}pstSystemOnlineUpgrade;

typedef struct _pstSystemProductInfo
{
    long pstSystemProductType;
}pstSystemProductInfo;

//typedef struct _pstSystem{
//    pstSystemBasicManagement  BasicManagement;
//    pstSystemVerInfo  VerInfo;
//    pstSystemTrapInfo  TrapInfo;
//    pstSystemStatus  Status;
//    pstSystemOnlineUpgrade  OnlineUpgrade;
//    pstSystemProductInfo  ProductInfo;
//}pstSystem;

class QPSTSystemPrivate : public QObject
{
    Q_OBJECT
public:
    explicit QPSTSystemPrivate(QObject *parent = 0);
    pstSystemBasicManagement  BasicManagement;
    pstSystemVerInfo  VerInfo;
    pstSystemTrapInfo  TrapInfo;
    pstSystemStatus  Status;
    pstSystemOnlineUpgrade  OnlineUpgrade;
    pstSystemProductInfo  ProductInfo;

    void init_pstData();

signals:

public slots:
    QString get_devName();
    void    set_devName(QString name);
    QString get_devIpAddr();
    void    set_devIpAddr(QString ip);
    QString get_devGateway();
    void    set_devGateway(QString gw);
    QString get_devNetMask();
    void    set_devNetMask(QString msk);
    long    get_saveCurrentConfiguration();
    void    set_saveCurrentConfiguration(long cfg);
    long    get_reset2Factory();
    void    set_reset2Factory(long rf);
    long    get_reboot();
    void    set_reboot(long rb);

private:
    QSettings    _ss;
};

#endif // QPSTSYSTEMPRIVATE_H
