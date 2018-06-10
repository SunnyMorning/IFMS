#include "qpst.h"

#include <QProcess>

//#define  DEBUG_TRAP  1

static QMutex gPST_mutex;

QAtomicPointer<QPST> _instance;/*!<使用原子指针,默认初始化为0。*/

QPST::QPST(QObject *agent)
{
//    _agent = agent;
    m_product = new QPSTProduct(this);
    m_system  = new QPSTSystem(this);
    _keeprunning = 1;
}

QPST::~QPST()
{

}

QPST* QPST::getInstance()
{
    if(!_instance)//第一次检测
    {
        QMutexLocker locker(&gPST_mutex);//加互斥锁。

        if(!_instance)//第二次检测。
            _instance = new QPST();
    }

    return _instance;
}

void QPST::setKeepRunning(int running)
{
	QMutexLocker locker(&gPST_mutex);
	_keeprunning = running;
}

int QPST::getKeepRunning(){
	 QMutexLocker locker(&gPST_mutex);
	 return _keeprunning;
}

void QPST::initConnections()
{
   connect(this, SIGNAL(sigOTDRTrap(quint16,QString&)), this, SLOT(onSigOTDRTrap(quint16,QString&)));
   connect(this, SIGNAL(sigSetProgress(quint16,quint16)), this, SLOT(onSigSetProgress(quint16,quint16)));
   connect(this, SIGNAL(sigTrapTargetsChanged()), this, SLOT(onTrapTargetsChanged()));
   m_gpios.configureGPIO(GPIO_ADG_AD0,QString("out"));
   m_gpios.configureGPIO(GPIO_ADG_AD1,QString("out"));
   m_gpios.configureGPIO(GPIO_ADG_AD2,QString("out"));
   m_gpios.writeGPIO(GPIO_ADG_AD0,1);
   m_gpios.writeGPIO(GPIO_ADG_AD1,1);
   m_gpios.writeGPIO(GPIO_ADG_AD2,1);
   m_gpios.configureGPIO(GPIO_STA_ALARMH, QString("out"));
   m_gpios.configureGPIO(GPIO_STA_ALARML, QString("out"));
   m_gpios.configureGPIO(GPIO_FAN_ALARMH, QString("out"));
   m_gpios.configureGPIO(GPIO_FAN_ALARML, QString("out"));
   m_gpios.configureGPIO(GPIO_ALERT_1, QString("in"));
   m_gpios.configureGPIO(GPIO_ALERT_0, QString("in"));
}

void QPST::TrapTargetsChanged()
{
//    emit this->sigTrapTargetsChanged();
}

void QPST::onSigTemperatureChanged(int t)
{
    int currentTemperature=0;
    int highTemperature = 0;
    int fan1_status = 1;
    int fan2_status = 1;
//    QMutexLocker locker(&gPST_mutex);
    QString s = QString("%1").arg(t);
    currentTemperature = m_system->m_pstSystem.get_pstSystemTemperature().toInt();
    highTemperature = m_system->m_pstSystem.get_pstSystemTemperatureHighThreshold().toInt();

    fan1_status = m_system->m_pstSystem.get_pstSystemFanStatus(1);
    fan2_status = m_system->m_pstSystem.get_pstSystemFanStatus(2);

    if((fan1_status == 1)||(fan2_status == 1))
    {
        m_gpios.writeGPIO(GPIO_FAN_ALARMH, 1);
        m_gpios.writeGPIO(GPIO_FAN_ALARML, 0);
    }
    else
    {
        m_gpios.writeGPIO(GPIO_FAN_ALARMH, 0);
        m_gpios.writeGPIO(GPIO_FAN_ALARML, 1);
    }

    if(currentTemperature > highTemperature){
//        m_gpios.configureGPIO(GPIO_STA_ALARMH, QString("out"));
//        m_gpios.configureGPIO(GPIO_STA_ALARML, QString("out"));
        m_gpios.writeGPIO(GPIO_STA_ALARMH, 0);
        m_gpios.writeGPIO(GPIO_STA_ALARML, 1);
    }
    else
    {
//        m_gpios.configureGPIO(GPIO_STA_ALARMH, QString("out"));
//        m_gpios.configureGPIO(GPIO_STA_ALARML, QString("out"));
        m_gpios.writeGPIO(GPIO_STA_ALARMH, 1);
        m_gpios.writeGPIO(GPIO_STA_ALARML, 0);
    }

    m_system->m_pstSystem.set_pstSystemTemerature(s);
}

