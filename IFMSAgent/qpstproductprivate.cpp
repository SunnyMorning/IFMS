#include <QString>
#include <QVariant>

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
        strcpy(portInfo.pstIFMS1000PortRxPwr,"0");
        strcpy(portInfo.pstIFMS1000PortTxPwr,"0");
        portInfo.pstIFMS1000PortWorkMode = 1;
        portInfo.pstIFMS1000PortActive = 0;
        portInfo.pstIFMS1000PortFiberAppType = 1;
        portInfo.pstIFMS1000PortRunningStatus = 1;
        portInfo.valid = 1;
        PortInfoTable.push_back(portInfo);
    }

    for(i=0;i<NUMBER_OF_CHANNES;i++){
        measure.pstIFMS1000MTPortNum = i+1;
        strcpy(measure.pstIFMS1000MeasureStartPosition,"0");
        measure.pstIFMS1000MeasureEndPosition_len = 1;
        strcpy(measure.pstIFMS1000MeasureEndPosition , "160");
        measure.pstIFMS1000MeasureEndPosition_len=3;
        strcpy(measure.pstIFMS1000MeasureRefIndex , "1.465");
        strcpy(measure.pstIFMS1000MeasureResolution, "10");
        measure.pstIFMS1000MeasureStatus = 0;
        measure.pstIFMS1000MeasureAction = 0;
        strcpy(measure.pstIFMS1000MeasurePulseWidth, "10000");
        measure.pstIFMS1000MeasureTime=30;
        measure.pstIFMS1000MeasureProgressStatus = 0;
        strcpy(measure.pstIFMS1000MeasureTLOS, "0");
        measure.pstIFMS1000MeasureTLOS_len = 1;
        strcpy(measure.pstIFMS1000MeasureTREF, "-14");
        measure.pstIFMS1000MeasureTREF_len = 3;
        
		strcpy(measure.pstIFMS1000MeasureFiberLengthChangeThreshold, "100");
		measure.pstIFMS1000MeasureFiberLengthChangeThreshold_len = 3;
				
		strcpy(measure.pstIFMS1000MeasureEndToEndLossCriticalThreshold, "5");
		measure.pstIFMS1000MeasureEndToEndLossCriticalThreshold_len = 1;
				
		strcpy(measure.pstIFMS1000MeasureEndToEndLossMajorThreshold, "1");
		measure.pstIFMS1000MeasureEndToEndLossMajorThreshold_len = 1;
				
		strcpy(measure.pstIFMS1000MeasureEndToEndLossMinorThreshold, "0");
		measure.pstIFMS1000MeasureEndToEndLossMinorThreshold_len = 1;
				
		strcpy(measure.pstIFMS1000MeasureNewLossCriticalThreshold, "5");
        measure.pstIFMS1000MeasureNewLossCriticalThreshold_len = 1;
        
		strcpy(measure.pstIFMS1000MeasureNewLossMajorThreshold, "2");
        measure.pstIFMS1000MeasureNewLossMajorThreshold_len = 1;
        
		strcpy(measure.pstIFMS1000MeasureNewLossMinorThreshold, "0.5");
        measure.pstIFMS1000MeasureNewLossMinorThreshold_len = 3;
        
		strcpy(measure.pstIFMS1000MeasureOldLossCriticalThreshold, "5");
        measure.pstIFMS1000MeasureOldLossCriticalThreshold_len = 1;
        
		strcpy(measure.pstIFMS1000MeasureOldLossMajorThreshold, "2");
        measure.pstIFMS1000MeasureOldLossMajorThreshold_len = 1;
        
		strcpy(measure.pstIFMS1000MeasureOldLossMinorThreshold, "0.5");
        measure.pstIFMS1000MeasureOldLossMinorThreshold_len = 3;
        
        strcpy(measure.pstIFMS1000MeasureTempHighThreshold, "55");
        measure.pstIFMS1000MeasureTempHighThreshold_len = 2;
        
        strcpy(measure.pstIFMS1000MeasureTempLowThreshold, "-5");
        measure.pstIFMS1000MeasureTempLowThreshold_len = 2;
        
        strcpy(measure.pstIFMS1000MeasureNumber, "0");
        measure.pstIFMS1000MeasureNumber_len = 1;
        strcpy(measure.pstIFMS1000MeasureNumberSORStoredEachChannel, "10");
        measure.pstIFMS1000MeasureNumberSORStoredEachChannel_len = 2;

//        QString filename = QString("IFMS_CH%1.sor").arg(i+1);
////        vchar2string(measure.pstIFMS1000MeasureResultFile, filename.toStdString());

//        filename = QString("IFMS_CH%1_DATA_First.bin").arg(i+1);
////        vchar2string(measure.pstIFMS1000MeasureResultRawDataFile, filename.toStdString());

//        filename = QString("IFMS_CH%1_DATA_current.bin").arg(i+1);
////        vchar2string(measure.pstIFMS1000MeasureResultRawPointFile, filename.toStdString());
        MeasureTable.push_back(measure);
    }

	
    for(i=0;i<NUMBER_OF_CHANNES;i++){
        finger.pstIFMS1000FTPortNum = i+1;
//        finger.pstIFMS1000FingerStartPosition = "0";
//        finger.pstIFMS1000FingerEndPosition = "260";
//        finger.pstIFMS1000FingerRefIndex = "1.465";
        FingerTable.push_back(finger);
    }


