#include <QFile>
#include <QDir>
#include <QDebug>
#include <QString>
#include <QCoreApplication>
#include <QThreadPool>
#include <QThread>

#include "qagentapp.h"
#include "qcommander.h"

#define DATA_DIR    D_RES_DIR
#define IFMS_AGENT_NAME     "ifms"

static void initDir(const QString &path)
{
    QDir dir;
    if (!dir.exists(path)) dir.mkpath(path);
}

QString QAgentApp::getAppName()     { return QString(IFMS_AGENT_NAME); }

QString QAgentApp::getConfigDir()   { return QDir::homePath() + "/.config/" + getAppName(); }
QString QAgentApp::getCacheDir()    { return QDir::homePath() + "/.cache/"  + getAppName(); }
QString QAgentApp::getDataDir()     { return QString(DATA_DIR); }

QString QAgentApp::getConfigFile()  { return getConfigDir() + "/settings.ini"; }

QAgentApp::QAgentApp(int &argc, char **argv)
          :QCoreApplication(argc,argv)
{

}

QAgentApp::~QAgentApp()
{

}

bool QAgentApp::startSession(int &argc, char **argv)
{
    QThreadPool *thread_pool = QThreadPool::globalInstance();
    QCommander *thread = new QCommander(this);
    thread_pool->start(thread);

    return true;
}

void QAgentApp::stopSession()
{

}

bool QAgentApp::sendCommandToModule(QString cmdline, int moduleIndex)
{
    QString tmp = QString("%1").arg(moduleIndex);
    message(cmdline, QString("COMMAND[").append(tmp).append(QString("]")));

    return true;
}

void QAgentApp::initAppDirs()
{
    QString configDir = getConfigDir();
    QString cacheDir  = getCacheDir();

    initDir(configDir);
    initDir(cacheDir);
}

//
void QAgentApp::message(const QString &text, const QString &title, QObject *parent)
{
    qDebug() << "============"<< title <<"==============" << endl;
    qDebug() << text ;
    qDebug() << "=================================" << endl;
}

void QAgentApp::warning(const QString &text, const QString &title, QObject *parent)
{
    qDebug() << "============WARNING==============" << endl;
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

void QAgentApp::showProperties(const QStringList &files)
{
    emit properties(files);
}
