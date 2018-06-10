#ifndef QAGENTAPP_H
#define QAGENTAPP_H

#include <QObject>
#include <QCoreApplication>
#include <QString>
#include <QStringList>

#include <map>
#include <vector>
#include <string>

#include "qotdrmodule.h"
#include "qcommander.h"
#include "qfancontrol.h"
#include "qpst.h"

using namespace std;

class QAgentApp : public QCoreApplication
{
    Q_OBJECT
public:
    explicit QAgentApp(int &argc, char **argv);
    virtual ~QAgentApp();
    static QAgentApp* getInstance(void);

    void showStatusMessage(const QString &msg, int ModuleIndex, int time);
    void showStatusMessage(const QStringList &msgList, int ModuleIndex, int time);
    void showProperties(const QStringList &files);

    static QString getAppName();
    static QString getConfigDir();
    static QString getCacheDir();
    static QString getDataDir();
    static QString getConfigFile();

    static void message(quint16 module, const QString &text, const QString &title = QString(), QObject *parent = NULL);
    static void warning(quint16 module, const QString &text, const QString &title = QString(), QObject *parent = NULL);
    static void error(quint16 module, const QString &text, const QString &title = QString(), QObject *parent = NULL);

    static bool confirm(quint16 module, const QString &text, const QString &title = QString(), QObject *parent = NULL);
    static void message(quint16 module, const QString &text, QObject *parent);
    static void warning(quint16 module, const QString &text, QObject *parent);
    static bool confirm(quint16 module, const QString &text, QObject *parent);

    static void msg(quint16 module, const QString &title, const QString &text);
    static bool ask(quint16 module, const QString &title, const QString &text);

    QAgentApp         *app() { return m_app; }
    bool   startSession(int &argc, char **argv);
    void   stopSession();

protected:
    void    initAppData(QPST *p);
    void    initFingerBin(QString filename, qint16 ch);

signals:
    void settingsChanged();
    void statusMessage(const QString &msg, int ModuleIndex, int time);
    void statusMessage(const QStringList &msgList, int ModuleIndex, int time);
    void sigSendCommandToModule(quint16 module, QString& cmdline);
    // for debug only
    void sigModuleRecvResponse(quint16 module ,QString& cmdline, QByteArray& data);
    void sigModuleStartMonitor(quint16 module);
    void sigModuleStopMonitor(quint16 module);
    void sigModuleSingleMonitor(quint16 module);
    void sigModuleUpdate(quint16 module);
public slots:
    void onSigExit(qint32 num);
    void onSwitchModule(quint16 module);
    void onSigSendCommandToModule(quint16 module, QString& cmdline);

// for debug only
    void onSigModuleRecvResponse(quint16 module, QString& cmdline, QByteArray& data);
    void onSigModuleStartMonitor(quint16 module);
    void onSigModuleStopMonitor(quint16 module);
    void onSigModuleSingleMonitor(quint16 module);
    void onSigModuleUpdate(quint16 module);

private:
    QAgentApp                   *m_app;
    QCommander                  *command_thread;
    QPST                        *pstThread ;

    QOTDRModule                 *_module1;
    QOTDRModule                 *_module2;
    QFanControl                 *m_fans;

};

#endif // QAGENTAPP_H