//    set_pstIFMS1000PortFiberAppType(4, 2);

//    int t = get_pstIFMS1000PortFiberAppType(4);

//    qDebug()<< "t = " << t << endl;

}

long QPSTProductPrivate::get_pstIFMS1000SysLedPW1(QObject *agent)
{
	return 0;
}
long QPSTProductPrivate::get_pstIFMS1000SysLedPW2(QObject *agent)
{
	return 0;
}
long QPSTProductPrivate::get_pstIFMS1000SysLedStatus(QObject *agent)
{
	return 0;
}

QString QPSTProductPrivate::get_pstIFMS1000PortRxPwr(quint16 channel)
{
    return QString("%1").arg(PortInfoTable[channel-1].pstIFMS1000PortRxPwr);
}

          
size_t QPSTProductPrivate::get_pstIFMS1000PortRxPwr_len(quint16 channel)
{
    return  PortInfoTable[channel-1].pstIFMS1000PortRxPwr_len;
}

      
QString QPSTProductPrivate::get_pstIFMS1000PortTxPwr(quint16 channel)
{
    return QString("%1").arg(PortInfoTable[channel-1].pstIFMS1000PortTxPwr);
}

          
size_t QPSTProductPrivate::get_pstIFMS1000PortTxPwr_len(quint16 channel)
{
    return  PortInfoTable[channel-1].pstIFMS1000PortTxPwr_len;
}

     
long QPSTProductPrivate::get_pstIFMS1000PortWorkMode(quint16 channel)
{
    return  PortInfoTable[channel-1].pstIFMS1000PortWorkMode;
}

           
long QPSTProductPrivate::get_pstIFMS1000PortActive(quint16 channel)
{
    long s;

    _ss.beginGroup(PRODUCT_SETTINGS_GROUP);
        _ss.beginReadArray("pstIFMS1000PortActive");
            _ss.setArrayIndex(channel-1);
            s = (long)_ss.value("pstIFMS1000PortActive", "0").toInt();
        _ss.endArray();
    _ss.endGroup();

    return s;
}

             
long QPSTProductPrivate::get_pstIFMS1000PortFiberAppType(quint16 channel)
{
    long s;

    _ss.beginGroup(PRODUCT_SETTINGS_GROUP);
        _ss.beginReadArray("pstIFMS1000PortFiberAppType");
            _ss.setArrayIndex(channel-1);
            s = (long)_ss.value("pstIFMS1000PortFiberAppType", "1").toInt();
        _ss.endArray();
    _ss.endGroup();

    return s;
}

       
long QPSTProductPrivate::get_pstIFMS1000PortRunningStatus(quint16 channel)
{
    return  PortInfoTable[channel-1].pstIFMS1000PortRunningStatus;
}

      

