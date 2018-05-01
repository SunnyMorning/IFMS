#include "qpstproduct.h"

QPSTProduct::QPSTProduct(QObject *parent) : QObject(parent)
{
    _agent = (QAgentApp*)parent;
}

void QPSTProduct::init_pstIFMS1000()
{
    const oid pstIFMS1000SysLedPW1_oid[] = { 1,3,6,1,4,1,48391,3,5,6,1,1 };
    const oid pstIFMS1000SysLedPW2_oid[] = { 1,3,6,1,4,1,48391,3,5,6,1,2 };
    const oid pstIFMS1000SysLedStatus_oid[] = { 1,3,6,1,4,1,48391,3,5,6,1,3 };
    const oid pstIFMS1000BootMode_oid[] = { 1,3,6,1,4,1,48391,3,5,11,1 };
    const oid pstIFMS1000SwitchModuleNum_oid[] = { 1,3,6,1,4,1,48391,3,5,17,1 };
    const oid pstIFMS1000SwitchInterval_oid[] = { 1,3,6,1,4,1,48391,3,5,17,2 };
    const oid pstIFMS1000SwitchCurrentPort_oid[] = { 1,3,6,1,4,1,48391,3,5,17,3 };
    const oid pstIFMS1000ExtSwitchAttType_oid[] = { 1,3,6,1,4,1,48391,3,5,18,1 };
    const oid pstIFMS1000ExtSwitchAttachPort_oid[] = { 1,3,6,1,4,1,48391,3,5,18,2 };
    const oid pstIFMS1000ExtSwitchConnType_oid[] = { 1,3,6,1,4,1,48391,3,5,18,3 };
    const oid pstIFMS1000ExtSwitchIpAddr_oid[] = { 1,3,6,1,4,1,48391,3,5,18,4 };
    const oid pstIFMS1000ExtSwitchIpPort_oid[] = { 1,3,6,1,4,1,48391,3,5,18,5 };
    const oid pstIFMS1000ExtSwitchUartBaud_oid[] = { 1,3,6,1,4,1,48391,3,5,18,6 };
    const oid pstIFMS1000ExtSwitchTotalSwitchNum_oid[] = { 1,3,6,1,4,1,48391,3,5,18,7 };
    const oid pstIFMS1000ExtSwitchCurrentNum_oid[] = { 1,3,6,1,4,1,48391,3,5,18,8 };
    const oid pstIFMS1000ExtSwitchStatus_oid[] = { 1,3,6,1,4,1,48391,3,5,18,9 };

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
    netsnmp_register_scalar(
        netsnmp_create_handler_registration("pstIFMS1000BootMode", handle_pstIFMS1000BootMode,
                               pstIFMS1000BootMode_oid, OID_LENGTH(pstIFMS1000BootMode_oid),
                               HANDLER_CAN_RWRITE
        ));
    netsnmp_register_scalar(
        netsnmp_create_handler_registration("pstIFMS1000SwitchModuleNum", handle_pstIFMS1000SwitchModuleNum,
                               pstIFMS1000SwitchModuleNum_oid, OID_LENGTH(pstIFMS1000SwitchModuleNum_oid),
                               HANDLER_CAN_RONLY
        ));
    netsnmp_register_scalar(
        netsnmp_create_handler_registration("pstIFMS1000SwitchInterval", handle_pstIFMS1000SwitchInterval,
                               pstIFMS1000SwitchInterval_oid, OID_LENGTH(pstIFMS1000SwitchInterval_oid),
                               HANDLER_CAN_RWRITE
        ));
    netsnmp_register_scalar(
        netsnmp_create_handler_registration("pstIFMS1000SwitchCurrentPort", handle_pstIFMS1000SwitchCurrentPort,
                               pstIFMS1000SwitchCurrentPort_oid, OID_LENGTH(pstIFMS1000SwitchCurrentPort_oid),
                               HANDLER_CAN_RONLY
        ));
    netsnmp_register_scalar(
        netsnmp_create_handler_registration("pstIFMS1000ExtSwitchAttType", handle_pstIFMS1000ExtSwitchAttType,
                               pstIFMS1000ExtSwitchAttType_oid, OID_LENGTH(pstIFMS1000ExtSwitchAttType_oid),
                               HANDLER_CAN_RWRITE
        ));
    netsnmp_register_scalar(
        netsnmp_create_handler_registration("pstIFMS1000ExtSwitchAttachPort", handle_pstIFMS1000ExtSwitchAttachPort,
                               pstIFMS1000ExtSwitchAttachPort_oid, OID_LENGTH(pstIFMS1000ExtSwitchAttachPort_oid),
                               HANDLER_CAN_RWRITE
        ));
    netsnmp_register_scalar(
        netsnmp_create_handler_registration("pstIFMS1000ExtSwitchConnType", handle_pstIFMS1000ExtSwitchConnType,
                               pstIFMS1000ExtSwitchConnType_oid, OID_LENGTH(pstIFMS1000ExtSwitchConnType_oid),
                               HANDLER_CAN_RWRITE
        ));
    netsnmp_register_scalar(
        netsnmp_create_handler_registration("pstIFMS1000ExtSwitchIpAddr", handle_pstIFMS1000ExtSwitchIpAddr,
                               pstIFMS1000ExtSwitchIpAddr_oid, OID_LENGTH(pstIFMS1000ExtSwitchIpAddr_oid),
                               HANDLER_CAN_RWRITE
        ));
    netsnmp_register_scalar(
        netsnmp_create_handler_registration("pstIFMS1000ExtSwitchIpPort", handle_pstIFMS1000ExtSwitchIpPort,
                               pstIFMS1000ExtSwitchIpPort_oid, OID_LENGTH(pstIFMS1000ExtSwitchIpPort_oid),
                               HANDLER_CAN_RWRITE
        ));
    netsnmp_register_scalar(
        netsnmp_create_handler_registration("pstIFMS1000ExtSwitchUartBaud", handle_pstIFMS1000ExtSwitchUartBaud,
                               pstIFMS1000ExtSwitchUartBaud_oid, OID_LENGTH(pstIFMS1000ExtSwitchUartBaud_oid),
                               HANDLER_CAN_RWRITE
        ));
    netsnmp_register_scalar(
        netsnmp_create_handler_registration("pstIFMS1000ExtSwitchTotalSwitchNum", handle_pstIFMS1000ExtSwitchTotalSwitchNum,
                               pstIFMS1000ExtSwitchTotalSwitchNum_oid, OID_LENGTH(pstIFMS1000ExtSwitchTotalSwitchNum_oid),
                               HANDLER_CAN_RONLY
        ));
    netsnmp_register_scalar(
        netsnmp_create_handler_registration("pstIFMS1000ExtSwitchCurrentNum", handle_pstIFMS1000ExtSwitchCurrentNum,
                               pstIFMS1000ExtSwitchCurrentNum_oid, OID_LENGTH(pstIFMS1000ExtSwitchCurrentNum_oid),
                               HANDLER_CAN_RONLY
        ));
    netsnmp_register_scalar(
        netsnmp_create_handler_registration("pstIFMS1000ExtSwitchStatus", handle_pstIFMS1000ExtSwitchStatus,
                               pstIFMS1000ExtSwitchStatus_oid, OID_LENGTH(pstIFMS1000ExtSwitchStatus_oid),
                               HANDLER_CAN_RONLY
        ));
        

  /* here we initialize all the tables we're planning on supporting */
    initialize_table_pstIFMS1000PortInfoTable();
    initialize_table_pstIFMS1000MeasureTable();
    initialize_table_pstIFMS1000FingerTable();
    initialize_table_pstIFMS1000DiffTotalTable();
    initialize_table_pstIFMS1000DiffInfoTable();
    initialize_table_pstIFMS1000PortLedTable();
    initialize_table_pstIFMS1000DiagnoseTable();
    initialize_table_pstIFMS1000DebugRegTable();
    initialize_table_pstIFMS1000DebugDACTable();
    initialize_table_pstIFMS1000DebugE2promTable();
    initialize_table_pstIFMS1000ExtendAlarmTable();
    initialize_table_pstIFMS1000ExpertExtendTable();
    initialize_table_pstIFMS1000PonConfTable();
    initialize_table_pstIFMS1000ParamsV32TotalNumTable();
    initialize_table_pstIFMS1000ParamsV32NameTable();
    initialize_table_pstIFMS1000ParamsV32ValTable();
    initialize_table_pstIFMS1000ParamsS32TotalNumTable();
    initialize_table_pstIFMS1000ParamsS32NameTable();
    initialize_table_pstIFMS1000ParamsS32ValTable();
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

    switch(reqinfo->mode) {

        case MODE_GET:
            snmp_set_var_typed_value(requests->requestvb, ASN_INTEGER,
                                     /* XXX: a pointer to the scalar's data */,
                                     /* XXX: the length of the data in bytes */);
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
    
    switch(reqinfo->mode) {

        case MODE_GET:
            snmp_set_var_typed_value(requests->requestvb, ASN_INTEGER,
                                     /* XXX: a pointer to the scalar's data */,
                                     /* XXX: the length of the data in bytes */);
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
    
    switch(reqinfo->mode) {

        case MODE_GET:
            snmp_set_var_typed_value(requests->requestvb, ASN_INTEGER,
                                     /* XXX: a pointer to the scalar's data */,
                                     /* XXX: the length of the data in bytes */);
            break;


        default:
            /* we should never get here, so this is a really bad error */
            snmp_log(LOG_ERR, "unknown mode (%d) in handle_pstIFMS1000SysLedStatus\n", reqinfo->mode );
            return SNMP_ERR_GENERR;
    }

    return SNMP_ERR_NOERROR;
}
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
    
    switch(reqinfo->mode) {

        case MODE_GET:
            snmp_set_var_typed_value(requests->requestvb, ASN_INTEGER,
                                     /* XXX: a pointer to the scalar's data */,
                                     /* XXX: the length of the data in bytes */);
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
            if (/* XXX if malloc, or whatever, failed: */) {
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
            if (/* XXX: error? */) {
                netsnmp_set_request_error(reqinfo, requests, /* some error */);
            }
            break;

        case MODE_SET_COMMIT:
            /* XXX: delete temporary storage */
            if (/* XXX: error? */) {
                /* try _really_really_ hard to never get to this point */
                netsnmp_set_request_error(reqinfo, requests, SNMP_ERR_COMMITFAILED);
            }
            break;

        case MODE_SET_UNDO:
            /* XXX: UNDO and return to previous value for the object */
            if (/* XXX: error? */) {
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
    
    switch(reqinfo->mode) {

        case MODE_GET:
            snmp_set_var_typed_value(requests->requestvb, ASN_INTEGER,
                                     /* XXX: a pointer to the scalar's data */,
                                     /* XXX: the length of the data in bytes */);
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
    
    switch(reqinfo->mode) {

        case MODE_GET:
            snmp_set_var_typed_value(requests->requestvb, ASN_INTEGER,
                                     /* XXX: a pointer to the scalar's data */,
                                     /* XXX: the length of the data in bytes */);
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
            if (/* XXX if malloc, or whatever, failed: */) {
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
            if (/* XXX: error? */) {
                netsnmp_set_request_error(reqinfo, requests, /* some error */);
            }
            break;

        case MODE_SET_COMMIT:
            /* XXX: delete temporary storage */
            if (/* XXX: error? */) {
                /* try _really_really_ hard to never get to this point */
                netsnmp_set_request_error(reqinfo, requests, SNMP_ERR_COMMITFAILED);
            }
            break;

        case MODE_SET_UNDO:
            /* XXX: UNDO and return to previous value for the object */
            if (/* XXX: error? */) {
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
    
    switch(reqinfo->mode) {

        case MODE_GET:
            snmp_set_var_typed_value(requests->requestvb, ASN_INTEGER,
                                     /* XXX: a pointer to the scalar's data */,
                                     /* XXX: the length of the data in bytes */);
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
    
    switch(reqinfo->mode) {

        case MODE_GET:
            snmp_set_var_typed_value(requests->requestvb, ASN_INTEGER,
                                     /* XXX: a pointer to the scalar's data */,
                                     /* XXX: the length of the data in bytes */);
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
            if (/* XXX if malloc, or whatever, failed: */) {
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
            if (/* XXX: error? */) {
                netsnmp_set_request_error(reqinfo, requests, /* some error */);
            }
            break;

        case MODE_SET_COMMIT:
            /* XXX: delete temporary storage */
            if (/* XXX: error? */) {
                /* try _really_really_ hard to never get to this point */
                netsnmp_set_request_error(reqinfo, requests, SNMP_ERR_COMMITFAILED);
            }
            break;

        case MODE_SET_UNDO:
            /* XXX: UNDO and return to previous value for the object */
            if (/* XXX: error? */) {
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
    
    switch(reqinfo->mode) {

        case MODE_GET:
            snmp_set_var_typed_value(requests->requestvb, ASN_INTEGER,
                                     /* XXX: a pointer to the scalar's data */,
                                     /* XXX: the length of the data in bytes */);
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
            if (/* XXX if malloc, or whatever, failed: */) {
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
            if (/* XXX: error? */) {
                netsnmp_set_request_error(reqinfo, requests, /* some error */);
            }
            break;

        case MODE_SET_COMMIT:
            /* XXX: delete temporary storage */
            if (/* XXX: error? */) {
                /* try _really_really_ hard to never get to this point */
                netsnmp_set_request_error(reqinfo, requests, SNMP_ERR_COMMITFAILED);
            }
            break;

        case MODE_SET_UNDO:
            /* XXX: UNDO and return to previous value for the object */
            if (/* XXX: error? */) {
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
    
    switch(reqinfo->mode) {

        case MODE_GET:
            snmp_set_var_typed_value(requests->requestvb, ASN_INTEGER,
                                     /* XXX: a pointer to the scalar's data */,
                                     /* XXX: the length of the data in bytes */);
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
            if (/* XXX if malloc, or whatever, failed: */) {
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
            if (/* XXX: error? */) {
                netsnmp_set_request_error(reqinfo, requests, /* some error */);
            }
            break;

        case MODE_SET_COMMIT:
            /* XXX: delete temporary storage */
            if (/* XXX: error? */) {
                /* try _really_really_ hard to never get to this point */
                netsnmp_set_request_error(reqinfo, requests, SNMP_ERR_COMMITFAILED);
            }
            break;

        case MODE_SET_UNDO:
            /* XXX: UNDO and return to previous value for the object */
            if (/* XXX: error? */) {
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
    
    switch(reqinfo->mode) {

        case MODE_GET:
            snmp_set_var_typed_value(requests->requestvb, ASN_IPADDRESS,
                                     /* XXX: a pointer to the scalar's data */,
                                     /* XXX: the length of the data in bytes */);
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
            if (/* XXX if malloc, or whatever, failed: */) {
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
            if (/* XXX: error? */) {
                netsnmp_set_request_error(reqinfo, requests, /* some error */);
            }
            break;

        case MODE_SET_COMMIT:
            /* XXX: delete temporary storage */
            if (/* XXX: error? */) {
                /* try _really_really_ hard to never get to this point */
                netsnmp_set_request_error(reqinfo, requests, SNMP_ERR_COMMITFAILED);
            }
            break;

        case MODE_SET_UNDO:
            /* XXX: UNDO and return to previous value for the object */
            if (/* XXX: error? */) {
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
    
    switch(reqinfo->mode) {

        case MODE_GET:
            snmp_set_var_typed_value(requests->requestvb, ASN_INTEGER,
                                     /* XXX: a pointer to the scalar's data */,
                                     /* XXX: the length of the data in bytes */);
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
            if (/* XXX if malloc, or whatever, failed: */) {
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
            if (/* XXX: error? */) {
                netsnmp_set_request_error(reqinfo, requests, /* some error */);
            }
            break;

        case MODE_SET_COMMIT:
            /* XXX: delete temporary storage */
            if (/* XXX: error? */) {
                /* try _really_really_ hard to never get to this point */
                netsnmp_set_request_error(reqinfo, requests, SNMP_ERR_COMMITFAILED);
            }
            break;

        case MODE_SET_UNDO:
            /* XXX: UNDO and return to previous value for the object */
            if (/* XXX: error? */) {
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
    
    switch(reqinfo->mode) {

        case MODE_GET:
            snmp_set_var_typed_value(requests->requestvb, ASN_INTEGER,
                                     /* XXX: a pointer to the scalar's data */,
                                     /* XXX: the length of the data in bytes */);
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
            if (/* XXX if malloc, or whatever, failed: */) {
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
            if (/* XXX: error? */) {
                netsnmp_set_request_error(reqinfo, requests, /* some error */);
            }
            break;

        case MODE_SET_COMMIT:
            /* XXX: delete temporary storage */
            if (/* XXX: error? */) {
                /* try _really_really_ hard to never get to this point */
                netsnmp_set_request_error(reqinfo, requests, SNMP_ERR_COMMITFAILED);
            }
            break;

        case MODE_SET_UNDO:
            /* XXX: UNDO and return to previous value for the object */
            if (/* XXX: error? */) {
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
    
    switch(reqinfo->mode) {

        case MODE_GET:
            snmp_set_var_typed_value(requests->requestvb, ASN_INTEGER,
                                     /* XXX: a pointer to the scalar's data */,
                                     /* XXX: the length of the data in bytes */);
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
    
    switch(reqinfo->mode) {

        case MODE_GET:
            snmp_set_var_typed_value(requests->requestvb, ASN_INTEGER,
                                     /* XXX: a pointer to the scalar's data */,
                                     /* XXX: the length of the data in bytes */);
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
    
    switch(reqinfo->mode) {

        case MODE_GET:
            snmp_set_var_typed_value(requests->requestvb, ASN_INTEGER,
                                     /* XXX: a pointer to the scalar's data */,
                                     /* XXX: the length of the data in bytes */);
            break;


        default:
            /* we should never get here, so this is a really bad error */
            snmp_log(LOG_ERR, "unknown mode (%d) in handle_pstIFMS1000ExtSwitchStatus\n", reqinfo->mode );
            return SNMP_ERR_GENERR;
    }

    return SNMP_ERR_NOERROR;
}

// Table

/** Initialize the pstIFMS1000PortInfoTable table by defining its contents and how it's structured */
void
 QPSTProduct::initialize_table_pstIFMS1000PortInfoTable(void)
{
    const oid pstIFMS1000PortInfoTable_oid[] = {1,3,6,1,4,1,48391,3,5,1};
    netsnmp_table_data_set *table_set;

    /* create the table structure itself */
    table_set = netsnmp_create_table_data_set("pstIFMS1000PortInfoTable");

    /* comment this out or delete if you don't support creation of new rows */
    table_set->allow_creation = 1;

    /***************************************************
     * Adding indexes
     */
    DEBUGMSGTL(("initialize_table_pstIFMS1000PortInfoTable",
                "adding indexes to table pstIFMS1000PortInfoTable\n"));
    netsnmp_table_set_add_indexes(table_set,
                           ASN_INTEGER,  /* index: pstIFMS1000PortNum */
                           0);

    DEBUGMSGTL(("initialize_table_pstIFMS1000PortInfoTable",
                "adding column types to table pstIFMS1000PortInfoTable\n"));		 
    netsnmp_table_set_multi_add_default_row(table_set,
                                            COLUMN_PSTIFMS1000PORTNUM, ASN_INTEGER, 0,
                                            NULL, 0,
                                            COLUMN_PSTIFMS1000PORTRXPWR, ASN_OCTET_STR, 0,
                                            NULL, 0,
                                            COLUMN_PSTIFMS1000PORTTXPWR, ASN_OCTET_STR, 0,
                                            NULL, 0,
                                            COLUMN_PSTIFMS1000PORTWORKMODE, ASN_INTEGER, 1,
                                            NULL, 0,
                                            COLUMN_PSTIFMS1000PORTACTIVE, ASN_INTEGER, 0,
                                            NULL, 0,
                                            COLUMN_PSTIFMS1000PORTFIBERAPPTYPE, ASN_INTEGER, 1,
                                            NULL, 0,
                                            COLUMN_PSTIFMS1000PORTRUNNINGSTATUS, ASN_INTEGER, 0,
                                            NULL, 0,
                              0);
    
    /* registering the table with the master agent */
    /* note: if you don't need a subhandler to deal with any aspects
       of the request, change pstIFMS1000PortInfoTable_handler to "NULL" */
    netsnmp_register_table_data_set(netsnmp_create_handler_registration("pstIFMS1000PortInfoTable", pstIFMS1000PortInfoTable_handler,
                                                        pstIFMS1000PortInfoTable_oid,
                                                        OID_LENGTH(pstIFMS1000PortInfoTable_oid),
                                                        HANDLER_CAN_RWRITE),
                            table_set, NULL);
}
/** Initialize the pstIFMS1000MeasureTable table by defining its contents and how it's structured */
void
 QPSTProduct::initialize_table_pstIFMS1000MeasureTable(void)
{
    const oid pstIFMS1000MeasureTable_oid[] = {1,3,6,1,4,1,48391,3,5,2};
    netsnmp_table_data_set *table_set;

    /* create the table structure itself */
    table_set = netsnmp_create_table_data_set("pstIFMS1000MeasureTable");

    /* comment this out or delete if you don't support creation of new rows */
    table_set->allow_creation = 1;

    /***************************************************
     * Adding indexes
     */
    DEBUGMSGTL(("initialize_table_pstIFMS1000MeasureTable",
                "adding indexes to table pstIFMS1000MeasureTable\n"));
    netsnmp_table_set_add_indexes(table_set,
                           ASN_INTEGER,  /* index: pstIFMS1000MTPortNum */
                           0);

    DEBUGMSGTL(("initialize_table_pstIFMS1000MeasureTable",
                "adding column types to table pstIFMS1000MeasureTable\n"));		 
    netsnmp_table_set_multi_add_default_row(table_set,
                                            COLUMN_PSTIFMS1000MTPORTNUM, ASN_INTEGER, 0,
                                            NULL, 0,
                                            COLUMN_PSTIFMS1000MEASURESTARTPOSITION, ASN_OCTET_STR, 1,
                                            NULL, 0,
                                            COLUMN_PSTIFMS1000MEASUREENDPOSITION, ASN_OCTET_STR, 1,
                                            NULL, 0,
                                            COLUMN_PSTIFMS1000MEASUREREFINDEX, ASN_OCTET_STR, 1,
                                            NULL, 0,
                                            COLUMN_PSTIFMS1000MEASURERESOLUTION, ASN_OCTET_STR, 1,
                                            NULL, 0,
                                            COLUMN_PSTIFMS1000MEASURESTATUS, ASN_INTEGER, 0,
                                            NULL, 0,
                                            COLUMN_PSTIFMS1000MEASUREACTION, ASN_INTEGER, 1,
                                            NULL, 0,
                                            COLUMN_PSTIFMS1000MEASURERESULTFILE, ASN_OCTET_STR, 0,
                                            NULL, 0,
                                            COLUMN_PSTIFMS1000MEASURERESULTRAWDATAFILE, ASN_OCTET_STR, 0,
                                            NULL, 0,
                                            COLUMN_PSTIFMS1000MEASUREPROGRESSSTATUS, ASN_INTEGER, 0,
                                            NULL, 0,
                                            COLUMN_PSTIFMS1000MEASURERESULTRAWPOINTFILE, ASN_OCTET_STR, 1,
                                            NULL, 0,
                              0);
    
    /* registering the table with the master agent */
    /* note: if you don't need a subhandler to deal with any aspects
       of the request, change pstIFMS1000MeasureTable_handler to "NULL" */
    netsnmp_register_table_data_set(netsnmp_create_handler_registration("pstIFMS1000MeasureTable", pstIFMS1000MeasureTable_handler,
                                                        pstIFMS1000MeasureTable_oid,
                                                        OID_LENGTH(pstIFMS1000MeasureTable_oid),
                                                        HANDLER_CAN_RWRITE),
                            table_set, NULL);
}
/** Initialize the pstIFMS1000FingerTable table by defining its contents and how it's structured */
void
 QPSTProduct::initialize_table_pstIFMS1000FingerTable(void)
{
    const oid pstIFMS1000FingerTable_oid[] = {1,3,6,1,4,1,48391,3,5,3};
    netsnmp_table_data_set *table_set;

    /* create the table structure itself */
    table_set = netsnmp_create_table_data_set("pstIFMS1000FingerTable");

    /* comment this out or delete if you don't support creation of new rows */
    table_set->allow_creation = 1;

    /***************************************************
     * Adding indexes
     */
    DEBUGMSGTL(("initialize_table_pstIFMS1000FingerTable",
                "adding indexes to table pstIFMS1000FingerTable\n"));
    netsnmp_table_set_add_indexes(table_set,
                           ASN_INTEGER,  /* index: pstIFMS1000FTPortNum */
                           0);

    DEBUGMSGTL(("initialize_table_pstIFMS1000FingerTable",
                "adding column types to table pstIFMS1000FingerTable\n"));		 
    netsnmp_table_set_multi_add_default_row(table_set,
                                            COLUMN_PSTIFMS1000FTPORTNUM, ASN_INTEGER, 0,
                                            NULL, 0,
                                            COLUMN_PSTIFMS1000FINGERSTARTPOSITION, ASN_OCTET_STR, 1,
                                            NULL, 0,
                                            COLUMN_PSTIFMS1000FINGERENDPOSITION, ASN_OCTET_STR, 1,
                                            NULL, 0,
                                            COLUMN_PSTIFMS1000FINGERREFINDEX, ASN_OCTET_STR, 1,
                                            NULL, 0,
                                            COLUMN_PSTIFMS1000FINGERRESOLUTION, ASN_OCTET_STR, 1,
                                            NULL, 0,
                                            COLUMN_PSTIFMS1000FINGERCREATETIME, ASN_OCTET_STR, 0,
                                            NULL, 0,
                                            COLUMN_PSTIFMS1000FINGERFILESTATUS, ASN_INTEGER, 0,
                                            NULL, 0,
                                            COLUMN_PSTIFMS1000FINGERACTION, ASN_INTEGER, 1,
                                            NULL, 0,
                                            COLUMN_PSTIFMS1000FINGERACTIONSTATUS, ASN_INTEGER, 0,
                                            NULL, 0,
                                            COLUMN_PSTIFMS1000FINGERSAVEDFILENAME, ASN_OCTET_STR, 0,
                                            NULL, 0,
                                            COLUMN_PSTIFMS1000FINGERCURRENTFILENAME, ASN_OCTET_STR, 0,
                                            NULL, 0,
                              0);
    
    /* registering the table with the master agent */
    /* note: if you don't need a subhandler to deal with any aspects
       of the request, change pstIFMS1000FingerTable_handler to "NULL" */
    netsnmp_register_table_data_set(netsnmp_create_handler_registration("pstIFMS1000FingerTable", pstIFMS1000FingerTable_handler,
                                                        pstIFMS1000FingerTable_oid,
                                                        OID_LENGTH(pstIFMS1000FingerTable_oid),
                                                        HANDLER_CAN_RWRITE),
                            table_set, NULL);
}
/** Initialize the pstIFMS1000DiffTotalTable table by defining its contents and how it's structured */
void
 QPSTProduct::initialize_table_pstIFMS1000DiffTotalTable(void)
{
    const oid pstIFMS1000DiffTotalTable_oid[] = {1,3,6,1,4,1,48391,3,5,4,1};
    netsnmp_table_data_set *table_set;

    /* create the table structure itself */
    table_set = netsnmp_create_table_data_set("pstIFMS1000DiffTotalTable");

    /* comment this out or delete if you don't support creation of new rows */
    table_set->allow_creation = 1;

    /***************************************************
     * Adding indexes
     */
    DEBUGMSGTL(("initialize_table_pstIFMS1000DiffTotalTable",
                "adding indexes to table pstIFMS1000DiffTotalTable\n"));
    netsnmp_table_set_add_indexes(table_set,
                           ASN_INTEGER,  /* index: pstIFMS1000DtPortNum */
                           0);

    DEBUGMSGTL(("initialize_table_pstIFMS1000DiffTotalTable",
                "adding column types to table pstIFMS1000DiffTotalTable\n"));		 
    netsnmp_table_set_multi_add_default_row(table_set,
                                            COLUMN_PSTIFMS1000DTPORTNUM, ASN_INTEGER, 0,
                                            NULL, 0,
                                            COLUMN_PSTIFMS1000DTTOTALNUM, ASN_INTEGER, 0,
                                            NULL, 0,
                              0);
    
    /* registering the table with the master agent */
    /* note: if you don't need a subhandler to deal with any aspects
       of the request, change pstIFMS1000DiffTotalTable_handler to "NULL" */
    netsnmp_register_table_data_set(netsnmp_create_handler_registration("pstIFMS1000DiffTotalTable", pstIFMS1000DiffTotalTable_handler,
                                                        pstIFMS1000DiffTotalTable_oid,
                                                        OID_LENGTH(pstIFMS1000DiffTotalTable_oid),
                                                        HANDLER_CAN_RWRITE),
                            table_set, NULL);
}
/** Initialize the pstIFMS1000DiffInfoTable table by defining its contents and how it's structured */
void
 QPSTProduct::initialize_table_pstIFMS1000DiffInfoTable(void)
{
    const oid pstIFMS1000DiffInfoTable_oid[] = {1,3,6,1,4,1,48391,3,5,4,2};
    netsnmp_table_data_set *table_set;

    /* create the table structure itself */
    table_set = netsnmp_create_table_data_set("pstIFMS1000DiffInfoTable");

    /* comment this out or delete if you don't support creation of new rows */
    table_set->allow_creation = 1;

    /***************************************************
     * Adding indexes
     */
    DEBUGMSGTL(("initialize_table_pstIFMS1000DiffInfoTable",
                "adding indexes to table pstIFMS1000DiffInfoTable\n"));
    netsnmp_table_set_add_indexes(table_set,
                           ASN_INTEGER,  /* index: pstIFMS1000DiffInfoPortNum */
                           ASN_INTEGER,  /* index: pstIFMS1000DiffInfoPortItemIndex */
                           0);

    DEBUGMSGTL(("initialize_table_pstIFMS1000DiffInfoTable",
                "adding column types to table pstIFMS1000DiffInfoTable\n"));		 
    netsnmp_table_set_multi_add_default_row(table_set,
                                            COLUMN_PSTIFMS1000DIFFINFOPORTNUM, ASN_INTEGER, 0,
                                            NULL, 0,
                                            COLUMN_PSTIFMS1000DIFFINFOPORTITEMINDEX, ASN_INTEGER, 0,
                                            NULL, 0,
                                            COLUMN_PSTIFMS1000DIFFINFODISTANCE, ASN_OCTET_STR, 0,
                                            NULL, 0,
                                            COLUMN_PSTIFMS1000DIFFINFONVAL, ASN_OCTET_STR, 0,
                                            NULL, 0,
                                            COLUMN_PSTIFMS1000DIFFINFODBVAL, ASN_OCTET_STR, 0,
                                            NULL, 0,
                                            COLUMN_PSTIFMS1000DIFFINFODIFFTYPE, ASN_INTEGER, 0,
                                            NULL, 0,
                                            COLUMN_PSTIFMS1000DIFFINFOPOINTID, ASN_UNSIGNED, 0,
                                            NULL, 0,
                              0);
    
    /* registering the table with the master agent */
    /* note: if you don't need a subhandler to deal with any aspects
       of the request, change pstIFMS1000DiffInfoTable_handler to "NULL" */
    netsnmp_register_table_data_set(netsnmp_create_handler_registration("pstIFMS1000DiffInfoTable", pstIFMS1000DiffInfoTable_handler,
                                                        pstIFMS1000DiffInfoTable_oid,
                                                        OID_LENGTH(pstIFMS1000DiffInfoTable_oid),
                                                        HANDLER_CAN_RWRITE),
                            table_set, NULL);
}
/** Initialize the pstIFMS1000PortLedTable table by defining its contents and how it's structured */
void
 QPSTProduct::initialize_table_pstIFMS1000PortLedTable(void)
{
    const oid pstIFMS1000PortLedTable_oid[] = {1,3,6,1,4,1,48391,3,5,6,2};
    netsnmp_table_data_set *table_set;

    /* create the table structure itself */
    table_set = netsnmp_create_table_data_set("pstIFMS1000PortLedTable");

    /* comment this out or delete if you don't support creation of new rows */
    table_set->allow_creation = 1;

    /***************************************************
     * Adding indexes
     */
    DEBUGMSGTL(("initialize_table_pstIFMS1000PortLedTable",
                "adding indexes to table pstIFMS1000PortLedTable\n"));
    netsnmp_table_set_add_indexes(table_set,
                           ASN_INTEGER,  /* index: pstIFMS1000PortLedPortNum */
                           0);

    DEBUGMSGTL(("initialize_table_pstIFMS1000PortLedTable",
                "adding column types to table pstIFMS1000PortLedTable\n"));		 
    netsnmp_table_set_multi_add_default_row(table_set,
                                            COLUMN_PSTIFMS1000PORTLEDPORTNUM, ASN_INTEGER, 0,
                                            NULL, 0,
                                            COLUMN_PSTIFMS1000PORTLEDSTATUS, ASN_INTEGER, 0,
                                            NULL, 0,
                              0);
    
    /* registering the table with the master agent */
    /* note: if you don't need a subhandler to deal with any aspects
       of the request, change pstIFMS1000PortLedTable_handler to "NULL" */
    netsnmp_register_table_data_set(netsnmp_create_handler_registration("pstIFMS1000PortLedTable", pstIFMS1000PortLedTable_handler,
                                                        pstIFMS1000PortLedTable_oid,
                                                        OID_LENGTH(pstIFMS1000PortLedTable_oid),
                                                        HANDLER_CAN_RWRITE),
                            table_set, NULL);
}
/** Initialize the pstIFMS1000DiagnoseTable table by defining its contents and how it's structured */
void
 QPSTProduct::initialize_table_pstIFMS1000DiagnoseTable(void)
{
    const oid pstIFMS1000DiagnoseTable_oid[] = {1,3,6,1,4,1,48391,3,5,7};
    netsnmp_table_data_set *table_set;

    /* create the table structure itself */
    table_set = netsnmp_create_table_data_set("pstIFMS1000DiagnoseTable");

    /* comment this out or delete if you don't support creation of new rows */
    table_set->allow_creation = 1;

    /***************************************************
     * Adding indexes
     */
    DEBUGMSGTL(("initialize_table_pstIFMS1000DiagnoseTable",
                "adding indexes to table pstIFMS1000DiagnoseTable\n"));
    netsnmp_table_set_add_indexes(table_set,
                           ASN_INTEGER,  /* index: pstIFMS1000DgPortNum */
                           0);

    DEBUGMSGTL(("initialize_table_pstIFMS1000DiagnoseTable",
                "adding column types to table pstIFMS1000DiagnoseTable\n"));		 
    netsnmp_table_set_multi_add_default_row(table_set,
                                            COLUMN_PSTIFMS1000DGPORTNUM, ASN_INTEGER, 0,
                                            NULL, 0,
                                            COLUMN_PSTIFMS1000DGLASERACBIAS, ASN_OCTET_STR, 1,
                                            NULL, 0,
                                            COLUMN_PSTIFMS1000DGLASERDCBIAS, ASN_OCTET_STR, 1,
                                            NULL, 0,
                                            COLUMN_PSTIFMS1000DGLASERACMODULATION, ASN_OCTET_STR, 1,
                                            NULL, 0,
                                            COLUMN_PSTIFMS1000DGLASERDCMODULATION, ASN_OCTET_STR, 1,
                                            NULL, 0,
                                            COLUMN_PSTIFMS1000DGLASEREN, ASN_INTEGER, 1,
                                            NULL, 0,
                                            COLUMN_PSTIFMS1000DGPWM, ASN_INTEGER, 1,
                                            NULL, 0,
                                            COLUMN_PSTIFMS1000DGSEED, ASN_INTEGER, 1,
                                            NULL, 0,
                                            COLUMN_PSTIFMS1000DGPRBS, ASN_INTEGER, 1,
                                            NULL, 0,
                                            COLUMN_PSTIFMS1000DGAVERAGE, ASN_INTEGER, 1,
                                            NULL, 0,
                                            COLUMN_PSTIFMS1000DGREGADDR, ASN_INTEGER, 1,
                                            NULL, 0,
                                            COLUMN_PSTIFMS1000DGREGVALUE, ASN_INTEGER, 1,
                                            NULL, 0,
                                            COLUMN_PSTIFMS1000DGMASKSTARTPOINT, ASN_OCTET_STR, 1,
                                            NULL, 0,
                                            COLUMN_PSTIFMS1000DGMASKSTOPPOINT, ASN_OCTET_STR, 1,
                                            NULL, 0,
                                            COLUMN_PSTIFMS1000DGMASKACTION, ASN_INTEGER, 1,
                                            NULL, 0,
                                            COLUMN_PSTIFMS1000DGMEASUREDELTATHLD, ASN_OCTET_STR, 1,
                                            NULL, 0,
                                            COLUMN_PSTIFMS1000DGCUTPOINTTHLD, ASN_OCTET_STR, 1,
                                            NULL, 0,
                                            COLUMN_PSTIFMS1000DGPERIOD, ASN_INTEGER, 1,
                                            NULL, 0,
                                            COLUMN_PSTIFMS1000DGDAC, ASN_INTEGER, 1,
                                            NULL, 0,
                                            COLUMN_PSTIFMS1000DGCOUNTERCLOCKMODE, ASN_INTEGER, 1,
                                            NULL, 0,
                                            COLUMN_PSTIFMS1000DGSCANRUNTYPE, ASN_INTEGER, 1,
                                            NULL, 0,
                                            COLUMN_PSTIFMS1000DGOPT, ASN_UNSIGNED, 1,
                                            NULL, 0,
                                            COLUMN_PSTIFMS1000DGFIBEROFFSET, ASN_OCTET_STR, 1,
                                            NULL, 0,
                                            COLUMN_PSTIFMS1000DGTESTWAVELEN, ASN_UNSIGNED, 1,
                                            NULL, 0,
                                            COLUMN_PSTIFMS1000DGPRT, ASN_UNSIGNED, 1,
                                            NULL, 0,
                                            COLUMN_PSTIFMS1000DGPPW, ASN_UNSIGNED, 1,
                                            NULL, 0,
                                            COLUMN_PSTIFMS1000DGPPRESCALE, ASN_UNSIGNED, 1,
                                            NULL, 0,
                                            COLUMN_PSTIFMS1000DGPAVG, ASN_UNSIGNED, 1,
                                            NULL, 0,
                                            COLUMN_PSTIFMS1000DGPGAIN, ASN_UNSIGNED, 1,
                                            NULL, 0,
                                            COLUMN_PSTIFMS1000DGPADCDATA, ASN_UNSIGNED, 0,
                                            NULL, 0,
                                            COLUMN_PSTIFMS1000DGPE2PROMACTION, ASN_UNSIGNED, 1,
                                            NULL, 0,
                              0);
    
    /* registering the table with the master agent */
    /* note: if you don't need a subhandler to deal with any aspects
       of the request, change pstIFMS1000DiagnoseTable_handler to "NULL" */
    netsnmp_register_table_data_set(netsnmp_create_handler_registration("pstIFMS1000DiagnoseTable", pstIFMS1000DiagnoseTable_handler,
                                                        pstIFMS1000DiagnoseTable_oid,
                                                        OID_LENGTH(pstIFMS1000DiagnoseTable_oid),
                                                        HANDLER_CAN_RWRITE),
                            table_set, NULL);
}
/** Initialize the pstIFMS1000DebugRegTable table by defining its contents and how it's structured */
void
 QPSTProduct::initialize_table_pstIFMS1000DebugRegTable(void)
{
    const oid pstIFMS1000DebugRegTable_oid[] = {1,3,6,1,4,1,48391,3,5,8};
    netsnmp_table_data_set *table_set;

    /* create the table structure itself */
    table_set = netsnmp_create_table_data_set("pstIFMS1000DebugRegTable");

    /* comment this out or delete if you don't support creation of new rows */
    table_set->allow_creation = 1;

    /***************************************************
     * Adding indexes
     */
    DEBUGMSGTL(("initialize_table_pstIFMS1000DebugRegTable",
                "adding indexes to table pstIFMS1000DebugRegTable\n"));
    netsnmp_table_set_add_indexes(table_set,
                           ASN_INTEGER,  /* index: pstIFMS1000DbPortNum */
                           0);

    DEBUGMSGTL(("initialize_table_pstIFMS1000DebugRegTable",
                "adding column types to table pstIFMS1000DebugRegTable\n"));		 
    netsnmp_table_set_multi_add_default_row(table_set,
                                            COLUMN_PSTIFMS1000DBPORTNUM, ASN_INTEGER, 0,
                                            NULL, 0,
                                            COLUMN_PSTIFMS1000DBREGADDR, ASN_INTEGER, 1,
                                            NULL, 0,
                                            COLUMN_PSTIFMS1000DBREGVALUE, ASN_INTEGER, 1,
                                            NULL, 0,
                              0);
    
    /* registering the table with the master agent */
    /* note: if you don't need a subhandler to deal with any aspects
       of the request, change pstIFMS1000DebugRegTable_handler to "NULL" */
    netsnmp_register_table_data_set(netsnmp_create_handler_registration("pstIFMS1000DebugRegTable", pstIFMS1000DebugRegTable_handler,
                                                        pstIFMS1000DebugRegTable_oid,
                                                        OID_LENGTH(pstIFMS1000DebugRegTable_oid),
                                                        HANDLER_CAN_RWRITE),
                            table_set, NULL);
}
/** Initialize the pstIFMS1000DebugDACTable table by defining its contents and how it's structured */
void
 QPSTProduct::initialize_table_pstIFMS1000DebugDACTable(void)
{
    const oid pstIFMS1000DebugDACTable_oid[] = {1,3,6,1,4,1,48391,3,5,9};
    netsnmp_table_data_set *table_set;

    /* create the table structure itself */
    table_set = netsnmp_create_table_data_set("pstIFMS1000DebugDACTable");

    /* comment this out or delete if you don't support creation of new rows */
    table_set->allow_creation = 1;

    /***************************************************
     * Adding indexes
     */
    DEBUGMSGTL(("initialize_table_pstIFMS1000DebugDACTable",
                "adding indexes to table pstIFMS1000DebugDACTable\n"));
    netsnmp_table_set_add_indexes(table_set,
                           ASN_INTEGER,  /* index: pstIFMS1000DacTPortNum */
                           0);

    DEBUGMSGTL(("initialize_table_pstIFMS1000DebugDACTable",
                "adding column types to table pstIFMS1000DebugDACTable\n"));		 
    netsnmp_table_set_multi_add_default_row(table_set,
                                            COLUMN_PSTIFMS1000DACTPORTNUM, ASN_INTEGER, 0,
                                            NULL, 0,
                                            COLUMN_PSTIFMS1000DACTCHANNELNUM, ASN_INTEGER, 1,
                                            NULL, 0,
                                            COLUMN_PSTIFMS1000TDACVALUE, ASN_INTEGER, 1,
                                            NULL, 0,
                              0);
    
    /* registering the table with the master agent */
    /* note: if you don't need a subhandler to deal with any aspects
       of the request, change pstIFMS1000DebugDACTable_handler to "NULL" */
    netsnmp_register_table_data_set(netsnmp_create_handler_registration("pstIFMS1000DebugDACTable", pstIFMS1000DebugDACTable_handler,
                                                        pstIFMS1000DebugDACTable_oid,
                                                        OID_LENGTH(pstIFMS1000DebugDACTable_oid),
                                                        HANDLER_CAN_RWRITE),
                            table_set, NULL);
}
/** Initialize the pstIFMS1000DebugE2promTable table by defining its contents and how it's structured */
void
 QPSTProduct::initialize_table_pstIFMS1000DebugE2promTable(void)
{
    const oid pstIFMS1000DebugE2promTable_oid[] = {1,3,6,1,4,1,48391,3,5,10};
    netsnmp_table_data_set *table_set;

    /* create the table structure itself */
    table_set = netsnmp_create_table_data_set("pstIFMS1000DebugE2promTable");

    /* comment this out or delete if you don't support creation of new rows */
    table_set->allow_creation = 1;

    /***************************************************
     * Adding indexes
     */
    DEBUGMSGTL(("initialize_table_pstIFMS1000DebugE2promTable",
                "adding indexes to table pstIFMS1000DebugE2promTable\n"));
    netsnmp_table_set_add_indexes(table_set,
                           ASN_INTEGER,  /* index: pstIFMS1000DbE2TPortNum */
                           0);

    DEBUGMSGTL(("initialize_table_pstIFMS1000DebugE2promTable",
                "adding column types to table pstIFMS1000DebugE2promTable\n"));		 
    netsnmp_table_set_multi_add_default_row(table_set,
                                            COLUMN_PSTIFMS1000DBE2TPORTNUM, ASN_INTEGER, 0,
                                            NULL, 0,
                                            COLUMN_PSTIFMS1000DBE2TADDR, ASN_INTEGER, 1,
                                            NULL, 0,
                                            COLUMN_PSTIFMS1000DBE2TVALUE, ASN_INTEGER, 1,
                                            NULL, 0,
                              0);
    
    /* registering the table with the master agent */
    /* note: if you don't need a subhandler to deal with any aspects
       of the request, change pstIFMS1000DebugE2promTable_handler to "NULL" */
    netsnmp_register_table_data_set(netsnmp_create_handler_registration("pstIFMS1000DebugE2promTable", pstIFMS1000DebugE2promTable_handler,
                                                        pstIFMS1000DebugE2promTable_oid,
                                                        OID_LENGTH(pstIFMS1000DebugE2promTable_oid),
                                                        HANDLER_CAN_RWRITE),
                            table_set, NULL);
}
/** Initialize the pstIFMS1000ExtendAlarmTable table by defining its contents and how it's structured */
void
 QPSTProduct::initialize_table_pstIFMS1000ExtendAlarmTable(void)
{
    const oid pstIFMS1000ExtendAlarmTable_oid[] = {1,3,6,1,4,1,48391,3,5,12};
    netsnmp_table_data_set *table_set;

    /* create the table structure itself */
    table_set = netsnmp_create_table_data_set("pstIFMS1000ExtendAlarmTable");

    /* comment this out or delete if you don't support creation of new rows */
    table_set->allow_creation = 1;

    /***************************************************
     * Adding indexes
     */
    DEBUGMSGTL(("initialize_table_pstIFMS1000ExtendAlarmTable",
                "adding indexes to table pstIFMS1000ExtendAlarmTable\n"));
    netsnmp_table_set_add_indexes(table_set,
                           ASN_INTEGER,  /* index: pstIFMS1000EAPortNum */
                           0);

    DEBUGMSGTL(("initialize_table_pstIFMS1000ExtendAlarmTable",
                "adding column types to table pstIFMS1000ExtendAlarmTable\n"));		 
    netsnmp_table_set_multi_add_default_row(table_set,
                                            COLUMN_PSTIFMS1000EAPORTNUM, ASN_INTEGER, 0,
                                            NULL, 0,
                                            COLUMN_PSTIFMS1000EXTENDALARM, ASN_UNSIGNED, 1,
                                            NULL, 0,
                              0);
    
    /* registering the table with the master agent */
    /* note: if you don't need a subhandler to deal with any aspects
       of the request, change pstIFMS1000ExtendAlarmTable_handler to "NULL" */
    netsnmp_register_table_data_set(netsnmp_create_handler_registration("pstIFMS1000ExtendAlarmTable", pstIFMS1000ExtendAlarmTable_handler,
                                                        pstIFMS1000ExtendAlarmTable_oid,
                                                        OID_LENGTH(pstIFMS1000ExtendAlarmTable_oid),
                                                        HANDLER_CAN_RWRITE),
                            table_set, NULL);
}
/** Initialize the pstIFMS1000ExpertExtendTable table by defining its contents and how it's structured */
void
 QPSTProduct::initialize_table_pstIFMS1000ExpertExtendTable(void)
{
    const oid pstIFMS1000ExpertExtendTable_oid[] = {1,3,6,1,4,1,48391,3,5,13};
    netsnmp_table_data_set *table_set;

    /* create the table structure itself */
    table_set = netsnmp_create_table_data_set("pstIFMS1000ExpertExtendTable");

    /* comment this out or delete if you don't support creation of new rows */
    table_set->allow_creation = 1;

    /***************************************************
     * Adding indexes
     */
    DEBUGMSGTL(("initialize_table_pstIFMS1000ExpertExtendTable",
                "adding indexes to table pstIFMS1000ExpertExtendTable\n"));
    netsnmp_table_set_add_indexes(table_set,
                           ASN_INTEGER,  /* index: pstIFMS1000EEPortNum */
                           0);

    DEBUGMSGTL(("initialize_table_pstIFMS1000ExpertExtendTable",
                "adding column types to table pstIFMS1000ExpertExtendTable\n"));		 
    netsnmp_table_set_multi_add_default_row(table_set,
                                            COLUMN_PSTIFMS1000EEPORTNUM, ASN_INTEGER, 0,
                                            NULL, 0,
                                            COLUMN_PSTIFMS1000DGPBIAS1, ASN_OCTET_STR, 1,
                                            NULL, 0,
                                            COLUMN_PSTIFMS1000DGPBIAS2, ASN_OCTET_STR, 1,
                                            NULL, 0,
                                            COLUMN_PSTIFMS1000DGPMODULATION1, ASN_OCTET_STR, 1,
                                            NULL, 0,
                                            COLUMN_PSTIFMS1000DGPMODULATION2, ASN_OCTET_STR, 1,
                                            NULL, 0,
                                            COLUMN_PSTIFMS1000DGPBACKSCATTER, ASN_INTEGER, 1,
                                            NULL, 0,
                                            COLUMN_PSTIFMS1000DGPMEASUREDELTATHLD, ASN_OCTET_STR, 1,
                                            NULL, 0,
                                            COLUMN_PSTIFMS1000DGPCUTPOINTTHLD, ASN_OCTET_STR, 1,
                                            NULL, 0,
                                            COLUMN_PSTIFMS1000DGPMFACTOR, ASN_OCTET_STR, 1,
                                            NULL, 0,
                                            COLUMN_PSTIFMS1000DGFAULTCRITICALTHLD, ASN_OCTET_STR, 1,
                                            NULL, 0,
                                            COLUMN_PSTIFMS1000DGFAULTMAJORTHLD, ASN_OCTET_STR, 1,
                                            NULL, 0,
                                            COLUMN_PSTIFMS1000DGFAULTMINORTHLD, ASN_OCTET_STR, 1,
                                            NULL, 0,
                                            COLUMN_PSTIFMS1000DGPAFACTOR, ASN_OCTET_STR, 1,
                                            NULL, 0,
                                            COLUMN_PSTIFMS1000DGPBFACTOR, ASN_OCTET_STR, 1,
                                            NULL, 0,
                              0);
    
    /* registering the table with the master agent */
    /* note: if you don't need a subhandler to deal with any aspects
       of the request, change pstIFMS1000ExpertExtendTable_handler to "NULL" */
    netsnmp_register_table_data_set(netsnmp_create_handler_registration("pstIFMS1000ExpertExtendTable", pstIFMS1000ExpertExtendTable_handler,
                                                        pstIFMS1000ExpertExtendTable_oid,
                                                        OID_LENGTH(pstIFMS1000ExpertExtendTable_oid),
                                                        HANDLER_CAN_RWRITE),
                            table_set, NULL);
}
/** Initialize the pstIFMS1000PonConfTable table by defining its contents and how it's structured */
void
 QPSTProduct::initialize_table_pstIFMS1000PonConfTable(void)
{
    const oid pstIFMS1000PonConfTable_oid[] = {1,3,6,1,4,1,48391,3,5,14};
    netsnmp_table_data_set *table_set;

    /* create the table structure itself */
    table_set = netsnmp_create_table_data_set("pstIFMS1000PonConfTable");

    /* comment this out or delete if you don't support creation of new rows */
    table_set->allow_creation = 1;

    /***************************************************
     * Adding indexes
     */
    DEBUGMSGTL(("initialize_table_pstIFMS1000PonConfTable",
                "adding indexes to table pstIFMS1000PonConfTable\n"));
    netsnmp_table_set_add_indexes(table_set,
                           ASN_UNSIGNED,  /* index: pctPortNum */
                           0);

    DEBUGMSGTL(("initialize_table_pstIFMS1000PonConfTable",
                "adding column types to table pstIFMS1000PonConfTable\n"));		 
    netsnmp_table_set_multi_add_default_row(table_set,
                                            COLUMN_PCTPORTNUM, ASN_UNSIGNED, 0,
                                            NULL, 0,
                                            COLUMN_PCTSP1LOCITEM, ASN_UNSIGNED, 1,
                                            NULL, 0,
                              0);
    
    /* registering the table with the master agent */
    /* note: if you don't need a subhandler to deal with any aspects
       of the request, change pstIFMS1000PonConfTable_handler to "NULL" */
    netsnmp_register_table_data_set(netsnmp_create_handler_registration("pstIFMS1000PonConfTable", pstIFMS1000PonConfTable_handler,
                                                        pstIFMS1000PonConfTable_oid,
                                                        OID_LENGTH(pstIFMS1000PonConfTable_oid),
                                                        HANDLER_CAN_RWRITE),
                            table_set, NULL);
}
/** Initialize the pstIFMS1000ParamsV32TotalNumTable table by defining its contents and how it's structured */
void
 QPSTProduct::initialize_table_pstIFMS1000ParamsV32TotalNumTable(void)
{
    const oid pstIFMS1000ParamsV32TotalNumTable_oid[] = {1,3,6,1,4,1,48391,3,5,15,1};
    netsnmp_table_data_set *table_set;

    /* create the table structure itself */
    table_set = netsnmp_create_table_data_set("pstIFMS1000ParamsV32TotalNumTable");

    /* comment this out or delete if you don't support creation of new rows */
    table_set->allow_creation = 1;

    /***************************************************
     * Adding indexes
     */
    DEBUGMSGTL(("initialize_table_pstIFMS1000ParamsV32TotalNumTable",
                "adding indexes to table pstIFMS1000ParamsV32TotalNumTable\n"));
    netsnmp_table_set_add_indexes(table_set,
                           ASN_INTEGER,  /* index: v32TPortNum */
                           0);

    DEBUGMSGTL(("initialize_table_pstIFMS1000ParamsV32TotalNumTable",
                "adding column types to table pstIFMS1000ParamsV32TotalNumTable\n"));		 
    netsnmp_table_set_multi_add_default_row(table_set,
                                            COLUMN_V32TPORTNUM, ASN_INTEGER, 0,
                                            NULL, 0,
                                            COLUMN_V32PORTTOTALNUM, ASN_INTEGER, 0,
                                            NULL, 0,
                              0);
    
    /* registering the table with the master agent */
    /* note: if you don't need a subhandler to deal with any aspects
       of the request, change pstIFMS1000ParamsV32TotalNumTable_handler to "NULL" */
    netsnmp_register_table_data_set(netsnmp_create_handler_registration("pstIFMS1000ParamsV32TotalNumTable", pstIFMS1000ParamsV32TotalNumTable_handler,
                                                        pstIFMS1000ParamsV32TotalNumTable_oid,
                                                        OID_LENGTH(pstIFMS1000ParamsV32TotalNumTable_oid),
                                                        HANDLER_CAN_RWRITE),
                            table_set, NULL);
}
/** Initialize the pstIFMS1000ParamsV32NameTable table by defining its contents and how it's structured */
void
 QPSTProduct::initialize_table_pstIFMS1000ParamsV32NameTable(void)
{
    const oid pstIFMS1000ParamsV32NameTable_oid[] = {1,3,6,1,4,1,48391,3,5,15,2};
    netsnmp_table_data_set *table_set;

    /* create the table structure itself */
    table_set = netsnmp_create_table_data_set("pstIFMS1000ParamsV32NameTable");

    /* comment this out or delete if you don't support creation of new rows */
    table_set->allow_creation = 1;

    /***************************************************
     * Adding indexes
     */
    DEBUGMSGTL(("initialize_table_pstIFMS1000ParamsV32NameTable",
                "adding indexes to table pstIFMS1000ParamsV32NameTable\n"));
    netsnmp_table_set_add_indexes(table_set,
                           ASN_INTEGER,  /* index: v32PortNum */
                           ASN_INTEGER,  /* index: v32ParamNameNum */
                           0);

    DEBUGMSGTL(("initialize_table_pstIFMS1000ParamsV32NameTable",
                "adding column types to table pstIFMS1000ParamsV32NameTable\n"));		 
    netsnmp_table_set_multi_add_default_row(table_set,
                                            COLUMN_V32PORTNUM, ASN_INTEGER, 0,
                                            NULL, 0,
                                            COLUMN_V32PARAMNAMENUM, ASN_INTEGER, 0,
                                            NULL, 0,
                                            COLUMN_V32PARAMNAME, ASN_OCTET_STR, 0,
                                            NULL, 0,
                              0);
    
    /* registering the table with the master agent */
    /* note: if you don't need a subhandler to deal with any aspects
       of the request, change pstIFMS1000ParamsV32NameTable_handler to "NULL" */
    netsnmp_register_table_data_set(netsnmp_create_handler_registration("pstIFMS1000ParamsV32NameTable", pstIFMS1000ParamsV32NameTable_handler,
                                                        pstIFMS1000ParamsV32NameTable_oid,
                                                        OID_LENGTH(pstIFMS1000ParamsV32NameTable_oid),
                                                        HANDLER_CAN_RWRITE),
                            table_set, NULL);
}
/** Initialize the pstIFMS1000ParamsV32ValTable table by defining its contents and how it's structured */
void
 QPSTProduct::initialize_table_pstIFMS1000ParamsV32ValTable(void)
{
    const oid pstIFMS1000ParamsV32ValTable_oid[] = {1,3,6,1,4,1,48391,3,5,15,3};
    netsnmp_table_data_set *table_set;

    /* create the table structure itself */
    table_set = netsnmp_create_table_data_set("pstIFMS1000ParamsV32ValTable");

    /* comment this out or delete if you don't support creation of new rows */
    table_set->allow_creation = 1;

    /***************************************************
     * Adding indexes
     */
    DEBUGMSGTL(("initialize_table_pstIFMS1000ParamsV32ValTable",
                "adding indexes to table pstIFMS1000ParamsV32ValTable\n"));
    netsnmp_table_set_add_indexes(table_set,
                           ASN_INTEGER,  /* index: v32ValPortNum */
                           ASN_INTEGER,  /* index: v32ParamValNum */
                           0);

    DEBUGMSGTL(("initialize_table_pstIFMS1000ParamsV32ValTable",
                "adding column types to table pstIFMS1000ParamsV32ValTable\n"));		 
    netsnmp_table_set_multi_add_default_row(table_set,
                                            COLUMN_V32VALPORTNUM, ASN_INTEGER, 0,
                                            NULL, 0,
                                            COLUMN_V32PARAMVALNUM, ASN_INTEGER, 0,
                                            NULL, 0,
                                            COLUMN_V32PARAMVAL, ASN_UNSIGNED, 1,
                                            NULL, 0,
                              0);
    
    /* registering the table with the master agent */
    /* note: if you don't need a subhandler to deal with any aspects
       of the request, change pstIFMS1000ParamsV32ValTable_handler to "NULL" */
    netsnmp_register_table_data_set(netsnmp_create_handler_registration("pstIFMS1000ParamsV32ValTable", pstIFMS1000ParamsV32ValTable_handler,
                                                        pstIFMS1000ParamsV32ValTable_oid,
                                                        OID_LENGTH(pstIFMS1000ParamsV32ValTable_oid),
                                                        HANDLER_CAN_RWRITE),
                            table_set, NULL);
}
/** Initialize the pstIFMS1000ParamsS32TotalNumTable table by defining its contents and how it's structured */
void
 QPSTProduct::initialize_table_pstIFMS1000ParamsS32TotalNumTable(void)
{
    const oid pstIFMS1000ParamsS32TotalNumTable_oid[] = {1,3,6,1,4,1,48391,3,5,16,1};
    netsnmp_table_data_set *table_set;

    /* create the table structure itself */
    table_set = netsnmp_create_table_data_set("pstIFMS1000ParamsS32TotalNumTable");

    /* comment this out or delete if you don't support creation of new rows */
    table_set->allow_creation = 1;

    /***************************************************
     * Adding indexes
     */
    DEBUGMSGTL(("initialize_table_pstIFMS1000ParamsS32TotalNumTable",
                "adding indexes to table pstIFMS1000ParamsS32TotalNumTable\n"));
    netsnmp_table_set_add_indexes(table_set,
                           ASN_INTEGER,  /* index: s32TPortNum */
                           0);

    DEBUGMSGTL(("initialize_table_pstIFMS1000ParamsS32TotalNumTable",
                "adding column types to table pstIFMS1000ParamsS32TotalNumTable\n"));		 
    netsnmp_table_set_multi_add_default_row(table_set,
                                            COLUMN_S32TPORTNUM, ASN_INTEGER, 0,
                                            NULL, 0,
                                            COLUMN_S32PORTTOTALNUM, ASN_INTEGER, 0,
                                            NULL, 0,
                              0);
    
    /* registering the table with the master agent */
    /* note: if you don't need a subhandler to deal with any aspects
       of the request, change pstIFMS1000ParamsS32TotalNumTable_handler to "NULL" */
    netsnmp_register_table_data_set(netsnmp_create_handler_registration("pstIFMS1000ParamsS32TotalNumTable", pstIFMS1000ParamsS32TotalNumTable_handler,
                                                        pstIFMS1000ParamsS32TotalNumTable_oid,
                                                        OID_LENGTH(pstIFMS1000ParamsS32TotalNumTable_oid),
                                                        HANDLER_CAN_RWRITE),
                            table_set, NULL);
}
/** Initialize the pstIFMS1000ParamsS32NameTable table by defining its contents and how it's structured */
void
 QPSTProduct::initialize_table_pstIFMS1000ParamsS32NameTable(void)
{
    const oid pstIFMS1000ParamsS32NameTable_oid[] = {1,3,6,1,4,1,48391,3,5,16,2};
    netsnmp_table_data_set *table_set;

    /* create the table structure itself */
    table_set = netsnmp_create_table_data_set("pstIFMS1000ParamsS32NameTable");

    /* comment this out or delete if you don't support creation of new rows */
    table_set->allow_creation = 1;

    /***************************************************
     * Adding indexes
     */
    DEBUGMSGTL(("initialize_table_pstIFMS1000ParamsS32NameTable",
                "adding indexes to table pstIFMS1000ParamsS32NameTable\n"));
    netsnmp_table_set_add_indexes(table_set,
                           ASN_INTEGER,  /* index: s32PortNum */
                           ASN_INTEGER,  /* index: s32ParamNameNum */
                           0);

    DEBUGMSGTL(("initialize_table_pstIFMS1000ParamsS32NameTable",
                "adding column types to table pstIFMS1000ParamsS32NameTable\n"));		 
    netsnmp_table_set_multi_add_default_row(table_set,
                                            COLUMN_S32PORTNUM, ASN_INTEGER, 0,
                                            NULL, 0,
                                            COLUMN_S32PARAMNAMENUM, ASN_INTEGER, 0,
                                            NULL, 0,
                                            COLUMN_S32PARAMNAMEVAL, ASN_OCTET_STR, 0,
                                            NULL, 0,
                              0);
    
    /* registering the table with the master agent */
    /* note: if you don't need a subhandler to deal with any aspects
       of the request, change pstIFMS1000ParamsS32NameTable_handler to "NULL" */
    netsnmp_register_table_data_set(netsnmp_create_handler_registration("pstIFMS1000ParamsS32NameTable", pstIFMS1000ParamsS32NameTable_handler,
                                                        pstIFMS1000ParamsS32NameTable_oid,
                                                        OID_LENGTH(pstIFMS1000ParamsS32NameTable_oid),
                                                        HANDLER_CAN_RWRITE),
                            table_set, NULL);
}
/** Initialize the pstIFMS1000ParamsS32ValTable table by defining its contents and how it's structured */
void
 QPSTProduct::initialize_table_pstIFMS1000ParamsS32ValTable(void)
{
    const oid pstIFMS1000ParamsS32ValTable_oid[] = {1,3,6,1,4,1,48391,3,5,16,3};
    netsnmp_table_data_set *table_set;

    /* create the table structure itself */
    table_set = netsnmp_create_table_data_set("pstIFMS1000ParamsS32ValTable");

    /* comment this out or delete if you don't support creation of new rows */
    table_set->allow_creation = 1;

    /***************************************************
     * Adding indexes
     */
    DEBUGMSGTL(("initialize_table_pstIFMS1000ParamsS32ValTable",
                "adding indexes to table pstIFMS1000ParamsS32ValTable\n"));
    netsnmp_table_set_add_indexes(table_set,
                           ASN_INTEGER,  /* index: s32ValPortNum */
                           ASN_INTEGER,  /* index: s32ParamValNum */
                           0);

    DEBUGMSGTL(("initialize_table_pstIFMS1000ParamsS32ValTable",
                "adding column types to table pstIFMS1000ParamsS32ValTable\n"));		 
    netsnmp_table_set_multi_add_default_row(table_set,
                                            COLUMN_S32VALPORTNUM, ASN_INTEGER, 0,
                                            NULL, 0,
                                            COLUMN_S32PARAMVALNUM, ASN_INTEGER, 0,
                                            NULL, 0,
                                            COLUMN_S32PARAMVAL, ASN_OCTET_STR, 1,
                                            NULL, 0,
                              0);
    
    /* registering the table with the master agent */
    /* note: if you don't need a subhandler to deal with any aspects
       of the request, change pstIFMS1000ParamsS32ValTable_handler to "NULL" */
    netsnmp_register_table_data_set(netsnmp_create_handler_registration("pstIFMS1000ParamsS32ValTable", pstIFMS1000ParamsS32ValTable_handler,
                                                        pstIFMS1000ParamsS32ValTable_oid,
                                                        OID_LENGTH(pstIFMS1000ParamsS32ValTable_oid),
                                                        HANDLER_CAN_RWRITE),
                            table_set, NULL);
}

/** handles requests for the pstIFMS1000PortInfoTable table, if anything else needs to be done */
int
 QPSTProduct::pstIFMS1000PortInfoTable_handler(
    netsnmp_mib_handler               *handler,
    netsnmp_handler_registration      *reginfo,
    netsnmp_agent_request_info        *reqinfo,
    netsnmp_request_info              *requests) {
    /* perform anything here that you need to do.  The requests have
       already been processed by the master table_dataset handler, but
       this gives you chance to act on the request in some other way
       if need be. */
    return SNMP_ERR_NOERROR;
}

/** handles requests for the pstIFMS1000MeasureTable table, if anything else needs to be done */
int
 QPSTProduct::pstIFMS1000MeasureTable_handler(
    netsnmp_mib_handler               *handler,
    netsnmp_handler_registration      *reginfo,
    netsnmp_agent_request_info        *reqinfo,
    netsnmp_request_info              *requests) {
    /* perform anything here that you need to do.  The requests have
       already been processed by the master table_dataset handler, but
       this gives you chance to act on the request in some other way
       if need be. */
    return SNMP_ERR_NOERROR;
}

/** handles requests for the pstIFMS1000FingerTable table, if anything else needs to be done */
int
 QPSTProduct::pstIFMS1000FingerTable_handler(
    netsnmp_mib_handler               *handler,
    netsnmp_handler_registration      *reginfo,
    netsnmp_agent_request_info        *reqinfo,
    netsnmp_request_info              *requests) {
    /* perform anything here that you need to do.  The requests have
       already been processed by the master table_dataset handler, but
       this gives you chance to act on the request in some other way
       if need be. */
    return SNMP_ERR_NOERROR;
}

/** handles requests for the pstIFMS1000DiffTotalTable table, if anything else needs to be done */
int
 QPSTProduct::pstIFMS1000DiffTotalTable_handler(
    netsnmp_mib_handler               *handler,
    netsnmp_handler_registration      *reginfo,
    netsnmp_agent_request_info        *reqinfo,
    netsnmp_request_info              *requests) {
    /* perform anything here that you need to do.  The requests have
       already been processed by the master table_dataset handler, but
       this gives you chance to act on the request in some other way
       if need be. */
    return SNMP_ERR_NOERROR;
}

/** handles requests for the pstIFMS1000DiffInfoTable table, if anything else needs to be done */
int
 QPSTProduct::pstIFMS1000DiffInfoTable_handler(
    netsnmp_mib_handler               *handler,
    netsnmp_handler_registration      *reginfo,
    netsnmp_agent_request_info        *reqinfo,
    netsnmp_request_info              *requests) {
    /* perform anything here that you need to do.  The requests have
       already been processed by the master table_dataset handler, but
       this gives you chance to act on the request in some other way
       if need be. */
    return SNMP_ERR_NOERROR;
}

/** handles requests for the pstIFMS1000PortLedTable table, if anything else needs to be done */
int
 QPSTProduct::pstIFMS1000PortLedTable_handler(
    netsnmp_mib_handler               *handler,
    netsnmp_handler_registration      *reginfo,
    netsnmp_agent_request_info        *reqinfo,
    netsnmp_request_info              *requests) {
    /* perform anything here that you need to do.  The requests have
       already been processed by the master table_dataset handler, but
       this gives you chance to act on the request in some other way
       if need be. */
    return SNMP_ERR_NOERROR;
}

/** handles requests for the pstIFMS1000DiagnoseTable table, if anything else needs to be done */
int
 QPSTProduct::pstIFMS1000DiagnoseTable_handler(
    netsnmp_mib_handler               *handler,
    netsnmp_handler_registration      *reginfo,
    netsnmp_agent_request_info        *reqinfo,
    netsnmp_request_info              *requests) {
    /* perform anything here that you need to do.  The requests have
       already been processed by the master table_dataset handler, but
       this gives you chance to act on the request in some other way
       if need be. */
    return SNMP_ERR_NOERROR;
}

/** handles requests for the pstIFMS1000DebugRegTable table, if anything else needs to be done */
int
 QPSTProduct::pstIFMS1000DebugRegTable_handler(
    netsnmp_mib_handler               *handler,
    netsnmp_handler_registration      *reginfo,
    netsnmp_agent_request_info        *reqinfo,
    netsnmp_request_info              *requests) {
    /* perform anything here that you need to do.  The requests have
       already been processed by the master table_dataset handler, but
       this gives you chance to act on the request in some other way
       if need be. */
    return SNMP_ERR_NOERROR;
}

/** handles requests for the pstIFMS1000DebugDACTable table, if anything else needs to be done */
int
 QPSTProduct::pstIFMS1000DebugDACTable_handler(
    netsnmp_mib_handler               *handler,
    netsnmp_handler_registration      *reginfo,
    netsnmp_agent_request_info        *reqinfo,
    netsnmp_request_info              *requests) {
    /* perform anything here that you need to do.  The requests have
       already been processed by the master table_dataset handler, but
       this gives you chance to act on the request in some other way
       if need be. */
    return SNMP_ERR_NOERROR;
}

/** handles requests for the pstIFMS1000DebugE2promTable table, if anything else needs to be done */
int
 QPSTProduct::pstIFMS1000DebugE2promTable_handler(
    netsnmp_mib_handler               *handler,
    netsnmp_handler_registration      *reginfo,
    netsnmp_agent_request_info        *reqinfo,
    netsnmp_request_info              *requests) {
    /* perform anything here that you need to do.  The requests have
       already been processed by the master table_dataset handler, but
       this gives you chance to act on the request in some other way
       if need be. */
    return SNMP_ERR_NOERROR;
}

/** handles requests for the pstIFMS1000ExtendAlarmTable table, if anything else needs to be done */
int
 QPSTProduct::pstIFMS1000ExtendAlarmTable_handler(
    netsnmp_mib_handler               *handler,
    netsnmp_handler_registration      *reginfo,
    netsnmp_agent_request_info        *reqinfo,
    netsnmp_request_info              *requests) {
    /* perform anything here that you need to do.  The requests have
       already been processed by the master table_dataset handler, but
       this gives you chance to act on the request in some other way
       if need be. */
    return SNMP_ERR_NOERROR;
}

/** handles requests for the pstIFMS1000ExpertExtendTable table, if anything else needs to be done */
int
 QPSTProduct::pstIFMS1000ExpertExtendTable_handler(
    netsnmp_mib_handler               *handler,
    netsnmp_handler_registration      *reginfo,
    netsnmp_agent_request_info        *reqinfo,
    netsnmp_request_info              *requests) {
    /* perform anything here that you need to do.  The requests have
       already been processed by the master table_dataset handler, but
       this gives you chance to act on the request in some other way
       if need be. */
    return SNMP_ERR_NOERROR;
}

/** handles requests for the pstIFMS1000PonConfTable table, if anything else needs to be done */
int
 QPSTProduct::pstIFMS1000PonConfTable_handler(
    netsnmp_mib_handler               *handler,
    netsnmp_handler_registration      *reginfo,
    netsnmp_agent_request_info        *reqinfo,
    netsnmp_request_info              *requests) {
    /* perform anything here that you need to do.  The requests have
       already been processed by the master table_dataset handler, but
       this gives you chance to act on the request in some other way
       if need be. */
    return SNMP_ERR_NOERROR;
}

/** handles requests for the pstIFMS1000ParamsV32TotalNumTable table, if anything else needs to be done */
int
 QPSTProduct::pstIFMS1000ParamsV32TotalNumTable_handler(
    netsnmp_mib_handler               *handler,
    netsnmp_handler_registration      *reginfo,
    netsnmp_agent_request_info        *reqinfo,
    netsnmp_request_info              *requests) {
    /* perform anything here that you need to do.  The requests have
       already been processed by the master table_dataset handler, but
       this gives you chance to act on the request in some other way
       if need be. */
    return SNMP_ERR_NOERROR;
}

/** handles requests for the pstIFMS1000ParamsV32NameTable table, if anything else needs to be done */
int
 QPSTProduct::pstIFMS1000ParamsV32NameTable_handler(
    netsnmp_mib_handler               *handler,
    netsnmp_handler_registration      *reginfo,
    netsnmp_agent_request_info        *reqinfo,
    netsnmp_request_info              *requests) {
    /* perform anything here that you need to do.  The requests have
       already been processed by the master table_dataset handler, but
       this gives you chance to act on the request in some other way
       if need be. */
    return SNMP_ERR_NOERROR;
}

/** handles requests for the pstIFMS1000ParamsV32ValTable table, if anything else needs to be done */
int
 QPSTProduct::pstIFMS1000ParamsV32ValTable_handler(
    netsnmp_mib_handler               *handler,
    netsnmp_handler_registration      *reginfo,
    netsnmp_agent_request_info        *reqinfo,
    netsnmp_request_info              *requests) {
    /* perform anything here that you need to do.  The requests have
       already been processed by the master table_dataset handler, but
       this gives you chance to act on the request in some other way
       if need be. */
    return SNMP_ERR_NOERROR;
}

/** handles requests for the pstIFMS1000ParamsS32TotalNumTable table, if anything else needs to be done */
int
 QPSTProduct::pstIFMS1000ParamsS32TotalNumTable_handler(
    netsnmp_mib_handler               *handler,
    netsnmp_handler_registration      *reginfo,
    netsnmp_agent_request_info        *reqinfo,
    netsnmp_request_info              *requests) {
    /* perform anything here that you need to do.  The requests have
       already been processed by the master table_dataset handler, but
       this gives you chance to act on the request in some other way
       if need be. */
    return SNMP_ERR_NOERROR;
}

/** handles requests for the pstIFMS1000ParamsS32NameTable table, if anything else needs to be done */
int
 QPSTProduct::pstIFMS1000ParamsS32NameTable_handler(
    netsnmp_mib_handler               *handler,
    netsnmp_handler_registration      *reginfo,
    netsnmp_agent_request_info        *reqinfo,
    netsnmp_request_info              *requests) {
    /* perform anything here that you need to do.  The requests have
       already been processed by the master table_dataset handler, but
       this gives you chance to act on the request in some other way
       if need be. */
    return SNMP_ERR_NOERROR;
}

/** handles requests for the pstIFMS1000ParamsS32ValTable table, if anything else needs to be done */
int
 QPSTProduct::pstIFMS1000ParamsS32ValTable_handler(
    netsnmp_mib_handler               *handler,
    netsnmp_handler_registration      *reginfo,
    netsnmp_agent_request_info        *reqinfo,
    netsnmp_request_info              *requests) {
    /* perform anything here that you need to do.  The requests have
       already been processed by the master table_dataset handler, but
       this gives you chance to act on the request in some other way
       if need be. */
    return SNMP_ERR_NOERROR;
}

// Trap
int
QPSTProduct::send_pstIFMS1000MeasureEvent_trap( void )
{
    netsnmp_variable_list  *var_list = NULL;
    const oid pstIFMS1000MeasureEvent_oid[] = { 1,3,6,1,4,1,48391,3,5,5,1 };
    const oid pstIFMS1000MeasureStatus_oid[] = { 1,3,6,1,4,1,48391,3,5,2,1,6, /* insert index here */ };

    /*
     * Set the snmpTrapOid.0 value
     */
    snmp_varlist_add_variable(&var_list,
        snmptrap_oid, snmptrap_oid_len,
        ASN_OBJECT_ID,
        pstIFMS1000MeasureEvent_oid, sizeof(pstIFMS1000MeasureEvent_oid));

    /*
     * Add any objects from the trap definition
     */
    snmp_varlist_add_variable(&var_list,
        pstIFMS1000MeasureStatus_oid, OID_LENGTH(pstIFMS1000MeasureStatus_oid),
        ASN_INTEGER,
        /* Set an appropriate value for pstIFMS1000MeasureStatus */
        NULL, 0);

    /*
     * Add any extra (optional) objects here
     */

    /*
     * Send the trap to the list of configured destinations
     *  and clean up
     */
    send_v2trap( var_list );
    snmp_free_varbind( var_list );

    return SNMP_ERR_NOERROR;
}
