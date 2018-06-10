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
				
		strcpy(measure.pstIFMS1000MeasureEndToEndLossHighThreshold, "5");
		measure.pstIFMS1000MeasureEndToEndLossHighThreshold_len = 1;
				
		strcpy(measure.pstIFMS1000MeasureEndToEndLossMiddleThreshold, "1");
		measure.pstIFMS1000MeasureEndToEndLossMiddleThreshold_len = 1;
				
		strcpy(measure.pstIFMS1000MeasureEndToEndLossLowThreshold, "0");
		measure.pstIFMS1000MeasureEndToEndLossLowThreshold_len = 1;
				
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
        
        strcpy(measure.pstIFMS1000MeasureEventPositionChangeThreshold, "100");
        measure.pstIFMS1000MeasureEventPositionChangeThreshold_len = 3;
        
        strcpy(measure.pstIFMS1000MeasureReserved2, "-5");
        measure.pstIFMS1000MeasureReserved2_len = 2;
        
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
    QPST *p = (QPST*)agent;
//    p->m_gpios.configureGPIO(GPIO_ALERT_0, QString("in"));
    if( p->m_gpios.readGPIO(GPIO_ALERT_0) == 1){
        return 0;
    }
    else
    {
        return 1;
    }
}
long QPSTProductPrivate::get_pstIFMS1000SysLedPW2(QObject *agent)
{
    QPST *p = (QPST*)agent;
//    p->m_gpios.configureGPIO(GPIO_ALERT_1, QString("in"));
    if( p->m_gpios.readGPIO(GPIO_ALERT_1) == 1){
        return 0;
    }
    else
    {
        return 1;
    }
}
long QPSTProductPrivate::get_pstIFMS1000SysLedStatus(QObject *agent)
{
    int sh = 0;
    int sl = 0;
    QPST *p = (QPST*)agent;
//    p->m_gpios.configureGPIO(GPIO_STA_ALARMH, QString("out"));
//    p->m_gpios.configureGPIO(GPIO_STA_ALARML, QString("out"));

    sh = p->m_gpios.readGPIO(GPIO_STA_ALARMH);
    sl = p->m_gpios.readGPIO(GPIO_STA_ALARML);


    if(  sh == sl){
        return 0;
    }
    else if(sh > sl)
    {
        return 1;
    }
    else
    {
        return 2;
    }
}

QString QPSTProductPrivate::get_pstIFMS1000PortRxPwr(quint16 channel)
{
    QString  s;

    _ss.beginGroup(PRODUCT_SETTINGS_GROUP);
    _ss.beginReadArray("pstIFMS1000PortRxPwr");
    _ss.setArrayIndex(channel-1);
    s = _ss.value("pstIFMS1000PortRxPwr", "0").toString();
    _ss.endArray();
    _ss.endGroup();

    return s;
}

          
size_t QPSTProductPrivate::get_pstIFMS1000PortRxPwr_len(quint16 channel)
{
    return  PortInfoTable[channel-1].pstIFMS1000PortRxPwr_len;
}

      
QString QPSTProductPrivate::get_pstIFMS1000PortTxPwr(quint16 channel)
{
    QString  s;

    _ss.beginGroup(PRODUCT_SETTINGS_GROUP);
    _ss.beginReadArray("pstIFMS1000PortTxPwr");
    _ss.setArrayIndex(channel-1);
    s = _ss.value("pstIFMS1000PortTxPwr", "0").toString();
    _ss.endArray();
    _ss.endGroup();

    return s;
}

          
size_t QPSTProductPrivate::get_pstIFMS1000PortTxPwr_len(quint16 channel)
{
    return  PortInfoTable[channel-1].pstIFMS1000PortTxPwr_len;
}

     
long QPSTProductPrivate::get_pstIFMS1000PortWorkMode(quint16 channel)
{
    return  PortInfoTable[channel-1].pstIFMS1000PortWorkMode;
}

// need to be stored           
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