void QPSTProductPrivate::set_pstIFMS1000PortRxPwr(quint16 channel,QString s)
{

}

          
void QPSTProductPrivate::set_pstIFMS1000PortRxPwr_len(quint16 channel, int s)
{

}

      
void QPSTProductPrivate::set_pstIFMS1000PortTxPwr(quint16 channel,QString s)
{

}

          
void QPSTProductPrivate::set_pstIFMS1000PortTxPwr_len(quint16 channel,int s)
{

}

     
void QPSTProductPrivate::set_pstIFMS1000PortWorkMode(quint16 channel,int s)
{

}

           
void QPSTProductPrivate::set_pstIFMS1000PortActive(quint16 channel,int s)
{
    _ss.beginGroup(PRODUCT_SETTINGS_GROUP);
        _ss.beginWriteArray("pstIFMS1000PortActive");
            _ss.setArrayIndex(channel-1);
            _ss.setValue("pstIFMS1000PortActive", s);
        _ss.endArray();
    _ss.endGroup();
    _ss.sync();
}

             
void QPSTProductPrivate::set_pstIFMS1000PortFiberAppType(quint16 channel,int s)
{
    _ss.beginGroup(PRODUCT_SETTINGS_GROUP);
        _ss.beginWriteArray("pstIFMS1000PortFiberAppType");
            _ss.setArrayIndex(channel-1);
            _ss.setValue("pstIFMS1000PortFiberAppType", s);
        _ss.endArray();
    _ss.endGroup();
    _ss.sync();
}

       
void QPSTProductPrivate::set_pstIFMS1000PortRunningStatus(quint16 channel,int s)
{

}

    

QString QPSTProductPrivate::get_pstIFMS1000MeasureStartPosition(quint16 channel)
{
    QString  s;

    _ss.beginGroup(PRODUCT_SETTINGS_GROUP);
    _ss.beginReadArray("pstIFMS1000MeasureStartPosition");
    _ss.setArrayIndex(channel-1);
    s = _ss.value("pstIFMS1000MeasureStartPosition", "0").toString();
    _ss.endArray();
    _ss.endGroup();

    return s;
}


size_t QPSTProductPrivate::get_pstIFMS1000MeasureStartPosition_len(quint16 channel)
{
	return 1;
}


QString QPSTProductPrivate::get_pstIFMS1000MeasureEndPosition(quint16 channel)
{
    QString  s;

    _ss.beginGroup(PRODUCT_SETTINGS_GROUP);
    _ss.beginReadArray("pstIFMS1000MeasureEndPosition");
    _ss.setArrayIndex(channel-1);
    s = _ss.value("pstIFMS1000MeasureEndPosition", "160").toString();
    _ss.endArray();
    _ss.endGroup();

    return s;
}


size_t QPSTProductPrivate::get_pstIFMS1000MeasureEndPosition_len(quint16 channel)
{
	return	3;
}


 QString QPSTProductPrivate::get_pstIFMS1000MeasureRefIndex(quint16 channel)
{
    QString  s;

    _ss.beginGroup(PRODUCT_SETTINGS_GROUP);
    _ss.beginReadArray("pstIFMS1000MeasureRefIndex");
    _ss.setArrayIndex(channel-1);
    s = _ss.value("pstIFMS1000MeasureRefIndex", "1.465").toString();
    _ss.endArray();
    _ss.endGroup();

    return s;
}


size_t QPSTProductPrivate::get_pstIFMS1000MeasureRefIndex_len(quint16 channel)
{
	return 5;
}


QString QPSTProductPrivate::get_pstIFMS1000MeasureResolution(quint16 channel)
{
    QString  s;

    _ss.beginGroup(PRODUCT_SETTINGS_GROUP);
    _ss.beginReadArray("pstIFMS1000MeasureResolution");
    _ss.setArrayIndex(channel-1);
    s = _ss.value("pstIFMS1000MeasureResolution", "10").toString();
    _ss.endArray();
    _ss.endGroup();

    return s;
}


