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
    char* devNetMask;
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
    long pstSystemTrapTargetName;

    /* Column values */
    char pstSystemTrapTargetIpAddr[NNN];
    size_t pstSystemTrapTargetIpAddr_len;
    char old_pstSystemTrapTargetIpAddr[NNN];
    size_t old_pstSystemTrapTargetIpAddr_len;
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

    char  pstSystemTemperature[NNN];
    char  pstSystemTemperatureHighThreshold[NNN];
    char  pstSystemTemperatureLowThreshold[NNN];
    long  pstSystemTemperatureControlMode;
	long  pstSystemADG707Switch;
	long  DDRConsumption;
	long  DDRCleanUp;

}pstSystemStatus;

typedef struct _pstSystemOnlineUpgrade
{
    char pstSystemFtpSrvIp[NNN];
    char pstSystemFtpUserName[NNN];
    char pstSystemFtpUserPwd[NNN];
    char pstSystemFtpFileName[NNN];
    long	pstSystemUpgFileType;
    long	pstSystemUpgDstSlot;
    long	pstSystemUpgAction;
    long	pstSystemUpgStatus1;
    long    pstSystemUpgStatus2;
    char pstSystemUpgResultInfo[NNN];
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
    
    QString get_devName();
    void    set_devName(QString s);
    QString get_devIpAddr();
    void    set_devIpAddr(QString s);
    QString get_devGateway();
    void    set_devGateway(QString s);
    QString get_devNetMask();
    void    set_devNetMask(QString s);
    long    get_saveCurrentConfiguration();
    void    set_saveCurrentConfiguration(long s);
    long    get_reset2Factory();
    void    set_reset2Factory(long rf);
    long    get_reboot();
    void    set_reboot(long s);
    
    QString get_pstHwVer();
    QString get_pstSwVer();
    QString get_pstFwVer();
    QString get_pstModel();
    QString get_pstSn();
	void    set_pstSn(QString s);
    QString get_devMacAddress();


    QString 	get_pstSystemTrapTargetCommunity(int index);
    void 			set_pstSystemTrapTargetCommunity(int index, QString s);
    long			get_pstSystemTrapTargetCommunity_len(int index);
    QString 	get_pstSystemTrapTargetIpAddr(int index);
    void			set_pstSystemTrapTargetIpAddr(int index, QString s);
    long 			get_pstSystemTrapTargetTrapVersion(int index);
    void			set_pstSystemTrapTargetTrapVersion(int index, long s);
    long 			get_pstSystemTrapTargetRowStatus(int index);
    void 			set_pstSystemTrapTargetRowStatus(int index, long s);
    long 		  get_pstSystemTrapFuncEn();
    void          set_pstSystemTrapFuncEn(long s);
    long 		  get_pstSystemTrapCount();   
    
    long get_pstSystemFanTotalNum();                     
    long get_pstSystemPowerTotalNum();      
    QString get_pstSystemTemperature();
    void set_pstSystemTemerature(QString s);
	  QString get_pstSystemTemperatureHighThreshold();                      
	  QString get_pstSystemTemperatureLowThreshold();
	  void set_pstSystemTemperatureHighThreshold(QString s);               	  
	  void set_pstSystemTemperatureLowThreshold(QString s);  
	  long	get_pstSystemTemperatureControlMode(int index);
	  void  set_pstSystemTemperatureControlMode(int index, long s);
	  long	get_pstSystemADG707Switch();
	  void  set_pstSystemADG707Switch(long s);
	  long	get_DDRConsumption();
	  long	get_DDRCleanUp();
	  void  set_DDRCleanUp(long s);
	  
	  
    QString get_pstSystemPowerMaximumConsumption(int index);      
    QString get_pstSystemPowerVoltage12VA(int index);             
    QString get_pstSystemPowerVoltage12VB(int index);             
    QString get_pstSystemPowerVoltage12VFAN(int index);           
    QString get_pstSystemPowerVoltage12VOTDR1(int index);         
    QString get_pstSystemPowerVoltage12VOTDR2(int index);         
    QString get_pstSystemPowerVoltageVDD5V(int index);            
    QString get_pstSystemPowerVoltageVDD3V3(int index);           
    QString get_pstSystemPowerVoltage1V8RTC(int index);

    long get_pstSystemFanStatus(long index);
    long get_pstSystemFanSpeed(long index);

	  
	  QString get_pstSystemFtpSrvIp();
    QString get_pstSystemFtpUserName();
    QString get_pstSystemFtpUserPwd();
    QString get_pstSystemFtpFileName();
    long	  get_pstSystemUpgFileType();
    long	  get_pstSystemUpgDstSlot();
    long	  get_pstSystemUpgAction();
    void    set_pstSystemFtpSrvIp(QString s);
    void    set_pstSystemFtpUserName(QString s);
    void    set_pstSystemFtpUserPwd(QString s);
    void    set_pstSystemFtpFileName(QString s);
    void    set_pstSystemUpgFileType(long s);
    void    set_pstSystemUpgDstSlot(long s);
    void    set_pstSystemUpgAction(long s);
        
    long get_pstSystemUpgStatus(int slot);
    void set_pstSystemUpgStatus(int slot, int status);
    QString get_pstSystemUpgResultInfo(int slot);
    long get_pstSystemProductType();
signals:

public slots:


private:
    QSettings    _ss;
};

#endif // QPSTSYSTEMPRIVATE_H
