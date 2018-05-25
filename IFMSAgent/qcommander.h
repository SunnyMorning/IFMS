#ifndef QCOMMANDER_H
#define QCOMMANDER_H

#include <QObject>
#include <QRunnable>
#include <QThread>
#include <QFile>
#include <QDataStream>
#include <QString>
#include <QByteArray>
#include <QIODevice>
#include <QMutex>
#include <QMutexLocker>
#include <QDebug>

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <QString>
#include <QStringList>

#include "qsorfilebase.h"


static QMutex gCommander_mutex;

class QCommander : public QThread
{
    Q_OBJECT
public:
    explicit QCommander(QObject *parent = NULL)
    {
        moduleIndex = 0;
        _keeprunning = 1;
        link = "TCP";
    }
    ~QCommander()
    {}

    int     moduleIndex;
    char    *link;

    void setKeepRunning(int running)
    {
         QMutexLocker locker(&gCommander_mutex);
        _keeprunning = running;
    }

    int getKeepRunning(){
         QMutexLocker locker(&gCommander_mutex);
         return _keeprunning;
    }

    void run();

signals:
    void sigSendCommandToModule(quint16 module, QString cmdline);
    void sigSwitchModule(quint16 module);
    void sigExit(qint32 num);
// for debug only
    void sigModuleRecvResponse(quint16 module ,QString& cmdline, QByteArray& data);
    void sigModuleStartMonitor(quint16 module);
    void sigModuleStopMonitor(quint16 module);
    void sigModuleSingleMonitor(quint16 module);
public slots:

private:
    int         _keeprunning;
};

#endif // QCOMMANDER_H