size_t QPSTProductPrivate::get_pstIFMS1000MeasureResolution_len(quint16 channel)
{

}


long QPSTProductPrivate::get_pstIFMS1000MeasureStatus(quint16 channel)
{
	return MeasureTable[channel-1].pstIFMS1000MeasureStatus;
}


long QPSTProductPrivate::get_pstIFMS1000MeasureAction(quint16 channel)
{
    return MeasureTable[channel-1].pstIFMS1000MeasureAction;
}


QString QPSTProductPrivate::get_pstIFMS1000MeasurePulseWidth(quint16 channel)
{
    QString  s;

    _ss.beginGroup(PRODUCT_SETTINGS_GROUP);
    _ss.beginReadArray("pstIFMS1000MeasurePulseWidth");
    _ss.setArrayIndex(channel-1);
    s = _ss.value("pstIFMS1000MeasurePulseWidth", "10000").toString();
    _ss.endArray();
    _ss.endGroup();

    return s;
}


size_t QPSTProductPrivate::get_pstIFMS1000MeasurePulseWidth_len(quint16 channel)
{
	return MeasureTable[channel-1].pstIFMS1000MeasurePulseWidth_len;
}


long QPSTProductPrivate::get_pstIFMS1000MeasureTime(quint16 channel)
{
	return MeasureTable[channel-1].pstIFMS1000MeasureTime;
}


 long QPSTProductPrivate::get_pstIFMS1000MeasureProgressStatus(quint16 channel)
{
    return MeasureTable[channel-1].pstIFMS1000MeasureProgressStatus;
}


QString QPSTProductPrivate::get_pstIFMS1000MeasureTLOS(quint16 channel)
{
	 QString  s;
	 
	 _ss.beginGroup(PRODUCT_SETTINGS_GROUP);
	 _ss.beginReadArray("pstIFMS1000MeasureTLOS");
	 _ss.setArrayIndex(channel-1);
	 s = _ss.value("pstIFMS1000MeasureTLOS", "0").toString();
	 _ss.endArray();
	 _ss.endGroup();
	 
	 return s;
}


size_t QPSTProductPrivate::get_pstIFMS1000MeasureTLOS_len(quint16 channel)
{
    return MeasureTable[channel-1].pstIFMS1000MeasureTLOS_len;
}


QString QPSTProductPrivate::get_pstIFMS1000MeasureTREF(quint16 channel)
{
    QString  s;

    _ss.beginGroup(PRODUCT_SETTINGS_GROUP);
    _ss.beginReadArray("pstIFMS1000MeasureTREF");
    _ss.setArrayIndex(channel-1);
    s = _ss.value("pstIFMS1000MeasureTREF", "-14").toString();
    _ss.endArray();
    _ss.endGroup();

    return s;
}


size_t QPSTProductPrivate::get_pstIFMS1000MeasureTREF_len(quint16 channel)
{
    return MeasureTable[channel-1].pstIFMS1000MeasureTREF_len;
}


QString QPSTProductPrivate::get_pstIFMS1000MeasureFiberLengthChangeThreshold(quint16 channel)
{
    QString  s;

    _ss.beginGroup(PRODUCT_SETTINGS_GROUP);
    _ss.beginReadArray("pstIFMS1000MeasureFiberLengthChangeThreshold");
    _ss.setArrayIndex(channel-1);
    s = _ss.value("pstIFMS1000MeasureFiberLengthChangeThreshold", "100").toString();
    _ss.endArray();
    _ss.endGroup();

    return s;
}


size_t QPSTProductPrivate::get_pstIFMS1000MeasureFiberLengthChangeThreshold_len(quint16 channel)
{
    return MeasureTable[channel-1].pstIFMS1000MeasureFiberLengthChangeThreshold_len;
}