// need to be stored             
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
    _ss.beginGroup(PRODUCT_SETTINGS_GROUP);
        _ss.beginWriteArray("pstIFMS1000PortRxPwr");
            _ss.setArrayIndex(channel-1);
            _ss.setValue("pstIFMS1000PortRxPwr", s);
        _ss.endArray();
    _ss.endGroup();
    _ss.sync();
}

          
void QPSTProductPrivate::set_pstIFMS1000PortRxPwr_len(quint16 channel, int s)
{
    PortInfoTable[channel-1].pstIFMS1000PortRxPwr_len = s;
}

      
void QPSTProductPrivate::set_pstIFMS1000PortTxPwr(quint16 channel,QString s)
{
    _ss.beginGroup(PRODUCT_SETTINGS_GROUP);
        _ss.beginWriteArray("pstIFMS1000PortTxPwr");
            _ss.setArrayIndex(channel-1);
            _ss.setValue("pstIFMS1000PortTxPwr", s);
        _ss.endArray();
    _ss.endGroup();
    _ss.sync();
}

          
void QPSTProductPrivate::set_pstIFMS1000PortTxPwr_len(quint16 channel,int s)
{
    PortInfoTable[channel-1].pstIFMS1000PortTxPwr_len = s;
}

     
void QPSTProductPrivate::set_pstIFMS1000PortWorkMode(quint16 channel,int s)
{
    PortInfoTable[channel-1].pstIFMS1000PortWorkMode = s;
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
    PortInfoTable[channel-1].pstIFMS1000PortRunningStatus = s;
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
	return MeasureTable[channel-1].pstIFMS1000MeasureStartPosition_len;
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
	return MeasureTable[channel-1].pstIFMS1000MeasureEndPosition_len;
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
	 return MeasureTable[channel-1].pstIFMS1000MeasureRefIndex_len;
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
	return MeasureTable[channel-1].pstIFMS1000MeasureResolution_len;
}

// no need to be stored
long QPSTProductPrivate::get_pstIFMS1000MeasureStatus(quint16 channel)
{
	return MeasureTable[channel-1].pstIFMS1000MeasureStatus;
}

// no need to be stored
long QPSTProductPrivate::get_pstIFMS1000MeasureAction(quint16 channel)
{
    return MeasureTable[channel-1].pstIFMS1000MeasureAction;
}

// need to be stored
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
    int  s;

    _ss.beginGroup(PRODUCT_SETTINGS_GROUP);
    _ss.beginReadArray("pstIFMS1000MeasureTime");
    _ss.setArrayIndex(channel-1);
    s = _ss.value("pstIFMS1000MeasureTime", "30").toInt();
    _ss.endArray();
    _ss.endGroup();

    return s;
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


QString QPSTProductPrivate::get_pstIFMS1000MeasureEndToEndLossHighThreshold(quint16 channel)
{
    QString  s;

    _ss.beginGroup(PRODUCT_SETTINGS_GROUP);
    _ss.beginReadArray("pstIFMS1000MeasureEndToEndLossHighThreshold");
    _ss.setArrayIndex(channel-1);
    s = _ss.value("pstIFMS1000MeasureEndToEndLossHighThreshold", "5").toString();
    _ss.endArray();
    _ss.endGroup();

    return s;
}


size_t QPSTProductPrivate::get_pstIFMS1000MeasureEndToEndLossHighThreshold_len(quint16 channel)
{
    return MeasureTable[channel-1].pstIFMS1000MeasureEndToEndLossHighThreshold_len;
}


QString QPSTProductPrivate::get_pstIFMS1000MeasureEndToEndLossMiddleThreshold(quint16 channel)
{
    QString  s;

    _ss.beginGroup(PRODUCT_SETTINGS_GROUP);
    _ss.beginReadArray("pstIFMS1000MeasureEndToEndLossMiddleThreshold");
    _ss.setArrayIndex(channel-1);
    s = _ss.value("pstIFMS1000MeasureEndToEndLossMiddleThreshold", "1").toString();
    _ss.endArray();
    _ss.endGroup();

    return s;
}


size_t QPSTProductPrivate::get_pstIFMS1000MeasureEndToEndLossMiddleThreshold_len(quint16 channel)
{
    return MeasureTable[channel-1].pstIFMS1000MeasureEndToEndLossMiddleThreshold_len;
}


QString QPSTProductPrivate::get_pstIFMS1000MeasureEndToEndLossLowThreshold(quint16 channel)
{
    QString  s;

    _ss.beginGroup(PRODUCT_SETTINGS_GROUP);
    _ss.beginReadArray("pstIFMS1000MeasureEndToEndLossLowThreshold");
    _ss.setArrayIndex(channel-1);
    s = _ss.value("pstIFMS1000MeasureEndToEndLossLowThreshold", "0").toString();
    _ss.endArray();
    _ss.endGroup();

    return s;
}


