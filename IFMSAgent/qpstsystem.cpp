#include <QObject>
#include <QMutex>
#include <QMutexLocker>

#include "qpstsystem.h"
#include "qagentapp.h"
#include "qpst.h"

static QMutex   gPSTSystem_mutex;

QPSTSystem::QPSTSystem(QObject *parent) : QObject(parent)
{
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
    const oid DDRConsumption_oid[] = { 1,3,6,1,4,1,48391,2,1,1,8 };
    const oid DDRCleanUp_oid[] = { 1,3,6,1,4,1,48391,2,1,1,9 };
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
    const oid pstSystemTemperatureHighThreshold_oid[] = { 1,3,6,1,4,1,48391,2,1,4,6 };
    const oid pstSystemTemperatureLowThreshold_oid[] = { 1,3,6,1,4,1,48391,2,1,4,7 };
    const oid pstSystemTemperatureControlMode_oid[] = { 1,3,6,1,4,1,48391,2,1,4,8 };
    const oid pstSystemADG707Switch_oid[] = { 1,3,6,1,4,1,48391,2,1,4,9 };
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
        netsnmp_create_handler_registration("DDRConsumption", handle_DDRConsumption,
                               DDRConsumption_oid, OID_LENGTH(DDRConsumption_oid),
                               HANDLER_CAN_RONLY
        ));
    netsnmp_register_scalar(
        netsnmp_create_handler_registration("DDRCleanUp", handle_DDRCleanUp,
                               DDRCleanUp_oid, OID_LENGTH(DDRCleanUp_oid),
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
                               HANDLER_CAN_RWRITE
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
        netsnmp_create_handler_registration("pstSystemTemperatureHighThreshold", handle_pstSystemTemperatureHighThreshold,
                               pstSystemTemperatureHighThreshold_oid, OID_LENGTH(pstSystemTemperatureHighThreshold_oid),
                               HANDLER_CAN_RWRITE
        ));
    netsnmp_register_scalar(
        netsnmp_create_handler_registration("pstSystemTemperatureLowThreshold", handle_pstSystemTemperatureLowThreshold,
                               pstSystemTemperatureLowThreshold_oid, OID_LENGTH(pstSystemTemperatureLowThreshold_oid),
                               HANDLER_CAN_RWRITE
        ));
    netsnmp_register_scalar(
        netsnmp_create_handler_registration("pstSystemTemperatureControlMode", handle_pstSystemTemperatureControlMode,
                               pstSystemTemperatureControlMode_oid, OID_LENGTH(pstSystemTemperatureControlMode_oid),
                               HANDLER_CAN_RWRITE
        ));
    netsnmp_register_scalar(
        netsnmp_create_handler_registration("pstSystemADG707Switch", handle_pstSystemADG707Switch,
                               pstSystemADG707Switch_oid, OID_LENGTH(pstSystemADG707Switch_oid),
                               HANDLER_CAN_RWRITE
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

// SCALAR 
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
    QPST *p = QPST::getInstance();

    char *devName = p->m_system->m_pstSystem.get_devName().toLatin1().data();
    
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
            {
            devName = (char*)(requests->requestvb->val.string);
            size_t len = requests->requestvb->val_len;
            QString name = QString::fromLatin1(devName,len);

            p->m_system->m_pstSystem.set_devName(name);

            netsnmp_set_request_error(reqinfo, requests, SNMP_ERR_NOERROR/* some error */);
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
    QPST *pst = QPST::getInstance();

    QString s = pst->m_system->m_pstSystem.get_devIpAddr();
    struct sockaddr_in sa;

    inet_pton(AF_INET, s.toLatin1().data(), &(sa.sin_addr));

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
            {
            ret = netsnmp_check_vb_type(requests->requestvb, ASN_IPADDRESS);
            if ( ret != SNMP_ERR_NOERROR ) {
                netsnmp_set_request_error(reqinfo, requests, ret );
            }

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
            {
            QPST *pst = QPST::getInstance();
            in_addr_t s = (in_addr_t)(*requests->requestvb->val.integer);
            char *ip = inet_ntoa(*((struct in_addr*)&s));
            QString qs = QString("%1").arg(ip);
            pst->m_system->m_pstSystem.set_devIpAddr(qs);
            if (0/* XXX: error? */) {
                netsnmp_set_request_error(reqinfo, requests, 0/* some error */);
            }
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
    QPST *pst = QPST::getInstance();
    QString  s = pst->m_system->m_pstSystem.get_devGateway();

    inet_pton(AF_INET, s.toLatin1().data(), &(sa.sin_addr));

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

    inet_pton(AF_INET, "255.255.255.0", &(sa.sin_addr));

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
            {
                QPST *pst = QPST::getInstance();
                long  s = (long)(*requests->requestvb->val.integer);
                if(s == 1){
                    pst->m_system->m_pstSystem.set_saveCurrentConfiguration(s);
                }
                else
                {
                netsnmp_set_request_error(reqinfo, requests, SNMP_ERR_BADVALUE);
                }
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
    QPST *pst = QPST::getInstance();

    long reboot = pst->m_system->m_pstSystem.get_reboot();
    
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
			{
            ret = netsnmp_check_vb_type(requests->requestvb, ASN_INTEGER);
            if ( ret != SNMP_ERR_NOERROR ) {
                netsnmp_set_request_error(reqinfo, requests, ret );
            }
			
            QPST *pst =  QPST::getInstance();
            int s = int(*requests->requestvb->val.integer);

            pst->m_system->m_pstSystem.set_reboot(s);

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
        {
            /* XXX: perform the value change here */
            if (0/* XXX: error? */) {
                netsnmp_set_request_error(reqinfo, requests, 0/* some error */);
            }
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
            snmp_log(LOG_ERR, "unknown mode (%d) in handle_reboot\n", reqinfo->mode );
            return SNMP_ERR_GENERR;
    }

    return SNMP_ERR_NOERROR;
}
int
 QPSTSystem::handle_DDRConsumption(netsnmp_mib_handler *handler,
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
        {
        	QPST *pst = QPST::getInstance();
            long s = pst->m_system->m_pstSystem.get_DDRConsumption();
            snmp_set_var_typed_value(requests->requestvb, ASN_INTEGER,
                                     &s/* XXX: a pointer to the scalar's data */,
                                     sizeof(s)/* XXX: the length of the data in bytes */);
        }
        break;


        default:
            /* we should never get here, so this is a really bad error */
            snmp_log(LOG_ERR, "unknown mode (%d) in handle_DDRConsumption\n", reqinfo->mode );
            return SNMP_ERR_GENERR;
    }

    return SNMP_ERR_NOERROR;
}
int
 QPSTSystem::handle_DDRCleanUp(netsnmp_mib_handler *handler,
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
    	{
		QPST *pst = QPST::getInstance();
		long s = pst->m_system->m_pstSystem.get_DDRCleanUp();
            snmp_set_var_typed_value(requests->requestvb, ASN_INTEGER,
                                     &s/* XXX: a pointer to the scalar's data */,
                                     sizeof(s)/* XXX: the length of the data in bytes */);
         }
		 break;

        /*
         * SET REQUEST
         *
         * multiple states in the transaction.  See:
         * http://www.net-snmp.org/tutorial-5/toolkit/mib_module/set-actions.jpg
         */
        case MODE_SET_RESERVE1:
                /* or you could use netsnmp_check_vb_type_and_size instead */
           {
            ret = netsnmp_check_vb_type(requests->requestvb, ASN_INTEGER);
            if ( ret != SNMP_ERR_NOERROR ) {
                netsnmp_set_request_error(reqinfo, requests, ret );
            }
			QPST *pst = QPST::getInstance();
			
            long s = (long)(*requests->requestvb->val.integer);
			pst->m_system->m_pstSystem.set_DDRCleanUp(s);
			
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
            snmp_log(LOG_ERR, "unknown mode (%d) in handle_DDRCleanUp\n", reqinfo->mode );
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

    const char *pstHwVer = "1.0.0";
    
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

    const char *pstSwVer = "1.0.0";
    
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

    const char *pstFwVer = "1.0.0";
    
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
    int ret;
    /* We are never called for a GETNEXT if it's registered as a
       "instance", as it's "magically" handled for us.  */

    /* a instance handler also only hands us one request at a time, so
       we don't need to loop over a list of requests; we'll only get one. */

    switch(reqinfo->mode) {

        case MODE_GET:
    	{
			QPST *pst = QPST::getInstance();
			QString s  = pst->m_system->m_pstSystem.get_pstSn();
		
            snmp_set_var_typed_value(requests->requestvb, ASN_OCTET_STR,
                                     s.toLatin1().data()/* XXX: a pointer to the scalar's data */,
                                     s.length()/* XXX: the length of the data in bytes */);

		}
        /*
         * SET REQUEST
         *
         * multiple states in the transaction.  See:
         * http://www.net-snmp.org/tutorial-5/toolkit/mib_module/set-actions.jpg
         */
        case MODE_SET_RESERVE1:
                /* or you could use netsnmp_check_vb_type_and_size instead */
                	{
            ret = netsnmp_check_vb_type(requests->requestvb, ASN_OCTET_STR);
            if ( ret != SNMP_ERR_NOERROR ) {
                netsnmp_set_request_error(reqinfo, requests, ret );
            }
			QPST *pst = QPST::getInstance();
			char *cs = (char*)requests->requestvb->val.string;
			QString s = QString("%1").arg(cs);
			pst->m_system->m_pstSystem.set_pstSn(s);
			
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
    QPST *pst = QPST::getInstance();
    QString s = pst->m_system->m_pstSystem.get_devMacAddress();

    switch(reqinfo->mode) {

        case MODE_GET:
            snmp_set_var_typed_value(requests->requestvb, ASN_OCTET_STR,
                                     s.toLatin1().data()/* XXX: a pointer to the scalar's data */,
                                     s.length()/* XXX: the length of the data in bytes */);
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

     
    switch(reqinfo->mode) {

        case MODE_GET:
    	{
    	QPST *pst = QPST::getInstance();
		long s = pst->m_system->m_pstSystem.get_pstSystemTrapFuncEn();
            snmp_set_var_typed_value(requests->requestvb, ASN_INTEGER,
                                     &s/* XXX: a pointer to the scalar's data */,
                                     sizeof(s)/* XXX: the length of the data in bytes */);
        	}
            break;

        /*
         * SET REQUEST
         *
         * multiple states in the transaction.  See:
         * http://www.net-snmp.org/tutorial-5/toolkit/mib_module/set-actions.jpg
         */
        case MODE_SET_RESERVE1:
                /* or you could use netsnmp_check_vb_type_and_size instead */
                	{
            ret = netsnmp_check_vb_type(requests->requestvb, ASN_INTEGER);
            if ( ret != SNMP_ERR_NOERROR ) {
                netsnmp_set_request_error(reqinfo, requests, ret );
            }
			QPST *pst = QPST::getInstance();
			long s = (long)(* requests->requestvb->val.integer);
			pst->m_system->m_pstSystem.set_pstSystemTrapFuncEn(s);
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

    switch(reqinfo->mode) {

        case MODE_GET:
    	{
    	QPST *pst = QPST::getInstance();
		long s = pst->m_system->m_pstSystem.get_pstSystemFanTotalNum();
            snmp_set_var_typed_value(requests->requestvb, ASN_INTEGER,
                                     &s/* XXX: a pointer to the scalar's data */,
                                     sizeof(s)/* XXX: the length of the data in bytes */);
        	}
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
    	{
    	QPST *pst = QPST::getInstance();
		long s = pst->m_system->m_pstSystem.get_pstSystemPowerTotalNum();

            snmp_set_var_typed_value(requests->requestvb, ASN_INTEGER,
                                     &s/* XXX: a pointer to the scalar's data */,
                                     sizeof(s)/* XXX: the length of the data in bytes */);
          }
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

    switch(reqinfo->mode) {

        case MODE_GET:
            {
            QPST *pst = QPST::getInstance();
            QString s = pst->m_system->m_pstSystem.get_pstSystemTemperature();

            snmp_set_var_typed_value(requests->requestvb, ASN_OCTET_STR,
                                     s.toLatin1().data()/* XXX: a pointer to the scalar's data */,
                                     s.length()/* XXX: the length of the data in bytes */);
            }
            break;


        default:
            /* we should never get here, so this is a really bad error */
            snmp_log(LOG_ERR, "unknown mode (%d) in handle_pstSystemTemperature\n", reqinfo->mode );
            return SNMP_ERR_GENERR;
    }

    return SNMP_ERR_NOERROR;
}
int
 QPSTSystem::handle_pstSystemTemperatureHighThreshold(netsnmp_mib_handler *handler,
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
        {
            QPST *pst = QPST::getInstance();
            QString s = pst->m_system->m_pstSystem.get_pstSystemTemperatureHighThreshold();
            snmp_set_var_typed_value(requests->requestvb, ASN_OCTET_STR,
                                     s.toLatin1().data()/* XXX: a pointer to the scalar's data */,
                                     s.length()/* XXX: the length of the data in bytes */);

        }
        break;


        /*
         * SET REQUEST
         *
         * multiple states in the transaction.  See:
         * http://www.net-snmp.org/tutorial-5/toolkit/mib_module/set-actions.jpg
         */
        case MODE_SET_RESERVE1:
                /* or you could use netsnmp_check_vb_type_and_size instead */
            {
            ret = netsnmp_check_vb_type(requests->requestvb, ASN_OCTET_STR);
            if ( ret != SNMP_ERR_NOERROR ) {
                netsnmp_set_request_error(reqinfo, requests, ret );
            }
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
            {
            QPST *pst = QPST::getInstance();
            char *cs = (char*)requests->requestvb->val.string;
            QString s = QString("%1").arg(cs);

            int  t = s.toInt();
            pst->m_system->m_pstSystem.set_pstSystemTemperatureHighThreshold(s);
            emit pst->sigSystemTemperatureHighThreshold(t);
            if (t <= 0) {
                netsnmp_set_request_error(reqinfo, requests, SNMP_ERR_BADVALUE);
            }
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
            snmp_log(LOG_ERR, "unknown mode (%d) in handle_pstSystemTemperatureHighThreshold\n", reqinfo->mode );
            return SNMP_ERR_GENERR;

    }

    return SNMP_ERR_NOERROR;
}
int
 QPSTSystem::handle_pstSystemTemperatureLowThreshold(netsnmp_mib_handler *handler,
                          netsnmp_handler_registration *reginfo,
                          netsnmp_agent_request_info   *reqinfo,
                          netsnmp_request_info         *requests)
{
    int ret;
    /* We are never called for a GETNEXT if it's registered as a
       "instance", as it's "magically" handled for us.  */

    /* a instance handler also only hands us one request at a time, so
       we don't need to loop over a list of requests; we'll only get one. */

    const char *pstSystemTemperatureLowThreshold = "-5";

    switch(reqinfo->mode) {

        case MODE_GET:
        {
            QPST *pst = QPST::getInstance();
            QString s = pst->m_system->m_pstSystem.get_pstSystemTemperatureLowThreshold();
            snmp_set_var_typed_value(requests->requestvb, ASN_OCTET_STR,
                                     s.toLatin1().data()/* XXX: a pointer to the scalar's data */,
                                     s.length()/* XXX: the length of the data in bytes */);

        }
        break;

        /*
         * SET REQUEST
         *
         * multiple states in the transaction.  See:
         * http://www.net-snmp.org/tutorial-5/toolkit/mib_module/set-actions.jpg
         */
        case MODE_SET_RESERVE1:
                /* or you could use netsnmp_check_vb_type_and_size instead */
            {
            ret = netsnmp_check_vb_type(requests->requestvb, ASN_OCTET_STR);
            if ( ret != SNMP_ERR_NOERROR ) {
                netsnmp_set_request_error(reqinfo, requests, ret );
            }

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
            {
                QPST *pst = QPST::getInstance();
                char *cs = (char*)requests->requestvb->val.string;
                QString s = QString("%1").arg(cs);

                int  t = s.toInt();
                int  tl = pst->m_system->m_pstSystem.get_pstSystemTemperatureLowThreshold().toInt();
                int  th = pst->m_system->m_pstSystem.get_pstSystemTemperatureHighThreshold().toInt();
                if( tl < th - DEFAULT_LOW_TEMPERATURE){
                    pst->m_system->m_pstSystem.set_pstSystemTemperatureLowThreshold(s);
                    emit pst->sigSystemTemperatureLowThreshold(t);
                }
                else
                {
                netsnmp_set_request_error(reqinfo, requests, SNMP_ERR_BADVALUE);
                }
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
            snmp_log(LOG_ERR, "unknown mode (%d) in handle_pstSystemTemperatureLowThreshold\n", reqinfo->mode );
            return SNMP_ERR_GENERR;
    }

    return SNMP_ERR_NOERROR;
}
int
 QPSTSystem::handle_pstSystemTemperatureControlMode(netsnmp_mib_handler *handler,
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
		{
			QPST *pst = QPST::getInstance();
			long s = pst->m_system->m_pstSystem.get_pstSystemTemperatureControlMode(0);
            snmp_set_var_typed_value(requests->requestvb, ASN_INTEGER,
                                     &s/* XXX: a pointer to the scalar's data */,
                                     sizeof(s)/* XXX: the length of the data in bytes */);
		}
            break;

        /*
         * SET REQUEST
         *
         * multiple states in the transaction.  See:
         * http://www.net-snmp.org/tutorial-5/toolkit/mib_module/set-actions.jpg
         */
        case MODE_SET_RESERVE1:
                /* or you could use netsnmp_check_vb_type_and_size instead */
            {
            ret = netsnmp_check_vb_type(requests->requestvb, ASN_INTEGER);
            if ( ret != SNMP_ERR_NOERROR ) {
                netsnmp_set_request_error(reqinfo, requests, ret );
            }
//			QPST *pst = QPST::getInstance();
//			long s = (long)(*requests->requestvb->val.integer);
//			pst->m_system->m_pstSystem.set_pstSystemTemperatureControlMode(0 , s);
//			emit pst->sigSystemFanControlMode(s);

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
            {
                {
                ret = netsnmp_check_vb_type(requests->requestvb, ASN_INTEGER);
                if ( ret != SNMP_ERR_NOERROR ) {
                    netsnmp_set_request_error(reqinfo, requests, ret );
                }
                QPST *pst = QPST::getInstance();
                long s = (long)(*requests->requestvb->val.integer);
                pst->m_system->m_pstSystem.set_pstSystemTemperatureControlMode(0 , s);
                emit pst->sigSystemFanControlMode(s);

                }

                if (0/* XXX: error? */) {
                    netsnmp_set_request_error(reqinfo, requests, 0/* some error */);
                }
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
            snmp_log(LOG_ERR, "unknown mode (%d) in handle_pstSystemTemperatureControlMode\n", reqinfo->mode );
            return SNMP_ERR_GENERR;
    }

    return SNMP_ERR_NOERROR;
}
int
 QPSTSystem::handle_pstSystemADG707Switch(netsnmp_mib_handler *handler,
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
			{
			QPST *pst = QPST::getInstance();
            long s = pst->m_system->m_pstSystem.get_pstSystemADG707Switch();
			snmp_set_var_typed_value(requests->requestvb, ASN_INTEGER,
                                     &s/* XXX: a pointer to the scalar's data */,
                                     sizeof(s)/* XXX: the length of the data in bytes */);
            }
			break;

        /*
         * SET REQUEST
         *
         * multiple states in the transaction.  See:
         * http://www.net-snmp.org/tutorial-5/toolkit/mib_module/set-actions.jpg
         */
        case MODE_SET_RESERVE1:
                /* or you could use netsnmp_check_vb_type_and_size instead */
             {
            ret = netsnmp_check_vb_type(requests->requestvb, ASN_INTEGER);
            if ( ret != SNMP_ERR_NOERROR ) {
                netsnmp_set_request_error(reqinfo, requests, ret );
            }

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
            {

            QPST *pst = QPST::getInstance();
            long s = (long)(*requests->requestvb->val.integer);
            pst->m_system->m_pstSystem.set_pstSystemADG707Switch(s);
            if (0/* XXX: error? */) {
                netsnmp_set_request_error(reqinfo, requests, 0/* some error */);
            }

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
            snmp_log(LOG_ERR, "unknown mode (%d) in handle_pstSystemADG707Switch\n", reqinfo->mode );
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
    switch(reqinfo->mode) {

        case MODE_GET:
    	{
		
		struct sockaddr_in sa;
		QPST *pst = QPST::getInstance();
		QString s = pst->m_system->m_pstSystem.get_pstSystemFtpSrvIp();
		inet_pton(AF_INET, s.toLatin1().data(), &(sa.sin_addr));
		
		in_addr_t	it = sa.sin_addr.s_addr;
		
            snmp_set_var_typed_value(requests->requestvb, ASN_IPADDRESS,
                                     &it/* XXX: a pointer to the scalar's data */,
                                     sizeof(it)/* XXX: the length of the data in bytes */);

		}
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
    switch(reqinfo->mode) {

        case MODE_GET:
        {
            QPST *pst = QPST::getInstance();
            long s = pst->m_system->m_pstSystem.get_pstSystemUpgDstSlot();
            snmp_set_var_typed_value(requests->requestvb, ASN_INTEGER,
                                     &s/* XXX: a pointer to the scalar's data */,
                                     sizeof(s)/* XXX: the length of the data in bytes */);
        }
        break;

        /*
         * SET REQUEST
         *
         * multiple states in the transaction.  See:
         * http://www.net-snmp.org/tutorial-5/toolkit/mib_module/set-actions.jpg
         */
        case MODE_SET_RESERVE1:
            {
                /* or you could use netsnmp_check_vb_type_and_size instead */
            ret = netsnmp_check_vb_type(requests->requestvb, ASN_INTEGER);
            if ( ret != SNMP_ERR_NOERROR ) {
                netsnmp_set_request_error(reqinfo, requests, ret );
            }
            QPST *pst = QPST::getInstance();

            long s = (long)(* requests->requestvb->val.integer);
            pst->m_system->m_pstSystem.set_pstSystemUpgDstSlot(s);

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
    switch(reqinfo->mode) {

        case MODE_GET:
        {
            QPST *pst = QPST::getInstance();
            long s = pst->m_system->m_pstSystem.get_pstSystemUpgAction();
            snmp_set_var_typed_value(requests->requestvb, ASN_INTEGER,
                                     &s/* XXX: a pointer to the scalar's data */,
                                     sizeof(s)/* XXX: the length of the data in bytes */);

        }
        break;

        /*
         * SET REQUEST
         *
         * multiple states in the transaction.  See:
         * http://www.net-snmp.org/tutorial-5/toolkit/mib_module/set-actions.jpg
         */
        case MODE_SET_RESERVE1:
                /* or you could use netsnmp_check_vb_type_and_size instead */
            {
            ret = netsnmp_check_vb_type(requests->requestvb, ASN_INTEGER);
            if ( ret != SNMP_ERR_NOERROR ) {
                netsnmp_set_request_error(reqinfo, requests, ret );
            }

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
            {
            QPST *pst = QPST::getInstance();

            long s = (long)(* requests->requestvb->val.integer);
            pst->m_system->m_pstSystem.set_pstSystemUpgAction(s);


            if ((s < 0)||(s > 2)) {
                netsnmp_set_request_error(reqinfo, requests, SNMP_ERR_BADVALUE);
            }

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

    switch(reqinfo->mode) {

        case MODE_GET:
        {
            QPST *pst = QPST::getInstance();
            int slot = pst->m_system->m_pstSystem.get_pstSystemUpgDstSlot();
            long s = pst->m_system->m_pstSystem.get_pstSystemUpgStatus(slot);
            snmp_set_var_typed_value(requests->requestvb, ASN_INTEGER,
                                     &s/* XXX: a pointer to the scalar's data */,
                                     sizeof(s)/* XXX: the length of the data in bytes */);
          }
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

    switch(reqinfo->mode) {

        case MODE_GET:
        {
            QPST *pst = QPST::getInstance();
            long slot = pst->m_system->m_pstSystem.get_pstSystemUpgDstSlot();

            QString s = pst->m_system->m_pstSystem.get_pstSystemUpgResultInfo(slot);
            snmp_set_var_typed_value(requests->requestvb, ASN_OCTET_STR,
                                     s.toLatin1().data()/* XXX: a pointer to the scalar's data */,
                                     s.length()/* XXX: the length of the data in bytes */);

        }
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

// TABLE

/* create a new row in the table */
static netsnmp_tdata_row *
pstSystemTrapTargetTable_createEntry(netsnmp_tdata *table_data
                 , long  pstSystemTrapTargetName
                ) {
    struct pstSystemTrapTargetTable_entry *entry;
    netsnmp_tdata_row *row;

    entry = SNMP_MALLOC_TYPEDEF(struct pstSystemTrapTargetTable_entry);
    if (!entry)
        return NULL;

    row = netsnmp_tdata_create_row();
    if (!row) {
        SNMP_FREE(entry);
        return NULL;
    }
    row->data = entry;

    DEBUGMSGT(("pstSystemTrapTargetTable:entry:create", "row 0x%x\n", (uintptr_t)row));
    entry->pstSystemTrapTargetName = pstSystemTrapTargetName;
    netsnmp_tdata_row_add_index( row, ASN_INTEGER,
                                 &(entry->pstSystemTrapTargetName),
                                 sizeof(entry->pstSystemTrapTargetName));
    if (table_data)
        netsnmp_tdata_add_row( table_data, row );
    return row;
}

/* remove a row from the table */
static void
pstSystemTrapTargetTable_removeEntry(netsnmp_tdata     *table_data,
                 netsnmp_tdata_row *row) {
    struct pstSystemTrapTargetTable_entry *entry;

    if (!row)
        return;    /* Nothing to remove */

    DEBUGMSGT(("pstSystemTrapTargetTable:entry:remove", "row 0x%x\n", (uintptr_t)row));

    entry = (struct pstSystemTrapTargetTable_entry *)row->data;
    SNMP_FREE( entry );   /* XXX - release any other internal resources */

    if (table_data)
        netsnmp_tdata_remove_and_delete_row( table_data, row );
    else
        netsnmp_tdata_delete_row( row );    
}

/** Initialize the pstSystemTrapTargetTable table by defining its contents and how it's structured */
void
 QPSTSystem::initialize_table_pstSystemTrapTargetTable(void)
{
    const oid pstSystemTrapTargetTable_oid[] = {1,3,6,1,4,1,48391,2,1,3,2};
    const size_t pstSystemTrapTargetTable_oid_len   = OID_LENGTH(pstSystemTrapTargetTable_oid);
    netsnmp_handler_registration    *reg;
    netsnmp_tdata                   *table_data;
    netsnmp_table_registration_info *table_info;

    DEBUGMSGTL(("pstSystem:init", "initializing table pstSystemTrapTargetTable\n"));

    reg = netsnmp_create_handler_registration(
              "pstSystemTrapTargetTable",     pstSystemTrapTargetTable_handler,
              pstSystemTrapTargetTable_oid, pstSystemTrapTargetTable_oid_len,
              HANDLER_CAN_RWRITE
              );

    table_data = netsnmp_tdata_create_table( "pstSystemTrapTargetTable", 0 );
    if (NULL == table_data) {
        snmp_log(LOG_ERR,"error creating tdata table for pstSystemTrapTargetTable\n");
        return;
    }
    table_info = SNMP_MALLOC_TYPEDEF( netsnmp_table_registration_info );
    if (NULL == table_info) {
        snmp_log(LOG_ERR,"error creating table info for pstSystemTrapTargetTable\n");
        return;
    }
    netsnmp_table_helper_add_indexes(table_info,
                           ASN_INTEGER,  /* index: pstSystemTrapTargetName */
                           0);

    table_info->min_column = COLUMN_PSTSYSTEMTRAPTARGETNAME;
    table_info->max_column = COLUMN_PSTSYSTEMTRAPTARGETROWSTATUS;
    
    netsnmp_tdata_register( reg, table_data, table_info );

    /* Initialise the contents of the table here */
	QPST *p = QPST::getInstance();
	long i = 0;
	
	netsnmp_tdata_row 	*row;
    long pstSystemTrapTargetName;
    QString  targetIP;
	QString	 targetCommunity;
	struct pstSystemTrapTargetTable_entry		*entry;
    for(i = 0; i < NUMBER_OF_TRAPTARGETS; i++){
        targetIP = p->m_system->m_pstSystem.get_pstSystemTrapTargetIpAddr(i);
        targetCommunity = p->m_system->m_pstSystem.get_pstSystemTrapTargetCommunity(i);
        pstSystemTrapTargetName = i+1;
        row = pstSystemTrapTargetTable_createEntry(table_data, pstSystemTrapTargetName);

        entry = (struct pstSystemTrapTargetTable_entry *)row->data;
        entry->pstSystemTrapTargetName = pstSystemTrapTargetName;
        strcpy(entry->pstSystemTrapTargetIpAddr, targetIP.toLatin1().data());
        entry->pstSystemTrapTargetIpAddr_len = targetIP.length();
//        entry->old_pstSystemTrapTargetIpAddr = 0;
        strcpy(entry->pstSystemTrapTargetCommunity, targetCommunity.toLatin1().data());
//        strcpy(entry->old_pstSystemTrapTargetCommunity, targetCommunity.toLatin1().data());
        entry->pstSystemTrapTargetCommunity_len = targetCommunity.length();
        entry->old_pstSystemTrapTargetCommunity_len = targetCommunity.length();
        entry->pstSystemTrapTargetTrapVersion = 2;//p->m_system->m_pstSystem.get_pstSystemTrapTargetTrapVersion(i);
        entry->old_pstSystemTrapTargetTrapVersion = 2;
        entry->pstSystemTrapTargetRowStatus = i;//p->m_system->m_pstSystem.get_pstSystemTrapTargetRowStatus(i);
        entry->old_pstSystemTrapTargetRowStatus = 0;
    }

//	return table_data;


}

//    /* Typical data structure for a row entry */
//struct pstSystemTrapTargetTable_entry {
//    /* Index values */
//    char pstSystemTrapTargetName[NNN];
//    size_t pstSystemTrapTargetName_len;

//    /* Column values */
//    in_addr_t pstSystemTrapTargetIpAddr;
//    in_addr_t old_pstSystemTrapTargetIpAddr;
//    char pstSystemTrapTargetCommunity[NNN];
//    size_t pstSystemTrapTargetCommunity_len;
//    char old_pstSystemTrapTargetCommunity[NNN];
//    size_t old_pstSystemTrapTargetCommunity_len;
//    long pstSystemTrapTargetTrapVersion;
//    long old_pstSystemTrapTargetTrapVersion;
//    long pstSystemTrapTargetRowStatus;
//    long old_pstSystemTrapTargetRowStatus;

//    int   valid;
//};

/** handles requests for the pstSystemTrapTargetTable table */
int
QPSTSystem::pstSystemTrapTargetTable_handler(
    netsnmp_mib_handler               *handler,
    netsnmp_handler_registration      *reginfo,
    netsnmp_agent_request_info        *reqinfo,
    netsnmp_request_info              *requests) {

    netsnmp_request_info       *request;
    netsnmp_table_request_info *table_info;
    netsnmp_tdata              *table_data;
    netsnmp_tdata_row          *table_row;
    struct pstSystemTrapTargetTable_entry          *table_entry;
    int                         ret;

    DEBUGMSGTL(("pstSystem:handler", "Processing request (%d)\n", reqinfo->mode));

    switch (reqinfo->mode) {
        /*
         * Read-support (also covers GetNext requests)
         */
    case MODE_GET:
        for (request=requests; request; request=request->next) {
            if (request->processed)
                continue;

            table_entry = (struct pstSystemTrapTargetTable_entry *)
                              netsnmp_tdata_extract_entry(request);
            table_info  =     netsnmp_extract_table_info( request);
    
            switch (table_info->colnum) {
            case COLUMN_PSTSYSTEMTRAPTARGETNAME:
                if ( !table_entry ) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_NOSUCHINSTANCE);
                    continue;
                }
                snmp_set_var_typed_integer( request->requestvb, ASN_INTEGER,
                                            table_entry->pstSystemTrapTargetName);
                break;
            case COLUMN_PSTSYSTEMTRAPTARGETIPADDR:
            {
                if ( !table_entry ) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_NOSUCHINSTANCE);
                    continue;
                }

                QPST *pst = QPST::getInstance();
                int index  = table_entry->pstSystemTrapTargetName;
                if( 0 < index <= NUMBER_OF_TRAPTARGETS){
                QString s = pst->m_system->m_pstSystem.get_pstSystemTrapTargetIpAddr(index);

                snmp_set_var_typed_value( request->requestvb, ASN_OCTET_STR,
                                          s.toLatin1().data(),
                                          s.length()/*table_entry->pstSystemTrapTargetIpAddr*/);
                }
            }
                break;
            case COLUMN_PSTSYSTEMTRAPTARGETCOMMUNITY:
            {
                if ( !table_entry ) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_NOSUCHINSTANCE);
                    continue;
                }
                QPST *pst = QPST::getInstance();
                int index  = table_entry->pstSystemTrapTargetName;
                if( 0 < index <= NUMBER_OF_TRAPTARGETS){

                QString s = pst->m_system->m_pstSystem.get_pstSystemTrapTargetCommunity(index);

                snmp_set_var_typed_value( request->requestvb, ASN_OCTET_STR,
                                          s.toLatin1().data(),
                                          s.length()
                                          /*table_entry->pstSystemTrapTargetCommunity,
                                          table_entry->pstSystemTrapTargetCommunity_len*/);
                }
            }
                break;
            case COLUMN_PSTSYSTEMTRAPTARGETTRAPVERSION:
                if ( !table_entry ) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_NOSUCHINSTANCE);
                    continue;
                }
                snmp_set_var_typed_integer( request->requestvb, ASN_INTEGER,
                                            table_entry->pstSystemTrapTargetTrapVersion);
                break;
            case COLUMN_PSTSYSTEMTRAPTARGETROWSTATUS:
                if ( !table_entry ) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_NOSUCHINSTANCE);
                    continue;
                }
                snmp_set_var_typed_integer( request->requestvb, ASN_INTEGER,
                                            table_entry->pstSystemTrapTargetRowStatus);
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

            table_entry = (struct pstSystemTrapTargetTable_entry *)
                              netsnmp_tdata_extract_entry(request);
            table_info  =     netsnmp_extract_table_info( request);
    
            switch (table_info->colnum) {
            case COLUMN_PSTSYSTEMTRAPTARGETIPADDR:
                /* or possibly 'netsnmp_check_vb_int_range' */
            {
                ret = netsnmp_check_vb_type_and_max_size(
                          request->requestvb, ASN_OCTET_STR, sizeof(table_entry->pstSystemTrapTargetIpAddr));
                if ( ret != SNMP_ERR_NOERROR ) {
                    netsnmp_set_request_error( reqinfo, request, ret );
                    return SNMP_ERR_NOERROR;
                }
                QPST *pst = QPST::getInstance();
                int index  = table_entry->pstSystemTrapTargetName;
                if( 0 < index <= NUMBER_OF_TRAPTARGETS){

//                in_addr_t s = (in_addr_t)(*request->requestvb->val.integer);
//                char *ip = inet_ntoa(*((struct in_addr*)&s));
//                QString qip = QString("%1").arg(ip);
                char *cs = (char*)request->requestvb->val.string;
                QString qs = QString("%1").arg(cs);
                pst->m_system->m_pstSystem.set_pstSystemTrapTargetIpAddr(index, qs);
                pst->TrapTargetsChanged();
                }
            }
                break;
            case COLUMN_PSTSYSTEMTRAPTARGETCOMMUNITY:
	        /* or possibly 'netsnmp_check_vb_type_and_size' */
            {
                ret = netsnmp_check_vb_type_and_max_size(
                          request->requestvb, ASN_OCTET_STR, sizeof(table_entry->pstSystemTrapTargetCommunity));
                if ( ret != SNMP_ERR_NOERROR ) {
                    netsnmp_set_request_error( reqinfo, request, ret );
                    return SNMP_ERR_NOERROR;
                }
                QPST *pst = QPST::getInstance();
                int index  = table_entry->pstSystemTrapTargetName;
                if( 0 < index <= NUMBER_OF_TRAPTARGETS){
                char *cs = (char*)request->requestvb->val.string;
                QString qs = QString("%1").arg(cs);

                pst->m_system->m_pstSystem.set_pstSystemTrapTargetCommunity(index, qs);
                pst->TrapTargetsChanged();
                }
            }
                break;
            case COLUMN_PSTSYSTEMTRAPTARGETTRAPVERSION:
                /* or possibly 'netsnmp_check_vb_int_range' */
                ret = netsnmp_check_vb_int( request->requestvb );
                if ( ret != SNMP_ERR_NOERROR ) {
                    netsnmp_set_request_error( reqinfo, request, ret );
                    return SNMP_ERR_NOERROR;
                }
                break;
            case COLUMN_PSTSYSTEMTRAPTARGETROWSTATUS:
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
        for (request=requests; request; request=request->next) {
            if (request->processed)
                continue;

            table_row  = netsnmp_tdata_extract_row(  request);
            table_data = netsnmp_tdata_extract_table(request);
            table_info = netsnmp_extract_table_info( request);
    
            switch (table_info->colnum) {
            case COLUMN_PSTSYSTEMTRAPTARGETROWSTATUS:
                if ( !table_row ) {
                    table_row = pstSystemTrapTargetTable_createEntry(table_data
                        , *table_info->indexes->val.integer
                        );
                    if (table_row) {
                        netsnmp_insert_tdata_row( request, table_row );
                    } else {
                        netsnmp_set_request_error( reqinfo, request,
                                                   SNMP_ERR_RESOURCEUNAVAILABLE );
                        return SNMP_ERR_NOERROR;
                    }
                }
                break;
            }
        }
        break;

    case MODE_SET_FREE:
        for (request=requests; request; request=request->next) {
            if (request->processed)
                continue;

            table_entry = (struct pstSystemTrapTargetTable_entry *)
                              netsnmp_tdata_extract_entry(request);
            table_row   =     netsnmp_tdata_extract_row(  request);
            table_data  =     netsnmp_tdata_extract_table(request);
            table_info  =     netsnmp_extract_table_info( request);
    
            switch (table_info->colnum) {
            case COLUMN_PSTSYSTEMTRAPTARGETROWSTATUS:
                if ( table_entry && !table_entry->valid ) {
                    pstSystemTrapTargetTable_removeEntry(table_data, table_row );
                }
                break;
            }
        }
        break;

    case MODE_SET_ACTION:
//        for (request=requests; request; request=request->next) {
//            if (request->processed)
//                continue;

//            table_entry = (struct pstSystemTrapTargetTable_entry *)
//                              netsnmp_tdata_extract_entry(request);
//            table_info  =     netsnmp_extract_table_info( request);
    
//            switch (table_info->colnum) {
//            case COLUMN_PSTSYSTEMTRAPTARGETIPADDR:
//                memcpy( table_entry->old_pstSystemTrapTargetIpAddr,
//                        table_entry->pstSystemTrapTargetIpAddr,
//                        sizeof(table_entry->pstSystemTrapTargetIpAddr));
//                table_entry->old_pstSystemTrapTargetIpAddr_len =
//                        table_entry->pstSystemTrapTargetIpAddr_len;
//                memset( table_entry->pstSystemTrapTargetIpAddr, 0,
//                        sizeof(table_entry->pstSystemTrapTargetIpAddr));
//                memcpy( table_entry->pstSystemTrapTargetIpAddr,
//                        request->requestvb->val.string,
//                        request->requestvb->val_len);
//                table_entry->pstSystemTrapTargetIpAddr_len =
//                        request->requestvb->val_len;
//                break;
//            case COLUMN_PSTSYSTEMTRAPTARGETCOMMUNITY:
//                memcpy( table_entry->old_pstSystemTrapTargetCommunity,
//                        table_entry->pstSystemTrapTargetCommunity,
//                        sizeof(table_entry->pstSystemTrapTargetCommunity));
//                table_entry->old_pstSystemTrapTargetCommunity_len =
//                        table_entry->pstSystemTrapTargetCommunity_len;
//                memset( table_entry->pstSystemTrapTargetCommunity, 0,
//                        sizeof(table_entry->pstSystemTrapTargetCommunity));
//                memcpy( table_entry->pstSystemTrapTargetCommunity,
//                        request->requestvb->val.string,
//                        request->requestvb->val_len);
//                table_entry->pstSystemTrapTargetCommunity_len =
//                        request->requestvb->val_len;
//                break;
//            case COLUMN_PSTSYSTEMTRAPTARGETTRAPVERSION:
//                table_entry->old_pstSystemTrapTargetTrapVersion = table_entry->pstSystemTrapTargetTrapVersion;
//                table_entry->pstSystemTrapTargetTrapVersion     = *request->requestvb->val.integer;
//                break;
//            case COLUMN_PSTSYSTEMTRAPTARGETROWSTATUS:
//                table_entry->old_pstSystemTrapTargetRowStatus = table_entry->pstSystemTrapTargetRowStatus;
//                table_entry->pstSystemTrapTargetRowStatus     = *request->requestvb->val.integer;
//                break;
//            }
//        }
        break;

    case MODE_SET_UNDO:
//        for (request=requests; request; request=request->next) {
//            if (request->processed)
//                continue;

//            table_entry = (struct pstSystemTrapTargetTable_entry *)
//                              netsnmp_tdata_extract_entry(request);
//            table_row   =     netsnmp_tdata_extract_row(  request);
//            table_data  =     netsnmp_tdata_extract_table(request);
//            table_info  =     netsnmp_extract_table_info( request);
    
//            switch (table_info->colnum) {
//            case COLUMN_PSTSYSTEMTRAPTARGETIPADDR:
//                memcpy( table_entry->pstSystemTrapTargetIpAddr,
//                        table_entry->old_pstSystemTrapTargetIpAddr,
//                        sizeof(table_entry->pstSystemTrapTargetIpAddr));
//                memset( table_entry->old_pstSystemTrapTargetIpAddr, 0,
//                        sizeof(table_entry->pstSystemTrapTargetIpAddr));
//                table_entry->pstSystemTrapTargetIpAddr_len =
//                        table_entry->old_pstSystemTrapTargetIpAddr_len;
//                break;
//            case COLUMN_PSTSYSTEMTRAPTARGETCOMMUNITY:
//                memcpy( table_entry->pstSystemTrapTargetCommunity,
//                        table_entry->old_pstSystemTrapTargetCommunity,
//                        sizeof(table_entry->pstSystemTrapTargetCommunity));
//                memset( table_entry->old_pstSystemTrapTargetCommunity, 0,
//                        sizeof(table_entry->pstSystemTrapTargetCommunity));
//                table_entry->pstSystemTrapTargetCommunity_len =
//                        table_entry->old_pstSystemTrapTargetCommunity_len;
//                break;
//            case COLUMN_PSTSYSTEMTRAPTARGETTRAPVERSION:
//                table_entry->pstSystemTrapTargetTrapVersion     = table_entry->old_pstSystemTrapTargetTrapVersion;
//                table_entry->old_pstSystemTrapTargetTrapVersion = 0;
//                break;
//            case COLUMN_PSTSYSTEMTRAPTARGETROWSTATUS:
//                if ( table_entry && !table_entry->valid ) {
//                    pstSystemTrapTargetTable_removeEntry(table_data, table_row );
//                } else {
//                    table_entry->pstSystemTrapTargetRowStatus     = table_entry->old_pstSystemTrapTargetRowStatus;
//                    table_entry->old_pstSystemTrapTargetRowStatus = 0;
//                }
//                break;
//            }
//        }
        break;

    case MODE_SET_COMMIT:
        for (request=requests; request; request=request->next) {
            if (request->processed)
                continue;

            table_entry = (struct pstSystemTrapTargetTable_entry *)
                              netsnmp_tdata_extract_entry(request);
            table_info  =     netsnmp_extract_table_info(    request);
    
            switch (table_info->colnum) {
            case COLUMN_PSTSYSTEMTRAPTARGETROWSTATUS:
                if ( table_entry && !table_entry->valid ) {
                    table_entry->valid = 1;
                }
            }
        }
        break;
    }
    return SNMP_ERR_NOERROR;
}

/* create a new row in the table */
static netsnmp_tdata_row *
pstSystemFanTable_createEntry(netsnmp_tdata *table_data
                 , long  pstSystemFanIndex
                ) {
    struct pstSystemFanTable_entry *entry;
    netsnmp_tdata_row *row;

    entry = SNMP_MALLOC_TYPEDEF(struct pstSystemFanTable_entry);
    if (!entry)
        return NULL;

    row = netsnmp_tdata_create_row();
    if (!row) {
        SNMP_FREE(entry);
        return NULL;
    }
    row->data = entry;

    DEBUGMSGT(("pstSystemFanTable:entry:create", "row 0x%x\n", (uintptr_t)row));
    entry->pstSystemFanIndex = pstSystemFanIndex;
    netsnmp_tdata_row_add_index( row, ASN_INTEGER,
                                 &(entry->pstSystemFanIndex),
                                 sizeof(entry->pstSystemFanIndex));
    if (table_data)
        netsnmp_tdata_add_row( table_data, row );
    return row;
}

/* remove a row from the table */
static void
pstSystemFanTable_removeEntry(netsnmp_tdata     *table_data,
                 netsnmp_tdata_row *row) {
    struct pstSystemFanTable_entry *entry;

    if (!row)
        return;    /* Nothing to remove */

    DEBUGMSGT(("pstSystemFanTable:entry:remove", "row 0x%x\n", (uintptr_t)row));

    entry = (struct pstSystemFanTable_entry *)row->data;
    SNMP_FREE( entry );   /* XXX - release any other internal resources */

    if (table_data)
        netsnmp_tdata_remove_and_delete_row( table_data, row );
    else
        netsnmp_tdata_delete_row( row );
}

/** Initialize the pstSystemFanTable table by defining its contents and how it's structured */
void
QPSTSystem::initialize_table_pstSystemFanTable(void)
{
    const oid pstSystemFanTable_oid[] = {1,3,6,1,4,1,48391,2,1,4,3};
    const size_t pstSystemFanTable_oid_len   = OID_LENGTH(pstSystemFanTable_oid);
    netsnmp_handler_registration    *reg;
    netsnmp_tdata                   *table_data;
    netsnmp_table_registration_info *table_info;

    DEBUGMSGTL(("pstSystem:init", "initializing table pstSystemFanTable\n"));

    reg = netsnmp_create_handler_registration(
              "pstSystemFanTable",     pstSystemFanTable_handler,
              pstSystemFanTable_oid, pstSystemFanTable_oid_len,
              HANDLER_CAN_RONLY
              );

    table_data = netsnmp_tdata_create_table( "pstSystemFanTable", 0 );
    if (NULL == table_data) {
        snmp_log(LOG_ERR,"error creating tdata table for pstSystemFanTable\n");
        return;
    }
    table_info = SNMP_MALLOC_TYPEDEF( netsnmp_table_registration_info );
    if (NULL == table_info) {
        snmp_log(LOG_ERR,"error creating table info for pstSystemFanTable\n");
        return;
    }
    netsnmp_table_helper_add_indexes(table_info,
                           ASN_INTEGER,  /* index: pstSystemFanIndex */
                           0);

    table_info->min_column = COLUMN_PSTSYSTEMFANINDEX;
    table_info->max_column = COLUMN_PSTSYSTEMFANSPEED;
    
    netsnmp_tdata_register( reg, table_data, table_info );

    /* Initialise the contents of the table here */
    long i= 0;
	netsnmp_tdata_row 	*row;

	struct pstSystemFanTable_entry		*entry;
	for(i = 0; i < NUMBER_OF_FANS; i++){
        row = pstSystemFanTable_createEntry(table_data, i+1);

        entry = (struct pstSystemFanTable_entry *)row->data;
        entry->pstSystemFanIndex= i+1;
		entry->pstSystemFanSpeed=255;
		entry->pstSystemFanStatus=0;
		}
}

//    /* Typical data structure for a row entry */
//struct pstSystemFanTable_entry {
//    /* Index values */
//    long pstSystemFanIndex;

//    /* Column values */
//    long pstSystemFanIndex;
//    long pstSystemFanStatus;
//    long pstSystemFanSpeed;

//    int   valid;
//};

/** handles requests for the pstSystemFanTable table */
int
QPSTSystem::pstSystemFanTable_handler(
    netsnmp_mib_handler               *handler,
    netsnmp_handler_registration      *reginfo,
    netsnmp_agent_request_info        *reqinfo,
    netsnmp_request_info              *requests) {

    netsnmp_request_info       *request;
    netsnmp_table_request_info *table_info;
    netsnmp_tdata              *table_data;
    netsnmp_tdata_row          *table_row;
    struct pstSystemFanTable_entry          *table_entry;
    int                         ret;

    DEBUGMSGTL(("pstSystem:handler", "Processing request (%d)\n", reqinfo->mode));

    switch (reqinfo->mode) {
        /*
         * Read-support (also covers GetNext requests)
         */
    case MODE_GET:
        for (request=requests; request; request=request->next) {
            if (request->processed)
                continue;

            table_entry = (struct pstSystemFanTable_entry *)
                              netsnmp_tdata_extract_entry(request);
            table_info  =     netsnmp_extract_table_info( request);
    
            switch (table_info->colnum) {
            case COLUMN_PSTSYSTEMFANINDEX:
                if ( !table_entry ) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_NOSUCHINSTANCE);
                    continue;
                }
                snmp_set_var_typed_integer( request->requestvb, ASN_INTEGER,
                                            table_entry->pstSystemFanIndex);
                break;
            case COLUMN_PSTSYSTEMFANSTATUS:
            {
                 if ( !table_entry ) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_NOSUCHINSTANCE);
                    continue;
                }

                QPST *pst = QPST::getInstance();
                long index = table_entry->pstSystemFanIndex;
                if(0 < index <=4){
                    long s = pst->m_system->m_pstSystem.get_pstSystemFanStatus(index);
                    snmp_set_var_typed_integer( request->requestvb, ASN_INTEGER,
                                                s/*table_entry->pstSystemFanStatus*/);
                }

            }
                break;
            case COLUMN_PSTSYSTEMFANSPEED:
            {
                if ( !table_entry ) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_NOSUCHINSTANCE);
                    continue;
                }

                QPST *pst = QPST::getInstance();
                long index = table_entry->pstSystemFanIndex;
                if(0 < index <=4){
                    long s = pst->m_system->m_pstSystem.get_pstSystemFanSpeed(index);
                    snmp_set_var_typed_integer( request->requestvb, ASN_INTEGER,
                                                s/*table_entry->pstSystemFanStatus*/);
                }
             }
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

/* create a new row in the table */
static netsnmp_tdata_row *
pstSystemPowerTable_createEntry(netsnmp_tdata *table_data
                 , char* pstSystemPowerIndex
                 , size_t pstSystemPowerIndex_len
                ) {
    struct pstSystemPowerTable_entry *entry;
    netsnmp_tdata_row *row;

    entry = SNMP_MALLOC_TYPEDEF(struct pstSystemPowerTable_entry);
    if (!entry)
        return NULL;

    row = netsnmp_tdata_create_row();
    if (!row) {
        SNMP_FREE(entry);
        return NULL;
    }
    row->data = entry;

    DEBUGMSGT(("pstSystemPowerTable:entry:create", "row 0x%x\n", (uintptr_t)row));
    memcpy(entry->pstSystemPowerIndex, pstSystemPowerIndex, pstSystemPowerIndex_len);
    entry->pstSystemPowerIndex_len = pstSystemPowerIndex_len;
    netsnmp_tdata_row_add_index( row, ASN_OCTET_STR,
                                 entry->pstSystemPowerIndex, pstSystemPowerIndex_len);
    if (table_data)
        netsnmp_tdata_add_row( table_data, row );
    return row;
}

/* remove a row from the table */
static void
pstSystemPowerTable_removeEntry(netsnmp_tdata     *table_data,
                 netsnmp_tdata_row *row) {
    struct pstSystemPowerTable_entry *entry;

    if (!row)
        return;    /* Nothing to remove */

    DEBUGMSGT(("pstSystemPowerTable:entry:remove", "row 0x%x\n", (uintptr_t)row));

    entry = (struct pstSystemPowerTable_entry *)row->data;
    SNMP_FREE( entry );   /* XXX - release any other internal resources */

    if (table_data)
        netsnmp_tdata_remove_and_delete_row( table_data, row );
    else
        netsnmp_tdata_delete_row( row );
}


/** Initialize the pstSystemPowerTable table by defining its contents and how it's structured */
void
QPSTSystem::initialize_table_pstSystemPowerTable(void)
{
    const oid pstSystemPowerTable_oid[] = {1,3,6,1,4,1,48391,2,1,4,4};
    const size_t pstSystemPowerTable_oid_len   = OID_LENGTH(pstSystemPowerTable_oid);
    netsnmp_handler_registration    *reg;
    netsnmp_tdata                   *table_data;
    netsnmp_table_registration_info *table_info;

    DEBUGMSGTL(("pstSystem:init", "initializing table pstSystemPowerTable\n"));

    reg = netsnmp_create_handler_registration(
              "pstSystemPowerTable",     pstSystemPowerTable_handler,
              pstSystemPowerTable_oid, pstSystemPowerTable_oid_len,
              HANDLER_CAN_RONLY
              );

    table_data = netsnmp_tdata_create_table( "pstSystemPowerTable", 0 );
    if (NULL == table_data) {
        snmp_log(LOG_ERR,"error creating tdata table for pstSystemPowerTable\n");
        return;
    }
    table_info = SNMP_MALLOC_TYPEDEF( netsnmp_table_registration_info );
    if (NULL == table_info) {
        snmp_log(LOG_ERR,"error creating table info for pstSystemPowerTable\n");
        return;
    }
    netsnmp_table_helper_add_indexes(table_info,
                           ASN_OCTET_STR,  /* index: pstSystemPowerIndex */
                           0);

    table_info->min_column = COLUMN_PSTSYSTEMPOWERINDEX;
    table_info->max_column = COLUMN_PSTSYSTEMPOWERVOLTAGE1V8RTC;
    
    netsnmp_tdata_register( reg, table_data, table_info );

    /* Initialise the contents of the table here */
    long i= 0;
    netsnmp_tdata_row 	*row;

    struct pstSystemPowerTable_entry		*entry;
    for(i = 0; i < 1; i++){
        row = pstSystemPowerTable_createEntry(table_data, "1", 1);

        entry = (struct pstSystemPowerTable_entry *)row->data;
        strcpy(entry->pstSystemPowerIndex, "1");
        entry->pstSystemPowerIndex_len = 1;
        strcpy(entry->pstSystemPowerMaximumConsumption, "45");
        entry->pstSystemPowerMaximumConsumption_len = 2;
        strcpy(entry->pstSystemPowerVoltage12VA,"0");
        entry->pstSystemPowerVoltage12VA_len = 1;
        strcpy(entry->pstSystemPowerVoltage12VB,"0");
        entry->pstSystemPowerVoltage12VB_len = 1;
        strcpy(entry->pstSystemPowerVoltage12VFAN,"0");
        entry->pstSystemPowerVoltage12VFAN_len = 1;
        strcpy(entry->pstSystemPowerVoltage12VOTDR1,"0");
        entry->pstSystemPowerVoltage12VOTDR1_len = 1;
        strcpy(entry->pstSystemPowerVoltage12VOTDR2,"0");
        entry->pstSystemPowerVoltage12VOTDR2_len = 1;
        strcpy(entry->pstSystemPowerVoltageVDD5V ,"0");
        entry->pstSystemPowerVoltageVDD5V_len = 1;
        strcpy(entry->pstSystemPowerVoltageVDD3V3,"0");
        entry->pstSystemPowerVoltageVDD3V3_len = 1;
        strcpy(entry->pstSystemPowerVoltage1V8RTC,"0");
        entry->pstSystemPowerVoltage1V8RTC_len = 1;
       }
}

//    /* Typical data structure for a row entry */
//struct pstSystemPowerTable_entry {
//    /* Index values */
//    char pstSystemPowerIndex[NNN];
//    size_t pstSystemPowerIndex_len;

//    /* Column values */
//    char pstSystemPowerIndex[NNN];
//    size_t pstSystemPowerIndex_len;
//    char pstSystemPowerMaximumConsumption[NNN];
//    size_t pstSystemPowerMaximumConsumption_len;
//    char pstSystemPowerVoltage12VA[NNN];
//    size_t pstSystemPowerVoltage12VA_len;
//    char pstSystemPowerVoltage12VB[NNN];
//    size_t pstSystemPowerVoltage12VB_len;
//    char pstSystemPowerVoltage12VFAN[NNN];
//    size_t pstSystemPowerVoltage12VFAN_len;
//    char pstSystemPowerVoltage12VOTDR1[NNN];
//    size_t pstSystemPowerVoltage12VOTDR1_len;
//    char pstSystemPowerVoltage12VOTDR2[NNN];
//    size_t pstSystemPowerVoltage12VOTDR2_len;
//    char pstSystemPowerVoltageVDD5V[NNN];
//    size_t pstSystemPowerVoltageVDD5V_len;
//    char pstSystemPowerVoltageVDD3V3[NNN];
//    size_t pstSystemPowerVoltageVDD3V3_len;
//    char pstSystemPowerVoltage1V8RTC[NNN];
//    size_t pstSystemPowerVoltage1V8RTC_len;

//    int   valid;
//};

/** handles requests for the pstSystemPowerTable table */
int
QPSTSystem::pstSystemPowerTable_handler(
    netsnmp_mib_handler               *handler,
    netsnmp_handler_registration      *reginfo,
    netsnmp_agent_request_info        *reqinfo,
    netsnmp_request_info              *requests) {

    netsnmp_request_info       *request;
    netsnmp_table_request_info *table_info;
    netsnmp_tdata              *table_data;
    netsnmp_tdata_row          *table_row;
    struct pstSystemPowerTable_entry          *table_entry;
    int                         ret;

    DEBUGMSGTL(("pstSystem:handler", "Processing request (%d)\n", reqinfo->mode));

    switch (reqinfo->mode) {
        /*
         * Read-support (also covers GetNext requests)
         */
    case MODE_GET:
        for (request=requests; request; request=request->next) {
            if (request->processed)
                continue;

            table_entry = (struct pstSystemPowerTable_entry *)
                              netsnmp_tdata_extract_entry(request);
            table_info  =     netsnmp_extract_table_info( request);
    
            switch (table_info->colnum) {
            case COLUMN_PSTSYSTEMPOWERINDEX:
                if ( !table_entry ) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_NOSUCHINSTANCE);
                    continue;
                }
                snmp_set_var_typed_value( request->requestvb, ASN_OCTET_STR,
                                          table_entry->pstSystemPowerIndex,
                                          table_entry->pstSystemPowerIndex_len);
                break;
            case COLUMN_PSTSYSTEMPOWERMAXIMUMCONSUMPTION:
                if ( !table_entry ) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_NOSUCHINSTANCE);
                    continue;
                }
                snmp_set_var_typed_value( request->requestvb, ASN_OCTET_STR,
                                          table_entry->pstSystemPowerMaximumConsumption,
                                          table_entry->pstSystemPowerMaximumConsumption_len);
                break;
            case COLUMN_PSTSYSTEMPOWERVOLTAGE12VA:
            {
                if ( !table_entry ) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_NOSUCHINSTANCE);
                    continue;
                }
                QPST *pst = QPST::getInstance();
                QString s =  pst->m_system->m_pstSystem.get_pstSystemPowerVoltage12VA(1);

                snmp_set_var_typed_value( request->requestvb, ASN_OCTET_STR,
                                          s.toLatin1().data(),
                                          s.length()/*table_entry->pstSystemPowerVoltage12VA,
                                          table_entry->pstSystemPowerVoltage12VA_len*/);
            }
                break;
            case COLUMN_PSTSYSTEMPOWERVOLTAGE12VB:
            {
                if ( !table_entry ) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_NOSUCHINSTANCE);
                    continue;
                }
                QPST *pst = QPST::getInstance();
                QString s =  pst->m_system->m_pstSystem.get_pstSystemPowerVoltage12VB(1);

                snmp_set_var_typed_value( request->requestvb, ASN_OCTET_STR,
                                          s.toLatin1().data(),
                                          s.length()/*table_entry->pstSystemPowerVoltage12VA,
                                          table_entry->pstSystemPowerVoltage12VA_len*/);
            }

                break;
            case COLUMN_PSTSYSTEMPOWERVOLTAGE12VFAN:
            {
                if ( !table_entry ) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_NOSUCHINSTANCE);
                    continue;
                }
                QPST *pst = QPST::getInstance();
                QString s =  pst->m_system->m_pstSystem.get_pstSystemPowerVoltage12VFAN(1);

                snmp_set_var_typed_value( request->requestvb, ASN_OCTET_STR,
                                          s.toLatin1().data(),
                                          s.length()/*table_entry->pstSystemPowerVoltage12VA,
                                          table_entry->pstSystemPowerVoltage12VA_len*/);

            }
                break;
            case COLUMN_PSTSYSTEMPOWERVOLTAGE12VOTDR1:
            {
                if ( !table_entry ) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_NOSUCHINSTANCE);
                    continue;
                }
                QPST *pst = QPST::getInstance();
                QString s =  pst->m_system->m_pstSystem.get_pstSystemPowerVoltage12VOTDR1(1);

                snmp_set_var_typed_value( request->requestvb, ASN_OCTET_STR,
                                          s.toLatin1().data(),
                                          s.length()/*table_entry->pstSystemPowerVoltage12VA,
                                          table_entry->pstSystemPowerVoltage12VA_len*/);

              }
                break;
            case COLUMN_PSTSYSTEMPOWERVOLTAGE12VOTDR2:
            {
                if ( !table_entry ) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_NOSUCHINSTANCE);
                    continue;
                }
                QPST *pst = QPST::getInstance();
                QString s =  pst->m_system->m_pstSystem.get_pstSystemPowerVoltage12VOTDR2(1);

                snmp_set_var_typed_value( request->requestvb, ASN_OCTET_STR,
                                          s.toLatin1().data(),
                                          s.length()/*table_entry->pstSystemPowerVoltage12VA,
                                          table_entry->pstSystemPowerVoltage12VA_len*/);

           }
                break;
            case COLUMN_PSTSYSTEMPOWERVOLTAGEVDD5V:
            {
                if ( !table_entry ) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_NOSUCHINSTANCE);
                    continue;
                }
                QPST *pst = QPST::getInstance();
                QString s =  pst->m_system->m_pstSystem.get_pstSystemPowerVoltageVDD5V(1);

                snmp_set_var_typed_value( request->requestvb, ASN_OCTET_STR,
                                          s.toLatin1().data(),
                                          s.length()/*table_entry->pstSystemPowerVoltage12VA,
                                          table_entry->pstSystemPowerVoltage12VA_len*/);
             }
                break;
            case COLUMN_PSTSYSTEMPOWERVOLTAGEVDD3V3:
            {
                if ( !table_entry ) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_NOSUCHINSTANCE);
                    continue;
                }
                QPST *pst = QPST::getInstance();
                QString s =  pst->m_system->m_pstSystem.get_pstSystemPowerVoltageVDD3V3(1);

                snmp_set_var_typed_value( request->requestvb, ASN_OCTET_STR,
                                          s.toLatin1().data(),
                                          s.length()/*table_entry->pstSystemPowerVoltage12VA,
                                          table_entry->pstSystemPowerVoltage12VA_len*/);

           }
                break;
            case COLUMN_PSTSYSTEMPOWERVOLTAGE1V8RTC:
            {
                if ( !table_entry ) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_NOSUCHINSTANCE);
                    continue;
                }
                QPST *pst = QPST::getInstance();
                QString s =  pst->m_system->m_pstSystem.get_pstSystemPowerVoltage1V8RTC(1);

                snmp_set_var_typed_value( request->requestvb, ASN_OCTET_STR,
                                          s.toLatin1().data(),
                                          s.length()/*table_entry->pstSystemPowerVoltage12VA,
                                          table_entry->pstSystemPowerVoltage12VA_len*/);

           }

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
