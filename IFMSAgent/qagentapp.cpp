#include <QFile>
#include <QDir>
#include <QDebug>
#include <QString>
#include <QCoreApplication>
#include <QThreadPool>
#include <QThread>
#include <QByteArray>
#include <QDataStream>
#include <QIODevice>
#include <QSettings>
#include <QVariant>
#include <QMutex>
#include <QMutexLocker>

#include "qagentapp.h"
#include "qcommander.h"
#include "qpst.h"

#define DATA_DIR    D_RES_DIR
#define IFMS_AGENT_NAME     "ifms"

static void initDir(const QString &path)
{
    QDir dir;
    if (!dir.exists(path)) dir.mkpath(path);
}

static QMutex   gAgentApp_mutex;
static quint16  _currentModule;

QString QAgentApp::getAppName()     { return QString(IFMS_AGENT_NAME); }

QString QAgentApp::getConfigDir()   { return QDir::homePath() + "/.config/" + getAppName() + "/"; }
QString QAgentApp::getCacheDir()    { return QDir::homePath() + "/.cache/"  + getAppName() + "/"; }
QString QAgentApp::getDataDir()     { return QString(DATA_DIR); }

QString QAgentApp::getConfigFile()  { return getConfigDir() + "settings.ini"; }

QAgentApp::QAgentApp(int &argc, char **argv)
          :QCoreApplication(argc,argv)
{

}

QAgentApp::~QAgentApp()
{

}

bool QAgentApp::startSession(int &argc, char **argv)
{
    bool ret = false;

    initAppData();

    _module1 = new QOTDRModule(this, 0);
    _module1->initModuleFingerData();
    _module1->setConnections();


    _module2 = new QOTDRModule(this, 1);
    _module2->initModuleFingerData();
    _module2->setConnections();

    command_thread = new QCommander(this);
    command_thread->start();

    pstThread = new QPST(this);
    pstThread->initConnections();
    pstThread->start();

    connect(command_thread, SIGNAL(sigExit(qint32)), this, SLOT(onSigExit(qint32)));
    connect(command_thread, SIGNAL(sigSwitchModule(quint16)), this, SLOT(onSwitchModule(quint16)));

    connect(command_thread, SIGNAL(sigModuleRecvResponse(quint16,QString&,QByteArray&)), this, SIGNAL(sigModuleRecvResponse(quint16,QString&,QByteArray&)));
    connect(command_thread, SIGNAL(sigSendCommandToModule(quint16,QString&)), this, SIGNAL(sigSendCommandToModule(quint16, QString&)));
    connect(command_thread, SIGNAL(sigModuleStartMonitor(quint16)), this, SIGNAL(sigModuleStartMonitor(quint16)));
    connect(command_thread, SIGNAL(sigModuleStopMonitor(quint16)), this, SIGNAL(sigModuleStopMonitor(quint16)));

    connect(this, SIGNAL(sigModuleRecvResponse(quint16,QString&,QByteArray&)), this, SLOT(onSigModuleRecvResponse(quint16, QString&, QByteArray&)));
    connect(this, SIGNAL(sigSendCommandToModule(quint16,QString&)), this, SLOT(onSigSendCommandToModule(quint16, QString&)));
    connect(this, SIGNAL(sigModuleStartMonitor(quint16)), this, SLOT(onSigModuleStartMonitor(quint16)));
    connect(this, SIGNAL(sigModuleStopMonitor(quint16)), this, SLOT(onSigModuleStopMonitor(quint16)));


    connect(_module1, SIGNAL(sigOTDRChanged(quint16,quint16)), pstThread, SIGNAL(sigOTDRChanged(quint16, quint16)));
    connect(_module1, SIGNAL(sigOTDRTrap(quint16,QByteArray&)), pstThread, SIGNAL(sigOTDRTrap(quint16, QByteArray&)));
    connect(_module2, SIGNAL(sigOTDRChanged(quint16,quint16)), pstThread, SIGNAL(sigOTDRChanged(quint16, quint16)));
    connect(_module2, SIGNAL(sigOTDRTrap(quint16,QByteArray&)), pstThread, SIGNAL(sigOTDRTrap(quint16, QByteArray&)));

// FOR DEBUG ONLY
    emit sigModuleStartMonitor(0);
    emit sigModuleStartMonitor(1);
    emit command_thread->sigSwitchModule(0);

    return true;
}

void QAgentApp::stopSession()
{
    if(_module1 != NULL){
        delete _module1;
        _module1 = NULL;
    }

    if(_module2 != NULL){
        delete _module2;
        _module2 = NULL;
    }

    if(command_thread->isRunning()){
        command_thread->terminate();
        command_thread->wait(1000);
    }

    if(pstThread->isRunning()){
        pstThread->terminate();
        pstThread->wait(1000);
    }
}


