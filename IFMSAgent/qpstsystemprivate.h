#ifndef QPSTSYSTEMPRIVATE_H
#define QPSTSYSTEMPRIVATE_H

#include <QObject>
#include <QSettings>
#include <QString>
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
#define SYSTEM_SETTINGS_GROUP		"SYSTEM"
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

typedef struct pstSystemTrapTargetTable_entry {
    /* Index values */
    char pstSystemTrapTargetName[NNN];
    size_t pstSystemTrapTargetName_len;

    /* Column values */
    char pstSystemTrapTargetIpAddr[NNN];
    size_t pstSystemTrapTargetIpAddr_len;
    char old_pstSystemTrapTargetIpAddr[NNN];
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

typedef struct pstSystemFanTable_entry {
    /* Index values */
    long pstSystemFanIndex;

    /* Column values */
//    long pstSystemFanIndex;
    long pstSystemFanStatus;
    long pstSystemFanSpeed;

    int   valid;
}pstSystemFanEntry;

typedef struct pstSystemPowerTable_entry {
    /* Index values */
    char pstSystemPowerIndex[NNN];
    size_t pstSystemPowerIndex_len;

    /* Column values */
//    char pstSystemPowerIndex[NNN];
//    size_t pstSystemPowerIndex_len;
    char pstSystemPowerMaximumConsumption[NNN];
    size_t pstSystemPowerMaximumConsumption_len;
    char pstSystemPowerVoltage12VA[NNN];
    size_t pstSystemPowerVoltage12VA_len;
    char pstSystemPowerVoltage12VB[NNN];
    size_t pstSystemPowerVoltage12VB_len;
    char pstSystemPowerVoltage12VFAN[NNN];
    size_t pstSystemPowerVoltage12VFAN_len;
    char pstSystemPowerVoltage12VOTDR1[NNN];
    size_t pstSystemPowerVoltage12VOTDR1_len;
    char pstSystemPowerVoltage12VOTDR2[NNN];
    size_t pstSystemPowerVoltage12VOTDR2_len;
    char pstSystemPowerVoltageVDD5V[NNN];
    size_t pstSystemPowerVoltageVDD5V_len;
    char pstSystemPowerVoltageVDD3V3[NNN];
    size_t pstSystemPowerVoltageVDD3V3_len;
    char pstSystemPowerVoltage1V8RTC[NNN];
    size_t pstSystemPowerVoltage1V8RTC_len;

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
    void    set_devName(QString s);
    QString get_devIpAddr();
    void    set_devIpAddr(QString s);
    QString get_devGateway();
    void    set_devGateway(QString s);
    QString get_devNetMask();
    void    set_devNetMask(QString s);
    long    get_saveCurrentConfiguration();
    void    set_saveCurrentConfiguration(long cfg);
    long    get_reset2Factory();
    void    set_reset2Factory(long rf);
    long    get_reboot();
    void    set_reboot(long rb);

    QString	get_pstSystemTrapTargetName(int index);

    long	get_pstSystemTrapTargetName_len(int index);

    QString get_pstSystemTrapTargetCommunity(int index);

    void 	set_pstSystemTrapTargetCommunity(int index, QString s);


    long	get_pstSystemTrapTargetCommunity_len(int index);


    QString 	get_pstSystemTrapTargetIpAddr(int index);

    void	set_pstSystemTrapTargetIpAddr(int index, QString s);


    long 	get_pstSystemTrapTargetTrapVersion(int index);

    void	set_pstSystemTrapTargetTrapVersion(int index, long version);


    long 	get_pstSystemTrapTargetRowStatus(int index);

    void 	set_pstSystemTrapTargetRowStatus(int index, long status);


private:
    QSettings    _ss;
};

#endif // QPSTSYSTEMPRIVATE_H
