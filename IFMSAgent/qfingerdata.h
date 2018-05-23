#ifndef QFINGERDATA_H
#define QFINGERDATA_H

#include <QObject>
#include <QByteArray>
#include <QString>

#include "ifmsfinger.h"

#define CH1_FINGER_FILE     "IFMS_CH1_finger.bin"
#define CH2_FINGER_FILE     "IFMS_CH2_finger.bin"
#define CH3_FINGER_FILE     "IFMS_CH3_finger.bin"
#define CH4_FINGER_FILE     "IFMS_CH4_finger.bin"
#define CH5_FINGER_FILE     "IFMS_CH5_finger.bin"
#define CH6_FINGER_FILE     "IFMS_CH6_finger.bin"
#define CH7_FINGER_FILE     "IFMS_CH7_finger.bin"
#define CH8_FINGER_FILE     "IFMS_CH8_finger.bin"


#define CH1_SOR_FILE     "IFMS_CH1.sor"
#define CH2_SOR_FILE     "IFMS_CH2.sor"
#define CH3_SOR_FILE     "IFMS_CH3.sor"
#define CH4_SOR_FILE     "IFMS_CH4.sor"
#define CH5_SOR_FILE     "IFMS_CH5.sor"
#define CH6_SOR_FILE     "IFMS_CH6.sor"
#define CH7_SOR_FILE     "IFMS_CH7.sor"
#define CH8_SOR_FILE     "IFMS_CH8.sor"


class QFingerData : public QObject
{
    Q_OBJECT
public:
    explicit QFingerData(QObject *parent = nullptr);
    QFingerData&  operator=(const QFingerData &other);
    IFMSFinger_t        mIFMSFingerData;
    qint16              mChannel;
    void                toIFMSFingerFile();
    QByteArray          toByteArray();
    static QString      getIFMSFingerFileName(qint16 channel);
    static QString      getIFMSSorFileName(qint16 channel);
signals:
    void    sigFingerDataChanged(qint16 channel);

public slots:
};

#endif // QFINGERDATA_H
