#ifndef QPSTSYSTEM_H
#define QPSTSYSTEM_H

#include <QObject>
#include <QMutex>
#include <QMutexLocker>

#include <stdbool.h>
#include <stdlib.h>
#include <net-snmp/net-snmp-config.h>
#include <net-snmp/net-snmp-features.h>
#include <net-snmp/net-snmp-includes.h>
#include <net-snmp/agent/net-snmp-agent-includes.h>
#include <net-snmp/agent/agent_handler.h>
#include <qagentapp.h>

static QMutex   mutex;
static long     reboot = 0;

class QPSTSystem : public QObject
{
    Q_OBJECT
public:
    explicit QPSTSystem(QObject *parent = 0);

    void init_pstObjects();

    static int   handle_reboot(netsnmp_mib_handler *handler, \
                          netsnmp_handler_registration *refinfo, \
                          netsnmp_agent_request_info   *reqinfo, \
                          netsnmp_request_info *requests);

signals:

public slots:

private:
    QAgentApp       *_agent;
};

#endif // QPSTSYSTEM_H
