#include <QString>

#include "qpstproductprivate.h"
#include "qpst.h"
#include "qagentapp.h"

QPSTProductPrivate::QPSTProductPrivate(QObject *parent) : QObject(parent)
{
    _ss.setPath(QSettings::IniFormat,QSettings::UserScope,QAgentApp::getConfigDir()+ "product.ini");
}

void QPSTProductPrivate::init_pstData()
{
    int i=0;

    pstIFMS1000PortInfoEntry	portInfo;
    pstIFMS1000MeasureEntry		measure;
    pstIFMS1000FingerEntry		finger;

    for(i=0; i<NUMBER_OF_CHANNES;i++){
        portInfo.pstIFMS1000PortNum = i+1;
//        portInfo.pstIFMS1000PortRxPwr = "0";
//        portInfo.pstIFMS1000PortTxPwr = "0";
        portInfo.pstIFMS1000PortWorkMode = 1;
        portInfo.pstIFMS1000PortActive = 0;
        portInfo.pstIFMS1000PortFiberAppType = 1;
        portInfo.pstIFMS1000PortRunningStatus = 1;
        PortInfoTable.push_back(portInfo);
        }

	QStringList		startPositions;
	QStringList		endPositions;
	startPositions <<"0" << "10"<<"20" << "30"<<"40" << "50"<<"60" << "70";
	endPositions <<"160" << "160"<<"160" << "160"<<"160" << "160"<<"160" << "160";

	_ss.beginGroup(PRODUCT_SETTINGS_GROUP);
	
	_ss.beginWriteArray("MeasureTable");
    for(i=0;i<NUMBER_OF_TRAPTARGETS;i++){
		_ss.setArrayIndex(i);
		_ss.setValue("pstIFMS1000MeasureStartPosition", startPositions.at(i));
		_ss.setValue("pstIFMS1000MeasureEndPosition", endPositions.at(i));
    }
	_ss.endArray();
	_ss.endGroup();
    _ss.sync();
    for(i=0;i<NUMBER_OF_CHANNES;i++){
        measure.pstIFMS1000MTPortNum = i+1;
//        measure.pstIFMS1000MeasureStartPosition = "0";
//        measure.pstIFMS1000MeasureEndPosition = "260";
//        measure.pstIFMS1000MeasureRefIndex = "1.465";
//        measure.pstIFMS1000MeasureResolution = "160";
        measure.pstIFMS1000MeasureStatus = 0;
        measure.pstIFMS1000MeasureAction = 0;
        measure.pstIFMS1000MeasureProgressStatus = 0;

        QString filename = QString("IFMS_CH%1.sor").arg(i+1);
//        vchar2string(measure.pstIFMS1000MeasureResultFile, filename.toStdString());

        filename = QString("IFMS_CH%1_DATA_First.bin").arg(i+1);
//        vchar2string(measure.pstIFMS1000MeasureResultRawDataFile, filename.toStdString());

        filename = QString("IFMS_CH%1_DATA_current.bin").arg(i+1);
//        vchar2string(measure.pstIFMS1000MeasureResultRawPointFile, filename.toStdString());
        measure.pstIFMS1000MeasureProgressStatus = 0;
        MeasureTable.push_back(measure);
        }

	
    for(i=0;i<NUMBER_OF_CHANNES;i++){
        finger.pstIFMS1000FTPortNum = 0;
//        finger.pstIFMS1000FingerStartPosition = "0";
//        finger.pstIFMS1000FingerEndPosition = "260";
//        finger.pstIFMS1000FingerRefIndex = "1.465";
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

QString QPSTProductPrivate::get_pstIFMS1000MeasureStartPosition(long index)
{
	QString  startPosition;
	int size = _ss.beginReadArray("MeasureTable");
	_ss.setArrayIndex(index);
    startPosition = _ss.value("pstIFMS1000MeasureStartPosition", "0").toString();
	return startPosition;
}


void QPSTProductPrivate::setModuleMeasuringProgess(quint16 module, quint16 progress)
{
    for(int i=0;i<CHANNELS_PER_MODULE;i++){
             MeasureTable[module*CHANNELS_PER_MODULE+i].pstIFMS1000MeasureProgressStatus = (long) (progress) ;
     }
}
