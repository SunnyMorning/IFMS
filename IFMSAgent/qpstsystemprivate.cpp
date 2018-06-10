#include <QHostAddress>
#include <QHostInfo>
#include <QNetworkInterface>
#include <QProcess>
#include <QList>
#include <QFile>
#include <QDir>
#include <QIODevice>
#include <QDataStream>

#include "NetworkHelper.h"
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
    memset(&VerInfo, 0, sizeof(VerInfo));
    TrapInfo.pstSystemTrapFuncEn = 1;
    Status.DDRCleanUp = 0;
    Status.DDRConsumption = 20;
    Status.pstSystemADG707Switch = 1;
    Status.pstSystemTemperatureControlMode = 2;
    OnlineUpgrade.pstSystemUpgAction = 0;
    OnlineUpgrade.pstSystemUpgDstSlot = 1;
    OnlineUpgrade.pstSystemUpgStatus1 = 0;
    OnlineUpgrade.pstSystemUpgStatus2 = 0;
    strcpy(Status.pstSystemTemperatureHighThreshold,"55");
    strcpy(Status.pstSystemTemperatureLowThreshold,"-5");
}

QString QPSTSystemPrivate::get_devName()
{
    QString  s;

    _ss.beginGroup(SYSTEM_SETTINGS_GROUP);
    s = _ss.value("devName", "IFMS1000").toString();
    _ss.endGroup();

    return s;
}

void    QPSTSystemPrivate::set_devName(QString s)
{
    _ss.beginGroup(SYSTEM_SETTINGS_GROUP);
    _ss.setValue("devName", s);
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
        s = QString("0.0.0.0");
    }

    return s;
}

void    QPSTSystemPrivate::set_devIpAddr(QString s)
{
    _ss.beginGroup(SYSTEM_SETTINGS_GROUP);
    _ss.setValue("devIpAddr", s);
    _ss.endGroup();
    _ss.sync();
}

QString QPSTSystemPrivate::get_devGateway()
{
    QString  s = NetworkHelper::DefaultGateway();

    return s;
}

void    QPSTSystemPrivate::set_devGateway(QString s)
{
    _ss.beginGroup(SYSTEM_SETTINGS_GROUP);
    _ss.setValue("devGateway", s);
    _ss.endGroup();
    _ss.sync();
}

QString QPSTSystemPrivate::get_devNetMask()
{

}

void    QPSTSystemPrivate::set_devNetMask(QString s)
{
    _ss.beginGroup(SYSTEM_SETTINGS_GROUP);
    _ss.setValue("devNetMask", s);
    _ss.endGroup();
    _ss.sync();
}

long    QPSTSystemPrivate::get_saveCurrentConfiguration()
{
    return 0;
}

void    QPSTSystemPrivate::set_saveCurrentConfiguration(long s)
{
    QString ip;
    QString gw;
    QString msk;
    QString dns = QString("8.8.8.8");
    _ss.beginGroup(SYSTEM_SETTINGS_GROUP);
    ip = _ss.value("devIpAddr", QString("192.168.1.2")).toString();
    gw = _ss.value("devGateway", QString("192.168.1.1")).toString();
    msk = _ss.value("devNetMask", QString("255.255.255.0")).toString();
    _ss.endGroup();

    QString cmdline = QString("/usr/bin/writeip.sh -i eth1 -s %1:%2:%3:%4").arg(ip).arg(gw).arg(msk).arg(dns);
    QProcess::execute(cmdline);
}

long    QPSTSystemPrivate::get_reset2Factory()
{
    return 0;
}

void    QPSTSystemPrivate::set_reset2Factory(long s)
{
    // TODO: reset to factory
}

long    QPSTSystemPrivate::get_reboot()
{
    return 0;
}

