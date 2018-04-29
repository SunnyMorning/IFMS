#include <QCoreApplication>
#include <QDebug>

#include <iostream>
#include <string>

#include "qagentapp.h"


int main(int argc, char *argv[])
{
    int ret = 0;
    QAgentApp app(argc, argv);

//        std::string  name;
//        std::cout << "Please enter a command:";
//        std::getline(std::cin, name);
//        std::cout << "Hello, " << name << "!\n";

//        QString qname = QString::fromStdString(name);

//        qDebug() << "onDataChannelDisconnected from " << qname << ".\n";

    if(app.startSession(argc, argv)){
        ret = app.exec();
        app.stopSession();
    }

    return ret;
}
