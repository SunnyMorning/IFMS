#include "qpstproduct.h"

QPSTProduct::QPSTProduct(QObject *parent) : QObject(parent)
{
    _agent = (QAgentApp*)parent;
}

void QPSTProduct::init_pstObjects()
{

}
