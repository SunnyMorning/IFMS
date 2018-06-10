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

#define DATA_DIR    D_DATA_DIR
#define CACHE_DIR	D_CACHE_DIR

#define IFMS_AGENT_NAME     "ifms"

static void initDir(const QString &path)
{
    QDir dir;
    if (!dir.exists(path)) dir.mkpath(path);
}

static QMutex   gAgentApp_mutex;
static quint16  _currentModule = 0;

QString QAgentApp::getAppName()     { return QString(IFMS_AGENT_NAME); }

QString QAgentApp::getConfigDir()   { return QDir::homePath() + "/.config/" + getAppName() + "/"; }
QString QAgentApp::getCacheDir()    { return QString(CACHE_DIR); }
QString QAgentApp::getDataDir()     { return QString(DATA_DIR); }

QString QAgentApp::getConfigFile()  { return getConfigDir() + "settings.ini"; }

QAgentApp::QAgentApp(int &argc, char **argv)
          :QCoreApplication(argc,argv)
{

}

QAgentApp::~QAgentApp()
{

}

QAgentApp* QAgentApp::getInstance(void)
{
    return (QAgentApp*) qApp;
}

bool QAgentApp::startSession(int &argc, char **argv)
{
    bool ret = false;
    onSwitchModule(0);
    _module1 = new QOTDRModule(this, 0);
    _module1->initModuleData();
    _module1->setConnections();


    _module2 = new QOTDRModule(this, 1);
    _module2->initModuleData();
    _module2->setConnections();

    m_fans = new QFanControl(this);

    command_thread = new QCommander(this);

    pstThread = QPST::getInstance();
    pstThread->initConnections();


    pstThread->start();
    command_thread->start();
    m_fans->start();

    initAppData(pstThread);

    connect(command_thread, SIGNAL(sigExit(qint32)), this, SLOT(onSigExit(qint32)));
    connect(command_thread, SIGNAL(sigSwitchModule(quint16)), this, SLOT(onSwitchModule(quint16)));
    connect(command_thread, SIGNAL(sigSwitchModule(quint16)), command_thread, SLOT(onSwitchModule(quint16)));
    connect(command_thread, SIGNAL(sigModuleRecvResponse(quint16,QString&,QByteArray&)), this, SIGNAL(sigModuleRecvResponse(quint16,QString&,QByteArray&)));
    connect(command_thread, SIGNAL(sigSendCommandToModule(quint16,QString)), this, SIGNAL(sigSendCommandToModule(quint16, QString)));
    connect(command_thread, SIGNAL(sigModuleStartMonitor(quint16)), this, SIGNAL(sigModuleStartMonitor(quint16)));
    connect(command_thread, SIGNAL(sigModuleStopMonitor(quint16)), this, SIGNAL(sigModuleStopMonitor(quint16)));
    connect(command_thread, SIGNAL(sigModuleSingleMonitor(quint16)), this, SIGNAL(sigModuleSingleMonitor(quint16)));

	connect(pstThread, SIGNAL(sigSendCommandToModule(quint16,QString)), this, SIGNAL(sigSendCommandToModule(quint16, QString)));
    connect(pstThread,  SIGNAL(sigSystemTemperatureHighThreshold(int)), m_fans, SLOT(onFanSetHighTemperature(int)));
    connect(pstThread, SIGNAL(sigSystemTemperatureLowThreshold(int)), m_fans, SLOT(onFanSetLowTemperature(int)));
    connect(pstThread, SIGNAL(sigSystemFanControlMode(int)), m_fans, SLOT(onFanControlMode(int)));
    connect(m_fans, SIGNAL(sigTemperatureChanged(int)), pstThread, SLOT(onSigTemperatureChanged(int)));

    connect(this, SIGNAL(sigModuleRecvResponse(quint16,QString&,QByteArray&)), this, SLOT(onSigModuleRecvResponse(quint16, QString&, QByteArray&)));
    connect(this, SIGNAL(sigSendCommandToModule(quint16,QString&)), this, SLOT(onSigSendCommandToModule(quint16, QString&)));
    connect(this, SIGNAL(sigModuleStartMonitor(quint16)), this, SLOT(onSigModuleStartMonitor(quint16)));
    connect(this, SIGNAL(sigModuleStopMonitor(quint16)), this, SLOT(onSigModuleStopMonitor(quint16)));
    connect(this, SIGNAL(sigModuleSingleMonitor(quint16)), this, SLOT(onSigModuleSingleMonitor(quint16)));
    connect(this, SIGNAL(sigModuleUpdate(quint16)), this, SLOT(onSigModuleUpdate(quint16)));


    connect(_module1, SIGNAL(sigSendCommand(quint16, QString&)), _module1, SLOT(onSendCommand(quint16, QString&)));
    connect(_module1, SIGNAL(sigOTDRSetMode(quint16,quint16)), pstThread, SLOT(onSigOTDRSetMode(quint16,quint16)));
    connect(_module1, SIGNAL(sigSetProgress(quint16,quint16)),pstThread, SIGNAL(sigSetProgress(quint16,quint16)));
    connect(_module1, SIGNAL(sigOTDRTrap(quint16,QString&)), pstThread, SIGNAL(sigOTDRTrap(quint16, QString&)));
    connect(_module1, SIGNAL(sigSetMeasuredCount(quint16, quint32)), pstThread, SLOT(onSigSetMeasuredCount(quint16, quint32)));
    connect(_module1, SIGNAL(sigOTDRSetMeasuringStatus(quint16,quint32)), pstThread, SLOT(onSigSetMeasuringStatus(quint16,quint32)));
    connect(_module1, SIGNAL(sigOTDRUpdateStatus(quint16,int)), pstThread, SLOT(onSigOTDRUpdateStatus(quint16,int)));

    connect(_module2, SIGNAL(sigSendCommand(quint16, QString&)), _module2, SLOT(onSendCommand(quint16, QString&)));
    connect(_module2, SIGNAL(sigOTDRSetMode(quint16,quint16)), pstThread, SLOT(onSigOTDRSetMode(quint16,quint16)));
    connect(_module2, SIGNAL(sigSetProgress(quint16,quint16)),pstThread, SIGNAL(sigSetProgress(quint16,quint16)));
    connect(_module2, SIGNAL(sigOTDRTrap(quint16,QString&)), pstThread, SIGNAL(sigOTDRTrap(quint16, QString&)));
    connect(_module2, SIGNAL(sigSetMeasuredCount(quint16, quint32)), pstThread, SLOT(onSigSetMeasuredCount(quint16, quint32)));
    connect(_module2, SIGNAL(sigOTDRSetMeasuringStatus(quint16,quint32)), pstThread, SLOT(onSigSetMeasuringStatus(quint16,quint32)));
    connect(_module2, SIGNAL(sigOTDRUpdateStatus(quint16,int)), pstThread, SLOT(onSigOTDRUpdateStatus(quint16,int)));
// FOR DEBUG ONLY
//    emit sigModuleStartMonitor(0);
//    emit sigModuleStartMonitor(1);
//    emit command_thread->sigSwitchModule(0);
//    QString qcmdline = QString("SCAN");
//    QString qcmdline = QString("GETSOR? 0");
//    emit command_thread->sigSendCommandToModule(0,qcmdline);
//    emit sigModuleSingleMonitor(0);
//    emit pstThread->TrapTargetsChanged();

    qDebug() << "[" << QThread::currentThreadId() << "] QAgent:StartSession" << endl;
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
	
	if(m_fans->isRunning()){
		m_fans->terminate();
		m_fans->wait(1000);
	}
}


