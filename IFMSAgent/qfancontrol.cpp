#include "qfancontrol.h"
#include "qpst.h"

#include <QMutex>
#include <QObject>
#include <QMutexLocker>
#include <QProcess>
#include <QDateTime>
#include <QTextStream>
#include <QIODevice>

static QMutex g_fanMutex;

QFanControl::QFanControl(QObject *parent) : QThread(parent)
{
    QPST *pst = QPST::getInstance();
    fan1ControlMode =  2;  // AUTO
    fan2ControlMode = 2;
    temperatureHigh = pst->m_system->m_pstSystem.get_pstSystemTemperatureHighThreshold().toInt();
    temperatureLow = pst->m_system->m_pstSystem.get_pstSystemTemperatureLowThreshold().toInt();

}

void QFanControl::run()
{
//    QDateTime  lasttime = QDateTime::currentDateTimeUtc();

    do{
        int    currentTemperature = get_Temperature();
        emit sigTemperatureChanged(currentTemperature);

        if(get_FanControlMode(1) == 2){ // AUTO
            if(currentTemperature > get_TemperatureHighThreshold()){
                set_FanTargetSpeed(1, MAX_TARGET_SPEED);
            }
            else if(get_TemperatureLowThreshold() < currentTemperature <= get_TemperatureHighThreshold())
            {
                   int target = (currentTemperature - DEFAULT_LOW_TEMPERATURE)* MAX_TARGET_SPEED/(temperatureHigh - temperatureLow);
                   set_FanTargetSpeed(1, target);
            }
            else
            {
                set_FanTargetSpeed(1,0);
            }
        }

        if(get_FanControlMode(2) == 2){ // AUTOa
            if(currentTemperature > get_TemperatureHighThreshold()){
                set_FanTargetSpeed(2, MAX_TARGET_SPEED);
            }
            else if(get_TemperatureLowThreshold() < currentTemperature <= get_TemperatureHighThreshold())
            {
                int target = (currentTemperature - DEFAULT_LOW_TEMPERATURE)* MAX_TARGET_SPEED/(temperatureHigh - temperatureLow);
                set_FanTargetSpeed(2, target);
            }
            else
            {
                set_FanTargetSpeed(2,0);
            }
        }
        QThread::msleep(2000);
    }while(true);
}

void QFanControl::set_FanTargetSpeed(int index, int t)
{
    QMutexLocker locker(&g_fanMutex);

    QFile file1("/sys/class/hwmon/hwmon1/fan1_target");
        if(file1.open(QIODevice::WriteOnly | QIODevice::Text)){
            QTextStream in(&file1);
            QString toWrite = QString("%1").arg(t);
            in << toWrite;
            file1.close();
        }

     QFile file2("/sys/class/hwmon/hwmon2/fan1_target");
     if(file2.open(QIODevice::WriteOnly | QIODevice::Text)){
                QTextStream in(&file2);
                QString toWrite = QString("%1").arg(t);
                in << toWrite;
                file2.close();
     }

}

int  QFanControl::get_FanControlMode(int index)
{
    QMutexLocker locker(&g_fanMutex);
    int t = 0;

    QFile   fanControlModeFile;
    if(index < 3 ){
       fanControlModeFile.setFileName("/sys/class/hwmon/hwmon1/pwm1_enable");
    }
    else
    {
        fanControlModeFile.setFileName("/sys/class/hwmon/hwmon2/pwm1_enable");
    }

    if(fanControlModeFile.open((QIODevice::ReadOnly | QIODevice::Text))){
        t = fanControlModeFile.readAll().trimmed().toInt();
    }

    if(index < 3){
        if( t == 0){
            fan1ControlMode = 1;
        }
        else if( t == 2){
            fan1ControlMode = 2;
        }

        return fan1ControlMode;
    }
    else
    {
        if( t == 0){
            fan2ControlMode = 1;
        }
        else if( t == 2){
            fan2ControlMode = 2;
        }

        return fan2ControlMode;
    }

    return 0;
}

void QFanControl::set_FanControlMode(int mode)
{
    QMutexLocker locker(&g_fanMutex);
    fan1ControlMode = mode;
    fan2ControlMode = mode;
    if(fan1ControlMode == 1){
        QFile file1("/sys/class/hwmon/hwmon1/pwm1_enable");
        if(file1.open(QIODevice::WriteOnly | QIODevice::Text)){
            QTextStream in(&file1);
            QString toWrite = QString("%1").arg(0);
            in << toWrite;
            file1.close();
        }
    }
    else if(fan1ControlMode == 2){
        QFile file1("/sys/class/hwmon/hwmon1/pwm1_enable");
        if(file1.open(QIODevice::WriteOnly | QIODevice::Text)){
            QTextStream in(&file1);
            QString toWrite = QString("%1").arg(2);
            in << toWrite;
            file1.close();
        }
    }

    if(fan2ControlMode == 1){
        QFile file2("/sys/class/hwmon/hwmon2/pwm1_enable");
        if(file2.open(QIODevice::WriteOnly | QIODevice::Text)){
            QTextStream in(&file2);
            QString toWrite = QString("%1").arg(0);
            in << toWrite;
            file2.close();
        }

    }
    else if(fan2ControlMode == 2){
        QFile file2("/sys/class/hwmon/hwmon2/pwm1_enable");
        if(file2.open(QIODevice::WriteOnly | QIODevice::Text)){
            QTextStream in(&file2);
            QString toWrite = QString("%1").arg(2);
            in << toWrite;
            file2.close();
        }
    }
}

int  QFanControl::get_Temperature()
{
    QFile   temperatureFile("/sys/class/hwmon/hwmon0/temp1_input");
    int t = 90;

    if(temperatureFile.open((QIODevice::ReadOnly | QIODevice::Text))){
        t = temperatureFile.readAll().trimmed().toInt()/1000;
    }

    return t;
}

int  QFanControl::get_TemperatureHighThreshold()
{
    QMutexLocker locker(&g_fanMutex);
    return temperatureHigh;

}
void QFanControl::set_TemperatureHighThreshold(int t)
{
    QMutexLocker locker(&g_fanMutex);
    temperatureHigh  = t;

}

int  QFanControl::get_TemperatureLowThreshold()
{
    QMutexLocker locker(&g_fanMutex);
    return temperatureLow;
}

void QFanControl::set_TemperatureLowThreshold(int t)
{
    QMutexLocker locker(&g_fanMutex);
    if( t < temperatureHigh - 10){
        temperatureLow = t;
    }
    else
    {
        temperatureLow = temperatureHigh - 60;
    }
}

// SLOTS

void QFanControl::onFanControlMode(int t)
{
    set_FanControlMode(t);
}

void QFanControl::onFanSetHighTemperature(int t)
{
    set_TemperatureHighThreshold(t);
}

void QFanControl::onFanSetLowTemperature(int t)
{
    set_TemperatureLowThreshold(t);
}


