#include "qpst.h"


QPST::QPST(QObject *agent)
{
    _agent = agent;
    _product = new QPSTProduct(agent);
    _system  = new QPSTSystem(agent);
    _keeprunning = 1;
}

QPST::~QPST()
{

}

void QPST::initConnections()
{
    connect(this, SIGNAL(sigOTDRChanged(quint16,quint16)), this, SLOT(onSigOTDRChanged(quint16,quint16)), Qt::DirectConnection);
    connect(this, SIGNAL(sigOTDRTrap(quint16,QByteArray&)), this, SLOT(onSigOTDRTrap(quint16,QByteArray&)), Qt::DirectConnection);
}

void QPST::onSigOTDRChanged(quint16 module, quint16 channel)
{

}

void QPST::onSigOTDRTrap(quint16 module, QByteArray &data)
{

}
