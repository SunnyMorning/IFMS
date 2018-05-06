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

void QPST::onSigOTDRChanged(quint16 module, quint16 channel)
{

}

void QPST::onSigOTDRTrap(quint16 module, QByteArray &data)
{

}

void QPST::onSigSetProgress(quint16 module, quint16 progress)
{
    m_product->setModuleMeasuringProgess(module, progress);
}