void QAgentApp::initAppData()
{



    QString configDir = getConfigDir();
    QString cacheDir  = getCacheDir();

    initDir(configDir);
    initDir(cacheDir);

    QSettings setting(getConfigFile(),QSettings::IniFormat);
    setting.beginGroup("pstRoot");
        setting.beginGroup("pstSystem");
            setting.beginGroup("pstSystemBasicManagement");
								setting.setValue("devName", QString("IFMS1000"));
								setting.setValue("devIpAddr", QString("192.168.1.100"));
								setting.setValue("devGateway", QString("192.168.1.1"));
								setting.setValue("devNetMask", QString("255.255.255.0"));
								setting.setValue("saveCurrentConfiguration", 0);
								setting.setValue("reset2Factory", 0);
								setting.setValue("reboot",0);
            setting.endGroup();
            setting.beginGroup("pstSystemVerInfo");
								setting.setValue("pstHwVer", QString("1.0"));
								setting.setValue("pstSwVer", QString("1.0"));
								setting.setValue("pstModel", QString("IFMS1000"));
								setting.setValue("pstSn", QString("123456789"));
								setting.setValue("pstFwVer", QString("1.0"));
								setting.setValue("devMacAddress", QString("aa:bb:cc:dd:ee:ff"));
						setting.endGroup();
            setting.beginGroup("pstSystemTrapInfo");
								setting.setValue("pstSystemTrapFuncEn", 1);
								

            setting.endGroup();
            setting.beginGroup("pstSystemStatus");


            setting.endGroup();
            setting.beginGroup("pstSystemOnlineUpgrade");


            setting.endGroup();
            setting.beginGroup("pstSystemProductInfo");


            setting.endGroup();
        setting.endGroup();
    setting.beginGroup("pstIFMS1000");

    setting.endGroup();
    setting.endGroup();
    setting.sync();
}

//
void QAgentApp::message(quint16 module, const QString &text, const QString &title, QObject *parent)
{
    QMutexLocker  locker(&gAgentApp_mutex);
    if(module == _currentModule){
//    qDebug() << "\n============"<< title <<"==============" << endl;
    qDebug() << text << endl ;
//    qDebug() << "=================================" << endl;
    }
}

void QAgentApp::warning(quint16 module, const QString &text, const QString &title, QObject *parent)
{
    QMutexLocker  locker(&gAgentApp_mutex);
    if(module == _currentModule){
    //    qDebug() << "\n============WARNING==============" << endl;
    qDebug() << text  << endl ;
    //    qDebug() << "=================================" << endl;
    }
}

void QAgentApp::error(quint16 module, const QString &text, const QString &title, QObject *parent)
{
    QMutexLocker  locker(&gAgentApp_mutex);
    if(module == _currentModule){
    qDebug() << "\n============ERROR==============" << endl;
    qDebug() << text ;
    qDebug() << "=================================" << endl;
    }
}

bool QAgentApp::confirm(quint16 module, const QString &text, const QString &title, QObject *parent)
{

}

void QAgentApp::message(quint16 module, const QString &text, QObject *parent)
{

}

void QAgentApp::warning(quint16 module, const QString &text, QObject *parent)
{

}

bool QAgentApp::confirm(quint16 module, const QString &text, QObject *parent)
{
    return true;
}

void QAgentApp::msg(quint16 module, const QString &title, const QString &text)
{

}

bool QAgentApp::ask(quint16 module, const QString &title, const QString &text)
{
    return true;
}

//==============================================================================================================================

void QAgentApp::showStatusMessage(const QString &msg, int ModuleIndex, int time)
{
    emit statusMessage(msg, ModuleIndex, time);
}

void QAgentApp::showStatusMessage(const QStringList &msgList, int ModuleIndex, int time)
{
    emit statusMessage(msgList, ModuleIndex, time);
}

////==================================
//void QAgentApp::onOTDRTrap(quint16 module, QByteArray &data)
//{
//// TODO: send trap to nms
//    message(module, QString(data));
//    QPSTProduct::send_pstIFMS1000MeasureEvent_trap();
//}

void QAgentApp::onSigExit(qint32 num)
{
    command_thread->setKeepRunning(0);
    command_thread->wait(1000);

    pstThread->setKeepRunning(0);
    pstThread->wait(1000);

    _module1->setKeepRunning(0);
    _module1->wait(1000);

    _module2->setKeepRunning(0);
    _module2->wait(1000);

    this->exit(num);
}

void QAgentApp::onSwitchModule(quint16 module)
{
    _currentModule = module;
}

void QAgentApp::onSigModuleRecvResponse(quint16 module, QString& cmdline, QByteArray& data)
{
    if(module == 0){
        _module1->setOTDRModuleState(QOTDRModule::OTDRModuleState::STATE_IDLING);
    }
    else
    {
        _module2->setOTDRModuleState(QOTDRModule::OTDRModuleState::STATE_IDLING);
    }
}

void QAgentApp::onSigSendCommandToModule(quint16 module, QString& cmdline)
{
    message(_currentModule,QString(">%1").arg(cmdline));
}

void QAgentApp::onSigModuleStartMonitor(quint16 moduleIndex)
{
    if(moduleIndex == 0){
        if(_module1){
            _module1->setKeepRunning(1);
            _module1->start();

        }
    }
    if(moduleIndex == 1){
        if(_module2){
            _module2->setKeepRunning(1);
            _module2->start();
        }
    }
}

void QAgentApp::onSigModuleStopMonitor(quint16 moduleIndex)
{
    if(moduleIndex == 0){
        if(_module1){
            _module1->setKeepRunning(0);
            _module1->exit(0);
            _module1->wait();
        }
    }
    if(moduleIndex == 1){
        if(_module2){
            _module2->setKeepRunning(2);
            _module2->exit(0);
            _module2->wait();
        }
    }
}