void    QPSTSystemPrivate::set_reboot(long s)
{
    QProcess::execute("reboot");
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
    QString  ip = QString("0.0.0.0");
    _ss.beginGroup(SYSTEM_SETTINGS_GROUP);
    _ss.beginReadArray("pstSystemTrapTargetIpAddr");
    _ss.setArrayIndex(index-1);
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
            _ss.setArrayIndex(index-1);
            _ss.setValue("pstSystemTrapTargetIpAddr", s);
        _ss.endArray();
    _ss.endGroup();
    _ss.sync();
}

long 	QPSTSystemPrivate::get_pstSystemTrapTargetTrapVersion(int index)
{

}

void	QPSTSystemPrivate::set_pstSystemTrapTargetTrapVersion(int index, long s)
{

}

long 	QPSTSystemPrivate::get_pstSystemTrapTargetRowStatus(int index)
{
}

void 	QPSTSystemPrivate::set_pstSystemTrapTargetRowStatus(int index, long s)
{
}
    
QString QPSTSystemPrivate::get_pstHwVer()
{
}

QString QPSTSystemPrivate::get_pstSwVer()
{
}

QString QPSTSystemPrivate::get_pstFwVer()
{
}

QString QPSTSystemPrivate::get_pstModel()
{
}

QString QPSTSystemPrivate::get_pstSn()
{
    QString s = QString("201806010001");
    return s;
}

void QPSTSystemPrivate::set_pstSn(QString s)
{

}

QString QPSTSystemPrivate::get_devMacAddress()
{
    QString  s;
    QNetworkInterface a = QNetworkInterface::interfaceFromName("eth1");

    s = a.hardwareAddress();

    if(s.isEmpty()){
        s = QString("AA:BB:CC:DD:EE:FF");
    }

    return s;
}

long QPSTSystemPrivate::get_pstSystemTrapFuncEn()
{
    return TrapInfo.pstSystemTrapFuncEn;
}

void QPSTSystemPrivate::set_pstSystemTrapFuncEn(long s)
{
    TrapInfo.pstSystemTrapFuncEn = s;
}

long QPSTSystemPrivate::get_pstSystemTrapCount()
{
    return 2;
}   

long QPSTSystemPrivate::get_pstSystemFanTotalNum()
{
    return 4;
}

long QPSTSystemPrivate::get_pstSystemPowerTotalNum()
{
    return 8;
}

QString QPSTSystemPrivate::get_pstSystemTemperature()
{
    QString s = QString("%1").arg(Status.pstSystemTemperature);
    return s;
}

void QPSTSystemPrivate::set_pstSystemTemerature(QString s)
{
    strcpy(Status.pstSystemTemperature, s.toLatin1().data());
}

QString QPSTSystemPrivate::get_pstSystemTemperatureHighThreshold()
{
    QString s = QString("%1").arg(Status.pstSystemTemperatureHighThreshold);
    return s;
}

QString QPSTSystemPrivate::get_pstSystemTemperatureLowThreshold()
{
    QString s = QString("%1").arg(Status.pstSystemTemperatureLowThreshold);
    return s;
}

void QPSTSystemPrivate::set_pstSystemTemperatureHighThreshold(QString s)
{
    strcpy(Status.pstSystemTemperatureHighThreshold, s.toLatin1().data());
    int t = s.toInt();
}

void QPSTSystemPrivate::set_pstSystemTemperatureLowThreshold(QString s)
{
    strcpy(Status.pstSystemTemperatureLowThreshold, s.toLatin1().data());
    int t = s.toInt();
}

long QPSTSystemPrivate::get_pstSystemTemperatureControlMode(int index)
{
	return Status.pstSystemTemperatureControlMode;
}

void  QPSTSystemPrivate::set_pstSystemTemperatureControlMode(int index, long s)
{
	Status.pstSystemTemperatureControlMode = s;
}

long	QPSTSystemPrivate::get_pstSystemADG707Switch()
{
    long s = 0;
    QPST *pst = QPST::getInstance();

    if(pst->m_gpios.readGPIO(26) == 1){
        s |= 0x1;
    }
    if(pst->m_gpios.readGPIO(23) == 1){
        s |= 0x2;
    }
    if(pst->m_gpios.readGPIO(27) == 1){
        s |= 0x4;
    }

    return s;
}

