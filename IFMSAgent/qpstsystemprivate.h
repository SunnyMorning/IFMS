#ifndef QPSTSYSTEMPRIVATE_H
#define QPSTSYSTEMPRIVATE_H

#include <QObject>
#include <QSettings>

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>

#define NUMBER_OF_FANS				4
#define NUMBER_OF_POWERS			8
#define NUMBER_OF_TRAPTARGETS		2

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

typedef struct _pstSystemTrapTargetEntry{
    char*	pstSystemTrapTargetName;
    char*	pstSystemTrapTargetIpAddr;
    char*	pstSystemTrapTargetCommunity;
    long  pstSystemTrapTargetTrapVersion;
    long  pstSystemTrapTargetRowStatus;
}pstSystemTrapTargetEntry;


typedef struct _pstSystemTrapInfo
{
    long pstSystemTrapFuncEn;
    long pstSystemTrapCount;
    vector<pstSystemTrapTargetEntry>   pstSystemTrapTargetTable;
}pstSystemTrapInfo;

typedef struct _pstSystemFanEntry{
    long  pstSystemFanIndex;
    long  pstSystemFanStatus;
    long  pstSystemFanSpeed;
}pstSystemFanEntry;

typedef struct _pstSystemPowerEntry{
    long  pstSystemPowerIndex;
    long  pstSystemPowerStatus;
    char* pstSystemPowerVoltage;
    char* pstSystemPowerCurrent;
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
};

#endif // QPSTSYSTEMPRIVATE_H
