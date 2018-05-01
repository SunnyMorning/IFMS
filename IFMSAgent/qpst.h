#ifndef QPST_H
#define QPST_H

#include <QObject>
#include <QThread>
#include <QRunnable>

#include <net-snmp/net-snmp-config.h>
#include <net-snmp/net-snmp-includes.h>
#include <net-snmp/net-snmp-features.h>
#include <net-snmp/agent/net-snmp-agent-includes.h>

#define  SUB_AGENT              "QPST"
#define  AGENTX_MASTER_SOCKET   "tcp:localhost:1705"

#include "qpstproduct.h"
#include "qpstsystem.h"

class QPST : public QRunnable, public QThread
{
//    Q_OBJECT
public:
    explicit QPST(QObject *agent = NULL)
    {
        _agent = agent;
        _product = new QPSTProduct(agent);
        _system  = new QPSTSystem(agent);
        _keeprunning = 1;
    }

    ~QPST(){

    }



    void run(){
        netsnmp_enable_subagent();
        netsnmp_ds_set_string(NETSNMP_DS_APPLICATION_ID, NETSNMP_DS_AGENT_X_SOCKET,AGENTX_MASTER_SOCKET);

        snmp_disable_log();

        init_agent(SUB_AGENT);

        _product->init_pstIFMS1000();
        _system->init_pstObjects();

        init_snmp(SUB_AGENT);


        do{
            agent_check_and_process(1);
        }while(_keeprunning == 1);

        snmp_shutdown(SUB_AGENT);
        shutdown_agent();
    }

private:
    QObject   *_agent;
    QPSTProduct *_product;
    QPSTSystem  *_system;
    int         _keeprunning;

signals:

public slots:
};

#endif // QPST_H
