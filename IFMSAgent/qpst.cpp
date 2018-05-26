#include "qpst.h"

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
void QPST::initConnections()
{
    connect(this, SIGNAL(sigOTDRChanged(quint16,quint16)), this, SLOT(onSigOTDRChanged(quint16,quint16)), Qt::DirectConnection);
    connect(this, SIGNAL(sigOTDRTrap(quint16,QByteArray&)), this, SLOT(onSigOTDRTrap(quint16,QByteArray&)), Qt::DirectConnection);
    connect(this, SIGNAL(sigSetProgress(quint16,quint16)), this, SLOT(onSigSetProgress(quint16,quint16)));
}


// Trap
int
QPST::send_pstIFMS1000MeasureEvent_trap( void )
{

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
        ASN_INTEGER,
        /* Set an appropriate value for pstIFMS1000MeasureStatus */
        &modstatus, sizeof(modstatus));

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
    return SNMP_ERR_NOERROR;
}


void QPST::onSigOTDRChanged(quint16 module, quint16 channel)
{

}

void QPST::onSigOTDRTrap(quint16 module, QByteArray &data)
{
// TODO: send trap to nms

    QPST::send_pstIFMS1000MeasureEvent_trap();

    qDebug() << "["<<QThread::currentThreadId() << "] onSigOTDRTrap" << endl;
}

void QPST::onSigSetProgress(quint16 module, quint16 progress)
{
    m_product->setModuleMeasuringProgess(module, progress);
}
