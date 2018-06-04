#include <QHostAddress>
#include <QHostInfo>
#include <QNetworkInterface>
#include <QProcess>
#include <QList>

#include "qpstsystemprivate.h"
#include "qagentapp.h"
#include <stdlib.h>
#include <stdio.h>

QPSTSystemPrivate::QPSTSystemPrivate(QObject *parent) : QObject(parent)
{
    _ss.setPath(QSettings::IniFormat,QSettings::UserScope,QAgentApp::getConfigDir()+ "system.ini");
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
    memset(&TrapInfo, 0, sizeof(TrapInfo));
    TrapInfo.pstSystemTrapCount = NUMBER_OF_TRAPTARGETS;
    TrapInfo.pstSystemTrapFuncEn = 1;

	QStringList		trapTargets;
	QStringList		trapIpAddrs;
	trapTargets << "192.168.1.44:1622" << "192.168.30.2:1622";
	trapIpAddrs << "192.168.1.44" << "192.168.30.2";

	_ss.beginGroup("pstSystemTrapInfo");
	_ss.setValue("pstSystemTrapCount", 2);
	_ss.setValue("pstSystemTrapFuncEn", 1);
	
	_ss.beginWriteArray("pstSystemTrapTargetTable");
    for(i=0;i<NUMBER_OF_TRAPTARGETS;i++){
//        char *str = "192.168.1.44:1622";
//        memcpy(trapTarget.pstSystemTrapTargetName, str, strlen(str));
//
//		struct sockaddr_in sa;
//	 	inet_pton(AF_INET, "192.168.1.44", &(sa.sin_addr));
//	 	in_addr_t	 it = sa.sin_addr.s_addr;
//
//		trapTarget.pstSystemTrapTargetIpAddr = it;
//        str = "public";
//        memcpy(trapTarget.pstSystemTrapTargetCommunity, str, strlen(str));
//        trapTarget.pstSystemTrapTargetTrapVersion = 2;
//        trapTarget.pstSystemTrapTargetRowStatus = 4;
//        TrapInfo.pstSystemTrapTargetTable.push_back(trapTarget);

//		int size = settings.beginReadArray("logins");
//		 for (int i = 0; i < size; ++i) {
//			 settings.setArrayIndex(i);
//			 Login login;
//			 login.userName = settings.value("userName").toString();
//			 login.password = settings.value("password").toString();
//			 logins.append(login);
//		 }
//		 settings.endArray();


		_ss.setArrayIndex(i);
		_ss.setValue("pstSystemTrapTargetName", trapTargets.at(i));
		_ss.setValue("pstSystemTrapTargetIpAddr", trapIpAddrs.at(i));
		_ss.setValue("pstSystemTrapTargetCommunity", QString("public"));
		_ss.setValue("pstSystemTrapVersion", 2);
		_ss.setValue("pstSystemTrapTargetRowStatus", 0);

    }
	_ss.endArray();
	_ss.endGroup();
    _ss.sync();

    pstSystemFanEntry fan;
    pstSystemPowerEntry power;
    memset(&Status, 0, sizeof(Status));
    Status.pstSystemFanTotalNum = NUMBER_OF_FANS;
    for(i=0;i<NUMBER_OF_FANS;i++){
        fan.pstSystemFanIndex = i+1;
        fan.pstSystemFanSpeed = 255;
        fan.pstSystemFanStatus = 0;
        Status.pstSystemFanTable.push_back(fan);
    }

    Status.pstSystemPowerTotalNum = NUMBER_OF_POWERS;
    QString  powerIndex;

    for(i=0;i<NUMBER_OF_POWERS;i++){
        powerIndex = QString("%1").arg(i);
        strcpy(power.pstSystemPowerIndex, powerIndex.toLatin1().data());
//        power.pstSystemPowerCurrent = "1";
//        power.pstSystemPowerVoltage = "12";
//        power.pstSystemPowerStatus = 0;
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

QString QPSTSystemPrivate::get_devName()
{
    QString  s;

    _ss.beginGroup(SYSTEM_SETTINGS_GROUP);
//    _ss.beginReadArray("devName");
//    _ss.setArrayIndex(channel-1);
    s = _ss.value("devName", "IFMS1000").toString();
//    _ss.endArray();
    _ss.endGroup();

    return s;
}

void    QPSTSystemPrivate::set_devName(QString s)
{
    _ss.beginGroup(SYSTEM_SETTINGS_GROUP);
//        _ss.beginWriteArray("pstIFMS1000PortRxPwr");
//            _ss.setArrayIndex(channel-1);
            _ss.setValue("devName", s);
//        _ss.endArray();
    _ss.endGroup();
    _ss.sync();
}

QString QPSTSystemPrivate::get_devIpAddr()
{
    QString  s;
    QNetworkInterface a = QNetworkInterface::interfaceFromName("eth1");

    QList<QHostAddress> list = a.allAddresses();
    foreach(QHostAddress add, list){
        if((add.protocol() == QAbstractSocket::IPv4Protocol)
                &&(add != QHostAddress::LocalHost)){
        s = add.toString();
        }
    }
    if(s.isEmpty()){
        s = QString("192.168.1.100");
    }

    return s;
}

void    QPSTSystemPrivate::set_devIpAddr(QString s)
{
//    QNetworkInterface a = QNetworkInterface::interfaceFromName("eth1");
//    QList<QHostAddress> list = a.allAddresses();
//    if(list.size() > 0){
//        QHostAddress h = list.at(0);
//        h.setAddress(s);
//    }
}

QString QPSTSystemPrivate::get_devGateway()
{

}

void    QPSTSystemPrivate::set_devGateway(QString s)
{

}

QString QPSTSystemPrivate::get_devNetMask()
{

}

void    QPSTSystemPrivate::set_devNetMask(QString s)
{

}

long    QPSTSystemPrivate::get_saveCurrentConfiguration()
{

}

void    QPSTSystemPrivate::set_saveCurrentConfiguration(long cfg)
{

}

long    QPSTSystemPrivate::get_reset2Factory()
{

}

void    QPSTSystemPrivate::set_reset2Factory(long rf)
{

}

long    QPSTSystemPrivate::get_reboot()
{

}

void    QPSTSystemPrivate::set_reboot(long rb)
{

}

QString	QPSTSystemPrivate::get_pstSystemTrapTargetName(int index)
{
    QString  targetName = QString("%1").arg(index);
//	int size = _ss.beginReadArray("pstSystemTrapTargetTable");
//	_ss.setArrayIndex(index);
//    targetName = _ss.value("pstSystemTrapTargetName", "0").toString();
    return targetName;
}

long	QPSTSystemPrivate::get_pstSystemTrapTargetName_len(int index)
{

}

QString QPSTSystemPrivate::get_pstSystemTrapTargetCommunity(int index)
{
    QString  s;

    _ss.beginGroup(SYSTEM_SETTINGS_GROUP);
    _ss.beginReadArray("pstSystemTrapTargetCommunity");
    _ss.setArrayIndex(index);
    s = _ss.value("pstSystemTrapTargetCommunity", "public").toString();
    _ss.endArray();
    _ss.endGroup();

    return s;
}

void 	QPSTSystemPrivate::set_pstSystemTrapTargetCommunity(int index, QString s)
{
    _ss.beginGroup(SYSTEM_SETTINGS_GROUP);
        _ss.beginWriteArray("pstSystemTrapTargetCommunity");
            _ss.setArrayIndex(index);
            _ss.setValue("pstSystemTrapTargetCommunity", s);
        _ss.endArray();
    _ss.endGroup();
    _ss.sync();
}

long	QPSTSystemPrivate::get_pstSystemTrapTargetCommunity_len(int index)
{

}

QString 	QPSTSystemPrivate::get_pstSystemTrapTargetIpAddr(int index)
{
//    struct sockaddr_in sa;
    QString  s;
    QString  ip = QString("192.168.1.%1").arg(index+43);
    _ss.beginGroup(SYSTEM_SETTINGS_GROUP);
    _ss.beginReadArray("pstSystemTrapTargetIpAddr");
    _ss.setArrayIndex(index);
    s = _ss.value("pstSystemTrapTargetIpAddr", ip).toString();
    _ss.endArray();
    _ss.endGroup();

//    inet_pton(AF_INET, s.toLatin1().data(), &(sa.sin_addr));
//    in_addr_t   it = sa.sin_addr.s_addr;

//    return it;
    return s;
}

void	QPSTSystemPrivate::set_pstSystemTrapTargetIpAddr(int index, QString s)
{
    _ss.beginGroup(SYSTEM_SETTINGS_GROUP);
        _ss.beginWriteArray("pstSystemTrapTargetIpAddr");
            _ss.setArrayIndex(index);
            _ss.setValue("pstSystemTrapTargetIpAddr", s);
        _ss.endArray();
    _ss.endGroup();
    _ss.sync();
}

long 	QPSTSystemPrivate::get_pstSystemTrapTargetTrapVersion(int index)
{

}

void	QPSTSystemPrivate::set_pstSystemTrapTargetTrapVersion(int index, long version)
{

}

long 	QPSTSystemPrivate::get_pstSystemTrapTargetRowStatus(int index)
{
}

void 	QPSTSystemPrivate::set_pstSystemTrapTargetRowStatus(int index, long status)
{
}
