#ifndef QPSTPRODUCT_H
#define QPSTPRODUCT_H

#include <QObject>
#include <QSettings>

#include <net-snmp/net-snmp-config.h>
#include <net-snmp/net-snmp-features.h>
#include <net-snmp/net-snmp-includes.h>
#include <net-snmp/agent/net-snmp-agent-includes.h>
#include <net-snmp/agent/agent_handler.h>
#include <net-snmp/agent/agent_trap.h>

#include "qpstproductprivate.h"

/* column number definitions for table pstIFMS1000PortInfoTable */
       #define COLUMN_PSTIFMS1000PORTNUM		1
       #define COLUMN_PSTIFMS1000PORTRXPWR		2
       #define COLUMN_PSTIFMS1000PORTTXPWR		3
       #define COLUMN_PSTIFMS1000PORTWORKMODE		4
       #define COLUMN_PSTIFMS1000PORTACTIVE		5
       #define COLUMN_PSTIFMS1000PORTFIBERAPPTYPE		6
       #define COLUMN_PSTIFMS1000PORTRUNNINGSTATUS		7

/* column number definitions for table pstIFMS1000MeasureTable */
       #define COLUMN_PSTIFMS1000MTPORTNUM		1
       #define COLUMN_PSTIFMS1000MEASURESTARTPOSITION		2
       #define COLUMN_PSTIFMS1000MEASUREENDPOSITION		3
       #define COLUMN_PSTIFMS1000MEASUREREFINDEX		4
       #define COLUMN_PSTIFMS1000MEASURERESOLUTION		5
       #define COLUMN_PSTIFMS1000MEASURESTATUS		6
       #define COLUMN_PSTIFMS1000MEASUREACTION		7
       #define COLUMN_PSTIFMS1000MEASURERESULTFILE		8
       #define COLUMN_PSTIFMS1000MEASURERESULTRAWDATAFILE		9
       #define COLUMN_PSTIFMS1000MEASUREPROGRESSSTATUS		10
       #define COLUMN_PSTIFMS1000MEASURERESULTRAWPOINTFILE		11

/* column number definitions for table pstIFMS1000FingerTable */
       #define COLUMN_PSTIFMS1000FTPORTNUM		1
       #define COLUMN_PSTIFMS1000FINGERSTARTPOSITION		2
       #define COLUMN_PSTIFMS1000FINGERENDPOSITION		3
       #define COLUMN_PSTIFMS1000FINGERREFINDEX		4
       #define COLUMN_PSTIFMS1000FINGERRESOLUTION		5
       #define COLUMN_PSTIFMS1000FINGERCREATETIME		6
       #define COLUMN_PSTIFMS1000FINGERFILESTATUS		7
       #define COLUMN_PSTIFMS1000FINGERACTION		8
       #define COLUMN_PSTIFMS1000FINGERACTIONSTATUS		9
       #define COLUMN_PSTIFMS1000FINGERSAVEDFILENAME		10
       #define COLUMN_PSTIFMS1000FINGERCURRENTFILENAME		11

/* column number definitions for table pstIFMS1000DiffTotalTable */
       #define COLUMN_PSTIFMS1000DTPORTNUM		1
       #define COLUMN_PSTIFMS1000DTTOTALNUM		2

/* column number definitions for table pstIFMS1000DiffInfoTable */
       #define COLUMN_PSTIFMS1000DIFFINFOPORTNUM		1
       #define COLUMN_PSTIFMS1000DIFFINFOPORTITEMINDEX		2
       #define COLUMN_PSTIFMS1000DIFFINFODISTANCE		3
       #define COLUMN_PSTIFMS1000DIFFINFONVAL		4
       #define COLUMN_PSTIFMS1000DIFFINFODBVAL		5
       #define COLUMN_PSTIFMS1000DIFFINFODIFFTYPE		6
       #define COLUMN_PSTIFMS1000DIFFINFOPOINTID		7

