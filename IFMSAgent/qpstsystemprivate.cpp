#include "qpstsystemprivate.h"

QPSTSystemPrivate::QPSTSystemPrivate(QObject *parent) : QObject(parent)
{

}

void QPSTSystemPrivate::init_pstData()
{
    int i=0;
    memset(&BasicManagement, 0, sizeof(BasicManagement));
    BasicManagement.devName = "IFMS";
    BasicManagement.devIpAddr = "192.168.1.100";
    BasicManagement.devGateway = "192.168.1.1";
    BasicManagement.devNetMask = "255.255.255.0";
    BasicManagement.saveCurrentConfiguration = 1;
    BasicManagement.reset2Factory = 0;
    BasicManagement.reboot = 1;
	
    memset(&VerInfo, 0, sizeof(VerInfo));
    VerInfo.pstHwVer = "1.0.0";
    VerInfo.pstSwVer = "1.0.0";
    VerInfo.pstFwVer = "1.0.0";
    VerInfo.pstModel = "IFMS-1000";
    VerInfo.pstSn = "IFMS-2018-0001";
    VerInfo.devMacAddress = "AA:BB:CC:DD:EE:FF";

    pstSystemTrapTargetEntry trapTarget;
    pstSystemFanEntry fan;
    pstSystemPowerEntry power;
    memset(&TrapInfo, 0, sizeof(TrapInfo));
    TrapInfo.pstSystemTrapCount = NUMBER_OF_TRAPTARGETS;
    TrapInfo.pstSystemTrapFuncEn = 1;
    for(i=0;i<NUMBER_OF_TRAPTARGETS;i++){

        trapTarget.pstSystemTrapTargetName = "192.168.1.44:1622";
        trapTarget.pstSystemTrapTargetIpAddr = "192.168.1.44";
        trapTarget.pstSystemTrapTargetCommunity = "public";
        trapTarget.pstSystemTrapTargetTrapVersion = 2;
        trapTarget.pstSystemTrapTargetRowStatus = 4;
        TrapInfo.pstSystemTrapTargetTable.push_back(trapTarget);
    }

    memset(&Status, 0, sizeof(Status));
    Status.pstSystemFanTotalNum = NUMBER_OF_FANS;
    for(i=0;i<NUMBER_OF_FANS;i++){
        fan.pstSystemFanIndex = i+1;
        fan.pstSystemFanSpeed = 255;
        fan.pstSystemFanStatus = 0;
        Status.pstSystemFanTable.push_back(fan);
    }

    Status.pstSystemPowerTotalNum = NUMBER_OF_POWERS;
    for(i=0;i<NUMBER_OF_POWERS;i++){
        power.pstSystemPowerIndex = i+1;
        power.pstSystemPowerCurrent = "1";
        power.pstSystemPowerVoltage = "12";
        power.pstSystemPowerStatus = 0;
        Status.pstSystemPowerTable.push_back(power);
    }

    Status.pstSystemTemperature = "50";
	
    memset(&OnlineUpgrade, 0, sizeof(OnlineUpgrade));
    OnlineUpgrade.pstSystemFtpSrvIp = "192.168.1.100";
    OnlineUpgrade.pstSystemFtpUserName = "ifms";
    OnlineUpgrade.pstSystemFtpUserPwd = "ifms";
    OnlineUpgrade.pstSystemFtpFileName = "*.*";
    OnlineUpgrade.pstSystemUpgFileType = 1;
    OnlineUpgrade.pstSystemUpgDstSlot = 1;
    OnlineUpgrade.pstSystemUpgAction = 1;
    OnlineUpgrade.pstSystemUpgStatus = 0;
    OnlineUpgrade.pstSystemUpgResultInfo = "ready";
    ProductInfo.pstSystemProductType = 1000;
}
