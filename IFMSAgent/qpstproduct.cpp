#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <QObject>
#include <QMutex>
#include <QMutexLocker>
#include <QSettings>
#include <QString>

#include "qpstproduct.h"
#include "qagentapp.h"
#include "qpst.h"

netsnmp_feature_require(table_dataset)
netsnmp_feature_require(table_set_multi_add_default_row)

static QMutex PSTProduct_mutex;

QPSTProduct::QPSTProduct(QObject *parent) : QObject(parent)
{
    init_pstIFMS1000Data();
}

void QPSTProduct::init_pstIFMS1000Data()
{
    m_pstIFMS1000.init_pstData();
}

long QPSTProduct::get_pstIFMS1000SysLedPW1(QObject *agent){
    QPST *p = (QPST*)agent;
    return p->m_product->m_pstIFMS1000.get_pstIFMS1000SysLedPW1(agent);
}
long QPSTProduct::get_pstIFMS1000SysLedPW2(QObject *agent){
    QPST *p = (QPST*)agent;
    return p->m_product->m_pstIFMS1000.get_pstIFMS1000SysLedPW2(agent);
}
long QPSTProduct::get_pstIFMS1000SysLedStatus(QObject *agent){
    QPST *p = (QPST*)agent;
    return p->m_product->m_pstIFMS1000.get_pstIFMS1000SysLedStatus(agent);
}

void QPSTProduct::init_pstIFMS1000()
{
    const oid pstIFMS1000SysLedPW1_oid[] = { 1,3,6,1,4,1,48391,3,5,6,1,1 };
    const oid pstIFMS1000SysLedPW2_oid[] = { 1,3,6,1,4,1,48391,3,5,6,1,2 };
    const oid pstIFMS1000SysLedStatus_oid[] = { 1,3,6,1,4,1,48391,3,5,6,1,3 };
//    const oid pstIFMS1000BootMode_oid[] = { 1,3,6,1,4,1,48391,3,5,11,1 };
//    const oid pstIFMS1000SwitchModuleNum_oid[] = { 1,3,6,1,4,1,48391,3,5,17,1 };
//    const oid pstIFMS1000SwitchInterval_oid[] = { 1,3,6,1,4,1,48391,3,5,17,2 };
//    const oid pstIFMS1000SwitchCurrentPort_oid[] = { 1,3,6,1,4,1,48391,3,5,17,3 };
//    const oid pstIFMS1000ExtSwitchAttType_oid[] = { 1,3,6,1,4,1,48391,3,5,18,1 };
//    const oid pstIFMS1000ExtSwitchAttachPort_oid[] = { 1,3,6,1,4,1,48391,3,5,18,2 };
//    const oid pstIFMS1000ExtSwitchConnType_oid[] = { 1,3,6,1,4,1,48391,3,5,18,3 };
//    const oid pstIFMS1000ExtSwitchIpAddr_oid[] = { 1,3,6,1,4,1,48391,3,5,18,4 };
//    const oid pstIFMS1000ExtSwitchIpPort_oid[] = { 1,3,6,1,4,1,48391,3,5,18,5 };
//    const oid pstIFMS1000ExtSwitchUartBaud_oid[] = { 1,3,6,1,4,1,48391,3,5,18,6 };
//    const oid pstIFMS1000ExtSwitchTotalSwitchNum_oid[] = { 1,3,6,1,4,1,48391,3,5,18,7 };
//    const oid pstIFMS1000ExtSwitchCurrentNum_oid[] = { 1,3,6,1,4,1,48391,3,5,18,8 };
//    const oid pstIFMS1000ExtSwitchStatus_oid[] = { 1,3,6,1,4,1,48391,3,5,18,9 };

  DEBUGMSGTL(("pstIFMS1000", "Initializing\n"));

    netsnmp_register_scalar(
        netsnmp_create_handler_registration("pstIFMS1000SysLedPW1", handle_pstIFMS1000SysLedPW1,
                               pstIFMS1000SysLedPW1_oid, OID_LENGTH(pstIFMS1000SysLedPW1_oid),
                               HANDLER_CAN_RONLY
        ));
    netsnmp_register_scalar(
        netsnmp_create_handler_registration("pstIFMS1000SysLedPW2", handle_pstIFMS1000SysLedPW2,
                               pstIFMS1000SysLedPW2_oid, OID_LENGTH(pstIFMS1000SysLedPW2_oid),
                               HANDLER_CAN_RONLY
        ));
    netsnmp_register_scalar(
        netsnmp_create_handler_registration("pstIFMS1000SysLedStatus", handle_pstIFMS1000SysLedStatus,
                               pstIFMS1000SysLedStatus_oid, OID_LENGTH(pstIFMS1000SysLedStatus_oid),
                               HANDLER_CAN_RONLY
        ));
//    netsnmp_register_scalar(
//        netsnmp_create_handler_registration("pstIFMS1000BootMode", handle_pstIFMS1000BootMode,
//                               pstIFMS1000BootMode_oid, OID_LENGTH(pstIFMS1000BootMode_oid),
//                               HANDLER_CAN_RWRITE
//        ));
//    netsnmp_register_scalar(
//        netsnmp_create_handler_registration("pstIFMS1000SwitchModuleNum", handle_pstIFMS1000SwitchModuleNum,
//                               pstIFMS1000SwitchModuleNum_oid, OID_LENGTH(pstIFMS1000SwitchModuleNum_oid),
//                               HANDLER_CAN_RONLY
//        ));
//    netsnmp_register_scalar(
//        netsnmp_create_handler_registration("pstIFMS1000SwitchInterval", handle_pstIFMS1000SwitchInterval,
//                               pstIFMS1000SwitchInterval_oid, OID_LENGTH(pstIFMS1000SwitchInterval_oid),
//                               HANDLER_CAN_RWRITE
//        ));
//    netsnmp_register_scalar(
//        netsnmp_create_handler_registration("pstIFMS1000SwitchCurrentPort", handle_pstIFMS1000SwitchCurrentPort,
//                               pstIFMS1000SwitchCurrentPort_oid, OID_LENGTH(pstIFMS1000SwitchCurrentPort_oid),
//                               HANDLER_CAN_RONLY
//        ));
//    netsnmp_register_scalar(
//        netsnmp_create_handler_registration("pstIFMS1000ExtSwitchAttType", handle_pstIFMS1000ExtSwitchAttType,
//                               pstIFMS1000ExtSwitchAttType_oid, OID_LENGTH(pstIFMS1000ExtSwitchAttType_oid),
//                               HANDLER_CAN_RWRITE
//        ));
//    netsnmp_register_scalar(
//        netsnmp_create_handler_registration("pstIFMS1000ExtSwitchAttachPort", handle_pstIFMS1000ExtSwitchAttachPort,
//                               pstIFMS1000ExtSwitchAttachPort_oid, OID_LENGTH(pstIFMS1000ExtSwitchAttachPort_oid),
//                               HANDLER_CAN_RWRITE
//        ));
//    netsnmp_register_scalar(
//        netsnmp_create_handler_registration("pstIFMS1000ExtSwitchConnType", handle_pstIFMS1000ExtSwitchConnType,
//                               pstIFMS1000ExtSwitchConnType_oid, OID_LENGTH(pstIFMS1000ExtSwitchConnType_oid),
//                               HANDLER_CAN_RWRITE
//        ));
//    netsnmp_register_scalar(
//        netsnmp_create_handler_registration("pstIFMS1000ExtSwitchIpAddr", handle_pstIFMS1000ExtSwitchIpAddr,
//                               pstIFMS1000ExtSwitchIpAddr_oid, OID_LENGTH(pstIFMS1000ExtSwitchIpAddr_oid),
//                               HANDLER_CAN_RWRITE
//        ));
//    netsnmp_register_scalar(
//        netsnmp_create_handler_registration("pstIFMS1000ExtSwitchIpPort", handle_pstIFMS1000ExtSwitchIpPort,
//                               pstIFMS1000ExtSwitchIpPort_oid, OID_LENGTH(pstIFMS1000ExtSwitchIpPort_oid),
//                               HANDLER_CAN_RWRITE
//        ));
//    netsnmp_register_scalar(
//        netsnmp_create_handler_registration("pstIFMS1000ExtSwitchUartBaud", handle_pstIFMS1000ExtSwitchUartBaud,
//                               pstIFMS1000ExtSwitchUartBaud_oid, OID_LENGTH(pstIFMS1000ExtSwitchUartBaud_oid),
//                               HANDLER_CAN_RWRITE
//        ));
//    netsnmp_register_scalar(
//        netsnmp_create_handler_registration("pstIFMS1000ExtSwitchTotalSwitchNum", handle_pstIFMS1000ExtSwitchTotalSwitchNum,
//                               pstIFMS1000ExtSwitchTotalSwitchNum_oid, OID_LENGTH(pstIFMS1000ExtSwitchTotalSwitchNum_oid),
//                               HANDLER_CAN_RONLY
//        ));
//    netsnmp_register_scalar(
//        netsnmp_create_handler_registration("pstIFMS1000ExtSwitchCurrentNum", handle_pstIFMS1000ExtSwitchCurrentNum,
//                               pstIFMS1000ExtSwitchCurrentNum_oid, OID_LENGTH(pstIFMS1000ExtSwitchCurrentNum_oid),
//                               HANDLER_CAN_RONLY
//        ));
//    netsnmp_register_scalar(
//        netsnmp_create_handler_registration("pstIFMS1000ExtSwitchStatus", handle_pstIFMS1000ExtSwitchStatus,
//                               pstIFMS1000ExtSwitchStatus_oid, OID_LENGTH(pstIFMS1000ExtSwitchStatus_oid),
//                               HANDLER_CAN_RONLY
//        ));
        

  /* here we initialize all the tables we're planning on supporting */
    initialize_table_pstIFMS1000PortInfoTable();
    initialize_table_pstIFMS1000MeasureTable();
    initialize_table_pstIFMS1000FingerTable();
//    initialize_table_pstIFMS1000DiffTotalTable();
//    initialize_table_pstIFMS1000DiffInfoTable();
//    initialize_table_pstIFMS1000PortLedTable();
//    initialize_table_pstIFMS1000DiagnoseTable();
//    initialize_table_pstIFMS1000DebugRegTable();
//    initialize_table_pstIFMS1000DebugDACTable();
//    initialize_table_pstIFMS1000DebugE2promTable();
//    initialize_table_pstIFMS1000ExtendAlarmTable();
//    initialize_table_pstIFMS1000ExpertExtendTable();
//    initialize_table_pstIFMS1000PonConfTable();
//    initialize_table_pstIFMS1000ParamsV32TotalNumTable();
//    initialize_table_pstIFMS1000ParamsV32NameTable();
//    initialize_table_pstIFMS1000ParamsV32ValTable();
//    initialize_table_pstIFMS1000ParamsS32TotalNumTable();
//    initialize_table_pstIFMS1000ParamsS32NameTable();
//    initialize_table_pstIFMS1000ParamsS32ValTable();
}

// SCALAR
int QPSTProduct::handle_pstIFMS1000SysLedPW1(netsnmp_mib_handler *handler,
                                                               netsnmp_handler_registration *reginfo,
                                                               netsnmp_agent_request_info   *reqinfo,
                                                               netsnmp_request_info         *requests)
{
    /* We are never called for a GETNEXT if it's registered as a
       "instance", as it's "magically" handled for us.  */

    /* a instance handler also only hands us one request at a time, so
       we don't need to loop over a list of requests; we'll only get one. */

    long ledpw1 = get_pstIFMS1000SysLedPW1(QPST::getInstance());

    switch(reqinfo->mode) {

        case MODE_GET:
            snmp_set_var_typed_value(requests->requestvb, ASN_INTEGER,
                                     &ledpw1/* XXX: a pointer to the scalar's data */,
                                     sizeof(ledpw1)/* XXX: the length of the data in bytes */);
            break;


        default:
            /* we should never get here, so this is a really bad error */
            snmp_log(LOG_ERR, "unknown mode (%d) in handle_pstIFMS1000SysLedPW1\n", reqinfo->mode );
            return SNMP_ERR_GENERR;
    }

    return SNMP_ERR_NOERROR;
}

 int QPSTProduct::handle_pstIFMS1000SysLedPW2(netsnmp_mib_handler *handler,
                          netsnmp_handler_registration *reginfo,
                          netsnmp_agent_request_info   *reqinfo,
                          netsnmp_request_info         *requests)
{
    /* We are never called for a GETNEXT if it's registered as a
       "instance", as it's "magically" handled for us.  */

    /* a instance handler also only hands us one request at a time, so
       we don't need to loop over a list of requests; we'll only get one. */
    long ledpw2 = get_pstIFMS1000SysLedPW2(QPST::getInstance());
    
    switch(reqinfo->mode) {

        case MODE_GET:
            snmp_set_var_typed_value(requests->requestvb, ASN_INTEGER,
                                     &ledpw2/* XXX: a pointer to the scalar's data */,
                                     sizeof(ledpw2)/* XXX: the length of the data in bytes */);
            break;


        default:
            /* we should never get here, so this is a really bad error */
            snmp_log(LOG_ERR, "unknown mode (%d) in handle_pstIFMS1000SysLedPW2\n", reqinfo->mode );
            return SNMP_ERR_GENERR;
    }

    return SNMP_ERR_NOERROR;
}
 int QPSTProduct::handle_pstIFMS1000SysLedStatus(netsnmp_mib_handler *handler,
                          netsnmp_handler_registration *reginfo,
                          netsnmp_agent_request_info   *reqinfo,
                          netsnmp_request_info         *requests)
{
    /* We are never called for a GETNEXT if it's registered as a
       "instance", as it's "magically" handled for us.  */

    /* a instance handler also only hands us one request at a time, so
       we don't need to loop over a list of requests; we'll only get one. */
    long ledstatus = get_pstIFMS1000SysLedStatus(QPST::getInstance());

    switch(reqinfo->mode) {

        case MODE_GET:
            snmp_set_var_typed_value(requests->requestvb, ASN_INTEGER,
                                     &ledstatus/* XXX: a pointer to the scalar's data */,
                                     sizeof(ledstatus)/* XXX: the length of the data in bytes */);
            break;


        default:
            /* we should never get here, so this is a really bad error */
            snmp_log(LOG_ERR, "unknown mode (%d) in handle_pstIFMS1000SysLedStatus\n", reqinfo->mode );
            return SNMP_ERR_GENERR;
    }

    return SNMP_ERR_NOERROR;
}
#if 0
 int QPSTProduct::handle_pstIFMS1000BootMode(netsnmp_mib_handler *handler,
                          netsnmp_handler_registration *reginfo,
                          netsnmp_agent_request_info   *reqinfo,
                          netsnmp_request_info         *requests)
{
    int ret;
    /* We are never called for a GETNEXT if it's registered as a
       "instance", as it's "magically" handled for us.  */

    /* a instance handler also only hands us one request at a time, so
       we don't need to loop over a list of requests; we'll only get one. */

    static long bootmode = 0;
    
    switch(reqinfo->mode) {

        case MODE_GET:
            snmp_set_var_typed_value(requests->requestvb, ASN_INTEGER,
                                     &bootmode/* XXX: a pointer to the scalar's data */,
                                     sizeof(bootmode)/* XXX: the length of the data in bytes */);
            break;

        /*
         * SET REQUEST
         *
         * multiple states in the transaction.  See:
         * http://www.net-snmp.org/tutorial-5/toolkit/mib_module/set-actions.jpg
         */
        case MODE_SET_RESERVE1:
                /* or you could use netsnmp_check_vb_type_and_size instead */
            ret = netsnmp_check_vb_type(requests->requestvb, ASN_INTEGER);
            if ( ret != SNMP_ERR_NOERROR ) {
                netsnmp_set_request_error(reqinfo, requests, ret );
            }
            break;

        case MODE_SET_RESERVE2:
            /* XXX malloc "undo" storage buffer */
            if (0/* XXX if malloc, or whatever, failed: */) {
                netsnmp_set_request_error(reqinfo, requests, SNMP_ERR_RESOURCEUNAVAILABLE);
            }
            break;

        case MODE_SET_FREE:
            /* XXX: free resources allocated in RESERVE1 and/or
               RESERVE2.  Something failed somewhere, and the states
               below won't be called. */
            break;

        case MODE_SET_ACTION:
            /* XXX: perform the value change here */
            if (0/* XXX: error? */) {
                netsnmp_set_request_error(reqinfo, requests, 0/* some error */);
            }
            break;

        case MODE_SET_COMMIT:
            /* XXX: delete temporary storage */
            if (0/* XXX: error? */) {
                /* try _really_really_ hard to never get to this point */
                netsnmp_set_request_error(reqinfo, requests, SNMP_ERR_COMMITFAILED);
            }
            break;

        case MODE_SET_UNDO:
            /* XXX: UNDO and return to previous value for the object */
            if (0/* XXX: error? */) {
                /* try _really_really_ hard to never get to this point */
                netsnmp_set_request_error(reqinfo, requests, SNMP_ERR_UNDOFAILED);
            }
            break;

        default:
            /* we should never get here, so this is a really bad error */
            snmp_log(LOG_ERR, "unknown mode (%d) in handle_pstIFMS1000BootMode\n", reqinfo->mode );
            return SNMP_ERR_GENERR;
    }

    return SNMP_ERR_NOERROR;
}
 int QPSTProduct::handle_pstIFMS1000SwitchModuleNum(netsnmp_mib_handler *handler,
                          netsnmp_handler_registration *reginfo,
                          netsnmp_agent_request_info   *reqinfo,
                          netsnmp_request_info         *requests)
{
    /* We are never called for a GETNEXT if it's registered as a
       "instance", as it's "magically" handled for us.  */

    /* a instance handler also only hands us one request at a time, so
       we don't need to loop over a list of requests; we'll only get one. */

     static long swModuleNum = 0;
    
    switch(reqinfo->mode) {

        case MODE_GET:
            snmp_set_var_typed_value(requests->requestvb, ASN_INTEGER,
                                     &swModuleNum/* XXX: a pointer to the scalar's data */,
                                     sizeof(swModuleNum)/* XXX: the length of the data in bytes */);
            break;


        default:
            /* we should never get here, so this is a really bad error */
            snmp_log(LOG_ERR, "unknown mode (%d) in handle_pstIFMS1000SwitchModuleNum\n", reqinfo->mode );
            return SNMP_ERR_GENERR;
    }

    return SNMP_ERR_NOERROR;
}
 int QPSTProduct::handle_pstIFMS1000SwitchInterval(netsnmp_mib_handler *handler,
                          netsnmp_handler_registration *reginfo,
                          netsnmp_agent_request_info   *reqinfo,
                          netsnmp_request_info         *requests)
{
    int ret;
    /* We are never called for a GETNEXT if it's registered as a
       "instance", as it's "magically" handled for us.  */

    /* a instance handler also only hands us one request at a time, so
       we don't need to loop over a list of requests; we'll only get one. */
    static long interval  = 10;
    
    switch(reqinfo->mode) {

        case MODE_GET:
            snmp_set_var_typed_value(requests->requestvb, ASN_INTEGER,
                                     &interval/* XXX: a pointer to the scalar's data */,
                                     sizeof(interval)/* XXX: the length of the data in bytes */);
            break;

        /*
         * SET REQUEST
         *
         * multiple states in the transaction.  See:
         * http://www.net-snmp.org/tutorial-5/toolkit/mib_module/set-actions.jpg
         */
        case MODE_SET_RESERVE1:
                /* or you could use netsnmp_check_vb_type_and_size instead */
            ret = netsnmp_check_vb_type(requests->requestvb, ASN_INTEGER);
            if ( ret != SNMP_ERR_NOERROR ) {
                netsnmp_set_request_error(reqinfo, requests, ret );
            }
            break;

        case MODE_SET_RESERVE2:
            /* XXX malloc "undo" storage buffer */
            if (0/* XXX if malloc, or whatever, failed: */) {
                netsnmp_set_request_error(reqinfo, requests, SNMP_ERR_RESOURCEUNAVAILABLE);
            }
            break;

        case MODE_SET_FREE:
            /* XXX: free resources allocated in RESERVE1 and/or
               RESERVE2.  Something failed somewhere, and the states
               below won't be called. */
            break;

        case MODE_SET_ACTION:
            /* XXX: perform the value change here */
            if (0/* XXX: error? */) {
                netsnmp_set_request_error(reqinfo, requests, 0/* some error */);
            }
            break;

        case MODE_SET_COMMIT:
            /* XXX: delete temporary storage */
            if (0/* XXX: error? */) {
                /* try _really_really_ hard to never get to this point */
                netsnmp_set_request_error(reqinfo, requests, SNMP_ERR_COMMITFAILED);
            }
            break;

        case MODE_SET_UNDO:
            /* XXX: UNDO and return to previous value for the object */
            if (0/* XXX: error? */) {
                /* try _really_really_ hard to never get to this point */
                netsnmp_set_request_error(reqinfo, requests, SNMP_ERR_UNDOFAILED);
            }
            break;

        default:
            /* we should never get here, so this is a really bad error */
            snmp_log(LOG_ERR, "unknown mode (%d) in handle_pstIFMS1000SwitchInterval\n", reqinfo->mode );
            return SNMP_ERR_GENERR;
    }

    return SNMP_ERR_NOERROR;
}
 int QPSTProduct::handle_pstIFMS1000SwitchCurrentPort(netsnmp_mib_handler *handler,
                          netsnmp_handler_registration *reginfo,
                          netsnmp_agent_request_info   *reqinfo,
                          netsnmp_request_info         *requests)
{
    /* We are never called for a GETNEXT if it's registered as a
       "instance", as it's "magically" handled for us.  */

    /* a instance handler also only hands us one request at a time, so
       we don't need to loop over a list of requests; we'll only get one. */

    static long swCurrPort = 0;
    
    switch(reqinfo->mode) {

        case MODE_GET:
            snmp_set_var_typed_value(requests->requestvb, ASN_INTEGER,
                                     &swCurrPort/* XXX: a pointer to the scalar's data */,
                                     sizeof(swCurrPort)/* XXX: the length of the data in bytes */);
            break;


        default:
            /* we should never get here, so this is a really bad error */
            snmp_log(LOG_ERR, "unknown mode (%d) in handle_pstIFMS1000SwitchCurrentPort\n", reqinfo->mode );
            return SNMP_ERR_GENERR;
    }

    return SNMP_ERR_NOERROR;
}
 int QPSTProduct::handle_pstIFMS1000ExtSwitchAttType(netsnmp_mib_handler *handler,
                          netsnmp_handler_registration *reginfo,
                          netsnmp_agent_request_info   *reqinfo,
                          netsnmp_request_info         *requests)
{
    int ret;
    /* We are never called for a GETNEXT if it's registered as a
       "instance", as it's "magically" handled for us.  */

    /* a instance handler also only hands us one request at a time, so
       we don't need to loop over a list of requests; we'll only get one. */

    static long swAttType = 1;
    
    switch(reqinfo->mode) {

        case MODE_GET:
            snmp_set_var_typed_value(requests->requestvb, ASN_INTEGER,
                                     &swAttType/* XXX: a pointer to the scalar's data */,
                                     sizeof(swAttType)/* XXX: the length of the data in bytes */);
            break;

        /*
         * SET REQUEST
         *
         * multiple states in the transaction.  See:
         * http://www.net-snmp.org/tutorial-5/toolkit/mib_module/set-actions.jpg
         */
        case MODE_SET_RESERVE1:
                /* or you could use netsnmp_check_vb_type_and_size instead */
            ret = netsnmp_check_vb_type(requests->requestvb, ASN_INTEGER);
            if ( ret != SNMP_ERR_NOERROR ) {
                netsnmp_set_request_error(reqinfo, requests, ret );
            }
            break;

        case MODE_SET_RESERVE2:
            /* XXX malloc "undo" storage buffer */
            if (0/* XXX if malloc, or whatever, failed: */) {
                netsnmp_set_request_error(reqinfo, requests, SNMP_ERR_RESOURCEUNAVAILABLE);
            }
            break;

        case MODE_SET_FREE:
            /* XXX: free resources allocated in RESERVE1 and/or
               RESERVE2.  Something failed somewhere, and the states
               below won't be called. */
            break;

        case MODE_SET_ACTION:
            /* XXX: perform the value change here */
            if (0/* XXX: error? */) {
                netsnmp_set_request_error(reqinfo, requests, 0/* some error */);
            }
            break;

        case MODE_SET_COMMIT:
            /* XXX: delete temporary storage */
            if (0/* XXX: error? */) {
                /* try _really_really_ hard to never get to this point */
                netsnmp_set_request_error(reqinfo, requests, SNMP_ERR_COMMITFAILED);
            }
            break;

        case MODE_SET_UNDO:
            /* XXX: UNDO and return to previous value for the object */
            if (0/* XXX: error? */) {
                /* try _really_really_ hard to never get to this point */
                netsnmp_set_request_error(reqinfo, requests, SNMP_ERR_UNDOFAILED);
            }
            break;

        default:
            /* we should never get here, so this is a really bad error */
            snmp_log(LOG_ERR, "unknown mode (%d) in handle_pstIFMS1000ExtSwitchAttType\n", reqinfo->mode );
            return SNMP_ERR_GENERR;
    }

    return SNMP_ERR_NOERROR;
}
 int QPSTProduct::handle_pstIFMS1000ExtSwitchAttachPort(netsnmp_mib_handler *handler,
                          netsnmp_handler_registration *reginfo,
                          netsnmp_agent_request_info   *reqinfo,
                          netsnmp_request_info         *requests)
{
    int ret;
    /* We are never called for a GETNEXT if it's registered as a
       "instance", as it's "magically" handled for us.  */

    /* a instance handler also only hands us one request at a time, so
       we don't need to loop over a list of requests; we'll only get one. */

    static long swAttPort = 80;
    
    switch(reqinfo->mode) {

        case MODE_GET:
            snmp_set_var_typed_value(requests->requestvb, ASN_INTEGER,
                                     &swAttPort/* XXX: a pointer to the scalar's data */,
                                     sizeof(swAttPort)/* XXX: the length of the data in bytes */);
            break;

        /*
         * SET REQUEST
         *
         * multiple states in the transaction.  See:
         * http://www.net-snmp.org/tutorial-5/toolkit/mib_module/set-actions.jpg
         */
        case MODE_SET_RESERVE1:
                /* or you could use netsnmp_check_vb_type_and_size instead */
            ret = netsnmp_check_vb_type(requests->requestvb, ASN_INTEGER);
            if ( ret != SNMP_ERR_NOERROR ) {
                netsnmp_set_request_error(reqinfo, requests, ret );
            }
            break;

        case MODE_SET_RESERVE2:
            /* XXX malloc "undo" storage buffer */
            if (0/* XXX if malloc, or whatever, failed: */) {
                netsnmp_set_request_error(reqinfo, requests, SNMP_ERR_RESOURCEUNAVAILABLE);
            }
            break;

        case MODE_SET_FREE:
            /* XXX: free resources allocated in RESERVE1 and/or
               RESERVE2.  Something failed somewhere, and the states
               below won't be called. */
            break;

        case MODE_SET_ACTION:
            /* XXX: perform the value change here */
            if (0/* XXX: error? */) {
                netsnmp_set_request_error(reqinfo, requests, 0/* some error */);
            }
            break;

        case MODE_SET_COMMIT:
            /* XXX: delete temporary storage */
            if (0/* XXX: error? */) {
                /* try _really_really_ hard to never get to this point */
                netsnmp_set_request_error(reqinfo, requests, SNMP_ERR_COMMITFAILED);
            }
            break;

        case MODE_SET_UNDO:
            /* XXX: UNDO and return to previous value for the object */
            if (0/* XXX: error? */) {
                /* try _really_really_ hard to never get to this point */
                netsnmp_set_request_error(reqinfo, requests, SNMP_ERR_UNDOFAILED);
            }
            break;

        default:
            /* we should never get here, so this is a really bad error */
            snmp_log(LOG_ERR, "unknown mode (%d) in handle_pstIFMS1000ExtSwitchAttachPort\n", reqinfo->mode );
            return SNMP_ERR_GENERR;
    }

    return SNMP_ERR_NOERROR;
}
 int QPSTProduct::handle_pstIFMS1000ExtSwitchConnType(netsnmp_mib_handler *handler,
                          netsnmp_handler_registration *reginfo,
                          netsnmp_agent_request_info   *reqinfo,
                          netsnmp_request_info         *requests)
{
    int ret;
    /* We are never called for a GETNEXT if it's registered as a
       "instance", as it's "magically" handled for us.  */

    /* a instance handler also only hands us one request at a time, so
       we don't need to loop over a list of requests; we'll only get one. */
    
    static long swConnType = 1;

    switch(reqinfo->mode) {

        case MODE_GET:
            snmp_set_var_typed_value(requests->requestvb, ASN_INTEGER,
                                     &swConnType/* XXX: a pointer to the scalar's data */,
                                     sizeof(swConnType)/* XXX: the length of the data in bytes */);
            break;

        /*
         * SET REQUEST
         *
         * multiple states in the transaction.  See:
         * http://www.net-snmp.org/tutorial-5/toolkit/mib_module/set-actions.jpg
         */
        case MODE_SET_RESERVE1:
                /* or you could use netsnmp_check_vb_type_and_size instead */
            ret = netsnmp_check_vb_type(requests->requestvb, ASN_INTEGER);
            if ( ret != SNMP_ERR_NOERROR ) {
                netsnmp_set_request_error(reqinfo, requests, ret );
            }
            break;

        case MODE_SET_RESERVE2:
            /* XXX malloc "undo" storage buffer */
            if (0/* XXX if malloc, or whatever, failed: */) {
                netsnmp_set_request_error(reqinfo, requests, SNMP_ERR_RESOURCEUNAVAILABLE);
            }
            break;

        case MODE_SET_FREE:
            /* XXX: free resources allocated in RESERVE1 and/or
               RESERVE2.  Something failed somewhere, and the states
               below won't be called. */
            break;

        case MODE_SET_ACTION:
            /* XXX: perform the value change here */
            if (0/* XXX: error? */) {
                netsnmp_set_request_error(reqinfo, requests, 0/* some error */);
            }
            break;

        case MODE_SET_COMMIT:
            /* XXX: delete temporary storage */
            if (0/* XXX: error? */) {
                /* try _really_really_ hard to never get to this point */
                netsnmp_set_request_error(reqinfo, requests, SNMP_ERR_COMMITFAILED);
            }
            break;

        case MODE_SET_UNDO:
            /* XXX: UNDO and return to previous value for the object */
            if (0/* XXX: error? */) {
                /* try _really_really_ hard to never get to this point */
                netsnmp_set_request_error(reqinfo, requests, SNMP_ERR_UNDOFAILED);
            }
            break;

        default:
            /* we should never get here, so this is a really bad error */
            snmp_log(LOG_ERR, "unknown mode (%d) in handle_pstIFMS1000ExtSwitchConnType\n", reqinfo->mode );
            return SNMP_ERR_GENERR;
    }

    return SNMP_ERR_NOERROR;
}
 int QPSTProduct::handle_pstIFMS1000ExtSwitchIpAddr(netsnmp_mib_handler *handler,
                          netsnmp_handler_registration *reginfo,
                          netsnmp_agent_request_info   *reqinfo,
                          netsnmp_request_info         *requests)
{
    int ret;
    /* We are never called for a GETNEXT if it's registered as a
       "instance", as it's "magically" handled for us.  */

    /* a instance handler also only hands us one request at a time, so
       we don't need to loop over a list of requests; we'll only get one. */
    struct sockaddr_in sa;

    inet_pton(AF_INET, "192.168.1.1", &(sa.sin_addr));

    in_addr_t   it = sa.sin_addr.s_addr;
    
    switch(reqinfo->mode) {

        case MODE_GET:
            snmp_set_var_typed_value(requests->requestvb, ASN_IPADDRESS,
                                     &it/* XXX: a pointer to the scalar's data */,
                                     sizeof(it)/* XXX: the length of the data in bytes */);
            break;

        /*
         * SET REQUEST
         *
         * multiple states in the transaction.  See:
         * http://www.net-snmp.org/tutorial-5/toolkit/mib_module/set-actions.jpg
         */
        case MODE_SET_RESERVE1:
                /* or you could use netsnmp_check_vb_type_and_size instead */
            ret = netsnmp_check_vb_type(requests->requestvb, ASN_IPADDRESS);
            if ( ret != SNMP_ERR_NOERROR ) {
                netsnmp_set_request_error(reqinfo, requests, ret );
            }
            break;

        case MODE_SET_RESERVE2:
            /* XXX malloc "undo" storage buffer */
            if (0/* XXX if malloc, or whatever, failed: */) {
                netsnmp_set_request_error(reqinfo, requests, SNMP_ERR_RESOURCEUNAVAILABLE);
            }
            break;

        case MODE_SET_FREE:
            /* XXX: free resources allocated in RESERVE1 and/or
               RESERVE2.  Something failed somewhere, and the states
               below won't be called. */
            break;

        case MODE_SET_ACTION:
            /* XXX: perform the value change here */
            if (0/* XXX: error? */) {
                netsnmp_set_request_error(reqinfo, requests, 0/* some error */);
            }
            break;

        case MODE_SET_COMMIT:
            /* XXX: delete temporary storage */
            if (0/* XXX: error? */) {
                /* try _really_really_ hard to never get to this point */
                netsnmp_set_request_error(reqinfo, requests, SNMP_ERR_COMMITFAILED);
            }
            break;

        case MODE_SET_UNDO:
            /* XXX: UNDO and return to previous value for the object */
            if (0/* XXX: error? */) {
                /* try _really_really_ hard to never get to this point */
                netsnmp_set_request_error(reqinfo, requests, SNMP_ERR_UNDOFAILED);
            }
            break;

        default:
            /* we should never get here, so this is a really bad error */
            snmp_log(LOG_ERR, "unknown mode (%d) in handle_pstIFMS1000ExtSwitchIpAddr\n", reqinfo->mode );
            return SNMP_ERR_GENERR;
    }

    return SNMP_ERR_NOERROR;
}
 int QPSTProduct::handle_pstIFMS1000ExtSwitchIpPort(netsnmp_mib_handler *handler,
                          netsnmp_handler_registration *reginfo,
                          netsnmp_agent_request_info   *reqinfo,
                          netsnmp_request_info         *requests)
{
    int ret;
    /* We are never called for a GETNEXT if it's registered as a
       "instance", as it's "magically" handled for us.  */

    /* a instance handler also only hands us one request at a time, so
       we don't need to loop over a list of requests; we'll only get one. */

    static long swIpPort = 1611;
    
    switch(reqinfo->mode) {

        case MODE_GET:
            snmp_set_var_typed_value(requests->requestvb, ASN_INTEGER,
                                     &swIpPort/* XXX: a pointer to the scalar's data */,
                                     sizeof(swIpPort)/* XXX: the length of the data in bytes */);
            break;

        /*
         * SET REQUEST
         *
         * multiple states in the transaction.  See:
         * http://www.net-snmp.org/tutorial-5/toolkit/mib_module/set-actions.jpg
         */
        case MODE_SET_RESERVE1:
                /* or you could use netsnmp_check_vb_type_and_size instead */
            ret = netsnmp_check_vb_type(requests->requestvb, ASN_INTEGER);
            if ( ret != SNMP_ERR_NOERROR ) {
                netsnmp_set_request_error(reqinfo, requests, ret );
            }
            break;

        case MODE_SET_RESERVE2:
            /* XXX malloc "undo" storage buffer */
            if (0/* XXX if malloc, or whatever, failed: */) {
                netsnmp_set_request_error(reqinfo, requests, SNMP_ERR_RESOURCEUNAVAILABLE);
            }
            break;

        case MODE_SET_FREE:
            /* XXX: free resources allocated in RESERVE1 and/or
               RESERVE2.  Something failed somewhere, and the states
               below won't be called. */
            break;

        case MODE_SET_ACTION:
            /* XXX: perform the value change here */
            if (0/* XXX: error? */) {
                netsnmp_set_request_error(reqinfo, requests, 0/* some error */);
            }
            break;

        case MODE_SET_COMMIT:
            /* XXX: delete temporary storage */
            if (0/* XXX: error? */) {
                /* try _really_really_ hard to never get to this point */
                netsnmp_set_request_error(reqinfo, requests, SNMP_ERR_COMMITFAILED);
            }
            break;

        case MODE_SET_UNDO:
            /* XXX: UNDO and return to previous value for the object */
            if (0/* XXX: error? */) {
                /* try _really_really_ hard to never get to this point */
                netsnmp_set_request_error(reqinfo, requests, SNMP_ERR_UNDOFAILED);
            }
            break;

        default:
            /* we should never get here, so this is a really bad error */
            snmp_log(LOG_ERR, "unknown mode (%d) in handle_pstIFMS1000ExtSwitchIpPort\n", reqinfo->mode );
            return SNMP_ERR_GENERR;
    }

    return SNMP_ERR_NOERROR;
}
 int QPSTProduct::handle_pstIFMS1000ExtSwitchUartBaud(netsnmp_mib_handler *handler,
                          netsnmp_handler_registration *reginfo,
                          netsnmp_agent_request_info   *reqinfo,
                          netsnmp_request_info         *requests)
{
    int ret;
    /* We are never called for a GETNEXT if it's registered as a
       "instance", as it's "magically" handled for us.  */

    /* a instance handler also only hands us one request at a time, so
       we don't need to loop over a list of requests; we'll only get one. */

    static long swUartBd = 115200;
    
    switch(reqinfo->mode) {

        case MODE_GET:
            snmp_set_var_typed_value(requests->requestvb, ASN_INTEGER,
                                     &swUartBd/* XXX: a pointer to the scalar's data */,
                                     sizeof(swUartBd)/* XXX: the length of the data in bytes */);
            break;

        /*
         * SET REQUEST
         *
         * multiple states in the transaction.  See:
         * http://www.net-snmp.org/tutorial-5/toolkit/mib_module/set-actions.jpg
         */
        case MODE_SET_RESERVE1:
                /* or you could use netsnmp_check_vb_type_and_size instead */
            ret = netsnmp_check_vb_type(requests->requestvb, ASN_INTEGER);
            if ( ret != SNMP_ERR_NOERROR ) {
                netsnmp_set_request_error(reqinfo, requests, ret );
            }
            break;

        case MODE_SET_RESERVE2:
            /* XXX malloc "undo" storage buffer */
            if (0/* XXX if malloc, or whatever, failed: */) {
                netsnmp_set_request_error(reqinfo, requests, SNMP_ERR_RESOURCEUNAVAILABLE);
            }
            break;

        case MODE_SET_FREE:
            /* XXX: free resources allocated in RESERVE1 and/or
               RESERVE2.  Something failed somewhere, and the states
               below won't be called. */
            break;

        case MODE_SET_ACTION:
            /* XXX: perform the value change here */
            if (0/* XXX: error? */) {
                netsnmp_set_request_error(reqinfo, requests, 0/* some error */);
            }
            break;

        case MODE_SET_COMMIT:
            /* XXX: delete temporary storage */
            if (0/* XXX: error? */) {
                /* try _really_really_ hard to never get to this point */
                netsnmp_set_request_error(reqinfo, requests, SNMP_ERR_COMMITFAILED);
            }
            break;

        case MODE_SET_UNDO:
            /* XXX: UNDO and return to previous value for the object */
            if (0/* XXX: error? */) {
                /* try _really_really_ hard to never get to this point */
                netsnmp_set_request_error(reqinfo, requests, SNMP_ERR_UNDOFAILED);
            }
            break;

        default:
            /* we should never get here, so this is a really bad error */
            snmp_log(LOG_ERR, "unknown mode (%d) in handle_pstIFMS1000ExtSwitchUartBaud\n", reqinfo->mode );
            return SNMP_ERR_GENERR;
    }

    return SNMP_ERR_NOERROR;
}
 int QPSTProduct::handle_pstIFMS1000ExtSwitchTotalSwitchNum(netsnmp_mib_handler *handler,
                          netsnmp_handler_registration *reginfo,
                          netsnmp_agent_request_info   *reqinfo,
                          netsnmp_request_info         *requests)
{
    /* We are never called for a GETNEXT if it's registered as a
       "instance", as it's "magically" handled for us.  */

    /* a instance handler also only hands us one request at a time, so
       we don't need to loop over a list of requests; we'll only get one. */

     static long swTotalNum = 4;
    
    switch(reqinfo->mode) {

        case MODE_GET:
            snmp_set_var_typed_value(requests->requestvb, ASN_INTEGER,
                                     &swTotalNum/* XXX: a pointer to the scalar's data */,
                                     sizeof(swTotalNum)/* XXX: the length of the data in bytes */);
            break;


        default:
            /* we should never get here, so this is a really bad error */
            snmp_log(LOG_ERR, "unknown mode (%d) in handle_pstIFMS1000ExtSwitchTotalSwitchNum\n", reqinfo->mode );
            return SNMP_ERR_GENERR;
    }

    return SNMP_ERR_NOERROR;
}
 int QPSTProduct::handle_pstIFMS1000ExtSwitchCurrentNum(netsnmp_mib_handler *handler,
                          netsnmp_handler_registration *reginfo,
                          netsnmp_agent_request_info   *reqinfo,
                          netsnmp_request_info         *requests)
{
    /* We are never called for a GETNEXT if it's registered as a
       "instance", as it's "magically" handled for us.  */

    /* a instance handler also only hands us one request at a time, so
       we don't need to loop over a list of requests; we'll only get one. */

    static long swCurrNum = 0;
    
    switch(reqinfo->mode) {

        case MODE_GET:
            snmp_set_var_typed_value(requests->requestvb, ASN_INTEGER,
                                     &swCurrNum/* XXX: a pointer to the scalar's data */,
                                     sizeof(swCurrNum)/* XXX: the length of the data in bytes */);
            break;


        default:
            /* we should never get here, so this is a really bad error */
            snmp_log(LOG_ERR, "unknown mode (%d) in handle_pstIFMS1000ExtSwitchCurrentNum\n", reqinfo->mode );
            return SNMP_ERR_GENERR;
    }

    return SNMP_ERR_NOERROR;
}
 int QPSTProduct::handle_pstIFMS1000ExtSwitchStatus(netsnmp_mib_handler *handler,
                          netsnmp_handler_registration *reginfo,
                          netsnmp_agent_request_info   *reqinfo,
                          netsnmp_request_info         *requests)
{
    /* We are never called for a GETNEXT if it's registered as a
       "instance", as it's "magically" handled for us.  */

    /* a instance handler also only hands us one request at a time, so
       we don't need to loop over a list of requests; we'll only get one. */

     static long swStatus = 1;
    
    switch(reqinfo->mode) {

        case MODE_GET:
            snmp_set_var_typed_value(requests->requestvb, ASN_INTEGER,
                                     &swStatus/* XXX: a pointer to the scalar's data */,
                                     sizeof(swStatus)/* XXX: the length of the data in bytes */);
            break;


        default:
            /* we should never get here, so this is a really bad error */
            snmp_log(LOG_ERR, "unknown mode (%d) in handle_pstIFMS1000ExtSwitchStatus\n", reqinfo->mode );
            return SNMP_ERR_GENERR;
    }

    return SNMP_ERR_NOERROR;
}
#endif
 //    /* Typical data structure for a row entry */
 //struct pstIFMS1000PortInfoTable_entry {
 //    /* Index values */
 //    long pstIFMS1000PortNum;

 //    /* Column values */
 //    long pstIFMS1000PortNum;
 //    char pstIFMS1000PortRxPwr[NNN];
 //    size_t pstIFMS1000PortRxPwr_len;
 //    char pstIFMS1000PortTxPwr[NNN];
 //    size_t pstIFMS1000PortTxPwr_len;
 //    long pstIFMS1000PortWorkMode;
 //    long old_pstIFMS1000PortWorkMode;
 //    long pstIFMS1000PortActive;
 //    long old_pstIFMS1000PortActive;
 //    long pstIFMS1000PortFiberAppType;
 //    long old_pstIFMS1000PortFiberAppType;
 //    long pstIFMS1000PortRunningStatus;

 //    int   valid;
 //};

 /* create a new row in the table */
 static netsnmp_tdata_row *
 pstIFMS1000PortInfoTable_createEntry(netsnmp_tdata *table_data
                  , long  pstIFMS1000PortNum
                 ) {
     struct pstIFMS1000PortInfoTable_entry *entry;
     netsnmp_tdata_row *row;

     entry = SNMP_MALLOC_TYPEDEF(struct pstIFMS1000PortInfoTable_entry);
     if (!entry)
         return NULL;

     row = netsnmp_tdata_create_row();
     if (!row) {
         SNMP_FREE(entry);
         return NULL;
     }
     row->data = entry;

     DEBUGMSGT(("pstIFMS1000PortInfoTable:entry:create", "row 0x%x\n", (uintptr_t)row));
     entry->pstIFMS1000PortNum = pstIFMS1000PortNum;
     netsnmp_tdata_row_add_index( row, ASN_INTEGER,
                                  &(entry->pstIFMS1000PortNum),
                                  sizeof(entry->pstIFMS1000PortNum));
     if (table_data)
         netsnmp_tdata_add_row( table_data, row );
     return row;
 }

 /* remove a row from the table */
 static void
 pstIFMS1000PortInfoTable_removeEntry(netsnmp_tdata     *table_data,
                  netsnmp_tdata_row *row) {
     struct pstIFMS1000PortInfoTable_entry *entry;

     if (!row)
         return;    /* Nothing to remove */

     DEBUGMSGT(("pstIFMS1000PortInfoTable:entry:remove", "row 0x%x\n", (uintptr_t)row));

     entry = (struct pstIFMS1000PortInfoTable_entry *)row->data;
     SNMP_FREE( entry );   /* XXX - release any other internal resources */

     if (table_data)
         netsnmp_tdata_remove_and_delete_row( table_data, row );
     else
         netsnmp_tdata_delete_row( row );
 }

// Table
/** Initialize the pstIFMS1000PortInfoTable table by defining its contents and how it's structured */
void
QPSTProduct::initialize_table_pstIFMS1000PortInfoTable(void)
{
    const oid pstIFMS1000PortInfoTable_oid[] = {1,3,6,1,4,1,48391,3,5,1};
    const size_t pstIFMS1000PortInfoTable_oid_len   = OID_LENGTH(pstIFMS1000PortInfoTable_oid);
    netsnmp_handler_registration    *reg;
    netsnmp_tdata                   *table_data;
    netsnmp_table_registration_info *table_info;

    DEBUGMSGTL(("pstIFMS1000:init", "initializing table pstIFMS1000PortInfoTable\n"));

    reg = netsnmp_create_handler_registration(
              "pstIFMS1000PortInfoTable",     pstIFMS1000PortInfoTable_handler,
              pstIFMS1000PortInfoTable_oid, pstIFMS1000PortInfoTable_oid_len,
              HANDLER_CAN_RWRITE
              );

    table_data = netsnmp_tdata_create_table( "pstIFMS1000PortInfoTable", 0 );
    if (NULL == table_data) {
        snmp_log(LOG_ERR,"error creating tdata table for pstIFMS1000PortInfoTable\n");
        return;
    }
    table_info = SNMP_MALLOC_TYPEDEF( netsnmp_table_registration_info );
    if (NULL == table_info) {
        snmp_log(LOG_ERR,"error creating table info for pstIFMS1000PortInfoTable\n");
        return;
    }
    netsnmp_table_helper_add_indexes(table_info,
                           ASN_INTEGER,  /* index: pstIFMS1000PortNum */
                           0);

    table_info->min_column = COLUMN_PSTIFMS1000PORTNUM;
    table_info->max_column = COLUMN_PSTIFMS1000PORTRUNNINGSTATUS;
    
    netsnmp_tdata_register( reg, table_data, table_info );

    /* Initialise the contents of the table here */
    long i = 0;
    QPST *pst = QPST::getInstance();
    netsnmp_tdata_row 	*row;

    struct pstIFMS1000PortInfoTable_entry		*entry;
    QString s;
    for(i = 0; i < NUMBER_OF_CHANNES; i++){
        row = pstIFMS1000PortInfoTable_createEntry(table_data, i+1);
        entry = (struct pstIFMS1000PortInfoTable_entry *)row->data;
        entry->valid = 1;
        s = pst->m_product->m_pstIFMS1000.get_pstIFMS1000PortRxPwr(i+1);
        strcpy(entry->pstIFMS1000PortRxPwr, s.toLatin1().data());
        entry->pstIFMS1000PortRxPwr_len		= s.length();

        s = pst->m_product->m_pstIFMS1000.get_pstIFMS1000PortTxPwr(i+1);
        strcpy(entry->pstIFMS1000PortTxPwr, s.toLatin1().data());
        entry->pstIFMS1000PortTxPwr_len		= s.length();
        entry->pstIFMS1000PortWorkMode		= pst->m_product->m_pstIFMS1000.get_pstIFMS1000PortWorkMode(i+1);
        entry->pstIFMS1000PortActive 		= pst->m_product->m_pstIFMS1000.get_pstIFMS1000PortActive(i+1);
        entry->pstIFMS1000PortFiberAppType 	= pst->m_product->m_pstIFMS1000.get_pstIFMS1000PortFiberAppType(i+1);
        entry->pstIFMS1000PortRunningStatus	= pst->m_product->m_pstIFMS1000.get_pstIFMS1000PortRunningStatus(i+1);
    }

}

/** handles requests for the pstIFMS1000PortInfoTable table */
int
QPSTProduct::pstIFMS1000PortInfoTable_handler(
    netsnmp_mib_handler               *handler,
    netsnmp_handler_registration      *reginfo,
    netsnmp_agent_request_info        *reqinfo,
    netsnmp_request_info              *requests) {

    netsnmp_request_info       *request;
    netsnmp_table_request_info *table_info;
    netsnmp_tdata              *table_data;
    netsnmp_tdata_row          *table_row;
    struct pstIFMS1000PortInfoTable_entry          *table_entry;
    int                         ret;

    DEBUGMSGTL(("pstIFMS1000:handler", "Processing request (%d)\n", reqinfo->mode));

    switch (reqinfo->mode) {
        /*
         * Read-support (also covers GetNext requests)
         */
    case MODE_GET:
        for (request=requests; request; request=request->next) {
            if (request->processed)
                continue;

            table_entry = (struct pstIFMS1000PortInfoTable_entry *)
                              netsnmp_tdata_extract_entry(request);
            table_info  =     netsnmp_extract_table_info( request);
    
            switch (table_info->colnum) {
            case COLUMN_PSTIFMS1000PORTNUM:
                if ( !table_entry ) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_NOSUCHINSTANCE);
                    continue;
                }
                snmp_set_var_typed_integer( request->requestvb, ASN_INTEGER,
                                            table_entry->pstIFMS1000PortNum);
                break;
            case COLUMN_PSTIFMS1000PORTRXPWR:
                if ( !table_entry ) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_NOSUCHINSTANCE);
                    continue;
                }
                snmp_set_var_typed_value( request->requestvb, ASN_OCTET_STR,
                                          table_entry->pstIFMS1000PortRxPwr,
                                          table_entry->pstIFMS1000PortRxPwr_len);
                break;
            case COLUMN_PSTIFMS1000PORTTXPWR:
                if ( !table_entry ) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_NOSUCHINSTANCE);
                    continue;
                }
                snmp_set_var_typed_value( request->requestvb, ASN_OCTET_STR,
                                          table_entry->pstIFMS1000PortTxPwr,
                                          table_entry->pstIFMS1000PortTxPwr_len);
                break;
            case COLUMN_PSTIFMS1000PORTWORKMODE:
                if ( !table_entry ) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_NOSUCHINSTANCE);
                    continue;
                }
                snmp_set_var_typed_integer( request->requestvb, ASN_INTEGER,
                                            table_entry->pstIFMS1000PortWorkMode);
                break;
            case COLUMN_PSTIFMS1000PORTACTIVE:
            {
                if ( !table_entry ) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_NOSUCHINSTANCE);
                    continue;
                }

                long index = table_entry->pstIFMS1000PortNum;
                QPST *pst = QPST::getInstance();
                long active = pst->m_product->m_pstIFMS1000.get_pstIFMS1000PortActive(index);


                snmp_set_var_typed_integer( request->requestvb, ASN_INTEGER,
                                            active/*table_entry->pstIFMS1000PortActive*/);
            }
                break;
            case COLUMN_PSTIFMS1000PORTFIBERAPPTYPE:
            {
                if ( !table_entry ) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_NOSUCHINSTANCE);
                    continue;
                }

                long index = table_entry->pstIFMS1000PortNum;
                QPST *pst = QPST::getInstance();
                long type = pst->m_product->m_pstIFMS1000.get_pstIFMS1000PortFiberAppType(index);

                snmp_set_var_typed_integer( request->requestvb, ASN_INTEGER,
                                            type/*table_entry->pstIFMS1000PortFiberAppType*/);
            }
                break;
            case COLUMN_PSTIFMS1000PORTRUNNINGSTATUS:
                if ( !table_entry ) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_NOSUCHINSTANCE);
                    continue;
                }
                snmp_set_var_typed_integer( request->requestvb, ASN_INTEGER,
                                            table_entry->pstIFMS1000PortRunningStatus);
                break;
            default:
                netsnmp_set_request_error(reqinfo, request,
                                          SNMP_NOSUCHOBJECT);
                break;
            }
        }
        break;

        /*
         * Write-support
         */
    case MODE_SET_RESERVE1:
        for (request=requests; request; request=request->next) {
            if (request->processed)
                continue;

            table_entry = (struct pstIFMS1000PortInfoTable_entry *)
                              netsnmp_tdata_extract_entry(request);
            table_info  =     netsnmp_extract_table_info( request);
    
            switch (table_info->colnum) {
            case COLUMN_PSTIFMS1000PORTWORKMODE:
                /* or possibly 'netsnmp_check_vb_int_range' */
                ret = netsnmp_check_vb_int( request->requestvb );
                if ( ret != SNMP_ERR_NOERROR ) {
                    netsnmp_set_request_error( reqinfo, request, ret );
                    return SNMP_ERR_NOERROR;
                }
                break;
            case COLUMN_PSTIFMS1000PORTACTIVE:
                /* or possibly 'netsnmp_check_vb_int_range' */
            {
                ret = netsnmp_check_vb_int( request->requestvb );
                if ( ret != SNMP_ERR_NOERROR ) {
                    netsnmp_set_request_error( reqinfo, request, ret );
                    return SNMP_ERR_NOERROR;
                }

                long index = table_entry->pstIFMS1000PortNum;
                long active = *(request->requestvb->val.integer);
                QPST *pst = QPST::getInstance();

                pst->m_product->m_pstIFMS1000.set_pstIFMS1000PortActive(index,active);

            }
                break;
            case COLUMN_PSTIFMS1000PORTFIBERAPPTYPE:
                /* or possibly 'netsnmp_check_vb_int_range' */
            {
                ret = netsnmp_check_vb_int( request->requestvb );
                if ( ret != SNMP_ERR_NOERROR ) {
                    netsnmp_set_request_error( reqinfo, request, ret );
                    return SNMP_ERR_NOERROR;
                }
                long index = table_entry->pstIFMS1000PortNum;
                long type = *(request->requestvb->val.integer);
                QPST *pst = QPST::getInstance();

                pst->m_product->m_pstIFMS1000.set_pstIFMS1000PortFiberAppType(index,type);


            }
                break;
            default:
                netsnmp_set_request_error( reqinfo, request,
                                           SNMP_ERR_NOTWRITABLE );
                return SNMP_ERR_NOERROR;
            }
        }
        break;

    case MODE_SET_RESERVE2:
        break;

    case MODE_SET_FREE:
        break;

    case MODE_SET_ACTION:
        for (request=requests; request; request=request->next) {
            if (request->processed)
                continue;

            table_entry = (struct pstIFMS1000PortInfoTable_entry *)
                              netsnmp_tdata_extract_entry(request);
            table_info  =     netsnmp_extract_table_info( request);
    
            switch (table_info->colnum) {
            case COLUMN_PSTIFMS1000PORTWORKMODE:
                table_entry->old_pstIFMS1000PortWorkMode = table_entry->pstIFMS1000PortWorkMode;
                table_entry->pstIFMS1000PortWorkMode     = *request->requestvb->val.integer;
                break;
            case COLUMN_PSTIFMS1000PORTACTIVE:
                table_entry->old_pstIFMS1000PortActive = table_entry->pstIFMS1000PortActive;
                table_entry->pstIFMS1000PortActive     = *request->requestvb->val.integer;
                break;
            case COLUMN_PSTIFMS1000PORTFIBERAPPTYPE:
                table_entry->old_pstIFMS1000PortFiberAppType = table_entry->pstIFMS1000PortFiberAppType;
                table_entry->pstIFMS1000PortFiberAppType     = *request->requestvb->val.integer;
                break;
            }
        }
        break;

    case MODE_SET_UNDO:
        for (request=requests; request; request=request->next) {
            if (request->processed)
                continue;

            table_entry = (struct pstIFMS1000PortInfoTable_entry *)
                              netsnmp_tdata_extract_entry(request);
            table_row   =     netsnmp_tdata_extract_row(  request);
            table_data  =     netsnmp_tdata_extract_table(request);
            table_info  =     netsnmp_extract_table_info( request);
    
            switch (table_info->colnum) {
            case COLUMN_PSTIFMS1000PORTWORKMODE:
                table_entry->pstIFMS1000PortWorkMode     = table_entry->old_pstIFMS1000PortWorkMode;
                table_entry->old_pstIFMS1000PortWorkMode = 0;
                break;
            case COLUMN_PSTIFMS1000PORTACTIVE:
                table_entry->pstIFMS1000PortActive     = table_entry->old_pstIFMS1000PortActive;
                table_entry->old_pstIFMS1000PortActive = 0;
                break;
            case COLUMN_PSTIFMS1000PORTFIBERAPPTYPE:
                table_entry->pstIFMS1000PortFiberAppType     = table_entry->old_pstIFMS1000PortFiberAppType;
                table_entry->old_pstIFMS1000PortFiberAppType = 0;
                break;
            }
        }
        break;

    case MODE_SET_COMMIT:
        break;
    }
    return SNMP_ERR_NOERROR;
}
	
	//	  /* Typical data structure for a row entry */
	//struct pstIFMS1000MeasureTable_entry {
	//	  /* Index values */
	//	  long pstIFMS1000MTPortNum;
	
	//	  /* Column values */
	//	  long pstIFMS1000MTPortNum;
	//	  char pstIFMS1000MeasureStartPosition[NNN];
	//	  size_t pstIFMS1000MeasureStartPosition_len;
	//	  char old_pstIFMS1000MeasureStartPosition[NNN];
	//	  size_t old_pstIFMS1000MeasureStartPosition_len;
	//	  char pstIFMS1000MeasureEndPosition[NNN];
	//	  size_t pstIFMS1000MeasureEndPosition_len;
	//	  char old_pstIFMS1000MeasureEndPosition[NNN];
	//	  size_t old_pstIFMS1000MeasureEndPosition_len;
	//	  char pstIFMS1000MeasureRefIndex[NNN];
	//	  size_t pstIFMS1000MeasureRefIndex_len;
	//	  char old_pstIFMS1000MeasureRefIndex[NNN];
	//	  size_t old_pstIFMS1000MeasureRefIndex_len;
	//	  char pstIFMS1000MeasureResolution[NNN];
	//	  size_t pstIFMS1000MeasureResolution_len;
	//	  char old_pstIFMS1000MeasureResolution[NNN];
	//	  size_t old_pstIFMS1000MeasureResolution_len;
	//	  long pstIFMS1000MeasureStatus;
	//	  long pstIFMS1000MeasureAction;
	//	  long old_pstIFMS1000MeasureAction;
	//	  char pstIFMS1000MeasurePulseWidth[NNN];
	//	  size_t pstIFMS1000MeasurePulseWidth_len;
	//	  char old_pstIFMS1000MeasurePulseWidth[NNN];
	//	  size_t old_pstIFMS1000MeasurePulseWidth_len;
	//	  long pstIFMS1000MeasureTime;
	//	  long old_pstIFMS1000MeasureTime;
	//	  long pstIFMS1000MeasureProgressStatus;
	//	  char pstIFMS1000MeasureTLOS[NNN];
	//	  size_t pstIFMS1000MeasureTLOS_len;
	//	  char old_pstIFMS1000MeasureTLOS[NNN];
	//	  size_t old_pstIFMS1000MeasureTLOS_len;
	//	  char pstIFMS1000MeasureTREF[NNN];
	//	  size_t pstIFMS1000MeasureTREF_len;
	//	  char old_pstIFMS1000MeasureTREF[NNN];
	//	  size_t old_pstIFMS1000MeasureTREF_len;
	//	  char pstIFMS1000MeasureFiberLengthChangeThreshold[NNN];
	//	  size_t pstIFMS1000MeasureFiberLengthChangeThreshold_len;
	//	  char old_pstIFMS1000MeasureFiberLengthChangeThreshold[NNN];
	//	  size_t old_pstIFMS1000MeasureFiberLengthChangeThreshold_len;
	//	  char pstIFMS1000MeasureEndToEndLossCriticalThreshold[NNN];
	//	  size_t pstIFMS1000MeasureEndToEndLossCriticalThreshold_len;
	//	  char old_pstIFMS1000MeasureEndToEndLossCriticalThreshold[NNN];
	//	  size_t old_pstIFMS1000MeasureEndToEndLossCriticalThreshold_len;
	//	  char pstIFMS1000MeasureEndToEndLossMajorThreshold[NNN];
	//	  size_t pstIFMS1000MeasureEndToEndLossMajorThreshold_len;
	//	  char old_pstIFMS1000MeasureEndToEndLossMajorThreshold[NNN];
	//	  size_t old_pstIFMS1000MeasureEndToEndLossMajorThreshold_len;
	//	  char pstIFMS1000MeasureEndToEndLossMinorThreshold[NNN];
	//	  size_t pstIFMS1000MeasureEndToEndLossMinorThreshold_len;
	//	  char old_pstIFMS1000MeasureEndToEndLossMinorThreshold[NNN];
	//	  size_t old_pstIFMS1000MeasureEndToEndLossMinorThreshold_len;
	//	  char pstIFMS1000MeasureNewLossCriticalThreshold[NNN];
	//	  size_t pstIFMS1000MeasureNewLossCriticalThreshold_len;
	//	  char old_pstIFMS1000MeasureNewLossCriticalThreshold[NNN];
	//	  size_t old_pstIFMS1000MeasureNewLossCriticalThreshold_len;
	//	  char pstIFMS1000MeasureNewLossMajorThreshold[NNN];
	//	  size_t pstIFMS1000MeasureNewLossMajorThreshold_len;
	//	  char old_pstIFMS1000MeasureNewLossMajorThreshold[NNN];
	//	  size_t old_pstIFMS1000MeasureNewLossMajorThreshold_len;
	//	  char pstIFMS1000MeasureNewLossMinorThreshold[NNN];
	//	  size_t pstIFMS1000MeasureNewLossMinorThreshold_len;
	//	  char old_pstIFMS1000MeasureNewLossMinorThreshold[NNN];
	//	  size_t old_pstIFMS1000MeasureNewLossMinorThreshold_len;
	//	  char pstIFMS1000MeasureOldLossCriticalThreshold[NNN];
	//	  size_t pstIFMS1000MeasureOldLossCriticalThreshold_len;
	//	  char old_pstIFMS1000MeasureOldLossCriticalThreshold[NNN];
	//	  size_t old_pstIFMS1000MeasureOldLossCriticalThreshold_len;
	//	  char pstIFMS1000MeasureOldLossMajorThreshold[NNN];
	//	  size_t pstIFMS1000MeasureOldLossMajorThreshold_len;
	//	  char old_pstIFMS1000MeasureOldLossMajorThreshold[NNN];
	//	  size_t old_pstIFMS1000MeasureOldLossMajorThreshold_len;
	//	  char pstIFMS1000MeasureOldLossMinorThreshold[NNN];
	//	  size_t pstIFMS1000MeasureOldLossMinorThreshold_len;
	//	  char old_pstIFMS1000MeasureOldLossMinorThreshold[NNN];
	//	  size_t old_pstIFMS1000MeasureOldLossMinorThreshold_len;
	//	  char pstIFMS1000MeasureTempHighThreshold[NNN];
	//	  size_t pstIFMS1000MeasureTempHighThreshold_len;
	//	  char old_pstIFMS1000MeasureTempHighThreshold[NNN];
	//	  size_t old_pstIFMS1000MeasureTempHighThreshold_len;
	//	  char pstIFMS1000MeasureTempLowThreshold[NNN];
	//	  size_t pstIFMS1000MeasureTempLowThreshold_len;
	//	  char old_pstIFMS1000MeasureTempLowThreshold[NNN];
	//	  size_t old_pstIFMS1000MeasureTempLowThreshold_len;
	//	  char pstIFMS1000MeasureNumber[NNN];
	//	  size_t pstIFMS1000MeasureNumber_len;
	//	  char pstIFMS1000MeasureNumberSORStoredEachChannel[NNN];
	//	  size_t pstIFMS1000MeasureNumberSORStoredEachChannel_len;
	//	  char old_pstIFMS1000MeasureNumberSORStoredEachChannel[NNN];
	//	  size_t old_pstIFMS1000MeasureNumberSORStoredEachChannel_len;
	
	//	  int	valid;
	//};
	
	/* create a new row in the table */
	static netsnmp_tdata_row *
	pstIFMS1000MeasureTable_createEntry(netsnmp_tdata *table_data
					 , long  pstIFMS1000MTPortNum
					) {
		struct pstIFMS1000MeasureTable_entry *entry;
		netsnmp_tdata_row *row;
	
		entry = SNMP_MALLOC_TYPEDEF(struct pstIFMS1000MeasureTable_entry);
		if (!entry)
			return NULL;
	
		row = netsnmp_tdata_create_row();
		if (!row) {
			SNMP_FREE(entry);
			return NULL;
		}
		row->data = entry;
	
		DEBUGMSGT(("pstIFMS1000MeasureTable:entry:create", "row 0x%x\n", (uintptr_t)row));
		entry->pstIFMS1000MTPortNum = pstIFMS1000MTPortNum;
		netsnmp_tdata_row_add_index( row, ASN_INTEGER,
									 &(entry->pstIFMS1000MTPortNum),
									 sizeof(entry->pstIFMS1000MTPortNum));
		if (table_data)
			netsnmp_tdata_add_row( table_data, row );
		return row;
	}
	
	/* remove a row from the table */
	static void
	pstIFMS1000MeasureTable_removeEntry(netsnmp_tdata	  *table_data, 
					 netsnmp_tdata_row *row) {
		struct pstIFMS1000MeasureTable_entry *entry;
	
		if (!row)
			return;    /* Nothing to remove */
	
		DEBUGMSGT(("pstIFMS1000MeasureTable:entry:remove", "row 0x%x\n", (uintptr_t)row));
	
		entry = (struct pstIFMS1000MeasureTable_entry *)row->data;
		SNMP_FREE( entry );   /* XXX - release any other internal resources */
	
		if (table_data)
			netsnmp_tdata_remove_and_delete_row( table_data, row );
		else
			netsnmp_tdata_delete_row( row );	
	}
	

/** Initialize the pstIFMS1000MeasureTable table by defining its contents and how it's structured */
void
QPSTProduct::initialize_table_pstIFMS1000MeasureTable(void)
{
    const oid pstIFMS1000MeasureTable_oid[] = {1,3,6,1,4,1,48391,3,5,2};
    const size_t pstIFMS1000MeasureTable_oid_len   = OID_LENGTH(pstIFMS1000MeasureTable_oid);
    netsnmp_handler_registration    *reg;
    netsnmp_tdata                   *table_data;
    netsnmp_table_registration_info *table_info;

    DEBUGMSGTL(("pstIFMS1000:init", "initializing table pstIFMS1000MeasureTable\n"));

    reg = netsnmp_create_handler_registration(
              "pstIFMS1000MeasureTable",     pstIFMS1000MeasureTable_handler,
              pstIFMS1000MeasureTable_oid, pstIFMS1000MeasureTable_oid_len,
              HANDLER_CAN_RWRITE
              );

    table_data = netsnmp_tdata_create_table( "pstIFMS1000MeasureTable", 0 );
    if (NULL == table_data) {
        snmp_log(LOG_ERR,"error creating tdata table for pstIFMS1000MeasureTable\n");
        return;
    }
    table_info = SNMP_MALLOC_TYPEDEF( netsnmp_table_registration_info );
    if (NULL == table_info) {
        snmp_log(LOG_ERR,"error creating table info for pstIFMS1000MeasureTable\n");
        return;
    }
    netsnmp_table_helper_add_indexes(table_info,
                           ASN_INTEGER,  /* index: pstIFMS1000MTPortNum */
                           0);

    table_info->min_column = COLUMN_PSTIFMS1000MTPORTNUM;
    table_info->max_column = COLUMN_PSTIFMS1000MEASURENUMBERSORSTOREDEACHCHANNEL;
    
    netsnmp_tdata_register( reg, table_data, table_info );

    /* Initialise the contents of the table here */
	long i = 0;
	QPST *pst = QPST::getInstance();
	netsnmp_tdata_row 	*row;

    struct pstIFMS1000MeasureTable_entry		*entry;
    QString s;
	for(i = 0; i < NUMBER_OF_CHANNES; i++){
		row = pstIFMS1000MeasureTable_createEntry(table_data, i+1);
		entry = (struct pstIFMS1000MeasureTable_entry *)row->data;
		
			/* Column values */
        s = pst->m_product->m_pstIFMS1000.get_pstIFMS1000MeasureStartPosition(i+1);
        strcpy(entry->pstIFMS1000MeasureStartPosition, s.toLatin1().data());
        entry->pstIFMS1000MeasureStartPosition_len	= s.length();

        s = pst->m_product->m_pstIFMS1000.get_pstIFMS1000MeasureEndPosition(i+1);
        strcpy(entry->pstIFMS1000MeasureEndPosition, s.toLatin1().data());
        entry->pstIFMS1000MeasureEndPosition_len	= s.length();

        s = pst->m_product->m_pstIFMS1000.get_pstIFMS1000MeasureRefIndex(i+1);
        strcpy(entry->pstIFMS1000MeasureRefIndex, s.toLatin1().data());
        entry->pstIFMS1000MeasureRefIndex_len	= s.length();

        s = pst->m_product->m_pstIFMS1000.get_pstIFMS1000MeasureResolution(i+1);
        strcpy(entry->pstIFMS1000MeasureResolution, s.toLatin1().data());
        entry->pstIFMS1000MeasureResolution_len	= s.length();

        entry->pstIFMS1000MeasureStatus = pst->m_product->m_pstIFMS1000.get_pstIFMS1000MeasureStatus(i+1);
        entry->pstIFMS1000MeasureAction = pst->m_product->m_pstIFMS1000.get_pstIFMS1000MeasureAction(i+1);

        s = pst->m_product->m_pstIFMS1000.get_pstIFMS1000MeasurePulseWidth(i+1);
        strcpy(entry->pstIFMS1000MeasurePulseWidth, s.toLatin1().data());
        entry->pstIFMS1000MeasurePulseWidth_len	= s.length();
        entry->pstIFMS1000MeasureTime = pst->m_product->m_pstIFMS1000.get_pstIFMS1000MeasureTime(i+1);
        entry->pstIFMS1000MeasureProgressStatus = pst->m_product->m_pstIFMS1000.get_pstIFMS1000MeasureProgressStatus(i+1);

        s = pst->m_product->m_pstIFMS1000.get_pstIFMS1000MeasureTLOS(i+1);
        strcpy(entry->pstIFMS1000MeasureTLOS, s.toLatin1().data());
        entry->pstIFMS1000MeasureTLOS_len	= s.length();

        s = pst->m_product->m_pstIFMS1000.get_pstIFMS1000MeasureTREF(i+1);
        strcpy(entry->pstIFMS1000MeasureTREF, s.toLatin1().data());
        entry->pstIFMS1000MeasureTREF_len	= s.length();

        s = pst->m_product->m_pstIFMS1000.get_pstIFMS1000MeasureFiberLengthChangeThreshold(i+1);
        strcpy(entry->pstIFMS1000MeasureFiberLengthChangeThreshold, s.toLatin1().data());
        entry->pstIFMS1000MeasureFiberLengthChangeThreshold_len	= s.length();

        s = pst->m_product->m_pstIFMS1000.get_pstIFMS1000MeasureEndToEndLossHighThreshold(i+1);
        strcpy(entry->pstIFMS1000MeasureEndToEndLossHighThreshold, s.toLatin1().data());
        entry->pstIFMS1000MeasureEndToEndLossHighThreshold_len	= s.length();

        s = pst->m_product->m_pstIFMS1000.get_pstIFMS1000MeasureEndToEndLossMiddleThreshold(i+1);
        strcpy(entry->pstIFMS1000MeasureEndToEndLossMiddleThreshold, s.toLatin1().data());
        entry->pstIFMS1000MeasureEndToEndLossMiddleThreshold_len	= s.length();

        s = pst->m_product->m_pstIFMS1000.get_pstIFMS1000MeasureEndToEndLossLowThreshold(i+1);
        strcpy(entry->pstIFMS1000MeasureEndToEndLossLowThreshold, s.toLatin1().data());
        entry->pstIFMS1000MeasureEndToEndLossLowThreshold_len	= s.length();

        s = pst->m_product->m_pstIFMS1000.get_pstIFMS1000MeasureNewLossCriticalThreshold(i+1);
        strcpy(entry->pstIFMS1000MeasureNewLossCriticalThreshold, s.toLatin1().data());
        entry->pstIFMS1000MeasureNewLossCriticalThreshold_len	= s.length();

        s = pst->m_product->m_pstIFMS1000.get_pstIFMS1000MeasureNewLossMajorThreshold(i+1);
        strcpy(entry->pstIFMS1000MeasureNewLossMajorThreshold, s.toLatin1().data());
        entry->pstIFMS1000MeasureNewLossMajorThreshold_len	= s.length();

        s = pst->m_product->m_pstIFMS1000.get_pstIFMS1000MeasureNewLossMinorThreshold(i+1);
        strcpy(entry->pstIFMS1000MeasureNewLossMinorThreshold, s.toLatin1().data());
        entry->pstIFMS1000MeasureNewLossMinorThreshold_len	= s.length();

        s = pst->m_product->m_pstIFMS1000.get_pstIFMS1000MeasureOldLossCriticalThreshold(i+1);
        strcpy(entry->pstIFMS1000MeasureOldLossCriticalThreshold, s.toLatin1().data());
        entry->pstIFMS1000MeasureOldLossCriticalThreshold_len	= s.length();

        s = pst->m_product->m_pstIFMS1000.get_pstIFMS1000MeasureOldLossMajorThreshold(i+1);
        strcpy(entry->pstIFMS1000MeasureOldLossMajorThreshold, s.toLatin1().data());
        entry->pstIFMS1000MeasureOldLossMajorThreshold_len	= s.length();

        s = pst->m_product->m_pstIFMS1000.get_pstIFMS1000MeasureOldLossMinorThreshold(i+1);
        strcpy(entry->pstIFMS1000MeasureOldLossMinorThreshold, s.toLatin1().data());
        entry->pstIFMS1000MeasureOldLossMinorThreshold_len	= s.length();

        s = pst->m_product->m_pstIFMS1000.get_pstIFMS1000MeasureEventPositionChangeThreshold(i+1);
        strcpy(entry->pstIFMS1000MeasureEventPositionChangeThreshold, s.toLatin1().data());
        entry->pstIFMS1000MeasureEventPositionChangeThreshold_len	= s.length();

        s = pst->m_product->m_pstIFMS1000.get_pstIFMS1000MeasureReserved2(i+1);
        strcpy(entry->pstIFMS1000MeasureReserved2, s.toLatin1().data());
        entry->pstIFMS1000MeasureReserved2_len	= s.length();

        s = pst->m_product->m_pstIFMS1000.get_pstIFMS1000MeasureNumber(i+1);
        strcpy(entry->pstIFMS1000MeasureNumber, s.toLatin1().data());
        entry->pstIFMS1000MeasureNumber_len	= s.length();

        s = pst->m_product->m_pstIFMS1000.get_pstIFMS1000MeasureNumberSORStoredEachChannel(i+1);
        strcpy(entry->pstIFMS1000MeasureNumberSORStoredEachChannel, s.toLatin1().data());
        entry->pstIFMS1000MeasureNumberSORStoredEachChannel_len	= s.length();
		
		entry->valid = 1;
	}

}

/** handles requests for the pstIFMS1000MeasureTable table */
int
QPSTProduct::pstIFMS1000MeasureTable_handler(
    netsnmp_mib_handler               *handler,
    netsnmp_handler_registration      *reginfo,
    netsnmp_agent_request_info        *reqinfo,
    netsnmp_request_info              *requests) {

    netsnmp_request_info       *request;
    netsnmp_table_request_info *table_info;
    netsnmp_tdata              *table_data;
    netsnmp_tdata_row          *table_row;
    struct pstIFMS1000MeasureTable_entry          *table_entry;
    int                         ret;

    DEBUGMSGTL(("pstIFMS1000:handler", "Processing request (%d)\n", reqinfo->mode));

    switch (reqinfo->mode) {
        /*
         * Read-support (also covers GetNext requests)
         */
    case MODE_GET:
        for (request=requests; request; request=request->next) {
            if (request->processed)
                continue;

            table_entry = (struct pstIFMS1000MeasureTable_entry *)
                              netsnmp_tdata_extract_entry(request);
            table_info  =     netsnmp_extract_table_info( request);
    
            switch (table_info->colnum) {
            case COLUMN_PSTIFMS1000MTPORTNUM:
                if ( !table_entry ) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_NOSUCHINSTANCE);
                    continue;
                }
                snmp_set_var_typed_integer( request->requestvb, ASN_INTEGER,
                                            table_entry->pstIFMS1000MTPortNum);
                break;
            case COLUMN_PSTIFMS1000MEASURESTARTPOSITION:
            {
                if ( !table_entry ) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_NOSUCHINSTANCE);
                    continue;
                }

                long index = table_entry->pstIFMS1000MTPortNum;
                QPST *pst = QPST::getInstance();

                QString  s = pst->m_product->m_pstIFMS1000.get_pstIFMS1000MeasureStartPosition(index);

                snmp_set_var_typed_value( request->requestvb, ASN_OCTET_STR,
										 s.toLatin1().data(),
										 s.length()
                                          /*table_entry->pstIFMS1000MeasureStartPosition,
                                          table_entry->pstIFMS1000MeasureStartPosition_len*/);
            }
                break;
            case COLUMN_PSTIFMS1000MEASUREENDPOSITION:
            	{
                if ( !table_entry ) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_NOSUCHINSTANCE);
                    continue;
                }

                long index = table_entry->pstIFMS1000MTPortNum;
                QPST *pst = QPST::getInstance();

                QString  s = pst->m_product->m_pstIFMS1000.get_pstIFMS1000MeasureEndPosition(index);

                snmp_set_var_typed_value( request->requestvb, ASN_OCTET_STR,
										s.toLatin1().data(),
										s.length()/*
                                          table_entry->pstIFMS1000MeasureEndPosition,
                                          table_entry->pstIFMS1000MeasureEndPosition_len*/);
            	}
				break;
            case COLUMN_PSTIFMS1000MEASUREREFINDEX:
            	{
                if ( !table_entry ) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_NOSUCHINSTANCE);
                    continue;
                }

                long index = table_entry->pstIFMS1000MTPortNum;
                QPST *pst = QPST::getInstance();

                QString  s = pst->m_product->m_pstIFMS1000.get_pstIFMS1000MeasureRefIndex(index);
                snmp_set_var_typed_value( request->requestvb, ASN_OCTET_STR,
										s.toLatin1().data(),
										s.length()/*
										table_entry->pstIFMS1000MeasureRefIndex,
                                        table_entry->pstIFMS1000MeasureRefIndex_len*/);
            	}
                break;
            case COLUMN_PSTIFMS1000MEASURERESOLUTION:
            	{
                if ( !table_entry ) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_NOSUCHINSTANCE);
                    continue;
                }

                long index = table_entry->pstIFMS1000MTPortNum;
                QPST *pst = QPST::getInstance();

                QString  s = pst->m_product->m_pstIFMS1000.get_pstIFMS1000MeasureResolution(index);
                snmp_set_var_typed_value( request->requestvb, ASN_OCTET_STR,
										s.toLatin1().data(),
										s.length()/*table_entry->pstIFMS1000MeasureResolution,
                                          table_entry->pstIFMS1000MeasureResolution_len*/);
               }
			   break;
            case COLUMN_PSTIFMS1000MEASURESTATUS:
            {
                if ( !table_entry ) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_NOSUCHINSTANCE);
                    continue;
                }
                QPST *pst = QPST::getInstance();
                long channel = table_entry->pstIFMS1000MTPortNum;

                long s = pst->m_product->m_pstIFMS1000.get_pstIFMS1000MeasureStatus(channel);
                snmp_set_var_typed_integer( request->requestvb, ASN_INTEGER,
                                            s/*table_entry->pstIFMS1000MeasureStatus*/);
            }
                break;
            case COLUMN_PSTIFMS1000MEASUREACTION:
            {
                if ( !table_entry ) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_NOSUCHINSTANCE);
                    continue;
                }

                long index = table_entry->pstIFMS1000MTPortNum;
                QPST *pst = QPST::getInstance();

                long  s = pst->m_product->m_pstIFMS1000.get_pstIFMS1000MeasureAction(index);
                snmp_set_var_typed_integer( request->requestvb, ASN_INTEGER,
                                            s/*table_entry->pstIFMS1000MeasureAction*/);
            }
                break;
            case COLUMN_PSTIFMS1000MEASUREPULSEWIDTH:
            	{
                if ( !table_entry ) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_NOSUCHINSTANCE);
                    continue;
                }

                long index = table_entry->pstIFMS1000MTPortNum;
                QPST *pst = QPST::getInstance();

                QString  s = pst->m_product->m_pstIFMS1000.get_pstIFMS1000MeasurePulseWidth(index);
                snmp_set_var_typed_value( request->requestvb, ASN_OCTET_STR,
										s.toLatin1().data(),
										s.length()/*table_entry->pstIFMS1000MeasurePulseWidth,
                                          table_entry->pstIFMS1000MeasurePulseWidth_len*/);
                }
				break;
            case COLUMN_PSTIFMS1000MEASURETIME:
            	{
                if ( !table_entry ) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_NOSUCHINSTANCE);
                    continue;
                }

                long index = table_entry->pstIFMS1000MTPortNum;
                QPST *pst = QPST::getInstance();

                long  s = pst->m_product->m_pstIFMS1000.get_pstIFMS1000MeasureTime(index);
                snmp_set_var_typed_integer( request->requestvb, ASN_INTEGER,
                                            s/*table_entry->pstIFMS1000MeasureTime*/);
                }
				break;
            case COLUMN_PSTIFMS1000MEASUREPROGRESSSTATUS:
            {
                if ( !table_entry ) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_NOSUCHINSTANCE);
                    continue;
                }

                long index = table_entry->pstIFMS1000MTPortNum;
                QPST *pst = QPST::getInstance();

                long progress = pst->m_product->m_pstIFMS1000.get_pstIFMS1000MeasureProgressStatus(index);

                snmp_set_var_typed_integer( request->requestvb, ASN_INTEGER,
                                            progress);
            }
                break;
            case COLUMN_PSTIFMS1000MEASURETLOS:
            	{
                if ( !table_entry ) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_NOSUCHINSTANCE);
                    continue;
                }
                long index = table_entry->pstIFMS1000MTPortNum;
				if(0 < index  <= NUMBER_OF_CHANNES){
	                QPST *pst = QPST::getInstance();

	                QString  s = pst->m_product->m_pstIFMS1000.get_pstIFMS1000MeasureTLOS(index);
	                snmp_set_var_typed_value( request->requestvb, ASN_OCTET_STR,
											s.toLatin1().data(),
											s.length()/*table_entry->pstIFMS1000MeasureTLOS,
	                                          table_entry->pstIFMS1000MeasureTLOS_len*/);
	                }
            	}
				break;
            case COLUMN_PSTIFMS1000MEASURETREF:
            	{
                if ( !table_entry ) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_NOSUCHINSTANCE);
                    continue;
                }
                long index = table_entry->pstIFMS1000MTPortNum;
                QPST *pst = QPST::getInstance();

                QString  s = pst->m_product->m_pstIFMS1000.get_pstIFMS1000MeasureTREF(index);
                snmp_set_var_typed_value( request->requestvb, ASN_OCTET_STR,
										s.toLatin1().data(),
										s.length()/*table_entry->pstIFMS1000MeasureTREF,
                                          table_entry->pstIFMS1000MeasureTREF_len*/);
                }
				break;
            case COLUMN_PSTIFMS1000MEASUREFIBERLENGTHCHANGETHRESHOLD:
            	{
                if ( !table_entry ) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_NOSUCHINSTANCE);
                    continue;
                }
                long index = table_entry->pstIFMS1000MTPortNum;
                QPST *pst = QPST::getInstance();

                QString  s = pst->m_product->m_pstIFMS1000.get_pstIFMS1000MeasureFiberLengthChangeThreshold(index);
                snmp_set_var_typed_value( request->requestvb, ASN_OCTET_STR,
										s.toLatin1().data(),
										s.length()/*table_entry->pstIFMS1000MeasureFiberLengthChangeThreshold,
                                          table_entry->pstIFMS1000MeasureFiberLengthChangeThreshold_len*/);
            	}
                break;
            case COLUMN_PSTIFMS1000MEASUREENDTOENDLOSSHIGHTHRESHOLD:
            {
                if ( !table_entry ) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_NOSUCHINSTANCE);
                    continue;
                }
                long index = table_entry->pstIFMS1000MTPortNum;
                QPST *pst = QPST::getInstance();

                QString  s = pst->m_product->m_pstIFMS1000.get_pstIFMS1000MeasureEndToEndLossHighThreshold(index);
                snmp_set_var_typed_value( request->requestvb, ASN_OCTET_STR,
										s.toLatin1().data(),
										s.length()/*table_entry->pstIFMS1000MeasureEndToEndLossHighThreshold,
                                          table_entry->pstIFMS1000MeasureEndToEndLossHighThreshold_len*/);
            }
                break;
            case COLUMN_PSTIFMS1000MEASUREENDTOENDLOSSMIDDLETHRESHOLD:
            {
                if ( !table_entry ) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_NOSUCHINSTANCE);
                    continue;
                }
                long index = table_entry->pstIFMS1000MTPortNum;
                QPST *pst = QPST::getInstance();

                QString  s = pst->m_product->m_pstIFMS1000.get_pstIFMS1000MeasureEndToEndLossMiddleThreshold(index);
                snmp_set_var_typed_value( request->requestvb, ASN_OCTET_STR,
										s.toLatin1().data(),
										s.length()/*table_entry->pstIFMS1000MeasureEndToEndLossMiddleThreshold,
                                          table_entry->pstIFMS1000MeasureEndToEndLossMiddleThreshold_len*/);
            }
                break;
            case COLUMN_PSTIFMS1000MEASUREENDTOENDLOSSLOWTHRESHOLD:
            	{
                if ( !table_entry ) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_NOSUCHINSTANCE);
                    continue;
                }
                long index = table_entry->pstIFMS1000MTPortNum;
                QPST *pst = QPST::getInstance();

                QString  s = pst->m_product->m_pstIFMS1000.get_pstIFMS1000MeasureEndToEndLossLowThreshold(index);
                snmp_set_var_typed_value( request->requestvb, ASN_OCTET_STR,
										s.toLatin1().data(),
										s.length()/*table_entry->pstIFMS1000MeasureEndToEndLossLowThreshold,
                                          table_entry->pstIFMS1000MeasureEndToEndLossLowThreshold_len*/);
                }
				break;
            case COLUMN_PSTIFMS1000MEASURENEWLOSSCRITICALTHRESHOLD:
            	{
                if ( !table_entry ) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_NOSUCHINSTANCE);
                    continue;
                }
                long index = table_entry->pstIFMS1000MTPortNum;
                QPST *pst = QPST::getInstance();

                QString  s = pst->m_product->m_pstIFMS1000.get_pstIFMS1000MeasureNewLossCriticalThreshold(index);
                snmp_set_var_typed_value( request->requestvb, ASN_OCTET_STR,
										s.toLatin1().data(),
										s.length()/*table_entry->pstIFMS1000MeasureNewLossCriticalThreshold,
                                          table_entry->pstIFMS1000MeasureNewLossCriticalThreshold_len*/);
                }
				break;
            case COLUMN_PSTIFMS1000MEASURENEWLOSSMAJORTHRESHOLD:
            	{
                if ( !table_entry ) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_NOSUCHINSTANCE);
                    continue;
                }
                long index = table_entry->pstIFMS1000MTPortNum;
                QPST *pst = QPST::getInstance();

                QString  s = pst->m_product->m_pstIFMS1000.get_pstIFMS1000MeasureNewLossMajorThreshold(index);
                snmp_set_var_typed_value( request->requestvb, ASN_OCTET_STR,
										s.toLatin1().data(),
										s.length()/*table_entry->pstIFMS1000MeasureNewLossMajorThreshold,
                                          table_entry->pstIFMS1000MeasureNewLossMajorThreshold_len*/);
                }
				break;
            case COLUMN_PSTIFMS1000MEASURENEWLOSSMINORTHRESHOLD:
            	{
                if ( !table_entry ) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_NOSUCHINSTANCE);
                    continue;
                }
                long index = table_entry->pstIFMS1000MTPortNum;
                QPST *pst = QPST::getInstance();

                QString  s = pst->m_product->m_pstIFMS1000.get_pstIFMS1000MeasureNewLossMinorThreshold(index);
                snmp_set_var_typed_value( request->requestvb, ASN_OCTET_STR,
										s.toLatin1().data(),
										s.length()/*table_entry->pstIFMS1000MeasureNewLossMinorThreshold,
                                          table_entry->pstIFMS1000MeasureNewLossMinorThreshold_len*/);
                }
				break;
            case COLUMN_PSTIFMS1000MEASUREOLDLOSSCRITICALTHRESHOLD:
            	{
                if ( !table_entry ) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_NOSUCHINSTANCE);
                    continue;
                }
                long index = table_entry->pstIFMS1000MTPortNum;
                QPST *pst = QPST::getInstance();

                QString  s = pst->m_product->m_pstIFMS1000.get_pstIFMS1000MeasureOldLossCriticalThreshold(index);
                snmp_set_var_typed_value( request->requestvb, ASN_OCTET_STR,
										s.toLatin1().data(),
										s.length()/*table_entry->pstIFMS1000MeasureOldLossCriticalThreshold,
                                          table_entry->pstIFMS1000MeasureOldLossCriticalThreshold_len*/);
                }
				break;
            case COLUMN_PSTIFMS1000MEASUREOLDLOSSMAJORTHRESHOLD:
            	{
                if ( !table_entry ) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_NOSUCHINSTANCE);
                    continue;
                }
                long index = table_entry->pstIFMS1000MTPortNum;
                QPST *pst = QPST::getInstance();

                QString  s = pst->m_product->m_pstIFMS1000.get_pstIFMS1000MeasureOldLossMajorThreshold(index);
                snmp_set_var_typed_value( request->requestvb, ASN_OCTET_STR,
										s.toLatin1().data(),
										s.length()/*table_entry->pstIFMS1000MeasureOldLossMajorThreshold,
                                          table_entry->pstIFMS1000MeasureOldLossMajorThreshold_len*/);
                }
				break;
            case COLUMN_PSTIFMS1000MEASUREOLDLOSSMINORTHRESHOLD:
            	{
                if ( !table_entry ) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_NOSUCHINSTANCE);
                    continue;
                }
                long index = table_entry->pstIFMS1000MTPortNum;
                QPST *pst = QPST::getInstance();

                QString  s = pst->m_product->m_pstIFMS1000.get_pstIFMS1000MeasureOldLossMinorThreshold(index);
                snmp_set_var_typed_value( request->requestvb, ASN_OCTET_STR,
										s.toLatin1().data(),
										s.length()/*table_entry->pstIFMS1000MeasureOldLossMinorThreshold,
                                          table_entry->pstIFMS1000MeasureOldLossMinorThreshold_len*/);
                }
				break;
            case COLUMN_PSTIFMS1000MEASUREEVENTPOSITIONCHANGETHRESHOLD:
            	{
                if ( !table_entry ) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_NOSUCHINSTANCE);
                    continue;
                }
                long index = table_entry->pstIFMS1000MTPortNum;
                QPST *pst = QPST::getInstance();

                QString  s = pst->m_product->m_pstIFMS1000.get_pstIFMS1000MeasureEventPositionChangeThreshold(index);
                snmp_set_var_typed_value( request->requestvb, ASN_OCTET_STR,
										s.toLatin1().data(),
										s.length()/*table_entry->pstIFMS1000MeasureEventPositionChangeThreshold,
                                          table_entry->pstIFMS1000MeasureEventPositionChangeThreshold_len*/);
                }
				break;
            case COLUMN_PSTIFMS1000MEASURERESERVED2:
            	{
                if ( !table_entry ) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_NOSUCHINSTANCE);
                    continue;
                }
                long index = table_entry->pstIFMS1000MTPortNum;
                QPST *pst = QPST::getInstance();

                QString  s = pst->m_product->m_pstIFMS1000.get_pstIFMS1000MeasureReserved2(index);
                snmp_set_var_typed_value( request->requestvb, ASN_OCTET_STR,
										s.toLatin1().data(),
										s.length()/*table_entry->pstIFMS1000MeasureReserved2,
                                          table_entry->pstIFMS1000MeasureReserved2_len*/);
                }
				break;
            case COLUMN_PSTIFMS1000MEASURENUMBER:
            {
                if ( !table_entry ) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_NOSUCHINSTANCE);
                    continue;
                }
                long index = table_entry->pstIFMS1000MTPortNum;
                QPST *pst = QPST::getInstance();

                QString s = pst->m_product->m_pstIFMS1000.get_pstIFMS1000MeasureNumber(index);

                snmp_set_var_typed_value( request->requestvb, ASN_OCTET_STR,
                                          s.toLatin1().data(),
                                          s.length()
                                          /*table_entry->pstIFMS1000MeasureNumber,
                                          table_entry->pstIFMS1000MeasureNumber_len*/);
            }
                break;
            case COLUMN_PSTIFMS1000MEASURENUMBERSORSTOREDEACHCHANNEL:
            	{
                if ( !table_entry ) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_NOSUCHINSTANCE);
                    continue;
                }
                long index = table_entry->pstIFMS1000MTPortNum;
                QPST *pst = QPST::getInstance();

                QString  s = pst->m_product->m_pstIFMS1000.get_pstIFMS1000MeasureNumberSORStoredEachChannel(index);
                snmp_set_var_typed_value( request->requestvb, ASN_OCTET_STR,
										s.toLatin1().data(),
										s.length()/*table_entry->pstIFMS1000MeasureNumberSORStoredEachChannel,
                                          table_entry->pstIFMS1000MeasureNumberSORStoredEachChannel_len*/);
                }
				break;
            default:
                netsnmp_set_request_error(reqinfo, request,
                                          SNMP_NOSUCHOBJECT);
                break;
            }
        }
        break;

        /*
         * Write-support
         */
    case MODE_SET_RESERVE1:
        for (request=requests; request; request=request->next) {
            if (request->processed)
                continue;

            table_entry = (struct pstIFMS1000MeasureTable_entry *)
                              netsnmp_tdata_extract_entry(request);
            table_info  =     netsnmp_extract_table_info( request);
    
            switch (table_info->colnum) {
            case COLUMN_PSTIFMS1000MEASURESTARTPOSITION:
	        /* or possibly 'netsnmp_check_vb_type_and_size' */
            	{
                ret = netsnmp_check_vb_type_and_max_size(
                          request->requestvb, ASN_OCTET_STR, sizeof(table_entry->pstIFMS1000MeasureStartPosition));
                if ( ret != SNMP_ERR_NOERROR ) {
                    netsnmp_set_request_error( reqinfo, request, ret );
                    return SNMP_ERR_NOERROR;
                }
                long index = table_entry->pstIFMS1000MTPortNum;
				QPST *pst = QPST::getInstance();
                char * cs =  (char*)requests->requestvb->val.string;
				QString os = pst->m_product->m_pstIFMS1000.get_pstIFMS1000MeasureStartPosition(index);
                QString ns = QString("%1").arg(cs);

				if(os != ns)
				{
					pst->m_product->m_pstIFMS1000.set_pstIFMS1000MeasureStartPosition(index, ns);
				}
	        	}
                break;
            case COLUMN_PSTIFMS1000MEASUREENDPOSITION:
	        /* or possibly 'netsnmp_check_vb_type_and_size' */
	        	{
                ret = netsnmp_check_vb_type_and_max_size(
                          request->requestvb, ASN_OCTET_STR, sizeof(table_entry->pstIFMS1000MeasureEndPosition));
                if ( ret != SNMP_ERR_NOERROR ) {
                    netsnmp_set_request_error( reqinfo, request, ret );
                    return SNMP_ERR_NOERROR;
                }
                long index = table_entry->pstIFMS1000MTPortNum;
                if( 0 < index <= NUMBER_OF_CHANNES){
                    QPST *pst = QPST::getInstance();
                    bool  measuring = pst->m_product->m_pstIFMS1000.is_pstIFMS1000Measuring(index);
                    if(measuring == false){
                        char * cs =  (char*)requests->requestvb->val.string;

                        QString os = pst->m_product->m_pstIFMS1000.get_pstIFMS1000MeasureEndPosition(index);
                        QString om = pst->m_product->m_pstIFMS1000.get_pstIFMS1000MeasurePulseWidth(index);
                        QString ores = pst->m_product->m_pstIFMS1000.get_pstIFMS1000MeasureResolution(index);
                        QString ns = QString("%1").arg(cs);
                        if(os != ns)
                        {
                            QString cmdline = QString("SPARA %1,%2,%3,0").arg(ns,om,ores);
                            emit pst->sigSendCommandToModule((index-1)/CHANNELS_PER_MODULE, cmdline);
                            pst->m_product->m_pstIFMS1000.set_pstIFMS1000MeasureEndPosition(index, ns);
                        }
                    }
                }
	        	}
                break;
            case COLUMN_PSTIFMS1000MEASUREREFINDEX:
	        /* or possibly 'netsnmp_check_vb_type_and_size' */
	        	{
                ret = netsnmp_check_vb_type_and_max_size(
                          request->requestvb, ASN_OCTET_STR, sizeof(table_entry->pstIFMS1000MeasureRefIndex));
                if ( ret != SNMP_ERR_NOERROR ) {
                    netsnmp_set_request_error( reqinfo, request, ret );
                    return SNMP_ERR_NOERROR;
                }
                long index = table_entry->pstIFMS1000MTPortNum;
                if( 0 < index <= NUMBER_OF_CHANNES){
                    QPST *pst = QPST::getInstance();
                    bool  measuring = pst->m_product->m_pstIFMS1000.is_pstIFMS1000Measuring(index);
                    if(measuring == false){
                        char * cs =  (char*)requests->requestvb->val.string;

                        QString os = pst->m_product->m_pstIFMS1000.get_pstIFMS1000MeasureRefIndex(index);
                        QString ns = QString("%1").arg(cs);
                        if(os != ns)
                        {
                            QString cmdline = QString("UIOR %1").arg(cs);
                            emit pst->sigSendCommandToModule((index-1)/CHANNELS_PER_MODULE, cmdline);
                            pst->m_product->m_pstIFMS1000.set_pstIFMS1000MeasureRefIndex(index, ns);
                        }
						}
                    }
	        	}
                break;
            case COLUMN_PSTIFMS1000MEASURERESOLUTION:
	        /* or possibly 'netsnmp_check_vb_type_and_size' */
	        	{
                ret = netsnmp_check_vb_type_and_max_size(
                          request->requestvb, ASN_OCTET_STR, sizeof(table_entry->pstIFMS1000MeasureResolution));
                if ( ret != SNMP_ERR_NOERROR ) {
                    netsnmp_set_request_error( reqinfo, request, ret );
                    return SNMP_ERR_NOERROR;
                }
                long index = table_entry->pstIFMS1000MTPortNum;
                if( 0 < index <= NUMBER_OF_CHANNES){
                    QPST *pst = QPST::getInstance();
                    bool  measuring = pst->m_product->m_pstIFMS1000.is_pstIFMS1000Measuring(index);
                    if(measuring == false){
                        char * cs =  (char*)requests->requestvb->val.string;

                        QString os = pst->m_product->m_pstIFMS1000.get_pstIFMS1000MeasureEndPosition(index);
                        QString om = pst->m_product->m_pstIFMS1000.get_pstIFMS1000MeasurePulseWidth(index);
                        QString ores = pst->m_product->m_pstIFMS1000.get_pstIFMS1000MeasureResolution(index);
                        QString nres = QString("%1").arg(cs);
                        if(ores != nres)
                        {
                            QString cmdline = QString("SPARA %1,%2,%3,0").arg(os,om,nres);
                            emit pst->sigSendCommandToModule((index-1)/CHANNELS_PER_MODULE, cmdline);
                            pst->m_product->m_pstIFMS1000.set_pstIFMS1000MeasureResolution(index, nres);
                        }
						}
                    }
	        	}
                break;
            case COLUMN_PSTIFMS1000MEASUREACTION:
                /* or possibly 'netsnmp_check_vb_int_range' */
				{

                ret = netsnmp_check_vb_int( request->requestvb );
                if ( ret != SNMP_ERR_NOERROR ) {
                    netsnmp_set_request_error( reqinfo, request, ret );
                    return SNMP_ERR_NOERROR;
                }
                long action = *(requests->requestvb->val.integer);
                long index = table_entry->pstIFMS1000MTPortNum;
                if(index <= 4){
                    if(action == 1) // start
                    {
                        emit QAgentApp::getInstance()->sigModuleStartMonitor(0);
                    }
                    else if(action == 3 )  // start single
                    {
                        emit QAgentApp::getInstance()->sigModuleSingleMonitor(0);
                    }
                    else
                    {
                        emit QAgentApp::getInstance()->sigModuleStopMonitor(0);
                    }
                }
                else if(4< index)
                {
                    if(action == 1) // start
                    {
                        emit QAgentApp::getInstance()->sigModuleStartMonitor(1);
                    }
                    else if(action == 3 )  // start single
                    {
                        emit QAgentApp::getInstance()->sigModuleSingleMonitor(1);
                    }
                    else
                    {
                        emit QAgentApp::getInstance()->sigModuleStopMonitor(1);
                    }
                }

            }
                break;
            case COLUMN_PSTIFMS1000MEASUREPULSEWIDTH:
	        /* or possibly 'netsnmp_check_vb_type_and_size' */
	        	{
                ret = netsnmp_check_vb_type_and_max_size(
                          request->requestvb, ASN_OCTET_STR, sizeof(table_entry->pstIFMS1000MeasurePulseWidth));
                if ( ret != SNMP_ERR_NOERROR ) {
                    netsnmp_set_request_error( reqinfo, request, ret );
                    return SNMP_ERR_NOERROR;
                }
				
                long index = table_entry->pstIFMS1000MTPortNum;
                if( 0 < index <= NUMBER_OF_CHANNES){
                    QPST *pst = QPST::getInstance();
                    bool  measuring = pst->m_product->m_pstIFMS1000.is_pstIFMS1000Measuring(index);
                    if(measuring == false){
                        char * cs =  (char*)requests->requestvb->val.string;

                        QString os = pst->m_product->m_pstIFMS1000.get_pstIFMS1000MeasureEndPosition(index);
                        QString om = pst->m_product->m_pstIFMS1000.get_pstIFMS1000MeasurePulseWidth(index);
                        QString ores = pst->m_product->m_pstIFMS1000.get_pstIFMS1000MeasureResolution(index);
                        QString nm = QString("%1").arg(cs);
                        if(om != nm)
                        {
                            QString cmdline = QString("SPARA %1,%2,%3,0").arg(os,nm,ores);
                            emit pst->sigSendCommandToModule((index-1)/CHANNELS_PER_MODULE, cmdline);
                            pst->m_product->m_pstIFMS1000.set_pstIFMS1000MeasurePulseWidth(index, nm);
                        }
                    }
					}
	        	}
                break;
            case COLUMN_PSTIFMS1000MEASURETIME:
                /* or possibly 'netsnmp_check_vb_int_range' */
                {
                ret = netsnmp_check_vb_int( request->requestvb );
                if ( ret != SNMP_ERR_NOERROR ) {
                    netsnmp_set_request_error( reqinfo, request, ret );
                    return SNMP_ERR_NOERROR;
                }
				 QPST *pst = QPST::getInstance();
                long index = table_entry->pstIFMS1000MTPortNum;
                if( 0 < index <= NUMBER_OF_CHANNES){
                    bool  measuring = pst->m_product->m_pstIFMS1000.is_pstIFMS1000Measuring(index);
                    if(measuring == false){
                        int ns = (int)(*requests->requestvb->val.integer);
                        long os = pst->m_product->m_pstIFMS1000.get_pstIFMS1000MeasureTime(index);

                        if(os != ns)
                        {
                            QString cmdline = QString("ACQT %1").arg(ns);
                            emit pst->sigSendCommandToModule((index-1)/CHANNELS_PER_MODULE, cmdline);
                            pst->m_product->m_pstIFMS1000.set_pstIFMS1000MeasureTime(index, ns);
                        }
					}
                }
				}
                break;
            case COLUMN_PSTIFMS1000MEASURETLOS:
	        /* or possibly 'netsnmp_check_vb_type_and_size' */
	        	{
                ret = netsnmp_check_vb_type_and_max_size(
                          request->requestvb, ASN_OCTET_STR, sizeof(table_entry->pstIFMS1000MeasureTLOS));
                if ( ret != SNMP_ERR_NOERROR ) {
                    netsnmp_set_request_error( reqinfo, request, ret );
                    return SNMP_ERR_NOERROR;
                }
                long index = table_entry->pstIFMS1000MTPortNum;
                if( 0 < index <= NUMBER_OF_CHANNES){
                    QPST *pst = QPST::getInstance();
                    bool  measuring = pst->m_product->m_pstIFMS1000.is_pstIFMS1000Measuring(index);
                    if(measuring == false){
                        char * cs =  (char*)requests->requestvb->val.string;
                        QString os = pst->m_product->m_pstIFMS1000.get_pstIFMS1000MeasureTLOS(index);
                        QString ns = QString("%1").arg(cs);

                        if(os != ns)
                        {
                            QString cmdline = QString("TLOS %1 %2").arg((index -1)%CHANNELS_PER_MODULE).arg(cs);
                            emit pst->sigSendCommandToModule((index-1)/CHANNELS_PER_MODULE, cmdline);
                            pst->m_product->m_pstIFMS1000.set_pstIFMS1000MeasureTLOS(index, ns);
                        }
                    }
					}
	        	}
                break;
            case COLUMN_PSTIFMS1000MEASURETREF:
	        /* or possibly 'netsnmp_check_vb_type_and_size' */
	        	{
                ret = netsnmp_check_vb_type_and_max_size(
                          request->requestvb, ASN_OCTET_STR, sizeof(table_entry->pstIFMS1000MeasureTREF));
                if ( ret != SNMP_ERR_NOERROR ) {
                    netsnmp_set_request_error( reqinfo, request, ret );
                    return SNMP_ERR_NOERROR;
                }
                long index = table_entry->pstIFMS1000MTPortNum;
                if( 0 < index <= NUMBER_OF_CHANNES){
                    QPST *pst = QPST::getInstance();
                    bool  measuring = pst->m_product->m_pstIFMS1000.is_pstIFMS1000Measuring(index);
                    if(measuring == false){
                        char * cs =  (char*)requests->requestvb->val.string;
                        QString os = pst->m_product->m_pstIFMS1000.get_pstIFMS1000MeasureTREF(index);
                        QString ns = QString("%1").arg(cs);

                        if(os != ns)
                        {
                            QString cmdline = QString("TREF %1 %2").arg((index -1)%CHANNELS_PER_MODULE).arg(cs);
                            emit pst->sigSendCommandToModule((index-1)/CHANNELS_PER_MODULE, cmdline);
                            pst->m_product->m_pstIFMS1000.set_pstIFMS1000MeasureTREF(index, ns);
                        }
                    }
					}
	        	}
                break;
            case COLUMN_PSTIFMS1000MEASUREFIBERLENGTHCHANGETHRESHOLD:
	        /* or possibly 'netsnmp_check_vb_type_and_size' */
	        	{
                ret = netsnmp_check_vb_type_and_max_size(
                          request->requestvb, ASN_OCTET_STR, sizeof(table_entry->pstIFMS1000MeasureFiberLengthChangeThreshold));
                if ( ret != SNMP_ERR_NOERROR ) {
                    netsnmp_set_request_error( reqinfo, request, ret );
                    return SNMP_ERR_NOERROR;
                }
                long index = table_entry->pstIFMS1000MTPortNum;
				QPST *pst = QPST::getInstance();
                char * cs =  (char*)requests->requestvb->val.string;
                QString os = pst->m_product->m_pstIFMS1000.get_pstIFMS1000MeasureFiberLengthChangeThreshold(index);
                QString ns = QString("%1").arg(cs);

				if(os != ns)
				{
					pst->m_product->m_pstIFMS1000.set_pstIFMS1000MeasureFiberLengthChangeThreshold(index, ns);
				}
	        	}
                break;
            case COLUMN_PSTIFMS1000MEASUREENDTOENDLOSSHIGHTHRESHOLD:
	        /* or possibly 'netsnmp_check_vb_type_and_size' */
	        	{
                ret = netsnmp_check_vb_type_and_max_size(
                          request->requestvb, ASN_OCTET_STR, sizeof(table_entry->pstIFMS1000MeasureEndToEndLossHighThreshold));
                if ( ret != SNMP_ERR_NOERROR ) {
                    netsnmp_set_request_error( reqinfo, request, ret );
                    return SNMP_ERR_NOERROR;
                }
                long index = table_entry->pstIFMS1000MTPortNum;
				QPST *pst = QPST::getInstance();
                char * cs =  (char*)requests->requestvb->val.string;
                QString os = pst->m_product->m_pstIFMS1000.get_pstIFMS1000MeasureEndToEndLossHighThreshold(index);
                QString ns = QString("%1").arg(cs);

				if(os != ns)
				{
					pst->m_product->m_pstIFMS1000.set_pstIFMS1000MeasureEndToEndLossHighThreshold(index, ns);
				}
	        	}
                break;
            case COLUMN_PSTIFMS1000MEASUREENDTOENDLOSSMIDDLETHRESHOLD:
	        /* or possibly 'netsnmp_check_vb_type_and_size' */
	        	{
                ret = netsnmp_check_vb_type_and_max_size(
                          request->requestvb, ASN_OCTET_STR, sizeof(table_entry->pstIFMS1000MeasureEndToEndLossMiddleThreshold));
                if ( ret != SNMP_ERR_NOERROR ) {
                    netsnmp_set_request_error( reqinfo, request, ret );
                    return SNMP_ERR_NOERROR;
                }
                long index = table_entry->pstIFMS1000MTPortNum;
				QPST *pst = QPST::getInstance();
                char * cs =  (char*)requests->requestvb->val.string;
                QString os = pst->m_product->m_pstIFMS1000.get_pstIFMS1000MeasureEndToEndLossMiddleThreshold(index);
                QString ns = QString("%1").arg(cs);

				if(os != ns)
				{
					pst->m_product->m_pstIFMS1000.set_pstIFMS1000MeasureEndToEndLossMiddleThreshold(index, ns);
				}
	        	}
                break;
            case COLUMN_PSTIFMS1000MEASUREENDTOENDLOSSLOWTHRESHOLD:
	        /* or possibly 'netsnmp_check_vb_type_and_size' */
	        	{
                ret = netsnmp_check_vb_type_and_max_size(
                          request->requestvb, ASN_OCTET_STR, sizeof(table_entry->pstIFMS1000MeasureEndToEndLossLowThreshold));
                if ( ret != SNMP_ERR_NOERROR ) {
                    netsnmp_set_request_error( reqinfo, request, ret );
                    return SNMP_ERR_NOERROR;
                }
                long index = table_entry->pstIFMS1000MTPortNum;
				QPST *pst = QPST::getInstance();
                char * cs =  (char*)requests->requestvb->val.string;
                QString os = pst->m_product->m_pstIFMS1000.get_pstIFMS1000MeasureEndToEndLossLowThreshold(index);
                QString ns = QString("%1").arg(cs);

				if(os != ns)
				{
					pst->m_product->m_pstIFMS1000.set_pstIFMS1000MeasureEndToEndLossLowThreshold(index, ns);
				}
	        	}
                break;
            case COLUMN_PSTIFMS1000MEASURENEWLOSSCRITICALTHRESHOLD:
	        /* or possibly 'netsnmp_check_vb_type_and_size' */
	        	{
                ret = netsnmp_check_vb_type_and_max_size(
                          request->requestvb, ASN_OCTET_STR, sizeof(table_entry->pstIFMS1000MeasureNewLossCriticalThreshold));
                if ( ret != SNMP_ERR_NOERROR ) {
                    netsnmp_set_request_error( reqinfo, request, ret );
                    return SNMP_ERR_NOERROR;
                }
                long index = table_entry->pstIFMS1000MTPortNum;
				QPST *pst = QPST::getInstance();
                char * cs =  (char*)requests->requestvb->val.string;
                QString os = pst->m_product->m_pstIFMS1000.get_pstIFMS1000MeasureNewLossCriticalThreshold(index);
                QString ns = QString("%1").arg(cs);

				if(os != ns)
				{
					pst->m_product->m_pstIFMS1000.set_pstIFMS1000MeasureNewLossCriticalThreshold(index, ns);
				}
	        	}
                break;
            case COLUMN_PSTIFMS1000MEASURENEWLOSSMAJORTHRESHOLD:
	        /* or possibly 'netsnmp_check_vb_type_and_size' */
	        	{
                ret = netsnmp_check_vb_type_and_max_size(
                          request->requestvb, ASN_OCTET_STR, sizeof(table_entry->pstIFMS1000MeasureNewLossMajorThreshold));
                if ( ret != SNMP_ERR_NOERROR ) {
                    netsnmp_set_request_error( reqinfo, request, ret );
                    return SNMP_ERR_NOERROR;
                }
                long index = table_entry->pstIFMS1000MTPortNum;
				QPST *pst = QPST::getInstance();
                char * cs =  (char*)requests->requestvb->val.string;
                QString os = pst->m_product->m_pstIFMS1000.get_pstIFMS1000MeasureNewLossMajorThreshold(index);
				QString ns = QString("%1").arg(cs);

				if(os != ns)
				{
					pst->m_product->m_pstIFMS1000.set_pstIFMS1000MeasureNewLossMajorThreshold(index, ns);
				}
	        	}
                break;
            case COLUMN_PSTIFMS1000MEASURENEWLOSSMINORTHRESHOLD:
	        /* or possibly 'netsnmp_check_vb_type_and_size' */
	        	{
                ret = netsnmp_check_vb_type_and_max_size(
                          request->requestvb, ASN_OCTET_STR, sizeof(table_entry->pstIFMS1000MeasureNewLossMinorThreshold));
                if ( ret != SNMP_ERR_NOERROR ) {
                    netsnmp_set_request_error( reqinfo, request, ret );
                    return SNMP_ERR_NOERROR;
                }
                long index = table_entry->pstIFMS1000MTPortNum;
				QPST *pst = QPST::getInstance();
                char * cs =  (char*)requests->requestvb->val.string;
                QString os = pst->m_product->m_pstIFMS1000.get_pstIFMS1000MeasureNewLossMinorThreshold(index);
				QString ns = QString("%1").arg(cs);

				if(os != ns)
				{
					pst->m_product->m_pstIFMS1000.set_pstIFMS1000MeasureNewLossMinorThreshold(index, ns);
				}
	        	}
                break;
            case COLUMN_PSTIFMS1000MEASUREOLDLOSSCRITICALTHRESHOLD:
	        /* or possibly 'netsnmp_check_vb_type_and_size' */
	        	{
                ret = netsnmp_check_vb_type_and_max_size(
                          request->requestvb, ASN_OCTET_STR, sizeof(table_entry->pstIFMS1000MeasureOldLossCriticalThreshold));
                if ( ret != SNMP_ERR_NOERROR ) {
                    netsnmp_set_request_error( reqinfo, request, ret );
                    return SNMP_ERR_NOERROR;
                }
                long index = table_entry->pstIFMS1000MTPortNum;
				QPST *pst = QPST::getInstance();
                char * cs =  (char*)requests->requestvb->val.string;
                QString os = pst->m_product->m_pstIFMS1000.get_pstIFMS1000MeasureOldLossCriticalThreshold(index);
				QString ns = QString("%1").arg(cs);

				if(os != ns)
				{
					pst->m_product->m_pstIFMS1000.set_pstIFMS1000MeasureOldLossCriticalThreshold(index, ns);
				}
	        	}
                break;
            case COLUMN_PSTIFMS1000MEASUREOLDLOSSMAJORTHRESHOLD:
	        /* or possibly 'netsnmp_check_vb_type_and_size' */
	        	{
                ret = netsnmp_check_vb_type_and_max_size(
                          request->requestvb, ASN_OCTET_STR, sizeof(table_entry->pstIFMS1000MeasureOldLossMajorThreshold));
                if ( ret != SNMP_ERR_NOERROR ) {
                    netsnmp_set_request_error( reqinfo, request, ret );
                    return SNMP_ERR_NOERROR;
                }
                long index = table_entry->pstIFMS1000MTPortNum;
				QPST *pst = QPST::getInstance();
                char * cs =  (char*)requests->requestvb->val.string;
                QString os = pst->m_product->m_pstIFMS1000.get_pstIFMS1000MeasureOldLossMajorThreshold(index);
				QString ns = QString("%1").arg(cs);

				if(os != ns)
				{
					pst->m_product->m_pstIFMS1000.set_pstIFMS1000MeasureOldLossMajorThreshold(index, ns);
				}
	        	}
                break;
            case COLUMN_PSTIFMS1000MEASUREOLDLOSSMINORTHRESHOLD:
	        /* or possibly 'netsnmp_check_vb_type_and_size' */
	        	{
                ret = netsnmp_check_vb_type_and_max_size(
                          request->requestvb, ASN_OCTET_STR, sizeof(table_entry->pstIFMS1000MeasureOldLossMinorThreshold));
                if ( ret != SNMP_ERR_NOERROR ) {
                    netsnmp_set_request_error( reqinfo, request, ret );
                    return SNMP_ERR_NOERROR;
                }
                long index = table_entry->pstIFMS1000MTPortNum;
				QPST *pst = QPST::getInstance();
                char * cs =  (char*)requests->requestvb->val.string;
                QString os = pst->m_product->m_pstIFMS1000.get_pstIFMS1000MeasureOldLossMinorThreshold(index);
				QString ns = QString("%1").arg(cs);

				if(os != ns)
				{
					pst->m_product->m_pstIFMS1000.set_pstIFMS1000MeasureOldLossMinorThreshold(index, ns);
				}
	        	}
                break;
            case COLUMN_PSTIFMS1000MEASUREEVENTPOSITIONCHANGETHRESHOLD:
	        /* or possibly 'netsnmp_check_vb_type_and_size' */
	        	{
                ret = netsnmp_check_vb_type_and_max_size(
                          request->requestvb, ASN_OCTET_STR, sizeof(table_entry->pstIFMS1000MeasureEventPositionChangeThreshold));
                if ( ret != SNMP_ERR_NOERROR ) {
                    netsnmp_set_request_error( reqinfo, request, ret );
                    return SNMP_ERR_NOERROR;
                }
                long index = table_entry->pstIFMS1000MTPortNum;
				QPST *pst = QPST::getInstance();
                char * cs =  (char*)requests->requestvb->val.string;
                QString os = pst->m_product->m_pstIFMS1000.get_pstIFMS1000MeasureEventPositionChangeThreshold(index);
				QString ns = QString("%1").arg(cs);

				if(os != ns)
				{
					pst->m_product->m_pstIFMS1000.set_pstIFMS1000MeasureEventPositionChangeThreshold(index, ns);
				}
	        	}
                break;
            case COLUMN_PSTIFMS1000MEASURERESERVED2:
	        /* or possibly 'netsnmp_check_vb_type_and_size' */
	        	{
                ret = netsnmp_check_vb_type_and_max_size(
                          request->requestvb, ASN_OCTET_STR, sizeof(table_entry->pstIFMS1000MeasureReserved2));
                if ( ret != SNMP_ERR_NOERROR ) {
                    netsnmp_set_request_error( reqinfo, request, ret );
                    return SNMP_ERR_NOERROR;
                }
                long index = table_entry->pstIFMS1000MTPortNum;
				QPST *pst = QPST::getInstance();
                char * cs =  (char*)requests->requestvb->val.string;
                QString os = pst->m_product->m_pstIFMS1000.get_pstIFMS1000MeasureReserved2(index);
				QString ns = QString("%1").arg(cs);

				if(os != ns)
				{
					pst->m_product->m_pstIFMS1000.set_pstIFMS1000MeasureReserved2(index, ns);
				}
	        	}
                break;
            case COLUMN_PSTIFMS1000MEASURENUMBERSORSTOREDEACHCHANNEL:
	        /* or possibly 'netsnmp_check_vb_type_and_size' */
	        	{
                ret = netsnmp_check_vb_type_and_max_size(
                          request->requestvb, ASN_OCTET_STR, sizeof(table_entry->pstIFMS1000MeasureNumberSORStoredEachChannel));
                if ( ret != SNMP_ERR_NOERROR ) {
                    netsnmp_set_request_error( reqinfo, request, ret );
                    return SNMP_ERR_NOERROR;
                }
                long index = table_entry->pstIFMS1000MTPortNum;
				QPST *pst = QPST::getInstance();
                char * cs =  (char*)requests->requestvb->val.string;
                QString os = pst->m_product->m_pstIFMS1000.get_pstIFMS1000MeasureNumberSORStoredEachChannel(index);
				QString ns = QString("%1").arg(cs);

				if(os != ns)
				{
					pst->m_product->m_pstIFMS1000.set_pstIFMS1000MeasureNumberSORStoredEachChannel(index, ns);
				}
	        	}
                break;
            default:
                netsnmp_set_request_error( reqinfo, request,
                                           SNMP_ERR_NOTWRITABLE );
                return SNMP_ERR_NOERROR;
            }
        }
        break;

    case MODE_SET_RESERVE2:
        break;

    case MODE_SET_FREE:
        break;

    case MODE_SET_ACTION:
//        for (request=requests; request; request=request->next) {
//            if (request->processed)
//                continue;

//            table_entry = (struct pstIFMS1000MeasureTable_entry *)
//                              netsnmp_tdata_extract_entry(request);
//            table_info  =     netsnmp_extract_table_info( request);
    
//            switch (table_info->colnum) {
//            case COLUMN_PSTIFMS1000MEASURESTARTPOSITION:
//                memcpy( table_entry->old_pstIFMS1000MeasureStartPosition,
//                        table_entry->pstIFMS1000MeasureStartPosition,
//                        sizeof(table_entry->pstIFMS1000MeasureStartPosition));
//                table_entry->old_pstIFMS1000MeasureStartPosition_len =
//                        table_entry->pstIFMS1000MeasureStartPosition_len;
//                memset( table_entry->pstIFMS1000MeasureStartPosition, 0,
//                        sizeof(table_entry->pstIFMS1000MeasureStartPosition));
//                memcpy( table_entry->pstIFMS1000MeasureStartPosition,
//                        request->requestvb->val.string,
//                        request->requestvb->val_len);
//                table_entry->pstIFMS1000MeasureStartPosition_len =
//                        request->requestvb->val_len;
//                break;
//            case COLUMN_PSTIFMS1000MEASUREENDPOSITION:
//                memcpy( table_entry->old_pstIFMS1000MeasureEndPosition,
//                        table_entry->pstIFMS1000MeasureEndPosition,
//                        sizeof(table_entry->pstIFMS1000MeasureEndPosition));
//                table_entry->old_pstIFMS1000MeasureEndPosition_len =
//                        table_entry->pstIFMS1000MeasureEndPosition_len;
//                memset( table_entry->pstIFMS1000MeasureEndPosition, 0,
//                        sizeof(table_entry->pstIFMS1000MeasureEndPosition));
//                memcpy( table_entry->pstIFMS1000MeasureEndPosition,
//                        request->requestvb->val.string,
//                        request->requestvb->val_len);
//                table_entry->pstIFMS1000MeasureEndPosition_len =
//                        request->requestvb->val_len;
//                break;
//            case COLUMN_PSTIFMS1000MEASUREREFINDEX:
//                memcpy( table_entry->old_pstIFMS1000MeasureRefIndex,
//                        table_entry->pstIFMS1000MeasureRefIndex,
//                        sizeof(table_entry->pstIFMS1000MeasureRefIndex));
//                table_entry->old_pstIFMS1000MeasureRefIndex_len =
//                        table_entry->pstIFMS1000MeasureRefIndex_len;
//                memset( table_entry->pstIFMS1000MeasureRefIndex, 0,
//                        sizeof(table_entry->pstIFMS1000MeasureRefIndex));
//                memcpy( table_entry->pstIFMS1000MeasureRefIndex,
//                        request->requestvb->val.string,
//                        request->requestvb->val_len);
//                table_entry->pstIFMS1000MeasureRefIndex_len =
//                        request->requestvb->val_len;
//                break;
//            case COLUMN_PSTIFMS1000MEASURERESOLUTION:
//                memcpy( table_entry->old_pstIFMS1000MeasureResolution,
//                        table_entry->pstIFMS1000MeasureResolution,
//                        sizeof(table_entry->pstIFMS1000MeasureResolution));
//                table_entry->old_pstIFMS1000MeasureResolution_len =
//                        table_entry->pstIFMS1000MeasureResolution_len;
//                memset( table_entry->pstIFMS1000MeasureResolution, 0,
//                        sizeof(table_entry->pstIFMS1000MeasureResolution));
//                memcpy( table_entry->pstIFMS1000MeasureResolution,
//                        request->requestvb->val.string,
//                        request->requestvb->val_len);
//                table_entry->pstIFMS1000MeasureResolution_len =
//                        request->requestvb->val_len;
//                break;
//            case COLUMN_PSTIFMS1000MEASUREACTION:
//                table_entry->old_pstIFMS1000MeasureAction = table_entry->pstIFMS1000MeasureAction;
//                table_entry->pstIFMS1000MeasureAction     = *request->requestvb->val.integer;
//                break;
//            case COLUMN_PSTIFMS1000MEASUREPULSEWIDTH:
//                memcpy( table_entry->old_pstIFMS1000MeasurePulseWidth,
//                        table_entry->pstIFMS1000MeasurePulseWidth,
//                        sizeof(table_entry->pstIFMS1000MeasurePulseWidth));
//                table_entry->old_pstIFMS1000MeasurePulseWidth_len =
//                        table_entry->pstIFMS1000MeasurePulseWidth_len;
//                memset( table_entry->pstIFMS1000MeasurePulseWidth, 0,
//                        sizeof(table_entry->pstIFMS1000MeasurePulseWidth));
//                memcpy( table_entry->pstIFMS1000MeasurePulseWidth,
//                        request->requestvb->val.string,
//                        request->requestvb->val_len);
//                table_entry->pstIFMS1000MeasurePulseWidth_len =
//                        request->requestvb->val_len;
//                break;
//            case COLUMN_PSTIFMS1000MEASURETIME:
//                table_entry->old_pstIFMS1000MeasureTime = table_entry->pstIFMS1000MeasureTime;
//                table_entry->pstIFMS1000MeasureTime     = *request->requestvb->val.integer;
//                break;
//            case COLUMN_PSTIFMS1000MEASURETLOS:
//                memcpy( table_entry->old_pstIFMS1000MeasureTLOS,
//                        table_entry->pstIFMS1000MeasureTLOS,
//                        sizeof(table_entry->pstIFMS1000MeasureTLOS));
//                table_entry->old_pstIFMS1000MeasureTLOS_len =
//                        table_entry->pstIFMS1000MeasureTLOS_len;
//                memset( table_entry->pstIFMS1000MeasureTLOS, 0,
//                        sizeof(table_entry->pstIFMS1000MeasureTLOS));
//                memcpy( table_entry->pstIFMS1000MeasureTLOS,
//                        request->requestvb->val.string,
//                        request->requestvb->val_len);
//                table_entry->pstIFMS1000MeasureTLOS_len =
//                        request->requestvb->val_len;
//                break;
//            case COLUMN_PSTIFMS1000MEASURETREF:
//                memcpy( table_entry->old_pstIFMS1000MeasureTREF,
//                        table_entry->pstIFMS1000MeasureTREF,
//                        sizeof(table_entry->pstIFMS1000MeasureTREF));
//                table_entry->old_pstIFMS1000MeasureTREF_len =
//                        table_entry->pstIFMS1000MeasureTREF_len;
//                memset( table_entry->pstIFMS1000MeasureTREF, 0,
//                        sizeof(table_entry->pstIFMS1000MeasureTREF));
//                memcpy( table_entry->pstIFMS1000MeasureTREF,
//                        request->requestvb->val.string,
//                        request->requestvb->val_len);
//                table_entry->pstIFMS1000MeasureTREF_len =
//                        request->requestvb->val_len;
//                break;
//            case COLUMN_PSTIFMS1000MEASUREFIBERLENGTHCHANGETHRESHOLD:
//                memcpy( table_entry->old_pstIFMS1000MeasureFiberLengthChangeThreshold,
//                        table_entry->pstIFMS1000MeasureFiberLengthChangeThreshold,
//                        sizeof(table_entry->pstIFMS1000MeasureFiberLengthChangeThreshold));
//                table_entry->old_pstIFMS1000MeasureFiberLengthChangeThreshold_len =
//                        table_entry->pstIFMS1000MeasureFiberLengthChangeThreshold_len;
//                memset( table_entry->pstIFMS1000MeasureFiberLengthChangeThreshold, 0,
//                        sizeof(table_entry->pstIFMS1000MeasureFiberLengthChangeThreshold));
//                memcpy( table_entry->pstIFMS1000MeasureFiberLengthChangeThreshold,
//                        request->requestvb->val.string,
//                        request->requestvb->val_len);
//                table_entry->pstIFMS1000MeasureFiberLengthChangeThreshold_len =
//                        request->requestvb->val_len;
//                break;
//            case COLUMN_PSTIFMS1000MEASUREENDTOENDLOSSHIGHTHRESHOLD:
//                memcpy( table_entry->old_pstIFMS1000MeasureEndToEndLossHighThreshold,
//                        table_entry->pstIFMS1000MeasureEndToEndLossHighThreshold,
//                        sizeof(table_entry->pstIFMS1000MeasureEndToEndLossHighThreshold));
//                table_entry->old_pstIFMS1000MeasureEndToEndLossHighThreshold_len =
//                        table_entry->pstIFMS1000MeasureEndToEndLossHighThreshold_len;
//                memset( table_entry->pstIFMS1000MeasureEndToEndLossHighThreshold, 0,
//                        sizeof(table_entry->pstIFMS1000MeasureEndToEndLossHighThreshold));
//                memcpy( table_entry->pstIFMS1000MeasureEndToEndLossHighThreshold,
//                        request->requestvb->val.string,
//                        request->requestvb->val_len);
//                table_entry->pstIFMS1000MeasureEndToEndLossHighThreshold_len =
//                        request->requestvb->val_len;
//                break;
//            case COLUMN_PSTIFMS1000MEASUREENDTOENDLOSSMIDDLETHRESHOLD:
//                memcpy( table_entry->old_pstIFMS1000MeasureEndToEndLossMiddleThreshold,
//                        table_entry->pstIFMS1000MeasureEndToEndLossMiddleThreshold,
//                        sizeof(table_entry->pstIFMS1000MeasureEndToEndLossMiddleThreshold));
//                table_entry->old_pstIFMS1000MeasureEndToEndLossMiddleThreshold_len =
//                        table_entry->pstIFMS1000MeasureEndToEndLossMiddleThreshold_len;
//                memset( table_entry->pstIFMS1000MeasureEndToEndLossMiddleThreshold, 0,
//                        sizeof(table_entry->pstIFMS1000MeasureEndToEndLossMiddleThreshold));
//                memcpy( table_entry->pstIFMS1000MeasureEndToEndLossMiddleThreshold,
//                        request->requestvb->val.string,
//                        request->requestvb->val_len);
//                table_entry->pstIFMS1000MeasureEndToEndLossMiddleThreshold_len =
//                        request->requestvb->val_len;
//                break;
//            case COLUMN_PSTIFMS1000MEASUREENDTOENDLOSSLOWTHRESHOLD:
//                memcpy( table_entry->old_pstIFMS1000MeasureEndToEndLossLowThreshold,
//                        table_entry->pstIFMS1000MeasureEndToEndLossLowThreshold,
//                        sizeof(table_entry->pstIFMS1000MeasureEndToEndLossLowThreshold));
//                table_entry->old_pstIFMS1000MeasureEndToEndLossLowThreshold_len =
//                        table_entry->pstIFMS1000MeasureEndToEndLossLowThreshold_len;
//                memset( table_entry->pstIFMS1000MeasureEndToEndLossLowThreshold, 0,
//                        sizeof(table_entry->pstIFMS1000MeasureEndToEndLossLowThreshold));
//                memcpy( table_entry->pstIFMS1000MeasureEndToEndLossLowThreshold,
//                        request->requestvb->val.string,
//                        request->requestvb->val_len);
//                table_entry->pstIFMS1000MeasureEndToEndLossLowThreshold_len =
//                        request->requestvb->val_len;
//                break;
//            case COLUMN_PSTIFMS1000MEASURENEWLOSSCRITICALTHRESHOLD:
//                memcpy( table_entry->old_pstIFMS1000MeasureNewLossCriticalThreshold,
//                        table_entry->pstIFMS1000MeasureNewLossCriticalThreshold,
//                        sizeof(table_entry->pstIFMS1000MeasureNewLossCriticalThreshold));
//                table_entry->old_pstIFMS1000MeasureNewLossCriticalThreshold_len =
//                        table_entry->pstIFMS1000MeasureNewLossCriticalThreshold_len;
//                memset( table_entry->pstIFMS1000MeasureNewLossCriticalThreshold, 0,
//                        sizeof(table_entry->pstIFMS1000MeasureNewLossCriticalThreshold));
//                memcpy( table_entry->pstIFMS1000MeasureNewLossCriticalThreshold,
//                        request->requestvb->val.string,
//                        request->requestvb->val_len);
//                table_entry->pstIFMS1000MeasureNewLossCriticalThreshold_len =
//                        request->requestvb->val_len;
//                break;
//            case COLUMN_PSTIFMS1000MEASURENEWLOSSMAJORTHRESHOLD:
//                memcpy( table_entry->old_pstIFMS1000MeasureNewLossMajorThreshold,
//                        table_entry->pstIFMS1000MeasureNewLossMajorThreshold,
//                        sizeof(table_entry->pstIFMS1000MeasureNewLossMajorThreshold));
//                table_entry->old_pstIFMS1000MeasureNewLossMajorThreshold_len =
//                        table_entry->pstIFMS1000MeasureNewLossMajorThreshold_len;
//                memset( table_entry->pstIFMS1000MeasureNewLossMajorThreshold, 0,
//                        sizeof(table_entry->pstIFMS1000MeasureNewLossMajorThreshold));
//                memcpy( table_entry->pstIFMS1000MeasureNewLossMajorThreshold,
//                        request->requestvb->val.string,
//                        request->requestvb->val_len);
//                table_entry->pstIFMS1000MeasureNewLossMajorThreshold_len =
//                        request->requestvb->val_len;
//                break;
//            case COLUMN_PSTIFMS1000MEASURENEWLOSSMINORTHRESHOLD:
//                memcpy( table_entry->old_pstIFMS1000MeasureNewLossMinorThreshold,
//                        table_entry->pstIFMS1000MeasureNewLossMinorThreshold,
//                        sizeof(table_entry->pstIFMS1000MeasureNewLossMinorThreshold));
//                table_entry->old_pstIFMS1000MeasureNewLossMinorThreshold_len =
//                        table_entry->pstIFMS1000MeasureNewLossMinorThreshold_len;
//                memset( table_entry->pstIFMS1000MeasureNewLossMinorThreshold, 0,
//                        sizeof(table_entry->pstIFMS1000MeasureNewLossMinorThreshold));
//                memcpy( table_entry->pstIFMS1000MeasureNewLossMinorThreshold,
//                        request->requestvb->val.string,
//                        request->requestvb->val_len);
//                table_entry->pstIFMS1000MeasureNewLossMinorThreshold_len =
//                        request->requestvb->val_len;
//                break;
//            case COLUMN_PSTIFMS1000MEASUREOLDLOSSCRITICALTHRESHOLD:
//                memcpy( table_entry->old_pstIFMS1000MeasureOldLossCriticalThreshold,
//                        table_entry->pstIFMS1000MeasureOldLossCriticalThreshold,
//                        sizeof(table_entry->pstIFMS1000MeasureOldLossCriticalThreshold));
//                table_entry->old_pstIFMS1000MeasureOldLossCriticalThreshold_len =
//                        table_entry->pstIFMS1000MeasureOldLossCriticalThreshold_len;
//                memset( table_entry->pstIFMS1000MeasureOldLossCriticalThreshold, 0,
//                        sizeof(table_entry->pstIFMS1000MeasureOldLossCriticalThreshold));
//                memcpy( table_entry->pstIFMS1000MeasureOldLossCriticalThreshold,
//                        request->requestvb->val.string,
//                        request->requestvb->val_len);
//                table_entry->pstIFMS1000MeasureOldLossCriticalThreshold_len =
//                        request->requestvb->val_len;
//                break;
//            case COLUMN_PSTIFMS1000MEASUREOLDLOSSMAJORTHRESHOLD:
//                memcpy( table_entry->old_pstIFMS1000MeasureOldLossMajorThreshold,
//                        table_entry->pstIFMS1000MeasureOldLossMajorThreshold,
//                        sizeof(table_entry->pstIFMS1000MeasureOldLossMajorThreshold));
//                table_entry->old_pstIFMS1000MeasureOldLossMajorThreshold_len =
//                        table_entry->pstIFMS1000MeasureOldLossMajorThreshold_len;
//                memset( table_entry->pstIFMS1000MeasureOldLossMajorThreshold, 0,
//                        sizeof(table_entry->pstIFMS1000MeasureOldLossMajorThreshold));
//                memcpy( table_entry->pstIFMS1000MeasureOldLossMajorThreshold,
//                        request->requestvb->val.string,
//                        request->requestvb->val_len);
//                table_entry->pstIFMS1000MeasureOldLossMajorThreshold_len =
//                        request->requestvb->val_len;
//                break;
//            case COLUMN_PSTIFMS1000MEASUREOLDLOSSMINORTHRESHOLD:
//                memcpy( table_entry->old_pstIFMS1000MeasureOldLossMinorThreshold,
//                        table_entry->pstIFMS1000MeasureOldLossMinorThreshold,
//                        sizeof(table_entry->pstIFMS1000MeasureOldLossMinorThreshold));
//                table_entry->old_pstIFMS1000MeasureOldLossMinorThreshold_len =
//                        table_entry->pstIFMS1000MeasureOldLossMinorThreshold_len;
//                memset( table_entry->pstIFMS1000MeasureOldLossMinorThreshold, 0,
//                        sizeof(table_entry->pstIFMS1000MeasureOldLossMinorThreshold));
//                memcpy( table_entry->pstIFMS1000MeasureOldLossMinorThreshold,
//                        request->requestvb->val.string,
//                        request->requestvb->val_len);
//                table_entry->pstIFMS1000MeasureOldLossMinorThreshold_len =
//                        request->requestvb->val_len;
//                break;
//            case COLUMN_PSTIFMS1000MEASUREEVENTPOSITIONCHANGETHRESHOLD:
////                memcpy( table_entry->old_pstIFMS1000MeasureTempHighThreshold,
////                        table_entry->pstIFMS1000MeasureTempHighThreshold,
////                        sizeof(table_entry->pstIFMS1000MeasureTempHighThreshold));
////                table_entry->old_pstIFMS1000MeasureTempHighThreshold_len =
////                        table_entry->pstIFMS1000MeasureTempHighThreshold_len;
//                memset( table_entry->pstIFMS1000MeasureEventPositionChangeThreshold, 0,
//                        sizeof(table_entry->pstIFMS1000MeasureEventPositionChangeThreshold));
//                memcpy( table_entry->pstIFMS1000MeasureEventPositionChangeThreshold,
//                        request->requestvb->val.string,
//                        request->requestvb->val_len);
//                table_entry->pstIFMS1000MeasureEventPositionChangeThreshold_len =
//                        request->requestvb->val_len;
//                break;
//            case COLUMN_PSTIFMS1000MEASURERESERVED2:
////                memcpy( table_entry->old_pstIFMS1000MeasureTempLowThreshold,
////                        table_entry->pstIFMS1000MeasureTempLowThreshold,
////                        sizeof(table_entry->pstIFMS1000MeasureTempLowThreshold));
////                table_entry->old_pstIFMS1000MeasureTempLowThreshold_len =
////                        table_entry->pstIFMS1000MeasureTempLowThreshold_len;
//                memset( table_entry->pstIFMS1000MeasureReserved2, 0,
//                        sizeof(table_entry->pstIFMS1000MeasureReserved2));
//                memcpy( table_entry->pstIFMS1000MeasureReserved2,
//                        request->requestvb->val.string,
//                        request->requestvb->val_len);
//                table_entry->pstIFMS1000MeasureReserved2_len =
//                        request->requestvb->val_len;
//                break;
//            case COLUMN_PSTIFMS1000MEASURENUMBERSORSTOREDEACHCHANNEL:
//                memcpy( table_entry->old_pstIFMS1000MeasureNumberSORStoredEachChannel,
//                        table_entry->pstIFMS1000MeasureNumberSORStoredEachChannel,
//                        sizeof(table_entry->pstIFMS1000MeasureNumberSORStoredEachChannel));
//                table_entry->old_pstIFMS1000MeasureNumberSORStoredEachChannel_len =
//                        table_entry->pstIFMS1000MeasureNumberSORStoredEachChannel_len;
//                memset( table_entry->pstIFMS1000MeasureNumberSORStoredEachChannel, 0,
//                        sizeof(table_entry->pstIFMS1000MeasureNumberSORStoredEachChannel));
//                memcpy( table_entry->pstIFMS1000MeasureNumberSORStoredEachChannel,
//                        request->requestvb->val.string,
//                        request->requestvb->val_len);
//                table_entry->pstIFMS1000MeasureNumberSORStoredEachChannel_len =
//                        request->requestvb->val_len;
//                break;
//            }
//        }
        break;

    case MODE_SET_UNDO:
//        for (request=requests; request; request=request->next) {
//            if (request->processed)
//                continue;

//            table_entry = (struct pstIFMS1000MeasureTable_entry *)
//                              netsnmp_tdata_extract_entry(request);
//            table_row   =     netsnmp_tdata_extract_row(  request);
//            table_data  =     netsnmp_tdata_extract_table(request);
//            table_info  =     netsnmp_extract_table_info( request);
    
//            switch (table_info->colnum) {
//            case COLUMN_PSTIFMS1000MEASURESTARTPOSITION:
//                memcpy( table_entry->pstIFMS1000MeasureStartPosition,
//                        table_entry->old_pstIFMS1000MeasureStartPosition,
//                        sizeof(table_entry->pstIFMS1000MeasureStartPosition));
//                memset( table_entry->old_pstIFMS1000MeasureStartPosition, 0,
//                        sizeof(table_entry->pstIFMS1000MeasureStartPosition));
//                table_entry->pstIFMS1000MeasureStartPosition_len =
//                        table_entry->old_pstIFMS1000MeasureStartPosition_len;
//                break;
//            case COLUMN_PSTIFMS1000MEASUREENDPOSITION:
//                memcpy( table_entry->pstIFMS1000MeasureEndPosition,
//                        table_entry->old_pstIFMS1000MeasureEndPosition,
//                        sizeof(table_entry->pstIFMS1000MeasureEndPosition));
//                memset( table_entry->old_pstIFMS1000MeasureEndPosition, 0,
//                        sizeof(table_entry->pstIFMS1000MeasureEndPosition));
//                table_entry->pstIFMS1000MeasureEndPosition_len =
//                        table_entry->old_pstIFMS1000MeasureEndPosition_len;
//                break;
//            case COLUMN_PSTIFMS1000MEASUREREFINDEX:
//                memcpy( table_entry->pstIFMS1000MeasureRefIndex,
//                        table_entry->old_pstIFMS1000MeasureRefIndex,
//                        sizeof(table_entry->pstIFMS1000MeasureRefIndex));
//                memset( table_entry->old_pstIFMS1000MeasureRefIndex, 0,
//                        sizeof(table_entry->pstIFMS1000MeasureRefIndex));
//                table_entry->pstIFMS1000MeasureRefIndex_len =
//                        table_entry->old_pstIFMS1000MeasureRefIndex_len;
//                break;
//            case COLUMN_PSTIFMS1000MEASURERESOLUTION:
//                memcpy( table_entry->pstIFMS1000MeasureResolution,
//                        table_entry->old_pstIFMS1000MeasureResolution,
//                        sizeof(table_entry->pstIFMS1000MeasureResolution));
//                memset( table_entry->old_pstIFMS1000MeasureResolution, 0,
//                        sizeof(table_entry->pstIFMS1000MeasureResolution));
//                table_entry->pstIFMS1000MeasureResolution_len =
//                        table_entry->old_pstIFMS1000MeasureResolution_len;
//                break;
//            case COLUMN_PSTIFMS1000MEASUREACTION:
//                table_entry->pstIFMS1000MeasureAction     = table_entry->old_pstIFMS1000MeasureAction;
//                table_entry->old_pstIFMS1000MeasureAction = 0;
//                break;
//            case COLUMN_PSTIFMS1000MEASUREPULSEWIDTH:
//                memcpy( table_entry->pstIFMS1000MeasurePulseWidth,
//                        table_entry->old_pstIFMS1000MeasurePulseWidth,
//                        sizeof(table_entry->pstIFMS1000MeasurePulseWidth));
//                memset( table_entry->old_pstIFMS1000MeasurePulseWidth, 0,
//                        sizeof(table_entry->pstIFMS1000MeasurePulseWidth));
//                table_entry->pstIFMS1000MeasurePulseWidth_len =
//                        table_entry->old_pstIFMS1000MeasurePulseWidth_len;
//                break;
//            case COLUMN_PSTIFMS1000MEASURETIME:
//                table_entry->pstIFMS1000MeasureTime     = table_entry->old_pstIFMS1000MeasureTime;
//                table_entry->old_pstIFMS1000MeasureTime = 0;
//                break;
//            case COLUMN_PSTIFMS1000MEASURETLOS:
//                memcpy( table_entry->pstIFMS1000MeasureTLOS,
//                        table_entry->old_pstIFMS1000MeasureTLOS,
//                        sizeof(table_entry->pstIFMS1000MeasureTLOS));
//                memset( table_entry->old_pstIFMS1000MeasureTLOS, 0,
//                        sizeof(table_entry->pstIFMS1000MeasureTLOS));
//                table_entry->pstIFMS1000MeasureTLOS_len =
//                        table_entry->old_pstIFMS1000MeasureTLOS_len;
//                break;
//            case COLUMN_PSTIFMS1000MEASURETREF:
//                memcpy( table_entry->pstIFMS1000MeasureTREF,
//                        table_entry->old_pstIFMS1000MeasureTREF,
//                        sizeof(table_entry->pstIFMS1000MeasureTREF));
//                memset( table_entry->old_pstIFMS1000MeasureTREF, 0,
//                        sizeof(table_entry->pstIFMS1000MeasureTREF));
//                table_entry->pstIFMS1000MeasureTREF_len =
//                        table_entry->old_pstIFMS1000MeasureTREF_len;
//                break;
//            case COLUMN_PSTIFMS1000MEASUREFIBERLENGTHCHANGETHRESHOLD:
//                memcpy( table_entry->pstIFMS1000MeasureFiberLengthChangeThreshold,
//                        table_entry->old_pstIFMS1000MeasureFiberLengthChangeThreshold,
//                        sizeof(table_entry->pstIFMS1000MeasureFiberLengthChangeThreshold));
//                memset( table_entry->old_pstIFMS1000MeasureFiberLengthChangeThreshold, 0,
//                        sizeof(table_entry->pstIFMS1000MeasureFiberLengthChangeThreshold));
//                table_entry->pstIFMS1000MeasureFiberLengthChangeThreshold_len =
//                        table_entry->old_pstIFMS1000MeasureFiberLengthChangeThreshold_len;
//                break;
//            case COLUMN_PSTIFMS1000MEASUREENDTOENDLOSSHIGHTHRESHOLD:
//                memcpy( table_entry->pstIFMS1000MeasureEndToEndLossHighThreshold,
//                        table_entry->old_pstIFMS1000MeasureEndToEndLossHighThreshold,
//                        sizeof(table_entry->pstIFMS1000MeasureEndToEndLossHighThreshold));
//                memset( table_entry->old_pstIFMS1000MeasureEndToEndLossHighThreshold, 0,
//                        sizeof(table_entry->pstIFMS1000MeasureEndToEndLossHighThreshold));
//                table_entry->pstIFMS1000MeasureEndToEndLossHighThreshold_len =
//                        table_entry->old_pstIFMS1000MeasureEndToEndLossHighThreshold_len;
//                break;
//            case COLUMN_PSTIFMS1000MEASUREENDTOENDLOSSMIDDLETHRESHOLD:
//                memcpy( table_entry->pstIFMS1000MeasureEndToEndLossMiddleThreshold,
//                        table_entry->old_pstIFMS1000MeasureEndToEndLossMiddleThreshold,
//                        sizeof(table_entry->pstIFMS1000MeasureEndToEndLossMiddleThreshold));
//                memset( table_entry->old_pstIFMS1000MeasureEndToEndLossMiddleThreshold, 0,
//                        sizeof(table_entry->pstIFMS1000MeasureEndToEndLossMiddleThreshold));
//                table_entry->pstIFMS1000MeasureEndToEndLossMiddleThreshold_len =
//                        table_entry->old_pstIFMS1000MeasureEndToEndLossMiddleThreshold_len;
//                break;
//            case COLUMN_PSTIFMS1000MEASUREENDTOENDLOSSLOWTHRESHOLD:
//                memcpy( table_entry->pstIFMS1000MeasureEndToEndLossLowThreshold,
//                        table_entry->old_pstIFMS1000MeasureEndToEndLossLowThreshold,
//                        sizeof(table_entry->pstIFMS1000MeasureEndToEndLossLowThreshold));
//                memset( table_entry->old_pstIFMS1000MeasureEndToEndLossLowThreshold, 0,
//                        sizeof(table_entry->pstIFMS1000MeasureEndToEndLossLowThreshold));
//                table_entry->pstIFMS1000MeasureEndToEndLossLowThreshold_len =
//                        table_entry->old_pstIFMS1000MeasureEndToEndLossLowThreshold_len;
//                break;
//            case COLUMN_PSTIFMS1000MEASURENEWLOSSCRITICALTHRESHOLD:
//                memcpy( table_entry->pstIFMS1000MeasureNewLossCriticalThreshold,
//                        table_entry->old_pstIFMS1000MeasureNewLossCriticalThreshold,
//                        sizeof(table_entry->pstIFMS1000MeasureNewLossCriticalThreshold));
//                memset( table_entry->old_pstIFMS1000MeasureNewLossCriticalThreshold, 0,
//                        sizeof(table_entry->pstIFMS1000MeasureNewLossCriticalThreshold));
//                table_entry->pstIFMS1000MeasureNewLossCriticalThreshold_len =
//                        table_entry->old_pstIFMS1000MeasureNewLossCriticalThreshold_len;
//                break;
//            case COLUMN_PSTIFMS1000MEASURENEWLOSSMAJORTHRESHOLD:
//                memcpy( table_entry->pstIFMS1000MeasureNewLossMajorThreshold,
//                        table_entry->old_pstIFMS1000MeasureNewLossMajorThreshold,
//                        sizeof(table_entry->pstIFMS1000MeasureNewLossMajorThreshold));
//                memset( table_entry->old_pstIFMS1000MeasureNewLossMajorThreshold, 0,
//                        sizeof(table_entry->pstIFMS1000MeasureNewLossMajorThreshold));
//                table_entry->pstIFMS1000MeasureNewLossMajorThreshold_len =
//                        table_entry->old_pstIFMS1000MeasureNewLossMajorThreshold_len;
//                break;
//            case COLUMN_PSTIFMS1000MEASURENEWLOSSMINORTHRESHOLD:
//                memcpy( table_entry->pstIFMS1000MeasureNewLossMinorThreshold,
//                        table_entry->old_pstIFMS1000MeasureNewLossMinorThreshold,
//                        sizeof(table_entry->pstIFMS1000MeasureNewLossMinorThreshold));
//                memset( table_entry->old_pstIFMS1000MeasureNewLossMinorThreshold, 0,
//                        sizeof(table_entry->pstIFMS1000MeasureNewLossMinorThreshold));
//                table_entry->pstIFMS1000MeasureNewLossMinorThreshold_len =
//                        table_entry->old_pstIFMS1000MeasureNewLossMinorThreshold_len;
//                break;
//            case COLUMN_PSTIFMS1000MEASUREOLDLOSSCRITICALTHRESHOLD:
//                memcpy( table_entry->pstIFMS1000MeasureOldLossCriticalThreshold,
//                        table_entry->old_pstIFMS1000MeasureOldLossCriticalThreshold,
//                        sizeof(table_entry->pstIFMS1000MeasureOldLossCriticalThreshold));
//                memset( table_entry->old_pstIFMS1000MeasureOldLossCriticalThreshold, 0,
//                        sizeof(table_entry->pstIFMS1000MeasureOldLossCriticalThreshold));
//                table_entry->pstIFMS1000MeasureOldLossCriticalThreshold_len =
//                        table_entry->old_pstIFMS1000MeasureOldLossCriticalThreshold_len;
//                break;
//            case COLUMN_PSTIFMS1000MEASUREOLDLOSSMAJORTHRESHOLD:
//                memcpy( table_entry->pstIFMS1000MeasureOldLossMajorThreshold,
//                        table_entry->old_pstIFMS1000MeasureOldLossMajorThreshold,
//                        sizeof(table_entry->pstIFMS1000MeasureOldLossMajorThreshold));
//                memset( table_entry->old_pstIFMS1000MeasureOldLossMajorThreshold, 0,
//                        sizeof(table_entry->pstIFMS1000MeasureOldLossMajorThreshold));
//                table_entry->pstIFMS1000MeasureOldLossMajorThreshold_len =
//                        table_entry->old_pstIFMS1000MeasureOldLossMajorThreshold_len;
//                break;
//            case COLUMN_PSTIFMS1000MEASUREOLDLOSSMINORTHRESHOLD:
//                memcpy( table_entry->pstIFMS1000MeasureOldLossMinorThreshold,
//                        table_entry->old_pstIFMS1000MeasureOldLossMinorThreshold,
//                        sizeof(table_entry->pstIFMS1000MeasureOldLossMinorThreshold));
//                memset( table_entry->old_pstIFMS1000MeasureOldLossMinorThreshold, 0,
//                        sizeof(table_entry->pstIFMS1000MeasureOldLossMinorThreshold));
//                table_entry->pstIFMS1000MeasureOldLossMinorThreshold_len =
//                        table_entry->old_pstIFMS1000MeasureOldLossMinorThreshold_len;
//                break;
//            case COLUMN_PSTIFMS1000MEASUREEVENTPOSITIONCHANGETHRESHOLD:

//                break;
//            case COLUMN_PSTIFMS1000MEASURERESERVED2:
//                break;
//            case COLUMN_PSTIFMS1000MEASURENUMBERSORSTOREDEACHCHANNEL:
//                memcpy( table_entry->pstIFMS1000MeasureNumberSORStoredEachChannel,
//                        table_entry->old_pstIFMS1000MeasureNumberSORStoredEachChannel,
//                        sizeof(table_entry->pstIFMS1000MeasureNumberSORStoredEachChannel));
//                memset( table_entry->old_pstIFMS1000MeasureNumberSORStoredEachChannel, 0,
//                        sizeof(table_entry->pstIFMS1000MeasureNumberSORStoredEachChannel));
//                table_entry->pstIFMS1000MeasureNumberSORStoredEachChannel_len =
//                        table_entry->old_pstIFMS1000MeasureNumberSORStoredEachChannel_len;
//                break;
//            }
//        }
        break;

    case MODE_SET_COMMIT:
        break;
    }
    return SNMP_ERR_NOERROR;
}

/** Initialize the pstIFMS1000FingerTable table by defining its contents and how it's structured */
void
QPSTProduct::initialize_table_pstIFMS1000FingerTable(void)
{
    const oid pstIFMS1000FingerTable_oid[] = {1,3,6,1,4,1,48391,3,5,3};
    const size_t pstIFMS1000FingerTable_oid_len   = OID_LENGTH(pstIFMS1000FingerTable_oid);
    netsnmp_handler_registration    *reg;
    netsnmp_tdata                   *table_data;
    netsnmp_table_registration_info *table_info;

    DEBUGMSGTL(("pstIFMS1000:init", "initializing table pstIFMS1000FingerTable\n"));

    reg = netsnmp_create_handler_registration(
              "pstIFMS1000FingerTable",     pstIFMS1000FingerTable_handler,
              pstIFMS1000FingerTable_oid, pstIFMS1000FingerTable_oid_len,
              HANDLER_CAN_RWRITE
              );

    table_data = netsnmp_tdata_create_table( "pstIFMS1000FingerTable", 0 );
    if (NULL == table_data) {
        snmp_log(LOG_ERR,"error creating tdata table for pstIFMS1000FingerTable\n");
        return;
    }
    table_info = SNMP_MALLOC_TYPEDEF( netsnmp_table_registration_info );
    if (NULL == table_info) {
        snmp_log(LOG_ERR,"error creating table info for pstIFMS1000FingerTable\n");
        return;
    }
    netsnmp_table_helper_add_indexes(table_info,
                           ASN_INTEGER,  /* index: pstIFMS1000FTPortNum */
                           0);

    table_info->min_column = COLUMN_PSTIFMS1000FTPORTNUM;
    table_info->max_column = COLUMN_PSTIFMS1000FINGERCURRENTFILENAME;
    
    netsnmp_tdata_register( reg, table_data, table_info );

    /* Initialise the contents of the table here */
}

//    /* Typical data structure for a row entry */
//struct pstIFMS1000FingerTable_entry {
//    /* Index values */
//    long pstIFMS1000FTPortNum;

//    /* Column values */
//    long pstIFMS1000FTPortNum;
//    char pstIFMS1000FingerStartPosition[NNN];
//    size_t pstIFMS1000FingerStartPosition_len;
//    char old_pstIFMS1000FingerStartPosition[NNN];
//    size_t old_pstIFMS1000FingerStartPosition_len;
//    char pstIFMS1000FingerEndPosition[NNN];
//    size_t pstIFMS1000FingerEndPosition_len;
//    char old_pstIFMS1000FingerEndPosition[NNN];
//    size_t old_pstIFMS1000FingerEndPosition_len;
//    char pstIFMS1000FingerRefIndex[NNN];
//    size_t pstIFMS1000FingerRefIndex_len;
//    char old_pstIFMS1000FingerRefIndex[NNN];
//    size_t old_pstIFMS1000FingerRefIndex_len;
//    char pstIFMS1000FingerResolution[NNN];
//    size_t pstIFMS1000FingerResolution_len;
//    char old_pstIFMS1000FingerResolution[NNN];
//    size_t old_pstIFMS1000FingerResolution_len;
//    char pstIFMS1000FingerCreateTime[NNN];
//    size_t pstIFMS1000FingerCreateTime_len;
//    long pstIFMS1000FingerFileStatus;
//    long pstIFMS1000FingerAction;
//    long old_pstIFMS1000FingerAction;
//    long pstIFMS1000FingerActionStatus;
//    char pstIFMS1000FingerSavedFileName[NNN];
//    size_t pstIFMS1000FingerSavedFileName_len;
//    char pstIFMS1000FingerCurrentFileName[NNN];
//    size_t pstIFMS1000FingerCurrentFileName_len;

//    int   valid;
//};

/* create a new row in the table */
static netsnmp_tdata_row *
pstIFMS1000FingerTable_createEntry(netsnmp_tdata *table_data
                 , long  pstIFMS1000FTPortNum
                ) {
    struct pstIFMS1000FingerTable_entry *entry;
    netsnmp_tdata_row *row;

    entry = SNMP_MALLOC_TYPEDEF(struct pstIFMS1000FingerTable_entry);
    if (!entry)
        return NULL;

    row = netsnmp_tdata_create_row();
    if (!row) {
        SNMP_FREE(entry);
        return NULL;
    }
    row->data = entry;

    DEBUGMSGT(("pstIFMS1000FingerTable:entry:create", "row 0x%x\n", (uintptr_t)row));
    entry->pstIFMS1000FTPortNum = pstIFMS1000FTPortNum;
    netsnmp_tdata_row_add_index( row, ASN_INTEGER,
                                 &(entry->pstIFMS1000FTPortNum),
                                 sizeof(entry->pstIFMS1000FTPortNum));
    if (table_data)
        netsnmp_tdata_add_row( table_data, row );
    return row;
}

/* remove a row from the table */
static void
pstIFMS1000FingerTable_removeEntry(netsnmp_tdata     *table_data, 
                 netsnmp_tdata_row *row) {
    struct pstIFMS1000FingerTable_entry *entry;

    if (!row)
        return;    /* Nothing to remove */

    DEBUGMSGT(("pstIFMS1000FingerTable:entry:remove", "row 0x%x\n", (uintptr_t)row));

    entry = (struct pstIFMS1000FingerTable_entry *)row->data;
    SNMP_FREE( entry );   /* XXX - release any other internal resources */

    if (table_data)
        netsnmp_tdata_remove_and_delete_row( table_data, row );
    else
        netsnmp_tdata_delete_row( row );    
}


/** handles requests for the pstIFMS1000FingerTable table */
int
QPSTProduct::pstIFMS1000FingerTable_handler(
    netsnmp_mib_handler               *handler,
    netsnmp_handler_registration      *reginfo,
    netsnmp_agent_request_info        *reqinfo,
    netsnmp_request_info              *requests) {

    netsnmp_request_info       *request;
    netsnmp_table_request_info *table_info;
    netsnmp_tdata              *table_data;
    netsnmp_tdata_row          *table_row;
    struct pstIFMS1000FingerTable_entry          *table_entry;
    int                         ret;

    DEBUGMSGTL(("pstIFMS1000:handler", "Processing request (%d)\n", reqinfo->mode));

    switch (reqinfo->mode) {
        /*
         * Read-support (also covers GetNext requests)
         */
    case MODE_GET:
        for (request=requests; request; request=request->next) {
            if (request->processed)
                continue;

            table_entry = (struct pstIFMS1000FingerTable_entry *)
                              netsnmp_tdata_extract_entry(request);
            table_info  =     netsnmp_extract_table_info( request);
    
            switch (table_info->colnum) {
            case COLUMN_PSTIFMS1000FTPORTNUM:
                if ( !table_entry ) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_NOSUCHINSTANCE);
                    continue;
                }
                snmp_set_var_typed_integer( request->requestvb, ASN_INTEGER,
                                            table_entry->pstIFMS1000FTPortNum);
                break;
            case COLUMN_PSTIFMS1000FINGERSTARTPOSITION:
                if ( !table_entry ) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_NOSUCHINSTANCE);
                    continue;
                }
                snmp_set_var_typed_value( request->requestvb, ASN_OCTET_STR,
                                          table_entry->pstIFMS1000FingerStartPosition,
                                          table_entry->pstIFMS1000FingerStartPosition_len);
                break;
            case COLUMN_PSTIFMS1000FINGERENDPOSITION:
                if ( !table_entry ) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_NOSUCHINSTANCE);
                    continue;
                }
                snmp_set_var_typed_value( request->requestvb, ASN_OCTET_STR,
                                          table_entry->pstIFMS1000FingerEndPosition,
                                          table_entry->pstIFMS1000FingerEndPosition_len);
                break;
            case COLUMN_PSTIFMS1000FINGERREFINDEX:
                if ( !table_entry ) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_NOSUCHINSTANCE);
                    continue;
                }
                snmp_set_var_typed_value( request->requestvb, ASN_OCTET_STR,
                                          table_entry->pstIFMS1000FingerRefIndex,
                                          table_entry->pstIFMS1000FingerRefIndex_len);
                break;
            case COLUMN_PSTIFMS1000FINGERRESOLUTION:
                if ( !table_entry ) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_NOSUCHINSTANCE);
                    continue;
                }
                snmp_set_var_typed_value( request->requestvb, ASN_OCTET_STR,
                                          table_entry->pstIFMS1000FingerResolution,
                                          table_entry->pstIFMS1000FingerResolution_len);
                break;
            case COLUMN_PSTIFMS1000FINGERCREATETIME:
                if ( !table_entry ) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_NOSUCHINSTANCE);
                    continue;
                }
                snmp_set_var_typed_value( request->requestvb, ASN_OCTET_STR,
                                          table_entry->pstIFMS1000FingerCreateTime,
                                          table_entry->pstIFMS1000FingerCreateTime_len);
                break;
            case COLUMN_PSTIFMS1000FINGERFILESTATUS:
                if ( !table_entry ) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_NOSUCHINSTANCE);
                    continue;
                }
                snmp_set_var_typed_integer( request->requestvb, ASN_INTEGER,
                                            table_entry->pstIFMS1000FingerFileStatus);
                break;
            case COLUMN_PSTIFMS1000FINGERACTION:
                if ( !table_entry ) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_NOSUCHINSTANCE);
                    continue;
                }
                snmp_set_var_typed_integer( request->requestvb, ASN_INTEGER,
                                            table_entry->pstIFMS1000FingerAction);
                break;
            case COLUMN_PSTIFMS1000FINGERACTIONSTATUS:
                if ( !table_entry ) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_NOSUCHINSTANCE);
                    continue;
                }
                snmp_set_var_typed_integer( request->requestvb, ASN_INTEGER,
                                            table_entry->pstIFMS1000FingerActionStatus);
                break;
            case COLUMN_PSTIFMS1000FINGERSAVEDFILENAME:
                if ( !table_entry ) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_NOSUCHINSTANCE);
                    continue;
                }
                snmp_set_var_typed_value( request->requestvb, ASN_OCTET_STR,
                                          table_entry->pstIFMS1000FingerSavedFileName,
                                          table_entry->pstIFMS1000FingerSavedFileName_len);
                break;
            case COLUMN_PSTIFMS1000FINGERCURRENTFILENAME:
                if ( !table_entry ) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_NOSUCHINSTANCE);
                    continue;
                }
                snmp_set_var_typed_value( request->requestvb, ASN_OCTET_STR,
                                          table_entry->pstIFMS1000FingerCurrentFileName,
                                          table_entry->pstIFMS1000FingerCurrentFileName_len);
                break;
            default:
                netsnmp_set_request_error(reqinfo, request,
                                          SNMP_NOSUCHOBJECT);
                break;
            }
        }
        break;

        /*
         * Write-support
         */
    case MODE_SET_RESERVE1:
        for (request=requests; request; request=request->next) {
            if (request->processed)
                continue;

            table_entry = (struct pstIFMS1000FingerTable_entry *)
                              netsnmp_tdata_extract_entry(request);
            table_info  =     netsnmp_extract_table_info( request);
    
            switch (table_info->colnum) {
            case COLUMN_PSTIFMS1000FINGERSTARTPOSITION:
	        /* or possibly 'netsnmp_check_vb_type_and_size' */
                ret = netsnmp_check_vb_type_and_max_size(
                          request->requestvb, ASN_OCTET_STR, sizeof(table_entry->pstIFMS1000FingerStartPosition));
                if ( ret != SNMP_ERR_NOERROR ) {
                    netsnmp_set_request_error( reqinfo, request, ret );
                    return SNMP_ERR_NOERROR;
                }
                break;
            case COLUMN_PSTIFMS1000FINGERENDPOSITION:
	        /* or possibly 'netsnmp_check_vb_type_and_size' */
                ret = netsnmp_check_vb_type_and_max_size(
                          request->requestvb, ASN_OCTET_STR, sizeof(table_entry->pstIFMS1000FingerEndPosition));
                if ( ret != SNMP_ERR_NOERROR ) {
                    netsnmp_set_request_error( reqinfo, request, ret );
                    return SNMP_ERR_NOERROR;
                }
                break;
            case COLUMN_PSTIFMS1000FINGERREFINDEX:
	        /* or possibly 'netsnmp_check_vb_type_and_size' */
                ret = netsnmp_check_vb_type_and_max_size(
                          request->requestvb, ASN_OCTET_STR, sizeof(table_entry->pstIFMS1000FingerRefIndex));
                if ( ret != SNMP_ERR_NOERROR ) {
                    netsnmp_set_request_error( reqinfo, request, ret );
                    return SNMP_ERR_NOERROR;
                }
                break;
            case COLUMN_PSTIFMS1000FINGERRESOLUTION:
	        /* or possibly 'netsnmp_check_vb_type_and_size' */
                ret = netsnmp_check_vb_type_and_max_size(
                          request->requestvb, ASN_OCTET_STR, sizeof(table_entry->pstIFMS1000FingerResolution));
                if ( ret != SNMP_ERR_NOERROR ) {
                    netsnmp_set_request_error( reqinfo, request, ret );
                    return SNMP_ERR_NOERROR;
                }
                break;
            case COLUMN_PSTIFMS1000FINGERACTION:
                /* or possibly 'netsnmp_check_vb_int_range' */
                ret = netsnmp_check_vb_int( request->requestvb );
                if ( ret != SNMP_ERR_NOERROR ) {
                    netsnmp_set_request_error( reqinfo, request, ret );
                    return SNMP_ERR_NOERROR;
                }
                break;
            default:
                netsnmp_set_request_error( reqinfo, request,
                                           SNMP_ERR_NOTWRITABLE );
                return SNMP_ERR_NOERROR;
            }
        }
        break;

    case MODE_SET_RESERVE2:
        break;

    case MODE_SET_FREE:
        break;

    case MODE_SET_ACTION:
        for (request=requests; request; request=request->next) {
            if (request->processed)
                continue;

            table_entry = (struct pstIFMS1000FingerTable_entry *)
                              netsnmp_tdata_extract_entry(request);
            table_info  =     netsnmp_extract_table_info( request);
    
            switch (table_info->colnum) {
            case COLUMN_PSTIFMS1000FINGERSTARTPOSITION:
                memcpy( table_entry->old_pstIFMS1000FingerStartPosition,
                        table_entry->pstIFMS1000FingerStartPosition,
                        sizeof(table_entry->pstIFMS1000FingerStartPosition));
                table_entry->old_pstIFMS1000FingerStartPosition_len =
                        table_entry->pstIFMS1000FingerStartPosition_len;
                memset( table_entry->pstIFMS1000FingerStartPosition, 0,
                        sizeof(table_entry->pstIFMS1000FingerStartPosition));
                memcpy( table_entry->pstIFMS1000FingerStartPosition,
                        request->requestvb->val.string,
                        request->requestvb->val_len);
                table_entry->pstIFMS1000FingerStartPosition_len =
                        request->requestvb->val_len;
                break;
            case COLUMN_PSTIFMS1000FINGERENDPOSITION:
                memcpy( table_entry->old_pstIFMS1000FingerEndPosition,
                        table_entry->pstIFMS1000FingerEndPosition,
                        sizeof(table_entry->pstIFMS1000FingerEndPosition));
                table_entry->old_pstIFMS1000FingerEndPosition_len =
                        table_entry->pstIFMS1000FingerEndPosition_len;
                memset( table_entry->pstIFMS1000FingerEndPosition, 0,
                        sizeof(table_entry->pstIFMS1000FingerEndPosition));
                memcpy( table_entry->pstIFMS1000FingerEndPosition,
                        request->requestvb->val.string,
                        request->requestvb->val_len);
                table_entry->pstIFMS1000FingerEndPosition_len =
                        request->requestvb->val_len;
                break;
            case COLUMN_PSTIFMS1000FINGERREFINDEX:
                memcpy( table_entry->old_pstIFMS1000FingerRefIndex,
                        table_entry->pstIFMS1000FingerRefIndex,
                        sizeof(table_entry->pstIFMS1000FingerRefIndex));
                table_entry->old_pstIFMS1000FingerRefIndex_len =
                        table_entry->pstIFMS1000FingerRefIndex_len;
                memset( table_entry->pstIFMS1000FingerRefIndex, 0,
                        sizeof(table_entry->pstIFMS1000FingerRefIndex));
                memcpy( table_entry->pstIFMS1000FingerRefIndex,
                        request->requestvb->val.string,
                        request->requestvb->val_len);
                table_entry->pstIFMS1000FingerRefIndex_len =
                        request->requestvb->val_len;
                break;
            case COLUMN_PSTIFMS1000FINGERRESOLUTION:
                memcpy( table_entry->old_pstIFMS1000FingerResolution,
                        table_entry->pstIFMS1000FingerResolution,
                        sizeof(table_entry->pstIFMS1000FingerResolution));
                table_entry->old_pstIFMS1000FingerResolution_len =
                        table_entry->pstIFMS1000FingerResolution_len;
                memset( table_entry->pstIFMS1000FingerResolution, 0,
                        sizeof(table_entry->pstIFMS1000FingerResolution));
                memcpy( table_entry->pstIFMS1000FingerResolution,
                        request->requestvb->val.string,
                        request->requestvb->val_len);
                table_entry->pstIFMS1000FingerResolution_len =
                        request->requestvb->val_len;
                break;
            case COLUMN_PSTIFMS1000FINGERACTION:
                table_entry->old_pstIFMS1000FingerAction = table_entry->pstIFMS1000FingerAction;
                table_entry->pstIFMS1000FingerAction     = *request->requestvb->val.integer;
                break;
            }
        }
        break;

    case MODE_SET_UNDO:
        for (request=requests; request; request=request->next) {
            if (request->processed)
                continue;

            table_entry = (struct pstIFMS1000FingerTable_entry *)
                              netsnmp_tdata_extract_entry(request);
            table_row   =     netsnmp_tdata_extract_row(  request);
            table_data  =     netsnmp_tdata_extract_table(request);
            table_info  =     netsnmp_extract_table_info( request);
    
            switch (table_info->colnum) {
            case COLUMN_PSTIFMS1000FINGERSTARTPOSITION:
                memcpy( table_entry->pstIFMS1000FingerStartPosition,
                        table_entry->old_pstIFMS1000FingerStartPosition,
                        sizeof(table_entry->pstIFMS1000FingerStartPosition));
                memset( table_entry->old_pstIFMS1000FingerStartPosition, 0,
                        sizeof(table_entry->pstIFMS1000FingerStartPosition));
                table_entry->pstIFMS1000FingerStartPosition_len =
                        table_entry->old_pstIFMS1000FingerStartPosition_len;
                break;
            case COLUMN_PSTIFMS1000FINGERENDPOSITION:
                memcpy( table_entry->pstIFMS1000FingerEndPosition,
                        table_entry->old_pstIFMS1000FingerEndPosition,
                        sizeof(table_entry->pstIFMS1000FingerEndPosition));
                memset( table_entry->old_pstIFMS1000FingerEndPosition, 0,
                        sizeof(table_entry->pstIFMS1000FingerEndPosition));
                table_entry->pstIFMS1000FingerEndPosition_len =
                        table_entry->old_pstIFMS1000FingerEndPosition_len;
                break;
            case COLUMN_PSTIFMS1000FINGERREFINDEX:
                memcpy( table_entry->pstIFMS1000FingerRefIndex,
                        table_entry->old_pstIFMS1000FingerRefIndex,
                        sizeof(table_entry->pstIFMS1000FingerRefIndex));
                memset( table_entry->old_pstIFMS1000FingerRefIndex, 0,
                        sizeof(table_entry->pstIFMS1000FingerRefIndex));
                table_entry->pstIFMS1000FingerRefIndex_len =
                        table_entry->old_pstIFMS1000FingerRefIndex_len;
                break;
            case COLUMN_PSTIFMS1000FINGERRESOLUTION:
                memcpy( table_entry->pstIFMS1000FingerResolution,
                        table_entry->old_pstIFMS1000FingerResolution,
                        sizeof(table_entry->pstIFMS1000FingerResolution));
                memset( table_entry->old_pstIFMS1000FingerResolution, 0,
                        sizeof(table_entry->pstIFMS1000FingerResolution));
                table_entry->pstIFMS1000FingerResolution_len =
                        table_entry->old_pstIFMS1000FingerResolution_len;
                break;
            case COLUMN_PSTIFMS1000FINGERACTION:
                table_entry->pstIFMS1000FingerAction     = table_entry->old_pstIFMS1000FingerAction;
                table_entry->old_pstIFMS1000FingerAction = 0;
                break;
            }
        }
        break;

    case MODE_SET_COMMIT:
        break;
    }
    return SNMP_ERR_NOERROR;
}
#if 0
/** Initialize the pstIFMS1000DiffTotalTable table by defining its contents and how it's structured */
void
QPSTProduct::initialize_table_pstIFMS1000DiffTotalTable(void)
{
    const oid pstIFMS1000DiffTotalTable_oid[] = {1,3,6,1,4,1,48391,3,5,4,1};
    const size_t pstIFMS1000DiffTotalTable_oid_len   = OID_LENGTH(pstIFMS1000DiffTotalTable_oid);
    netsnmp_handler_registration    *reg;
    netsnmp_tdata                   *table_data;
    netsnmp_table_registration_info *table_info;

    DEBUGMSGTL(("pstIFMS1000:init", "initializing table pstIFMS1000DiffTotalTable\n"));

    reg = netsnmp_create_handler_registration(
              "pstIFMS1000DiffTotalTable",     pstIFMS1000DiffTotalTable_handler,
              pstIFMS1000DiffTotalTable_oid, pstIFMS1000DiffTotalTable_oid_len,
              HANDLER_CAN_RONLY
              );

    table_data = netsnmp_tdata_create_table( "pstIFMS1000DiffTotalTable", 0 );
    if (NULL == table_data) {
        snmp_log(LOG_ERR,"error creating tdata table for pstIFMS1000DiffTotalTable\n");
        return;
    }
    table_info = SNMP_MALLOC_TYPEDEF( netsnmp_table_registration_info );
    if (NULL == table_info) {
        snmp_log(LOG_ERR,"error creating table info for pstIFMS1000DiffTotalTable\n");
        return;
    }
    netsnmp_table_helper_add_indexes(table_info,
                           ASN_INTEGER,  /* index: pstIFMS1000DtPortNum */
                           0);

    table_info->min_column = COLUMN_PSTIFMS1000DTPORTNUM;
    table_info->max_column = COLUMN_PSTIFMS1000DTTOTALNUM;
    
    netsnmp_tdata_register( reg, table_data, table_info );

    /* Initialise the contents of the table here */
}

//    /* Typical data structure for a row entry */
//struct pstIFMS1000DiffTotalTable_entry {
//    /* Index values */
//    long pstIFMS1000DtPortNum;

//    /* Column values */
//    long pstIFMS1000DtPortNum;
//    long pstIFMS1000DtTotalNum;

//    int   valid;
//};

/* create a new row in the table */
static netsnmp_tdata_row *
pstIFMS1000DiffTotalTable_createEntry(netsnmp_tdata *table_data
                 , long  pstIFMS1000DtPortNum
                ) {
    struct pstIFMS1000DiffTotalTable_entry *entry;
    netsnmp_tdata_row *row;

    entry = SNMP_MALLOC_TYPEDEF(struct pstIFMS1000DiffTotalTable_entry);
    if (!entry)
        return NULL;

    row = netsnmp_tdata_create_row();
    if (!row) {
        SNMP_FREE(entry);
        return NULL;
    }
    row->data = entry;

    DEBUGMSGT(("pstIFMS1000DiffTotalTable:entry:create", "row 0x%x\n", (uintptr_t)row));
    entry->pstIFMS1000DtPortNum = pstIFMS1000DtPortNum;
    netsnmp_tdata_row_add_index( row, ASN_INTEGER,
                                 &(entry->pstIFMS1000DtPortNum),
                                 sizeof(entry->pstIFMS1000DtPortNum));
    if (table_data)
        netsnmp_tdata_add_row( table_data, row );
    return row;
}

/* remove a row from the table */
static void
pstIFMS1000DiffTotalTable_removeEntry(netsnmp_tdata     *table_data, 
                 netsnmp_tdata_row *row) {
    struct pstIFMS1000DiffTotalTable_entry *entry;

    if (!row)
        return;    /* Nothing to remove */

    DEBUGMSGT(("pstIFMS1000DiffTotalTable:entry:remove", "row 0x%x\n", (uintptr_t)row));

    entry = (struct pstIFMS1000DiffTotalTable_entry *)row->data;
    SNMP_FREE( entry );   /* XXX - release any other internal resources */

    if (table_data)
        netsnmp_tdata_remove_and_delete_row( table_data, row );
    else
        netsnmp_tdata_delete_row( row );    
}


/** handles requests for the pstIFMS1000DiffTotalTable table */
int
QPSTProduct::pstIFMS1000DiffTotalTable_handler(
    netsnmp_mib_handler               *handler,
    netsnmp_handler_registration      *reginfo,
    netsnmp_agent_request_info        *reqinfo,
    netsnmp_request_info              *requests) {

    netsnmp_request_info       *request;
    netsnmp_table_request_info *table_info;
    netsnmp_tdata              *table_data;
    netsnmp_tdata_row          *table_row;
    struct pstIFMS1000DiffTotalTable_entry          *table_entry;
    int                         ret;

    DEBUGMSGTL(("pstIFMS1000:handler", "Processing request (%d)\n", reqinfo->mode));

    switch (reqinfo->mode) {
        /*
         * Read-support (also covers GetNext requests)
         */
    case MODE_GET:
        for (request=requests; request; request=request->next) {
            if (request->processed)
                continue;

            table_entry = (struct pstIFMS1000DiffTotalTable_entry *)
                              netsnmp_tdata_extract_entry(request);
            table_info  =     netsnmp_extract_table_info( request);
    
            switch (table_info->colnum) {
            case COLUMN_PSTIFMS1000DTPORTNUM:
                if ( !table_entry ) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_NOSUCHINSTANCE);
                    continue;
                }
                snmp_set_var_typed_integer( request->requestvb, ASN_INTEGER,
                                            table_entry->pstIFMS1000DtPortNum);
                break;
            case COLUMN_PSTIFMS1000DTTOTALNUM:
                if ( !table_entry ) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_NOSUCHINSTANCE);
                    continue;
                }
                snmp_set_var_typed_integer( request->requestvb, ASN_INTEGER,
                                            table_entry->pstIFMS1000DtTotalNum);
                break;
            default:
                netsnmp_set_request_error(reqinfo, request,
                                          SNMP_NOSUCHOBJECT);
                break;
            }
        }
        break;

    }
    return SNMP_ERR_NOERROR;
}

/** Initialize the pstIFMS1000DiffInfoTable table by defining its contents and how it's structured */
void
QPSTProduct::initialize_table_pstIFMS1000DiffInfoTable(void)
{
    const oid pstIFMS1000DiffInfoTable_oid[] = {1,3,6,1,4,1,48391,3,5,4,2};
    const size_t pstIFMS1000DiffInfoTable_oid_len   = OID_LENGTH(pstIFMS1000DiffInfoTable_oid);
    netsnmp_handler_registration    *reg;
    netsnmp_tdata                   *table_data;
    netsnmp_table_registration_info *table_info;

    DEBUGMSGTL(("pstIFMS1000:init", "initializing table pstIFMS1000DiffInfoTable\n"));

    reg = netsnmp_create_handler_registration(
              "pstIFMS1000DiffInfoTable",     pstIFMS1000DiffInfoTable_handler,
              pstIFMS1000DiffInfoTable_oid, pstIFMS1000DiffInfoTable_oid_len,
              HANDLER_CAN_RONLY
              );

    table_data = netsnmp_tdata_create_table( "pstIFMS1000DiffInfoTable", 0 );
    if (NULL == table_data) {
        snmp_log(LOG_ERR,"error creating tdata table for pstIFMS1000DiffInfoTable\n");
        return;
    }
    table_info = SNMP_MALLOC_TYPEDEF( netsnmp_table_registration_info );
    if (NULL == table_info) {
        snmp_log(LOG_ERR,"error creating table info for pstIFMS1000DiffInfoTable\n");
        return;
    }
    netsnmp_table_helper_add_indexes(table_info,
                           ASN_INTEGER,  /* index: pstIFMS1000DiffInfoPortNum */
                           ASN_INTEGER,  /* index: pstIFMS1000DiffInfoPortItemIndex */
                           0);

    table_info->min_column = COLUMN_PSTIFMS1000DIFFINFOPORTNUM;
    table_info->max_column = COLUMN_PSTIFMS1000DIFFINFOPOINTID;
    
    netsnmp_tdata_register( reg, table_data, table_info );

    /* Initialise the contents of the table here */
}

//    /* Typical data structure for a row entry */
//struct pstIFMS1000DiffInfoTable_entry {
//    /* Index values */
//    long pstIFMS1000DiffInfoPortNum;
//    long pstIFMS1000DiffInfoPortItemIndex;

//    /* Column values */
//    long pstIFMS1000DiffInfoPortNum;
//    long pstIFMS1000DiffInfoPortItemIndex;
//    char pstIFMS1000DiffInfoDistance[NNN];
//    size_t pstIFMS1000DiffInfoDistance_len;
//    char pstIFMS1000DiffInfoNVal[NNN];
//    size_t pstIFMS1000DiffInfoNVal_len;
//    char pstIFMS1000DiffInfodBVal[NNN];
//    size_t pstIFMS1000DiffInfodBVal_len;
//    long pstIFMS1000DiffInfoDiffType;
//    u_long pstIFMS1000DiffInfoPointId;

//    int   valid;
//};

/* create a new row in the table */
static netsnmp_tdata_row *
pstIFMS1000DiffInfoTable_createEntry(netsnmp_tdata *table_data
                 , long  pstIFMS1000DiffInfoPortNum
                 , long  pstIFMS1000DiffInfoPortItemIndex
                ) {
    struct pstIFMS1000DiffInfoTable_entry *entry;
    netsnmp_tdata_row *row;

    entry = SNMP_MALLOC_TYPEDEF(struct pstIFMS1000DiffInfoTable_entry);
    if (!entry)
        return NULL;

    row = netsnmp_tdata_create_row();
    if (!row) {
        SNMP_FREE(entry);
        return NULL;
    }
    row->data = entry;

    DEBUGMSGT(("pstIFMS1000DiffInfoTable:entry:create", "row 0x%x\n", (uintptr_t)row));
    entry->pstIFMS1000DiffInfoPortNum = pstIFMS1000DiffInfoPortNum;
    netsnmp_tdata_row_add_index( row, ASN_INTEGER,
                                 &(entry->pstIFMS1000DiffInfoPortNum),
                                 sizeof(entry->pstIFMS1000DiffInfoPortNum));
    entry->pstIFMS1000DiffInfoPortItemIndex = pstIFMS1000DiffInfoPortItemIndex;
    netsnmp_tdata_row_add_index( row, ASN_INTEGER,
                                 &(entry->pstIFMS1000DiffInfoPortItemIndex),
                                 sizeof(entry->pstIFMS1000DiffInfoPortItemIndex));
    if (table_data)
        netsnmp_tdata_add_row( table_data, row );
    return row;
}

/* remove a row from the table */
static void
pstIFMS1000DiffInfoTable_removeEntry(netsnmp_tdata     *table_data, 
                 netsnmp_tdata_row *row) {
    struct pstIFMS1000DiffInfoTable_entry *entry;

    if (!row)
        return;    /* Nothing to remove */

    DEBUGMSGT(("pstIFMS1000DiffInfoTable:entry:remove", "row 0x%x\n", (uintptr_t)row));

    entry = (struct pstIFMS1000DiffInfoTable_entry *)row->data;
    SNMP_FREE( entry );   /* XXX - release any other internal resources */

    if (table_data)
        netsnmp_tdata_remove_and_delete_row( table_data, row );
    else
        netsnmp_tdata_delete_row( row );    
}


/** handles requests for the pstIFMS1000DiffInfoTable table */
int
QPSTProduct::pstIFMS1000DiffInfoTable_handler(
    netsnmp_mib_handler               *handler,
    netsnmp_handler_registration      *reginfo,
    netsnmp_agent_request_info        *reqinfo,
    netsnmp_request_info              *requests) {

    netsnmp_request_info       *request;
    netsnmp_table_request_info *table_info;
    netsnmp_tdata              *table_data;
    netsnmp_tdata_row          *table_row;
    struct pstIFMS1000DiffInfoTable_entry          *table_entry;
    int                         ret;

    DEBUGMSGTL(("pstIFMS1000:handler", "Processing request (%d)\n", reqinfo->mode));

    switch (reqinfo->mode) {
        /*
         * Read-support (also covers GetNext requests)
         */
    case MODE_GET:
        for (request=requests; request; request=request->next) {
            if (request->processed)
                continue;

            table_entry = (struct pstIFMS1000DiffInfoTable_entry *)
                              netsnmp_tdata_extract_entry(request);
            table_info  =     netsnmp_extract_table_info( request);
    
            switch (table_info->colnum) {
            case COLUMN_PSTIFMS1000DIFFINFOPORTNUM:
                if ( !table_entry ) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_NOSUCHINSTANCE);
                    continue;
                }
                snmp_set_var_typed_integer( request->requestvb, ASN_INTEGER,
                                            table_entry->pstIFMS1000DiffInfoPortNum);
                break;
            case COLUMN_PSTIFMS1000DIFFINFOPORTITEMINDEX:
                if ( !table_entry ) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_NOSUCHINSTANCE);
                    continue;
                }
                snmp_set_var_typed_integer( request->requestvb, ASN_INTEGER,
                                            table_entry->pstIFMS1000DiffInfoPortItemIndex);
                break;
            case COLUMN_PSTIFMS1000DIFFINFODISTANCE:
                if ( !table_entry ) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_NOSUCHINSTANCE);
                    continue;
                }
                snmp_set_var_typed_value( request->requestvb, ASN_OCTET_STR,
                                          table_entry->pstIFMS1000DiffInfoDistance,
                                          table_entry->pstIFMS1000DiffInfoDistance_len);
                break;
            case COLUMN_PSTIFMS1000DIFFINFONVAL:
                if ( !table_entry ) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_NOSUCHINSTANCE);
                    continue;
                }
                snmp_set_var_typed_value( request->requestvb, ASN_OCTET_STR,
                                          table_entry->pstIFMS1000DiffInfoNVal,
                                          table_entry->pstIFMS1000DiffInfoNVal_len);
                break;
            case COLUMN_PSTIFMS1000DIFFINFODBVAL:
                if ( !table_entry ) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_NOSUCHINSTANCE);
                    continue;
                }
                snmp_set_var_typed_value( request->requestvb, ASN_OCTET_STR,
                                          table_entry->pstIFMS1000DiffInfodBVal,
                                          table_entry->pstIFMS1000DiffInfodBVal_len);
                break;
            case COLUMN_PSTIFMS1000DIFFINFODIFFTYPE:
                if ( !table_entry ) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_NOSUCHINSTANCE);
                    continue;
                }
                snmp_set_var_typed_integer( request->requestvb, ASN_INTEGER,
                                            table_entry->pstIFMS1000DiffInfoDiffType);
                break;
            case COLUMN_PSTIFMS1000DIFFINFOPOINTID:
                if ( !table_entry ) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_NOSUCHINSTANCE);
                    continue;
                }
                snmp_set_var_typed_integer( request->requestvb, ASN_UNSIGNED,
                                            table_entry->pstIFMS1000DiffInfoPointId);
                break;
            default:
                netsnmp_set_request_error(reqinfo, request,
                                          SNMP_NOSUCHOBJECT);
                break;
            }
        }
        break;

    }
    return SNMP_ERR_NOERROR;
}

/** Initialize the pstIFMS1000PortLedTable table by defining its contents and how it's structured */
void
QPSTProduct::initialize_table_pstIFMS1000PortLedTable(void)
{
    const oid pstIFMS1000PortLedTable_oid[] = {1,3,6,1,4,1,48391,3,5,6,2};
    const size_t pstIFMS1000PortLedTable_oid_len   = OID_LENGTH(pstIFMS1000PortLedTable_oid);
    netsnmp_handler_registration    *reg;
    netsnmp_tdata                   *table_data;
    netsnmp_table_registration_info *table_info;

    DEBUGMSGTL(("pstIFMS1000:init", "initializing table pstIFMS1000PortLedTable\n"));

    reg = netsnmp_create_handler_registration(
              "pstIFMS1000PortLedTable",     pstIFMS1000PortLedTable_handler,
              pstIFMS1000PortLedTable_oid, pstIFMS1000PortLedTable_oid_len,
              HANDLER_CAN_RONLY
              );

    table_data = netsnmp_tdata_create_table( "pstIFMS1000PortLedTable", 0 );
    if (NULL == table_data) {
        snmp_log(LOG_ERR,"error creating tdata table for pstIFMS1000PortLedTable\n");
        return;
    }
    table_info = SNMP_MALLOC_TYPEDEF( netsnmp_table_registration_info );
    if (NULL == table_info) {
        snmp_log(LOG_ERR,"error creating table info for pstIFMS1000PortLedTable\n");
        return;
    }
    netsnmp_table_helper_add_indexes(table_info,
                           ASN_INTEGER,  /* index: pstIFMS1000PortLedPortNum */
                           0);

    table_info->min_column = COLUMN_PSTIFMS1000PORTLEDPORTNUM;
    table_info->max_column = COLUMN_PSTIFMS1000PORTLEDSTATUS;
    
    netsnmp_tdata_register( reg, table_data, table_info );

    /* Initialise the contents of the table here */
}

//    /* Typical data structure for a row entry */
//struct pstIFMS1000PortLedTable_entry {
//    /* Index values */
//    long pstIFMS1000PortLedPortNum;

//    /* Column values */
//    long pstIFMS1000PortLedPortNum;
//    long pstIFMS1000PortLedStatus;

//    int   valid;
//};

/* create a new row in the table */
static netsnmp_tdata_row *
pstIFMS1000PortLedTable_createEntry(netsnmp_tdata *table_data
                 , long  pstIFMS1000PortLedPortNum
                ) {
    struct pstIFMS1000PortLedTable_entry *entry;
    netsnmp_tdata_row *row;

    entry = SNMP_MALLOC_TYPEDEF(struct pstIFMS1000PortLedTable_entry);
    if (!entry)
        return NULL;

    row = netsnmp_tdata_create_row();
    if (!row) {
        SNMP_FREE(entry);
        return NULL;
    }
    row->data = entry;

    DEBUGMSGT(("pstIFMS1000PortLedTable:entry:create", "row 0x%x\n", (uintptr_t)row));
    entry->pstIFMS1000PortLedPortNum = pstIFMS1000PortLedPortNum;
    netsnmp_tdata_row_add_index( row, ASN_INTEGER,
                                 &(entry->pstIFMS1000PortLedPortNum),
                                 sizeof(entry->pstIFMS1000PortLedPortNum));
    if (table_data)
        netsnmp_tdata_add_row( table_data, row );
    return row;
}

/* remove a row from the table */
static void
pstIFMS1000PortLedTable_removeEntry(netsnmp_tdata     *table_data, 
                 netsnmp_tdata_row *row) {
    struct pstIFMS1000PortLedTable_entry *entry;

    if (!row)
        return;    /* Nothing to remove */

    DEBUGMSGT(("pstIFMS1000PortLedTable:entry:remove", "row 0x%x\n", (uintptr_t)row));

    entry = (struct pstIFMS1000PortLedTable_entry *)row->data;
    SNMP_FREE( entry );   /* XXX - release any other internal resources */

    if (table_data)
        netsnmp_tdata_remove_and_delete_row( table_data, row );
    else
        netsnmp_tdata_delete_row( row );    
}


/** handles requests for the pstIFMS1000PortLedTable table */
int
QPSTProduct::pstIFMS1000PortLedTable_handler(
    netsnmp_mib_handler               *handler,
    netsnmp_handler_registration      *reginfo,
    netsnmp_agent_request_info        *reqinfo,
    netsnmp_request_info              *requests) {

    netsnmp_request_info       *request;
    netsnmp_table_request_info *table_info;
    netsnmp_tdata              *table_data;
    netsnmp_tdata_row          *table_row;
    struct pstIFMS1000PortLedTable_entry          *table_entry;
    int                         ret;

    DEBUGMSGTL(("pstIFMS1000:handler", "Processing request (%d)\n", reqinfo->mode));

    switch (reqinfo->mode) {
        /*
         * Read-support (also covers GetNext requests)
         */
    case MODE_GET:
        for (request=requests; request; request=request->next) {
            if (request->processed)
                continue;

            table_entry = (struct pstIFMS1000PortLedTable_entry *)
                              netsnmp_tdata_extract_entry(request);
            table_info  =     netsnmp_extract_table_info( request);
    
            switch (table_info->colnum) {
            case COLUMN_PSTIFMS1000PORTLEDPORTNUM:
                if ( !table_entry ) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_NOSUCHINSTANCE);
                    continue;
                }
                snmp_set_var_typed_integer( request->requestvb, ASN_INTEGER,
                                            table_entry->pstIFMS1000PortLedPortNum);
                break;
            case COLUMN_PSTIFMS1000PORTLEDSTATUS:
                if ( !table_entry ) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_NOSUCHINSTANCE);
                    continue;
                }
                snmp_set_var_typed_integer( request->requestvb, ASN_INTEGER,
                                            table_entry->pstIFMS1000PortLedStatus);
                break;
            default:
                netsnmp_set_request_error(reqinfo, request,
                                          SNMP_NOSUCHOBJECT);
                break;
            }
        }
        break;

    }
    return SNMP_ERR_NOERROR;
}

/** Initialize the pstIFMS1000DiagnoseTable table by defining its contents and how it's structured */
void
QPSTProduct::initialize_table_pstIFMS1000DiagnoseTable(void)
{
    const oid pstIFMS1000DiagnoseTable_oid[] = {1,3,6,1,4,1,48391,3,5,7};
    const size_t pstIFMS1000DiagnoseTable_oid_len   = OID_LENGTH(pstIFMS1000DiagnoseTable_oid);
    netsnmp_handler_registration    *reg;
    netsnmp_tdata                   *table_data;
    netsnmp_table_registration_info *table_info;

    DEBUGMSGTL(("pstIFMS1000:init", "initializing table pstIFMS1000DiagnoseTable\n"));

    reg = netsnmp_create_handler_registration(
              "pstIFMS1000DiagnoseTable",     pstIFMS1000DiagnoseTable_handler,
              pstIFMS1000DiagnoseTable_oid, pstIFMS1000DiagnoseTable_oid_len,
              HANDLER_CAN_RWRITE
              );

    table_data = netsnmp_tdata_create_table( "pstIFMS1000DiagnoseTable", 0 );
    if (NULL == table_data) {
        snmp_log(LOG_ERR,"error creating tdata table for pstIFMS1000DiagnoseTable\n");
        return;
    }
    table_info = SNMP_MALLOC_TYPEDEF( netsnmp_table_registration_info );
    if (NULL == table_info) {
        snmp_log(LOG_ERR,"error creating table info for pstIFMS1000DiagnoseTable\n");
        return;
    }
    netsnmp_table_helper_add_indexes(table_info,
                           ASN_INTEGER,  /* index: pstIFMS1000DgPortNum */
                           0);

    table_info->min_column = COLUMN_PSTIFMS1000DGPORTNUM;
    table_info->max_column = COLUMN_PSTIFMS1000DGPE2PROMACTION;
    
    netsnmp_tdata_register( reg, table_data, table_info );

    /* Initialise the contents of the table here */
}

//    /* Typical data structure for a row entry */
//struct pstIFMS1000DiagnoseTable_entry {
//    /* Index values */
//    long pstIFMS1000DgPortNum;

//    /* Column values */
//    long pstIFMS1000DgPortNum;
//    char pstIFMS1000DgLaserACBias[NNN];
//    size_t pstIFMS1000DgLaserACBias_len;
//    char old_pstIFMS1000DgLaserACBias[NNN];
//    size_t old_pstIFMS1000DgLaserACBias_len;
//    char pstIFMS1000DgLaserDCBias[NNN];
//    size_t pstIFMS1000DgLaserDCBias_len;
//    char old_pstIFMS1000DgLaserDCBias[NNN];
//    size_t old_pstIFMS1000DgLaserDCBias_len;
//    char pstIFMS1000DgLaserACModulation[NNN];
//    size_t pstIFMS1000DgLaserACModulation_len;
//    char old_pstIFMS1000DgLaserACModulation[NNN];
//    size_t old_pstIFMS1000DgLaserACModulation_len;
//    char pstIFMS1000DgLaserDCModulation[NNN];
//    size_t pstIFMS1000DgLaserDCModulation_len;
//    char old_pstIFMS1000DgLaserDCModulation[NNN];
//    size_t old_pstIFMS1000DgLaserDCModulation_len;
//    long pstIFMS1000DgLaserEn;
//    long old_pstIFMS1000DgLaserEn;
//    long pstIFMS1000DgPwm;
//    long old_pstIFMS1000DgPwm;
//    long pstIFMS1000DgSeed;
//    long old_pstIFMS1000DgSeed;
//    long pstIFMS1000DgPrbs;
//    long old_pstIFMS1000DgPrbs;
//    long pstIFMS1000DgAverage;
//    long old_pstIFMS1000DgAverage;
//    long pstIFMS1000DgRegAddr;
//    long old_pstIFMS1000DgRegAddr;
//    long pstIFMS1000DgRegValue;
//    long old_pstIFMS1000DgRegValue;
//    char pstIFMS1000DgMaskStartPoint[NNN];
//    size_t pstIFMS1000DgMaskStartPoint_len;
//    char old_pstIFMS1000DgMaskStartPoint[NNN];
//    size_t old_pstIFMS1000DgMaskStartPoint_len;
//    char pstIFMS1000DgMaskStopPoint[NNN];
//    size_t pstIFMS1000DgMaskStopPoint_len;
//    char old_pstIFMS1000DgMaskStopPoint[NNN];
//    size_t old_pstIFMS1000DgMaskStopPoint_len;
//    long pstIFMS1000DgMaskAction;
//    long old_pstIFMS1000DgMaskAction;
//    char pstIFMS1000DgMeasureDeltaThld[NNN];
//    size_t pstIFMS1000DgMeasureDeltaThld_len;
//    char old_pstIFMS1000DgMeasureDeltaThld[NNN];
//    size_t old_pstIFMS1000DgMeasureDeltaThld_len;
//    char pstIFMS1000DgCutPointThld[NNN];
//    size_t pstIFMS1000DgCutPointThld_len;
//    char old_pstIFMS1000DgCutPointThld[NNN];
//    size_t old_pstIFMS1000DgCutPointThld_len;
//    long pstIFMS1000DgPeriod;
//    long old_pstIFMS1000DgPeriod;
//    long pstIFMS1000DgDAC;
//    long old_pstIFMS1000DgDAC;
//    long pstIFMS1000DgCounterClockMode;
//    long old_pstIFMS1000DgCounterClockMode;
//    long pstIFMS1000DgScanRunType;
//    long old_pstIFMS1000DgScanRunType;
//    u_long pstIFMS1000DgOpt;
//    u_long old_pstIFMS1000DgOpt;
//    char pstIFMS1000DgFiberOffset[NNN];
//    size_t pstIFMS1000DgFiberOffset_len;
//    char old_pstIFMS1000DgFiberOffset[NNN];
//    size_t old_pstIFMS1000DgFiberOffset_len;
//    u_long pstIFMS1000DgTestWaveLen;
//    u_long old_pstIFMS1000DgTestWaveLen;
//    u_long pstIFMS1000DgPRT;
//    u_long old_pstIFMS1000DgPRT;
//    u_long pstIFMS1000DgPPW;
//    u_long old_pstIFMS1000DgPPW;
//    u_long pstIFMS1000DgPPrescale;
//    u_long old_pstIFMS1000DgPPrescale;
//    u_long pstIFMS1000DgPAvg;
//    u_long old_pstIFMS1000DgPAvg;
//    u_long pstIFMS1000DgPGain;
//    u_long old_pstIFMS1000DgPGain;
//    u_long pstIFMS1000DgPAdcData;
//    u_long pstIFMS1000DgPE2promAction;
//    u_long old_pstIFMS1000DgPE2promAction;

//    int   valid;
//};

/* create a new row in the table */
static netsnmp_tdata_row *
pstIFMS1000DiagnoseTable_createEntry(netsnmp_tdata *table_data
                 , long  pstIFMS1000DgPortNum
                ) {
    struct pstIFMS1000DiagnoseTable_entry *entry;
    netsnmp_tdata_row *row;

    entry = SNMP_MALLOC_TYPEDEF(struct pstIFMS1000DiagnoseTable_entry);
    if (!entry)
        return NULL;

    row = netsnmp_tdata_create_row();
    if (!row) {
        SNMP_FREE(entry);
        return NULL;
    }
    row->data = entry;

    DEBUGMSGT(("pstIFMS1000DiagnoseTable:entry:create", "row 0x%x\n", (uintptr_t)row));
    entry->pstIFMS1000DgPortNum = pstIFMS1000DgPortNum;
    netsnmp_tdata_row_add_index( row, ASN_INTEGER,
                                 &(entry->pstIFMS1000DgPortNum),
                                 sizeof(entry->pstIFMS1000DgPortNum));
    if (table_data)
        netsnmp_tdata_add_row( table_data, row );
    return row;
}

/* remove a row from the table */
static void
pstIFMS1000DiagnoseTable_removeEntry(netsnmp_tdata     *table_data, 
                 netsnmp_tdata_row *row) {
    struct pstIFMS1000DiagnoseTable_entry *entry;

    if (!row)
        return;    /* Nothing to remove */

    DEBUGMSGT(("pstIFMS1000DiagnoseTable:entry:remove", "row 0x%x\n", (uintptr_t)row));

    entry = (struct pstIFMS1000DiagnoseTable_entry *)row->data;
    SNMP_FREE( entry );   /* XXX - release any other internal resources */

    if (table_data)
        netsnmp_tdata_remove_and_delete_row( table_data, row );
    else
        netsnmp_tdata_delete_row( row );    
}


/** handles requests for the pstIFMS1000DiagnoseTable table */
int
QPSTProduct::pstIFMS1000DiagnoseTable_handler(
    netsnmp_mib_handler               *handler,
    netsnmp_handler_registration      *reginfo,
    netsnmp_agent_request_info        *reqinfo,
    netsnmp_request_info              *requests) {

    netsnmp_request_info       *request;
    netsnmp_table_request_info *table_info;
    netsnmp_tdata              *table_data;
    netsnmp_tdata_row          *table_row;
    struct pstIFMS1000DiagnoseTable_entry          *table_entry;
    int                         ret;

    DEBUGMSGTL(("pstIFMS1000:handler", "Processing request (%d)\n", reqinfo->mode));

    switch (reqinfo->mode) {
        /*
         * Read-support (also covers GetNext requests)
         */
    case MODE_GET:
        for (request=requests; request; request=request->next) {
            if (request->processed)
                continue;

            table_entry = (struct pstIFMS1000DiagnoseTable_entry *)
                              netsnmp_tdata_extract_entry(request);
            table_info  =     netsnmp_extract_table_info( request);
    
            switch (table_info->colnum) {
            case COLUMN_PSTIFMS1000DGPORTNUM:
                if ( !table_entry ) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_NOSUCHINSTANCE);
                    continue;
                }
                snmp_set_var_typed_integer( request->requestvb, ASN_INTEGER,
                                            table_entry->pstIFMS1000DgPortNum);
                break;
            case COLUMN_PSTIFMS1000DGLASERACBIAS:
                if ( !table_entry ) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_NOSUCHINSTANCE);
                    continue;
                }
                snmp_set_var_typed_value( request->requestvb, ASN_OCTET_STR,
                                          table_entry->pstIFMS1000DgLaserACBias,
                                          table_entry->pstIFMS1000DgLaserACBias_len);
                break;
            case COLUMN_PSTIFMS1000DGLASERDCBIAS:
                if ( !table_entry ) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_NOSUCHINSTANCE);
                    continue;
                }
                snmp_set_var_typed_value( request->requestvb, ASN_OCTET_STR,
                                          table_entry->pstIFMS1000DgLaserDCBias,
                                          table_entry->pstIFMS1000DgLaserDCBias_len);
                break;
            case COLUMN_PSTIFMS1000DGLASERACMODULATION:
                if ( !table_entry ) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_NOSUCHINSTANCE);
                    continue;
                }
                snmp_set_var_typed_value( request->requestvb, ASN_OCTET_STR,
                                          table_entry->pstIFMS1000DgLaserACModulation,
                                          table_entry->pstIFMS1000DgLaserACModulation_len);
                break;
            case COLUMN_PSTIFMS1000DGLASERDCMODULATION:
                if ( !table_entry ) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_NOSUCHINSTANCE);
                    continue;
                }
                snmp_set_var_typed_value( request->requestvb, ASN_OCTET_STR,
                                          table_entry->pstIFMS1000DgLaserDCModulation,
                                          table_entry->pstIFMS1000DgLaserDCModulation_len);
                break;
            case COLUMN_PSTIFMS1000DGLASEREN:
                if ( !table_entry ) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_NOSUCHINSTANCE);
                    continue;
                }
                snmp_set_var_typed_integer( request->requestvb, ASN_INTEGER,
                                            table_entry->pstIFMS1000DgLaserEn);
                break;
            case COLUMN_PSTIFMS1000DGPWM:
                if ( !table_entry ) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_NOSUCHINSTANCE);
                    continue;
                }
                snmp_set_var_typed_integer( request->requestvb, ASN_INTEGER,
                                            table_entry->pstIFMS1000DgPwm);
                break;
            case COLUMN_PSTIFMS1000DGSEED:
                if ( !table_entry ) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_NOSUCHINSTANCE);
                    continue;
                }
                snmp_set_var_typed_integer( request->requestvb, ASN_INTEGER,
                                            table_entry->pstIFMS1000DgSeed);
                break;
            case COLUMN_PSTIFMS1000DGPRBS:
                if ( !table_entry ) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_NOSUCHINSTANCE);
                    continue;
                }
                snmp_set_var_typed_integer( request->requestvb, ASN_INTEGER,
                                            table_entry->pstIFMS1000DgPrbs);
                break;
            case COLUMN_PSTIFMS1000DGAVERAGE:
                if ( !table_entry ) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_NOSUCHINSTANCE);
                    continue;
                }
                snmp_set_var_typed_integer( request->requestvb, ASN_INTEGER,
                                            table_entry->pstIFMS1000DgAverage);
                break;
            case COLUMN_PSTIFMS1000DGREGADDR:
                if ( !table_entry ) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_NOSUCHINSTANCE);
                    continue;
                }
                snmp_set_var_typed_integer( request->requestvb, ASN_INTEGER,
                                            table_entry->pstIFMS1000DgRegAddr);
                break;
            case COLUMN_PSTIFMS1000DGREGVALUE:
                if ( !table_entry ) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_NOSUCHINSTANCE);
                    continue;
                }
                snmp_set_var_typed_integer( request->requestvb, ASN_INTEGER,
                                            table_entry->pstIFMS1000DgRegValue);
                break;
            case COLUMN_PSTIFMS1000DGMASKSTARTPOINT:
                if ( !table_entry ) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_NOSUCHINSTANCE);
                    continue;
                }
                snmp_set_var_typed_value( request->requestvb, ASN_OCTET_STR,
                                          table_entry->pstIFMS1000DgMaskStartPoint,
                                          table_entry->pstIFMS1000DgMaskStartPoint_len);
                break;
            case COLUMN_PSTIFMS1000DGMASKSTOPPOINT:
                if ( !table_entry ) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_NOSUCHINSTANCE);
                    continue;
                }
                snmp_set_var_typed_value( request->requestvb, ASN_OCTET_STR,
                                          table_entry->pstIFMS1000DgMaskStopPoint,
                                          table_entry->pstIFMS1000DgMaskStopPoint_len);
                break;
            case COLUMN_PSTIFMS1000DGMASKACTION:
                if ( !table_entry ) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_NOSUCHINSTANCE);
                    continue;
                }
                snmp_set_var_typed_integer( request->requestvb, ASN_INTEGER,
                                            table_entry->pstIFMS1000DgMaskAction);
                break;
            case COLUMN_PSTIFMS1000DGMEASUREDELTATHLD:
                if ( !table_entry ) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_NOSUCHINSTANCE);
                    continue;
                }
                snmp_set_var_typed_value( request->requestvb, ASN_OCTET_STR,
                                          table_entry->pstIFMS1000DgMeasureDeltaThld,
                                          table_entry->pstIFMS1000DgMeasureDeltaThld_len);
                break;
            case COLUMN_PSTIFMS1000DGCUTPOINTTHLD:
                if ( !table_entry ) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_NOSUCHINSTANCE);
                    continue;
                }
                snmp_set_var_typed_value( request->requestvb, ASN_OCTET_STR,
                                          table_entry->pstIFMS1000DgCutPointThld,
                                          table_entry->pstIFMS1000DgCutPointThld_len);
                break;
            case COLUMN_PSTIFMS1000DGPERIOD:
                if ( !table_entry ) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_NOSUCHINSTANCE);
                    continue;
                }
                snmp_set_var_typed_integer( request->requestvb, ASN_INTEGER,
                                            table_entry->pstIFMS1000DgPeriod);
                break;
            case COLUMN_PSTIFMS1000DGDAC:
                if ( !table_entry ) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_NOSUCHINSTANCE);
                    continue;
                }
                snmp_set_var_typed_integer( request->requestvb, ASN_INTEGER,
                                            table_entry->pstIFMS1000DgDAC);
                break;
            case COLUMN_PSTIFMS1000DGCOUNTERCLOCKMODE:
                if ( !table_entry ) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_NOSUCHINSTANCE);
                    continue;
                }
                snmp_set_var_typed_integer( request->requestvb, ASN_INTEGER,
                                            table_entry->pstIFMS1000DgCounterClockMode);
                break;
            case COLUMN_PSTIFMS1000DGSCANRUNTYPE:
                if ( !table_entry ) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_NOSUCHINSTANCE);
                    continue;
                }
                snmp_set_var_typed_integer( request->requestvb, ASN_INTEGER,
                                            table_entry->pstIFMS1000DgScanRunType);
                break;
            case COLUMN_PSTIFMS1000DGOPT:
                if ( !table_entry ) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_NOSUCHINSTANCE);
                    continue;
                }
                snmp_set_var_typed_integer( request->requestvb, ASN_UNSIGNED,
                                            table_entry->pstIFMS1000DgOpt);
                break;
            case COLUMN_PSTIFMS1000DGFIBEROFFSET:
                if ( !table_entry ) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_NOSUCHINSTANCE);
                    continue;
                }
                snmp_set_var_typed_value( request->requestvb, ASN_OCTET_STR,
                                          table_entry->pstIFMS1000DgFiberOffset,
                                          table_entry->pstIFMS1000DgFiberOffset_len);
                break;
            case COLUMN_PSTIFMS1000DGTESTWAVELEN:
                if ( !table_entry ) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_NOSUCHINSTANCE);
                    continue;
                }
                snmp_set_var_typed_integer( request->requestvb, ASN_UNSIGNED,
                                            table_entry->pstIFMS1000DgTestWaveLen);
                break;
            case COLUMN_PSTIFMS1000DGPRT:
                if ( !table_entry ) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_NOSUCHINSTANCE);
                    continue;
                }
                snmp_set_var_typed_integer( request->requestvb, ASN_UNSIGNED,
                                            table_entry->pstIFMS1000DgPRT);
                break;
            case COLUMN_PSTIFMS1000DGPPW:
                if ( !table_entry ) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_NOSUCHINSTANCE);
                    continue;
                }
                snmp_set_var_typed_integer( request->requestvb, ASN_UNSIGNED,
                                            table_entry->pstIFMS1000DgPPW);
                break;
            case COLUMN_PSTIFMS1000DGPPRESCALE:
                if ( !table_entry ) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_NOSUCHINSTANCE);
                    continue;
                }
                snmp_set_var_typed_integer( request->requestvb, ASN_UNSIGNED,
                                            table_entry->pstIFMS1000DgPPrescale);
                break;
            case COLUMN_PSTIFMS1000DGPAVG:
                if ( !table_entry ) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_NOSUCHINSTANCE);
                    continue;
                }
                snmp_set_var_typed_integer( request->requestvb, ASN_UNSIGNED,
                                            table_entry->pstIFMS1000DgPAvg);
                break;
            case COLUMN_PSTIFMS1000DGPGAIN:
                if ( !table_entry ) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_NOSUCHINSTANCE);
                    continue;
                }
                snmp_set_var_typed_integer( request->requestvb, ASN_UNSIGNED,
                                            table_entry->pstIFMS1000DgPGain);
                break;
            case COLUMN_PSTIFMS1000DGPADCDATA:
                if ( !table_entry ) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_NOSUCHINSTANCE);
                    continue;
                }
                snmp_set_var_typed_integer( request->requestvb, ASN_UNSIGNED,
                                            table_entry->pstIFMS1000DgPAdcData);
                break;
            case COLUMN_PSTIFMS1000DGPE2PROMACTION:
                if ( !table_entry ) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_NOSUCHINSTANCE);
                    continue;
                }
                snmp_set_var_typed_integer( request->requestvb, ASN_UNSIGNED,
                                            table_entry->pstIFMS1000DgPE2promAction);
                break;
            default:
                netsnmp_set_request_error(reqinfo, request,
                                          SNMP_NOSUCHOBJECT);
                break;
            }
        }
        break;

        /*
         * Write-support
         */
    case MODE_SET_RESERVE1:
        for (request=requests; request; request=request->next) {
            if (request->processed)
                continue;

            table_entry = (struct pstIFMS1000DiagnoseTable_entry *)
                              netsnmp_tdata_extract_entry(request);
            table_info  =     netsnmp_extract_table_info( request);
    
            switch (table_info->colnum) {
            case COLUMN_PSTIFMS1000DGLASERACBIAS:
	        /* or possibly 'netsnmp_check_vb_type_and_size' */
                ret = netsnmp_check_vb_type_and_max_size(
                          request->requestvb, ASN_OCTET_STR, sizeof(table_entry->pstIFMS1000DgLaserACBias));
                if ( ret != SNMP_ERR_NOERROR ) {
                    netsnmp_set_request_error( reqinfo, request, ret );
                    return SNMP_ERR_NOERROR;
                }
                break;
            case COLUMN_PSTIFMS1000DGLASERDCBIAS:
	        /* or possibly 'netsnmp_check_vb_type_and_size' */
                ret = netsnmp_check_vb_type_and_max_size(
                          request->requestvb, ASN_OCTET_STR, sizeof(table_entry->pstIFMS1000DgLaserDCBias));
                if ( ret != SNMP_ERR_NOERROR ) {
                    netsnmp_set_request_error( reqinfo, request, ret );
                    return SNMP_ERR_NOERROR;
                }
                break;
            case COLUMN_PSTIFMS1000DGLASERACMODULATION:
	        /* or possibly 'netsnmp_check_vb_type_and_size' */
                ret = netsnmp_check_vb_type_and_max_size(
                          request->requestvb, ASN_OCTET_STR, sizeof(table_entry->pstIFMS1000DgLaserACModulation));
                if ( ret != SNMP_ERR_NOERROR ) {
                    netsnmp_set_request_error( reqinfo, request, ret );
                    return SNMP_ERR_NOERROR;
                }
                break;
            case COLUMN_PSTIFMS1000DGLASERDCMODULATION:
	        /* or possibly 'netsnmp_check_vb_type_and_size' */
                ret = netsnmp_check_vb_type_and_max_size(
                          request->requestvb, ASN_OCTET_STR, sizeof(table_entry->pstIFMS1000DgLaserDCModulation));
                if ( ret != SNMP_ERR_NOERROR ) {
                    netsnmp_set_request_error( reqinfo, request, ret );
                    return SNMP_ERR_NOERROR;
                }
                break;
            case COLUMN_PSTIFMS1000DGLASEREN:
                /* or possibly 'netsnmp_check_vb_int_range' */
                ret = netsnmp_check_vb_int( request->requestvb );
                if ( ret != SNMP_ERR_NOERROR ) {
                    netsnmp_set_request_error( reqinfo, request, ret );
                    return SNMP_ERR_NOERROR;
                }
                break;
            case COLUMN_PSTIFMS1000DGPWM:
                /* or possibly 'netsnmp_check_vb_int_range' */
                ret = netsnmp_check_vb_int( request->requestvb );
                if ( ret != SNMP_ERR_NOERROR ) {
                    netsnmp_set_request_error( reqinfo, request, ret );
                    return SNMP_ERR_NOERROR;
                }
                break;
            case COLUMN_PSTIFMS1000DGSEED:
                /* or possibly 'netsnmp_check_vb_int_range' */
                ret = netsnmp_check_vb_int( request->requestvb );
                if ( ret != SNMP_ERR_NOERROR ) {
                    netsnmp_set_request_error( reqinfo, request, ret );
                    return SNMP_ERR_NOERROR;
                }
                break;
            case COLUMN_PSTIFMS1000DGPRBS:
                /* or possibly 'netsnmp_check_vb_int_range' */
                ret = netsnmp_check_vb_int( request->requestvb );
                if ( ret != SNMP_ERR_NOERROR ) {
                    netsnmp_set_request_error( reqinfo, request, ret );
                    return SNMP_ERR_NOERROR;
                }
                break;
            case COLUMN_PSTIFMS1000DGAVERAGE:
                /* or possibly 'netsnmp_check_vb_int_range' */
                ret = netsnmp_check_vb_int( request->requestvb );
                if ( ret != SNMP_ERR_NOERROR ) {
                    netsnmp_set_request_error( reqinfo, request, ret );
                    return SNMP_ERR_NOERROR;
                }
                break;
            case COLUMN_PSTIFMS1000DGREGADDR:
                /* or possibly 'netsnmp_check_vb_int_range' */
                ret = netsnmp_check_vb_int( request->requestvb );
                if ( ret != SNMP_ERR_NOERROR ) {
                    netsnmp_set_request_error( reqinfo, request, ret );
                    return SNMP_ERR_NOERROR;
                }
                break;
            case COLUMN_PSTIFMS1000DGREGVALUE:
                /* or possibly 'netsnmp_check_vb_int_range' */
                ret = netsnmp_check_vb_int( request->requestvb );
                if ( ret != SNMP_ERR_NOERROR ) {
                    netsnmp_set_request_error( reqinfo, request, ret );
                    return SNMP_ERR_NOERROR;
                }
                break;
            case COLUMN_PSTIFMS1000DGMASKSTARTPOINT:
	        /* or possibly 'netsnmp_check_vb_type_and_size' */
                ret = netsnmp_check_vb_type_and_max_size(
                          request->requestvb, ASN_OCTET_STR, sizeof(table_entry->pstIFMS1000DgMaskStartPoint));
                if ( ret != SNMP_ERR_NOERROR ) {
                    netsnmp_set_request_error( reqinfo, request, ret );
                    return SNMP_ERR_NOERROR;
                }
                break;
            case COLUMN_PSTIFMS1000DGMASKSTOPPOINT:
	        /* or possibly 'netsnmp_check_vb_type_and_size' */
                ret = netsnmp_check_vb_type_and_max_size(
                          request->requestvb, ASN_OCTET_STR, sizeof(table_entry->pstIFMS1000DgMaskStopPoint));
                if ( ret != SNMP_ERR_NOERROR ) {
                    netsnmp_set_request_error( reqinfo, request, ret );
                    return SNMP_ERR_NOERROR;
                }
                break;
            case COLUMN_PSTIFMS1000DGMASKACTION:
                /* or possibly 'netsnmp_check_vb_int_range' */
                ret = netsnmp_check_vb_int( request->requestvb );
                if ( ret != SNMP_ERR_NOERROR ) {
                    netsnmp_set_request_error( reqinfo, request, ret );
                    return SNMP_ERR_NOERROR;
                }
                break;
            case COLUMN_PSTIFMS1000DGMEASUREDELTATHLD:
	        /* or possibly 'netsnmp_check_vb_type_and_size' */
                ret = netsnmp_check_vb_type_and_max_size(
                          request->requestvb, ASN_OCTET_STR, sizeof(table_entry->pstIFMS1000DgMeasureDeltaThld));
                if ( ret != SNMP_ERR_NOERROR ) {
                    netsnmp_set_request_error( reqinfo, request, ret );
                    return SNMP_ERR_NOERROR;
                }
                break;
            case COLUMN_PSTIFMS1000DGCUTPOINTTHLD:
	        /* or possibly 'netsnmp_check_vb_type_and_size' */
                ret = netsnmp_check_vb_type_and_max_size(
                          request->requestvb, ASN_OCTET_STR, sizeof(table_entry->pstIFMS1000DgCutPointThld));
                if ( ret != SNMP_ERR_NOERROR ) {
                    netsnmp_set_request_error( reqinfo, request, ret );
                    return SNMP_ERR_NOERROR;
                }
                break;
            case COLUMN_PSTIFMS1000DGPERIOD:
                /* or possibly 'netsnmp_check_vb_int_range' */
                ret = netsnmp_check_vb_int( request->requestvb );
                if ( ret != SNMP_ERR_NOERROR ) {
                    netsnmp_set_request_error( reqinfo, request, ret );
                    return SNMP_ERR_NOERROR;
                }
                break;
            case COLUMN_PSTIFMS1000DGDAC:
                /* or possibly 'netsnmp_check_vb_int_range' */
                ret = netsnmp_check_vb_int( request->requestvb );
                if ( ret != SNMP_ERR_NOERROR ) {
                    netsnmp_set_request_error( reqinfo, request, ret );
                    return SNMP_ERR_NOERROR;
                }
                break;
            case COLUMN_PSTIFMS1000DGCOUNTERCLOCKMODE:
                /* or possibly 'netsnmp_check_vb_int_range' */
                ret = netsnmp_check_vb_int( request->requestvb );
                if ( ret != SNMP_ERR_NOERROR ) {
                    netsnmp_set_request_error( reqinfo, request, ret );
                    return SNMP_ERR_NOERROR;
                }
                break;
            case COLUMN_PSTIFMS1000DGSCANRUNTYPE:
                /* or possibly 'netsnmp_check_vb_int_range' */
                ret = netsnmp_check_vb_int( request->requestvb );
                if ( ret != SNMP_ERR_NOERROR ) {
                    netsnmp_set_request_error( reqinfo, request, ret );
                    return SNMP_ERR_NOERROR;
                }
                break;
            case COLUMN_PSTIFMS1000DGOPT:
                /* or possibly 'netsnmp_check_vb_int_range' */
                ret = netsnmp_check_vb_int( request->requestvb );
                if ( ret != SNMP_ERR_NOERROR ) {
                    netsnmp_set_request_error( reqinfo, request, ret );
                    return SNMP_ERR_NOERROR;
                }
                break;
            case COLUMN_PSTIFMS1000DGFIBEROFFSET:
	        /* or possibly 'netsnmp_check_vb_type_and_size' */
                ret = netsnmp_check_vb_type_and_max_size(
                          request->requestvb, ASN_OCTET_STR, sizeof(table_entry->pstIFMS1000DgFiberOffset));
                if ( ret != SNMP_ERR_NOERROR ) {
                    netsnmp_set_request_error( reqinfo, request, ret );
                    return SNMP_ERR_NOERROR;
                }
                break;
            case COLUMN_PSTIFMS1000DGTESTWAVELEN:
                /* or possibly 'netsnmp_check_vb_int_range' */
                ret = netsnmp_check_vb_int( request->requestvb );
                if ( ret != SNMP_ERR_NOERROR ) {
                    netsnmp_set_request_error( reqinfo, request, ret );
                    return SNMP_ERR_NOERROR;
                }
                break;
            case COLUMN_PSTIFMS1000DGPRT:
                /* or possibly 'netsnmp_check_vb_int_range' */
                ret = netsnmp_check_vb_int( request->requestvb );
                if ( ret != SNMP_ERR_NOERROR ) {
                    netsnmp_set_request_error( reqinfo, request, ret );
                    return SNMP_ERR_NOERROR;
                }
                break;
            case COLUMN_PSTIFMS1000DGPPW:
                /* or possibly 'netsnmp_check_vb_int_range' */
                ret = netsnmp_check_vb_int( request->requestvb );
                if ( ret != SNMP_ERR_NOERROR ) {
                    netsnmp_set_request_error( reqinfo, request, ret );
                    return SNMP_ERR_NOERROR;
                }
                break;
            case COLUMN_PSTIFMS1000DGPPRESCALE:
                /* or possibly 'netsnmp_check_vb_int_range' */
                ret = netsnmp_check_vb_int( request->requestvb );
                if ( ret != SNMP_ERR_NOERROR ) {
                    netsnmp_set_request_error( reqinfo, request, ret );
                    return SNMP_ERR_NOERROR;
                }
                break;
            case COLUMN_PSTIFMS1000DGPAVG:
                /* or possibly 'netsnmp_check_vb_int_range' */
                ret = netsnmp_check_vb_int( request->requestvb );
                if ( ret != SNMP_ERR_NOERROR ) {
                    netsnmp_set_request_error( reqinfo, request, ret );
                    return SNMP_ERR_NOERROR;
                }
                break;
            case COLUMN_PSTIFMS1000DGPGAIN:
                /* or possibly 'netsnmp_check_vb_int_range' */
                ret = netsnmp_check_vb_int( request->requestvb );
                if ( ret != SNMP_ERR_NOERROR ) {
                    netsnmp_set_request_error( reqinfo, request, ret );
                    return SNMP_ERR_NOERROR;
                }
                break;
            case COLUMN_PSTIFMS1000DGPE2PROMACTION:
                /* or possibly 'netsnmp_check_vb_int_range' */
                ret = netsnmp_check_vb_int( request->requestvb );
                if ( ret != SNMP_ERR_NOERROR ) {
                    netsnmp_set_request_error( reqinfo, request, ret );
                    return SNMP_ERR_NOERROR;
                }
                break;
            default:
                netsnmp_set_request_error( reqinfo, request,
                                           SNMP_ERR_NOTWRITABLE );
                return SNMP_ERR_NOERROR;
            }
        }
        break;

    case MODE_SET_RESERVE2:
        break;

    case MODE_SET_FREE:
        break;

    case MODE_SET_ACTION:
        for (request=requests; request; request=request->next) {
            if (request->processed)
                continue;

            table_entry = (struct pstIFMS1000DiagnoseTable_entry *)
                              netsnmp_tdata_extract_entry(request);
            table_info  =     netsnmp_extract_table_info( request);
    
            switch (table_info->colnum) {
            case COLUMN_PSTIFMS1000DGLASERACBIAS:
                memcpy( table_entry->old_pstIFMS1000DgLaserACBias,
                        table_entry->pstIFMS1000DgLaserACBias,
                        sizeof(table_entry->pstIFMS1000DgLaserACBias));
                table_entry->old_pstIFMS1000DgLaserACBias_len =
                        table_entry->pstIFMS1000DgLaserACBias_len;
                memset( table_entry->pstIFMS1000DgLaserACBias, 0,
                        sizeof(table_entry->pstIFMS1000DgLaserACBias));
                memcpy( table_entry->pstIFMS1000DgLaserACBias,
                        request->requestvb->val.string,
                        request->requestvb->val_len);
                table_entry->pstIFMS1000DgLaserACBias_len =
                        request->requestvb->val_len;
                break;
            case COLUMN_PSTIFMS1000DGLASERDCBIAS:
                memcpy( table_entry->old_pstIFMS1000DgLaserDCBias,
                        table_entry->pstIFMS1000DgLaserDCBias,
                        sizeof(table_entry->pstIFMS1000DgLaserDCBias));
                table_entry->old_pstIFMS1000DgLaserDCBias_len =
                        table_entry->pstIFMS1000DgLaserDCBias_len;
                memset( table_entry->pstIFMS1000DgLaserDCBias, 0,
                        sizeof(table_entry->pstIFMS1000DgLaserDCBias));
                memcpy( table_entry->pstIFMS1000DgLaserDCBias,
                        request->requestvb->val.string,
                        request->requestvb->val_len);
                table_entry->pstIFMS1000DgLaserDCBias_len =
                        request->requestvb->val_len;
                break;
            case COLUMN_PSTIFMS1000DGLASERACMODULATION:
                memcpy( table_entry->old_pstIFMS1000DgLaserACModulation,
                        table_entry->pstIFMS1000DgLaserACModulation,
                        sizeof(table_entry->pstIFMS1000DgLaserACModulation));
                table_entry->old_pstIFMS1000DgLaserACModulation_len =
                        table_entry->pstIFMS1000DgLaserACModulation_len;
                memset( table_entry->pstIFMS1000DgLaserACModulation, 0,
                        sizeof(table_entry->pstIFMS1000DgLaserACModulation));
                memcpy( table_entry->pstIFMS1000DgLaserACModulation,
                        request->requestvb->val.string,
                        request->requestvb->val_len);
                table_entry->pstIFMS1000DgLaserACModulation_len =
                        request->requestvb->val_len;
                break;
            case COLUMN_PSTIFMS1000DGLASERDCMODULATION:
                memcpy( table_entry->old_pstIFMS1000DgLaserDCModulation,
                        table_entry->pstIFMS1000DgLaserDCModulation,
                        sizeof(table_entry->pstIFMS1000DgLaserDCModulation));
                table_entry->old_pstIFMS1000DgLaserDCModulation_len =
                        table_entry->pstIFMS1000DgLaserDCModulation_len;
                memset( table_entry->pstIFMS1000DgLaserDCModulation, 0,
                        sizeof(table_entry->pstIFMS1000DgLaserDCModulation));
                memcpy( table_entry->pstIFMS1000DgLaserDCModulation,
                        request->requestvb->val.string,
                        request->requestvb->val_len);
                table_entry->pstIFMS1000DgLaserDCModulation_len =
                        request->requestvb->val_len;
                break;
            case COLUMN_PSTIFMS1000DGLASEREN:
                table_entry->old_pstIFMS1000DgLaserEn = table_entry->pstIFMS1000DgLaserEn;
                table_entry->pstIFMS1000DgLaserEn     = *request->requestvb->val.integer;
                break;
            case COLUMN_PSTIFMS1000DGPWM:
                table_entry->old_pstIFMS1000DgPwm = table_entry->pstIFMS1000DgPwm;
                table_entry->pstIFMS1000DgPwm     = *request->requestvb->val.integer;
                break;
            case COLUMN_PSTIFMS1000DGSEED:
                table_entry->old_pstIFMS1000DgSeed = table_entry->pstIFMS1000DgSeed;
                table_entry->pstIFMS1000DgSeed     = *request->requestvb->val.integer;
                break;
            case COLUMN_PSTIFMS1000DGPRBS:
                table_entry->old_pstIFMS1000DgPrbs = table_entry->pstIFMS1000DgPrbs;
                table_entry->pstIFMS1000DgPrbs     = *request->requestvb->val.integer;
                break;
            case COLUMN_PSTIFMS1000DGAVERAGE:
                table_entry->old_pstIFMS1000DgAverage = table_entry->pstIFMS1000DgAverage;
                table_entry->pstIFMS1000DgAverage     = *request->requestvb->val.integer;
                break;
            case COLUMN_PSTIFMS1000DGREGADDR:
                table_entry->old_pstIFMS1000DgRegAddr = table_entry->pstIFMS1000DgRegAddr;
                table_entry->pstIFMS1000DgRegAddr     = *request->requestvb->val.integer;
                break;
            case COLUMN_PSTIFMS1000DGREGVALUE:
                table_entry->old_pstIFMS1000DgRegValue = table_entry->pstIFMS1000DgRegValue;
                table_entry->pstIFMS1000DgRegValue     = *request->requestvb->val.integer;
                break;
            case COLUMN_PSTIFMS1000DGMASKSTARTPOINT:
                memcpy( table_entry->old_pstIFMS1000DgMaskStartPoint,
                        table_entry->pstIFMS1000DgMaskStartPoint,
                        sizeof(table_entry->pstIFMS1000DgMaskStartPoint));
                table_entry->old_pstIFMS1000DgMaskStartPoint_len =
                        table_entry->pstIFMS1000DgMaskStartPoint_len;
                memset( table_entry->pstIFMS1000DgMaskStartPoint, 0,
                        sizeof(table_entry->pstIFMS1000DgMaskStartPoint));
                memcpy( table_entry->pstIFMS1000DgMaskStartPoint,
                        request->requestvb->val.string,
                        request->requestvb->val_len);
                table_entry->pstIFMS1000DgMaskStartPoint_len =
                        request->requestvb->val_len;
                break;
            case COLUMN_PSTIFMS1000DGMASKSTOPPOINT:
                memcpy( table_entry->old_pstIFMS1000DgMaskStopPoint,
                        table_entry->pstIFMS1000DgMaskStopPoint,
                        sizeof(table_entry->pstIFMS1000DgMaskStopPoint));
                table_entry->old_pstIFMS1000DgMaskStopPoint_len =
                        table_entry->pstIFMS1000DgMaskStopPoint_len;
                memset( table_entry->pstIFMS1000DgMaskStopPoint, 0,
                        sizeof(table_entry->pstIFMS1000DgMaskStopPoint));
                memcpy( table_entry->pstIFMS1000DgMaskStopPoint,
                        request->requestvb->val.string,
                        request->requestvb->val_len);
                table_entry->pstIFMS1000DgMaskStopPoint_len =
                        request->requestvb->val_len;
                break;
            case COLUMN_PSTIFMS1000DGMASKACTION:
                table_entry->old_pstIFMS1000DgMaskAction = table_entry->pstIFMS1000DgMaskAction;
                table_entry->pstIFMS1000DgMaskAction     = *request->requestvb->val.integer;
                break;
            case COLUMN_PSTIFMS1000DGMEASUREDELTATHLD:
                memcpy( table_entry->old_pstIFMS1000DgMeasureDeltaThld,
                        table_entry->pstIFMS1000DgMeasureDeltaThld,
                        sizeof(table_entry->pstIFMS1000DgMeasureDeltaThld));
                table_entry->old_pstIFMS1000DgMeasureDeltaThld_len =
                        table_entry->pstIFMS1000DgMeasureDeltaThld_len;
                memset( table_entry->pstIFMS1000DgMeasureDeltaThld, 0,
                        sizeof(table_entry->pstIFMS1000DgMeasureDeltaThld));
                memcpy( table_entry->pstIFMS1000DgMeasureDeltaThld,
                        request->requestvb->val.string,
                        request->requestvb->val_len);
                table_entry->pstIFMS1000DgMeasureDeltaThld_len =
                        request->requestvb->val_len;
                break;
            case COLUMN_PSTIFMS1000DGCUTPOINTTHLD:
                memcpy( table_entry->old_pstIFMS1000DgCutPointThld,
                        table_entry->pstIFMS1000DgCutPointThld,
                        sizeof(table_entry->pstIFMS1000DgCutPointThld));
                table_entry->old_pstIFMS1000DgCutPointThld_len =
                        table_entry->pstIFMS1000DgCutPointThld_len;
                memset( table_entry->pstIFMS1000DgCutPointThld, 0,
                        sizeof(table_entry->pstIFMS1000DgCutPointThld));
                memcpy( table_entry->pstIFMS1000DgCutPointThld,
                        request->requestvb->val.string,
                        request->requestvb->val_len);
                table_entry->pstIFMS1000DgCutPointThld_len =
                        request->requestvb->val_len;
                break;
            case COLUMN_PSTIFMS1000DGPERIOD:
                table_entry->old_pstIFMS1000DgPeriod = table_entry->pstIFMS1000DgPeriod;
                table_entry->pstIFMS1000DgPeriod     = *request->requestvb->val.integer;
                break;
            case COLUMN_PSTIFMS1000DGDAC:
                table_entry->old_pstIFMS1000DgDAC = table_entry->pstIFMS1000DgDAC;
                table_entry->pstIFMS1000DgDAC     = *request->requestvb->val.integer;
                break;
            case COLUMN_PSTIFMS1000DGCOUNTERCLOCKMODE:
                table_entry->old_pstIFMS1000DgCounterClockMode = table_entry->pstIFMS1000DgCounterClockMode;
                table_entry->pstIFMS1000DgCounterClockMode     = *request->requestvb->val.integer;
                break;
            case COLUMN_PSTIFMS1000DGSCANRUNTYPE:
                table_entry->old_pstIFMS1000DgScanRunType = table_entry->pstIFMS1000DgScanRunType;
                table_entry->pstIFMS1000DgScanRunType     = *request->requestvb->val.integer;
                break;
            case COLUMN_PSTIFMS1000DGOPT:
                table_entry->old_pstIFMS1000DgOpt = table_entry->pstIFMS1000DgOpt;
                table_entry->pstIFMS1000DgOpt     = *request->requestvb->val.integer;
                break;
            case COLUMN_PSTIFMS1000DGFIBEROFFSET:
                memcpy( table_entry->old_pstIFMS1000DgFiberOffset,
                        table_entry->pstIFMS1000DgFiberOffset,
                        sizeof(table_entry->pstIFMS1000DgFiberOffset));
                table_entry->old_pstIFMS1000DgFiberOffset_len =
                        table_entry->pstIFMS1000DgFiberOffset_len;
                memset( table_entry->pstIFMS1000DgFiberOffset, 0,
                        sizeof(table_entry->pstIFMS1000DgFiberOffset));
                memcpy( table_entry->pstIFMS1000DgFiberOffset,
                        request->requestvb->val.string,
                        request->requestvb->val_len);
                table_entry->pstIFMS1000DgFiberOffset_len =
                        request->requestvb->val_len;
                break;
            case COLUMN_PSTIFMS1000DGTESTWAVELEN:
                table_entry->old_pstIFMS1000DgTestWaveLen = table_entry->pstIFMS1000DgTestWaveLen;
                table_entry->pstIFMS1000DgTestWaveLen     = *request->requestvb->val.integer;
                break;
            case COLUMN_PSTIFMS1000DGPRT:
                table_entry->old_pstIFMS1000DgPRT = table_entry->pstIFMS1000DgPRT;
                table_entry->pstIFMS1000DgPRT     = *request->requestvb->val.integer;
                break;
            case COLUMN_PSTIFMS1000DGPPW:
                table_entry->old_pstIFMS1000DgPPW = table_entry->pstIFMS1000DgPPW;
                table_entry->pstIFMS1000DgPPW     = *request->requestvb->val.integer;
                break;
            case COLUMN_PSTIFMS1000DGPPRESCALE:
                table_entry->old_pstIFMS1000DgPPrescale = table_entry->pstIFMS1000DgPPrescale;
                table_entry->pstIFMS1000DgPPrescale     = *request->requestvb->val.integer;
                break;
            case COLUMN_PSTIFMS1000DGPAVG:
                table_entry->old_pstIFMS1000DgPAvg = table_entry->pstIFMS1000DgPAvg;
                table_entry->pstIFMS1000DgPAvg     = *request->requestvb->val.integer;
                break;
            case COLUMN_PSTIFMS1000DGPGAIN:
                table_entry->old_pstIFMS1000DgPGain = table_entry->pstIFMS1000DgPGain;
                table_entry->pstIFMS1000DgPGain     = *request->requestvb->val.integer;
                break;
            case COLUMN_PSTIFMS1000DGPE2PROMACTION:
                table_entry->old_pstIFMS1000DgPE2promAction = table_entry->pstIFMS1000DgPE2promAction;
                table_entry->pstIFMS1000DgPE2promAction     = *request->requestvb->val.integer;
                break;
            }
        }
        break;

    case MODE_SET_UNDO:
        for (request=requests; request; request=request->next) {
            if (request->processed)
                continue;

            table_entry = (struct pstIFMS1000DiagnoseTable_entry *)
                              netsnmp_tdata_extract_entry(request);
            table_row   =     netsnmp_tdata_extract_row(  request);
            table_data  =     netsnmp_tdata_extract_table(request);
            table_info  =     netsnmp_extract_table_info( request);
    
            switch (table_info->colnum) {
            case COLUMN_PSTIFMS1000DGLASERACBIAS:
                memcpy( table_entry->pstIFMS1000DgLaserACBias,
                        table_entry->old_pstIFMS1000DgLaserACBias,
                        sizeof(table_entry->pstIFMS1000DgLaserACBias));
                memset( table_entry->old_pstIFMS1000DgLaserACBias, 0,
                        sizeof(table_entry->pstIFMS1000DgLaserACBias));
                table_entry->pstIFMS1000DgLaserACBias_len =
                        table_entry->old_pstIFMS1000DgLaserACBias_len;
                break;
            case COLUMN_PSTIFMS1000DGLASERDCBIAS:
                memcpy( table_entry->pstIFMS1000DgLaserDCBias,
                        table_entry->old_pstIFMS1000DgLaserDCBias,
                        sizeof(table_entry->pstIFMS1000DgLaserDCBias));
                memset( table_entry->old_pstIFMS1000DgLaserDCBias, 0,
                        sizeof(table_entry->pstIFMS1000DgLaserDCBias));
                table_entry->pstIFMS1000DgLaserDCBias_len =
                        table_entry->old_pstIFMS1000DgLaserDCBias_len;
                break;
            case COLUMN_PSTIFMS1000DGLASERACMODULATION:
                memcpy( table_entry->pstIFMS1000DgLaserACModulation,
                        table_entry->old_pstIFMS1000DgLaserACModulation,
                        sizeof(table_entry->pstIFMS1000DgLaserACModulation));
                memset( table_entry->old_pstIFMS1000DgLaserACModulation, 0,
                        sizeof(table_entry->pstIFMS1000DgLaserACModulation));
                table_entry->pstIFMS1000DgLaserACModulation_len =
                        table_entry->old_pstIFMS1000DgLaserACModulation_len;
                break;
            case COLUMN_PSTIFMS1000DGLASERDCMODULATION:
                memcpy( table_entry->pstIFMS1000DgLaserDCModulation,
                        table_entry->old_pstIFMS1000DgLaserDCModulation,
                        sizeof(table_entry->pstIFMS1000DgLaserDCModulation));
                memset( table_entry->old_pstIFMS1000DgLaserDCModulation, 0,
                        sizeof(table_entry->pstIFMS1000DgLaserDCModulation));
                table_entry->pstIFMS1000DgLaserDCModulation_len =
                        table_entry->old_pstIFMS1000DgLaserDCModulation_len;
                break;
            case COLUMN_PSTIFMS1000DGLASEREN:
                table_entry->pstIFMS1000DgLaserEn     = table_entry->old_pstIFMS1000DgLaserEn;
                table_entry->old_pstIFMS1000DgLaserEn = 0;
                break;
            case COLUMN_PSTIFMS1000DGPWM:
                table_entry->pstIFMS1000DgPwm     = table_entry->old_pstIFMS1000DgPwm;
                table_entry->old_pstIFMS1000DgPwm = 0;
                break;
            case COLUMN_PSTIFMS1000DGSEED:
                table_entry->pstIFMS1000DgSeed     = table_entry->old_pstIFMS1000DgSeed;
                table_entry->old_pstIFMS1000DgSeed = 0;
                break;
            case COLUMN_PSTIFMS1000DGPRBS:
                table_entry->pstIFMS1000DgPrbs     = table_entry->old_pstIFMS1000DgPrbs;
                table_entry->old_pstIFMS1000DgPrbs = 0;
                break;
            case COLUMN_PSTIFMS1000DGAVERAGE:
                table_entry->pstIFMS1000DgAverage     = table_entry->old_pstIFMS1000DgAverage;
                table_entry->old_pstIFMS1000DgAverage = 0;
                break;
            case COLUMN_PSTIFMS1000DGREGADDR:
                table_entry->pstIFMS1000DgRegAddr     = table_entry->old_pstIFMS1000DgRegAddr;
                table_entry->old_pstIFMS1000DgRegAddr = 0;
                break;
            case COLUMN_PSTIFMS1000DGREGVALUE:
                table_entry->pstIFMS1000DgRegValue     = table_entry->old_pstIFMS1000DgRegValue;
                table_entry->old_pstIFMS1000DgRegValue = 0;
                break;
            case COLUMN_PSTIFMS1000DGMASKSTARTPOINT:
                memcpy( table_entry->pstIFMS1000DgMaskStartPoint,
                        table_entry->old_pstIFMS1000DgMaskStartPoint,
                        sizeof(table_entry->pstIFMS1000DgMaskStartPoint));
                memset( table_entry->old_pstIFMS1000DgMaskStartPoint, 0,
                        sizeof(table_entry->pstIFMS1000DgMaskStartPoint));
                table_entry->pstIFMS1000DgMaskStartPoint_len =
                        table_entry->old_pstIFMS1000DgMaskStartPoint_len;
                break;
            case COLUMN_PSTIFMS1000DGMASKSTOPPOINT:
                memcpy( table_entry->pstIFMS1000DgMaskStopPoint,
                        table_entry->old_pstIFMS1000DgMaskStopPoint,
                        sizeof(table_entry->pstIFMS1000DgMaskStopPoint));
                memset( table_entry->old_pstIFMS1000DgMaskStopPoint, 0,
                        sizeof(table_entry->pstIFMS1000DgMaskStopPoint));
                table_entry->pstIFMS1000DgMaskStopPoint_len =
                        table_entry->old_pstIFMS1000DgMaskStopPoint_len;
                break;
            case COLUMN_PSTIFMS1000DGMASKACTION:
                table_entry->pstIFMS1000DgMaskAction     = table_entry->old_pstIFMS1000DgMaskAction;
                table_entry->old_pstIFMS1000DgMaskAction = 0;
                break;
            case COLUMN_PSTIFMS1000DGMEASUREDELTATHLD:
                memcpy( table_entry->pstIFMS1000DgMeasureDeltaThld,
                        table_entry->old_pstIFMS1000DgMeasureDeltaThld,
                        sizeof(table_entry->pstIFMS1000DgMeasureDeltaThld));
                memset( table_entry->old_pstIFMS1000DgMeasureDeltaThld, 0,
                        sizeof(table_entry->pstIFMS1000DgMeasureDeltaThld));
                table_entry->pstIFMS1000DgMeasureDeltaThld_len =
                        table_entry->old_pstIFMS1000DgMeasureDeltaThld_len;
                break;
            case COLUMN_PSTIFMS1000DGCUTPOINTTHLD:
                memcpy( table_entry->pstIFMS1000DgCutPointThld,
                        table_entry->old_pstIFMS1000DgCutPointThld,
                        sizeof(table_entry->pstIFMS1000DgCutPointThld));
                memset( table_entry->old_pstIFMS1000DgCutPointThld, 0,
                        sizeof(table_entry->pstIFMS1000DgCutPointThld));
                table_entry->pstIFMS1000DgCutPointThld_len =
                        table_entry->old_pstIFMS1000DgCutPointThld_len;
                break;
            case COLUMN_PSTIFMS1000DGPERIOD:
                table_entry->pstIFMS1000DgPeriod     = table_entry->old_pstIFMS1000DgPeriod;
                table_entry->old_pstIFMS1000DgPeriod = 0;
                break;
            case COLUMN_PSTIFMS1000DGDAC:
                table_entry->pstIFMS1000DgDAC     = table_entry->old_pstIFMS1000DgDAC;
                table_entry->old_pstIFMS1000DgDAC = 0;
                break;
            case COLUMN_PSTIFMS1000DGCOUNTERCLOCKMODE:
                table_entry->pstIFMS1000DgCounterClockMode     = table_entry->old_pstIFMS1000DgCounterClockMode;
                table_entry->old_pstIFMS1000DgCounterClockMode = 0;
                break;
            case COLUMN_PSTIFMS1000DGSCANRUNTYPE:
                table_entry->pstIFMS1000DgScanRunType     = table_entry->old_pstIFMS1000DgScanRunType;
                table_entry->old_pstIFMS1000DgScanRunType = 0;
                break;
            case COLUMN_PSTIFMS1000DGOPT:
                table_entry->pstIFMS1000DgOpt     = table_entry->old_pstIFMS1000DgOpt;
                table_entry->old_pstIFMS1000DgOpt = 0;
                break;
            case COLUMN_PSTIFMS1000DGFIBEROFFSET:
                memcpy( table_entry->pstIFMS1000DgFiberOffset,
                        table_entry->old_pstIFMS1000DgFiberOffset,
                        sizeof(table_entry->pstIFMS1000DgFiberOffset));
                memset( table_entry->old_pstIFMS1000DgFiberOffset, 0,
                        sizeof(table_entry->pstIFMS1000DgFiberOffset));
                table_entry->pstIFMS1000DgFiberOffset_len =
                        table_entry->old_pstIFMS1000DgFiberOffset_len;
                break;
            case COLUMN_PSTIFMS1000DGTESTWAVELEN:
                table_entry->pstIFMS1000DgTestWaveLen     = table_entry->old_pstIFMS1000DgTestWaveLen;
                table_entry->old_pstIFMS1000DgTestWaveLen = 0;
                break;
            case COLUMN_PSTIFMS1000DGPRT:
                table_entry->pstIFMS1000DgPRT     = table_entry->old_pstIFMS1000DgPRT;
                table_entry->old_pstIFMS1000DgPRT = 0;
                break;
            case COLUMN_PSTIFMS1000DGPPW:
                table_entry->pstIFMS1000DgPPW     = table_entry->old_pstIFMS1000DgPPW;
                table_entry->old_pstIFMS1000DgPPW = 0;
                break;
            case COLUMN_PSTIFMS1000DGPPRESCALE:
                table_entry->pstIFMS1000DgPPrescale     = table_entry->old_pstIFMS1000DgPPrescale;
                table_entry->old_pstIFMS1000DgPPrescale = 0;
                break;
            case COLUMN_PSTIFMS1000DGPAVG:
                table_entry->pstIFMS1000DgPAvg     = table_entry->old_pstIFMS1000DgPAvg;
                table_entry->old_pstIFMS1000DgPAvg = 0;
                break;
            case COLUMN_PSTIFMS1000DGPGAIN:
                table_entry->pstIFMS1000DgPGain     = table_entry->old_pstIFMS1000DgPGain;
                table_entry->old_pstIFMS1000DgPGain = 0;
                break;
            case COLUMN_PSTIFMS1000DGPE2PROMACTION:
                table_entry->pstIFMS1000DgPE2promAction     = table_entry->old_pstIFMS1000DgPE2promAction;
                table_entry->old_pstIFMS1000DgPE2promAction = 0;
                break;
            }
        }
        break;

    case MODE_SET_COMMIT:
        break;
    }
    return SNMP_ERR_NOERROR;
}

/** Initialize the pstIFMS1000DebugRegTable table by defining its contents and how it's structured */
void
QPSTProduct::initialize_table_pstIFMS1000DebugRegTable(void)
{
    const oid pstIFMS1000DebugRegTable_oid[] = {1,3,6,1,4,1,48391,3,5,8};
    const size_t pstIFMS1000DebugRegTable_oid_len   = OID_LENGTH(pstIFMS1000DebugRegTable_oid);
    netsnmp_handler_registration    *reg;
    netsnmp_tdata                   *table_data;
    netsnmp_table_registration_info *table_info;

    DEBUGMSGTL(("pstIFMS1000:init", "initializing table pstIFMS1000DebugRegTable\n"));

    reg = netsnmp_create_handler_registration(
              "pstIFMS1000DebugRegTable",     pstIFMS1000DebugRegTable_handler,
              pstIFMS1000DebugRegTable_oid, pstIFMS1000DebugRegTable_oid_len,
              HANDLER_CAN_RWRITE
              );

    table_data = netsnmp_tdata_create_table( "pstIFMS1000DebugRegTable", 0 );
    if (NULL == table_data) {
        snmp_log(LOG_ERR,"error creating tdata table for pstIFMS1000DebugRegTable\n");
        return;
    }
    table_info = SNMP_MALLOC_TYPEDEF( netsnmp_table_registration_info );
    if (NULL == table_info) {
        snmp_log(LOG_ERR,"error creating table info for pstIFMS1000DebugRegTable\n");
        return;
    }
    netsnmp_table_helper_add_indexes(table_info,
                           ASN_INTEGER,  /* index: pstIFMS1000DbPortNum */
                           0);

    table_info->min_column = COLUMN_PSTIFMS1000DBPORTNUM;
    table_info->max_column = COLUMN_PSTIFMS1000DBREGVALUE;
    
    netsnmp_tdata_register( reg, table_data, table_info );

    /* Initialise the contents of the table here */
}

//    /* Typical data structure for a row entry */
//struct pstIFMS1000DebugRegTable_entry {
//    /* Index values */
//    long pstIFMS1000DbPortNum;

//    /* Column values */
//    long pstIFMS1000DbPortNum;
//    long pstIFMS1000DbRegAddr;
//    long old_pstIFMS1000DbRegAddr;
//    long pstIFMS1000DbRegValue;
//    long old_pstIFMS1000DbRegValue;

//    int   valid;
//};

/* create a new row in the table */
static netsnmp_tdata_row *
pstIFMS1000DebugRegTable_createEntry(netsnmp_tdata *table_data
                 , long  pstIFMS1000DbPortNum
                ) {
    struct pstIFMS1000DebugRegTable_entry *entry;
    netsnmp_tdata_row *row;

    entry = SNMP_MALLOC_TYPEDEF(struct pstIFMS1000DebugRegTable_entry);
    if (!entry)
        return NULL;

    row = netsnmp_tdata_create_row();
    if (!row) {
        SNMP_FREE(entry);
        return NULL;
    }
    row->data = entry;

    DEBUGMSGT(("pstIFMS1000DebugRegTable:entry:create", "row 0x%x\n", (uintptr_t)row));
    entry->pstIFMS1000DbPortNum = pstIFMS1000DbPortNum;
    netsnmp_tdata_row_add_index( row, ASN_INTEGER,
                                 &(entry->pstIFMS1000DbPortNum),
                                 sizeof(entry->pstIFMS1000DbPortNum));
    if (table_data)
        netsnmp_tdata_add_row( table_data, row );
    return row;
}

/* remove a row from the table */
static void
pstIFMS1000DebugRegTable_removeEntry(netsnmp_tdata     *table_data, 
                 netsnmp_tdata_row *row) {
    struct pstIFMS1000DebugRegTable_entry *entry;

    if (!row)
        return;    /* Nothing to remove */

    DEBUGMSGT(("pstIFMS1000DebugRegTable:entry:remove", "row 0x%x\n", (uintptr_t)row));

    entry = (struct pstIFMS1000DebugRegTable_entry *)row->data;
    SNMP_FREE( entry );   /* XXX - release any other internal resources */

    if (table_data)
        netsnmp_tdata_remove_and_delete_row( table_data, row );
    else
        netsnmp_tdata_delete_row( row );    
}


/** handles requests for the pstIFMS1000DebugRegTable table */
int
QPSTProduct::pstIFMS1000DebugRegTable_handler(
    netsnmp_mib_handler               *handler,
    netsnmp_handler_registration      *reginfo,
    netsnmp_agent_request_info        *reqinfo,
    netsnmp_request_info              *requests) {

    netsnmp_request_info       *request;
    netsnmp_table_request_info *table_info;
    netsnmp_tdata              *table_data;
    netsnmp_tdata_row          *table_row;
    struct pstIFMS1000DebugRegTable_entry          *table_entry;
    int                         ret;

    DEBUGMSGTL(("pstIFMS1000:handler", "Processing request (%d)\n", reqinfo->mode));

    switch (reqinfo->mode) {
        /*
         * Read-support (also covers GetNext requests)
         */
    case MODE_GET:
        for (request=requests; request; request=request->next) {
            if (request->processed)
                continue;

            table_entry = (struct pstIFMS1000DebugRegTable_entry *)
                              netsnmp_tdata_extract_entry(request);
            table_info  =     netsnmp_extract_table_info( request);
    
            switch (table_info->colnum) {
            case COLUMN_PSTIFMS1000DBPORTNUM:
                if ( !table_entry ) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_NOSUCHINSTANCE);
                    continue;
                }
                snmp_set_var_typed_integer( request->requestvb, ASN_INTEGER,
                                            table_entry->pstIFMS1000DbPortNum);
                break;
            case COLUMN_PSTIFMS1000DBREGADDR:
                if ( !table_entry ) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_NOSUCHINSTANCE);
                    continue;
                }
                snmp_set_var_typed_integer( request->requestvb, ASN_INTEGER,
                                            table_entry->pstIFMS1000DbRegAddr);
                break;
            case COLUMN_PSTIFMS1000DBREGVALUE:
                if ( !table_entry ) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_NOSUCHINSTANCE);
                    continue;
                }
                snmp_set_var_typed_integer( request->requestvb, ASN_INTEGER,
                                            table_entry->pstIFMS1000DbRegValue);
                break;
            default:
                netsnmp_set_request_error(reqinfo, request,
                                          SNMP_NOSUCHOBJECT);
                break;
            }
        }
        break;

        /*
         * Write-support
         */
    case MODE_SET_RESERVE1:
        for (request=requests; request; request=request->next) {
            if (request->processed)
                continue;

            table_entry = (struct pstIFMS1000DebugRegTable_entry *)
                              netsnmp_tdata_extract_entry(request);
            table_info  =     netsnmp_extract_table_info( request);
    
            switch (table_info->colnum) {
            case COLUMN_PSTIFMS1000DBREGADDR:
                /* or possibly 'netsnmp_check_vb_int_range' */
                ret = netsnmp_check_vb_int( request->requestvb );
                if ( ret != SNMP_ERR_NOERROR ) {
                    netsnmp_set_request_error( reqinfo, request, ret );
                    return SNMP_ERR_NOERROR;
                }
                break;
            case COLUMN_PSTIFMS1000DBREGVALUE:
                /* or possibly 'netsnmp_check_vb_int_range' */
                ret = netsnmp_check_vb_int( request->requestvb );
                if ( ret != SNMP_ERR_NOERROR ) {
                    netsnmp_set_request_error( reqinfo, request, ret );
                    return SNMP_ERR_NOERROR;
                }
                break;
            default:
                netsnmp_set_request_error( reqinfo, request,
                                           SNMP_ERR_NOTWRITABLE );
                return SNMP_ERR_NOERROR;
            }
        }
        break;

    case MODE_SET_RESERVE2:
        break;

    case MODE_SET_FREE:
        break;

    case MODE_SET_ACTION:
        for (request=requests; request; request=request->next) {
            if (request->processed)
                continue;

            table_entry = (struct pstIFMS1000DebugRegTable_entry *)
                              netsnmp_tdata_extract_entry(request);
            table_info  =     netsnmp_extract_table_info( request);
    
            switch (table_info->colnum) {
            case COLUMN_PSTIFMS1000DBREGADDR:
                table_entry->old_pstIFMS1000DbRegAddr = table_entry->pstIFMS1000DbRegAddr;
                table_entry->pstIFMS1000DbRegAddr     = *request->requestvb->val.integer;
                break;
            case COLUMN_PSTIFMS1000DBREGVALUE:
                table_entry->old_pstIFMS1000DbRegValue = table_entry->pstIFMS1000DbRegValue;
                table_entry->pstIFMS1000DbRegValue     = *request->requestvb->val.integer;
                break;
            }
        }
        break;

    case MODE_SET_UNDO:
        for (request=requests; request; request=request->next) {
            if (request->processed)
                continue;

            table_entry = (struct pstIFMS1000DebugRegTable_entry *)
                              netsnmp_tdata_extract_entry(request);
            table_row   =     netsnmp_tdata_extract_row(  request);
            table_data  =     netsnmp_tdata_extract_table(request);
            table_info  =     netsnmp_extract_table_info( request);
    
            switch (table_info->colnum) {
            case COLUMN_PSTIFMS1000DBREGADDR:
                table_entry->pstIFMS1000DbRegAddr     = table_entry->old_pstIFMS1000DbRegAddr;
                table_entry->old_pstIFMS1000DbRegAddr = 0;
                break;
            case COLUMN_PSTIFMS1000DBREGVALUE:
                table_entry->pstIFMS1000DbRegValue     = table_entry->old_pstIFMS1000DbRegValue;
                table_entry->old_pstIFMS1000DbRegValue = 0;
                break;
            }
        }
        break;

    case MODE_SET_COMMIT:
        break;
    }
    return SNMP_ERR_NOERROR;
}

/** Initialize the pstIFMS1000DebugDACTable table by defining its contents and how it's structured */
void
QPSTProduct::initialize_table_pstIFMS1000DebugDACTable(void)
{
    const oid pstIFMS1000DebugDACTable_oid[] = {1,3,6,1,4,1,48391,3,5,9};
    const size_t pstIFMS1000DebugDACTable_oid_len   = OID_LENGTH(pstIFMS1000DebugDACTable_oid);
    netsnmp_handler_registration    *reg;
    netsnmp_tdata                   *table_data;
    netsnmp_table_registration_info *table_info;

    DEBUGMSGTL(("pstIFMS1000:init", "initializing table pstIFMS1000DebugDACTable\n"));

    reg = netsnmp_create_handler_registration(
              "pstIFMS1000DebugDACTable",     pstIFMS1000DebugDACTable_handler,
              pstIFMS1000DebugDACTable_oid, pstIFMS1000DebugDACTable_oid_len,
              HANDLER_CAN_RWRITE
              );

    table_data = netsnmp_tdata_create_table( "pstIFMS1000DebugDACTable", 0 );
    if (NULL == table_data) {
        snmp_log(LOG_ERR,"error creating tdata table for pstIFMS1000DebugDACTable\n");
        return;
    }
    table_info = SNMP_MALLOC_TYPEDEF( netsnmp_table_registration_info );
    if (NULL == table_info) {
        snmp_log(LOG_ERR,"error creating table info for pstIFMS1000DebugDACTable\n");
        return;
    }
    netsnmp_table_helper_add_indexes(table_info,
                           ASN_INTEGER,  /* index: pstIFMS1000DacTPortNum */
                           0);

    table_info->min_column = COLUMN_PSTIFMS1000DACTPORTNUM;
    table_info->max_column = COLUMN_PSTIFMS1000TDACVALUE;
    
    netsnmp_tdata_register( reg, table_data, table_info );

    /* Initialise the contents of the table here */
}

//    /* Typical data structure for a row entry */
//struct pstIFMS1000DebugDACTable_entry {
//    /* Index values */
//    long pstIFMS1000DacTPortNum;

//    /* Column values */
//    long pstIFMS1000DacTPortNum;
//    long pstIFMS1000DacTChannelNum;
//    long old_pstIFMS1000DacTChannelNum;
//    long pstIFMS1000TDacValue;
//    long old_pstIFMS1000TDacValue;

//    int   valid;
//};

/* create a new row in the table */
static netsnmp_tdata_row *
pstIFMS1000DebugDACTable_createEntry(netsnmp_tdata *table_data
                 , long  pstIFMS1000DacTPortNum
                ) {
    struct pstIFMS1000DebugDACTable_entry *entry;
    netsnmp_tdata_row *row;

    entry = SNMP_MALLOC_TYPEDEF(struct pstIFMS1000DebugDACTable_entry);
    if (!entry)
        return NULL;

    row = netsnmp_tdata_create_row();
    if (!row) {
        SNMP_FREE(entry);
        return NULL;
    }
    row->data = entry;

    DEBUGMSGT(("pstIFMS1000DebugDACTable:entry:create", "row 0x%x\n", (uintptr_t)row));
    entry->pstIFMS1000DacTPortNum = pstIFMS1000DacTPortNum;
    netsnmp_tdata_row_add_index( row, ASN_INTEGER,
                                 &(entry->pstIFMS1000DacTPortNum),
                                 sizeof(entry->pstIFMS1000DacTPortNum));
    if (table_data)
        netsnmp_tdata_add_row( table_data, row );
    return row;
}

/* remove a row from the table */
static void
pstIFMS1000DebugDACTable_removeEntry(netsnmp_tdata     *table_data, 
                 netsnmp_tdata_row *row) {
    struct pstIFMS1000DebugDACTable_entry *entry;

    if (!row)
        return;    /* Nothing to remove */

    DEBUGMSGT(("pstIFMS1000DebugDACTable:entry:remove", "row 0x%x\n", (uintptr_t)row));

    entry = (struct pstIFMS1000DebugDACTable_entry *)row->data;
    SNMP_FREE( entry );   /* XXX - release any other internal resources */

    if (table_data)
        netsnmp_tdata_remove_and_delete_row( table_data, row );
    else
        netsnmp_tdata_delete_row( row );    
}


/** handles requests for the pstIFMS1000DebugDACTable table */
int
QPSTProduct::pstIFMS1000DebugDACTable_handler(
    netsnmp_mib_handler               *handler,
    netsnmp_handler_registration      *reginfo,
    netsnmp_agent_request_info        *reqinfo,
    netsnmp_request_info              *requests) {

    netsnmp_request_info       *request;
    netsnmp_table_request_info *table_info;
    netsnmp_tdata              *table_data;
    netsnmp_tdata_row          *table_row;
    struct pstIFMS1000DebugDACTable_entry          *table_entry;
    int                         ret;

    DEBUGMSGTL(("pstIFMS1000:handler", "Processing request (%d)\n", reqinfo->mode));

    switch (reqinfo->mode) {
        /*
         * Read-support (also covers GetNext requests)
         */
    case MODE_GET:
        for (request=requests; request; request=request->next) {
            if (request->processed)
                continue;

            table_entry = (struct pstIFMS1000DebugDACTable_entry *)
                              netsnmp_tdata_extract_entry(request);
            table_info  =     netsnmp_extract_table_info( request);
    
            switch (table_info->colnum) {
            case COLUMN_PSTIFMS1000DACTPORTNUM:
                if ( !table_entry ) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_NOSUCHINSTANCE);
                    continue;
                }
                snmp_set_var_typed_integer( request->requestvb, ASN_INTEGER,
                                            table_entry->pstIFMS1000DacTPortNum);
                break;
            case COLUMN_PSTIFMS1000DACTCHANNELNUM:
                if ( !table_entry ) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_NOSUCHINSTANCE);
                    continue;
                }
                snmp_set_var_typed_integer( request->requestvb, ASN_INTEGER,
                                            table_entry->pstIFMS1000DacTChannelNum);
                break;
            case COLUMN_PSTIFMS1000TDACVALUE:
                if ( !table_entry ) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_NOSUCHINSTANCE);
                    continue;
                }
                snmp_set_var_typed_integer( request->requestvb, ASN_INTEGER,
                                            table_entry->pstIFMS1000TDacValue);
                break;
            default:
                netsnmp_set_request_error(reqinfo, request,
                                          SNMP_NOSUCHOBJECT);
                break;
            }
        }
        break;

        /*
         * Write-support
         */
    case MODE_SET_RESERVE1:
        for (request=requests; request; request=request->next) {
            if (request->processed)
                continue;

            table_entry = (struct pstIFMS1000DebugDACTable_entry *)
                              netsnmp_tdata_extract_entry(request);
            table_info  =     netsnmp_extract_table_info( request);
    
            switch (table_info->colnum) {
            case COLUMN_PSTIFMS1000DACTCHANNELNUM:
                /* or possibly 'netsnmp_check_vb_int_range' */
                ret = netsnmp_check_vb_int( request->requestvb );
                if ( ret != SNMP_ERR_NOERROR ) {
                    netsnmp_set_request_error( reqinfo, request, ret );
                    return SNMP_ERR_NOERROR;
                }
                break;
            case COLUMN_PSTIFMS1000TDACVALUE:
                /* or possibly 'netsnmp_check_vb_int_range' */
                ret = netsnmp_check_vb_int( request->requestvb );
                if ( ret != SNMP_ERR_NOERROR ) {
                    netsnmp_set_request_error( reqinfo, request, ret );
                    return SNMP_ERR_NOERROR;
                }
                break;
            default:
                netsnmp_set_request_error( reqinfo, request,
                                           SNMP_ERR_NOTWRITABLE );
                return SNMP_ERR_NOERROR;
            }
        }
        break;

    case MODE_SET_RESERVE2:
        break;

    case MODE_SET_FREE:
        break;

    case MODE_SET_ACTION:
        for (request=requests; request; request=request->next) {
            if (request->processed)
                continue;

            table_entry = (struct pstIFMS1000DebugDACTable_entry *)
                              netsnmp_tdata_extract_entry(request);
            table_info  =     netsnmp_extract_table_info( request);
    
            switch (table_info->colnum) {
            case COLUMN_PSTIFMS1000DACTCHANNELNUM:
                table_entry->old_pstIFMS1000DacTChannelNum = table_entry->pstIFMS1000DacTChannelNum;
                table_entry->pstIFMS1000DacTChannelNum     = *request->requestvb->val.integer;
                break;
            case COLUMN_PSTIFMS1000TDACVALUE:
                table_entry->old_pstIFMS1000TDacValue = table_entry->pstIFMS1000TDacValue;
                table_entry->pstIFMS1000TDacValue     = *request->requestvb->val.integer;
                break;
            }
        }
        break;

    case MODE_SET_UNDO:
        for (request=requests; request; request=request->next) {
            if (request->processed)
                continue;

            table_entry = (struct pstIFMS1000DebugDACTable_entry *)
                              netsnmp_tdata_extract_entry(request);
            table_row   =     netsnmp_tdata_extract_row(  request);
            table_data  =     netsnmp_tdata_extract_table(request);
            table_info  =     netsnmp_extract_table_info( request);
    
            switch (table_info->colnum) {
            case COLUMN_PSTIFMS1000DACTCHANNELNUM:
                table_entry->pstIFMS1000DacTChannelNum     = table_entry->old_pstIFMS1000DacTChannelNum;
                table_entry->old_pstIFMS1000DacTChannelNum = 0;
                break;
            case COLUMN_PSTIFMS1000TDACVALUE:
                table_entry->pstIFMS1000TDacValue     = table_entry->old_pstIFMS1000TDacValue;
                table_entry->old_pstIFMS1000TDacValue = 0;
                break;
            }
        }
        break;

    case MODE_SET_COMMIT:
        break;
    }
    return SNMP_ERR_NOERROR;
}

/** Initialize the pstIFMS1000DebugE2promTable table by defining its contents and how it's structured */
void
QPSTProduct::initialize_table_pstIFMS1000DebugE2promTable(void)
{
    const oid pstIFMS1000DebugE2promTable_oid[] = {1,3,6,1,4,1,48391,3,5,10};
    const size_t pstIFMS1000DebugE2promTable_oid_len   = OID_LENGTH(pstIFMS1000DebugE2promTable_oid);
    netsnmp_handler_registration    *reg;
    netsnmp_tdata                   *table_data;
    netsnmp_table_registration_info *table_info;

    DEBUGMSGTL(("pstIFMS1000:init", "initializing table pstIFMS1000DebugE2promTable\n"));

    reg = netsnmp_create_handler_registration(
              "pstIFMS1000DebugE2promTable",     pstIFMS1000DebugE2promTable_handler,
              pstIFMS1000DebugE2promTable_oid, pstIFMS1000DebugE2promTable_oid_len,
              HANDLER_CAN_RWRITE
              );

    table_data = netsnmp_tdata_create_table( "pstIFMS1000DebugE2promTable", 0 );
    if (NULL == table_data) {
        snmp_log(LOG_ERR,"error creating tdata table for pstIFMS1000DebugE2promTable\n");
        return;
    }
    table_info = SNMP_MALLOC_TYPEDEF( netsnmp_table_registration_info );
    if (NULL == table_info) {
        snmp_log(LOG_ERR,"error creating table info for pstIFMS1000DebugE2promTable\n");
        return;
    }
    netsnmp_table_helper_add_indexes(table_info,
                           ASN_INTEGER,  /* index: pstIFMS1000DbE2TPortNum */
                           0);

    table_info->min_column = COLUMN_PSTIFMS1000DBE2TPORTNUM;
    table_info->max_column = COLUMN_PSTIFMS1000DBE2TVALUE;
    
    netsnmp_tdata_register( reg, table_data, table_info );

    /* Initialise the contents of the table here */
}

//    /* Typical data structure for a row entry */
//struct pstIFMS1000DebugE2promTable_entry {
//    /* Index values */
//    long pstIFMS1000DbE2TPortNum;

//    /* Column values */
//    long pstIFMS1000DbE2TPortNum;
//    long pstIFMS1000DbE2TAddr;
//    long old_pstIFMS1000DbE2TAddr;
//    long pstIFMS1000DbE2TValue;
//    long old_pstIFMS1000DbE2TValue;

//    int   valid;
//};

/* create a new row in the table */
static netsnmp_tdata_row *
pstIFMS1000DebugE2promTable_createEntry(netsnmp_tdata *table_data
                 , long  pstIFMS1000DbE2TPortNum
                ) {
    struct pstIFMS1000DebugE2promTable_entry *entry;
    netsnmp_tdata_row *row;

    entry = SNMP_MALLOC_TYPEDEF(struct pstIFMS1000DebugE2promTable_entry);
    if (!entry)
        return NULL;

    row = netsnmp_tdata_create_row();
    if (!row) {
        SNMP_FREE(entry);
        return NULL;
    }
    row->data = entry;

    DEBUGMSGT(("pstIFMS1000DebugE2promTable:entry:create", "row 0x%x\n", (uintptr_t)row));
    entry->pstIFMS1000DbE2TPortNum = pstIFMS1000DbE2TPortNum;
    netsnmp_tdata_row_add_index( row, ASN_INTEGER,
                                 &(entry->pstIFMS1000DbE2TPortNum),
                                 sizeof(entry->pstIFMS1000DbE2TPortNum));
    if (table_data)
        netsnmp_tdata_add_row( table_data, row );
    return row;
}

/* remove a row from the table */
static void
pstIFMS1000DebugE2promTable_removeEntry(netsnmp_tdata     *table_data, 
                 netsnmp_tdata_row *row) {
    struct pstIFMS1000DebugE2promTable_entry *entry;

    if (!row)
        return;    /* Nothing to remove */

    DEBUGMSGT(("pstIFMS1000DebugE2promTable:entry:remove", "row 0x%x\n", (uintptr_t)row));

    entry = (struct pstIFMS1000DebugE2promTable_entry *)row->data;
    SNMP_FREE( entry );   /* XXX - release any other internal resources */

    if (table_data)
        netsnmp_tdata_remove_and_delete_row( table_data, row );
    else
        netsnmp_tdata_delete_row( row );    
}


/** handles requests for the pstIFMS1000DebugE2promTable table */
int
QPSTProduct::pstIFMS1000DebugE2promTable_handler(
    netsnmp_mib_handler               *handler,
    netsnmp_handler_registration      *reginfo,
    netsnmp_agent_request_info        *reqinfo,
    netsnmp_request_info              *requests) {

    netsnmp_request_info       *request;
    netsnmp_table_request_info *table_info;
    netsnmp_tdata              *table_data;
    netsnmp_tdata_row          *table_row;
    struct pstIFMS1000DebugE2promTable_entry          *table_entry;
    int                         ret;

    DEBUGMSGTL(("pstIFMS1000:handler", "Processing request (%d)\n", reqinfo->mode));

    switch (reqinfo->mode) {
        /*
         * Read-support (also covers GetNext requests)
         */
    case MODE_GET:
        for (request=requests; request; request=request->next) {
            if (request->processed)
                continue;

            table_entry = (struct pstIFMS1000DebugE2promTable_entry *)
                              netsnmp_tdata_extract_entry(request);
            table_info  =     netsnmp_extract_table_info( request);
    
            switch (table_info->colnum) {
            case COLUMN_PSTIFMS1000DBE2TPORTNUM:
                if ( !table_entry ) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_NOSUCHINSTANCE);
                    continue;
                }
                snmp_set_var_typed_integer( request->requestvb, ASN_INTEGER,
                                            table_entry->pstIFMS1000DbE2TPortNum);
                break;
            case COLUMN_PSTIFMS1000DBE2TADDR:
                if ( !table_entry ) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_NOSUCHINSTANCE);
                    continue;
                }
                snmp_set_var_typed_integer( request->requestvb, ASN_INTEGER,
                                            table_entry->pstIFMS1000DbE2TAddr);
                break;
            case COLUMN_PSTIFMS1000DBE2TVALUE:
                if ( !table_entry ) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_NOSUCHINSTANCE);
                    continue;
                }
                snmp_set_var_typed_integer( request->requestvb, ASN_INTEGER,
                                            table_entry->pstIFMS1000DbE2TValue);
                break;
            default:
                netsnmp_set_request_error(reqinfo, request,
                                          SNMP_NOSUCHOBJECT);
                break;
            }
        }
        break;

        /*
         * Write-support
         */
    case MODE_SET_RESERVE1:
        for (request=requests; request; request=request->next) {
            if (request->processed)
                continue;

            table_entry = (struct pstIFMS1000DebugE2promTable_entry *)
                              netsnmp_tdata_extract_entry(request);
            table_info  =     netsnmp_extract_table_info( request);
    
            switch (table_info->colnum) {
            case COLUMN_PSTIFMS1000DBE2TADDR:
                /* or possibly 'netsnmp_check_vb_int_range' */
                ret = netsnmp_check_vb_int( request->requestvb );
                if ( ret != SNMP_ERR_NOERROR ) {
                    netsnmp_set_request_error( reqinfo, request, ret );
                    return SNMP_ERR_NOERROR;
                }
                break;
            case COLUMN_PSTIFMS1000DBE2TVALUE:
                /* or possibly 'netsnmp_check_vb_int_range' */
                ret = netsnmp_check_vb_int( request->requestvb );
                if ( ret != SNMP_ERR_NOERROR ) {
                    netsnmp_set_request_error( reqinfo, request, ret );
                    return SNMP_ERR_NOERROR;
                }
                break;
            default:
                netsnmp_set_request_error( reqinfo, request,
                                           SNMP_ERR_NOTWRITABLE );
                return SNMP_ERR_NOERROR;
            }
        }
        break;

    case MODE_SET_RESERVE2:
        break;

    case MODE_SET_FREE:
        break;

    case MODE_SET_ACTION:
        for (request=requests; request; request=request->next) {
            if (request->processed)
                continue;

            table_entry = (struct pstIFMS1000DebugE2promTable_entry *)
                              netsnmp_tdata_extract_entry(request);
            table_info  =     netsnmp_extract_table_info( request);
    
            switch (table_info->colnum) {
            case COLUMN_PSTIFMS1000DBE2TADDR:
                table_entry->old_pstIFMS1000DbE2TAddr = table_entry->pstIFMS1000DbE2TAddr;
                table_entry->pstIFMS1000DbE2TAddr     = *request->requestvb->val.integer;
                break;
            case COLUMN_PSTIFMS1000DBE2TVALUE:
                table_entry->old_pstIFMS1000DbE2TValue = table_entry->pstIFMS1000DbE2TValue;
                table_entry->pstIFMS1000DbE2TValue     = *request->requestvb->val.integer;
                break;
            }
        }
        break;

    case MODE_SET_UNDO:
        for (request=requests; request; request=request->next) {
            if (request->processed)
                continue;

            table_entry = (struct pstIFMS1000DebugE2promTable_entry *)
                              netsnmp_tdata_extract_entry(request);
            table_row   =     netsnmp_tdata_extract_row(  request);
            table_data  =     netsnmp_tdata_extract_table(request);
            table_info  =     netsnmp_extract_table_info( request);
    
            switch (table_info->colnum) {
            case COLUMN_PSTIFMS1000DBE2TADDR:
                table_entry->pstIFMS1000DbE2TAddr     = table_entry->old_pstIFMS1000DbE2TAddr;
                table_entry->old_pstIFMS1000DbE2TAddr = 0;
                break;
            case COLUMN_PSTIFMS1000DBE2TVALUE:
                table_entry->pstIFMS1000DbE2TValue     = table_entry->old_pstIFMS1000DbE2TValue;
                table_entry->old_pstIFMS1000DbE2TValue = 0;
                break;
            }
        }
        break;

    case MODE_SET_COMMIT:
        break;
    }
    return SNMP_ERR_NOERROR;
}

/** Initialize the pstIFMS1000ExtendAlarmTable table by defining its contents and how it's structured */
void
QPSTProduct::initialize_table_pstIFMS1000ExtendAlarmTable(void)
{
    const oid pstIFMS1000ExtendAlarmTable_oid[] = {1,3,6,1,4,1,48391,3,5,12};
    const size_t pstIFMS1000ExtendAlarmTable_oid_len   = OID_LENGTH(pstIFMS1000ExtendAlarmTable_oid);
    netsnmp_handler_registration    *reg;
    netsnmp_tdata                   *table_data;
    netsnmp_table_registration_info *table_info;

    DEBUGMSGTL(("pstIFMS1000:init", "initializing table pstIFMS1000ExtendAlarmTable\n"));

    reg = netsnmp_create_handler_registration(
              "pstIFMS1000ExtendAlarmTable",     pstIFMS1000ExtendAlarmTable_handler,
              pstIFMS1000ExtendAlarmTable_oid, pstIFMS1000ExtendAlarmTable_oid_len,
              HANDLER_CAN_RWRITE
              );

    table_data = netsnmp_tdata_create_table( "pstIFMS1000ExtendAlarmTable", 0 );
    if (NULL == table_data) {
        snmp_log(LOG_ERR,"error creating tdata table for pstIFMS1000ExtendAlarmTable\n");
        return;
    }
    table_info = SNMP_MALLOC_TYPEDEF( netsnmp_table_registration_info );
    if (NULL == table_info) {
        snmp_log(LOG_ERR,"error creating table info for pstIFMS1000ExtendAlarmTable\n");
        return;
    }
    netsnmp_table_helper_add_indexes(table_info,
                           ASN_INTEGER,  /* index: pstIFMS1000EAPortNum */
                           0);

    table_info->min_column = COLUMN_PSTIFMS1000EAPORTNUM;
    table_info->max_column = COLUMN_PSTIFMS1000EXTENDALARM;
    
    netsnmp_tdata_register( reg, table_data, table_info );

    /* Initialise the contents of the table here */
}

//    /* Typical data structure for a row entry */
//struct pstIFMS1000ExtendAlarmTable_entry {
//    /* Index values */
//    long pstIFMS1000EAPortNum;

//    /* Column values */
//    long pstIFMS1000EAPortNum;
//    u_long pstIFMS1000ExtendAlarm;
//    u_long old_pstIFMS1000ExtendAlarm;

//    int   valid;
//};

/* create a new row in the table */
static netsnmp_tdata_row *
pstIFMS1000ExtendAlarmTable_createEntry(netsnmp_tdata *table_data
                 , long  pstIFMS1000EAPortNum
                ) {
    struct pstIFMS1000ExtendAlarmTable_entry *entry;
    netsnmp_tdata_row *row;

    entry = SNMP_MALLOC_TYPEDEF(struct pstIFMS1000ExtendAlarmTable_entry);
    if (!entry)
        return NULL;

    row = netsnmp_tdata_create_row();
    if (!row) {
        SNMP_FREE(entry);
        return NULL;
    }
    row->data = entry;

    DEBUGMSGT(("pstIFMS1000ExtendAlarmTable:entry:create", "row 0x%x\n", (uintptr_t)row));
    entry->pstIFMS1000EAPortNum = pstIFMS1000EAPortNum;
    netsnmp_tdata_row_add_index( row, ASN_INTEGER,
                                 &(entry->pstIFMS1000EAPortNum),
                                 sizeof(entry->pstIFMS1000EAPortNum));
    if (table_data)
        netsnmp_tdata_add_row( table_data, row );
    return row;
}

/* remove a row from the table */
static void
pstIFMS1000ExtendAlarmTable_removeEntry(netsnmp_tdata     *table_data, 
                 netsnmp_tdata_row *row) {
    struct pstIFMS1000ExtendAlarmTable_entry *entry;

    if (!row)
        return;    /* Nothing to remove */

    DEBUGMSGT(("pstIFMS1000ExtendAlarmTable:entry:remove", "row 0x%x\n", (uintptr_t)row));

    entry = (struct pstIFMS1000ExtendAlarmTable_entry *)row->data;
    SNMP_FREE( entry );   /* XXX - release any other internal resources */

    if (table_data)
        netsnmp_tdata_remove_and_delete_row( table_data, row );
    else
        netsnmp_tdata_delete_row( row );    
}


/** handles requests for the pstIFMS1000ExtendAlarmTable table */
int
QPSTProduct::pstIFMS1000ExtendAlarmTable_handler(
    netsnmp_mib_handler               *handler,
    netsnmp_handler_registration      *reginfo,
    netsnmp_agent_request_info        *reqinfo,
    netsnmp_request_info              *requests) {

    netsnmp_request_info       *request;
    netsnmp_table_request_info *table_info;
    netsnmp_tdata              *table_data;
    netsnmp_tdata_row          *table_row;
    struct pstIFMS1000ExtendAlarmTable_entry          *table_entry;
    int                         ret;

    DEBUGMSGTL(("pstIFMS1000:handler", "Processing request (%d)\n", reqinfo->mode));

    switch (reqinfo->mode) {
        /*
         * Read-support (also covers GetNext requests)
         */
    case MODE_GET:
        for (request=requests; request; request=request->next) {
            if (request->processed)
                continue;

            table_entry = (struct pstIFMS1000ExtendAlarmTable_entry *)
                              netsnmp_tdata_extract_entry(request);
            table_info  =     netsnmp_extract_table_info( request);
    
            switch (table_info->colnum) {
            case COLUMN_PSTIFMS1000EAPORTNUM:
                if ( !table_entry ) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_NOSUCHINSTANCE);
                    continue;
                }
                snmp_set_var_typed_integer( request->requestvb, ASN_INTEGER,
                                            table_entry->pstIFMS1000EAPortNum);
                break;
            case COLUMN_PSTIFMS1000EXTENDALARM:
                if ( !table_entry ) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_NOSUCHINSTANCE);
                    continue;
                }
                snmp_set_var_typed_integer( request->requestvb, ASN_UNSIGNED,
                                            table_entry->pstIFMS1000ExtendAlarm);
                break;
            default:
                netsnmp_set_request_error(reqinfo, request,
                                          SNMP_NOSUCHOBJECT);
                break;
            }
        }
        break;

        /*
         * Write-support
         */
    case MODE_SET_RESERVE1:
        for (request=requests; request; request=request->next) {
            if (request->processed)
                continue;

            table_entry = (struct pstIFMS1000ExtendAlarmTable_entry *)
                              netsnmp_tdata_extract_entry(request);
            table_info  =     netsnmp_extract_table_info( request);
    
            switch (table_info->colnum) {
            case COLUMN_PSTIFMS1000EXTENDALARM:
                /* or possibly 'netsnmp_check_vb_int_range' */
                ret = netsnmp_check_vb_int( request->requestvb );
                if ( ret != SNMP_ERR_NOERROR ) {
                    netsnmp_set_request_error( reqinfo, request, ret );
                    return SNMP_ERR_NOERROR;
                }
                break;
            default:
                netsnmp_set_request_error( reqinfo, request,
                                           SNMP_ERR_NOTWRITABLE );
                return SNMP_ERR_NOERROR;
            }
        }
        break;

    case MODE_SET_RESERVE2:
        break;

    case MODE_SET_FREE:
        break;

    case MODE_SET_ACTION:
        for (request=requests; request; request=request->next) {
            if (request->processed)
                continue;

            table_entry = (struct pstIFMS1000ExtendAlarmTable_entry *)
                              netsnmp_tdata_extract_entry(request);
            table_info  =     netsnmp_extract_table_info( request);
    
            switch (table_info->colnum) {
            case COLUMN_PSTIFMS1000EXTENDALARM:
                table_entry->old_pstIFMS1000ExtendAlarm = table_entry->pstIFMS1000ExtendAlarm;
                table_entry->pstIFMS1000ExtendAlarm     = *request->requestvb->val.integer;
                break;
            }
        }
        break;

    case MODE_SET_UNDO:
        for (request=requests; request; request=request->next) {
            if (request->processed)
                continue;

            table_entry = (struct pstIFMS1000ExtendAlarmTable_entry *)
                              netsnmp_tdata_extract_entry(request);
            table_row   =     netsnmp_tdata_extract_row(  request);
            table_data  =     netsnmp_tdata_extract_table(request);
            table_info  =     netsnmp_extract_table_info( request);
    
            switch (table_info->colnum) {
            case COLUMN_PSTIFMS1000EXTENDALARM:
                table_entry->pstIFMS1000ExtendAlarm     = table_entry->old_pstIFMS1000ExtendAlarm;
                table_entry->old_pstIFMS1000ExtendAlarm = 0;
                break;
            }
        }
        break;

    case MODE_SET_COMMIT:
        break;
    }
    return SNMP_ERR_NOERROR;
}

/** Initialize the pstIFMS1000ExpertExtendTable table by defining its contents and how it's structured */
void
QPSTProduct::initialize_table_pstIFMS1000ExpertExtendTable(void)
{
    const oid pstIFMS1000ExpertExtendTable_oid[] = {1,3,6,1,4,1,48391,3,5,13};
    const size_t pstIFMS1000ExpertExtendTable_oid_len   = OID_LENGTH(pstIFMS1000ExpertExtendTable_oid);
    netsnmp_handler_registration    *reg;
    netsnmp_tdata                   *table_data;
    netsnmp_table_registration_info *table_info;

    DEBUGMSGTL(("pstIFMS1000:init", "initializing table pstIFMS1000ExpertExtendTable\n"));

    reg = netsnmp_create_handler_registration(
              "pstIFMS1000ExpertExtendTable",     pstIFMS1000ExpertExtendTable_handler,
              pstIFMS1000ExpertExtendTable_oid, pstIFMS1000ExpertExtendTable_oid_len,
              HANDLER_CAN_RWRITE
              );

    table_data = netsnmp_tdata_create_table( "pstIFMS1000ExpertExtendTable", 0 );
    if (NULL == table_data) {
        snmp_log(LOG_ERR,"error creating tdata table for pstIFMS1000ExpertExtendTable\n");
        return;
    }
    table_info = SNMP_MALLOC_TYPEDEF( netsnmp_table_registration_info );
    if (NULL == table_info) {
        snmp_log(LOG_ERR,"error creating table info for pstIFMS1000ExpertExtendTable\n");
        return;
    }
    netsnmp_table_helper_add_indexes(table_info,
                           ASN_INTEGER,  /* index: pstIFMS1000EEPortNum */
                           0);

    table_info->min_column = COLUMN_PSTIFMS1000EEPORTNUM;
    table_info->max_column = COLUMN_PSTIFMS1000DGPBFACTOR;
    
    netsnmp_tdata_register( reg, table_data, table_info );

    /* Initialise the contents of the table here */
}

//    /* Typical data structure for a row entry */
//struct pstIFMS1000ExpertExtendTable_entry {
//    /* Index values */
//    long pstIFMS1000EEPortNum;

//    /* Column values */
//    long pstIFMS1000EEPortNum;
//    char pstIFMS1000DgPBias1[NNN];
//    size_t pstIFMS1000DgPBias1_len;
//    char old_pstIFMS1000DgPBias1[NNN];
//    size_t old_pstIFMS1000DgPBias1_len;
//    char pstIFMS1000DgPBias2[NNN];
//    size_t pstIFMS1000DgPBias2_len;
//    char old_pstIFMS1000DgPBias2[NNN];
//    size_t old_pstIFMS1000DgPBias2_len;
//    char pstIFMS1000DgPModulation1[NNN];
//    size_t pstIFMS1000DgPModulation1_len;
//    char old_pstIFMS1000DgPModulation1[NNN];
//    size_t old_pstIFMS1000DgPModulation1_len;
//    char pstIFMS1000DgPModulation2[NNN];
//    size_t pstIFMS1000DgPModulation2_len;
//    char old_pstIFMS1000DgPModulation2[NNN];
//    size_t old_pstIFMS1000DgPModulation2_len;
//    long pstIFMS1000DgPBackScatter;
//    long old_pstIFMS1000DgPBackScatter;
//    char pstIFMS1000DgPMeasureDeltaThld[NNN];
//    size_t pstIFMS1000DgPMeasureDeltaThld_len;
//    char old_pstIFMS1000DgPMeasureDeltaThld[NNN];
//    size_t old_pstIFMS1000DgPMeasureDeltaThld_len;
//    char pstIFMS1000DgPCutPointThld[NNN];
//    size_t pstIFMS1000DgPCutPointThld_len;
//    char old_pstIFMS1000DgPCutPointThld[NNN];
//    size_t old_pstIFMS1000DgPCutPointThld_len;
//    char pstIFMS1000DgPMFactor[NNN];
//    size_t pstIFMS1000DgPMFactor_len;
//    char old_pstIFMS1000DgPMFactor[NNN];
//    size_t old_pstIFMS1000DgPMFactor_len;
//    char pstIFMS1000DgFaultCriticalThld[NNN];
//    size_t pstIFMS1000DgFaultCriticalThld_len;
//    char old_pstIFMS1000DgFaultCriticalThld[NNN];
//    size_t old_pstIFMS1000DgFaultCriticalThld_len;
//    char pstIFMS1000DgFaultMajorThld[NNN];
//    size_t pstIFMS1000DgFaultMajorThld_len;
//    char old_pstIFMS1000DgFaultMajorThld[NNN];
//    size_t old_pstIFMS1000DgFaultMajorThld_len;
//    char pstIFMS1000DgFaultMinorThld[NNN];
//    size_t pstIFMS1000DgFaultMinorThld_len;
//    char old_pstIFMS1000DgFaultMinorThld[NNN];
//    size_t old_pstIFMS1000DgFaultMinorThld_len;
//    char pstIFMS1000DgPAFactor[NNN];
//    size_t pstIFMS1000DgPAFactor_len;
//    char old_pstIFMS1000DgPAFactor[NNN];
//    size_t old_pstIFMS1000DgPAFactor_len;
//    char pstIFMS1000DgPBFactor[NNN];
//    size_t pstIFMS1000DgPBFactor_len;
//    char old_pstIFMS1000DgPBFactor[NNN];
//    size_t old_pstIFMS1000DgPBFactor_len;

//    int   valid;
//};

/* create a new row in the table */
static netsnmp_tdata_row *
pstIFMS1000ExpertExtendTable_createEntry(netsnmp_tdata *table_data
                 , long  pstIFMS1000EEPortNum
                ) {
    struct pstIFMS1000ExpertExtendTable_entry *entry;
    netsnmp_tdata_row *row;

    entry = SNMP_MALLOC_TYPEDEF(struct pstIFMS1000ExpertExtendTable_entry);
    if (!entry)
        return NULL;

    row = netsnmp_tdata_create_row();
    if (!row) {
        SNMP_FREE(entry);
        return NULL;
    }
    row->data = entry;

    DEBUGMSGT(("pstIFMS1000ExpertExtendTable:entry:create", "row 0x%x\n", (uintptr_t)row));
    entry->pstIFMS1000EEPortNum = pstIFMS1000EEPortNum;
    netsnmp_tdata_row_add_index( row, ASN_INTEGER,
                                 &(entry->pstIFMS1000EEPortNum),
                                 sizeof(entry->pstIFMS1000EEPortNum));
    if (table_data)
        netsnmp_tdata_add_row( table_data, row );
    return row;
}

/* remove a row from the table */
static void
pstIFMS1000ExpertExtendTable_removeEntry(netsnmp_tdata     *table_data, 
                 netsnmp_tdata_row *row) {
    struct pstIFMS1000ExpertExtendTable_entry *entry;

    if (!row)
        return;    /* Nothing to remove */

    DEBUGMSGT(("pstIFMS1000ExpertExtendTable:entry:remove", "row 0x%x\n", (uintptr_t)row));

    entry = (struct pstIFMS1000ExpertExtendTable_entry *)row->data;
    SNMP_FREE( entry );   /* XXX - release any other internal resources */

    if (table_data)
        netsnmp_tdata_remove_and_delete_row( table_data, row );
    else
        netsnmp_tdata_delete_row( row );    
}


/** handles requests for the pstIFMS1000ExpertExtendTable table */
int
QPSTProduct::pstIFMS1000ExpertExtendTable_handler(
    netsnmp_mib_handler               *handler,
    netsnmp_handler_registration      *reginfo,
    netsnmp_agent_request_info        *reqinfo,
    netsnmp_request_info              *requests) {

    netsnmp_request_info       *request;
    netsnmp_table_request_info *table_info;
    netsnmp_tdata              *table_data;
    netsnmp_tdata_row          *table_row;
    struct pstIFMS1000ExpertExtendTable_entry          *table_entry;
    int                         ret;

    DEBUGMSGTL(("pstIFMS1000:handler", "Processing request (%d)\n", reqinfo->mode));

    switch (reqinfo->mode) {
        /*
         * Read-support (also covers GetNext requests)
         */
    case MODE_GET:
        for (request=requests; request; request=request->next) {
            if (request->processed)
                continue;

            table_entry = (struct pstIFMS1000ExpertExtendTable_entry *)
                              netsnmp_tdata_extract_entry(request);
            table_info  =     netsnmp_extract_table_info( request);
    
            switch (table_info->colnum) {
            case COLUMN_PSTIFMS1000EEPORTNUM:
                if ( !table_entry ) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_NOSUCHINSTANCE);
                    continue;
                }
                snmp_set_var_typed_integer( request->requestvb, ASN_INTEGER,
                                            table_entry->pstIFMS1000EEPortNum);
                break;
            case COLUMN_PSTIFMS1000DGPBIAS1:
                if ( !table_entry ) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_NOSUCHINSTANCE);
                    continue;
                }
                snmp_set_var_typed_value( request->requestvb, ASN_OCTET_STR,
                                          table_entry->pstIFMS1000DgPBias1,
                                          table_entry->pstIFMS1000DgPBias1_len);
                break;
            case COLUMN_PSTIFMS1000DGPBIAS2:
                if ( !table_entry ) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_NOSUCHINSTANCE);
                    continue;
                }
                snmp_set_var_typed_value( request->requestvb, ASN_OCTET_STR,
                                          table_entry->pstIFMS1000DgPBias2,
                                          table_entry->pstIFMS1000DgPBias2_len);
                break;
            case COLUMN_PSTIFMS1000DGPMODULATION1:
                if ( !table_entry ) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_NOSUCHINSTANCE);
                    continue;
                }
                snmp_set_var_typed_value( request->requestvb, ASN_OCTET_STR,
                                          table_entry->pstIFMS1000DgPModulation1,
                                          table_entry->pstIFMS1000DgPModulation1_len);
                break;
            case COLUMN_PSTIFMS1000DGPMODULATION2:
                if ( !table_entry ) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_NOSUCHINSTANCE);
                    continue;
                }
                snmp_set_var_typed_value( request->requestvb, ASN_OCTET_STR,
                                          table_entry->pstIFMS1000DgPModulation2,
                                          table_entry->pstIFMS1000DgPModulation2_len);
                break;
            case COLUMN_PSTIFMS1000DGPBACKSCATTER:
                if ( !table_entry ) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_NOSUCHINSTANCE);
                    continue;
                }
                snmp_set_var_typed_integer( request->requestvb, ASN_INTEGER,
                                            table_entry->pstIFMS1000DgPBackScatter);
                break;
            case COLUMN_PSTIFMS1000DGPMEASUREDELTATHLD:
                if ( !table_entry ) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_NOSUCHINSTANCE);
                    continue;
                }
                snmp_set_var_typed_value( request->requestvb, ASN_OCTET_STR,
                                          table_entry->pstIFMS1000DgPMeasureDeltaThld,
                                          table_entry->pstIFMS1000DgPMeasureDeltaThld_len);
                break;
            case COLUMN_PSTIFMS1000DGPCUTPOINTTHLD:
                if ( !table_entry ) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_NOSUCHINSTANCE);
                    continue;
                }
                snmp_set_var_typed_value( request->requestvb, ASN_OCTET_STR,
                                          table_entry->pstIFMS1000DgPCutPointThld,
                                          table_entry->pstIFMS1000DgPCutPointThld_len);
                break;
            case COLUMN_PSTIFMS1000DGPMFACTOR:
                if ( !table_entry ) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_NOSUCHINSTANCE);
                    continue;
                }
                snmp_set_var_typed_value( request->requestvb, ASN_OCTET_STR,
                                          table_entry->pstIFMS1000DgPMFactor,
                                          table_entry->pstIFMS1000DgPMFactor_len);
                break;
            case COLUMN_PSTIFMS1000DGFAULTCRITICALTHLD:
                if ( !table_entry ) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_NOSUCHINSTANCE);
                    continue;
                }
                snmp_set_var_typed_value( request->requestvb, ASN_OCTET_STR,
                                          table_entry->pstIFMS1000DgFaultCriticalThld,
                                          table_entry->pstIFMS1000DgFaultCriticalThld_len);
                break;
            case COLUMN_PSTIFMS1000DGFAULTMAJORTHLD:
                if ( !table_entry ) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_NOSUCHINSTANCE);
                    continue;
                }
                snmp_set_var_typed_value( request->requestvb, ASN_OCTET_STR,
                                          table_entry->pstIFMS1000DgFaultMajorThld,
                                          table_entry->pstIFMS1000DgFaultMajorThld_len);
                break;
            case COLUMN_PSTIFMS1000DGFAULTMINORTHLD:
                if ( !table_entry ) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_NOSUCHINSTANCE);
                    continue;
                }
                snmp_set_var_typed_value( request->requestvb, ASN_OCTET_STR,
                                          table_entry->pstIFMS1000DgFaultMinorThld,
                                          table_entry->pstIFMS1000DgFaultMinorThld_len);
                break;
            case COLUMN_PSTIFMS1000DGPAFACTOR:
                if ( !table_entry ) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_NOSUCHINSTANCE);
                    continue;
                }
                snmp_set_var_typed_value( request->requestvb, ASN_OCTET_STR,
                                          table_entry->pstIFMS1000DgPAFactor,
                                          table_entry->pstIFMS1000DgPAFactor_len);
                break;
            case COLUMN_PSTIFMS1000DGPBFACTOR:
                if ( !table_entry ) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_NOSUCHINSTANCE);
                    continue;
                }
                snmp_set_var_typed_value( request->requestvb, ASN_OCTET_STR,
                                          table_entry->pstIFMS1000DgPBFactor,
                                          table_entry->pstIFMS1000DgPBFactor_len);
                break;
            default:
                netsnmp_set_request_error(reqinfo, request,
                                          SNMP_NOSUCHOBJECT);
                break;
            }
        }
        break;

        /*
         * Write-support
         */
    case MODE_SET_RESERVE1:
        for (request=requests; request; request=request->next) {
            if (request->processed)
                continue;

            table_entry = (struct pstIFMS1000ExpertExtendTable_entry *)
                              netsnmp_tdata_extract_entry(request);
            table_info  =     netsnmp_extract_table_info( request);
    
            switch (table_info->colnum) {
            case COLUMN_PSTIFMS1000DGPBIAS1:
	        /* or possibly 'netsnmp_check_vb_type_and_size' */
                ret = netsnmp_check_vb_type_and_max_size(
                          request->requestvb, ASN_OCTET_STR, sizeof(table_entry->pstIFMS1000DgPBias1));
                if ( ret != SNMP_ERR_NOERROR ) {
                    netsnmp_set_request_error( reqinfo, request, ret );
                    return SNMP_ERR_NOERROR;
                }
                break;
            case COLUMN_PSTIFMS1000DGPBIAS2:
	        /* or possibly 'netsnmp_check_vb_type_and_size' */
                ret = netsnmp_check_vb_type_and_max_size(
                          request->requestvb, ASN_OCTET_STR, sizeof(table_entry->pstIFMS1000DgPBias2));
                if ( ret != SNMP_ERR_NOERROR ) {
                    netsnmp_set_request_error( reqinfo, request, ret );
                    return SNMP_ERR_NOERROR;
                }
                break;
            case COLUMN_PSTIFMS1000DGPMODULATION1:
	        /* or possibly 'netsnmp_check_vb_type_and_size' */
                ret = netsnmp_check_vb_type_and_max_size(
                          request->requestvb, ASN_OCTET_STR, sizeof(table_entry->pstIFMS1000DgPModulation1));
                if ( ret != SNMP_ERR_NOERROR ) {
                    netsnmp_set_request_error( reqinfo, request, ret );
                    return SNMP_ERR_NOERROR;
                }
                break;
            case COLUMN_PSTIFMS1000DGPMODULATION2:
	        /* or possibly 'netsnmp_check_vb_type_and_size' */
                ret = netsnmp_check_vb_type_and_max_size(
                          request->requestvb, ASN_OCTET_STR, sizeof(table_entry->pstIFMS1000DgPModulation2));
                if ( ret != SNMP_ERR_NOERROR ) {
                    netsnmp_set_request_error( reqinfo, request, ret );
                    return SNMP_ERR_NOERROR;
                }
                break;
            case COLUMN_PSTIFMS1000DGPBACKSCATTER:
                /* or possibly 'netsnmp_check_vb_int_range' */
                ret = netsnmp_check_vb_int( request->requestvb );
                if ( ret != SNMP_ERR_NOERROR ) {
                    netsnmp_set_request_error( reqinfo, request, ret );
                    return SNMP_ERR_NOERROR;
                }
                break;
            case COLUMN_PSTIFMS1000DGPMEASUREDELTATHLD:
	        /* or possibly 'netsnmp_check_vb_type_and_size' */
                ret = netsnmp_check_vb_type_and_max_size(
                          request->requestvb, ASN_OCTET_STR, sizeof(table_entry->pstIFMS1000DgPMeasureDeltaThld));
                if ( ret != SNMP_ERR_NOERROR ) {
                    netsnmp_set_request_error( reqinfo, request, ret );
                    return SNMP_ERR_NOERROR;
                }
                break;
            case COLUMN_PSTIFMS1000DGPCUTPOINTTHLD:
	        /* or possibly 'netsnmp_check_vb_type_and_size' */
                ret = netsnmp_check_vb_type_and_max_size(
                          request->requestvb, ASN_OCTET_STR, sizeof(table_entry->pstIFMS1000DgPCutPointThld));
                if ( ret != SNMP_ERR_NOERROR ) {
                    netsnmp_set_request_error( reqinfo, request, ret );
                    return SNMP_ERR_NOERROR;
                }
                break;
            case COLUMN_PSTIFMS1000DGPMFACTOR:
	        /* or possibly 'netsnmp_check_vb_type_and_size' */
                ret = netsnmp_check_vb_type_and_max_size(
                          request->requestvb, ASN_OCTET_STR, sizeof(table_entry->pstIFMS1000DgPMFactor));
                if ( ret != SNMP_ERR_NOERROR ) {
                    netsnmp_set_request_error( reqinfo, request, ret );
                    return SNMP_ERR_NOERROR;
                }
                break;
            case COLUMN_PSTIFMS1000DGFAULTCRITICALTHLD:
	        /* or possibly 'netsnmp_check_vb_type_and_size' */
                ret = netsnmp_check_vb_type_and_max_size(
                          request->requestvb, ASN_OCTET_STR, sizeof(table_entry->pstIFMS1000DgFaultCriticalThld));
                if ( ret != SNMP_ERR_NOERROR ) {
                    netsnmp_set_request_error( reqinfo, request, ret );
                    return SNMP_ERR_NOERROR;
                }
                break;
            case COLUMN_PSTIFMS1000DGFAULTMAJORTHLD:
	        /* or possibly 'netsnmp_check_vb_type_and_size' */
                ret = netsnmp_check_vb_type_and_max_size(
                          request->requestvb, ASN_OCTET_STR, sizeof(table_entry->pstIFMS1000DgFaultMajorThld));
                if ( ret != SNMP_ERR_NOERROR ) {
                    netsnmp_set_request_error( reqinfo, request, ret );
                    return SNMP_ERR_NOERROR;
                }
                break;
            case COLUMN_PSTIFMS1000DGFAULTMINORTHLD:
	        /* or possibly 'netsnmp_check_vb_type_and_size' */
                ret = netsnmp_check_vb_type_and_max_size(
                          request->requestvb, ASN_OCTET_STR, sizeof(table_entry->pstIFMS1000DgFaultMinorThld));
                if ( ret != SNMP_ERR_NOERROR ) {
                    netsnmp_set_request_error( reqinfo, request, ret );
                    return SNMP_ERR_NOERROR;
                }
                break;
            case COLUMN_PSTIFMS1000DGPAFACTOR:
	        /* or possibly 'netsnmp_check_vb_type_and_size' */
                ret = netsnmp_check_vb_type_and_max_size(
                          request->requestvb, ASN_OCTET_STR, sizeof(table_entry->pstIFMS1000DgPAFactor));
                if ( ret != SNMP_ERR_NOERROR ) {
                    netsnmp_set_request_error( reqinfo, request, ret );
                    return SNMP_ERR_NOERROR;
                }
                break;
            case COLUMN_PSTIFMS1000DGPBFACTOR:
	        /* or possibly 'netsnmp_check_vb_type_and_size' */
                ret = netsnmp_check_vb_type_and_max_size(
                          request->requestvb, ASN_OCTET_STR, sizeof(table_entry->pstIFMS1000DgPBFactor));
                if ( ret != SNMP_ERR_NOERROR ) {
                    netsnmp_set_request_error( reqinfo, request, ret );
                    return SNMP_ERR_NOERROR;
                }
                break;
            default:
                netsnmp_set_request_error( reqinfo, request,
                                           SNMP_ERR_NOTWRITABLE );
                return SNMP_ERR_NOERROR;
            }
        }
        break;

    case MODE_SET_RESERVE2:
        break;

    case MODE_SET_FREE:
        break;

    case MODE_SET_ACTION:
        for (request=requests; request; request=request->next) {
            if (request->processed)
                continue;

            table_entry = (struct pstIFMS1000ExpertExtendTable_entry *)
                              netsnmp_tdata_extract_entry(request);
            table_info  =     netsnmp_extract_table_info( request);
    
            switch (table_info->colnum) {
            case COLUMN_PSTIFMS1000DGPBIAS1:
                memcpy( table_entry->old_pstIFMS1000DgPBias1,
                        table_entry->pstIFMS1000DgPBias1,
                        sizeof(table_entry->pstIFMS1000DgPBias1));
                table_entry->old_pstIFMS1000DgPBias1_len =
                        table_entry->pstIFMS1000DgPBias1_len;
                memset( table_entry->pstIFMS1000DgPBias1, 0,
                        sizeof(table_entry->pstIFMS1000DgPBias1));
                memcpy( table_entry->pstIFMS1000DgPBias1,
                        request->requestvb->val.string,
                        request->requestvb->val_len);
                table_entry->pstIFMS1000DgPBias1_len =
                        request->requestvb->val_len;
                break;
            case COLUMN_PSTIFMS1000DGPBIAS2:
                memcpy( table_entry->old_pstIFMS1000DgPBias2,
                        table_entry->pstIFMS1000DgPBias2,
                        sizeof(table_entry->pstIFMS1000DgPBias2));
                table_entry->old_pstIFMS1000DgPBias2_len =
                        table_entry->pstIFMS1000DgPBias2_len;
                memset( table_entry->pstIFMS1000DgPBias2, 0,
                        sizeof(table_entry->pstIFMS1000DgPBias2));
                memcpy( table_entry->pstIFMS1000DgPBias2,
                        request->requestvb->val.string,
                        request->requestvb->val_len);
                table_entry->pstIFMS1000DgPBias2_len =
                        request->requestvb->val_len;
                break;
            case COLUMN_PSTIFMS1000DGPMODULATION1:
                memcpy( table_entry->old_pstIFMS1000DgPModulation1,
                        table_entry->pstIFMS1000DgPModulation1,
                        sizeof(table_entry->pstIFMS1000DgPModulation1));
                table_entry->old_pstIFMS1000DgPModulation1_len =
                        table_entry->pstIFMS1000DgPModulation1_len;
                memset( table_entry->pstIFMS1000DgPModulation1, 0,
                        sizeof(table_entry->pstIFMS1000DgPModulation1));
                memcpy( table_entry->pstIFMS1000DgPModulation1,
                        request->requestvb->val.string,
                        request->requestvb->val_len);
                table_entry->pstIFMS1000DgPModulation1_len =
                        request->requestvb->val_len;
                break;
            case COLUMN_PSTIFMS1000DGPMODULATION2:
                memcpy( table_entry->old_pstIFMS1000DgPModulation2,
                        table_entry->pstIFMS1000DgPModulation2,
                        sizeof(table_entry->pstIFMS1000DgPModulation2));
                table_entry->old_pstIFMS1000DgPModulation2_len =
                        table_entry->pstIFMS1000DgPModulation2_len;
                memset( table_entry->pstIFMS1000DgPModulation2, 0,
                        sizeof(table_entry->pstIFMS1000DgPModulation2));
                memcpy( table_entry->pstIFMS1000DgPModulation2,
                        request->requestvb->val.string,
                        request->requestvb->val_len);
                table_entry->pstIFMS1000DgPModulation2_len =
                        request->requestvb->val_len;
                break;
            case COLUMN_PSTIFMS1000DGPBACKSCATTER:
                table_entry->old_pstIFMS1000DgPBackScatter = table_entry->pstIFMS1000DgPBackScatter;
                table_entry->pstIFMS1000DgPBackScatter     = *request->requestvb->val.integer;
                break;
            case COLUMN_PSTIFMS1000DGPMEASUREDELTATHLD:
                memcpy( table_entry->old_pstIFMS1000DgPMeasureDeltaThld,
                        table_entry->pstIFMS1000DgPMeasureDeltaThld,
                        sizeof(table_entry->pstIFMS1000DgPMeasureDeltaThld));
                table_entry->old_pstIFMS1000DgPMeasureDeltaThld_len =
                        table_entry->pstIFMS1000DgPMeasureDeltaThld_len;
                memset( table_entry->pstIFMS1000DgPMeasureDeltaThld, 0,
                        sizeof(table_entry->pstIFMS1000DgPMeasureDeltaThld));
                memcpy( table_entry->pstIFMS1000DgPMeasureDeltaThld,
                        request->requestvb->val.string,
                        request->requestvb->val_len);
                table_entry->pstIFMS1000DgPMeasureDeltaThld_len =
                        request->requestvb->val_len;
                break;
            case COLUMN_PSTIFMS1000DGPCUTPOINTTHLD:
                memcpy( table_entry->old_pstIFMS1000DgPCutPointThld,
                        table_entry->pstIFMS1000DgPCutPointThld,
                        sizeof(table_entry->pstIFMS1000DgPCutPointThld));
                table_entry->old_pstIFMS1000DgPCutPointThld_len =
                        table_entry->pstIFMS1000DgPCutPointThld_len;
                memset( table_entry->pstIFMS1000DgPCutPointThld, 0,
                        sizeof(table_entry->pstIFMS1000DgPCutPointThld));
                memcpy( table_entry->pstIFMS1000DgPCutPointThld,
                        request->requestvb->val.string,
                        request->requestvb->val_len);
                table_entry->pstIFMS1000DgPCutPointThld_len =
                        request->requestvb->val_len;
                break;
            case COLUMN_PSTIFMS1000DGPMFACTOR:
                memcpy( table_entry->old_pstIFMS1000DgPMFactor,
                        table_entry->pstIFMS1000DgPMFactor,
                        sizeof(table_entry->pstIFMS1000DgPMFactor));
                table_entry->old_pstIFMS1000DgPMFactor_len =
                        table_entry->pstIFMS1000DgPMFactor_len;
                memset( table_entry->pstIFMS1000DgPMFactor, 0,
                        sizeof(table_entry->pstIFMS1000DgPMFactor));
                memcpy( table_entry->pstIFMS1000DgPMFactor,
                        request->requestvb->val.string,
                        request->requestvb->val_len);
                table_entry->pstIFMS1000DgPMFactor_len =
                        request->requestvb->val_len;
                break;
            case COLUMN_PSTIFMS1000DGFAULTCRITICALTHLD:
                memcpy( table_entry->old_pstIFMS1000DgFaultCriticalThld,
                        table_entry->pstIFMS1000DgFaultCriticalThld,
                        sizeof(table_entry->pstIFMS1000DgFaultCriticalThld));
                table_entry->old_pstIFMS1000DgFaultCriticalThld_len =
                        table_entry->pstIFMS1000DgFaultCriticalThld_len;
                memset( table_entry->pstIFMS1000DgFaultCriticalThld, 0,
                        sizeof(table_entry->pstIFMS1000DgFaultCriticalThld));
                memcpy( table_entry->pstIFMS1000DgFaultCriticalThld,
                        request->requestvb->val.string,
                        request->requestvb->val_len);
                table_entry->pstIFMS1000DgFaultCriticalThld_len =
                        request->requestvb->val_len;
                break;
            case COLUMN_PSTIFMS1000DGFAULTMAJORTHLD:
                memcpy( table_entry->old_pstIFMS1000DgFaultMajorThld,
                        table_entry->pstIFMS1000DgFaultMajorThld,
                        sizeof(table_entry->pstIFMS1000DgFaultMajorThld));
                table_entry->old_pstIFMS1000DgFaultMajorThld_len =
                        table_entry->pstIFMS1000DgFaultMajorThld_len;
                memset( table_entry->pstIFMS1000DgFaultMajorThld, 0,
                        sizeof(table_entry->pstIFMS1000DgFaultMajorThld));
                memcpy( table_entry->pstIFMS1000DgFaultMajorThld,
                        request->requestvb->val.string,
                        request->requestvb->val_len);
                table_entry->pstIFMS1000DgFaultMajorThld_len =
                        request->requestvb->val_len;
                break;
            case COLUMN_PSTIFMS1000DGFAULTMINORTHLD:
                memcpy( table_entry->old_pstIFMS1000DgFaultMinorThld,
                        table_entry->pstIFMS1000DgFaultMinorThld,
                        sizeof(table_entry->pstIFMS1000DgFaultMinorThld));
                table_entry->old_pstIFMS1000DgFaultMinorThld_len =
                        table_entry->pstIFMS1000DgFaultMinorThld_len;
                memset( table_entry->pstIFMS1000DgFaultMinorThld, 0,
                        sizeof(table_entry->pstIFMS1000DgFaultMinorThld));
                memcpy( table_entry->pstIFMS1000DgFaultMinorThld,
                        request->requestvb->val.string,
                        request->requestvb->val_len);
                table_entry->pstIFMS1000DgFaultMinorThld_len =
                        request->requestvb->val_len;
                break;
            case COLUMN_PSTIFMS1000DGPAFACTOR:
                memcpy( table_entry->old_pstIFMS1000DgPAFactor,
                        table_entry->pstIFMS1000DgPAFactor,
                        sizeof(table_entry->pstIFMS1000DgPAFactor));
                table_entry->old_pstIFMS1000DgPAFactor_len =
                        table_entry->pstIFMS1000DgPAFactor_len;
                memset( table_entry->pstIFMS1000DgPAFactor, 0,
                        sizeof(table_entry->pstIFMS1000DgPAFactor));
                memcpy( table_entry->pstIFMS1000DgPAFactor,
                        request->requestvb->val.string,
                        request->requestvb->val_len);
                table_entry->pstIFMS1000DgPAFactor_len =
                        request->requestvb->val_len;
                break;
            case COLUMN_PSTIFMS1000DGPBFACTOR:
                memcpy( table_entry->old_pstIFMS1000DgPBFactor,
                        table_entry->pstIFMS1000DgPBFactor,
                        sizeof(table_entry->pstIFMS1000DgPBFactor));
                table_entry->old_pstIFMS1000DgPBFactor_len =
                        table_entry->pstIFMS1000DgPBFactor_len;
                memset( table_entry->pstIFMS1000DgPBFactor, 0,
                        sizeof(table_entry->pstIFMS1000DgPBFactor));
                memcpy( table_entry->pstIFMS1000DgPBFactor,
                        request->requestvb->val.string,
                        request->requestvb->val_len);
                table_entry->pstIFMS1000DgPBFactor_len =
                        request->requestvb->val_len;
                break;
            }
        }
        break;

    case MODE_SET_UNDO:
        for (request=requests; request; request=request->next) {
            if (request->processed)
                continue;

            table_entry = (struct pstIFMS1000ExpertExtendTable_entry *)
                              netsnmp_tdata_extract_entry(request);
            table_row   =     netsnmp_tdata_extract_row(  request);
            table_data  =     netsnmp_tdata_extract_table(request);
            table_info  =     netsnmp_extract_table_info( request);
    
            switch (table_info->colnum) {
            case COLUMN_PSTIFMS1000DGPBIAS1:
                memcpy( table_entry->pstIFMS1000DgPBias1,
                        table_entry->old_pstIFMS1000DgPBias1,
                        sizeof(table_entry->pstIFMS1000DgPBias1));
                memset( table_entry->old_pstIFMS1000DgPBias1, 0,
                        sizeof(table_entry->pstIFMS1000DgPBias1));
                table_entry->pstIFMS1000DgPBias1_len =
                        table_entry->old_pstIFMS1000DgPBias1_len;
                break;
            case COLUMN_PSTIFMS1000DGPBIAS2:
                memcpy( table_entry->pstIFMS1000DgPBias2,
                        table_entry->old_pstIFMS1000DgPBias2,
                        sizeof(table_entry->pstIFMS1000DgPBias2));
                memset( table_entry->old_pstIFMS1000DgPBias2, 0,
                        sizeof(table_entry->pstIFMS1000DgPBias2));
                table_entry->pstIFMS1000DgPBias2_len =
                        table_entry->old_pstIFMS1000DgPBias2_len;
                break;
            case COLUMN_PSTIFMS1000DGPMODULATION1:
                memcpy( table_entry->pstIFMS1000DgPModulation1,
                        table_entry->old_pstIFMS1000DgPModulation1,
                        sizeof(table_entry->pstIFMS1000DgPModulation1));
                memset( table_entry->old_pstIFMS1000DgPModulation1, 0,
                        sizeof(table_entry->pstIFMS1000DgPModulation1));
                table_entry->pstIFMS1000DgPModulation1_len =
                        table_entry->old_pstIFMS1000DgPModulation1_len;
                break;
            case COLUMN_PSTIFMS1000DGPMODULATION2:
                memcpy( table_entry->pstIFMS1000DgPModulation2,
                        table_entry->old_pstIFMS1000DgPModulation2,
                        sizeof(table_entry->pstIFMS1000DgPModulation2));
                memset( table_entry->old_pstIFMS1000DgPModulation2, 0,
                        sizeof(table_entry->pstIFMS1000DgPModulation2));
                table_entry->pstIFMS1000DgPModulation2_len =
                        table_entry->old_pstIFMS1000DgPModulation2_len;
                break;
            case COLUMN_PSTIFMS1000DGPBACKSCATTER:
                table_entry->pstIFMS1000DgPBackScatter     = table_entry->old_pstIFMS1000DgPBackScatter;
                table_entry->old_pstIFMS1000DgPBackScatter = 0;
                break;
            case COLUMN_PSTIFMS1000DGPMEASUREDELTATHLD:
                memcpy( table_entry->pstIFMS1000DgPMeasureDeltaThld,
                        table_entry->old_pstIFMS1000DgPMeasureDeltaThld,
                        sizeof(table_entry->pstIFMS1000DgPMeasureDeltaThld));
                memset( table_entry->old_pstIFMS1000DgPMeasureDeltaThld, 0,
                        sizeof(table_entry->pstIFMS1000DgPMeasureDeltaThld));
                table_entry->pstIFMS1000DgPMeasureDeltaThld_len =
                        table_entry->old_pstIFMS1000DgPMeasureDeltaThld_len;
                break;
            case COLUMN_PSTIFMS1000DGPCUTPOINTTHLD:
                memcpy( table_entry->pstIFMS1000DgPCutPointThld,
                        table_entry->old_pstIFMS1000DgPCutPointThld,
                        sizeof(table_entry->pstIFMS1000DgPCutPointThld));
                memset( table_entry->old_pstIFMS1000DgPCutPointThld, 0,
                        sizeof(table_entry->pstIFMS1000DgPCutPointThld));
                table_entry->pstIFMS1000DgPCutPointThld_len =
                        table_entry->old_pstIFMS1000DgPCutPointThld_len;
                break;
            case COLUMN_PSTIFMS1000DGPMFACTOR:
                memcpy( table_entry->pstIFMS1000DgPMFactor,
                        table_entry->old_pstIFMS1000DgPMFactor,
                        sizeof(table_entry->pstIFMS1000DgPMFactor));
                memset( table_entry->old_pstIFMS1000DgPMFactor, 0,
                        sizeof(table_entry->pstIFMS1000DgPMFactor));
                table_entry->pstIFMS1000DgPMFactor_len =
                        table_entry->old_pstIFMS1000DgPMFactor_len;
                break;
            case COLUMN_PSTIFMS1000DGFAULTCRITICALTHLD:
                memcpy( table_entry->pstIFMS1000DgFaultCriticalThld,
                        table_entry->old_pstIFMS1000DgFaultCriticalThld,
                        sizeof(table_entry->pstIFMS1000DgFaultCriticalThld));
                memset( table_entry->old_pstIFMS1000DgFaultCriticalThld, 0,
                        sizeof(table_entry->pstIFMS1000DgFaultCriticalThld));
                table_entry->pstIFMS1000DgFaultCriticalThld_len =
                        table_entry->old_pstIFMS1000DgFaultCriticalThld_len;
                break;
            case COLUMN_PSTIFMS1000DGFAULTMAJORTHLD:
                memcpy( table_entry->pstIFMS1000DgFaultMajorThld,
                        table_entry->old_pstIFMS1000DgFaultMajorThld,
                        sizeof(table_entry->pstIFMS1000DgFaultMajorThld));
                memset( table_entry->old_pstIFMS1000DgFaultMajorThld, 0,
                        sizeof(table_entry->pstIFMS1000DgFaultMajorThld));
                table_entry->pstIFMS1000DgFaultMajorThld_len =
                        table_entry->old_pstIFMS1000DgFaultMajorThld_len;
                break;
            case COLUMN_PSTIFMS1000DGFAULTMINORTHLD:
                memcpy( table_entry->pstIFMS1000DgFaultMinorThld,
                        table_entry->old_pstIFMS1000DgFaultMinorThld,
                        sizeof(table_entry->pstIFMS1000DgFaultMinorThld));
                memset( table_entry->old_pstIFMS1000DgFaultMinorThld, 0,
                        sizeof(table_entry->pstIFMS1000DgFaultMinorThld));
                table_entry->pstIFMS1000DgFaultMinorThld_len =
                        table_entry->old_pstIFMS1000DgFaultMinorThld_len;
                break;
            case COLUMN_PSTIFMS1000DGPAFACTOR:
                memcpy( table_entry->pstIFMS1000DgPAFactor,
                        table_entry->old_pstIFMS1000DgPAFactor,
                        sizeof(table_entry->pstIFMS1000DgPAFactor));
                memset( table_entry->old_pstIFMS1000DgPAFactor, 0,
                        sizeof(table_entry->pstIFMS1000DgPAFactor));
                table_entry->pstIFMS1000DgPAFactor_len =
                        table_entry->old_pstIFMS1000DgPAFactor_len;
                break;
            case COLUMN_PSTIFMS1000DGPBFACTOR:
                memcpy( table_entry->pstIFMS1000DgPBFactor,
                        table_entry->old_pstIFMS1000DgPBFactor,
                        sizeof(table_entry->pstIFMS1000DgPBFactor));
                memset( table_entry->old_pstIFMS1000DgPBFactor, 0,
                        sizeof(table_entry->pstIFMS1000DgPBFactor));
                table_entry->pstIFMS1000DgPBFactor_len =
                        table_entry->old_pstIFMS1000DgPBFactor_len;
                break;
            }
        }
        break;

    case MODE_SET_COMMIT:
        break;
    }
    return SNMP_ERR_NOERROR;
}

/** Initialize the pstIFMS1000PonConfTable table by defining its contents and how it's structured */
void
QPSTProduct::initialize_table_pstIFMS1000PonConfTable(void)
{
    const oid pstIFMS1000PonConfTable_oid[] = {1,3,6,1,4,1,48391,3,5,14};
    const size_t pstIFMS1000PonConfTable_oid_len   = OID_LENGTH(pstIFMS1000PonConfTable_oid);
    netsnmp_handler_registration    *reg;
    netsnmp_tdata                   *table_data;
    netsnmp_table_registration_info *table_info;

    DEBUGMSGTL(("pstIFMS1000:init", "initializing table pstIFMS1000PonConfTable\n"));

    reg = netsnmp_create_handler_registration(
              "pstIFMS1000PonConfTable",     pstIFMS1000PonConfTable_handler,
              pstIFMS1000PonConfTable_oid, pstIFMS1000PonConfTable_oid_len,
              HANDLER_CAN_RWRITE
              );

    table_data = netsnmp_tdata_create_table( "pstIFMS1000PonConfTable", 0 );
    if (NULL == table_data) {
        snmp_log(LOG_ERR,"error creating tdata table for pstIFMS1000PonConfTable\n");
        return;
    }
    table_info = SNMP_MALLOC_TYPEDEF( netsnmp_table_registration_info );
    if (NULL == table_info) {
        snmp_log(LOG_ERR,"error creating table info for pstIFMS1000PonConfTable\n");
        return;
    }
    netsnmp_table_helper_add_indexes(table_info,
                           ASN_UNSIGNED,  /* index: pctPortNum */
                           0);

    table_info->min_column = COLUMN_PCTPORTNUM;
    table_info->max_column = COLUMN_PCTSP1LOCITEM;
    
    netsnmp_tdata_register( reg, table_data, table_info );

    /* Initialise the contents of the table here */
}

//    /* Typical data structure for a row entry */
//struct pstIFMS1000PonConfTable_entry {
//    /* Index values */
//    u_long pctPortNum;

//    /* Column values */
//    u_long pctPortNum;
//    u_long pctSp1LocItem;
//    u_long old_pctSp1LocItem;

//    int   valid;
//};

/* create a new row in the table */
static netsnmp_tdata_row *
pstIFMS1000PonConfTable_createEntry(netsnmp_tdata *table_data
                 , u_long  pctPortNum
                ) {
    struct pstIFMS1000PonConfTable_entry *entry;
    netsnmp_tdata_row *row;

    entry = SNMP_MALLOC_TYPEDEF(struct pstIFMS1000PonConfTable_entry);
    if (!entry)
        return NULL;

    row = netsnmp_tdata_create_row();
    if (!row) {
        SNMP_FREE(entry);
        return NULL;
    }
    row->data = entry;

    DEBUGMSGT(("pstIFMS1000PonConfTable:entry:create", "row 0x%x\n", (uintptr_t)row));
    entry->pctPortNum = pctPortNum;
    netsnmp_tdata_row_add_index( row, ASN_UNSIGNED,
                                 &(entry->pctPortNum),
                                 sizeof(entry->pctPortNum));
    if (table_data)
        netsnmp_tdata_add_row( table_data, row );
    return row;
}

/* remove a row from the table */
static void
pstIFMS1000PonConfTable_removeEntry(netsnmp_tdata     *table_data, 
                 netsnmp_tdata_row *row) {
    struct pstIFMS1000PonConfTable_entry *entry;

    if (!row)
        return;    /* Nothing to remove */

    DEBUGMSGT(("pstIFMS1000PonConfTable:entry:remove", "row 0x%x\n", (uintptr_t)row));

    entry = (struct pstIFMS1000PonConfTable_entry *)row->data;
    SNMP_FREE( entry );   /* XXX - release any other internal resources */

    if (table_data)
        netsnmp_tdata_remove_and_delete_row( table_data, row );
    else
        netsnmp_tdata_delete_row( row );    
}


/** handles requests for the pstIFMS1000PonConfTable table */
int
QPSTProduct::pstIFMS1000PonConfTable_handler(
    netsnmp_mib_handler               *handler,
    netsnmp_handler_registration      *reginfo,
    netsnmp_agent_request_info        *reqinfo,
    netsnmp_request_info              *requests) {

    netsnmp_request_info       *request;
    netsnmp_table_request_info *table_info;
    netsnmp_tdata              *table_data;
    netsnmp_tdata_row          *table_row;
    struct pstIFMS1000PonConfTable_entry          *table_entry;
    int                         ret;

    DEBUGMSGTL(("pstIFMS1000:handler", "Processing request (%d)\n", reqinfo->mode));

    switch (reqinfo->mode) {
        /*
         * Read-support (also covers GetNext requests)
         */
    case MODE_GET:
        for (request=requests; request; request=request->next) {
            if (request->processed)
                continue;

            table_entry = (struct pstIFMS1000PonConfTable_entry *)
                              netsnmp_tdata_extract_entry(request);
            table_info  =     netsnmp_extract_table_info( request);
    
            switch (table_info->colnum) {
            case COLUMN_PCTPORTNUM:
                if ( !table_entry ) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_NOSUCHINSTANCE);
                    continue;
                }
                snmp_set_var_typed_integer( request->requestvb, ASN_UNSIGNED,
                                            table_entry->pctPortNum);
                break;
            case COLUMN_PCTSP1LOCITEM:
                if ( !table_entry ) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_NOSUCHINSTANCE);
                    continue;
                }
                snmp_set_var_typed_integer( request->requestvb, ASN_UNSIGNED,
                                            table_entry->pctSp1LocItem);
                break;
            default:
                netsnmp_set_request_error(reqinfo, request,
                                          SNMP_NOSUCHOBJECT);
                break;
            }
        }
        break;

        /*
         * Write-support
         */
    case MODE_SET_RESERVE1:
        for (request=requests; request; request=request->next) {
            if (request->processed)
                continue;

            table_entry = (struct pstIFMS1000PonConfTable_entry *)
                              netsnmp_tdata_extract_entry(request);
            table_info  =     netsnmp_extract_table_info( request);
    
            switch (table_info->colnum) {
            case COLUMN_PCTSP1LOCITEM:
                /* or possibly 'netsnmp_check_vb_int_range' */
                ret = netsnmp_check_vb_int( request->requestvb );
                if ( ret != SNMP_ERR_NOERROR ) {
                    netsnmp_set_request_error( reqinfo, request, ret );
                    return SNMP_ERR_NOERROR;
                }
                break;
            default:
                netsnmp_set_request_error( reqinfo, request,
                                           SNMP_ERR_NOTWRITABLE );
                return SNMP_ERR_NOERROR;
            }
        }
        break;

    case MODE_SET_RESERVE2:
        break;

    case MODE_SET_FREE:
        break;

    case MODE_SET_ACTION:
        for (request=requests; request; request=request->next) {
            if (request->processed)
                continue;

            table_entry = (struct pstIFMS1000PonConfTable_entry *)
                              netsnmp_tdata_extract_entry(request);
            table_info  =     netsnmp_extract_table_info( request);
    
            switch (table_info->colnum) {
            case COLUMN_PCTSP1LOCITEM:
                table_entry->old_pctSp1LocItem = table_entry->pctSp1LocItem;
                table_entry->pctSp1LocItem     = *request->requestvb->val.integer;
                break;
            }
        }
        break;

    case MODE_SET_UNDO:
        for (request=requests; request; request=request->next) {
            if (request->processed)
                continue;

            table_entry = (struct pstIFMS1000PonConfTable_entry *)
                              netsnmp_tdata_extract_entry(request);
            table_row   =     netsnmp_tdata_extract_row(  request);
            table_data  =     netsnmp_tdata_extract_table(request);
            table_info  =     netsnmp_extract_table_info( request);
    
            switch (table_info->colnum) {
            case COLUMN_PCTSP1LOCITEM:
                table_entry->pctSp1LocItem     = table_entry->old_pctSp1LocItem;
                table_entry->old_pctSp1LocItem = 0;
                break;
            }
        }
        break;

    case MODE_SET_COMMIT:
        break;
    }
    return SNMP_ERR_NOERROR;
}

/** Initialize the pstIFMS1000ParamsV32TotalNumTable table by defining its contents and how it's structured */
void
QPSTProduct::initialize_table_pstIFMS1000ParamsV32TotalNumTable(void)
{
    const oid pstIFMS1000ParamsV32TotalNumTable_oid[] = {1,3,6,1,4,1,48391,3,5,15,1};
    const size_t pstIFMS1000ParamsV32TotalNumTable_oid_len   = OID_LENGTH(pstIFMS1000ParamsV32TotalNumTable_oid);
    netsnmp_handler_registration    *reg;
    netsnmp_tdata                   *table_data;
    netsnmp_table_registration_info *table_info;

    DEBUGMSGTL(("pstIFMS1000:init", "initializing table pstIFMS1000ParamsV32TotalNumTable\n"));

    reg = netsnmp_create_handler_registration(
              "pstIFMS1000ParamsV32TotalNumTable",     pstIFMS1000ParamsV32TotalNumTable_handler,
              pstIFMS1000ParamsV32TotalNumTable_oid, pstIFMS1000ParamsV32TotalNumTable_oid_len,
              HANDLER_CAN_RONLY
              );

    table_data = netsnmp_tdata_create_table( "pstIFMS1000ParamsV32TotalNumTable", 0 );
    if (NULL == table_data) {
        snmp_log(LOG_ERR,"error creating tdata table for pstIFMS1000ParamsV32TotalNumTable\n");
        return;
    }
    table_info = SNMP_MALLOC_TYPEDEF( netsnmp_table_registration_info );
    if (NULL == table_info) {
        snmp_log(LOG_ERR,"error creating table info for pstIFMS1000ParamsV32TotalNumTable\n");
        return;
    }
    netsnmp_table_helper_add_indexes(table_info,
                           ASN_INTEGER,  /* index: v32TPortNum */
                           0);

    table_info->min_column = COLUMN_V32TPORTNUM;
    table_info->max_column = COLUMN_V32PORTTOTALNUM;
    
    netsnmp_tdata_register( reg, table_data, table_info );

    /* Initialise the contents of the table here */
}

//    /* Typical data structure for a row entry */
//struct pstIFMS1000ParamsV32TotalNumTable_entry {
//    /* Index values */
//    long v32TPortNum;

//    /* Column values */
//    long v32TPortNum;
//    long v32PortTotalNum;

//    int   valid;
//};

/* create a new row in the table */
static netsnmp_tdata_row *
pstIFMS1000ParamsV32TotalNumTable_createEntry(netsnmp_tdata *table_data
                 , long  v32TPortNum
                ) {
    struct pstIFMS1000ParamsV32TotalNumTable_entry *entry;
    netsnmp_tdata_row *row;

    entry = SNMP_MALLOC_TYPEDEF(struct pstIFMS1000ParamsV32TotalNumTable_entry);
    if (!entry)
        return NULL;

    row = netsnmp_tdata_create_row();
    if (!row) {
        SNMP_FREE(entry);
        return NULL;
    }
    row->data = entry;

    DEBUGMSGT(("pstIFMS1000ParamsV32TotalNumTable:entry:create", "row 0x%x\n", (uintptr_t)row));
    entry->v32TPortNum = v32TPortNum;
    netsnmp_tdata_row_add_index( row, ASN_INTEGER,
                                 &(entry->v32TPortNum),
                                 sizeof(entry->v32TPortNum));
    if (table_data)
        netsnmp_tdata_add_row( table_data, row );
    return row;
}

/* remove a row from the table */
static void
pstIFMS1000ParamsV32TotalNumTable_removeEntry(netsnmp_tdata     *table_data, 
                 netsnmp_tdata_row *row) {
    struct pstIFMS1000ParamsV32TotalNumTable_entry *entry;

    if (!row)
        return;    /* Nothing to remove */

    DEBUGMSGT(("pstIFMS1000ParamsV32TotalNumTable:entry:remove", "row 0x%x\n", (uintptr_t)row));

    entry = (struct pstIFMS1000ParamsV32TotalNumTable_entry *)row->data;
    SNMP_FREE( entry );   /* XXX - release any other internal resources */

    if (table_data)
        netsnmp_tdata_remove_and_delete_row( table_data, row );
    else
        netsnmp_tdata_delete_row( row );    
}


/** handles requests for the pstIFMS1000ParamsV32TotalNumTable table */
int
QPSTProduct::pstIFMS1000ParamsV32TotalNumTable_handler(
    netsnmp_mib_handler               *handler,
    netsnmp_handler_registration      *reginfo,
    netsnmp_agent_request_info        *reqinfo,
    netsnmp_request_info              *requests) {

    netsnmp_request_info       *request;
    netsnmp_table_request_info *table_info;
    netsnmp_tdata              *table_data;
    netsnmp_tdata_row          *table_row;
    struct pstIFMS1000ParamsV32TotalNumTable_entry          *table_entry;
    int                         ret;

    DEBUGMSGTL(("pstIFMS1000:handler", "Processing request (%d)\n", reqinfo->mode));

    switch (reqinfo->mode) {
        /*
         * Read-support (also covers GetNext requests)
         */
    case MODE_GET:
        for (request=requests; request; request=request->next) {
            if (request->processed)
                continue;

            table_entry = (struct pstIFMS1000ParamsV32TotalNumTable_entry *)
                              netsnmp_tdata_extract_entry(request);
            table_info  =     netsnmp_extract_table_info( request);
    
            switch (table_info->colnum) {
            case COLUMN_V32TPORTNUM:
                if ( !table_entry ) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_NOSUCHINSTANCE);
                    continue;
                }
                snmp_set_var_typed_integer( request->requestvb, ASN_INTEGER,
                                            table_entry->v32TPortNum);
                break;
            case COLUMN_V32PORTTOTALNUM:
                if ( !table_entry ) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_NOSUCHINSTANCE);
                    continue;
                }
                snmp_set_var_typed_integer( request->requestvb, ASN_INTEGER,
                                            table_entry->v32PortTotalNum);
                break;
            default:
                netsnmp_set_request_error(reqinfo, request,
                                          SNMP_NOSUCHOBJECT);
                break;
            }
        }
        break;

    }
    return SNMP_ERR_NOERROR;
}

/** Initialize the pstIFMS1000ParamsV32NameTable table by defining its contents and how it's structured */
void
QPSTProduct::initialize_table_pstIFMS1000ParamsV32NameTable(void)
{
    const oid pstIFMS1000ParamsV32NameTable_oid[] = {1,3,6,1,4,1,48391,3,5,15,2};
    const size_t pstIFMS1000ParamsV32NameTable_oid_len   = OID_LENGTH(pstIFMS1000ParamsV32NameTable_oid);
    netsnmp_handler_registration    *reg;
    netsnmp_tdata                   *table_data;
    netsnmp_table_registration_info *table_info;

    DEBUGMSGTL(("pstIFMS1000:init", "initializing table pstIFMS1000ParamsV32NameTable\n"));

    reg = netsnmp_create_handler_registration(
              "pstIFMS1000ParamsV32NameTable",     pstIFMS1000ParamsV32NameTable_handler,
              pstIFMS1000ParamsV32NameTable_oid, pstIFMS1000ParamsV32NameTable_oid_len,
              HANDLER_CAN_RONLY
              );

    table_data = netsnmp_tdata_create_table( "pstIFMS1000ParamsV32NameTable", 0 );
    if (NULL == table_data) {
        snmp_log(LOG_ERR,"error creating tdata table for pstIFMS1000ParamsV32NameTable\n");
        return;
    }
    table_info = SNMP_MALLOC_TYPEDEF( netsnmp_table_registration_info );
    if (NULL == table_info) {
        snmp_log(LOG_ERR,"error creating table info for pstIFMS1000ParamsV32NameTable\n");
        return;
    }
    netsnmp_table_helper_add_indexes(table_info,
                           ASN_INTEGER,  /* index: v32PortNum */
                           ASN_INTEGER,  /* index: v32ParamNameNum */
                           0);

    table_info->min_column = COLUMN_V32PORTNUM;
    table_info->max_column = COLUMN_V32PARAMNAME;
    
    netsnmp_tdata_register( reg, table_data, table_info );

    /* Initialise the contents of the table here */
}

//    /* Typical data structure for a row entry */
//struct pstIFMS1000ParamsV32NameTable_entry {
//    /* Index values */
//    long v32PortNum;
//    long v32ParamNameNum;

//    /* Column values */
//    long v32PortNum;
//    long v32ParamNameNum;
//    char v32ParamName[NNN];
//    size_t v32ParamName_len;

//    int   valid;
//};

/* create a new row in the table */
static netsnmp_tdata_row *
pstIFMS1000ParamsV32NameTable_createEntry(netsnmp_tdata *table_data
                 , long  v32PortNum
                 , long  v32ParamNameNum
                ) {
    struct pstIFMS1000ParamsV32NameTable_entry *entry;
    netsnmp_tdata_row *row;

    entry = SNMP_MALLOC_TYPEDEF(struct pstIFMS1000ParamsV32NameTable_entry);
    if (!entry)
        return NULL;

    row = netsnmp_tdata_create_row();
    if (!row) {
        SNMP_FREE(entry);
        return NULL;
    }
    row->data = entry;

    DEBUGMSGT(("pstIFMS1000ParamsV32NameTable:entry:create", "row 0x%x\n", (uintptr_t)row));
    entry->v32PortNum = v32PortNum;
    netsnmp_tdata_row_add_index( row, ASN_INTEGER,
                                 &(entry->v32PortNum),
                                 sizeof(entry->v32PortNum));
    entry->v32ParamNameNum = v32ParamNameNum;
    netsnmp_tdata_row_add_index( row, ASN_INTEGER,
                                 &(entry->v32ParamNameNum),
                                 sizeof(entry->v32ParamNameNum));
    if (table_data)
        netsnmp_tdata_add_row( table_data, row );
    return row;
}

/* remove a row from the table */
static void
pstIFMS1000ParamsV32NameTable_removeEntry(netsnmp_tdata     *table_data, 
                 netsnmp_tdata_row *row) {
    struct pstIFMS1000ParamsV32NameTable_entry *entry;

    if (!row)
        return;    /* Nothing to remove */

    DEBUGMSGT(("pstIFMS1000ParamsV32NameTable:entry:remove", "row 0x%x\n", (uintptr_t)row));

    entry = (struct pstIFMS1000ParamsV32NameTable_entry *)row->data;
    SNMP_FREE( entry );   /* XXX - release any other internal resources */

    if (table_data)
        netsnmp_tdata_remove_and_delete_row( table_data, row );
    else
        netsnmp_tdata_delete_row( row );    
}


/** handles requests for the pstIFMS1000ParamsV32NameTable table */
int
QPSTProduct::pstIFMS1000ParamsV32NameTable_handler(
    netsnmp_mib_handler               *handler,
    netsnmp_handler_registration      *reginfo,
    netsnmp_agent_request_info        *reqinfo,
    netsnmp_request_info              *requests) {

    netsnmp_request_info       *request;
    netsnmp_table_request_info *table_info;
    netsnmp_tdata              *table_data;
    netsnmp_tdata_row          *table_row;
    struct pstIFMS1000ParamsV32NameTable_entry          *table_entry;
    int                         ret;

    DEBUGMSGTL(("pstIFMS1000:handler", "Processing request (%d)\n", reqinfo->mode));

    switch (reqinfo->mode) {
        /*
         * Read-support (also covers GetNext requests)
         */
    case MODE_GET:
        for (request=requests; request; request=request->next) {
            if (request->processed)
                continue;

            table_entry = (struct pstIFMS1000ParamsV32NameTable_entry *)
                              netsnmp_tdata_extract_entry(request);
            table_info  =     netsnmp_extract_table_info( request);
    
            switch (table_info->colnum) {
            case COLUMN_V32PORTNUM:
                if ( !table_entry ) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_NOSUCHINSTANCE);
                    continue;
                }
                snmp_set_var_typed_integer( request->requestvb, ASN_INTEGER,
                                            table_entry->v32PortNum);
                break;
            case COLUMN_V32PARAMNAMENUM:
                if ( !table_entry ) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_NOSUCHINSTANCE);
                    continue;
                }
                snmp_set_var_typed_integer( request->requestvb, ASN_INTEGER,
                                            table_entry->v32ParamNameNum);
                break;
            case COLUMN_V32PARAMNAME:
                if ( !table_entry ) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_NOSUCHINSTANCE);
                    continue;
                }
                snmp_set_var_typed_value( request->requestvb, ASN_OCTET_STR,
                                          table_entry->v32ParamName,
                                          table_entry->v32ParamName_len);
                break;
            default:
                netsnmp_set_request_error(reqinfo, request,
                                          SNMP_NOSUCHOBJECT);
                break;
            }
        }
        break;

    }
    return SNMP_ERR_NOERROR;
}

/** Initialize the pstIFMS1000ParamsV32ValTable table by defining its contents and how it's structured */
void
QPSTProduct::initialize_table_pstIFMS1000ParamsV32ValTable(void)
{
    const oid pstIFMS1000ParamsV32ValTable_oid[] = {1,3,6,1,4,1,48391,3,5,15,3};
    const size_t pstIFMS1000ParamsV32ValTable_oid_len   = OID_LENGTH(pstIFMS1000ParamsV32ValTable_oid);
    netsnmp_handler_registration    *reg;
    netsnmp_tdata                   *table_data;
    netsnmp_table_registration_info *table_info;

    DEBUGMSGTL(("pstIFMS1000:init", "initializing table pstIFMS1000ParamsV32ValTable\n"));

    reg = netsnmp_create_handler_registration(
              "pstIFMS1000ParamsV32ValTable",     pstIFMS1000ParamsV32ValTable_handler,
              pstIFMS1000ParamsV32ValTable_oid, pstIFMS1000ParamsV32ValTable_oid_len,
              HANDLER_CAN_RWRITE
              );

    table_data = netsnmp_tdata_create_table( "pstIFMS1000ParamsV32ValTable", 0 );
    if (NULL == table_data) {
        snmp_log(LOG_ERR,"error creating tdata table for pstIFMS1000ParamsV32ValTable\n");
        return;
    }
    table_info = SNMP_MALLOC_TYPEDEF( netsnmp_table_registration_info );
    if (NULL == table_info) {
        snmp_log(LOG_ERR,"error creating table info for pstIFMS1000ParamsV32ValTable\n");
        return;
    }
    netsnmp_table_helper_add_indexes(table_info,
                           ASN_INTEGER,  /* index: v32ValPortNum */
                           ASN_INTEGER,  /* index: v32ParamValNum */
                           0);

    table_info->min_column = COLUMN_V32VALPORTNUM;
    table_info->max_column = COLUMN_V32PARAMVAL;
    
    netsnmp_tdata_register( reg, table_data, table_info );

    /* Initialise the contents of the table here */
}

//    /* Typical data structure for a row entry */
//struct pstIFMS1000ParamsV32ValTable_entry {
//    /* Index values */
//    long v32ValPortNum;
//    long v32ParamValNum;

//    /* Column values */
//    long v32ValPortNum;
//    long v32ParamValNum;
//    u_long v32ParamVal;
//    u_long old_v32ParamVal;

//    int   valid;
//};

/* create a new row in the table */
static netsnmp_tdata_row *
pstIFMS1000ParamsV32ValTable_createEntry(netsnmp_tdata *table_data
                 , long  v32ValPortNum
                 , long  v32ParamValNum
                ) {
    struct pstIFMS1000ParamsV32ValTable_entry *entry;
    netsnmp_tdata_row *row;

    entry = SNMP_MALLOC_TYPEDEF(struct pstIFMS1000ParamsV32ValTable_entry);
    if (!entry)
        return NULL;

    row = netsnmp_tdata_create_row();
    if (!row) {
        SNMP_FREE(entry);
        return NULL;
    }
    row->data = entry;

    DEBUGMSGT(("pstIFMS1000ParamsV32ValTable:entry:create", "row 0x%x\n", (uintptr_t)row));
    entry->v32ValPortNum = v32ValPortNum;
    netsnmp_tdata_row_add_index( row, ASN_INTEGER,
                                 &(entry->v32ValPortNum),
                                 sizeof(entry->v32ValPortNum));
    entry->v32ParamValNum = v32ParamValNum;
    netsnmp_tdata_row_add_index( row, ASN_INTEGER,
                                 &(entry->v32ParamValNum),
                                 sizeof(entry->v32ParamValNum));
    if (table_data)
        netsnmp_tdata_add_row( table_data, row );
    return row;
}

/* remove a row from the table */
static void
pstIFMS1000ParamsV32ValTable_removeEntry(netsnmp_tdata     *table_data, 
                 netsnmp_tdata_row *row) {
    struct pstIFMS1000ParamsV32ValTable_entry *entry;

    if (!row)
        return;    /* Nothing to remove */

    DEBUGMSGT(("pstIFMS1000ParamsV32ValTable:entry:remove", "row 0x%x\n", (uintptr_t)row));

    entry = (struct pstIFMS1000ParamsV32ValTable_entry *)row->data;
    SNMP_FREE( entry );   /* XXX - release any other internal resources */

    if (table_data)
        netsnmp_tdata_remove_and_delete_row( table_data, row );
    else
        netsnmp_tdata_delete_row( row );    
}


/** handles requests for the pstIFMS1000ParamsV32ValTable table */
int
QPSTProduct::pstIFMS1000ParamsV32ValTable_handler(
    netsnmp_mib_handler               *handler,
    netsnmp_handler_registration      *reginfo,
    netsnmp_agent_request_info        *reqinfo,
    netsnmp_request_info              *requests) {

    netsnmp_request_info       *request;
    netsnmp_table_request_info *table_info;
    netsnmp_tdata              *table_data;
    netsnmp_tdata_row          *table_row;
    struct pstIFMS1000ParamsV32ValTable_entry          *table_entry;
    int                         ret;

    DEBUGMSGTL(("pstIFMS1000:handler", "Processing request (%d)\n", reqinfo->mode));

    switch (reqinfo->mode) {
        /*
         * Read-support (also covers GetNext requests)
         */
    case MODE_GET:
        for (request=requests; request; request=request->next) {
            if (request->processed)
                continue;

            table_entry = (struct pstIFMS1000ParamsV32ValTable_entry *)
                              netsnmp_tdata_extract_entry(request);
            table_info  =     netsnmp_extract_table_info( request);
    
            switch (table_info->colnum) {
            case COLUMN_V32VALPORTNUM:
                if ( !table_entry ) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_NOSUCHINSTANCE);
                    continue;
                }
                snmp_set_var_typed_integer( request->requestvb, ASN_INTEGER,
                                            table_entry->v32ValPortNum);
                break;
            case COLUMN_V32PARAMVALNUM:
                if ( !table_entry ) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_NOSUCHINSTANCE);
                    continue;
                }
                snmp_set_var_typed_integer( request->requestvb, ASN_INTEGER,
                                            table_entry->v32ParamValNum);
                break;
            case COLUMN_V32PARAMVAL:
                if ( !table_entry ) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_NOSUCHINSTANCE);
                    continue;
                }
                snmp_set_var_typed_integer( request->requestvb, ASN_UNSIGNED,
                                            table_entry->v32ParamVal);
                break;
            default:
                netsnmp_set_request_error(reqinfo, request,
                                          SNMP_NOSUCHOBJECT);
                break;
            }
        }
        break;

        /*
         * Write-support
         */
    case MODE_SET_RESERVE1:
        for (request=requests; request; request=request->next) {
            if (request->processed)
                continue;

            table_entry = (struct pstIFMS1000ParamsV32ValTable_entry *)
                              netsnmp_tdata_extract_entry(request);
            table_info  =     netsnmp_extract_table_info( request);
    
            switch (table_info->colnum) {
            case COLUMN_V32PARAMVAL:
                /* or possibly 'netsnmp_check_vb_int_range' */
                ret = netsnmp_check_vb_int( request->requestvb );
                if ( ret != SNMP_ERR_NOERROR ) {
                    netsnmp_set_request_error( reqinfo, request, ret );
                    return SNMP_ERR_NOERROR;
                }
                break;
            default:
                netsnmp_set_request_error( reqinfo, request,
                                           SNMP_ERR_NOTWRITABLE );
                return SNMP_ERR_NOERROR;
            }
        }
        break;

    case MODE_SET_RESERVE2:
        break;

    case MODE_SET_FREE:
        break;

    case MODE_SET_ACTION:
        for (request=requests; request; request=request->next) {
            if (request->processed)
                continue;

            table_entry = (struct pstIFMS1000ParamsV32ValTable_entry *)
                              netsnmp_tdata_extract_entry(request);
            table_info  =     netsnmp_extract_table_info( request);
    
            switch (table_info->colnum) {
            case COLUMN_V32PARAMVAL:
                table_entry->old_v32ParamVal = table_entry->v32ParamVal;
                table_entry->v32ParamVal     = *request->requestvb->val.integer;
                break;
            }
        }
        break;

    case MODE_SET_UNDO:
        for (request=requests; request; request=request->next) {
            if (request->processed)
                continue;

            table_entry = (struct pstIFMS1000ParamsV32ValTable_entry *)
                              netsnmp_tdata_extract_entry(request);
            table_row   =     netsnmp_tdata_extract_row(  request);
            table_data  =     netsnmp_tdata_extract_table(request);
            table_info  =     netsnmp_extract_table_info( request);
    
            switch (table_info->colnum) {
            case COLUMN_V32PARAMVAL:
                table_entry->v32ParamVal     = table_entry->old_v32ParamVal;
                table_entry->old_v32ParamVal = 0;
                break;
            }
        }
        break;

    case MODE_SET_COMMIT:
        break;
    }
    return SNMP_ERR_NOERROR;
}

/** Initialize the pstIFMS1000ParamsS32TotalNumTable table by defining its contents and how it's structured */
void
QPSTProduct::initialize_table_pstIFMS1000ParamsS32TotalNumTable(void)
{
    const oid pstIFMS1000ParamsS32TotalNumTable_oid[] = {1,3,6,1,4,1,48391,3,5,16,1};
    const size_t pstIFMS1000ParamsS32TotalNumTable_oid_len   = OID_LENGTH(pstIFMS1000ParamsS32TotalNumTable_oid);
    netsnmp_handler_registration    *reg;
    netsnmp_tdata                   *table_data;
    netsnmp_table_registration_info *table_info;

    DEBUGMSGTL(("pstIFMS1000:init", "initializing table pstIFMS1000ParamsS32TotalNumTable\n"));

    reg = netsnmp_create_handler_registration(
              "pstIFMS1000ParamsS32TotalNumTable",     pstIFMS1000ParamsS32TotalNumTable_handler,
              pstIFMS1000ParamsS32TotalNumTable_oid, pstIFMS1000ParamsS32TotalNumTable_oid_len,
              HANDLER_CAN_RONLY
              );

    table_data = netsnmp_tdata_create_table( "pstIFMS1000ParamsS32TotalNumTable", 0 );
    if (NULL == table_data) {
        snmp_log(LOG_ERR,"error creating tdata table for pstIFMS1000ParamsS32TotalNumTable\n");
        return;
    }
    table_info = SNMP_MALLOC_TYPEDEF( netsnmp_table_registration_info );
    if (NULL == table_info) {
        snmp_log(LOG_ERR,"error creating table info for pstIFMS1000ParamsS32TotalNumTable\n");
        return;
    }
    netsnmp_table_helper_add_indexes(table_info,
                           ASN_INTEGER,  /* index: s32TPortNum */
                           0);

    table_info->min_column = COLUMN_S32TPORTNUM;
    table_info->max_column = COLUMN_S32PORTTOTALNUM;
    
    netsnmp_tdata_register( reg, table_data, table_info );

    /* Initialise the contents of the table here */
}

//    /* Typical data structure for a row entry */
//struct pstIFMS1000ParamsS32TotalNumTable_entry {
//    /* Index values */
//    long s32TPortNum;

//    /* Column values */
//    long s32TPortNum;
//    long s32PortTotalNum;

//    int   valid;
//};

/* create a new row in the table */
static netsnmp_tdata_row *
pstIFMS1000ParamsS32TotalNumTable_createEntry(netsnmp_tdata *table_data
                 , long  s32TPortNum
                ) {
    struct pstIFMS1000ParamsS32TotalNumTable_entry *entry;
    netsnmp_tdata_row *row;

    entry = SNMP_MALLOC_TYPEDEF(struct pstIFMS1000ParamsS32TotalNumTable_entry);
    if (!entry)
        return NULL;

    row = netsnmp_tdata_create_row();
    if (!row) {
        SNMP_FREE(entry);
        return NULL;
    }
    row->data = entry;

    DEBUGMSGT(("pstIFMS1000ParamsS32TotalNumTable:entry:create", "row 0x%x\n", (uintptr_t)row));
    entry->s32TPortNum = s32TPortNum;
    netsnmp_tdata_row_add_index( row, ASN_INTEGER,
                                 &(entry->s32TPortNum),
                                 sizeof(entry->s32TPortNum));
    if (table_data)
        netsnmp_tdata_add_row( table_data, row );
    return row;
}

/* remove a row from the table */
static void
pstIFMS1000ParamsS32TotalNumTable_removeEntry(netsnmp_tdata     *table_data, 
                 netsnmp_tdata_row *row) {
    struct pstIFMS1000ParamsS32TotalNumTable_entry *entry;

    if (!row)
        return;    /* Nothing to remove */

    DEBUGMSGT(("pstIFMS1000ParamsS32TotalNumTable:entry:remove", "row 0x%x\n", (uintptr_t)row));

    entry = (struct pstIFMS1000ParamsS32TotalNumTable_entry *)row->data;
    SNMP_FREE( entry );   /* XXX - release any other internal resources */

    if (table_data)
        netsnmp_tdata_remove_and_delete_row( table_data, row );
    else
        netsnmp_tdata_delete_row( row );    
}


/** handles requests for the pstIFMS1000ParamsS32TotalNumTable table */
int
QPSTProduct::pstIFMS1000ParamsS32TotalNumTable_handler(
    netsnmp_mib_handler               *handler,
    netsnmp_handler_registration      *reginfo,
    netsnmp_agent_request_info        *reqinfo,
    netsnmp_request_info              *requests) {

    netsnmp_request_info       *request;
    netsnmp_table_request_info *table_info;
    netsnmp_tdata              *table_data;
    netsnmp_tdata_row          *table_row;
    struct pstIFMS1000ParamsS32TotalNumTable_entry          *table_entry;
    int                         ret;

    DEBUGMSGTL(("pstIFMS1000:handler", "Processing request (%d)\n", reqinfo->mode));

    switch (reqinfo->mode) {
        /*
         * Read-support (also covers GetNext requests)
         */
    case MODE_GET:
        for (request=requests; request; request=request->next) {
            if (request->processed)
                continue;

            table_entry = (struct pstIFMS1000ParamsS32TotalNumTable_entry *)
                              netsnmp_tdata_extract_entry(request);
            table_info  =     netsnmp_extract_table_info( request);
    
            switch (table_info->colnum) {
            case COLUMN_S32TPORTNUM:
                if ( !table_entry ) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_NOSUCHINSTANCE);
                    continue;
                }
                snmp_set_var_typed_integer( request->requestvb, ASN_INTEGER,
                                            table_entry->s32TPortNum);
                break;
            case COLUMN_S32PORTTOTALNUM:
                if ( !table_entry ) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_NOSUCHINSTANCE);
                    continue;
                }
                snmp_set_var_typed_integer( request->requestvb, ASN_INTEGER,
                                            table_entry->s32PortTotalNum);
                break;
            default:
                netsnmp_set_request_error(reqinfo, request,
                                          SNMP_NOSUCHOBJECT);
                break;
            }
        }
        break;

    }
    return SNMP_ERR_NOERROR;
}

/** Initialize the pstIFMS1000ParamsS32NameTable table by defining its contents and how it's structured */
void
QPSTProduct::initialize_table_pstIFMS1000ParamsS32NameTable(void)
{
    const oid pstIFMS1000ParamsS32NameTable_oid[] = {1,3,6,1,4,1,48391,3,5,16,2};
    const size_t pstIFMS1000ParamsS32NameTable_oid_len   = OID_LENGTH(pstIFMS1000ParamsS32NameTable_oid);
    netsnmp_handler_registration    *reg;
    netsnmp_tdata                   *table_data;
    netsnmp_table_registration_info *table_info;

    DEBUGMSGTL(("pstIFMS1000:init", "initializing table pstIFMS1000ParamsS32NameTable\n"));

    reg = netsnmp_create_handler_registration(
              "pstIFMS1000ParamsS32NameTable",     pstIFMS1000ParamsS32NameTable_handler,
              pstIFMS1000ParamsS32NameTable_oid, pstIFMS1000ParamsS32NameTable_oid_len,
              HANDLER_CAN_RONLY
              );

    table_data = netsnmp_tdata_create_table( "pstIFMS1000ParamsS32NameTable", 0 );
    if (NULL == table_data) {
        snmp_log(LOG_ERR,"error creating tdata table for pstIFMS1000ParamsS32NameTable\n");
        return;
    }
    table_info = SNMP_MALLOC_TYPEDEF( netsnmp_table_registration_info );
    if (NULL == table_info) {
        snmp_log(LOG_ERR,"error creating table info for pstIFMS1000ParamsS32NameTable\n");
        return;
    }
    netsnmp_table_helper_add_indexes(table_info,
                           ASN_INTEGER,  /* index: s32PortNum */
                           ASN_INTEGER,  /* index: s32ParamNameNum */
                           0);

    table_info->min_column = COLUMN_S32PORTNUM;
    table_info->max_column = COLUMN_S32PARAMNAMEVAL;
    
    netsnmp_tdata_register( reg, table_data, table_info );

    /* Initialise the contents of the table here */
}

//    /* Typical data structure for a row entry */
//struct pstIFMS1000ParamsS32NameTable_entry {
//    /* Index values */
//    long s32PortNum;
//    long s32ParamNameNum;

//    /* Column values */
//    long s32PortNum;
//    long s32ParamNameNum;
//    char s32ParamNameVal[NNN];
//    size_t s32ParamNameVal_len;

//    int   valid;
//};

/* create a new row in the table */
static netsnmp_tdata_row *
pstIFMS1000ParamsS32NameTable_createEntry(netsnmp_tdata *table_data
                 , long  s32PortNum
                 , long  s32ParamNameNum
                ) {
    struct pstIFMS1000ParamsS32NameTable_entry *entry;
    netsnmp_tdata_row *row;

    entry = SNMP_MALLOC_TYPEDEF(struct pstIFMS1000ParamsS32NameTable_entry);
    if (!entry)
        return NULL;

    row = netsnmp_tdata_create_row();
    if (!row) {
        SNMP_FREE(entry);
        return NULL;
    }
    row->data = entry;

    DEBUGMSGT(("pstIFMS1000ParamsS32NameTable:entry:create", "row 0x%x\n", (uintptr_t)row));
    entry->s32PortNum = s32PortNum;
    netsnmp_tdata_row_add_index( row, ASN_INTEGER,
                                 &(entry->s32PortNum),
                                 sizeof(entry->s32PortNum));
    entry->s32ParamNameNum = s32ParamNameNum;
    netsnmp_tdata_row_add_index( row, ASN_INTEGER,
                                 &(entry->s32ParamNameNum),
                                 sizeof(entry->s32ParamNameNum));
    if (table_data)
        netsnmp_tdata_add_row( table_data, row );
    return row;
}

/* remove a row from the table */
static void
pstIFMS1000ParamsS32NameTable_removeEntry(netsnmp_tdata     *table_data, 
                 netsnmp_tdata_row *row) {
    struct pstIFMS1000ParamsS32NameTable_entry *entry;

    if (!row)
        return;    /* Nothing to remove */

    DEBUGMSGT(("pstIFMS1000ParamsS32NameTable:entry:remove", "row 0x%x\n", (uintptr_t)row));

    entry = (struct pstIFMS1000ParamsS32NameTable_entry *)row->data;
    SNMP_FREE( entry );   /* XXX - release any other internal resources */

    if (table_data)
        netsnmp_tdata_remove_and_delete_row( table_data, row );
    else
        netsnmp_tdata_delete_row( row );    
}


/** handles requests for the pstIFMS1000ParamsS32NameTable table */
int
QPSTProduct::pstIFMS1000ParamsS32NameTable_handler(
    netsnmp_mib_handler               *handler,
    netsnmp_handler_registration      *reginfo,
    netsnmp_agent_request_info        *reqinfo,
    netsnmp_request_info              *requests) {

    netsnmp_request_info       *request;
    netsnmp_table_request_info *table_info;
    netsnmp_tdata              *table_data;
    netsnmp_tdata_row          *table_row;
    struct pstIFMS1000ParamsS32NameTable_entry          *table_entry;
    int                         ret;

    DEBUGMSGTL(("pstIFMS1000:handler", "Processing request (%d)\n", reqinfo->mode));

    switch (reqinfo->mode) {
        /*
         * Read-support (also covers GetNext requests)
         */
    case MODE_GET:
        for (request=requests; request; request=request->next) {
            if (request->processed)
                continue;

            table_entry = (struct pstIFMS1000ParamsS32NameTable_entry *)
                              netsnmp_tdata_extract_entry(request);
            table_info  =     netsnmp_extract_table_info( request);
    
            switch (table_info->colnum) {
            case COLUMN_S32PORTNUM:
                if ( !table_entry ) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_NOSUCHINSTANCE);
                    continue;
                }
                snmp_set_var_typed_integer( request->requestvb, ASN_INTEGER,
                                            table_entry->s32PortNum);
                break;
            case COLUMN_S32PARAMNAMENUM:
                if ( !table_entry ) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_NOSUCHINSTANCE);
                    continue;
                }
                snmp_set_var_typed_integer( request->requestvb, ASN_INTEGER,
                                            table_entry->s32ParamNameNum);
                break;
            case COLUMN_S32PARAMNAMEVAL:
                if ( !table_entry ) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_NOSUCHINSTANCE);
                    continue;
                }
                snmp_set_var_typed_value( request->requestvb, ASN_OCTET_STR,
                                          table_entry->s32ParamNameVal,
                                          table_entry->s32ParamNameVal_len);
                break;
            default:
                netsnmp_set_request_error(reqinfo, request,
                                          SNMP_NOSUCHOBJECT);
                break;
            }
        }
        break;

    }
    return SNMP_ERR_NOERROR;
}

/** Initialize the pstIFMS1000ParamsS32ValTable table by defining its contents and how it's structured */
void
QPSTProduct::initialize_table_pstIFMS1000ParamsS32ValTable(void)
{
    const oid pstIFMS1000ParamsS32ValTable_oid[] = {1,3,6,1,4,1,48391,3,5,16,3};
    const size_t pstIFMS1000ParamsS32ValTable_oid_len   = OID_LENGTH(pstIFMS1000ParamsS32ValTable_oid);
    netsnmp_handler_registration    *reg;
    netsnmp_tdata                   *table_data;
    netsnmp_table_registration_info *table_info;

    DEBUGMSGTL(("pstIFMS1000:init", "initializing table pstIFMS1000ParamsS32ValTable\n"));

    reg = netsnmp_create_handler_registration(
              "pstIFMS1000ParamsS32ValTable",     pstIFMS1000ParamsS32ValTable_handler,
              pstIFMS1000ParamsS32ValTable_oid, pstIFMS1000ParamsS32ValTable_oid_len,
              HANDLER_CAN_RWRITE
              );

    table_data = netsnmp_tdata_create_table( "pstIFMS1000ParamsS32ValTable", 0 );
    if (NULL == table_data) {
        snmp_log(LOG_ERR,"error creating tdata table for pstIFMS1000ParamsS32ValTable\n");
        return;
    }
    table_info = SNMP_MALLOC_TYPEDEF( netsnmp_table_registration_info );
    if (NULL == table_info) {
        snmp_log(LOG_ERR,"error creating table info for pstIFMS1000ParamsS32ValTable\n");
        return;
    }
    netsnmp_table_helper_add_indexes(table_info,
                           ASN_INTEGER,  /* index: s32ValPortNum */
                           ASN_INTEGER,  /* index: s32ParamValNum */
                           0);

    table_info->min_column = COLUMN_S32VALPORTNUM;
    table_info->max_column = COLUMN_S32PARAMVAL;
    
    netsnmp_tdata_register( reg, table_data, table_info );

    /* Initialise the contents of the table here */
}

//    /* Typical data structure for a row entry */
//struct pstIFMS1000ParamsS32ValTable_entry {
//    /* Index values */
//    long s32ValPortNum;
//    long s32ParamValNum;

//    /* Column values */
//    long s32ValPortNum;
//    long s32ParamValNum;
//    char s32ParamVal[NNN];
//    size_t s32ParamVal_len;
//    char old_s32ParamVal[NNN];
//    size_t old_s32ParamVal_len;

//    int   valid;
//};

/* create a new row in the table */
static netsnmp_tdata_row *
pstIFMS1000ParamsS32ValTable_createEntry(netsnmp_tdata *table_data
                 , long  s32ValPortNum
                 , long  s32ParamValNum
                ) {
    struct pstIFMS1000ParamsS32ValTable_entry *entry;
    netsnmp_tdata_row *row;

    entry = SNMP_MALLOC_TYPEDEF(struct pstIFMS1000ParamsS32ValTable_entry);
    if (!entry)
        return NULL;

    row = netsnmp_tdata_create_row();
    if (!row) {
        SNMP_FREE(entry);
        return NULL;
    }
    row->data = entry;

    DEBUGMSGT(("pstIFMS1000ParamsS32ValTable:entry:create", "row 0x%x\n", (uintptr_t)row));
    entry->s32ValPortNum = s32ValPortNum;
    netsnmp_tdata_row_add_index( row, ASN_INTEGER,
                                 &(entry->s32ValPortNum),
                                 sizeof(entry->s32ValPortNum));
    entry->s32ParamValNum = s32ParamValNum;
    netsnmp_tdata_row_add_index( row, ASN_INTEGER,
                                 &(entry->s32ParamValNum),
                                 sizeof(entry->s32ParamValNum));
    if (table_data)
        netsnmp_tdata_add_row( table_data, row );
    return row;
}

/* remove a row from the table */
static void
pstIFMS1000ParamsS32ValTable_removeEntry(netsnmp_tdata     *table_data, 
                 netsnmp_tdata_row *row) {
    struct pstIFMS1000ParamsS32ValTable_entry *entry;

    if (!row)
        return;    /* Nothing to remove */

    DEBUGMSGT(("pstIFMS1000ParamsS32ValTable:entry:remove", "row 0x%x\n", (uintptr_t)row));

    entry = (struct pstIFMS1000ParamsS32ValTable_entry *)row->data;
    SNMP_FREE( entry );   /* XXX - release any other internal resources */

    if (table_data)
        netsnmp_tdata_remove_and_delete_row( table_data, row );
    else
        netsnmp_tdata_delete_row( row );    
}


/** handles requests for the pstIFMS1000ParamsS32ValTable table */
int
QPSTProduct::pstIFMS1000ParamsS32ValTable_handler(
    netsnmp_mib_handler               *handler,
    netsnmp_handler_registration      *reginfo,
    netsnmp_agent_request_info        *reqinfo,
    netsnmp_request_info              *requests) {

    netsnmp_request_info       *request;
    netsnmp_table_request_info *table_info;
    netsnmp_tdata              *table_data;
    netsnmp_tdata_row          *table_row;
    struct pstIFMS1000ParamsS32ValTable_entry          *table_entry;
    int                         ret;

    DEBUGMSGTL(("pstIFMS1000:handler", "Processing request (%d)\n", reqinfo->mode));

    switch (reqinfo->mode) {
        /*
         * Read-support (also covers GetNext requests)
         */
    case MODE_GET:
        for (request=requests; request; request=request->next) {
            if (request->processed)
                continue;

            table_entry = (struct pstIFMS1000ParamsS32ValTable_entry *)
                              netsnmp_tdata_extract_entry(request);
            table_info  =     netsnmp_extract_table_info( request);
    
            switch (table_info->colnum) {
            case COLUMN_S32VALPORTNUM:
                if ( !table_entry ) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_NOSUCHINSTANCE);
                    continue;
                }
                snmp_set_var_typed_integer( request->requestvb, ASN_INTEGER,
                                            table_entry->s32ValPortNum);
                break;
            case COLUMN_S32PARAMVALNUM:
                if ( !table_entry ) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_NOSUCHINSTANCE);
                    continue;
                }
                snmp_set_var_typed_integer( request->requestvb, ASN_INTEGER,
                                            table_entry->s32ParamValNum);
                break;
            case COLUMN_S32PARAMVAL:
                if ( !table_entry ) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_NOSUCHINSTANCE);
                    continue;
                }
                snmp_set_var_typed_value( request->requestvb, ASN_OCTET_STR,
                                          table_entry->s32ParamVal,
                                          table_entry->s32ParamVal_len);
                break;
            default:
                netsnmp_set_request_error(reqinfo, request,
                                          SNMP_NOSUCHOBJECT);
                break;
            }
        }
        break;

        /*
         * Write-support
         */
    case MODE_SET_RESERVE1:
        for (request=requests; request; request=request->next) {
            if (request->processed)
                continue;

            table_entry = (struct pstIFMS1000ParamsS32ValTable_entry *)
                              netsnmp_tdata_extract_entry(request);
            table_info  =     netsnmp_extract_table_info( request);
    
            switch (table_info->colnum) {
            case COLUMN_S32PARAMVAL:
	        /* or possibly 'netsnmp_check_vb_type_and_size' */
                ret = netsnmp_check_vb_type_and_max_size(
                          request->requestvb, ASN_OCTET_STR, sizeof(table_entry->s32ParamVal));
                if ( ret != SNMP_ERR_NOERROR ) {
                    netsnmp_set_request_error( reqinfo, request, ret );
                    return SNMP_ERR_NOERROR;
                }
                break;
            default:
                netsnmp_set_request_error( reqinfo, request,
                                           SNMP_ERR_NOTWRITABLE );
                return SNMP_ERR_NOERROR;
            }
        }
        break;

    case MODE_SET_RESERVE2:
        break;

    case MODE_SET_FREE:
        break;

    case MODE_SET_ACTION:
        for (request=requests; request; request=request->next) {
            if (request->processed)
                continue;

            table_entry = (struct pstIFMS1000ParamsS32ValTable_entry *)
                              netsnmp_tdata_extract_entry(request);
            table_info  =     netsnmp_extract_table_info( request);
    
            switch (table_info->colnum) {
            case COLUMN_S32PARAMVAL:
                memcpy( table_entry->old_s32ParamVal,
                        table_entry->s32ParamVal,
                        sizeof(table_entry->s32ParamVal));
                table_entry->old_s32ParamVal_len =
                        table_entry->s32ParamVal_len;
                memset( table_entry->s32ParamVal, 0,
                        sizeof(table_entry->s32ParamVal));
                memcpy( table_entry->s32ParamVal,
                        request->requestvb->val.string,
                        request->requestvb->val_len);
                table_entry->s32ParamVal_len =
                        request->requestvb->val_len;
                break;
            }
        }
        break;

    case MODE_SET_UNDO:
        for (request=requests; request; request=request->next) {
            if (request->processed)
                continue;

            table_entry = (struct pstIFMS1000ParamsS32ValTable_entry *)
                              netsnmp_tdata_extract_entry(request);
            table_row   =     netsnmp_tdata_extract_row(  request);
            table_data  =     netsnmp_tdata_extract_table(request);
            table_info  =     netsnmp_extract_table_info( request);
    
            switch (table_info->colnum) {
            case COLUMN_S32PARAMVAL:
                memcpy( table_entry->s32ParamVal,
                        table_entry->old_s32ParamVal,
                        sizeof(table_entry->s32ParamVal));
                memset( table_entry->old_s32ParamVal, 0,
                        sizeof(table_entry->s32ParamVal));
                table_entry->s32ParamVal_len =
                        table_entry->old_s32ParamVal_len;
                break;
            }
        }
        break;

    case MODE_SET_COMMIT:
        break;
    }
    return SNMP_ERR_NOERROR;
}
#endif
