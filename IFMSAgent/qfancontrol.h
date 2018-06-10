#ifndef QFANCONTROL_H
#define QFANCONTROL_H

#include <QObject>
#include <QThread>
#include <QMutex>
#include <QMutexLocker>
#include <QFile>
#include <QSettings>
#include <QMap>

#define     MAX_TARGET_SPEED            9500
#define     DEFAULT_LOW_TEMPERATURE     10

class QFanControl : public QThread
{
    Q_OBJECT
public:
    explicit QFanControl(QObject *parent = 0);

    void run();
//    void get_FanSpeed(int index);
    void set_FanTargetSpeed(int index, int t);
    int  get_FanControlMode(int index);
    void set_FanControlMode(int mode);

    int  get_Temperature();
    int  get_TemperatureHighThreshold();
    void set_TemperatureHighThreshold(int t);

    int  get_TemperatureLowThreshold();
    void set_TemperatureLowThreshold(int t);

signals:
    void    sigTemperatureChanged(int t);

public slots:
    void    onFanControlMode(int t);
    void    onFanSetHighTemperature(int t);
    void    onFanSetLowTemperature(int t);

private:
    int     temperatureHigh;
    int     temperatureLow;
    int 	fan1ControlMode;
    int     fan2ControlMode;
    int     fan1Status;
    int     fan2Status;
 };

#endif // QFANCONTROL_H