/* column number definitions for table pstIFMS1000PortLedTable */
       #define COLUMN_PSTIFMS1000PORTLEDPORTNUM		1
       #define COLUMN_PSTIFMS1000PORTLEDSTATUS		2

/* column number definitions for table pstIFMS1000DiagnoseTable */
       #define COLUMN_PSTIFMS1000DGPORTNUM		1
       #define COLUMN_PSTIFMS1000DGLASERACBIAS		2
       #define COLUMN_PSTIFMS1000DGLASERDCBIAS		3
       #define COLUMN_PSTIFMS1000DGLASERACMODULATION		4
       #define COLUMN_PSTIFMS1000DGLASERDCMODULATION		5
       #define COLUMN_PSTIFMS1000DGLASEREN		6
       #define COLUMN_PSTIFMS1000DGPWM		7
       #define COLUMN_PSTIFMS1000DGSEED		8
       #define COLUMN_PSTIFMS1000DGPRBS		9
       #define COLUMN_PSTIFMS1000DGAVERAGE		10
       #define COLUMN_PSTIFMS1000DGREGADDR		11
       #define COLUMN_PSTIFMS1000DGREGVALUE		12
       #define COLUMN_PSTIFMS1000DGMASKSTARTPOINT		13
       #define COLUMN_PSTIFMS1000DGMASKSTOPPOINT		14
       #define COLUMN_PSTIFMS1000DGMASKACTION		15
       #define COLUMN_PSTIFMS1000DGMEASUREDELTATHLD		16
       #define COLUMN_PSTIFMS1000DGCUTPOINTTHLD		17
       #define COLUMN_PSTIFMS1000DGPERIOD		18
       #define COLUMN_PSTIFMS1000DGDAC		19
       #define COLUMN_PSTIFMS1000DGCOUNTERCLOCKMODE		20
       #define COLUMN_PSTIFMS1000DGSCANRUNTYPE		21
       #define COLUMN_PSTIFMS1000DGOPT		22
       #define COLUMN_PSTIFMS1000DGFIBEROFFSET		23
       #define COLUMN_PSTIFMS1000DGTESTWAVELEN		24
       #define COLUMN_PSTIFMS1000DGPRT		25
       #define COLUMN_PSTIFMS1000DGPPW		26
       #define COLUMN_PSTIFMS1000DGPPRESCALE		27
       #define COLUMN_PSTIFMS1000DGPAVG		28
       #define COLUMN_PSTIFMS1000DGPGAIN		29
       #define COLUMN_PSTIFMS1000DGPADCDATA		30
       #define COLUMN_PSTIFMS1000DGPE2PROMACTION		31

/* column number definitions for table pstIFMS1000DebugRegTable */
       #define COLUMN_PSTIFMS1000DBPORTNUM		1
       #define COLUMN_PSTIFMS1000DBREGADDR		11
       #define COLUMN_PSTIFMS1000DBREGVALUE		12

/* column number definitions for table pstIFMS1000DebugDACTable */
       #define COLUMN_PSTIFMS1000DACTPORTNUM		1
       #define COLUMN_PSTIFMS1000DACTCHANNELNUM		2
       #define COLUMN_PSTIFMS1000TDACVALUE		3

/* column number definitions for table pstIFMS1000DebugE2promTable */
       #define COLUMN_PSTIFMS1000DBE2TPORTNUM		1
       #define COLUMN_PSTIFMS1000DBE2TADDR		2
       #define COLUMN_PSTIFMS1000DBE2TVALUE		3

/* column number definitions for table pstIFMS1000ExtendAlarmTable */
       #define COLUMN_PSTIFMS1000EAPORTNUM		1
       #define COLUMN_PSTIFMS1000EXTENDALARM		2

