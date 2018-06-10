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
       #define COLUMN_PSTSYSTEMPOWERMAXIMUMCONSUMPTION		2
       #define COLUMN_PSTSYSTEMPOWERVOLTAGE12VA		3
       #define COLUMN_PSTSYSTEMPOWERVOLTAGE12VB		4
       #define COLUMN_PSTSYSTEMPOWERVOLTAGE12VFAN		5
       #define COLUMN_PSTSYSTEMPOWERVOLTAGE12VOTDR1		6
       #define COLUMN_PSTSYSTEMPOWERVOLTAGE12VOTDR2		7
       #define COLUMN_PSTSYSTEMPOWERVOLTAGEVDD5V		8
       #define COLUMN_PSTSYSTEMPOWERVOLTAGEVDD3V3		9
       #define COLUMN_PSTSYSTEMPOWERVOLTAGE1V8RTC		10

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
static Netsnmp_Node_Handler handle_DDRConsumption;
static Netsnmp_Node_Handler handle_DDRCleanUp;
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
static Netsnmp_Node_Handler handle_pstSystemTemperatureHighThreshold;
static Netsnmp_Node_Handler handle_pstSystemTemperatureLowThreshold;
static Netsnmp_Node_Handler handle_pstSystemTemperatureControlMode;
static Netsnmp_Node_Handler handle_pstSystemADG707Switch;
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

private:

};

#endif // QPSTSYSTEM_H