QString QPSTProductPrivate::get_pstIFMS1000MeasureEndToEndLossCriticalThreshold(quint16 channel)
{
    QString  s;

    _ss.beginGroup(PRODUCT_SETTINGS_GROUP);
    _ss.beginReadArray("pstIFMS1000MeasureEndToEndLossCriticalThreshold");
    _ss.setArrayIndex(channel-1);
    s = _ss.value("pstIFMS1000MeasureEndToEndLossCriticalThreshold", "5").toString();
    _ss.endArray();
    _ss.endGroup();

    return s;
}


size_t QPSTProductPrivate::get_pstIFMS1000MeasureEndToEndLossCriticalThreshold_len(quint16 channel)
{
    return MeasureTable[channel-1].pstIFMS1000MeasureEndToEndLossCriticalThreshold_len;
}


QString QPSTProductPrivate::get_pstIFMS1000MeasureEndToEndLossMajorThreshold(quint16 channel)
{
    QString  s;

    _ss.beginGroup(PRODUCT_SETTINGS_GROUP);
    _ss.beginReadArray("pstIFMS1000MeasureEndToEndLossMajorThreshold");
    _ss.setArrayIndex(channel-1);
    s = _ss.value("pstIFMS1000MeasureEndToEndLossMajorThreshold", "1").toString();
    _ss.endArray();
    _ss.endGroup();

    return s;
}


size_t QPSTProductPrivate::get_pstIFMS1000MeasureEndToEndLossMajorThreshold_len(quint16 channel)
{
    return MeasureTable[channel-1].pstIFMS1000MeasureEndToEndLossMajorThreshold_len;
}


QString QPSTProductPrivate::get_pstIFMS1000MeasureEndToEndLossMinorThreshold(quint16 channel)
{
    QString  s;

    _ss.beginGroup(PRODUCT_SETTINGS_GROUP);
    _ss.beginReadArray("pstIFMS1000MeasureEndToEndLossMinorThreshold");
    _ss.setArrayIndex(channel-1);
    s = _ss.value("pstIFMS1000MeasureEndToEndLossMinorThreshold", "0").toString();
    _ss.endArray();
    _ss.endGroup();

    return s;
}


size_t QPSTProductPrivate::get_pstIFMS1000MeasureEndToEndLossMinorThreshold_len(quint16 channel)
{
    return MeasureTable[channel-1].pstIFMS1000MeasureEndToEndLossMinorThreshold_len;
}


QString QPSTProductPrivate::get_pstIFMS1000MeasureNewLossCriticalThreshold(quint16 channel)
{
    QString  s;

    _ss.beginGroup(PRODUCT_SETTINGS_GROUP);
    _ss.beginReadArray("pstIFMS1000MeasureNewLossCriticalThreshold");
    _ss.setArrayIndex(channel-1);
    s = _ss.value("pstIFMS1000MeasureNewLossCriticalThreshold", "5").toString();
    _ss.endArray();
    _ss.endGroup();

    return s;
}


size_t QPSTProductPrivate::get_pstIFMS1000MeasureNewLossCriticalThreshold_len(quint16 channel)
{
    return MeasureTable[channel-1].pstIFMS1000MeasureNewLossCriticalThreshold_len;
}


QString QPSTProductPrivate::get_pstIFMS1000MeasureNewLossMajorThreshold(quint16 channel)
{
    QString  s;

    _ss.beginGroup(PRODUCT_SETTINGS_GROUP);
    _ss.beginReadArray("pstIFMS1000MeasureNewLossMajorThreshold");
    _ss.setArrayIndex(channel-1);
    s = _ss.value("pstIFMS1000MeasureNewLossMajorThreshold", "2").toString();
    _ss.endArray();
    _ss.endGroup();

    return s;
}


size_t QPSTProductPrivate::get_pstIFMS1000MeasureNewLossMajorThreshold_len(quint16 channel)
{
    return MeasureTable[channel-1].pstIFMS1000MeasureNewLossMajorThreshold_len;
}