void  QPSTSystemPrivate::set_pstSystemADG707Switch(long s)
{
    long t = 0;
    if(0< s <= 7){
        QPST *pst = QPST::getInstance();
//        pst->m_gpios.configureGPIO(26,QString("out"));
//        pst->m_gpios.configureGPIO(23,QString("out"));
//        pst->m_gpios.configureGPIO(27,QString("out"));
        t = s & 0x01;
        if(t != 0){
            pst->m_gpios.writeGPIO(GPIO_ADG_AD0, 1);
        }
        else{
            pst->m_gpios.writeGPIO(GPIO_ADG_AD0, 0);
        }

        t = s & 0x02;
        if(t != 0){
            pst->m_gpios.writeGPIO(GPIO_ADG_AD1, 1);
        }
        else{
            pst->m_gpios.writeGPIO(GPIO_ADG_AD1,0);
        }

        t = s & 0x04;
        if(t != 0){
            pst->m_gpios.writeGPIO(GPIO_ADG_AD2,1);
        }else
        {
            pst->m_gpios.writeGPIO(GPIO_ADG_AD2,0);
        }

    }
}

long	QPSTSystemPrivate::get_DDRConsumption()
{
	// TODO: get ddr comsumption
    QProcess    p;
    QString     s;
    int memoryAll = 256;
    int memoryFree = 200;
    int memoryPercent = 20;

    p.start("awk", QStringList() << "/MemTotal/ {print $2 }" << "/proc/meminfo");
    p.waitForFinished(1000);
    s = p.readAllStandardOutput();
    memoryAll = s.toLong();

    p.start("awk", QStringList() << "/MemFree/ {print $2 }" << "/proc/meminfo");
    p.waitForFinished();
    s = p.readAllStandardOutput();
    memoryFree = s.toLong();

    memoryPercent = 100*(memoryAll - memoryFree)/memoryAll;
    return memoryPercent;
}

long	QPSTSystemPrivate::get_DDRCleanUp()
{
	return 0;
}
void  QPSTSystemPrivate::set_DDRCleanUp(long s)
{
    QString path = QAgentApp::getCacheDir();
    QDir dir(path);
    dir.setNameFilters(QStringList() << "*.*");
    dir.setFilter(QDir::Files);
    foreach(QString dirFile, dir.entryList()){
        dir.remove(dirFile);
    }
}

QString QPSTSystemPrivate::get_pstSystemPowerMaximumConsumption(int index)
{
	// TODO: 45W
}

QString QPSTSystemPrivate::get_pstSystemPowerVoltage12VA(int index)
{
    QFile   file("/sys/bus/iio/devices/iio:device0/in_voltage1_raw");
    QString s;
    float t = 3200;

    if(file.open((QIODevice::ReadOnly | QIODevice::Text))){
        t = file.readAll().trimmed().toInt();
    }

    s = QString("%1").arg((float)t*1.8f*8.5f/4096);
    file.close();
    return s;
}

QString QPSTSystemPrivate::get_pstSystemPowerVoltage12VB(int index)
{
    QFile   file("/sys/bus/iio/devices/iio:device0/in_voltage0_raw");
    QString s;
    float t = 3200;

    if(file.open((QIODevice::ReadOnly | QIODevice::Text))){
        t = file.readAll().trimmed().toInt();
    }

    s = QString("%1").arg((float)t*1.8f*8.5f/4096);
    file.close();
    return s;
}             
QString QPSTSystemPrivate::get_pstSystemPowerVoltage12VFAN(int index)
{
    QFile   file("/sys/bus/iio/devices/iio:device0/in_voltage2_raw");
    QString s;
    float t = 3200;

    if(file.open((QIODevice::ReadOnly | QIODevice::Text))){
        t = file.readAll().trimmed().toInt();
    }

    s = QString("%1").arg((float)t*1.8f*8.5f/4096);
    file.close();
    return s;
}