void QPST::onTrapTargetsChanged()
{
#ifdef DEBUG_TRAP
    char peername[256];
    char community[256];
//    QMutexLocker locker(&gPST_mutex);//加互斥锁。

    QString targetIP;
    QString targetCommunity;

//    snmpd_free_trapsinks();

    for(int i=0; i< NUMBER_OF_TRAPTARGETS;i++)
    {
        targetIP = m_system->m_pstSystem.get_pstSystemTrapTargetIpAddr(i);
        if(targetIP != QString("0.0.0.0")){
            strcpy(peername, targetIP.toLatin1().data());
            targetCommunity = m_system->m_pstSystem.get_pstSystemTrapTargetCommunity(i);
            strcpy(community, targetCommunity.toLatin1().data());
            create_trap_session(peername, 0, community, SNMP_VERSION_2c, SNMP_MSG_INFORM);
        }
    }
#endif
    qDebug() << "onTrapTargetsChanged!" << endl;
}

void QPST::run()
{
        qDebug() << "["<<QThread::currentThreadId() <<"] qpst running" << endl;

        netsnmp_enable_subagent();
        netsnmp_ds_set_string(NETSNMP_DS_APPLICATION_ID, NETSNMP_DS_AGENT_X_SOCKET,AGENTX_MASTER_SOCKET);

        snmp_disable_log();

        init_agent(SUB_AGENT);
        init_snmp(SUB_AGENT);

        m_product->init_pstIFMS1000();
        m_system->init_pstSystem();

        onTrapTargetsChanged();

        do{
            agent_check_and_process(1);
        }while(getKeepRunning() == 1);

        snmp_shutdown(SUB_AGENT);
        shutdown_agent();
}

void QPST::sendCommandToOTDRModule(quint16 channel, QString cmdline)
{
    quint16 module = (channel-1)/CHANNELS_PER_MODULE;
    emit this->sigSendCommandToModule(module, cmdline);
}