QString QPSTProductPrivate::get_pstIFMS1000MeasureNewLossMinorThreshold(quint16 channel)
{
    QString  s;

    _ss.beginGroup(PRODUCT_SETTINGS_GROUP);
    _ss.beginReadArray("pstIFMS1000MeasureNewLossMinorThreshold");
    _ss.setArrayIndex(channel-1);
    s = _ss.value("pstIFMS1000MeasureNewLossMinorThreshold", "0.5").toString();
    _ss.endArray();
    _ss.endGroup();

    return s;
}


size_t QPSTProductPrivate::get_pstIFMS1000MeasureNewLossMinorThreshold_len(quint16 channel)
{
    return MeasureTable[channel-1].pstIFMS1000MeasureNewLossMinorThreshold_len;
}


QString QPSTProductPrivate::get_pstIFMS1000MeasureOldLossCriticalThreshold(quint16 channel)
{
    QString  s;

    _ss.beginGroup(PRODUCT_SETTINGS_GROUP);
    _ss.beginReadArray("pstIFMS1000MeasureOldLossCriticalThreshold");
    _ss.setArrayIndex(channel-1);
    s = _ss.value("pstIFMS1000MeasureOldLossCriticalThreshold", "5").toString();
    _ss.endArray();
    _ss.endGroup();

    return s;
}


size_t QPSTProductPrivate::get_pstIFMS1000MeasureOldLossCriticalThreshold_len(quint16 channel)
{
    return MeasureTable[channel-1].pstIFMS1000MeasureOldLossCriticalThreshold_len;
}


QString QPSTProductPrivate::get_pstIFMS1000MeasureOldLossMajorThreshold(quint16 channel)
{
    QString  s;

    _ss.beginGroup(PRODUCT_SETTINGS_GROUP);
    _ss.beginReadArray("pstIFMS1000MeasureOldLossMajorThreshold");
    _ss.setArrayIndex(channel-1);
    s = _ss.value("pstIFMS1000MeasureOldLossMajorThreshold", "2").toString();
    _ss.endArray();
    _ss.endGroup();

    return s;
}


size_t QPSTProductPrivate::get_pstIFMS1000MeasureOldLossMajorThreshold_len(quint16 channel)
{
    return MeasureTable[channel-1].pstIFMS1000MeasureOldLossMajorThreshold_len;
}


QString QPSTProductPrivate::get_pstIFMS1000MeasureOldLossMinorThreshold(quint16 channel)
{
    QString  s;

    _ss.beginGroup(PRODUCT_SETTINGS_GROUP);
    _ss.beginReadArray("pstIFMS1000MeasureOldLossMinorThreshold");
    _ss.setArrayIndex(channel-1);
    s = _ss.value("pstIFMS1000MeasureOldLossMinorThreshold", "0.5").toString();
    _ss.endArray();
    _ss.endGroup();

    return s;
}


size_t QPSTProductPrivate::get_pstIFMS1000MeasureOldLossMinorThreshold_len(quint16 channel)
{
    return MeasureTable[channel-1].pstIFMS1000MeasureOldLossMinorThreshold_len;
}


QString QPSTProductPrivate::get_pstIFMS1000MeasureTempHighThreshold(quint16 channel)
{
    QString  s;

    _ss.beginGroup(PRODUCT_SETTINGS_GROUP);
    _ss.beginReadArray("pstIFMS1000MeasureTempHighThreshold");
    _ss.setArrayIndex(channel-1);
    s = _ss.value("pstIFMS1000MeasureTempHighThreshold", "55").toString();
    _ss.endArray();
    _ss.endGroup();

    return s;
}


size_t QPSTProductPrivate::get_pstIFMS1000MeasureTempHighThreshold_len(quint16 channel)
{
    return MeasureTable[channel-1].pstIFMS1000MeasureTempHighThreshold_len;
}


