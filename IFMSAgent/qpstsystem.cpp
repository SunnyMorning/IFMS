#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <QObject>
#include <QMutex>
#include <QMutexLocker>

#include "qpstsystem.h"
#include "qagentapp.h"
#include "qpst.h"

static QObject       *system_agent;

QPSTSystem::QPSTSystem(QObject *parent) : QObject(parent)
{
    system_agent = parent;
    init_pstSystemData();
}

void QPSTSystem::init_pstSystemData(){
    m_pstSystem.init_pstData();
}

void QPSTSystem::init_pstSystem()
{
    const oid devName_oid[] = { 1,3,6,1,4,1,48391,2,1,1,1 };
    const oid devIpAddr_oid[] = { 1,3,6,1,4,1,48391,2,1,1,2 };
    const oid devGateway_oid[] = { 1,3,6,1,4,1,48391,2,1,1,3 };
    const oid devNetMask_oid[] = { 1,3,6,1,4,1,48391,2,1,1,4 };
    const oid saveCurrentConfiguration_oid[] = { 1,3,6,1,4,1,48391,2,1,1,5 };
    const oid reset2Factory_oid[] = { 1,3,6,1,4,1,48391,2,1,1,6 };
    const oid reboot_oid[] = { 1,3,6,1,4,1,48391,2,1,1,7 };
    const oid pstHwVer_oid[] = { 1,3,6,1,4,1,48391,2,1,2,1 };
    const oid pstSwVer_oid[] = { 1,3,6,1,4,1,48391,2,1,2,2 };
    const oid pstFwVer_oid[] = { 1,3,6,1,4,1,48391,2,1,2,3 };
    const oid pstModel_oid[] = { 1,3,6,1,4,1,48391,2,1,2,4 };
    const oid pstSn_oid[] = { 1,3,6,1,4,1,48391,2,1,2,5 };
    const oid devMacAddress_oid[] = { 1,3,6,1,4,1,48391,2,1,2,6 };
    const oid pstSystemTrapFuncEn_oid[] = { 1,3,6,1,4,1,48391,2,1,3,1 };
    const oid pstSystemFanTotalNum_oid[] = { 1,3,6,1,4,1,48391,2,1,4,1 };
    const oid pstSystemPowerTotalNum_oid[] = { 1,3,6,1,4,1,48391,2,1,4,2 };
    const oid pstSystemTemperature_oid[] = { 1,3,6,1,4,1,48391,2,1,4,5 };
    const oid pstSystemFtpSrvIp_oid[] = { 1,3,6,1,4,1,48391,2,1,5,1 };
    const oid pstSystemFtpUserName_oid[] = { 1,3,6,1,4,1,48391,2,1,5,2 };
    const oid pstSystemFtpUserPwd_oid[] = { 1,3,6,1,4,1,48391,2,1,5,3 };
    const oid pstSystemFtpFileName_oid[] = { 1,3,6,1,4,1,48391,2,1,5,4 };
    const oid pstSystemUpgFileType_oid[] = { 1,3,6,1,4,1,48391,2,1,5,5 };
    const oid pstSystemUpgDstSlot_oid[] = { 1,3,6,1,4,1,48391,2,1,5,6 };
    const oid pstSystemUpgAction_oid[] = { 1,3,6,1,4,1,48391,2,1,5,7 };
    const oid pstSystemUpgStatus_oid[] = { 1,3,6,1,4,1,48391,2,1,5,8 };
    const oid pstSystemUpgResultInfo_oid[] = { 1,3,6,1,4,1,48391,2,1,5,9 };
    const oid pstSystemProductType_oid[] = { 1,3,6,1,4,1,48391,2,1,6,1 };

  DEBUGMSGTL(("pstSystem", "Initializing\n"));

    netsnmp_register_scalar(
        netsnmp_create_handler_registration("devName", handle_devName,
                               devName_oid, OID_LENGTH(devName_oid),
                               HANDLER_CAN_RWRITE
        ));
    netsnmp_register_scalar(
        netsnmp_create_handler_registration("devIpAddr", handle_devIpAddr,
                               devIpAddr_oid, OID_LENGTH(devIpAddr_oid),
                               HANDLER_CAN_RWRITE
        ));
    netsnmp_register_scalar(
        netsnmp_create_handler_registration("devGateway", handle_devGateway,
                               devGateway_oid, OID_LENGTH(devGateway_oid),
                               HANDLER_CAN_RWRITE
        ));
    netsnmp_register_scalar(
        netsnmp_create_handler_registration("devNetMask", handle_devNetMask,
                               devNetMask_oid, OID_LENGTH(devNetMask_oid),
                               HANDLER_CAN_RWRITE
        ));
    netsnmp_register_scalar(
        netsnmp_create_handler_registration("saveCurrentConfiguration", handle_saveCurrentConfiguration,
                               saveCurrentConfiguration_oid, OID_LENGTH(saveCurrentConfiguration_oid),
                               HANDLER_CAN_RWRITE
        ));
    netsnmp_register_scalar(
        netsnmp_create_handler_registration("reset2Factory", handle_reset2Factory,
                               reset2Factory_oid, OID_LENGTH(reset2Factory_oid),
                               HANDLER_CAN_RWRITE
        ));
    netsnmp_register_scalar(
        netsnmp_create_handler_registration("reboot", handle_reboot,
                               reboot_oid, OID_LENGTH(reboot_oid),
                               HANDLER_CAN_RWRITE
        ));
    netsnmp_register_scalar(
        netsnmp_create_handler_registration("pstHwVer", handle_pstHwVer,
                               pstHwVer_oid, OID_LENGTH(pstHwVer_oid),
                               HANDLER_CAN_RONLY
        ));
    netsnmp_register_scalar(
        netsnmp_create_handler_registration("pstSwVer", handle_pstSwVer,
                               pstSwVer_oid, OID_LENGTH(pstSwVer_oid),
                               HANDLER_CAN_RONLY
        ));
    netsnmp_register_scalar(
        netsnmp_create_handler_registration("pstFwVer", handle_pstFwVer,
                               pstFwVer_oid, OID_LENGTH(pstFwVer_oid),
                               HANDLER_CAN_RONLY
        ));
    netsnmp_register_scalar(
        netsnmp_create_handler_registration("pstModel", handle_pstModel,
                               pstModel_oid, OID_LENGTH(pstModel_oid),
                               HANDLER_CAN_RONLY
        ));
    netsnmp_register_scalar(
        netsnmp_create_handler_registration("pstSn", handle_pstSn,
                               pstSn_oid, OID_LENGTH(pstSn_oid),
                               HANDLER_CAN_RONLY
        ));
    netsnmp_register_scalar(
        netsnmp_create_handler_registration("devMacAddress", handle_devMacAddress,
                               devMacAddress_oid, OID_LENGTH(devMacAddress_oid),
                               HANDLER_CAN_RONLY
        ));
    netsnmp_register_scalar(
        netsnmp_create_handler_registration("pstSystemTrapFuncEn", handle_pstSystemTrapFuncEn,
                               pstSystemTrapFuncEn_oid, OID_LENGTH(pstSystemTrapFuncEn_oid),
                               HANDLER_CAN_RWRITE
        ));
    netsnmp_register_scalar(
        netsnmp_create_handler_registration("pstSystemFanTotalNum", handle_pstSystemFanTotalNum,
                               pstSystemFanTotalNum_oid, OID_LENGTH(pstSystemFanTotalNum_oid),
                               HANDLER_CAN_RONLY
        ));
    netsnmp_register_scalar(
        netsnmp_create_handler_registration("pstSystemPowerTotalNum", handle_pstSystemPowerTotalNum,
                               pstSystemPowerTotalNum_oid, OID_LENGTH(pstSystemPowerTotalNum_oid),
                               HANDLER_CAN_RONLY
        ));
    netsnmp_register_scalar(
        netsnmp_create_handler_registration("pstSystemTemperature", handle_pstSystemTemperature,
                               pstSystemTemperature_oid, OID_LENGTH(pstSystemTemperature_oid),
                               HANDLER_CAN_RONLY
        ));
    netsnmp_register_scalar(
        netsnmp_create_handler_registration("pstSystemFtpSrvIp", handle_pstSystemFtpSrvIp,
                               pstSystemFtpSrvIp_oid, OID_LENGTH(pstSystemFtpSrvIp_oid),
                               HANDLER_CAN_RWRITE
        ));
    netsnmp_register_scalar(
        netsnmp_create_handler_registration("pstSystemFtpUserName", handle_pstSystemFtpUserName,
                               pstSystemFtpUserName_oid, OID_LENGTH(pstSystemFtpUserName_oid),
                               HANDLER_CAN_RWRITE
        ));
    netsnmp_register_scalar(
        netsnmp_create_handler_registration("pstSystemFtpUserPwd", handle_pstSystemFtpUserPwd,
                               pstSystemFtpUserPwd_oid, OID_LENGTH(pstSystemFtpUserPwd_oid),
                               HANDLER_CAN_RWRITE
        ));
    netsnmp_register_scalar(
        netsnmp_create_handler_registration("pstSystemFtpFileName", handle_pstSystemFtpFileName,
                               pstSystemFtpFileName_oid, OID_LENGTH(pstSystemFtpFileName_oid),
                               HANDLER_CAN_RWRITE
        ));
    netsnmp_register_scalar(
        netsnmp_create_handler_registration("pstSystemUpgFileType", handle_pstSystemUpgFileType,
                               pstSystemUpgFileType_oid, OID_LENGTH(pstSystemUpgFileType_oid),
                               HANDLER_CAN_RWRITE
        ));
    netsnmp_register_scalar(
        netsnmp_create_handler_registration("pstSystemUpgDstSlot", handle_pstSystemUpgDstSlot,
                               pstSystemUpgDstSlot_oid, OID_LENGTH(pstSystemUpgDstSlot_oid),
                               HANDLER_CAN_RWRITE
        ));
    netsnmp_register_scalar(
        netsnmp_create_handler_registration("pstSystemUpgAction", handle_pstSystemUpgAction,
                               pstSystemUpgAction_oid, OID_LENGTH(pstSystemUpgAction_oid),
                               HANDLER_CAN_RWRITE
        ));
    netsnmp_register_scalar(
        netsnmp_create_handler_registration("pstSystemUpgStatus", handle_pstSystemUpgStatus,
                               pstSystemUpgStatus_oid, OID_LENGTH(pstSystemUpgStatus_oid),
                               HANDLER_CAN_RONLY
        ));
    netsnmp_register_scalar(
        netsnmp_create_handler_registration("pstSystemUpgResultInfo", handle_pstSystemUpgResultInfo,
                               pstSystemUpgResultInfo_oid, OID_LENGTH(pstSystemUpgResultInfo_oid),
                               HANDLER_CAN_RONLY
        ));
    netsnmp_register_scalar(
        netsnmp_create_handler_registration("pstSystemProductType", handle_pstSystemProductType,
                               pstSystemProductType_oid, OID_LENGTH(pstSystemProductType_oid),
                               HANDLER_CAN_RONLY
        ));
        

  /* here we initialize all the tables we're planning on supporting */
    initialize_table_pstSystemTrapTargetTable();
    initialize_table_pstSystemFanTable();
    initialize_table_pstSystemPowerTable();
}


