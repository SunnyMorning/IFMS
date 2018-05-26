#include "qagentapp.h"
#include "qcommander.h"

static QMutex gCommander_mutex;

void QCommander::run()
{
        do{
            std::string     cmdline;
            QString         qcmdline;
            QStringList     qcmdlist;
            int             cmdcount;

            printf("\n[0x%x] IFMS[%d][%s]>#",  QThread::currentThreadId(),moduleIndex, link);
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
                else if(qcmdline.contains(QString("single"),Qt::CaseInsensitive))
                {
//                    emit sigModuleSingleMonitor(moduleIndex);
                    QAgentApp::getInstance()->onSigModuleSingleMonitor(moduleIndex);
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
                    qDebug() << " send " << qcmdline << endl;
//                    emit sigSendCommandToModule(moduleIndex,qcmdline);
                    QAgentApp::getInstance()->onSigSendCommandToModule(moduleIndex,qcmdline);

                }

            }

            QThread::msleep(500);
        }while(getKeepRunning() == 1);

        qDebug() << "\n Exit Expert mode...."<<endl;
    }


void QCommander::onSwitchModule(quint16 module)
{
     QMutexLocker locker(&gCommander_mutex);
     moduleIndex = module;
}

void QCommander::setKeepRunning(int running)
{
     QMutexLocker locker(&gCommander_mutex);
    _keeprunning = running;
}

int QCommander::getKeepRunning()
{
    QMutexLocker locker(&gCommander_mutex);
    return _keeprunning;
}