QString QPSTProductPrivate::get_pstIFMS1000MeasureTempLowThreshold(quint16 channel)
{
    QString  s;

    _ss.beginGroup(PRODUCT_SETTINGS_GROUP);
    _ss.beginReadArray("pstIFMS1000MeasureTempLowThreshold");
    _ss.setArrayIndex(channel-1);
    s = _ss.value("pstIFMS1000MeasureTempLowThreshold", "-5").toString();
    _ss.endArray();
    _ss.endGroup();

    return s;
}


size_t QPSTProductPrivate::get_pstIFMS1000MeasureTempLowThreshold_len(quint16 channel)
{
    return MeasureTable[channel-1].pstIFMS1000MeasureTempLowThreshold_len;
}


QString QPSTProductPrivate::get_pstIFMS1000MeasureNumber(quint16 channel)
{
    QString s = QString("%1").arg(MeasureTable[channel-1].pstIFMS1000MeasureNumber);
    return s;
}


size_t QPSTProductPrivate::get_pstIFMS1000MeasureNumber_len(quint16 channel)
{
    return MeasureTable[channel-1].pstIFMS1000MeasureNumber_len;
}

// N
QString QPSTProductPrivate::get_pstIFMS1000MeasureNumberSORStoredEachChannel(quint16 channel)
{
    QString s = QString("%1").arg(MeasureTable[channel-1].pstIFMS1000MeasureNumberSORStoredEachChannel);
    return s;
}


size_t QPSTProductPrivate::get_pstIFMS1000MeasureNumberSORStoredEachChannel_len(quint16 channel)
{
    return MeasureTable[channel-1].pstIFMS1000MeasureNumberSORStoredEachChannel_len;
}



void  QPSTProductPrivate::set_pstIFMS1000MeasureStartPosition(quint16 channel, QString s)
{

}


void  QPSTProductPrivate::set_pstIFMS1000MeasureStartPosition_len(quint16 channel, int s)
{

}


void  QPSTProductPrivate::set_pstIFMS1000MeasureEndPosition(quint16 channel, QString s)
{

}


void  QPSTProductPrivate::set_pstIFMS1000MeasureEndPosition_len(quint16 channel, int s)
{

}


void  QPSTProductPrivate::set_pstIFMS1000MeasureRefIndex(quint16 channel, QString s)
{

}


void  QPSTProductPrivate::set_pstIFMS1000MeasureRefIndex_len(quint16 channel, int s)
{

}


void  QPSTProductPrivate::set_pstIFMS1000MeasureResolution(quint16 channel, QString s)
{

}


void  QPSTProductPrivate::set_pstIFMS1000MeasureResolution_len(quint16 channel, int s)
{

}


void  QPSTProductPrivate::set_pstIFMS1000MeasureStatus(quint16 channel, int s)
{
    MeasureTable[channel-1].pstIFMS1000MeasureStatus = (long) (s) ;
}


void  QPSTProductPrivate::set_pstIFMS1000MeasureAction(quint16 channel, int s)
{
    MeasureTable[channel-1].pstIFMS1000MeasureAction = (long) (s) ;
}


void  QPSTProductPrivate::set_pstIFMS1000MeasurePulseWidth(quint16 channel, QString s)
{

}


void  QPSTProductPrivate::set_pstIFMS1000MeasurePulseWidth_len(quint16 channel, int s)
{

}


void  QPSTProductPrivate::set_pstIFMS1000MeasureTime(quint16 channel, int s)
{

}


void  QPSTProductPrivate::set_pstIFMS1000MeasureProgressStatus(quint16 channel, int s)
{
    MeasureTable[channel-1].pstIFMS1000MeasureProgressStatus = (long) (s) ;
}


void  QPSTProductPrivate::set_pstIFMS1000MeasureTLOS(quint16 channel, QString s)
{

}


void  QPSTProductPrivate::set_pstIFMS1000MeasureTLOS_len(quint16 channel, int s)
{

}


void  QPSTProductPrivate::set_pstIFMS1000MeasureTREF(quint16 channel, QString s)
{

}


void  QPSTProductPrivate::set_pstIFMS1000MeasureTREF_len(quint16 channel, int s)
{

}


