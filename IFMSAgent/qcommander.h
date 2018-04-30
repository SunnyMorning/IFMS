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

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <QString>
#include <QStringList>

#include "qagentapp.h"
#include "qsorfilebase.h"

class QCommander : public QRunnable, public QThread
{
//    Q_OBJECT
public:
    explicit QCommander(QAgentApp *agent = NULL, QObject *parent = NULL)
    {
        _agent = agent;
        moduleIndex = 0;
        _keeprunning = 1;
    }
    ~QCommander()
    {}

    int         moduleIndex;


    void run(){
        do{
            std::string     cmdline;
            QString         qcmdline;
            QStringList     qcmdlist;
            int             cmdcount;

            printf("IFMS[%d]>#",moduleIndex);
            std::getline(std::cin, cmdline);

            qcmdline = QString::fromStdString(cmdline);
            qcmdlist = qcmdline.split(" ", QString::SkipEmptyParts);

            cmdcount = qcmdlist.size();
            if(cmdcount < 1)
            {
                _agent->warning(QString("Please enter a command:"));
            }
            else
            {
                if(qcmdlist.contains(QString("module"), Qt::CaseInsensitive)){
                    if(qcmdlist.size() < 2){
                        _agent->warning(("Wrong module command format!"));
                    }
                    else
                    {
                        QString module = qcmdlist.at(1);
                        moduleIndex = module.toInt();
                    }
                }
                else if(qcmdlist.contains(QString("exit"), Qt::CaseInsensitive)){
                        _agent->exit(0);
                        _keeprunning = 0;
                }
                else if(qcmdlist.contains(QString("sor"), Qt::CaseInsensitive)){
//                        QSorFileBase    sorfile;
                        QString         filename = QAgentApp::getCacheDir()+QString("otdr_0000_160000_10000_CH3.sor");
                        QFile           readFile(filename);
                        if(!readFile.open(QIODevice::ReadOnly)){
                            qDebug() << "open " << filename << " error" << endl;
                        }
                        QByteArray blob = readFile.readAll();
                        qint16 channel = 2;
                        if(qcmdlist.size() == 2){
                            channel = ((QString)(qcmdlist.at(1))).toShort();
                        }
                        QString cmdline = QString("getsor? %1").arg(channel);
                         _agent->m_module2->onRecvResponse(cmdline, blob);

                         emit _agent->m_module1->sigRecvResponse(cmdline, blob);

//                        sorfile.parseData(blob.data(), blob.length());
//                        qDebug() << "read sor test" <<endl;

                }
                else
                {
                    _agent->sendCommandToModule(qcmdline,moduleIndex);

                }

            }

            QThread::msleep(500);
        }while(_keeprunning == 1);
    }

signals:

public slots:

private:
    QAgentApp   *_agent;
    int         _keeprunning;
};

#endif // QCOMMANDER_H
