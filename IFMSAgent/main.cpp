#include <QCoreApplication>
#include <QDebug>

#include <iostream>
#include <string>

#include "qagentapp.h"


int main(int argc, char *argv[])
{
    int ret = 0;
    QAgentApp app(argc, argv);

    if(app.startSession(argc, argv)){
        ret = app.exec();
        app.stopSession();
    }

    return ret;
}
