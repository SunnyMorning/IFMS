#include <QHostAddress>
#include <QHostInfo>
#include <QNetworkInterface>
#include <QProcess>
#include <QList>
#include <QFile>
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
// TODO: store the IP to ini and wait savecfg
//    QProcess::execute("writeip.sh");
}

QString QPSTSystemPrivate::get_devGateway()
{
    QString  s = NetworkHelper::DefaultGateway();

    return s;
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

void    QPSTSystemPrivate::set_saveCurrentConfiguration(long s)
{

}

long    QPSTSystemPrivate::get_reset2Factory()
{

}

void    QPSTSystemPrivate::set_reset2Factory(long s)
{

}

long    QPSTSystemPrivate::get_reboot()
{
    return 0;
}

void    QPSTSystemPrivate::set_reboot(long s)
{
    QProcess::execute("shutdown -r -t 0");
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
}                     
long QPSTSystemPrivate::get_pstSystemPowerTotalNum()
{
}      
QString QPSTSystemPrivate::get_pstSystemTemperature()
{
    QFile   file("/sys/class/hwmon/hwmon0/temp1_input");
    QString s;
    int t = 10000;

    if(file.open((QIODevice::ReadOnly | QIODevice::Text))){
        t = file.readAll().trimmed().toInt();
    }

    s = QString("%1").arg((float)t/1000);
    return s;
}

QString QPSTSystemPrivate::get_pstSystemTemperatureHighThreshold()
{

}

QString QPSTSystemPrivate::get_pstSystemTemperatureLowThreshold()
{
}
void QPSTSystemPrivate::set_pstSystemTemperatureHighThreshold(QString s)
{
}               	  
void QPSTSystemPrivate::set_pstSystemTemperatureLowThreshold(QString s)
{
}    

QString QPSTSystemPrivate::get_pstSystemPowerMaximumConsumption(int index)
{
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
    return s;
}

QString QPSTSystemPrivate::get_pstSystemPowerVoltage12VB(int index)
{
}             
QString QPSTSystemPrivate::get_pstSystemPowerVoltage12VFAN(int index)
{
}           
QString QPSTSystemPrivate::get_pstSystemPowerVoltage12VOTDR1(int index)
{
}         
QString QPSTSystemPrivate::get_pstSystemPowerVoltage12VOTDR2(int index)
{
}         
QString QPSTSystemPrivate::get_pstSystemPowerVoltageVDD5V(int index)
{
}            
QString QPSTSystemPrivate::get_pstSystemPowerVoltageVDD3V3(int index)
{
}           
QString QPSTSystemPrivate::get_pstSystemPowerVoltage1V8RTC(int index)
{
}           

long QPSTSystemPrivate::get_pstSystemFanStatus(long index)
{
    // TODO: get the status
    return 0;
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
    return s;
}

QString QPSTSystemPrivate::get_pstSystemFtpSrvIp()
{
    return get_devIpAddr();
}
QString QPSTSystemPrivate::get_pstSystemFtpUserName()
{
}
QString QPSTSystemPrivate::get_pstSystemFtpUserPwd()
{
}
QString QPSTSystemPrivate::get_pstSystemFtpFileName()
{
}
long	  QPSTSystemPrivate::get_pstSystemUpgFileType()
{
}
long	  QPSTSystemPrivate::get_pstSystemUpgDstSlot()
{
}
long	  QPSTSystemPrivate::get_pstSystemUpgAction()
{
}
void    QPSTSystemPrivate::set_pstSystemFtpSrvIp(QString s)
{

}
void    QPSTSystemPrivate::set_pstSystemFtpUserName(QString s)
{
}
void    QPSTSystemPrivate::set_pstSystemFtpUserPwd(QString s)
{
}
void    QPSTSystemPrivate::set_pstSystemFtpFileName(QString s)
{
}
void    QPSTSystemPrivate::set_pstSystemUpgFileType(long s)
{
}
void    QPSTSystemPrivate::set_pstSystemUpgDstSlot(long s)
{
}
void    QPSTSystemPrivate::set_pstSystemUpgAction(long s)
{
}
    
long			QPSTSystemPrivate::get_pstSystemUpgStatus()
{
}
QString   QPSTSystemPrivate::get_pstSystemUpgResultInfo()
{
}
long 		  QPSTSystemPrivate::get_pstSystemProductType()
{
}    