int
 QPSTSystem::handle_devName(netsnmp_mib_handler *handler,
                          netsnmp_handler_registration *reginfo,
                          netsnmp_agent_request_info   *reqinfo,
                          netsnmp_request_info         *requests)
{
    int ret;
    /* We are never called for a GETNEXT if it's registered as a
       "instance", as it's "magically" handled for us.  */

    /* a instance handler also only hands us one request at a time, so
       we don't need to loop over a list of requests; we'll only get one. */

    char *devName = "IFMS1000";
    
    switch(reqinfo->mode) {

        case MODE_GET:
            snmp_set_var_typed_value(requests->requestvb, ASN_OCTET_STR,
                                     devName/* XXX: a pointer to the scalar's data */,
                                     strlen(devName)/* XXX: the length of the data in bytes */);
            break;

        /*
         * SET REQUEST
         *
         * multiple states in the transaction.  See:
         * http://www.net-snmp.org/tutorial-5/toolkit/mib_module/set-actions.jpg
         */
        case MODE_SET_RESERVE1:
                /* or you could use netsnmp_check_vb_type_and_size instead */
            ret = netsnmp_check_vb_type(requests->requestvb, ASN_OCTET_STR);
            if ( ret != SNMP_ERR_NOERROR ) {
                netsnmp_set_request_error(reqinfo, requests, ret );
            }
            break;

//        case MODE_SET_RESERVE2:
//            /* XXX malloc "undo" storage buffer */
//            if (/* XXX if malloc, or whatever, failed: */) {
//                netsnmp_set_request_error(reqinfo, requests, SNMP_ERR_RESOURCEUNAVAILABLE);
//            }
//            break;

//        case MODE_SET_FREE:
//            /* XXX: free resources allocated in RESERVE1 and/or
//               RESERVE2.  Something failed somewhere, and the states
//               below won't be called. */
//            break;

//        case MODE_SET_ACTION:
//            /* XXX: perform the value change here */
//            if (/* XXX: error? */) {
//                netsnmp_set_request_error(reqinfo, requests, /* some error */);
//            }
//            break;

//        case MODE_SET_COMMIT:
//            /* XXX: delete temporary storage */
//            if (/* XXX: error? */) {
//                /* try _really_really_ hard to never get to this point */
//                netsnmp_set_request_error(reqinfo, requests, SNMP_ERR_COMMITFAILED);
//            }
//            break;

//        case MODE_SET_UNDO:
//            /* XXX: UNDO and return to previous value for the object */
//            if (/* XXX: error? */) {
//                /* try _really_really_ hard to never get to this point */
//                netsnmp_set_request_error(reqinfo, requests, SNMP_ERR_UNDOFAILED);
//            }
//            break;

        default:
            /* we should never get here, so this is a really bad error */
            snmp_log(LOG_ERR, "unknown mode (%d) in handle_devName\n", reqinfo->mode );
            return SNMP_ERR_GENERR;
    }

    return SNMP_ERR_NOERROR;
}
int
 QPSTSystem::handle_devIpAddr(netsnmp_mib_handler *handler,
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

    inet_pton(AF_INET, "192.168.1.100", &(sa.sin_addr));

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

//        case MODE_SET_RESERVE2:
//            /* XXX malloc "undo" storage buffer */
//            if (/* XXX if malloc, or whatever, failed: */) {
//                netsnmp_set_request_error(reqinfo, requests, SNMP_ERR_RESOURCEUNAVAILABLE);
//            }
//            break;

//        case MODE_SET_FREE:
//            /* XXX: free resources allocated in RESERVE1 and/or
//               RESERVE2.  Something failed somewhere, and the states
//               below won't be called. */
//            break;

//        case MODE_SET_ACTION:
//            /* XXX: perform the value change here */
//            if (/* XXX: error? */) {
//                netsnmp_set_request_error(reqinfo, requests, /* some error */);
//            }
//            break;

//        case MODE_SET_COMMIT:
//            /* XXX: delete temporary storage */
//            if (/* XXX: error? */) {
//                /* try _really_really_ hard to never get to this point */
//                netsnmp_set_request_error(reqinfo, requests, SNMP_ERR_COMMITFAILED);
//            }
//            break;

//        case MODE_SET_UNDO:
//            /* XXX: UNDO and return to previous value for the object */
//            if (/* XXX: error? */) {
//                /* try _really_really_ hard to never get to this point */
//                netsnmp_set_request_error(reqinfo, requests, SNMP_ERR_UNDOFAILED);
//            }
//            break;

        default:
            /* we should never get here, so this is a really bad error */
            snmp_log(LOG_ERR, "unknown mode (%d) in handle_devIpAddr\n", reqinfo->mode );
            return SNMP_ERR_GENERR;
    }

    return SNMP_ERR_NOERROR;
}
int
 QPSTSystem::handle_devGateway(netsnmp_mib_handler *handler,
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

//        case MODE_SET_RESERVE2:
//            /* XXX malloc "undo" storage buffer */
//            if (/* XXX if malloc, or whatever, failed: */) {
//                netsnmp_set_request_error(reqinfo, requests, SNMP_ERR_RESOURCEUNAVAILABLE);
//            }
//            break;

//        case MODE_SET_FREE:
//            /* XXX: free resources allocated in RESERVE1 and/or
//               RESERVE2.  Something failed somewhere, and the states
//               below won't be called. */
//            break;

//        case MODE_SET_ACTION:
//            /* XXX: perform the value change here */
//            if (/* XXX: error? */) {
//                netsnmp_set_request_error(reqinfo, requests, /* some error */);
//            }
//            break;

//        case MODE_SET_COMMIT:
//            /* XXX: delete temporary storage */
//            if (/* XXX: error? */) {
//                /* try _really_really_ hard to never get to this point */
//                netsnmp_set_request_error(reqinfo, requests, SNMP_ERR_COMMITFAILED);
//            }
//            break;

//        case MODE_SET_UNDO:
//            /* XXX: UNDO and return to previous value for the object */
//            if (/* XXX: error? */) {
//                /* try _really_really_ hard to never get to this point */
//                netsnmp_set_request_error(reqinfo, requests, SNMP_ERR_UNDOFAILED);
//            }
//            break;

        default:
            /* we should never get here, so this is a really bad error */
            snmp_log(LOG_ERR, "unknown mode (%d) in handle_devGateway\n", reqinfo->mode );
            return SNMP_ERR_GENERR;
    }

    return SNMP_ERR_NOERROR;
}
int
 QPSTSystem::handle_devNetMask(netsnmp_mib_handler *handler,
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

    inet_pton(AF_INET, "255.255.255.1", &(sa.sin_addr));

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

//        case MODE_SET_RESERVE2:
//            /* XXX malloc "undo" storage buffer */
//            if (/* XXX if malloc, or whatever, failed: */) {
//                netsnmp_set_request_error(reqinfo, requests, SNMP_ERR_RESOURCEUNAVAILABLE);
//            }
//            break;

//        case MODE_SET_FREE:
//            /* XXX: free resources allocated in RESERVE1 and/or
//               RESERVE2.  Something failed somewhere, and the states
//               below won't be called. */
//            break;

//        case MODE_SET_ACTION:
//            /* XXX: perform the value change here */
//            if (/* XXX: error? */) {
//                netsnmp_set_request_error(reqinfo, requests, /* some error */);
//            }
//            break;

//        case MODE_SET_COMMIT:
//            /* XXX: delete temporary storage */
//            if (/* XXX: error? */) {
//                /* try _really_really_ hard to never get to this point */
//                netsnmp_set_request_error(reqinfo, requests, SNMP_ERR_COMMITFAILED);
//            }
//            break;

//        case MODE_SET_UNDO:
//            /* XXX: UNDO and return to previous value for the object */
//            if (/* XXX: error? */) {
//                /* try _really_really_ hard to never get to this point */
//                netsnmp_set_request_error(reqinfo, requests, SNMP_ERR_UNDOFAILED);
//            }
//            break;

        default:
            /* we should never get here, so this is a really bad error */
            snmp_log(LOG_ERR, "unknown mode (%d) in handle_devNetMask\n", reqinfo->mode );
            return SNMP_ERR_GENERR;
    }

    return SNMP_ERR_NOERROR;
}
int
 QPSTSystem::handle_saveCurrentConfiguration(netsnmp_mib_handler *handler,
                          netsnmp_handler_registration *reginfo,
                          netsnmp_agent_request_info   *reqinfo,
                          netsnmp_request_info         *requests)
{
    int ret;
    /* We are never called for a GETNEXT if it's registered as a
       "instance", as it's "magically" handled for us.  */

    /* a instance handler also only hands us one request at a time, so
       we don't need to loop over a list of requests; we'll only get one. */

    static long saveCurrent = 0;
    
    switch(reqinfo->mode) {

        case MODE_GET:
            snmp_set_var_typed_value(requests->requestvb, ASN_INTEGER,
                                     &saveCurrent/* XXX: a pointer to the scalar's data */,
                                     sizeof(saveCurrent)/* XXX: the length of the data in bytes */);
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

//        case MODE_SET_RESERVE2:
//            /* XXX malloc "undo" storage buffer */
//            if (/* XXX if malloc, or whatever, failed: */) {
//                netsnmp_set_request_error(reqinfo, requests, SNMP_ERR_RESOURCEUNAVAILABLE);
//            }
//            break;

//        case MODE_SET_FREE:
//            /* XXX: free resources allocated in RESERVE1 and/or
//               RESERVE2.  Something failed somewhere, and the states
//               below won't be called. */
//            break;

//        case MODE_SET_ACTION:
//            /* XXX: perform the value change here */
//            if (/* XXX: error? */) {
//                netsnmp_set_request_error(reqinfo, requests, /* some error */);
//            }
//            break;

//        case MODE_SET_COMMIT:
//            /* XXX: delete temporary storage */
//            if (/* XXX: error? */) {
//                /* try _really_really_ hard to never get to this point */
//                netsnmp_set_request_error(reqinfo, requests, SNMP_ERR_COMMITFAILED);
//            }
//            break;

//        case MODE_SET_UNDO:
//            /* XXX: UNDO and return to previous value for the object */
//            if (/* XXX: error? */) {
//                /* try _really_really_ hard to never get to this point */
//                netsnmp_set_request_error(reqinfo, requests, SNMP_ERR_UNDOFAILED);
//            }
//            break;

        default:
            /* we should never get here, so this is a really bad error */
            snmp_log(LOG_ERR, "unknown mode (%d) in handle_saveCurrentConfiguration\n", reqinfo->mode );
            return SNMP_ERR_GENERR;
    }

    return SNMP_ERR_NOERROR;
}
int
 QPSTSystem::handle_reset2Factory(netsnmp_mib_handler *handler,
                          netsnmp_handler_registration *reginfo,
                          netsnmp_agent_request_info   *reqinfo,
                          netsnmp_request_info         *requests)
{
    int ret;
    /* We are never called for a GETNEXT if it's registered as a
       "instance", as it's "magically" handled for us.  */

    /* a instance handler also only hands us one request at a time, so
       we don't need to loop over a list of requests; we'll only get one. */
     static long reset2Factory = 0;
    switch(reqinfo->mode) {

        case MODE_GET:
            snmp_set_var_typed_value(requests->requestvb, ASN_INTEGER,
                                     &reset2Factory/* XXX: a pointer to the scalar's data */,
                                     sizeof(reset2Factory)/* XXX: the length of the data in bytes */);
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

//        case MODE_SET_RESERVE2:
//            /* XXX malloc "undo" storage buffer */
//            if (/* XXX if malloc, or whatever, failed: */) {
//                netsnmp_set_request_error(reqinfo, requests, SNMP_ERR_RESOURCEUNAVAILABLE);
//            }
//            break;

//        case MODE_SET_FREE:
//            /* XXX: free resources allocated in RESERVE1 and/or
//               RESERVE2.  Something failed somewhere, and the states
//               below won't be called. */
//            break;

//        case MODE_SET_ACTION:
//            /* XXX: perform the value change here */
//            if (/* XXX: error? */) {
//                netsnmp_set_request_error(reqinfo, requests, /* some error */);
//            }
//            break;

//        case MODE_SET_COMMIT:
//            /* XXX: delete temporary storage */
//            if (/* XXX: error? */) {
//                /* try _really_really_ hard to never get to this point */
//                netsnmp_set_request_error(reqinfo, requests, SNMP_ERR_COMMITFAILED);
//            }
//            break;

//        case MODE_SET_UNDO:
//            /* XXX: UNDO and return to previous value for the object */
//            if (/* XXX: error? */) {
//                /* try _really_really_ hard to never get to this point */
//                netsnmp_set_request_error(reqinfo, requests, SNMP_ERR_UNDOFAILED);
//            }
//            break;

        default:
            /* we should never get here, so this is a really bad error */
            snmp_log(LOG_ERR, "unknown mode (%d) in handle_reset2Factory\n", reqinfo->mode );
            return SNMP_ERR_GENERR;
    }

    return SNMP_ERR_NOERROR;
}
int
 QPSTSystem::handle_reboot(netsnmp_mib_handler *handler,
                          netsnmp_handler_registration *reginfo,
                          netsnmp_agent_request_info   *reqinfo,
                          netsnmp_request_info         *requests)
{
    int ret;
    /* We are never called for a GETNEXT if it's registered as a
       "instance", as it's "magically" handled for us.  */

    /* a instance handler also only hands us one request at a time, so
       we don't need to loop over a list of requests; we'll only get one. */

    static long reboot;
    
    switch(reqinfo->mode) {

        case MODE_GET:
            snmp_set_var_typed_value(requests->requestvb, ASN_INTEGER,
                                     &reboot/* XXX: a pointer to the scalar's data */,
                                     sizeof(reboot)/* XXX: the length of the data in bytes */);
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

//        case MODE_SET_RESERVE2:
//            /* XXX malloc "undo" storage buffer */
//            if (/* XXX if malloc, or whatever, failed: */) {
//                netsnmp_set_request_error(reqinfo, requests, SNMP_ERR_RESOURCEUNAVAILABLE);
//            }
//            break;

//        case MODE_SET_FREE:
//            /* XXX: free resources allocated in RESERVE1 and/or
//               RESERVE2.  Something failed somewhere, and the states
//               below won't be called. */
//            break;

//        case MODE_SET_ACTION:
//            /* XXX: perform the value change here */
//            if (/* XXX: error? */) {
//                netsnmp_set_request_error(reqinfo, requests, /* some error */);
//            }
//            break;

//        case MODE_SET_COMMIT:
//            /* XXX: delete temporary storage */
//            if (/* XXX: error? */) {
//                /* try _really_really_ hard to never get to this point */
//                netsnmp_set_request_error(reqinfo, requests, SNMP_ERR_COMMITFAILED);
//            }
//            break;

//        case MODE_SET_UNDO:
//            /* XXX: UNDO and return to previous value for the object */
//            if (/* XXX: error? */) {
//                /* try _really_really_ hard to never get to this point */
//                netsnmp_set_request_error(reqinfo, requests, SNMP_ERR_UNDOFAILED);
//            }
//            break;

        default:
            /* we should never get here, so this is a really bad error */
            snmp_log(LOG_ERR, "unknown mode (%d) in handle_reboot\n", reqinfo->mode );
            return SNMP_ERR_GENERR;
    }

    return SNMP_ERR_NOERROR;
}
int
 QPSTSystem::handle_pstHwVer(netsnmp_mib_handler *handler,
                          netsnmp_handler_registration *reginfo,
                          netsnmp_agent_request_info   *reqinfo,
                          netsnmp_request_info         *requests)
{
    /* We are never called for a GETNEXT if it's registered as a
       "instance", as it's "magically" handled for us.  */

    /* a instance handler also only hands us one request at a time, so
       we don't need to loop over a list of requests; we'll only get one. */

    const char *pstHwVer = "1.0";
    
    switch(reqinfo->mode) {

        case MODE_GET:
            snmp_set_var_typed_value(requests->requestvb, ASN_OCTET_STR,
                                     pstHwVer/* XXX: a pointer to the scalar's data */,
                                     strlen(pstHwVer)/* XXX: the length of the data in bytes */);
            break;


        default:
            /* we should never get here, so this is a really bad error */
            snmp_log(LOG_ERR, "unknown mode (%d) in handle_pstHwVer\n", reqinfo->mode );
            return SNMP_ERR_GENERR;
    }

    return SNMP_ERR_NOERROR;
}
int
 QPSTSystem::handle_pstSwVer(netsnmp_mib_handler *handler,
                          netsnmp_handler_registration *reginfo,
                          netsnmp_agent_request_info   *reqinfo,
                          netsnmp_request_info         *requests)
{
    /* We are never called for a GETNEXT if it's registered as a
       "instance", as it's "magically" handled for us.  */

    /* a instance handler also only hands us one request at a time, so
       we don't need to loop over a list of requests; we'll only get one. */

    const char *pstSwVer = "1.0";
    
    switch(reqinfo->mode) {

        case MODE_GET:
            snmp_set_var_typed_value(requests->requestvb, ASN_OCTET_STR,
                                     pstSwVer/* XXX: a pointer to the scalar's data */,
                                     strlen(pstSwVer)/* XXX: the length of the data in bytes */);
            break;


        default:
            /* we should never get here, so this is a really bad error */
            snmp_log(LOG_ERR, "unknown mode (%d) in handle_pstSwVer\n", reqinfo->mode );
            return SNMP_ERR_GENERR;
    }

    return SNMP_ERR_NOERROR;
}
int
 QPSTSystem::handle_pstFwVer(netsnmp_mib_handler *handler,
                          netsnmp_handler_registration *reginfo,
                          netsnmp_agent_request_info   *reqinfo,
                          netsnmp_request_info         *requests)
{
    /* We are never called for a GETNEXT if it's registered as a
       "instance", as it's "magically" handled for us.  */

    /* a instance handler also only hands us one request at a time, so
       we don't need to loop over a list of requests; we'll only get one. */

    const char *pstFwVer = "1.0";
    
    switch(reqinfo->mode) {

        case MODE_GET:
            snmp_set_var_typed_value(requests->requestvb, ASN_OCTET_STR,
                                     pstFwVer/* XXX: a pointer to the scalar's data */,
                                     strlen(pstFwVer)/* XXX: the length of the data in bytes */);
            break;


        default:
            /* we should never get here, so this is a really bad error */
            snmp_log(LOG_ERR, "unknown mode (%d) in handle_pstFwVer\n", reqinfo->mode );
            return SNMP_ERR_GENERR;
    }

    return SNMP_ERR_NOERROR;
}
int
 QPSTSystem::handle_pstModel(netsnmp_mib_handler *handler,
                          netsnmp_handler_registration *reginfo,
                          netsnmp_agent_request_info   *reqinfo,
                          netsnmp_request_info         *requests)
{
    /* We are never called for a GETNEXT if it's registered as a
       "instance", as it's "magically" handled for us.  */

    /* a instance handler also only hands us one request at a time, so
       we don't need to loop over a list of requests; we'll only get one. */

    const char *pstModel = "IFMS1000";
    
    switch(reqinfo->mode) {

        case MODE_GET:
            snmp_set_var_typed_value(requests->requestvb, ASN_OCTET_STR,
                                     pstModel/* XXX: a pointer to the scalar's data */,
                                     strlen(pstModel)/* XXX: the length of the data in bytes */);
            break;


        default:
            /* we should never get here, so this is a really bad error */
            snmp_log(LOG_ERR, "unknown mode (%d) in handle_pstModel\n", reqinfo->mode );
            return SNMP_ERR_GENERR;
    }

    return SNMP_ERR_NOERROR;
}
int
 QPSTSystem::handle_pstSn(netsnmp_mib_handler *handler,
                          netsnmp_handler_registration *reginfo,
                          netsnmp_agent_request_info   *reqinfo,
                          netsnmp_request_info         *requests)
{
    /* We are never called for a GETNEXT if it's registered as a
       "instance", as it's "magically" handled for us.  */

    /* a instance handler also only hands us one request at a time, so
       we don't need to loop over a list of requests; we'll only get one. */

    const char *pstSn = "1234";
    
    switch(reqinfo->mode) {

        case MODE_GET:
            snmp_set_var_typed_value(requests->requestvb, ASN_OCTET_STR,
                                     pstSn/* XXX: a pointer to the scalar's data */,
                                     strlen(pstSn)/* XXX: the length of the data in bytes */);
            break;


        default:
            /* we should never get here, so this is a really bad error */
            snmp_log(LOG_ERR, "unknown mode (%d) in handle_pstSn\n", reqinfo->mode );
            return SNMP_ERR_GENERR;
    }

    return SNMP_ERR_NOERROR;
}
int
 QPSTSystem::handle_devMacAddress(netsnmp_mib_handler *handler,
                          netsnmp_handler_registration *reginfo,
                          netsnmp_agent_request_info   *reqinfo,
                          netsnmp_request_info         *requests)
{
    /* We are never called for a GETNEXT if it's registered as a
       "instance", as it's "magically" handled for us.  */

    /* a instance handler also only hands us one request at a time, so
       we don't need to loop over a list of requests; we'll only get one. */
    const char *devMacAddress = "aa:bb:cc:dd:ee:ff";

    switch(reqinfo->mode) {

        case MODE_GET:
            snmp_set_var_typed_value(requests->requestvb, ASN_OCTET_STR,
                                     devMacAddress/* XXX: a pointer to the scalar's data */,
                                     strlen(devMacAddress)/* XXX: the length of the data in bytes */);
            break;


        default:
            /* we should never get here, so this is a really bad error */
            snmp_log(LOG_ERR, "unknown mode (%d) in handle_devMacAddress\n", reqinfo->mode );
            return SNMP_ERR_GENERR;
    }

    return SNMP_ERR_NOERROR;
}
int
 QPSTSystem::handle_pstSystemTrapFuncEn(netsnmp_mib_handler *handler,
                          netsnmp_handler_registration *reginfo,
                          netsnmp_agent_request_info   *reqinfo,
                          netsnmp_request_info         *requests)
{
    int ret;
    /* We are never called for a GETNEXT if it's registered as a
       "instance", as it's "magically" handled for us.  */

    /* a instance handler also only hands us one request at a time, so
       we don't need to loop over a list of requests; we'll only get one. */

    static long pstSystemTrapFuncEn = 1;
    
    switch(reqinfo->mode) {

        case MODE_GET:
            snmp_set_var_typed_value(requests->requestvb, ASN_INTEGER,
                                     &pstSystemTrapFuncEn/* XXX: a pointer to the scalar's data */,
                                     sizeof(pstSystemTrapFuncEn)/* XXX: the length of the data in bytes */);
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

//        case MODE_SET_RESERVE2:
//            /* XXX malloc "undo" storage buffer */
//            if (/* XXX if malloc, or whatever, failed: */) {
//                netsnmp_set_request_error(reqinfo, requests, SNMP_ERR_RESOURCEUNAVAILABLE);
//            }
//            break;

//        case MODE_SET_FREE:
//            /* XXX: free resources allocated in RESERVE1 and/or
//               RESERVE2.  Something failed somewhere, and the states
//               below won't be called. */
//            break;

//        case MODE_SET_ACTION:
//            /* XXX: perform the value change here */
//            if (/* XXX: error? */) {
//                netsnmp_set_request_error(reqinfo, requests, /* some error */);
//            }
//            break;

//        case MODE_SET_COMMIT:
//            /* XXX: delete temporary storage */
//            if (/* XXX: error? */) {
//                /* try _really_really_ hard to never get to this point */
//                netsnmp_set_request_error(reqinfo, requests, SNMP_ERR_COMMITFAILED);
//            }
//            break;

//        case MODE_SET_UNDO:
//            /* XXX: UNDO and return to previous value for the object */
//            if (/* XXX: error? */) {
//                /* try _really_really_ hard to never get to this point */
//                netsnmp_set_request_error(reqinfo, requests, SNMP_ERR_UNDOFAILED);
//            }
//            break;

        default:
            /* we should never get here, so this is a really bad error */
            snmp_log(LOG_ERR, "unknown mode (%d) in handle_pstSystemTrapFuncEn\n", reqinfo->mode );
            return SNMP_ERR_GENERR;
    }

    return SNMP_ERR_NOERROR;
}
int
 QPSTSystem::handle_pstSystemFanTotalNum(netsnmp_mib_handler *handler,
                          netsnmp_handler_registration *reginfo,
                          netsnmp_agent_request_info   *reqinfo,
                          netsnmp_request_info         *requests)
{
    /* We are never called for a GETNEXT if it's registered as a
       "instance", as it's "magically" handled for us.  */

    /* a instance handler also only hands us one request at a time, so
       we don't need to loop over a list of requests; we'll only get one. */

    static long pstSystemFanTotalNum = 4;
    
    switch(reqinfo->mode) {

        case MODE_GET:
            snmp_set_var_typed_value(requests->requestvb, ASN_INTEGER,
                                     &pstSystemFanTotalNum/* XXX: a pointer to the scalar's data */,
                                     sizeof(pstSystemFanTotalNum)/* XXX: the length of the data in bytes */);
            break;


        default:
            /* we should never get here, so this is a really bad error */
            snmp_log(LOG_ERR, "unknown mode (%d) in handle_pstSystemFanTotalNum\n", reqinfo->mode );
            return SNMP_ERR_GENERR;
    }

    return SNMP_ERR_NOERROR;
}
int
 QPSTSystem::handle_pstSystemPowerTotalNum(netsnmp_mib_handler *handler,
                          netsnmp_handler_registration *reginfo,
                          netsnmp_agent_request_info   *reqinfo,
                          netsnmp_request_info         *requests)
{
    /* We are never called for a GETNEXT if it's registered as a
       "instance", as it's "magically" handled for us.  */

    /* a instance handler also only hands us one request at a time, so
       we don't need to loop over a list of requests; we'll only get one. */

    static long pstSystemPowerTotalNum = 8;
    
    switch(reqinfo->mode) {

        case MODE_GET:
            snmp_set_var_typed_value(requests->requestvb, ASN_INTEGER,
                                     &pstSystemPowerTotalNum/* XXX: a pointer to the scalar's data */,
                                     sizeof(pstSystemPowerTotalNum)/* XXX: the length of the data in bytes */);
            break;


        default:
            /* we should never get here, so this is a really bad error */
            snmp_log(LOG_ERR, "unknown mode (%d) in handle_pstSystemPowerTotalNum\n", reqinfo->mode );
            return SNMP_ERR_GENERR;
    }

    return SNMP_ERR_NOERROR;
}
int
 QPSTSystem::handle_pstSystemTemperature(netsnmp_mib_handler *handler,
                          netsnmp_handler_registration *reginfo,
                          netsnmp_agent_request_info   *reqinfo,
                          netsnmp_request_info         *requests)
{
    /* We are never called for a GETNEXT if it's registered as a
       "instance", as it's "magically" handled for us.  */

    /* a instance handler also only hands us one request at a time, so
       we don't need to loop over a list of requests; we'll only get one. */

    const char *pstSystemTemperature = "45.678";
    
    switch(reqinfo->mode) {

        case MODE_GET:
            snmp_set_var_typed_value(requests->requestvb, ASN_OCTET_STR,
                                     pstSystemTemperature/* XXX: a pointer to the scalar's data */,
                                     strlen(pstSystemTemperature)/* XXX: the length of the data in bytes */);
            break;


        default:
            /* we should never get here, so this is a really bad error */
            snmp_log(LOG_ERR, "unknown mode (%d) in handle_pstSystemTemperature\n", reqinfo->mode );
            return SNMP_ERR_GENERR;
    }

    return SNMP_ERR_NOERROR;
}
int
 QPSTSystem::handle_pstSystemFtpSrvIp(netsnmp_mib_handler *handler,
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

    inet_pton(AF_INET, "192.168.1.101", &(sa.sin_addr));

    in_addr_t   it = sa.sin_addr.s_addr;
    
    switch(reqinfo->mode) {

        case MODE_GET:
            snmp_set_var_typed_value(requests->requestvb, ASN_IPADDRESS,
                                     &it/* XXX: a pointer to the scalar's data */,
                                     sizeof(it)/* XXX: the length of the data in bytes */);
            break;

//        /*
//         * SET REQUEST
//         *
//         * multiple states in the transaction.  See:
//         * http://www.net-snmp.org/tutorial-5/toolkit/mib_module/set-actions.jpg
//         */
//        case MODE_SET_RESERVE1:
//                /* or you could use netsnmp_check_vb_type_and_size instead */
//            ret = netsnmp_check_vb_type(requests->requestvb, ASN_IPADDRESS);
//            if ( ret != SNMP_ERR_NOERROR ) {
//                netsnmp_set_request_error(reqinfo, requests, ret );
//            }
//            break;

//        case MODE_SET_RESERVE2:
//            /* XXX malloc "undo" storage buffer */
//            if (/* XXX if malloc, or whatever, failed: */) {
//                netsnmp_set_request_error(reqinfo, requests, SNMP_ERR_RESOURCEUNAVAILABLE);
//            }
//            break;

//        case MODE_SET_FREE:
//            /* XXX: free resources allocated in RESERVE1 and/or
//               RESERVE2.  Something failed somewhere, and the states
//               below won't be called. */
//            break;

//        case MODE_SET_ACTION:
//            /* XXX: perform the value change here */
//            if (/* XXX: error? */) {
//                netsnmp_set_request_error(reqinfo, requests, /* some error */);
//            }
//            break;

//        case MODE_SET_COMMIT:
//            /* XXX: delete temporary storage */
//            if (/* XXX: error? */) {
//                /* try _really_really_ hard to never get to this point */
//                netsnmp_set_request_error(reqinfo, requests, SNMP_ERR_COMMITFAILED);
//            }
//            break;

//        case MODE_SET_UNDO:
//            /* XXX: UNDO and return to previous value for the object */
//            if (/* XXX: error? */) {
//                /* try _really_really_ hard to never get to this point */
//                netsnmp_set_request_error(reqinfo, requests, SNMP_ERR_UNDOFAILED);
//            }
//            break;

        default:
            /* we should never get here, so this is a really bad error */
            snmp_log(LOG_ERR, "unknown mode (%d) in handle_pstSystemFtpSrvIp\n", reqinfo->mode );
            return SNMP_ERR_GENERR;
    }

    return SNMP_ERR_NOERROR;
}
int
 QPSTSystem::handle_pstSystemFtpUserName(netsnmp_mib_handler *handler,
                          netsnmp_handler_registration *reginfo,
                          netsnmp_agent_request_info   *reqinfo,
                          netsnmp_request_info         *requests)
{
    int ret;
    /* We are never called for a GETNEXT if it's registered as a
       "instance", as it's "magically" handled for us.  */

    /* a instance handler also only hands us one request at a time, so
       we don't need to loop over a list of requests; we'll only get one. */
    const char *pstSystemFtpUserName = "ifms";

    switch(reqinfo->mode) {

        case MODE_GET:
            snmp_set_var_typed_value(requests->requestvb, ASN_OCTET_STR,
                                     pstSystemFtpUserName/* XXX: a pointer to the scalar's data */,
                                     strlen(pstSystemFtpUserName)/* XXX: the length of the data in bytes */);
            break;

        /*
         * SET REQUEST
         *
         * multiple states in the transaction.  See:
         * http://www.net-snmp.org/tutorial-5/toolkit/mib_module/set-actions.jpg
         */
        case MODE_SET_RESERVE1:
                /* or you could use netsnmp_check_vb_type_and_size instead */
            ret = netsnmp_check_vb_type(requests->requestvb, ASN_OCTET_STR);
            if ( ret != SNMP_ERR_NOERROR ) {
                netsnmp_set_request_error(reqinfo, requests, ret );
            }
            break;

//        case MODE_SET_RESERVE2:
//            /* XXX malloc "undo" storage buffer */
//            if (/* XXX if malloc, or whatever, failed: */) {
//                netsnmp_set_request_error(reqinfo, requests, SNMP_ERR_RESOURCEUNAVAILABLE);
//            }
//            break;

//        case MODE_SET_FREE:
//            /* XXX: free resources allocated in RESERVE1 and/or
//               RESERVE2.  Something failed somewhere, and the states
//               below won't be called. */
//            break;

//        case MODE_SET_ACTION:
//            /* XXX: perform the value change here */
//            if (/* XXX: error? */) {
//                netsnmp_set_request_error(reqinfo, requests, /* some error */);
//            }
//            break;

//        case MODE_SET_COMMIT:
//            /* XXX: delete temporary storage */
//            if (/* XXX: error? */) {
//                /* try _really_really_ hard to never get to this point */
//                netsnmp_set_request_error(reqinfo, requests, SNMP_ERR_COMMITFAILED);
//            }
//            break;

//        case MODE_SET_UNDO:
//            /* XXX: UNDO and return to previous value for the object */
//            if (/* XXX: error? */) {
//                /* try _really_really_ hard to never get to this point */
//                netsnmp_set_request_error(reqinfo, requests, SNMP_ERR_UNDOFAILED);
//            }
//            break;

        default:
            /* we should never get here, so this is a really bad error */
            snmp_log(LOG_ERR, "unknown mode (%d) in handle_pstSystemFtpUserName\n", reqinfo->mode );
            return SNMP_ERR_GENERR;
    }

    return SNMP_ERR_NOERROR;
}
int
 QPSTSystem::handle_pstSystemFtpUserPwd(netsnmp_mib_handler *handler,
                          netsnmp_handler_registration *reginfo,
                          netsnmp_agent_request_info   *reqinfo,
                          netsnmp_request_info         *requests)
{
    int ret;
    /* We are never called for a GETNEXT if it's registered as a
       "instance", as it's "magically" handled for us.  */

    /* a instance handler also only hands us one request at a time, so
       we don't need to loop over a list of requests; we'll only get one. */
    const char *pstSystemFtpUserPwd = "ifms";
    switch(reqinfo->mode) {

        case MODE_GET:
            snmp_set_var_typed_value(requests->requestvb, ASN_OCTET_STR,
                                     pstSystemFtpUserPwd/* XXX: a pointer to the scalar's data */,
                                     strlen(pstSystemFtpUserPwd)/* XXX: the length of the data in bytes */);
            break;

        /*
         * SET REQUEST
         *
         * multiple states in the transaction.  See:
         * http://www.net-snmp.org/tutorial-5/toolkit/mib_module/set-actions.jpg
         */
        case MODE_SET_RESERVE1:
                /* or you could use netsnmp_check_vb_type_and_size instead */
            ret = netsnmp_check_vb_type(requests->requestvb, ASN_OCTET_STR);
            if ( ret != SNMP_ERR_NOERROR ) {
                netsnmp_set_request_error(reqinfo, requests, ret );
            }
            break;

//        case MODE_SET_RESERVE2:
//            /* XXX malloc "undo" storage buffer */
//            if (/* XXX if malloc, or whatever, failed: */) {
//                netsnmp_set_request_error(reqinfo, requests, SNMP_ERR_RESOURCEUNAVAILABLE);
//            }
//            break;

//        case MODE_SET_FREE:
//            /* XXX: free resources allocated in RESERVE1 and/or
//               RESERVE2.  Something failed somewhere, and the states
//               below won't be called. */
//            break;

//        case MODE_SET_ACTION:
//            /* XXX: perform the value change here */
//            if (/* XXX: error? */) {
//                netsnmp_set_request_error(reqinfo, requests, /* some error */);
//            }
//            break;

//        case MODE_SET_COMMIT:
//            /* XXX: delete temporary storage */
//            if (/* XXX: error? */) {
//                /* try _really_really_ hard to never get to this point */
//                netsnmp_set_request_error(reqinfo, requests, SNMP_ERR_COMMITFAILED);
//            }
//            break;

//        case MODE_SET_UNDO:
//            /* XXX: UNDO and return to previous value for the object */
//            if (/* XXX: error? */) {
//                /* try _really_really_ hard to never get to this point */
//                netsnmp_set_request_error(reqinfo, requests, SNMP_ERR_UNDOFAILED);
//            }
//            break;

        default:
            /* we should never get here, so this is a really bad error */
            snmp_log(LOG_ERR, "unknown mode (%d) in handle_pstSystemFtpUserPwd\n", reqinfo->mode );
            return SNMP_ERR_GENERR;
    }

    return SNMP_ERR_NOERROR;
}
int
 QPSTSystem::handle_pstSystemFtpFileName(netsnmp_mib_handler *handler,
                          netsnmp_handler_registration *reginfo,
                          netsnmp_agent_request_info   *reqinfo,
                          netsnmp_request_info         *requests)
{
    int ret;
    /* We are never called for a GETNEXT if it's registered as a
       "instance", as it's "magically" handled for us.  */

    /* a instance handler also only hands us one request at a time, so
       we don't need to loop over a list of requests; we'll only get one. */

    const char *pstSystemFtpFileName = "1.bin";
    
    switch(reqinfo->mode) {

        case MODE_GET:
            snmp_set_var_typed_value(requests->requestvb, ASN_OCTET_STR,
                                     pstSystemFtpFileName/* XXX: a pointer to the scalar's data */,
                                     strlen(pstSystemFtpFileName)/* XXX: the length of the data in bytes */);
            break;

        /*
         * SET REQUEST
         *
         * multiple states in the transaction.  See:
         * http://www.net-snmp.org/tutorial-5/toolkit/mib_module/set-actions.jpg
         */
        case MODE_SET_RESERVE1:
                /* or you could use netsnmp_check_vb_type_and_size instead */
            ret = netsnmp_check_vb_type(requests->requestvb, ASN_OCTET_STR);
            if ( ret != SNMP_ERR_NOERROR ) {
                netsnmp_set_request_error(reqinfo, requests, ret );
            }
            break;

//        case MODE_SET_RESERVE2:
//            /* XXX malloc "undo" storage buffer */
//            if (/* XXX if malloc, or whatever, failed: */) {
//                netsnmp_set_request_error(reqinfo, requests, SNMP_ERR_RESOURCEUNAVAILABLE);
//            }
//            break;

//        case MODE_SET_FREE:
//            /* XXX: free resources allocated in RESERVE1 and/or
//               RESERVE2.  Something failed somewhere, and the states
//               below won't be called. */
//            break;

//        case MODE_SET_ACTION:
//            /* XXX: perform the value change here */
//            if (/* XXX: error? */) {
//                netsnmp_set_request_error(reqinfo, requests, /* some error */);
//            }
//            break;

//        case MODE_SET_COMMIT:
//            /* XXX: delete temporary storage */
//            if (/* XXX: error? */) {
//                /* try _really_really_ hard to never get to this point */
//                netsnmp_set_request_error(reqinfo, requests, SNMP_ERR_COMMITFAILED);
//            }
//            break;

//        case MODE_SET_UNDO:
//            /* XXX: UNDO and return to previous value for the object */
//            if (/* XXX: error? */) {
//                /* try _really_really_ hard to never get to this point */
//                netsnmp_set_request_error(reqinfo, requests, SNMP_ERR_UNDOFAILED);
//            }
//            break;

        default:
            /* we should never get here, so this is a really bad error */
            snmp_log(LOG_ERR, "unknown mode (%d) in handle_pstSystemFtpFileName\n", reqinfo->mode );
            return SNMP_ERR_GENERR;
    }

    return SNMP_ERR_NOERROR;
}
int
 QPSTSystem::handle_pstSystemUpgFileType(netsnmp_mib_handler *handler,
                          netsnmp_handler_registration *reginfo,
                          netsnmp_agent_request_info   *reqinfo,
                          netsnmp_request_info         *requests)
{
    int ret;
    /* We are never called for a GETNEXT if it's registered as a
       "instance", as it's "magically" handled for us.  */

    /* a instance handler also only hands us one request at a time, so
       we don't need to loop over a list of requests; we'll only get one. */
    static long pstSystemUpgFileType=1;
    switch(reqinfo->mode) {

        case MODE_GET:
            snmp_set_var_typed_value(requests->requestvb, ASN_INTEGER,
                                     &pstSystemUpgFileType/* XXX: a pointer to the scalar's data */,
                                     sizeof(pstSystemUpgFileType)/* XXX: the length of the data in bytes */);
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

//        case MODE_SET_RESERVE2:
//            /* XXX malloc "undo" storage buffer */
//            if (/* XXX if malloc, or whatever, failed: */) {
//                netsnmp_set_request_error(reqinfo, requests, SNMP_ERR_RESOURCEUNAVAILABLE);
//            }
//            break;

//        case MODE_SET_FREE:
//            /* XXX: free resources allocated in RESERVE1 and/or
//               RESERVE2.  Something failed somewhere, and the states
//               below won't be called. */
//            break;

//        case MODE_SET_ACTION:
//            /* XXX: perform the value change here */
//            if (/* XXX: error? */) {
//                netsnmp_set_request_error(reqinfo, requests, /* some error */);
//            }
//            break;

//        case MODE_SET_COMMIT:
//            /* XXX: delete temporary storage */
//            if (/* XXX: error? */) {
//                /* try _really_really_ hard to never get to this point */
//                netsnmp_set_request_error(reqinfo, requests, SNMP_ERR_COMMITFAILED);
//            }
//            break;

//        case MODE_SET_UNDO:
//            /* XXX: UNDO and return to previous value for the object */
//            if (/* XXX: error? */) {
//                /* try _really_really_ hard to never get to this point */
//                netsnmp_set_request_error(reqinfo, requests, SNMP_ERR_UNDOFAILED);
//            }
//            break;

        default:
            /* we should never get here, so this is a really bad error */
            snmp_log(LOG_ERR, "unknown mode (%d) in handle_pstSystemUpgFileType\n", reqinfo->mode );
            return SNMP_ERR_GENERR;
    }

    return SNMP_ERR_NOERROR;
}
int
 QPSTSystem::handle_pstSystemUpgDstSlot(netsnmp_mib_handler *handler,
                          netsnmp_handler_registration *reginfo,
                          netsnmp_agent_request_info   *reqinfo,
                          netsnmp_request_info         *requests)
{
    int ret;
    /* We are never called for a GETNEXT if it's registered as a
       "instance", as it's "magically" handled for us.  */

    /* a instance handler also only hands us one request at a time, so
       we don't need to loop over a list of requests; we'll only get one. */
    static long pstSystemUpgDstSlot = 2;
    switch(reqinfo->mode) {

        case MODE_GET:
            snmp_set_var_typed_value(requests->requestvb, ASN_INTEGER,
                                     &pstSystemUpgDstSlot/* XXX: a pointer to the scalar's data */,
                                     sizeof(pstSystemUpgDstSlot)/* XXX: the length of the data in bytes */);
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

//        case MODE_SET_RESERVE2:
//            /* XXX malloc "undo" storage buffer */
//            if (/* XXX if malloc, or whatever, failed: */) {
//                netsnmp_set_request_error(reqinfo, requests, SNMP_ERR_RESOURCEUNAVAILABLE);
//            }
//            break;

//        case MODE_SET_FREE:
//            /* XXX: free resources allocated in RESERVE1 and/or
//               RESERVE2.  Something failed somewhere, and the states
//               below won't be called. */
//            break;

//        case MODE_SET_ACTION:
//            /* XXX: perform the value change here */
//            if (/* XXX: error? */) {
//                netsnmp_set_request_error(reqinfo, requests, /* some error */);
//            }
//            break;

//        case MODE_SET_COMMIT:
//            /* XXX: delete temporary storage */
//            if (/* XXX: error? */) {
//                /* try _really_really_ hard to never get to this point */
//                netsnmp_set_request_error(reqinfo, requests, SNMP_ERR_COMMITFAILED);
//            }
//            break;

//        case MODE_SET_UNDO:
//            /* XXX: UNDO and return to previous value for the object */
//            if (/* XXX: error? */) {
//                /* try _really_really_ hard to never get to this point */
//                netsnmp_set_request_error(reqinfo, requests, SNMP_ERR_UNDOFAILED);
//            }
//            break;

        default:
            /* we should never get here, so this is a really bad error */
            snmp_log(LOG_ERR, "unknown mode (%d) in handle_pstSystemUpgDstSlot\n", reqinfo->mode );
            return SNMP_ERR_GENERR;
    }

    return SNMP_ERR_NOERROR;
}
int
 QPSTSystem::handle_pstSystemUpgAction(netsnmp_mib_handler *handler,
                          netsnmp_handler_registration *reginfo,
                          netsnmp_agent_request_info   *reqinfo,
                          netsnmp_request_info         *requests)
{
    int ret;
    /* We are never called for a GETNEXT if it's registered as a
       "instance", as it's "magically" handled for us.  */

    /* a instance handler also only hands us one request at a time, so
       we don't need to loop over a list of requests; we'll only get one. */
    static long pstSystemUpgAction = 0;
    switch(reqinfo->mode) {

        case MODE_GET:
            snmp_set_var_typed_value(requests->requestvb, ASN_INTEGER,
                                     &pstSystemUpgAction/* XXX: a pointer to the scalar's data */,
                                     sizeof(pstSystemUpgAction)/* XXX: the length of the data in bytes */);
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

//        case MODE_SET_RESERVE2:
//            /* XXX malloc "undo" storage buffer */
//            if (/* XXX if malloc, or whatever, failed: */) {
//                netsnmp_set_request_error(reqinfo, requests, SNMP_ERR_RESOURCEUNAVAILABLE);
//            }
//            break;

//        case MODE_SET_FREE:
//            /* XXX: free resources allocated in RESERVE1 and/or
//               RESERVE2.  Something failed somewhere, and the states
//               below won't be called. */
//            break;

//        case MODE_SET_ACTION:
//            /* XXX: perform the value change here */
//            if (/* XXX: error? */) {
//                netsnmp_set_request_error(reqinfo, requests, /* some error */);
//            }
//            break;

//        case MODE_SET_COMMIT:
//            /* XXX: delete temporary storage */
//            if (/* XXX: error? */) {
//                /* try _really_really_ hard to never get to this point */
//                netsnmp_set_request_error(reqinfo, requests, SNMP_ERR_COMMITFAILED);
//            }
//            break;

//        case MODE_SET_UNDO:
//            /* XXX: UNDO and return to previous value for the object */
//            if (/* XXX: error? */) {
//                /* try _really_really_ hard to never get to this point */
//                netsnmp_set_request_error(reqinfo, requests, SNMP_ERR_UNDOFAILED);
//            }
//            break;

        default:
            /* we should never get here, so this is a really bad error */
            snmp_log(LOG_ERR, "unknown mode (%d) in handle_pstSystemUpgAction\n", reqinfo->mode );
            return SNMP_ERR_GENERR;
    }

    return SNMP_ERR_NOERROR;
}
int
 QPSTSystem::handle_pstSystemUpgStatus(netsnmp_mib_handler *handler,
                          netsnmp_handler_registration *reginfo,
                          netsnmp_agent_request_info   *reqinfo,
                          netsnmp_request_info         *requests)
{
    /* We are never called for a GETNEXT if it's registered as a
       "instance", as it's "magically" handled for us.  */

    /* a instance handler also only hands us one request at a time, so
       we don't need to loop over a list of requests; we'll only get one. */
    static long pstSystemUpgStatus = 1;
    switch(reqinfo->mode) {

        case MODE_GET:
            snmp_set_var_typed_value(requests->requestvb, ASN_INTEGER,
                                     &pstSystemUpgStatus/* XXX: a pointer to the scalar's data */,
                                     sizeof(pstSystemUpgStatus)/* XXX: the length of the data in bytes */);
            break;


        default:
            /* we should never get here, so this is a really bad error */
            snmp_log(LOG_ERR, "unknown mode (%d) in handle_pstSystemUpgStatus\n", reqinfo->mode );
            return SNMP_ERR_GENERR;
    }

    return SNMP_ERR_NOERROR;
}
int
 QPSTSystem::handle_pstSystemUpgResultInfo(netsnmp_mib_handler *handler,
                          netsnmp_handler_registration *reginfo,
                          netsnmp_agent_request_info   *reqinfo,
                          netsnmp_request_info         *requests)
{
    /* We are never called for a GETNEXT if it's registered as a
       "instance", as it's "magically" handled for us.  */

    /* a instance handler also only hands us one request at a time, so
       we don't need to loop over a list of requests; we'll only get one. */
    const char *pstSystemUpgResultInfo="success";
    switch(reqinfo->mode) {

        case MODE_GET:
            snmp_set_var_typed_value(requests->requestvb, ASN_OCTET_STR,
                                     pstSystemUpgResultInfo/* XXX: a pointer to the scalar's data */,
                                     strlen(pstSystemUpgResultInfo)/* XXX: the length of the data in bytes */);
            break;


        default:
            /* we should never get here, so this is a really bad error */
            snmp_log(LOG_ERR, "unknown mode (%d) in handle_pstSystemUpgResultInfo\n", reqinfo->mode );
            return SNMP_ERR_GENERR;
    }

    return SNMP_ERR_NOERROR;
}
int
 QPSTSystem::handle_pstSystemProductType(netsnmp_mib_handler *handler,
                          netsnmp_handler_registration *reginfo,
                          netsnmp_agent_request_info   *reqinfo,
                          netsnmp_request_info         *requests)
{
    /* We are never called for a GETNEXT if it's registered as a
       "instance", as it's "magically" handled for us.  */

    /* a instance handler also only hands us one request at a time, so
       we don't need to loop over a list of requests; we'll only get one. */
    static long pstSystemProductType = 0;
    switch(reqinfo->mode) {

        case MODE_GET:
            snmp_set_var_typed_value(requests->requestvb, ASN_INTEGER,
                                     &pstSystemProductType/* XXX: a pointer to the scalar's data */,
                                     sizeof(pstSystemProductType)/* XXX: the length of the data in bytes */);
            break;


        default:
            /* we should never get here, so this is a really bad error */
            snmp_log(LOG_ERR, "unknown mode (%d) in handle_pstSystemProductType\n", reqinfo->mode );
            return SNMP_ERR_GENERR;
    }

    return SNMP_ERR_NOERROR;
}


