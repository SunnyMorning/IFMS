#include <QString>

#include "qpstproductprivate.h"
#include "qpst.h"

QPSTProductPrivate::QPSTProductPrivate(QObject *parent) : QObject(parent)
{

}

void QPSTProductPrivate::init_pstData()
{
    int i=0;

    pstIFMS1000PortInfoEntry	portInfo;
    pstIFMS1000MeasureEntry		measure;
    pstIFMS1000FingerEntry		finger;

    for(i=0; i<NUMBER_OF_CHANNES;i++){
        portInfo.pstIFMS1000PortNum = i+1;
        portInfo.pstIFMS1000PortRxPwr = "0";
        portInfo.pstIFMS1000PortTxPwr = "0";
        portInfo.pstIFMS1000PortWorkMode = 1;
        portInfo.pstIFMS1000PortActive = 0;
        portInfo.pstIFMS1000PortFiberAppType = 1;
        portInfo.pstIFMS1000PortRunningStatus = 1;
        PortInfoTable.push_back(portInfo);
        }
    for(i=0;i<NUMBER_OF_CHANNES;i++){
        measure.pstIFMS1000MTPortNum = i+1;
        measure.pstIFMS1000MeasureStartPosition = "0";
        measure.pstIFMS1000MeasureEndPosition = "260";
        measure.pstIFMS1000MeasureRefIndex = "1.465";
        measure.pstIFMS1000MeasureResolution = "160";
        measure.pstIFMS1000MeasureStatus = 0;
        measure.pstIFMS1000MeasureAction = 0;
        measure.pstIFMS1000MeasureProgressStatus = 0;

        QString filename = QString("IFMS_CH%1.sor").arg(i+1);
        vchar2string(measure.pstIFMS1000MeasureResultFile, filename.toStdString());

        filename = QString("IFMS_CH%1_DATA_First.bin").arg(i+1);
        vchar2string(measure.pstIFMS1000MeasureResultRawDataFile, filename.toStdString());

        filename = QString("IFMS_CH%1_DATA_current.bin").arg(i+1);
        vchar2string(measure.pstIFMS1000MeasureResultRawPointFile, filename.toStdString());
        measure.pstIFMS1000MeasureProgressStatus = 0;
        MeasureTable.push_back(measure);
        }
    for(i=0;i<NUMBER_OF_CHANNES;i++){
        finger.pstIFMS1000FTPortNum = 0;
        finger.pstIFMS1000FingerStartPosition = "0";
        finger.pstIFMS1000FingerEndPosition = "260";
        finger.pstIFMS1000FingerRefIndex = "1.465";
        FingerTable.push_back(finger);
        }
}

long QPSTProductPrivate::get_pstIFMS1000SysLedPW1(QObject *agent){
//    QPST *p = (QPST*)agent;
    return LedStatus.pstIFMS1000SystemLed.pstIFMS1000SysLedPW1;
}
long QPSTProductPrivate::get_pstIFMS1000SysLedPW2(QObject *agent){
//    QPST *p = (QPST*)agent;
    return LedStatus.pstIFMS1000SystemLed.pstIFMS1000SysLedPW2;
}
long QPSTProductPrivate::get_pstIFMS1000SysLedStatus(QObject *agent){
//    QPST *p = (QPST*)agent;
    return LedStatus.pstIFMS1000SystemLed.pstIFMS1000SysLedStatus;
}
void QPSTProductPrivate::setModuleMeasuringProgess(quint16 module, quint16 progress)
{
    if(module == 0){
        for(int i=0;i<CHANNELS_PER_MODULE;i++){
             MeasureTable[i].pstIFMS1000MeasureProgressStatus = (long) (progress) ;
        }
    }
}
