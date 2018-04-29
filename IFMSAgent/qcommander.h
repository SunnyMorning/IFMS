#ifndef QCOMMANDER_H
#define QCOMMANDER_H

#include <QObject>
#include <QRunnable>
#include <QThread>

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <QString>
#include <QStringList>

#include "qagentapp.h"

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