void QAgentApp::initAppData(QPST* p)
{

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

//==================================

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
        _module1->setModuleState(QOTDRModule::ModuleState::STATE_IDLING);
    }
    else
    {
        _module2->setModuleState(QOTDRModule::ModuleState::STATE_IDLING);
    }
}

void QAgentApp::onSigSendCommandToModule(quint16 module, QString& cmdline)
{
    message(_currentModule,QString("onSigSendCommandToModule> %1 %2").arg(module).arg(cmdline));
    if(module == 0){
        emit  _module1->sigSendCommand(module,cmdline);
    }
    else
    {
        emit _module2->sigSendCommand(module,cmdline);
    }
}

void QAgentApp::onSigModuleStartMonitor(quint16 moduleIndex)
{
    if(moduleIndex == 0){
        if(_module1){
            if(_module1->isMeasured() != true){
                qDebug() << "It is measuring ...." << endl;
                return;
            }
            _module1->setKeepRunning(1);
            _module1->setModuleMode(0,OTDR_WORK_MODE_AUTO);
            _module1->start();

        }
    }
    if(moduleIndex == 1){
        if(_module2){
            if(_module2->isMeasured() != true){
                qDebug() << "It is measuring ...." << endl;
                return;
            }
            _module2->setKeepRunning(1);
            _module2->setModuleMode(1,OTDR_WORK_MODE_AUTO);
            _module2->start();
        }
    }
}

void QAgentApp::onSigModuleStopMonitor(quint16 moduleIndex)
{
    if(moduleIndex == 0){
        if(_module1){
            _module1->setModuleMode(0, OTDR_WORK_MODE_STOP);
            _module1->setKeepRunning(0);
            _module1->exit(0);
            _module1->wait();
        }
    }
    if(moduleIndex == 1){
        if(_module2){
            _module2->setModuleMode(1, OTDR_WORK_MODE_STOP);
            _module2->setKeepRunning(0);
            _module2->exit(0);
            _module2->wait();
        }
    }
}

void QAgentApp::onSigModuleSingleMonitor(quint16 module)
{
    qDebug() << "qAgentApp:" <<  QThread::currentThreadId() << endl;

    if(module == 0){
        if(_module1){
            if(_module1->isMeasured()!=true){
                qDebug() << "It is measuring ...." << endl;
                return;
            }
            _module1->setModuleMode(0 , OTDR_WORK_MODE_SINGLE);
            _module1->setKeepRunning(0);
            _module1->start();
        }
    }
    if(module == 1){
        if(_module2){
            if(_module2->isMeasured()!=true){
                qDebug() << "It is measuring ...." << endl;
                return;
            }
            _module2->setKeepRunning(0);
            _module2->setModuleMode(1 , OTDR_WORK_MODE_SINGLE);
            _module2->start();
        }
    }
}


void QAgentApp::onSigModuleUpdate(quint16 module)
{
    qDebug() << "qAgentApp:" <<  QThread::currentThreadId() << endl;

    if(module == 0){
        if(_module1){
            if((_module1->isMeasured()!=true) && (_module1->isIdling()!= true)) {
                qDebug() << "It is measuring ...." << endl;
                return;
            }
            _module1->setModuleMode(0 , OTDR_WORK_MODE_UPDATE);
            _module1->setKeepRunning(0);
            _module1->start();
        }
    }
    if(module == 1){
        if(_module2){
            if((_module2->isMeasured()!=true) && (_module2->isIdling()!= true)) {
                qDebug() << "It is measuring ...." << endl;
                return;
            }
            _module2->setKeepRunning(0);
            _module2->setModuleMode(1 , OTDR_WORK_MODE_UPDATE);
            _module2->start();
        }
    }
}