QString QPSTSystemPrivate::get_pstSystemPowerVoltage12VOTDR1(int index)
{
    QFile   file("/sys/bus/iio/devices/iio:device0/in_voltage4_raw");
    QString s;
    float t = 3200;

    if(file.open((QIODevice::ReadOnly | QIODevice::Text))){
        t = file.readAll().trimmed().toInt();
    }

    s = QString("%1").arg((float)t*1.8f*8.5f/4096);
    file.close();
    return s;
}         
QString QPSTSystemPrivate::get_pstSystemPowerVoltage12VOTDR2(int index)
{
    QFile   file("/sys/bus/iio/devices/iio:device0/in_voltage3_raw");
    QString s;
    float t = 3200;

    if(file.open((QIODevice::ReadOnly | QIODevice::Text))){
        t = file.readAll().trimmed().toInt();
    }

    s = QString("%1").arg((float)t*1.8f*8.5f/4096);
    file.close();
    return s;
}         
QString QPSTSystemPrivate::get_pstSystemPowerVoltageVDD5V(int index)
{
    QFile   file("/sys/bus/iio/devices/iio:device0/in_voltage6_raw");
    QString s;
    float t = 3200;

    if(file.open((QIODevice::ReadOnly | QIODevice::Text))){
        t = file.readAll().trimmed().toInt();
    }

    s = QString("%1").arg((float)t*1.8f*6.99f/4096/2);
    file.close();
    return s;
}            
QString QPSTSystemPrivate::get_pstSystemPowerVoltageVDD3V3(int index)
{
    QFile   file("/sys/bus/iio/devices/iio:device0/in_voltage5_raw");
    QString s;
    float t = 3200;

    if(file.open((QIODevice::ReadOnly | QIODevice::Text))){
        t = file.readAll().trimmed().toInt();
    }

    s = QString("%1").arg((float)t*1.8f*18.2f/8.2f/4096);
    file.close();
    return s;
}           
QString QPSTSystemPrivate::get_pstSystemPowerVoltage1V8RTC(int index)
{
    QFile   file("/sys/bus/iio/devices/iio:device0/in_voltage7_raw");
    QString s;
    float t = 3200;

    if(file.open((QIODevice::ReadOnly | QIODevice::Text))){
        t = file.readAll().trimmed().toInt();
    }

    s = QString("%1").arg((float)t*1.8f*2.5f/2/4096);
    file.close();
    return s;
}           

long QPSTSystemPrivate::get_pstSystemFanStatus(long index)
{
    long status = 1;
    QPST *pst = QPST::getInstance();
    if(index < 3){
//        pst->m_gpios.configureGPIO(GPIO_ALERT_0, QString("in"));
        status = pst->m_gpios.readGPIO(GPIO_ALERT_0);
    }
    else
    {
//        pst->m_gpios.configureGPIO(GPIO_ALERT_1, QString("in"));
        status = pst->m_gpios.readGPIO(GPIO_ALERT_1);
    }

    return status;
}

long QPSTSystemPrivate::get_pstSystemFanSpeed(long index)
{
    QFile file;
    if(index < 3){
        file.setFileName("/sys/class/hwmon/hwmon1/pwm1");
    }
    else
    {
        file.setFileName("/sys/class/hwmon/hwmon2/pwm1");
    }
    long  s;
    int t = 67;

    if(file.open((QIODevice::ReadOnly | QIODevice::Text))){
        t = file.readAll().trimmed().toInt();
    }

    s = t*9500/255;
    file.close();
    return s;
}

QString QPSTSystemPrivate::get_pstSystemFtpSrvIp()
{
    return get_devIpAddr();
}
QString QPSTSystemPrivate::get_pstSystemFtpUserName()
{
    QString s = QString("%1").arg(OnlineUpgrade.pstSystemFtpUserName);
    return s;
}

QString QPSTSystemPrivate::get_pstSystemFtpUserPwd()
{
    QString s = QString("%1").arg(OnlineUpgrade.pstSystemFtpUserPwd);
    return s;
}
QString QPSTSystemPrivate::get_pstSystemFtpFileName()
{
    QString s = QAgentApp::getDataDir()+QString("firmware/CCU_FIRMWARE");
    return s;
}

