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
    }
    ~QCommander()
    {}

    int     moduleIndex;

    void setKeepRunning(int running)
    {
         QMutexLocker locker(&gCommander_mutex);
        _keeprunning = running;
    }

    int getKeepRunning(){
         QMutexLocker locker(&gCommander_mutex);
         return _keeprunning;
    }

    void run(){
        do{
            std::string     cmdline;
            QString         qcmdline;
            QStringList     qcmdlist;
            int             cmdcount;

            printf("\n[0x%x] IFMS[%d]>#",  QThread::currentThreadId(),moduleIndex);
            std::getline(std::cin, cmdline);

            qcmdline = QString::fromStdString(cmdline);
            qcmdlist = qcmdline.split(" ", QString::SkipEmptyParts);

            cmdcount = qcmdlist.size();
            if(cmdcount < 1)
            {
                 printf("\n[0x%x] Please enter a command:", QThread::currentThreadId());
            }
            else
            {
                if(qcmdlist.contains(QString("module"), Qt::CaseInsensitive)){
                    if(qcmdlist.size() < 2){
                        printf("\nWrong module command format!\n");
                    }
                    else
                    {
                        QString module = qcmdlist.at(1);
                        moduleIndex = module.toInt();
                        emit sigSwitchModule(moduleIndex);
                    }
                }
                else if(qcmdlist.contains(QString("exit"), Qt::CaseInsensitive)){
                        emit sigExit(0);
                        _keeprunning = 0;
                }
                else if(qcmdline.contains(QString("idle"), Qt::CaseInsensitive))
                {
                     QByteArray blob = QByteArray(QString("STATE 0\r\n").toLatin1());
                     emit sigModuleRecvResponse(moduleIndex, qcmdline, blob);
                }
                else if(qcmdline.contains(QString("start"),Qt::CaseInsensitive))
                {
                    emit sigModuleStartMonitor(moduleIndex);
                }
                else if(qcmdline.contains(QString("stop"),Qt::CaseInsensitive))
                {
                    emit sigModuleStopMonitor(moduleIndex);
                }
#ifdef DEBUG_ON
                else if(qcmdlist.contains(QString("getsor?"), Qt::CaseInsensitive)){

                        QString         filename = QString("/home/dustin/.cache/ifms/otdr_0000_160000_10000_CH3.sor");
                        QFile           readFile(filename);
                        if(!readFile.open(QIODevice::ReadOnly)){
                             qDebug() << "\n open " << filename << " failed!\n";
                        }
                        QByteArray blob = readFile.readAll();
                        int len = blob.length();
                        char leng[4] ={0};
                        memcpy(leng, &len, sizeof(len));
                        QByteArray data(leng, 4);
                        data.append(blob);

                        qint16 channel = 2;
                        if(qcmdlist.size() == 2){
                            channel = ((QString)(qcmdlist.at(1))).toShort();
                        }
                        QString cmdline = QString("getsor? %1").arg(channel);
                        if(blob.size() > 4){
                            emit sigModuleRecvResponse(0, cmdline, data);
                            emit sigModuleRecvResponse(1, cmdline, data);
                        }
                }
#endif
                else
                {
                    emit sigSendCommandToModule(moduleIndex,qcmdline);

                }

            }

            QThread::msleep(500);
        }while(getKeepRunning() == 1);

        qDebug() << "\n Exit Expert mode...."<<endl;
    }

signals:
    void sigSendCommandToModule(quint16 module, QString& cmdline);
    void sigSwitchModule(quint16 module);
    void sigExit(qint32 num);
// for debug only
    void sigModuleRecvResponse(quint16 module ,QString& cmdline, QByteArray& data);
    void sigModuleStartMonitor(quint16 module);
    void sigModuleStopMonitor(quint16 module);
public slots:

private:
    int         _keeprunning;
};

#endif // QCOMMANDER_H
