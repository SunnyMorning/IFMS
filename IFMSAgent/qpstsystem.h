#ifndef QPSTSYSTEM_H
#define QPSTSYSTEM_H

#include <QObject>
#include <QMutex>
#include <QMutexLocker>
#include <QSettings>
#include <QString>

#include <net-snmp/net-snmp-config.h>
#include <net-snmp/net-snmp-features.h>
#include <net-snmp/net-snmp-includes.h>
#include <net-snmp/agent/net-snmp-agent-includes.h>
#include <net-snmp/agent/agent_handler.h>

#include "qpstsystemprivate.h"

static QMutex   gPSTSystem_mutex;

/* column number definitions for table pstSystemTrapTargetTable */
       #define COLUMN_PSTSYSTEMTRAPTARGETNAME		1
       #define COLUMN_PSTSYSTEMTRAPTARGETIPADDR		2
       #define COLUMN_PSTSYSTEMTRAPTARGETCOMMUNITY		3
       #define COLUMN_PSTSYSTEMTRAPTARGETTRAPVERSION		4
       #define COLUMN_PSTSYSTEMTRAPTARGETROWSTATUS		5

/* column number definitions for table pstSystemFanTable */
       #define COLUMN_PSTSYSTEMFANINDEX		1
       #define COLUMN_PSTSYSTEMFANSTATUS		2
       #define COLUMN_PSTSYSTEMFANSPEED		3

/* column number definitions for table pstSystemPowerTable */
       #define COLUMN_PSTSYSTEMPOWERINDEX		1
       #define COLUMN_PSTSYSTEMPOWERSTATUS		2
       #define COLUMN_PSTSYSTEMPOWERVOLTAGE		3
       #define COLUMN_PSTSYSTEMPOWERCURRENT		4

class QPSTSystem : public QObject
{
    Q_OBJECT
public:
    explicit QPSTSystem(QObject *parent = 0);
	
    QPSTSystemPrivate	m_pstSystem;
    void init_pstSystemData();
    void init_pstSystem();

static Netsnmp_Node_Handler handle_devName;
static Netsnmp_Node_Handler handle_devIpAddr;
static Netsnmp_Node_Handler handle_devGateway;
static Netsnmp_Node_Handler handle_devNetMask;
static Netsnmp_Node_Handler handle_saveCurrentConfiguration;
static Netsnmp_Node_Handler handle_reset2Factory;
static Netsnmp_Node_Handler handle_reboot;
static Netsnmp_Node_Handler handle_pstHwVer;
static Netsnmp_Node_Handler handle_pstSwVer;
static Netsnmp_Node_Handler handle_pstFwVer;
static Netsnmp_Node_Handler handle_pstModel;
static Netsnmp_Node_Handler handle_pstSn;
static Netsnmp_Node_Handler handle_devMacAddress;
static Netsnmp_Node_Handler handle_pstSystemTrapFuncEn;
static Netsnmp_Node_Handler handle_pstSystemFanTotalNum;
static Netsnmp_Node_Handler handle_pstSystemPowerTotalNum;
static Netsnmp_Node_Handler handle_pstSystemTemperature;
static Netsnmp_Node_Handler handle_pstSystemFtpSrvIp;
static Netsnmp_Node_Handler handle_pstSystemFtpUserName;
static Netsnmp_Node_Handler handle_pstSystemFtpUserPwd;
static Netsnmp_Node_Handler handle_pstSystemFtpFileName;
static Netsnmp_Node_Handler handle_pstSystemUpgFileType;
static Netsnmp_Node_Handler handle_pstSystemUpgDstSlot;
static Netsnmp_Node_Handler handle_pstSystemUpgAction;
static Netsnmp_Node_Handler handle_pstSystemUpgStatus;
static Netsnmp_Node_Handler handle_pstSystemUpgResultInfo;
static Netsnmp_Node_Handler handle_pstSystemProductType;
static void initialize_table_pstSystemTrapTargetTable(void);          
static Netsnmp_Node_Handler pstSystemTrapTargetTable_handler;         
static void initialize_table_pstSystemFanTable(void);                 
static Netsnmp_Node_Handler pstSystemFanTable_handler;                
static void initialize_table_pstSystemPowerTable(void);               
static Netsnmp_Node_Handler pstSystemPowerTable_handler;              

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

};

#endif // QPSTSYSTEM_H
