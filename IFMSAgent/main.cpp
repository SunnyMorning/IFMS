#include <QtGlobal>
#include <QCoreApplication>
#include <QDebug>

#include <iostream>
#include <string>

#include "qagentapp.h"

//void customHandler(QtMsgType type, const char* msg) {
// fprintf(stderr, msg);
// fflush(stderr);
//}


int main(int argc, char *argv[])
{
    int ret = 0;
    QAgentApp app(argc, argv);
//    qInstallMsgHandler(customHandler);

    if(app.startSession(argc, argv)){
        ret = app.exec();
        app.stopSession();
    }

    return ret;
}
