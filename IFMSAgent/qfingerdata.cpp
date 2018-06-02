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

    data.append((const char*)(&mIFMSFingerData.EndtoEndLoss), sizeof(mIFMSFingerData.EndtoEndLoss));
    return data;
}

void QFingerData::toIFMSFingerFile(QString filename)
{
//    QString filename = getIFMSFingerFileName(mChannel);
    if(!filename.isEmpty()){
        QFile   file(filename);
        if(file.open(QIODevice::WriteOnly)){
            file.write(toByteArray());
            file.flush();
            file.close();
        }
    }
}

float QFingerData::getLength(void)
{
    float	f = 1.0f;
	if(	mIFMSFingerData.NumberOfEvents > 0){

		f = mIFMSFingerData.vIFMSEvents.back().EventPosition;
	}

	return f;
}