void  QPSTProductPrivate::set_pstIFMS1000MeasureFiberLengthChangeThreshold(quint16 channel, QString s)
{

}


void  QPSTProductPrivate::set_pstIFMS1000MeasureFiberLengthChangeThreshold_len(quint16 channel, int s)
{

}


void  QPSTProductPrivate::set_pstIFMS1000MeasureEndToEndLossCriticalThreshold(quint16 channel, QString s)
{

}


void  QPSTProductPrivate::set_pstIFMS1000MeasureEndToEndLossCriticalThreshold_len(quint16 channel, int s)
{

}


void  QPSTProductPrivate::set_pstIFMS1000MeasureEndToEndLossMajorThreshold(quint16 channel, QString s)
{

}


void  QPSTProductPrivate::set_pstIFMS1000MeasureEndToEndLossMajorThreshold_len(quint16 channel, int s)
{

}


void  QPSTProductPrivate::set_pstIFMS1000MeasureEndToEndLossMinorThreshold(quint16 channel, QString s)
{

}


void  QPSTProductPrivate::set_pstIFMS1000MeasureEndToEndLossMinorThreshold_len(quint16 channel, int s)
{

}


void  QPSTProductPrivate::set_pstIFMS1000MeasureNewLossCriticalThreshold(quint16 channel, QString s)
{

}


void  QPSTProductPrivate::set_pstIFMS1000MeasureNewLossCriticalThreshold_len(quint16 channel, int s)
{

}


void  QPSTProductPrivate::set_pstIFMS1000MeasureNewLossMajorThreshold(quint16 channel, QString s)
{

}


void  QPSTProductPrivate::set_pstIFMS1000MeasureNewLossMajorThreshold_len(quint16 channel, int s)
{

}


void  QPSTProductPrivate::set_pstIFMS1000MeasureNewLossMinorThreshold(quint16 channel, QString s)
{

}


void  QPSTProductPrivate::set_pstIFMS1000MeasureNewLossMinorThreshold_len(quint16 channel, int s)
{

}


void  QPSTProductPrivate::set_pstIFMS1000MeasureOldLossCriticalThreshold(quint16 channel, QString s)
{

}


void  QPSTProductPrivate::set_pstIFMS1000MeasureOldLossCriticalThreshold_len(quint16 channel, int s)
{

}


void  QPSTProductPrivate::set_pstIFMS1000MeasureOldLossMajorThreshold(quint16 channel, QString s)
{

}


void  QPSTProductPrivate::set_pstIFMS1000MeasureOldLossMajorThreshold_len(quint16 channel, int s)
{

}


void  QPSTProductPrivate::set_pstIFMS1000MeasureOldLossMinorThreshold(quint16 channel, QString s)
{

}


void  QPSTProductPrivate::set_pstIFMS1000MeasureOldLossMinorThreshold_len(quint16 channel, int s)
{

}


void  QPSTProductPrivate::set_pstIFMS1000MeasureTempHighThreshold(quint16 channel, QString s)
{

}


void  QPSTProductPrivate::set_pstIFMS1000MeasureTempHighThreshold_len(quint16 channel, int s)
{

}


void  QPSTProductPrivate::set_pstIFMS1000MeasureTempLowThreshold(quint16 channel, QString s)
{

}


void  QPSTProductPrivate::set_pstIFMS1000MeasureTempLowThreshold_len(quint16 channel, int s)
{

}


void  QPSTProductPrivate::set_pstIFMS1000MeasureNumber(quint16 channel, QString s)
{

}


void  QPSTProductPrivate::set_pstIFMS1000MeasureNumber_len(quint16 channel, int s)
{

}


void  QPSTProductPrivate::set_pstIFMS1000MeasureNumberSORStoredEachChannel(quint16 channel, QString s)
{

}


void  QPSTProductPrivate::set_pstIFMS1000MeasureNumberSORStoredEachChannel_len(quint16 channel, int s)
{

}