/* column number definitions for table pstIFMS1000ExpertExtendTable */
       #define COLUMN_PSTIFMS1000EEPORTNUM		1
       #define COLUMN_PSTIFMS1000DGPBIAS1		2
       #define COLUMN_PSTIFMS1000DGPBIAS2		3
       #define COLUMN_PSTIFMS1000DGPMODULATION1		4
       #define COLUMN_PSTIFMS1000DGPMODULATION2		5
       #define COLUMN_PSTIFMS1000DGPBACKSCATTER		6
       #define COLUMN_PSTIFMS1000DGPMEASUREDELTATHLD		7
       #define COLUMN_PSTIFMS1000DGPCUTPOINTTHLD		8
       #define COLUMN_PSTIFMS1000DGPMFACTOR		9
       #define COLUMN_PSTIFMS1000DGFAULTCRITICALTHLD		10
       #define COLUMN_PSTIFMS1000DGFAULTMAJORTHLD		11
       #define COLUMN_PSTIFMS1000DGFAULTMINORTHLD		12
       #define COLUMN_PSTIFMS1000DGPAFACTOR		13
       #define COLUMN_PSTIFMS1000DGPBFACTOR		14

/* column number definitions for table pstIFMS1000PonConfTable */
       #define COLUMN_PCTPORTNUM		1
       #define COLUMN_PCTSP1LOCITEM		2

/* column number definitions for table pstIFMS1000ParamsV32TotalNumTable */
       #define COLUMN_V32TPORTNUM		1
       #define COLUMN_V32PORTTOTALNUM		2

/* column number definitions for table pstIFMS1000ParamsV32NameTable */
       #define COLUMN_V32PORTNUM		1
       #define COLUMN_V32PARAMNAMENUM		2
       #define COLUMN_V32PARAMNAME		3

/* column number definitions for table pstIFMS1000ParamsV32ValTable */
       #define COLUMN_V32VALPORTNUM		1
       #define COLUMN_V32PARAMVALNUM		2
       #define COLUMN_V32PARAMVAL		3

/* column number definitions for table pstIFMS1000ParamsS32TotalNumTable */
       #define COLUMN_S32TPORTNUM		1
       #define COLUMN_S32PORTTOTALNUM		2

/* column number definitions for table pstIFMS1000ParamsS32NameTable */
       #define COLUMN_S32PORTNUM		1
       #define COLUMN_S32PARAMNAMENUM		2
       #define COLUMN_S32PARAMNAMEVAL		3

/* column number definitions for table pstIFMS1000ParamsS32ValTable */
       #define COLUMN_S32VALPORTNUM		1
       #define COLUMN_S32PARAMVALNUM		2
       #define COLUMN_S32PARAMVAL		3


class QPSTProduct : public QObject
{
    Q_OBJECT
public:
    explicit QPSTProduct(QObject *parent = 0);

    void init_pstIFMS1000Data();
    void init_pstIFMS1000(void);

    QPSTProductPrivate  m_pstIFMS1000;

