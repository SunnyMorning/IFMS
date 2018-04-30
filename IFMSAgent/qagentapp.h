#ifndef QAGENTAPP_H
#define QAGENTAPP_H

#include <QObject>
#include <QCoreApplication>
#include <QString>
#include <QStringList>

#include "qotdrmodule.h"
#include "qfingerdata.h"


class QAgentApp : public QCoreApplication
{
    Q_OBJECT
public:
    explicit QAgentApp(int &argc, char **argv);
    virtual ~QAgentApp();

    void showStatusMessage(const QString &msg, int ModuleIndex, int time);
    void showStatusMessage(const QStringList &msgList, int ModuleIndex, int time);
    void showProperties(const QStringList &files);

protected:
    void    initAppDirs();
    void    initFingerBin(QString filename, qint16 ch);

signals:
    void settingsChanged();
    void statusMessage(const QString &msg, int ModuleIndex, int time);
    void statusMessage(const QStringList &msgList, int ModuleIndex, int time);

public slots:

public:
    static QString getAppName();
    static QString getConfigDir();
    static QString getCacheDir();
    static QString getDataDir();
    static QString getConfigFile();

    static void message(const QString &text, const QString &title = QString(), QObject *parent = NULL);
    static void warning(const QString &text, const QString &title = QString(), QObject *parent = NULL);
    static void error(const QString &text, const QString &title = QString(), QObject *parent = NULL);

    static bool confirm(const QString &text, const QString &title = QString(), QObject *parent = NULL);
    static void message(const QString &text, QObject *parent);
    static void warning(const QString &text, QObject *parent);
    static bool confirm(const QString &text, QObject *parent);

    static void msg(const QString &title, const QString &text);
    static bool ask(const QString &title, const QString &text);

public:
    QOTDRModule                 *m_module1;
    QOTDRModule                 *m_module2;
    QAgentApp         *app() { return m_app; }
    bool   startSession(int &argc, char **argv);
    void   stopSession();
    bool   sendCommandToModule(QString cmdline, int moduleIndex = 0);

protected:
    QAgentApp                   *m_app;
};

#endif // QAGENTAPP_H
