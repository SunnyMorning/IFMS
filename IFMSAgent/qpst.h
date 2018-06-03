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
    void TrapTargetsChanged();


    // Trap
    static int send_pstIFMS1000MeasureEvent_trap(QString data);

    void run();
private:
    QPST(QObject *agent = NULL);
    QPST(const QPST &);//禁止拷贝构造函数。
    QPST & operator=(const QPST &);//禁止赋值拷贝函数。

    QReadWriteLock internalMutex;//函数使用的读写锁
    QMap<QString, int>  _sinks;

    int         _keeprunning;

signals:
    void sigOTDRTrap(quint16 module, QString &data);
    void sigSetProgress(quint16 module, quint16 progress);
    void sigSendCommandToModule(quint16 module, QString &cmdline);
    void sigTrapTargetsChanged(void);


public slots:
    void onSigOTDRTrap(quint16 module, QString& data);
    void onSigSetProgress(quint16 module, quint16 progress);
    void onSigOTDRSetMode(quint16 module, quint16 mode);
    void onSigSetMeasuredCount(quint16 channel, quint32 count);
    void onSigSetMeasuringStatus(quint16 channel, quint32 status);
    void onTrapTargetsChanged(void);
};

#endif // QPST_H
