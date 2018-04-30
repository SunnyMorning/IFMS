#include <QFile>
#include <QIODevice>
#include <QString>
#include <QMetaType>
#include <QByteArray>

#include "qfingerdata.h"
#include "qagentapp.h"

QFingerData::QFingerData(QObject *parent) : QObject(parent)
{
    qRegisterMetaType<QString>("QString");
    qRegisterMetaType<QString>("QString&");
    qRegisterMetaType<QByteArray>("QByteArray");
    qRegisterMetaType<QByteArray>("QByteArray&");
}

QFingerData& QFingerData::operator=(const QFingerData &other)
{
    mChannel = other.mChannel;

    mIFMSFingerData.Channel = other.mIFMSFingerData.Channel;
    mIFMSFingerData.GroupIndex = other.mIFMSFingerData.GroupIndex;
    mIFMSFingerData.NumberOfEvents = other.mIFMSFingerData.NumberOfEvents;
    mIFMSFingerData.vIFMSEvents.clear();
    mIFMSFingerData.vIFMSEvents.assign(other.mIFMSFingerData.vIFMSEvents.begin(), other.mIFMSFingerData.vIFMSEvents.end());
}

QByteArray  QFingerData::toByteArray()
{
    QByteArray  data;
    int i = 0;
    data.append((const char*)(&mIFMSFingerData.Channel), sizeof(mIFMSFingerData.Channel));
    data.append((const char*)(&mIFMSFingerData.GroupIndex), sizeof(mIFMSFingerData.GroupIndex));
    data.append((const char*)(&mIFMSFingerData.NumberOfEvents), sizeof(mIFMSFingerData.NumberOfEvents));

    for(i=0;i < mIFMSFingerData.vIFMSEvents.size(); i++){
        data.append((const char*)(&mIFMSFingerData.vIFMSEvents.at(i)), sizeof(IFMSEvent_t));
    }

    return data;
}

void QFingerData::toIFMSFingerFile()
{
    QString filename = getIFMSFingerFileName(mChannel);
    if(!filename.isEmpty()){
        QFile   file(filename);
        if(file.open(QIODevice::WriteOnly)){
            file.write(toByteArray());
            file.flush();
            file.close();
        }
    }
}

QString QFingerData::getIFMSFingerFileName(qint16 channel)
{
    QString     filename = QAgentApp::getCacheDir()+QString("wrong");
    if(channel == 1){
            filename = QAgentApp::getCacheDir()+QString(CH1_FINGER_FILE);
    }
    if(channel == 2){
            filename = QAgentApp::getCacheDir()+QString(CH2_FINGER_FILE);
    }
    if(channel == 3){
            filename = QAgentApp::getCacheDir()+QString(CH3_FINGER_FILE);
    }
    if(channel == 4){
            filename = QAgentApp::getCacheDir()+QString(CH4_FINGER_FILE);
    }
    if(channel == 5){
            filename = QAgentApp::getCacheDir()+QString(CH5_FINGER_FILE);
    }
    if(channel == 6){
            filename = QAgentApp::getCacheDir()+QString(CH6_FINGER_FILE);
    }
    if(channel == 7){
            filename = QAgentApp::getCacheDir()+QString(CH7_FINGER_FILE);
    }
    if(channel == 8){
            filename = QAgentApp::getCacheDir()+QString(CH8_FINGER_FILE);
    }

    return filename;
}
