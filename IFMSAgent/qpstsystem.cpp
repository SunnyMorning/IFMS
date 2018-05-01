#include "qpstsystem.h"

static oid reboot_oid[] = {1,3,6,1,4,1,48391,2,1,1,7,0};

QPSTSystem::QPSTSystem(QObject *parent) : QObject(parent)
{
    _agent = (QAgentApp*)parent;
}

int QPSTSystem::handle_reboot(netsnmp_mib_handler *handler, \
                               netsnmp_handler_registration *refinfo, \
                               netsnmp_agent_request_info   *reqinfo, \
                               netsnmp_request_info *requests)
{
    int rc = SNMP_ERR_NOERROR;

    switch(reqinfo->mode){

    case MODE_GET:
            {
                QMutexLocker    locker(&mutex);
                snmp_set_var_value(requests->requestvb, &reboot, sizeof(reboot));
            }
            break;
    case MODE_SET_RESERVE1:
            break;
    case MODE_SET_RESERVE2:
            break;
    case MODE_SET_ACTION:
        if(*requests->requestvb->val.integer == 1){
            QMutexLocker locker(&mutex);
            reboot = 1;
        }
        break;
    case MODE_SET_COMMIT:

        break;
    case MODE_SET_FREE:
        if(*requests->requestvb->val.integer == 1){
            QMutexLocker locker(&mutex);
            reboot = 1;
        }
        break;
    default:
        return SNMP_ERR_GENERR;
    }

    return rc;
}

void QPSTSystem::init_pstObjects()
{
    netsnmp_register_long_instance("reboot", reboot_oid, OID_LENGTH(reboot_oid),&reboot, handle_reboot);
}