    static long get_pstIFMS1000SysLedPW1(QObject *agent);
    static long get_pstIFMS1000SysLedPW2(QObject *agent);
    static long get_pstIFMS1000SysLedStatus(QObject *agent);

// SCALAR
    static Netsnmp_Node_Handler handle_pstIFMS1000SysLedPW1;
    static Netsnmp_Node_Handler handle_pstIFMS1000SysLedPW2;
    static Netsnmp_Node_Handler handle_pstIFMS1000SysLedStatus;
    static Netsnmp_Node_Handler handle_pstIFMS1000BootMode;
    static Netsnmp_Node_Handler handle_pstIFMS1000SwitchModuleNum;
    static Netsnmp_Node_Handler handle_pstIFMS1000SwitchInterval;
    static Netsnmp_Node_Handler handle_pstIFMS1000SwitchCurrentPort;
    static Netsnmp_Node_Handler handle_pstIFMS1000ExtSwitchAttType;
    static Netsnmp_Node_Handler handle_pstIFMS1000ExtSwitchAttachPort;
    static Netsnmp_Node_Handler handle_pstIFMS1000ExtSwitchConnType;
    static Netsnmp_Node_Handler handle_pstIFMS1000ExtSwitchIpAddr;
    static Netsnmp_Node_Handler handle_pstIFMS1000ExtSwitchIpPort;
    static Netsnmp_Node_Handler handle_pstIFMS1000ExtSwitchUartBaud;
    static Netsnmp_Node_Handler handle_pstIFMS1000ExtSwitchTotalSwitchNum;
    static Netsnmp_Node_Handler handle_pstIFMS1000ExtSwitchCurrentNum;
    static Netsnmp_Node_Handler handle_pstIFMS1000ExtSwitchStatus;

// Table
    void initialize_table_pstIFMS1000PortInfoTable(void);
    static Netsnmp_Node_Handler pstIFMS1000PortInfoTable_handler;
    void initialize_table_pstIFMS1000MeasureTable(void);
    static Netsnmp_Node_Handler pstIFMS1000MeasureTable_handler;
    void initialize_table_pstIFMS1000FingerTable(void);
    static Netsnmp_Node_Handler pstIFMS1000FingerTable_handler;
    void initialize_table_pstIFMS1000DiffTotalTable(void);
    static Netsnmp_Node_Handler pstIFMS1000DiffTotalTable_handler;
    void initialize_table_pstIFMS1000DiffInfoTable(void);
    static Netsnmp_Node_Handler pstIFMS1000DiffInfoTable_handler;
    void initialize_table_pstIFMS1000PortLedTable(void);
    static Netsnmp_Node_Handler pstIFMS1000PortLedTable_handler;
    void initialize_table_pstIFMS1000DiagnoseTable(void);
    static Netsnmp_Node_Handler pstIFMS1000DiagnoseTable_handler;
    void initialize_table_pstIFMS1000DebugRegTable(void);
    static Netsnmp_Node_Handler pstIFMS1000DebugRegTable_handler;
    void initialize_table_pstIFMS1000DebugDACTable(void);
    static Netsnmp_Node_Handler pstIFMS1000DebugDACTable_handler;
    void initialize_table_pstIFMS1000DebugE2promTable(void);
    static Netsnmp_Node_Handler pstIFMS1000DebugE2promTable_handler;
    void initialize_table_pstIFMS1000ExtendAlarmTable(void);
    static Netsnmp_Node_Handler pstIFMS1000ExtendAlarmTable_handler;
    void initialize_table_pstIFMS1000ExpertExtendTable(void);
    static Netsnmp_Node_Handler pstIFMS1000ExpertExtendTable_handler;
    void initialize_table_pstIFMS1000PonConfTable(void);
    static Netsnmp_Node_Handler pstIFMS1000PonConfTable_handler;
    void initialize_table_pstIFMS1000ParamsV32TotalNumTable(void);
    static Netsnmp_Node_Handler pstIFMS1000ParamsV32TotalNumTable_handler;
    void initialize_table_pstIFMS1000ParamsV32NameTable(void);
    static Netsnmp_Node_Handler pstIFMS1000ParamsV32NameTable_handler;
    void initialize_table_pstIFMS1000ParamsV32ValTable(void);
    static Netsnmp_Node_Handler pstIFMS1000ParamsV32ValTable_handler;
    void initialize_table_pstIFMS1000ParamsS32TotalNumTable(void);
    static Netsnmp_Node_Handler pstIFMS1000ParamsS32TotalNumTable_handler;
    void initialize_table_pstIFMS1000ParamsS32NameTable(void);
    static Netsnmp_Node_Handler pstIFMS1000ParamsS32NameTable_handler;
    void initialize_table_pstIFMS1000ParamsS32ValTable(void);
    static Netsnmp_Node_Handler pstIFMS1000ParamsS32ValTable_handler;

// Trap
    int send_pstIFMS1000MeasureEvent_trap(void);

signals:

public slots:
    void setModuleMeasuringProgess(quint16 module, quint16 progress);

private:

};

#endif // QPSTPRODUCT_H
