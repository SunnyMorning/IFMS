#ifndef QFINGERDATA_H
#define QFINGERDATA_H

#include <QObject>

#define CH1_FINGER_FILE     "IFMS_CH1_finger.bin"
#define CH2_FINGER_FILE     "IFMS_CH2_finger.bin"
#define CH3_FINGER_FILE     "IFMS_CH3_finger.bin"
#define CH4_FINGER_FILE     "IFMS_CH4_finger.bin"
#define CH5_FINGER_FILE     "IFMS_CH5_finger.bin"
#define CH6_FINGER_FILE     "IFMS_CH6_finger.bin"
#define CH7_FINGER_FILE     "IFMS_CH7_finger.bin"
#define CH8_FINGER_FILE     "IFMS_CH8_finger.bin"

class QFingerData : public QObject
{
    Q_OBJECT
public:
    explicit QFingerData(QObject *parent = nullptr);

signals:

public slots:
};

#endif // QFINGERDATA_H