size_t QPSTProductPrivate::get_pstIFMS1000MeasureEndToEndLossLowThreshold_len(quint16 channel)
{
    return MeasureTable[channel-1].pstIFMS1000MeasureEndToEndLossLowThreshold_len;
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


QString QPSTProductPrivate::get_pstIFMS1000MeasureEventPositionChangeThreshold(quint16 channel)
{
    QString  s;

    _ss.beginGroup(PRODUCT_SETTINGS_GROUP);
    _ss.beginReadArray("pstIFMS1000MeasureEventPositionChangeThreshold");
    _ss.setArrayIndex(channel-1);
    s = _ss.value("pstIFMS1000MeasureEventPositionChangeThreshold", "100").toString();
    _ss.endArray();
    _ss.endGroup();

    return s;
}


size_t QPSTProductPrivate::get_pstIFMS1000MeasureEventPositionChangeThreshold_len(quint16 channel)
{
    return MeasureTable[channel-1].pstIFMS1000MeasureEventPositionChangeThreshold_len;
}


QString QPSTProductPrivate::get_pstIFMS1000MeasureReserved2(quint16 channel)
{
    QString  s;

    _ss.beginGroup(PRODUCT_SETTINGS_GROUP);
    _ss.beginReadArray("pstIFMS1000MeasureReserved2");
    _ss.setArrayIndex(channel-1);
    s = _ss.value("pstIFMS1000MeasureReserved2", "-5").toString();
    _ss.endArray();
    _ss.endGroup();

    return s;
}


size_t QPSTProductPrivate::get_pstIFMS1000MeasureReserved2_len(quint16 channel)
{
    return MeasureTable[channel-1].pstIFMS1000MeasureReserved2_len;
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

// no need to be stored
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
    _ss.beginGroup(PRODUCT_SETTINGS_GROUP);
        _ss.beginWriteArray("pstIFMS1000MeasureStartPosition");
            _ss.setArrayIndex(channel-1);
            _ss.setValue("pstIFMS1000MeasureStartPosition", s);
        _ss.endArray();
    _ss.endGroup();
    _ss.sync();
}


void  QPSTProductPrivate::set_pstIFMS1000MeasureStartPosition_len(quint16 channel, int s)
{
	MeasureTable[channel-1].pstIFMS1000MeasureStartPosition_len = s;
}


void  QPSTProductPrivate::set_pstIFMS1000MeasureEndPosition(quint16 channel, QString s)
{
	quint16 module_index = (channel-1)/CHANNELS_PER_MODULE;
    _ss.beginGroup(PRODUCT_SETTINGS_GROUP);
        _ss.beginWriteArray("pstIFMS1000MeasureEndPosition");
		for(int i=0;i<CHANNELS_PER_MODULE;i++){
            _ss.setArrayIndex(module_index*CHANNELS_PER_MODULE+i);
            _ss.setValue("pstIFMS1000MeasureEndPosition", s);
			}
        _ss.endArray();
    _ss.endGroup();
    _ss.sync();
}


void  QPSTProductPrivate::set_pstIFMS1000MeasureEndPosition_len(quint16 channel, int s)
{
	MeasureTable[channel-1].pstIFMS1000MeasureEndPosition_len = s;
}


void  QPSTProductPrivate::set_pstIFMS1000MeasureRefIndex(quint16 channel, QString s)
{
	quint16 module_index = (channel-1)/CHANNELS_PER_MODULE;
    _ss.beginGroup(PRODUCT_SETTINGS_GROUP);
        _ss.beginWriteArray("pstIFMS1000MeasureRefIndex");
		for(int i=0;i<CHANNELS_PER_MODULE;i++){
            _ss.setArrayIndex(module_index*CHANNELS_PER_MODULE+i);
            _ss.setValue("pstIFMS1000MeasureRefIndex", s);
			}
        _ss.endArray();
    _ss.endGroup();
    _ss.sync();
}


void  QPSTProductPrivate::set_pstIFMS1000MeasureRefIndex_len(quint16 channel, int s)
{
	MeasureTable[channel-1].pstIFMS1000MeasureRefIndex_len = s;
}


void  QPSTProductPrivate::set_pstIFMS1000MeasureResolution(quint16 channel, QString s)
{
	quint16 module_index = (channel-1)/CHANNELS_PER_MODULE;
    _ss.beginGroup(PRODUCT_SETTINGS_GROUP);
        _ss.beginWriteArray("pstIFMS1000MeasureResolution");
		for(int i=0;i<CHANNELS_PER_MODULE;i++){
            _ss.setArrayIndex(module_index*CHANNELS_PER_MODULE+i);
            _ss.setValue("pstIFMS1000MeasureResolution", s);
			}
        _ss.endArray();
    _ss.endGroup();
    _ss.sync();
}


void  QPSTProductPrivate::set_pstIFMS1000MeasureResolution_len(quint16 channel, int s)
{
	MeasureTable[channel-1].pstIFMS1000MeasureResolution_len = s;
}


void  QPSTProductPrivate::set_pstIFMS1000MeasureStatus(quint16 channel, int s)
{
    MeasureTable[channel-1].pstIFMS1000MeasureStatus = (long) (s) ;
}


void  QPSTProductPrivate::set_pstIFMS1000MeasureAction(quint16 channel, int s)
{
    quint16 module_index = (channel-1)/CHANNELS_PER_MODULE;
    for(int i = 0; i< CHANNELS_PER_MODULE; i++){
        MeasureTable[module_index*CHANNELS_PER_MODULE + i].pstIFMS1000MeasureAction = (long) (s) ;
    }
}


void  QPSTProductPrivate::set_pstIFMS1000MeasurePulseWidth(quint16 channel, QString s)
{
	quint16 module_index = (channel-1)/CHANNELS_PER_MODULE;
    _ss.beginGroup(PRODUCT_SETTINGS_GROUP);
        _ss.beginWriteArray("pstIFMS1000MeasurePulseWidth");
		for(int i=0;i<CHANNELS_PER_MODULE;i++){
            _ss.setArrayIndex(module_index*CHANNELS_PER_MODULE+i);
            _ss.setValue("pstIFMS1000MeasurePulseWidth", s);
			}
        _ss.endArray();
    _ss.endGroup();
    _ss.sync();
}


void  QPSTProductPrivate::set_pstIFMS1000MeasurePulseWidth_len(quint16 channel, int s)
{
    MeasureTable[channel-1].pstIFMS1000MeasurePulseWidth_len = (long) (s) ;
}


void  QPSTProductPrivate::set_pstIFMS1000MeasureTime(quint16 channel, int s)
{
	quint16 module_index = (channel-1)/CHANNELS_PER_MODULE;
    _ss.beginGroup(PRODUCT_SETTINGS_GROUP);
        _ss.beginWriteArray("pstIFMS1000MeasureTime");
		for(int i=0;i<CHANNELS_PER_MODULE;i++){
            _ss.setArrayIndex(module_index*CHANNELS_PER_MODULE+i);
            _ss.setValue("pstIFMS1000MeasureTime", s);
			}
        _ss.endArray();
    _ss.endGroup();
    _ss.sync();
}


void  QPSTProductPrivate::set_pstIFMS1000MeasureProgressStatus(quint16 channel, int s)
{
    MeasureTable[channel-1].pstIFMS1000MeasureProgressStatus = (long) (s) ;
}


void  QPSTProductPrivate::set_pstIFMS1000MeasureTLOS(quint16 channel, QString s)
{
    _ss.beginGroup(PRODUCT_SETTINGS_GROUP);
        _ss.beginWriteArray("pstIFMS1000MeasureTLOS");
            _ss.setArrayIndex(channel-1);
            _ss.setValue("pstIFMS1000MeasureTLOS", s);
        _ss.endArray();
    _ss.endGroup();
    _ss.sync();
}


void  QPSTProductPrivate::set_pstIFMS1000MeasureTLOS_len(quint16 channel, int s)
{
    MeasureTable[channel-1].pstIFMS1000MeasureTLOS_len = (long) (s) ;
}


void  QPSTProductPrivate::set_pstIFMS1000MeasureTREF(quint16 channel, QString s)
{
    _ss.beginGroup(PRODUCT_SETTINGS_GROUP);
        _ss.beginWriteArray("pstIFMS1000MeasureTREF");
            _ss.setArrayIndex(channel-1);
            _ss.setValue("pstIFMS1000MeasureTREF", s);
        _ss.endArray();
    _ss.endGroup();
    _ss.sync();
}


void  QPSTProductPrivate::set_pstIFMS1000MeasureTREF_len(quint16 channel, int s)
{
    MeasureTable[channel-1].pstIFMS1000MeasureTREF_len = (long) (s) ;
}


void  QPSTProductPrivate::set_pstIFMS1000MeasureFiberLengthChangeThreshold(quint16 channel, QString s)
{
    _ss.beginGroup(PRODUCT_SETTINGS_GROUP);
        _ss.beginWriteArray("pstIFMS1000MeasureFiberLengthChangeThreshold");
            _ss.setArrayIndex(channel-1);
            _ss.setValue("pstIFMS1000MeasureFiberLengthChangeThreshold", s);
        _ss.endArray();
    _ss.endGroup();
    _ss.sync();
}


void  QPSTProductPrivate::set_pstIFMS1000MeasureFiberLengthChangeThreshold_len(quint16 channel, int s)
{
    MeasureTable[channel-1].pstIFMS1000MeasureFiberLengthChangeThreshold_len = (long) (s) ;
}


void  QPSTProductPrivate::set_pstIFMS1000MeasureEndToEndLossHighThreshold(quint16 channel, QString s)
{
    _ss.beginGroup(PRODUCT_SETTINGS_GROUP);
        _ss.beginWriteArray("pstIFMS1000MeasureEndToEndLossHighThreshold");
            _ss.setArrayIndex(channel-1);
            _ss.setValue("pstIFMS1000MeasureEndToEndLossHighThreshold", s);
        _ss.endArray();
    _ss.endGroup();
    _ss.sync();
}


void  QPSTProductPrivate::set_pstIFMS1000MeasureEndToEndLossHighThreshold_len(quint16 channel, int s)
{
    MeasureTable[channel-1].pstIFMS1000MeasureEndToEndLossHighThreshold_len = (long) (s) ;
}


void  QPSTProductPrivate::set_pstIFMS1000MeasureEndToEndLossMiddleThreshold(quint16 channel, QString s)
{
    _ss.beginGroup(PRODUCT_SETTINGS_GROUP);
        _ss.beginWriteArray("pstIFMS1000MeasureEndToEndLossMiddleThreshold");
            _ss.setArrayIndex(channel-1);
            _ss.setValue("pstIFMS1000MeasureEndToEndLossMiddleThreshold", s);
        _ss.endArray();
    _ss.endGroup();
    _ss.sync();
}


void  QPSTProductPrivate::set_pstIFMS1000MeasureEndToEndLossMiddleThreshold_len(quint16 channel, int s)
{
    MeasureTable[channel-1].pstIFMS1000MeasureEndToEndLossMiddleThreshold_len = (long) (s) ;

}


void  QPSTProductPrivate::set_pstIFMS1000MeasureEndToEndLossLowThreshold(quint16 channel, QString s)
{
    _ss.beginGroup(PRODUCT_SETTINGS_GROUP);
        _ss.beginWriteArray("pstIFMS1000MeasureEndToEndLossLowThreshold");
            _ss.setArrayIndex(channel-1);
            _ss.setValue("pstIFMS1000MeasureEndToEndLossLowThreshold", s);
        _ss.endArray();
    _ss.endGroup();
    _ss.sync();
}


void  QPSTProductPrivate::set_pstIFMS1000MeasureEndToEndLossLowThreshold_len(quint16 channel, int s)
{
    MeasureTable[channel-1].pstIFMS1000MeasureEndToEndLossLowThreshold_len = (long) (s) ;
}


void  QPSTProductPrivate::set_pstIFMS1000MeasureNewLossCriticalThreshold(quint16 channel, QString s)
{
    _ss.beginGroup(PRODUCT_SETTINGS_GROUP);
        _ss.beginWriteArray("pstIFMS1000MeasureNewLossCriticalThreshold");
            _ss.setArrayIndex(channel-1);
            _ss.setValue("pstIFMS1000MeasureNewLossCriticalThreshold", s);
        _ss.endArray();
    _ss.endGroup();
    _ss.sync();
}


void  QPSTProductPrivate::set_pstIFMS1000MeasureNewLossCriticalThreshold_len(quint16 channel, int s)
{
    MeasureTable[channel-1].pstIFMS1000MeasureNewLossCriticalThreshold_len = (long) (s) ;
}


void  QPSTProductPrivate::set_pstIFMS1000MeasureNewLossMajorThreshold(quint16 channel, QString s)
{
    _ss.beginGroup(PRODUCT_SETTINGS_GROUP);
        _ss.beginWriteArray("pstIFMS1000MeasureNewLossMajorThreshold");
            _ss.setArrayIndex(channel-1);
            _ss.setValue("pstIFMS1000MeasureNewLossMajorThreshold", s);
        _ss.endArray();
    _ss.endGroup();
    _ss.sync();
}


void  QPSTProductPrivate::set_pstIFMS1000MeasureNewLossMajorThreshold_len(quint16 channel, int s)
{
    MeasureTable[channel-1].pstIFMS1000MeasureNewLossMajorThreshold_len = (long) (s) ;
}


void  QPSTProductPrivate::set_pstIFMS1000MeasureNewLossMinorThreshold(quint16 channel, QString s)
{
    _ss.beginGroup(PRODUCT_SETTINGS_GROUP);
        _ss.beginWriteArray("pstIFMS1000MeasureNewLossMinorThreshold");
            _ss.setArrayIndex(channel-1);
            _ss.setValue("pstIFMS1000MeasureNewLossMinorThreshold", s);
        _ss.endArray();
    _ss.endGroup();
    _ss.sync();
}


void  QPSTProductPrivate::set_pstIFMS1000MeasureNewLossMinorThreshold_len(quint16 channel, int s)
{
    MeasureTable[channel-1].pstIFMS1000MeasureNewLossMinorThreshold_len = (long) (s) ;
}


void  QPSTProductPrivate::set_pstIFMS1000MeasureOldLossCriticalThreshold(quint16 channel, QString s)
{
    _ss.beginGroup(PRODUCT_SETTINGS_GROUP);
        _ss.beginWriteArray("pstIFMS1000MeasureOldLossCriticalThreshold");
            _ss.setArrayIndex(channel-1);
            _ss.setValue("pstIFMS1000MeasureOldLossCriticalThreshold", s);
        _ss.endArray();
    _ss.endGroup();
    _ss.sync();
}


void  QPSTProductPrivate::set_pstIFMS1000MeasureOldLossCriticalThreshold_len(quint16 channel, int s)
{
    MeasureTable[channel-1].pstIFMS1000MeasureOldLossCriticalThreshold_len = (long) (s) ;
}


void  QPSTProductPrivate::set_pstIFMS1000MeasureOldLossMajorThreshold(quint16 channel, QString s)
{
    _ss.beginGroup(PRODUCT_SETTINGS_GROUP);
        _ss.beginWriteArray("pstIFMS1000MeasureOldLossMajorThreshold");
            _ss.setArrayIndex(channel-1);
            _ss.setValue("pstIFMS1000MeasureOldLossMajorThreshold", s);
        _ss.endArray();
    _ss.endGroup();
    _ss.sync();
}


void  QPSTProductPrivate::set_pstIFMS1000MeasureOldLossMajorThreshold_len(quint16 channel, int s)
{
    MeasureTable[channel-1].pstIFMS1000MeasureOldLossMajorThreshold_len = (long) (s) ;
}


void  QPSTProductPrivate::set_pstIFMS1000MeasureOldLossMinorThreshold(quint16 channel, QString s)
{
    _ss.beginGroup(PRODUCT_SETTINGS_GROUP);
        _ss.beginWriteArray("pstIFMS1000MeasureOldLossMinorThreshold");
            _ss.setArrayIndex(channel-1);
            _ss.setValue("pstIFMS1000MeasureOldLossMinorThreshold", s);
        _ss.endArray();
    _ss.endGroup();
    _ss.sync();
}


void  QPSTProductPrivate::set_pstIFMS1000MeasureOldLossMinorThreshold_len(quint16 channel, int s)
{
    MeasureTable[channel-1].pstIFMS1000MeasureOldLossMinorThreshold_len = (long) (s) ;
}


void  QPSTProductPrivate::set_pstIFMS1000MeasureEventPositionChangeThreshold(quint16 channel, QString s)
{
    _ss.beginGroup(PRODUCT_SETTINGS_GROUP);
        _ss.beginWriteArray("pstIFMS1000MeasureEventPositionChangeThreshold");
            _ss.setArrayIndex(channel-1);
            _ss.setValue("pstIFMS1000MeasureEventPositionChangeThreshold", s);
        _ss.endArray();
    _ss.endGroup();
    _ss.sync();
}


void  QPSTProductPrivate::set_pstIFMS1000MeasureEventPositionChangeThreshold_len(quint16 channel, int s)
{
    MeasureTable[channel-1].pstIFMS1000MeasureEventPositionChangeThreshold_len = (long) (s) ;
}


void  QPSTProductPrivate::set_pstIFMS1000MeasureReserved2(quint16 channel, QString s)
{
    _ss.beginGroup(PRODUCT_SETTINGS_GROUP);
        _ss.beginWriteArray("pstIFMS1000MeasureReserved2");
            _ss.setArrayIndex(channel-1);
            _ss.setValue("pstIFMS1000MeasureReserved2", s);
        _ss.endArray();
    _ss.endGroup();
    _ss.sync();
}


void  QPSTProductPrivate::set_pstIFMS1000MeasureReserved2_len(quint16 channel, int s)
{
    MeasureTable[channel-1].pstIFMS1000MeasureReserved2_len = (long) (s) ;
}


void  QPSTProductPrivate::set_pstIFMS1000MeasureNumber(quint16 channel, QString s)
{
    strcpy(MeasureTable[channel-1].pstIFMS1000MeasureNumber, s.toLatin1().data());
}


void  QPSTProductPrivate::set_pstIFMS1000MeasureNumber_len(quint16 channel, int s)
{
// Read only
}


void  QPSTProductPrivate::set_pstIFMS1000MeasureNumberSORStoredEachChannel(quint16 channel, QString s)
{
    _ss.beginGroup(PRODUCT_SETTINGS_GROUP);
        _ss.beginWriteArray("pstIFMS1000MeasureNumberSORStoredEachChannel");
            _ss.setArrayIndex(channel-1);
            _ss.setValue("pstIFMS1000MeasureNumberSORStoredEachChannel", s);
        _ss.endArray();
    _ss.endGroup();
    _ss.sync();
}


void  QPSTProductPrivate::set_pstIFMS1000MeasureNumberSORStoredEachChannel_len(quint16 channel, int s)
{
    MeasureTable[channel-1].pstIFMS1000MeasureNumberSORStoredEachChannel_len = (long) (s) ;
}

bool  QPSTProductPrivate::is_pstIFMS1000Measuring(quint16 channel)
{
    bool ret = true;
    long  action = get_pstIFMS1000MeasureAction(channel);
    if((action == OTDR_WORK_MODE_AUTO) || (action == OTDR_WORK_MODE_SINGLE))
    {
        ret = true;
    }
    else
    {
        ret = false;
    }
    return ret;
}

long  QPSTProductPrivate::get_pstIFMS1000PortLedStatus(int index)
{
    return 0;
}

void  QPSTProductPrivate::set_pstIFMS1000PortLedStatus(int index, int status)
{
    QPST *pst = QPST::getInstance();
    if(index == 1){
        pst->m_gpios.configureGPIO(GPIO_FIBER1_ALARMH, QString("out"));
        pst->m_gpios.configureGPIO(GPIO_FIBER1_ALARML, QString("out"));
        if(status == 0){
            pst->m_gpios.writeGPIO(GPIO_FIBER1_ALARMH, 0);
            pst->m_gpios.writeGPIO(GPIO_FIBER1_ALARML, 0);
        }
        else if(status == 1)
        {
            pst->m_gpios.writeGPIO(GPIO_FIBER1_ALARMH, 1);
            pst->m_gpios.writeGPIO(GPIO_FIBER1_ALARML, 0);
        }
        else if(status == 2){
            pst->m_gpios.writeGPIO(GPIO_FIBER1_ALARMH, 0);
            pst->m_gpios.writeGPIO(GPIO_FIBER1_ALARML, 1);
        }
    }
    if(index == 2){
        pst->m_gpios.configureGPIO(GPIO_FIBER2_ALARMH, QString("out"));
        pst->m_gpios.configureGPIO(GPIO_FIBER2_ALARML, QString("out"));
        if(status == 0){
            pst->m_gpios.writeGPIO(GPIO_FIBER2_ALARMH, 0);
            pst->m_gpios.writeGPIO(GPIO_FIBER2_ALARML, 0);
        }
        else if(status == 1)
        {
            pst->m_gpios.writeGPIO(GPIO_FIBER2_ALARMH, 1);
            pst->m_gpios.writeGPIO(GPIO_FIBER2_ALARML, 0);
        }
        else if(status == 2){
            pst->m_gpios.writeGPIO(GPIO_FIBER2_ALARMH, 0);
            pst->m_gpios.writeGPIO(GPIO_FIBER2_ALARML, 1);
        }
    }
    if(index == 3){
        pst->m_gpios.configureGPIO(GPIO_FIBER3_ALARMH, QString("out"));
        pst->m_gpios.configureGPIO(GPIO_FIBER3_ALARML, QString("out"));
        if(status == 0){
            pst->m_gpios.writeGPIO(GPIO_FIBER3_ALARMH, 0);
            pst->m_gpios.writeGPIO(GPIO_FIBER3_ALARML, 0);
        }
        else if(status == 1)
        {
            pst->m_gpios.writeGPIO(GPIO_FIBER3_ALARMH, 1);
            pst->m_gpios.writeGPIO(GPIO_FIBER3_ALARML, 0);
        }
        else if(status == 2){
            pst->m_gpios.writeGPIO(GPIO_FIBER3_ALARMH, 0);
            pst->m_gpios.writeGPIO(GPIO_FIBER3_ALARML, 1);
        }

    }
    if(index == 4){
        pst->m_gpios.configureGPIO(GPIO_FIBER4_ALARMH, QString("out"));
        pst->m_gpios.configureGPIO(GPIO_FIBER4_ALARML, QString("out"));
        if(status == 0){
            pst->m_gpios.writeGPIO(GPIO_FIBER4_ALARMH, 0);
            pst->m_gpios.writeGPIO(GPIO_FIBER4_ALARML, 0);
        }
        else if(status == 1)
        {
            pst->m_gpios.writeGPIO(GPIO_FIBER4_ALARMH, 1);
            pst->m_gpios.writeGPIO(GPIO_FIBER4_ALARML, 0);
        }
        else if(status == 2){
            pst->m_gpios.writeGPIO(GPIO_FIBER4_ALARMH, 0);
            pst->m_gpios.writeGPIO(GPIO_FIBER4_ALARML, 1);
        }

    }
    if(index == 5){
        pst->m_gpios.configureGPIO(GPIO_FIBER5_ALARMH, QString("out"));
        pst->m_gpios.configureGPIO(GPIO_FIBER5_ALARML, QString("out"));
        if(status == 0){
            pst->m_gpios.writeGPIO(GPIO_FIBER5_ALARMH, 0);
            pst->m_gpios.writeGPIO(GPIO_FIBER5_ALARML, 0);
        }
        else if(status == 1)
        {
            pst->m_gpios.writeGPIO(GPIO_FIBER5_ALARMH, 1);
            pst->m_gpios.writeGPIO(GPIO_FIBER5_ALARML, 0);
        }
        else if(status == 2){
            pst->m_gpios.writeGPIO(GPIO_FIBER5_ALARMH, 0);
            pst->m_gpios.writeGPIO(GPIO_FIBER5_ALARML, 1);
        }

    }
    if(index == 6){
        pst->m_gpios.configureGPIO(GPIO_FIBER6_ALARMH, QString("out"));
        pst->m_gpios.configureGPIO(GPIO_FIBER6_ALARML, QString("out"));
        if(status == 0){
            pst->m_gpios.writeGPIO(GPIO_FIBER6_ALARMH, 0);
            pst->m_gpios.writeGPIO(GPIO_FIBER6_ALARML, 0);
        }
        else if(status == 1)
        {
            pst->m_gpios.writeGPIO(GPIO_FIBER6_ALARMH, 1);
            pst->m_gpios.writeGPIO(GPIO_FIBER6_ALARML, 0);
        }
        else if(status == 2){
            pst->m_gpios.writeGPIO(GPIO_FIBER6_ALARMH, 0);
            pst->m_gpios.writeGPIO(GPIO_FIBER6_ALARML, 1);
        }

    }
    if(index == 7){
        pst->m_gpios.configureGPIO(GPIO_FIBER7_ALARMH, QString("out"));
        pst->m_gpios.configureGPIO(GPIO_FIBER7_ALARML, QString("out"));
        if(status == 0){
            pst->m_gpios.writeGPIO(GPIO_FIBER7_ALARMH, 0);
            pst->m_gpios.writeGPIO(GPIO_FIBER7_ALARML, 0);
        }
        else if(status == 1)
        {
            pst->m_gpios.writeGPIO(GPIO_FIBER7_ALARMH, 1);
            pst->m_gpios.writeGPIO(GPIO_FIBER7_ALARML, 0);
        }
        else if(status == 2){
            pst->m_gpios.writeGPIO(GPIO_FIBER7_ALARMH, 0);
            pst->m_gpios.writeGPIO(GPIO_FIBER7_ALARML, 1);
        }

    }
    if(index == 8){
        pst->m_gpios.configureGPIO(GPIO_FIBER8_ALARMH, QString("out"));
        pst->m_gpios.configureGPIO(GPIO_FIBER8_ALARML, QString("out"));
        if(status == 0){
            pst->m_gpios.writeGPIO(GPIO_FIBER8_ALARMH, 0);
            pst->m_gpios.writeGPIO(GPIO_FIBER8_ALARML, 0);
        }
        else if(status == 1)
        {
            pst->m_gpios.writeGPIO(GPIO_FIBER8_ALARMH, 1);
            pst->m_gpios.writeGPIO(GPIO_FIBER8_ALARML, 0);
        }
        else if(status == 2){
            pst->m_gpios.writeGPIO(GPIO_FIBER8_ALARMH, 0);
            pst->m_gpios.writeGPIO(GPIO_FIBER8_ALARML, 1);
        }

    }

}