/** Initialize the pstSystemTrapTargetTable table by defining its contents and how it's structured */
void
 QPSTSystem::initialize_table_pstSystemTrapTargetTable(void)
{
    const oid pstSystemTrapTargetTable_oid[] = {1,3,6,1,4,1,48391,2,1,3,2};
    netsnmp_table_data_set *table_set;

    /* create the table structure itself */
    table_set = netsnmp_create_table_data_set("pstSystemTrapTargetTable");

    /* comment this out or delete if you don't support creation of new rows */
    table_set->allow_creation = 1;

    /***************************************************
     * Adding indexes
     */
    DEBUGMSGTL(("initialize_table_pstSystemTrapTargetTable",
                "adding indexes to table pstSystemTrapTargetTable\n"));
    netsnmp_table_set_add_indexes(table_set,
                           ASN_OCTET_STR,  /* index: pstSystemTrapTargetName */
                           0);

    DEBUGMSGTL(("initialize_table_pstSystemTrapTargetTable",
                "adding column types to table pstSystemTrapTargetTable\n"));		 
    netsnmp_table_set_multi_add_default_row(table_set,
                                            COLUMN_PSTSYSTEMTRAPTARGETNAME, ASN_OCTET_STR, 0,
                                            NULL, 0,
                                            COLUMN_PSTSYSTEMTRAPTARGETIPADDR, ASN_IPADDRESS, 1,
                                            NULL, 0,
                                            COLUMN_PSTSYSTEMTRAPTARGETCOMMUNITY, ASN_OCTET_STR, 1,
                                            NULL, 0,
                                            COLUMN_PSTSYSTEMTRAPTARGETTRAPVERSION, ASN_INTEGER, 1,
                                            NULL, 0,
                                            COLUMN_PSTSYSTEMTRAPTARGETROWSTATUS, ASN_INTEGER, 1,
                                            NULL, 0,
                              0);
    
    /* registering the table with the master agent */
    /* note: if you don't need a subhandler to deal with any aspects
       of the request, change pstSystemTrapTargetTable_handler to "NULL" */
    netsnmp_register_table_data_set(netsnmp_create_handler_registration("pstSystemTrapTargetTable", pstSystemTrapTargetTable_handler,
                                                        pstSystemTrapTargetTable_oid,
                                                        OID_LENGTH(pstSystemTrapTargetTable_oid),
                                                        HANDLER_CAN_RWRITE),
                            table_set, NULL);
}
/** Initialize the pstSystemFanTable table by defining its contents and how it's structured */
void
 QPSTSystem::initialize_table_pstSystemFanTable(void)
{
    const oid pstSystemFanTable_oid[] = {1,3,6,1,4,1,48391,2,1,4,3};
    netsnmp_table_data_set *table_set;

    /* create the table structure itself */
    table_set = netsnmp_create_table_data_set("pstSystemFanTable");

    /* comment this out or delete if you don't support creation of new rows */
    table_set->allow_creation = 1;

    /***************************************************
     * Adding indexes
     */
    DEBUGMSGTL(("initialize_table_pstSystemFanTable",
                "adding indexes to table pstSystemFanTable\n"));
    netsnmp_table_set_add_indexes(table_set,
                           ASN_INTEGER,  /* index: pstSystemFanIndex */
                           0);

    DEBUGMSGTL(("initialize_table_pstSystemFanTable",
                "adding column types to table pstSystemFanTable\n"));		 
    netsnmp_table_set_multi_add_default_row(table_set,
                                            COLUMN_PSTSYSTEMFANINDEX, ASN_INTEGER, 0,
                                            NULL, 0,
                                            COLUMN_PSTSYSTEMFANSTATUS, ASN_INTEGER, 0,
                                            NULL, 0,
                                            COLUMN_PSTSYSTEMFANSPEED, ASN_INTEGER, 0,
                                            NULL, 0,
                              0);
    
    /* registering the table with the master agent */
    /* note: if you don't need a subhandler to deal with any aspects
       of the request, change pstSystemFanTable_handler to "NULL" */
    netsnmp_register_table_data_set(netsnmp_create_handler_registration("pstSystemFanTable", pstSystemFanTable_handler,
                                                        pstSystemFanTable_oid,
                                                        OID_LENGTH(pstSystemFanTable_oid),
                                                        HANDLER_CAN_RWRITE),
                            table_set, NULL);
}
/** Initialize the pstSystemPowerTable table by defining its contents and how it's structured */
void
 QPSTSystem::initialize_table_pstSystemPowerTable(void)
{
    const oid pstSystemPowerTable_oid[] = {1,3,6,1,4,1,48391,2,1,4,4};
    netsnmp_table_data_set *table_set;

    /* create the table structure itself */
    table_set = netsnmp_create_table_data_set("pstSystemPowerTable");

    /* comment this out or delete if you don't support creation of new rows */
    table_set->allow_creation = 1;

    /***************************************************
     * Adding indexes
     */
    DEBUGMSGTL(("initialize_table_pstSystemPowerTable",
                "adding indexes to table pstSystemPowerTable\n"));
    netsnmp_table_set_add_indexes(table_set,
                           ASN_INTEGER,  /* index: pstSystemPowerIndex */
                           0);

    DEBUGMSGTL(("initialize_table_pstSystemPowerTable",
                "adding column types to table pstSystemPowerTable\n"));		 
    netsnmp_table_set_multi_add_default_row(table_set,
                                            COLUMN_PSTSYSTEMPOWERINDEX, ASN_INTEGER, 0,
                                            NULL, 0,
                                            COLUMN_PSTSYSTEMPOWERSTATUS, ASN_INTEGER, 0,
                                            NULL, 0,
                                            COLUMN_PSTSYSTEMPOWERVOLTAGE, ASN_OCTET_STR, 0,
                                            NULL, 0,
                                            COLUMN_PSTSYSTEMPOWERCURRENT, ASN_OCTET_STR, 0,
                                            NULL, 0,
                              0);
    
    /* registering the table with the master agent */
    /* note: if you don't need a subhandler to deal with any aspects
       of the request, change pstSystemPowerTable_handler to "NULL" */
    netsnmp_register_table_data_set(netsnmp_create_handler_registration("pstSystemPowerTable", pstSystemPowerTable_handler,
                                                        pstSystemPowerTable_oid,
                                                        OID_LENGTH(pstSystemPowerTable_oid),
                                                        HANDLER_CAN_RWRITE),
                            table_set, NULL);
}

/** handles requests for the pstSystemTrapTargetTable table, if anything else needs to be done */
int
 QPSTSystem::pstSystemTrapTargetTable_handler(
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

/** handles requests for the pstSystemFanTable table, if anything else needs to be done */
int
 QPSTSystem::pstSystemFanTable_handler(
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

/** handles requests for the pstSystemPowerTable table, if anything else needs to be done */
int
 QPSTSystem::pstSystemPowerTable_handler(
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
