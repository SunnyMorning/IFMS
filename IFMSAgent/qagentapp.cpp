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

//    QThreadPool *thread_pool = QThreadPool::globalInstance();
    QCommander *thread = new QCommander(this);
    QPST       *pstThread = new QPST(this);

//    thread_pool->start(thread);
//    thread_pool->start(pstThread);
    thread->start();
    pstThread->start();


    m_module1 = new QOTDRModule(this, 0);
    m_module1->initModuleFingerData();
    m_module1->setConnections();
    ret = m_module1->setSerialPortParam(QString("/dev/ttyO2"));
//    if(ret != true){
//        return ret;
//    }

    m_module2 = new QOTDRModule(this, 1);
    m_module2->initModuleFingerData();
    m_module2->setConnections();

    ret = m_module2->setSerialPortParam(QString("/dev/ttyO3"));
//    if(ret != true){
//        return  ret;
//    }

    connect(m_module1, SIGNAL(sigOTDRTrap(QByteArray&)), this, SLOT(onOTDRTrap(QByteArray&)));
    connect(m_module2, SIGNAL(sigOTDRTrap(QByteArray&)), this, SLOT(onOTDRTrap(QByteArray&)));

    return true;
}

void QAgentApp::stopSession()
{
    if(m_module1 != NULL){
        delete m_module1;
        m_module1 = NULL;
    }

    if(m_module2 != NULL){
        delete m_module2;
        m_module2 = NULL;
    }
}

bool QAgentApp::sendCommandToModule(QString cmdline, int moduleIndex)
{
// attach 0x0D and 0x0A to the endof command from console
    cmdline.push_back(QString("\r\n"));
    if(moduleIndex == 0){
        emit m_module1->sigSendCommand(cmdline);
    }

    if(moduleIndex == 1){
        emit m_module2->sigSendCommand(cmdline);
    }

    return true;
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
void QAgentApp::message(const QString &text, const QString &title, QObject *parent)
{
//    qDebug() << "\n============"<< title <<"==============" << endl;
    qDebug() << text << endl ;
//    qDebug() << "=================================" << endl;
}

void QAgentApp::warning(const QString &text, const QString &title, QObject *parent)
{
//    qDebug() << "\n============WARNING==============" << endl;
    qDebug() << text  << endl ;
//    qDebug() << "=================================" << endl;
}

void QAgentApp::error(const QString &text, const QString &title, QObject *parent)
{
    qDebug() << "\n============ERROR==============" << endl;
    qDebug() << text ;
    qDebug() << "=================================" << endl;
}

bool QAgentApp::confirm(const QString &text, const QString &title, QObject *parent)
{

}

void QAgentApp::message(const QString &text, QObject *parent)
{

}

void QAgentApp::warning(const QString &text, QObject *parent)
{

}

bool QAgentApp::confirm(const QString &text, QObject *parent)
{
    return true;
}

void QAgentApp::msg(const QString &title, const QString &text)
{

}

bool QAgentApp::ask(const QString &title, const QString &text)
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
void QAgentApp::onOTDRTrap(QByteArray &data)
{
// TODO: send trap to nms
    message(QString(data));
    QPSTProduct::send_pstIFMS1000MeasureEvent_trap();
}
