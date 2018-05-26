#ifndef QPST_H
#define QPST_H

#include <QObject>
#include <QThread>
#include <QRunnable>
#include <QMutex>
#include <QMutexLocker>
#include <QDebug>
#include <QReadWriteLock>
#include <QAtomicPointer>
#include <QMap>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <vector>

#include "qpstproduct.h"
#include "qpstsystem.h"

#include <net-snmp/net-snmp-config.h>
#include <net-snmp/net-snmp-includes.h>
#include <net-snmp/net-snmp-features.h>
#include <net-snmp/agent/net-snmp-agent-includes.h>

#define  SUB_AGENT              "QPST"
#define  AGENTX_MASTER_SOCKET   "tcp:localhost:1705"

class QPST : public QThread
{
    Q_OBJECT
public:
    ~QPST();
    static QPST* getInstance(void);

    QPSTProduct *m_product;
    QPSTSystem  *m_system;
    void initConnections();

    void setKeepRunning(int running);
    int  getKeepRunning();

	void sendCommandToOTDRModule(quint16 channel, QString cmdline);

    // Trap
    static int send_pstIFMS1000MeasureEvent_trap(void);

    void run(){
        qDebug() << "["<<QThread::currentThreadId() <<"] qpst running" << endl;
        char peername[256];
        char community[256];
        strcpy(peername,"192.168.1.200:1622");
        strcpy(community,"public");


        netsnmp_enable_subagent();
        netsnmp_ds_set_string(NETSNMP_DS_APPLICATION_ID, NETSNMP_DS_AGENT_X_SOCKET,AGENTX_MASTER_SOCKET);

        snmp_disable_log();

        init_agent(SUB_AGENT);

        m_product->init_pstIFMS1000();
        m_system->init_pstSystem();

        init_snmp(SUB_AGENT);

        create_trap_session(peername, 0, community, SNMP_VERSION_2c, SNMP_MSG_INFORM);
//        _sinks.insert()

        do{
            agent_check_and_process(1);
        }while(getKeepRunning() == 1);

        snmp_shutdown(SUB_AGENT);
        shutdown_agent();
    }

private:
    QPST(QObject *agent = NULL);
    QPST(const QPST &);//禁止拷贝构造函数。
    QPST & operator=(const QPST &);//禁止赋值拷贝函数。

    QReadWriteLock internalMutex;//函数使用的读写锁
    QMap<QString, int>  _sinks;

    int         _keeprunning;

signals:
    void sigOTDRChanged(quint16 module, quint16 channel);
    void sigOTDRTrap(quint16 module, QByteArray &data);
    void sigSetProgress(quint16 module, quint16 progress);

	void sigSenCommandToModule(quint16 module, QString &cmdline);


public slots:
    void onSigOTDRChanged(quint16 module, quint16 channel);
    void onSigOTDRTrap(quint16 module, QByteArray& data);
    void onSigSetProgress(quint16 module, quint16 progress);
	
};

#endif // QPST_H