// Trap
int
QPST::send_pstIFMS1000MeasureEvent_trap(QString data)
{
#ifdef DEBUG_TRAP
     static long modstatus = 0;
//     netsnmp_session     _session;
//    netsnmp_session     *_ss;
//    char           *trap = NULL;

//    char peername[256];
//    char community[256];
//    strcpy(peername,"192.168.0.12:1622");
//    strcpy(community,"public");
//    init_snmp(QAgentApp::getAppName().toLatin1());
//     snmp_sess_init(&_session);
//    _session.paramName = peername;
//    _session.community = (u_char*)community;
//    _session.community_len = strlen(community);
//    _session.version = SNMP_VERSION_2c;
//    _ss = snmp_add(&_session, netsnmp_transport_open_client("snmptrap", _session.peername),NULL,NULL);

//    if(_ss == NULL){
//        snmp_sess_perror("snmptrap", &_session);
//    }
    //    const oid objid_sysuptime[]={1,3,6,1,2,1,1,3,0};
    //    const oid objid_snmptrap[]={1,3,6,1,6,3,1,1,4,1,0};
    //    const oid objid_enterprise[] = {1,3,6,1,4,1,48391};
    //    const oid pstIFMS1000MeasureEvent_oid[] = { 1,3,6,1,4,1,48391,3,5,5,1,0};
    ////    const oid pstIFMS1000MeasureStatus_oid[] = { 1,3,6,1,4,1,48391,3,5,2,1,6,0 /* insert index here */ };


    //    long    sysuptime;
    //    char    csysuptime[20];

    netsnmp_variable_list  *var_list = NULL;
    const oid snmptrap_oid[]={1,3,6,1,6,3,1,1,4,1,0};
    const oid pstIFMS1000MeasureEvent_oid[] = { 1,3,6,1,4,1,48391,3,5,5,1 };
    const oid pstIFMS1000MeasureStatus_oid[] = { 1,3,6,1,4,1,48391,3,5,2,1,6,1 /* insert index here */ };

    /*
     * Set the snmpTrapOid.0 value
     */
    snmp_varlist_add_variable(&var_list,
        snmptrap_oid, OID_LENGTH(snmptrap_oid),
        ASN_OBJECT_ID,
        pstIFMS1000MeasureEvent_oid, sizeof(pstIFMS1000MeasureEvent_oid));

    /*
     * Add any objects from the trap definition
     */
    snmp_varlist_add_variable(&var_list,
        pstIFMS1000MeasureEvent_oid, OID_LENGTH(pstIFMS1000MeasureEvent_oid),
        ASN_OCTET_STR,
        /* Set an appropriate value for pstIFMS1000MeasureStatus */
        data.toLatin1().data(), data.length());

    /*
     * Add any extra (optional) objects here
     */
//    snmp_varlist_add_variable(&var_list,
//        pstIFMS1000MeasureStatus_oid, OID_LENGTH(pstIFMS1000MeasureStatus_oid),
//        ASN_INTEGER,
//        /* Set an appropriate value for pstIFMS1000MeasureStatus */
//        NULL, 0);


    /*
     * Send the trap to the list of configured destinations
     *  and clean up
     */
    send_v2trap( var_list );
    snmp_free_varbind( var_list );
//    snmpd_free_trapsinks();

#else
    QProcess *process;
    QString  targetIP;
    QString  targetCommunity;
    QString  trapCommand;
    QString  trapOID = QString("1.3.6.1.4.1.48391.3.5.5.1");
    QString  trapName = QString("pstIFMS1000MeasureEvent");
    QPST *pst = QPST::getInstance();

        for(int i=0; i< NUMBER_OF_TRAPTARGETS;i++)
        {
            targetIP = pst->m_system->m_pstSystem.get_pstSystemTrapTargetIpAddr(i+1);
            targetCommunity = pst->m_system->m_pstSystem.get_pstSystemTrapTargetCommunity(i+1);

            if((targetIP != QString("0.0.0.0")) && (!targetCommunity.isEmpty())){
//                process = new QProcess();
                trapCommand = QString("snmptrap -v 2c -c %1 %2 \"\" %3 %4 s \"%5\"").arg(targetCommunity).arg(\
                            targetIP).arg(trapOID).arg(trapName).arg(data);
//                process->start(trapCommand);
                qDebug() << qPrintable(trapCommand) << endl;
//                QProcess::execute(trapCommand);
                system(qPrintable(trapCommand));
            }
        }
#endif
    return SNMP_ERR_NOERROR;
}


//void QPST::onSigOTDRChanged(quint16 module, quint16 channel)
//{

//}

void QPST::onSigOTDRTrap(quint16 module, QString &data)
{
    qDebug() << "["<<QThread::currentThreadId() << "] onSigOTDRTrap" << endl;
    send_pstIFMS1000MeasureEvent_trap(data);
}

void QPST::onSigSetProgress(quint16 channel, quint16 progress)
{
    m_product->m_pstIFMS1000.set_pstIFMS1000MeasureProgressStatus(channel, progress);
}

void QPST::onSigOTDRSetMode(quint16 module, quint16 mode)
{
    int i = 0;
    quint16 channel = 1;
    for(i=0;i<CHANNELS_PER_MODULE;i++){
        channel = module*CHANNELS_PER_MODULE + i +1;
        m_product->m_pstIFMS1000.set_pstIFMS1000MeasureAction(channel, mode);
    }
}

void QPST::onSigSetMeasuredCount(quint16 channel, quint32 count)
{
    QString s = QString("%1").arg(count);
    m_product->m_pstIFMS1000.set_pstIFMS1000MeasureNumber(channel, s);
}

void QPST::onSigSetMeasuringStatus(quint16 channel, quint32 status)
{
    m_product->m_pstIFMS1000.set_pstIFMS1000MeasureStatus(channel, status);
}

void QPST::onSigOTDRUpdateStatus(quint16 module, int status)
{
    m_system->m_pstSystem.set_pstSystemUpgStatus(module+1, status);
}