long	  QPSTSystemPrivate::get_pstSystemUpgFileType()
{
}
long	  QPSTSystemPrivate::get_pstSystemUpgDstSlot()
{
    return OnlineUpgrade.pstSystemUpgDstSlot;
}

long	  QPSTSystemPrivate::get_pstSystemUpgAction()
{
    return OnlineUpgrade.pstSystemUpgAction;
}
void    QPSTSystemPrivate::set_pstSystemFtpSrvIp(QString s)
{
    strcpy(OnlineUpgrade.pstSystemFtpSrvIp, s.toLatin1().data());
}
void    QPSTSystemPrivate::set_pstSystemFtpUserName(QString s)
{
    strcpy(OnlineUpgrade.pstSystemFtpUserName, s.toLatin1().data());
}
void    QPSTSystemPrivate::set_pstSystemFtpUserPwd(QString s)
{
    strcpy(OnlineUpgrade.pstSystemFtpUserPwd, s.toLatin1().data());
}
void    QPSTSystemPrivate::set_pstSystemFtpFileName(QString s)
{
    strcpy(OnlineUpgrade.pstSystemFtpFileName, s.toLatin1().data());
}

void    QPSTSystemPrivate::set_pstSystemUpgFileType(long s)
{
    OnlineUpgrade.pstSystemUpgFileType = s;
}
void    QPSTSystemPrivate::set_pstSystemUpgDstSlot(long s)
{
    OnlineUpgrade.pstSystemUpgDstSlot = s;
}
void    QPSTSystemPrivate::set_pstSystemUpgAction(long s)
{
    OnlineUpgrade.pstSystemUpgAction = s;
    if( s == 2){
        quint16 module = 0;
        if(OnlineUpgrade.pstSystemUpgDstSlot > 0){
            module = OnlineUpgrade.pstSystemUpgDstSlot -1;
            emit QAgentApp::getInstance()->sigModuleUpdate(module);
        }
        else if(OnlineUpgrade.pstSystemUpgDstSlot  == 0)
        {
            // TODO: update system
        }
    }
}
    
long QPSTSystemPrivate::get_pstSystemUpgStatus(int slot)
{
    if(slot == 1){
        return OnlineUpgrade.pstSystemUpgStatus1;
    }
    else if(slot == 2)
    {
        return OnlineUpgrade.pstSystemUpgStatus2;
    }
}

void QPSTSystemPrivate::set_pstSystemUpgStatus(int slot, int status)
{
    if(slot == 1){
        OnlineUpgrade.pstSystemUpgStatus1 = status;
    }
    else if(slot == 2)
    {
        OnlineUpgrade.pstSystemUpgStatus2 = status;
    }
}

QString   QPSTSystemPrivate::get_pstSystemUpgResultInfo(int slot)
{
    QString s = QString("unknown");
    if(slot == 1){
        if(OnlineUpgrade.pstSystemUpgStatus1 == 0){
            s = QString("ready");
        }
        if(OnlineUpgrade.pstSystemUpgStatus1 == 1){
            s = QString("updating");
        }
        if(OnlineUpgrade.pstSystemUpgStatus1 == 2){
            s = QString("success");
        }
        if(OnlineUpgrade.pstSystemUpgStatus1 == 3){
            s = QString("failed");
        }
    }
    else if(slot == 2)
    {
        if(OnlineUpgrade.pstSystemUpgStatus2 == 0){
            s = QString("ready");
        }
        if(OnlineUpgrade.pstSystemUpgStatus2 == 1){
            s = QString("updating");
        }
        if(OnlineUpgrade.pstSystemUpgStatus2 == 2){
            s = QString("success");
        }
        if(OnlineUpgrade.pstSystemUpgStatus2 == 3){
            s = QString("failed");
        }
    }

    return s;
}

long 		  QPSTSystemPrivate::get_pstSystemProductType()
{
}    
