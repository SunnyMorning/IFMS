#ifndef QPSTPRODUCTPRIVATE_H
#define QPSTPRODUCTPRIVATE_H


#include <QObject>
#include <QSettings>
#include <QString>

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>

#define NUMBER_OF_MODULES           2
#define NUMBER_OF_CHANNES           8
#define CHANNELS_PER_MODULE         4
#define NNN                         32
#define PRODUCT_SETTINGS_GROUP		"PRODUCT"

using namespace std;

typedef struct pstIFMS1000PortInfoTable_entry {
    /* Index values */
    long pstIFMS1000PortNum;

    /* Column values */
//    long pstIFMS1000PortNum;
    char pstIFMS1000PortRxPwr[NNN];
    size_t pstIFMS1000PortRxPwr_len;
    char pstIFMS1000PortTxPwr[NNN];
    size_t pstIFMS1000PortTxPwr_len;
    long pstIFMS1000PortWorkMode;
    long old_pstIFMS1000PortWorkMode;
    long pstIFMS1000PortActive;
    long old_pstIFMS1000PortActive;
    long pstIFMS1000PortFiberAppType;
    long old_pstIFMS1000PortFiberAppType;
    long pstIFMS1000PortRunningStatus;

    int   valid;
}pstIFMS1000PortInfoEntry;

typedef struct pstIFMS1000MeasureTable_entry {
    /* Index values */
    long pstIFMS1000MTPortNum;

    /* Column values */
//    long pstIFMS1000MTPortNum;
    char pstIFMS1000MeasureStartPosition[NNN];
    size_t pstIFMS1000MeasureStartPosition_len;
    char old_pstIFMS1000MeasureStartPosition[NNN];
    size_t old_pstIFMS1000MeasureStartPosition_len;
    char pstIFMS1000MeasureEndPosition[NNN];
    size_t pstIFMS1000MeasureEndPosition_len;
    char old_pstIFMS1000MeasureEndPosition[NNN];
    size_t old_pstIFMS1000MeasureEndPosition_len;
    char pstIFMS1000MeasureRefIndex[NNN];
    size_t pstIFMS1000MeasureRefIndex_len;
    char old_pstIFMS1000MeasureRefIndex[NNN];
    size_t old_pstIFMS1000MeasureRefIndex_len;
    char pstIFMS1000MeasureResolution[NNN];
    size_t pstIFMS1000MeasureResolution_len;
    char old_pstIFMS1000MeasureResolution[NNN];
    size_t old_pstIFMS1000MeasureResolution_len;
    long pstIFMS1000MeasureStatus;
    long pstIFMS1000MeasureAction;
    long old_pstIFMS1000MeasureAction;
    char pstIFMS1000MeasurePulseWidth[NNN];
    size_t pstIFMS1000MeasurePulseWidth_len;
    char old_pstIFMS1000MeasurePulseWidth[NNN];
    size_t old_pstIFMS1000MeasurePulseWidth_len;
    long pstIFMS1000MeasureTime;
    long old_pstIFMS1000MeasureTime;
    long pstIFMS1000MeasureProgressStatus;
    char pstIFMS1000MeasureTLOS[NNN];
    size_t pstIFMS1000MeasureTLOS_len;
    char old_pstIFMS1000MeasureTLOS[NNN];
    size_t old_pstIFMS1000MeasureTLOS_len;
    char pstIFMS1000MeasureTREF[NNN];
    size_t pstIFMS1000MeasureTREF_len;
    char old_pstIFMS1000MeasureTREF[NNN];
    size_t old_pstIFMS1000MeasureTREF_len;
    char pstIFMS1000MeasureFiberLengthChangeThreshold[NNN];
    size_t pstIFMS1000MeasureFiberLengthChangeThreshold_len;
    char old_pstIFMS1000MeasureFiberLengthChangeThreshold[NNN];
    size_t old_pstIFMS1000MeasureFiberLengthChangeThreshold_len;
    char pstIFMS1000MeasureEndToEndLossCriticalThreshold[NNN];
    size_t pstIFMS1000MeasureEndToEndLossCriticalThreshold_len;
    char old_pstIFMS1000MeasureEndToEndLossCriticalThreshold[NNN];
    size_t old_pstIFMS1000MeasureEndToEndLossCriticalThreshold_len;
    char pstIFMS1000MeasureEndToEndLossMajorThreshold[NNN];
    size_t pstIFMS1000MeasureEndToEndLossMajorThreshold_len;
    char old_pstIFMS1000MeasureEndToEndLossMajorThreshold[NNN];
    size_t old_pstIFMS1000MeasureEndToEndLossMajorThreshold_len;
    char pstIFMS1000MeasureEndToEndLossMinorThreshold[NNN];
    size_t pstIFMS1000MeasureEndToEndLossMinorThreshold_len;
    char old_pstIFMS1000MeasureEndToEndLossMinorThreshold[NNN];
    size_t old_pstIFMS1000MeasureEndToEndLossMinorThreshold_len;
    char pstIFMS1000MeasureNewLossCriticalThreshold[NNN];
    size_t pstIFMS1000MeasureNewLossCriticalThreshold_len;
    char old_pstIFMS1000MeasureNewLossCriticalThreshold[NNN];
    size_t old_pstIFMS1000MeasureNewLossCriticalThreshold_len;
    char pstIFMS1000MeasureNewLossMajorThreshold[NNN];
    size_t pstIFMS1000MeasureNewLossMajorThreshold_len;
    char old_pstIFMS1000MeasureNewLossMajorThreshold[NNN];
    size_t old_pstIFMS1000MeasureNewLossMajorThreshold_len;
    char pstIFMS1000MeasureNewLossMinorThreshold[NNN];
    size_t pstIFMS1000MeasureNewLossMinorThreshold_len;
    char old_pstIFMS1000MeasureNewLossMinorThreshold[NNN];
    size_t old_pstIFMS1000MeasureNewLossMinorThreshold_len;
    char pstIFMS1000MeasureOldLossCriticalThreshold[NNN];
    size_t pstIFMS1000MeasureOldLossCriticalThreshold_len;
    char old_pstIFMS1000MeasureOldLossCriticalThreshold[NNN];
    size_t old_pstIFMS1000MeasureOldLossCriticalThreshold_len;
    char pstIFMS1000MeasureOldLossMajorThreshold[NNN];
    size_t pstIFMS1000MeasureOldLossMajorThreshold_len;
    char old_pstIFMS1000MeasureOldLossMajorThreshold[NNN];
    size_t old_pstIFMS1000MeasureOldLossMajorThreshold_len;
    char pstIFMS1000MeasureOldLossMinorThreshold[NNN];
    size_t pstIFMS1000MeasureOldLossMinorThreshold_len;
    char old_pstIFMS1000MeasureOldLossMinorThreshold[NNN];
    size_t old_pstIFMS1000MeasureOldLossMinorThreshold_len;
    char pstIFMS1000MeasureTempHighThreshold[NNN];
    size_t pstIFMS1000MeasureTempHighThreshold_len;
    char old_pstIFMS1000MeasureTempHighThreshold[NNN];
    size_t old_pstIFMS1000MeasureTempHighThreshold_len;
    char pstIFMS1000MeasureTempLowThreshold[NNN];
    size_t pstIFMS1000MeasureTempLowThreshold_len;
    char old_pstIFMS1000MeasureTempLowThreshold[NNN];
    size_t old_pstIFMS1000MeasureTempLowThreshold_len;
    char pstIFMS1000MeasureNumber[NNN];
    size_t pstIFMS1000MeasureNumber_len;
    char pstIFMS1000MeasureNumberSORStoredEachChannel[NNN];
    size_t pstIFMS1000MeasureNumberSORStoredEachChannel_len;
    char old_pstIFMS1000MeasureNumberSORStoredEachChannel[NNN];
    size_t old_pstIFMS1000MeasureNumberSORStoredEachChannel_len;

    int   valid;
}pstIFMS1000MeasureEntry;

typedef struct pstIFMS1000FingerTable_entry {
    /* Index values */
    long pstIFMS1000FTPortNum;

    /* Column values */
//    long pstIFMS1000FTPortNum;
    char pstIFMS1000FingerStartPosition[NNN];
    size_t pstIFMS1000FingerStartPosition_len;
    char old_pstIFMS1000FingerStartPosition[NNN];
    size_t old_pstIFMS1000FingerStartPosition_len;
    char pstIFMS1000FingerEndPosition[NNN];
    size_t pstIFMS1000FingerEndPosition_len;
    char old_pstIFMS1000FingerEndPosition[NNN];
    size_t old_pstIFMS1000FingerEndPosition_len;
    char pstIFMS1000FingerRefIndex[NNN];
    size_t pstIFMS1000FingerRefIndex_len;
    char old_pstIFMS1000FingerRefIndex[NNN];
    size_t old_pstIFMS1000FingerRefIndex_len;
    char pstIFMS1000FingerResolution[NNN];
    size_t pstIFMS1000FingerResolution_len;
    char old_pstIFMS1000FingerResolution[NNN];
    size_t old_pstIFMS1000FingerResolution_len;
    char pstIFMS1000FingerCreateTime[NNN];
    size_t pstIFMS1000FingerCreateTime_len;
    long pstIFMS1000FingerFileStatus;
    long pstIFMS1000FingerAction;
    long old_pstIFMS1000FingerAction;
    long pstIFMS1000FingerActionStatus;
    char pstIFMS1000FingerSavedFileName[NNN];
    size_t pstIFMS1000FingerSavedFileName_len;
    char pstIFMS1000FingerCurrentFileName[NNN];
    size_t pstIFMS1000FingerCurrentFileName_len;

    int   valid;
}pstIFMS1000FingerEntry;

typedef struct pstIFMS1000DiffTotalTable_entry {
    /* Index values */
    long pstIFMS1000DtPortNum;

    /* Column values */
//    long pstIFMS1000DtPortNum;
    long pstIFMS1000DtTotalNum;

    int   valid;
}pstIFMS1000DiffTotalEntry;

typedef struct pstIFMS1000DiffInfoTable_entry {
    /* Index values */
    long pstIFMS1000DiffInfoPortNum;
    long pstIFMS1000DiffInfoPortItemIndex;

    /* Column values */
//    long pstIFMS1000DiffInfoPortNum;
//    long pstIFMS1000DiffInfoPortItemIndex;
    char pstIFMS1000DiffInfoDistance[NNN];
    size_t pstIFMS1000DiffInfoDistance_len;
    char pstIFMS1000DiffInfoNVal[NNN];
    size_t pstIFMS1000DiffInfoNVal_len;
    char pstIFMS1000DiffInfodBVal[NNN];
    size_t pstIFMS1000DiffInfodBVal_len;
    long pstIFMS1000DiffInfoDiffType;
    u_long pstIFMS1000DiffInfoPointId;

    int   valid;
}pstIFMS1000DiffInfoEntry;

typedef struct pstIFMS1000PortLedTable_entry {
    /* Index values */
    long pstIFMS1000PortLedPortNum;

    /* Column values */
//    long pstIFMS1000PortLedPortNum;
    long pstIFMS1000PortLedStatus;

    int   valid;
}pstIFMS1000PortLedEntry;

typedef struct _pstIFMS1000DiffInfo
{
    vector<pstIFMS1000DiffTotalEntry> pstIFMS1000DiffTotalTable;
    vector<pstIFMS1000DiffInfoEntry> pstIFMS1000DiffInfoTable;
}pstIFMS1000DiffInfo;

typedef struct _pstIFMS1000LedStatus
{
    struct _pstIFMS1000SystemLed
    {
        long pstIFMS1000SysLedPW1;
        long pstIFMS1000SysLedPW2;
        long pstIFMS1000SysLedStatus;
    }pstIFMS1000SystemLed;

    vector<pstIFMS1000PortLedEntry> pstIFMS1000PortLedTable;
}pstIFMS1000LedStatus;

struct pstIFMS1000DiagnoseTable_entry {
    /* Index values */
    long pstIFMS1000DgPortNum;

    /* Column values */
//    long pstIFMS1000DgPortNum;
    char pstIFMS1000DgLaserACBias[NNN];
    size_t pstIFMS1000DgLaserACBias_len;
    char old_pstIFMS1000DgLaserACBias[NNN];
    size_t old_pstIFMS1000DgLaserACBias_len;
    char pstIFMS1000DgLaserDCBias[NNN];
    size_t pstIFMS1000DgLaserDCBias_len;
    char old_pstIFMS1000DgLaserDCBias[NNN];
    size_t old_pstIFMS1000DgLaserDCBias_len;
    char pstIFMS1000DgLaserACModulation[NNN];
    size_t pstIFMS1000DgLaserACModulation_len;
    char old_pstIFMS1000DgLaserACModulation[NNN];
    size_t old_pstIFMS1000DgLaserACModulation_len;
    char pstIFMS1000DgLaserDCModulation[NNN];
    size_t pstIFMS1000DgLaserDCModulation_len;
    char old_pstIFMS1000DgLaserDCModulation[NNN];
    size_t old_pstIFMS1000DgLaserDCModulation_len;
    long pstIFMS1000DgLaserEn;
    long old_pstIFMS1000DgLaserEn;
    long pstIFMS1000DgPwm;
    long old_pstIFMS1000DgPwm;
    long pstIFMS1000DgSeed;
    long old_pstIFMS1000DgSeed;
    long pstIFMS1000DgPrbs;
    long old_pstIFMS1000DgPrbs;
    long pstIFMS1000DgAverage;
    long old_pstIFMS1000DgAverage;
    long pstIFMS1000DgRegAddr;
    long old_pstIFMS1000DgRegAddr;
    long pstIFMS1000DgRegValue;
    long old_pstIFMS1000DgRegValue;
    char pstIFMS1000DgMaskStartPoint[NNN];
    size_t pstIFMS1000DgMaskStartPoint_len;
    char old_pstIFMS1000DgMaskStartPoint[NNN];
    size_t old_pstIFMS1000DgMaskStartPoint_len;
    char pstIFMS1000DgMaskStopPoint[NNN];
    size_t pstIFMS1000DgMaskStopPoint_len;
    char old_pstIFMS1000DgMaskStopPoint[NNN];
    size_t old_pstIFMS1000DgMaskStopPoint_len;
    long pstIFMS1000DgMaskAction;
    long old_pstIFMS1000DgMaskAction;
    char pstIFMS1000DgMeasureDeltaThld[NNN];
    size_t pstIFMS1000DgMeasureDeltaThld_len;
    char old_pstIFMS1000DgMeasureDeltaThld[NNN];
    size_t old_pstIFMS1000DgMeasureDeltaThld_len;
    char pstIFMS1000DgCutPointThld[NNN];
    size_t pstIFMS1000DgCutPointThld_len;
    char old_pstIFMS1000DgCutPointThld[NNN];
    size_t old_pstIFMS1000DgCutPointThld_len;
    long pstIFMS1000DgPeriod;
    long old_pstIFMS1000DgPeriod;
    long pstIFMS1000DgDAC;
    long old_pstIFMS1000DgDAC;
    long pstIFMS1000DgCounterClockMode;
    long old_pstIFMS1000DgCounterClockMode;
    long pstIFMS1000DgScanRunType;
    long old_pstIFMS1000DgScanRunType;
    u_long pstIFMS1000DgOpt;
    u_long old_pstIFMS1000DgOpt;
    char pstIFMS1000DgFiberOffset[NNN];
    size_t pstIFMS1000DgFiberOffset_len;
    char old_pstIFMS1000DgFiberOffset[NNN];
    size_t old_pstIFMS1000DgFiberOffset_len;
    u_long pstIFMS1000DgTestWaveLen;
    u_long old_pstIFMS1000DgTestWaveLen;
    u_long pstIFMS1000DgPRT;
    u_long old_pstIFMS1000DgPRT;
    u_long pstIFMS1000DgPPW;
    u_long old_pstIFMS1000DgPPW;
    u_long pstIFMS1000DgPPrescale;
    u_long old_pstIFMS1000DgPPrescale;
    u_long pstIFMS1000DgPAvg;
    u_long old_pstIFMS1000DgPAvg;
    u_long pstIFMS1000DgPGain;
    u_long old_pstIFMS1000DgPGain;
    u_long pstIFMS1000DgPAdcData;
    u_long pstIFMS1000DgPE2promAction;
    u_long old_pstIFMS1000DgPE2promAction;

    int   valid;
};


/* Typical data structure for a row entry */
struct pstIFMS1000DebugRegTable_entry {
    /* Index values */
    long pstIFMS1000DbPortNum;

    /* Column values */
//    long pstIFMS1000DbPortNum;
    long pstIFMS1000DbRegAddr;
    long old_pstIFMS1000DbRegAddr;
    long pstIFMS1000DbRegValue;
    long old_pstIFMS1000DbRegValue;

    int   valid;
};

/* Typical data structure for a row entry */
struct pstIFMS1000DebugDACTable_entry {
    /* Index values */
    long pstIFMS1000DacTPortNum;

    /* Column values */
//    long pstIFMS1000DacTPortNum;
    long pstIFMS1000DacTChannelNum;
    long old_pstIFMS1000DacTChannelNum;
    long pstIFMS1000TDacValue;
    long old_pstIFMS1000TDacValue;

    int   valid;
};

    /* Typical data structure for a row entry */
struct pstIFMS1000DebugE2promTable_entry {
    /* Index values */
    long pstIFMS1000DbE2TPortNum;

    /* Column values */
//    long pstIFMS1000DbE2TPortNum;
    long pstIFMS1000DbE2TAddr;
    long old_pstIFMS1000DbE2TAddr;
    long pstIFMS1000DbE2TValue;
    long old_pstIFMS1000DbE2TValue;

    int   valid;
};

    /* Typical data structure for a row entry */
struct pstIFMS1000ExtendAlarmTable_entry {
    /* Index values */
    long pstIFMS1000EAPortNum;

    /* Column values */
//    long pstIFMS1000EAPortNum;
    u_long pstIFMS1000ExtendAlarm;
    u_long old_pstIFMS1000ExtendAlarm;

    int   valid;
};

/* Typical data structure for a row entry */
struct pstIFMS1000ExpertExtendTable_entry {
    /* Index values */
    long pstIFMS1000EEPortNum;

    /* Column values */
//    long pstIFMS1000EEPortNum;
    char pstIFMS1000DgPBias1[NNN];
    size_t pstIFMS1000DgPBias1_len;
    char old_pstIFMS1000DgPBias1[NNN];
    size_t old_pstIFMS1000DgPBias1_len;
    char pstIFMS1000DgPBias2[NNN];
    size_t pstIFMS1000DgPBias2_len;
    char old_pstIFMS1000DgPBias2[NNN];
    size_t old_pstIFMS1000DgPBias2_len;
    char pstIFMS1000DgPModulation1[NNN];
    size_t pstIFMS1000DgPModulation1_len;
    char old_pstIFMS1000DgPModulation1[NNN];
    size_t old_pstIFMS1000DgPModulation1_len;
    char pstIFMS1000DgPModulation2[NNN];
    size_t pstIFMS1000DgPModulation2_len;
    char old_pstIFMS1000DgPModulation2[NNN];
    size_t old_pstIFMS1000DgPModulation2_len;
    long pstIFMS1000DgPBackScatter;
    long old_pstIFMS1000DgPBackScatter;
    char pstIFMS1000DgPMeasureDeltaThld[NNN];
    size_t pstIFMS1000DgPMeasureDeltaThld_len;
    char old_pstIFMS1000DgPMeasureDeltaThld[NNN];
    size_t old_pstIFMS1000DgPMeasureDeltaThld_len;
    char pstIFMS1000DgPCutPointThld[NNN];
    size_t pstIFMS1000DgPCutPointThld_len;
    char old_pstIFMS1000DgPCutPointThld[NNN];
    size_t old_pstIFMS1000DgPCutPointThld_len;
    char pstIFMS1000DgPMFactor[NNN];
    size_t pstIFMS1000DgPMFactor_len;
    char old_pstIFMS1000DgPMFactor[NNN];
    size_t old_pstIFMS1000DgPMFactor_len;
    char pstIFMS1000DgFaultCriticalThld[NNN];
    size_t pstIFMS1000DgFaultCriticalThld_len;
    char old_pstIFMS1000DgFaultCriticalThld[NNN];
    size_t old_pstIFMS1000DgFaultCriticalThld_len;
    char pstIFMS1000DgFaultMajorThld[NNN];
    size_t pstIFMS1000DgFaultMajorThld_len;
    char old_pstIFMS1000DgFaultMajorThld[NNN];
    size_t old_pstIFMS1000DgFaultMajorThld_len;
    char pstIFMS1000DgFaultMinorThld[NNN];
    size_t pstIFMS1000DgFaultMinorThld_len;
    char old_pstIFMS1000DgFaultMinorThld[NNN];
    size_t old_pstIFMS1000DgFaultMinorThld_len;
    char pstIFMS1000DgPAFactor[NNN];
    size_t pstIFMS1000DgPAFactor_len;
    char old_pstIFMS1000DgPAFactor[NNN];
    size_t old_pstIFMS1000DgPAFactor_len;
    char pstIFMS1000DgPBFactor[NNN];
    size_t pstIFMS1000DgPBFactor_len;
    char old_pstIFMS1000DgPBFactor[NNN];
    size_t old_pstIFMS1000DgPBFactor_len;

    int   valid;
};


/* Typical data structure for a row entry */
struct pstIFMS1000PonConfTable_entry {
    /* Index values */
    u_long pctPortNum;

    /* Column values */
//    u_long pctPortNum;
    u_long pctSp1LocItem;
    u_long old_pctSp1LocItem;

    int   valid;
};


/* Typical data structure for a row entry */
struct pstIFMS1000ParamsV32TotalNumTable_entry {
    /* Index values */
    long v32TPortNum;

    /* Column values */
//    long v32TPortNum;
    long v32PortTotalNum;

    int   valid;
};

/* Typical data structure for a row entry */
struct pstIFMS1000ParamsV32NameTable_entry {
    /* Index values */
    long v32PortNum;
    long v32ParamNameNum;

    /* Column values */
    //    long v32PortNum;
    //    long v32ParamNameNum;
    char v32ParamName[NNN];
    size_t v32ParamName_len;

    int   valid;
};


/* Typical data structure for a row entry */
struct pstIFMS1000ParamsV32ValTable_entry {
    /* Index values */
    long v32ValPortNum;
    long v32ParamValNum;

    /* Column values */
    //    long v32ValPortNum;
    //    long v32ParamValNum;
    u_long v32ParamVal;
    u_long old_v32ParamVal;

    int   valid;
};

/* Typical data structure for a row entry */
struct pstIFMS1000ParamsS32TotalNumTable_entry {
    /* Index values */
    long s32TPortNum;

    /* Column values */
    //    long s32TPortNum;
    long s32PortTotalNum;

    int   valid;
};

/* Typical data structure for a row entry */
struct pstIFMS1000ParamsS32NameTable_entry {
    /* Index values */
    long s32PortNum;
    long s32ParamNameNum;

    /* Column values */
    //    long s32PortNum;
    //    long s32ParamNameNum;
    char s32ParamNameVal[NNN];
    size_t s32ParamNameVal_len;

    int   valid;
};


/* Typical data structure for a row entry */
struct pstIFMS1000ParamsS32ValTable_entry {
    /* Index values */
    long s32ValPortNum;
    long s32ParamValNum;

    /* Column values */
    //    long s32ValPortNum;
    //    long s32ParamValNum;
    char s32ParamVal[NNN];
    size_t s32ParamVal_len;
    char old_s32ParamVal[NNN];
    size_t old_s32ParamVal_len;

    int   valid;
};


class QPSTProductPrivate : public QObject
{
    Q_OBJECT
public:
    explicit QPSTProductPrivate(QObject *parent = 0);
    vector<pstIFMS1000PortInfoEntry>  PortInfoTable;
    vector<pstIFMS1000MeasureEntry>   MeasureTable;
    vector<pstIFMS1000FingerEntry>  FingerTable;
    pstIFMS1000DiffInfo DiffInfo;
    pstIFMS1000LedStatus LedStatus;

    void vchar2string(vector<char> &t, string f)
    {
        t.assign(f.begin(),f.end());
    }

    void init_pstData();

    long get_pstIFMS1000SysLedPW1(QObject *agent);
    long get_pstIFMS1000SysLedPW2(QObject *agent);
    long get_pstIFMS1000SysLedStatus(QObject *agent);
    
    QString get_pstIFMS1000PortRxPwr(quint16 channel);          
    size_t get_pstIFMS1000PortRxPwr_len(quint16 channel);      
    QString get_pstIFMS1000PortTxPwr(quint16 channel);          
    size_t get_pstIFMS1000PortTxPwr_len(quint16 channel);     
    long get_pstIFMS1000PortWorkMode(quint16 channel);           
    long get_pstIFMS1000PortActive(quint16 channel);             
    long get_pstIFMS1000PortFiberAppType(quint16 channel);       
    long get_pstIFMS1000PortRunningStatus(quint16 channel);      
    
    void set_pstIFMS1000PortRxPwr(quint16 channel,QString s);          
    void set_pstIFMS1000PortRxPwr_len(quint16 channel, int s);      
    void set_pstIFMS1000PortTxPwr(quint16 channel,QString s);          
    void set_pstIFMS1000PortTxPwr_len(quint16 channel,int s);     
    void set_pstIFMS1000PortWorkMode(quint16 channel,int s);           
    void set_pstIFMS1000PortActive(quint16 channel,int s);             
    void set_pstIFMS1000PortFiberAppType(quint16 channel,int s);       
    void set_pstIFMS1000PortRunningStatus(quint16 channel,int s);    
    
    
    QString get_pstIFMS1000MeasureStartPosition(quint16 channel);
    size_t get_pstIFMS1000MeasureStartPosition_len(quint16 channel);
    QString get_pstIFMS1000MeasureEndPosition(quint16 channel);
    size_t get_pstIFMS1000MeasureEndPosition_len(quint16 channel);
     QString get_pstIFMS1000MeasureRefIndex(quint16 channel);
    size_t get_pstIFMS1000MeasureRefIndex_len(quint16 channel);
    QString get_pstIFMS1000MeasureResolution(quint16 channel);
    size_t get_pstIFMS1000MeasureResolution_len(quint16 channel);
    long get_pstIFMS1000MeasureStatus(quint16 channel);
    long get_pstIFMS1000MeasureAction(quint16 channel);
    QString get_pstIFMS1000MeasurePulseWidth(quint16 channel);
    size_t get_pstIFMS1000MeasurePulseWidth_len(quint16 channel);
    long get_pstIFMS1000MeasureTime(quint16 channel);
     long get_pstIFMS1000MeasureProgressStatus(quint16 channel);
    QString get_pstIFMS1000MeasureTLOS(quint16 channel);
    size_t get_pstIFMS1000MeasureTLOS_len(quint16 channel);
    QString get_pstIFMS1000MeasureTREF(quint16 channel);
    size_t get_pstIFMS1000MeasureTREF_len(quint16 channel);
    QString get_pstIFMS1000MeasureFiberLengthChangeThreshold(quint16 channel);
    size_t get_pstIFMS1000MeasureFiberLengthChangeThreshold_len(quint16 channel);
    QString get_pstIFMS1000MeasureEndToEndLossCriticalThreshold(quint16 channel);
    size_t get_pstIFMS1000MeasureEndToEndLossCriticalThreshold_len(quint16 channel);
    QString get_pstIFMS1000MeasureEndToEndLossMajorThreshold(quint16 channel);
    size_t get_pstIFMS1000MeasureEndToEndLossMajorThreshold_len(quint16 channel);
    QString get_pstIFMS1000MeasureEndToEndLossMinorThreshold(quint16 channel);
    size_t get_pstIFMS1000MeasureEndToEndLossMinorThreshold_len(quint16 channel);
    QString get_pstIFMS1000MeasureNewLossCriticalThreshold(quint16 channel);
    size_t get_pstIFMS1000MeasureNewLossCriticalThreshold_len(quint16 channel);
    QString get_pstIFMS1000MeasureNewLossMajorThreshold(quint16 channel);
    size_t get_pstIFMS1000MeasureNewLossMajorThreshold_len(quint16 channel);
    QString get_pstIFMS1000MeasureNewLossMinorThreshold(quint16 channel);
    size_t get_pstIFMS1000MeasureNewLossMinorThreshold_len(quint16 channel);
    QString get_pstIFMS1000MeasureOldLossCriticalThreshold(quint16 channel);
    size_t get_pstIFMS1000MeasureOldLossCriticalThreshold_len(quint16 channel);
    QString get_pstIFMS1000MeasureOldLossMajorThreshold(quint16 channel);
    size_t get_pstIFMS1000MeasureOldLossMajorThreshold_len(quint16 channel);
    QString get_pstIFMS1000MeasureOldLossMinorThreshold(quint16 channel);
    size_t get_pstIFMS1000MeasureOldLossMinorThreshold_len(quint16 channel);
    QString get_pstIFMS1000MeasureTempHighThreshold(quint16 channel);
    size_t get_pstIFMS1000MeasureTempHighThreshold_len(quint16 channel);
    QString get_pstIFMS1000MeasureTempLowThreshold(quint16 channel);
    size_t get_pstIFMS1000MeasureTempLowThreshold_len(quint16 channel);
    QString get_pstIFMS1000MeasureNumber(quint16 channel);
    size_t get_pstIFMS1000MeasureNumber_len(quint16 channel);
    QString get_pstIFMS1000MeasureNumberSORStoredEachChannel(quint16 channel);
    size_t get_pstIFMS1000MeasureNumberSORStoredEachChannel_len(quint16 channel);

    void  set_pstIFMS1000MeasureStartPosition(quint16 channel, QString s);
    void  set_pstIFMS1000MeasureStartPosition_len(quint16 channel, int s);
    void  set_pstIFMS1000MeasureEndPosition(quint16 channel, QString s);
    void  set_pstIFMS1000MeasureEndPosition_len(quint16 channel, int s);
    void  set_pstIFMS1000MeasureRefIndex(quint16 channel, QString s);
    void  set_pstIFMS1000MeasureRefIndex_len(quint16 channel, int s);
    void  set_pstIFMS1000MeasureResolution(quint16 channel, QString s);
    void  set_pstIFMS1000MeasureResolution_len(quint16 channel, int s);
    void  set_pstIFMS1000MeasureStatus(quint16 channel, int s);
    void  set_pstIFMS1000MeasureAction(quint16 channel, int s);
    void  set_pstIFMS1000MeasurePulseWidth(quint16 channel, QString s);
    void  set_pstIFMS1000MeasurePulseWidth_len(quint16 channel, int s);
    void  set_pstIFMS1000MeasureTime(quint16 channel, int s);
    void  set_pstIFMS1000MeasureProgressStatus(quint16 channel, int s);
    void  set_pstIFMS1000MeasureTLOS(quint16 channel, QString s);
    void  set_pstIFMS1000MeasureTLOS_len(quint16 channel, int s);
    void  set_pstIFMS1000MeasureTREF(quint16 channel, QString s);
    void  set_pstIFMS1000MeasureTREF_len(quint16 channel, int s);
    void  set_pstIFMS1000MeasureFiberLengthChangeThreshold(quint16 channel, QString s);
    void  set_pstIFMS1000MeasureFiberLengthChangeThreshold_len(quint16 channel, int s);
    void  set_pstIFMS1000MeasureEndToEndLossCriticalThreshold(quint16 channel, QString s);
    void  set_pstIFMS1000MeasureEndToEndLossCriticalThreshold_len(quint16 channel, int s);
    void  set_pstIFMS1000MeasureEndToEndLossMajorThreshold(quint16 channel, QString s);
    void  set_pstIFMS1000MeasureEndToEndLossMajorThreshold_len(quint16 channel, int s);
    void  set_pstIFMS1000MeasureEndToEndLossMinorThreshold(quint16 channel, QString s);
    void  set_pstIFMS1000MeasureEndToEndLossMinorThreshold_len(quint16 channel, int s);
    void  set_pstIFMS1000MeasureNewLossCriticalThreshold(quint16 channel, QString s);
    void  set_pstIFMS1000MeasureNewLossCriticalThreshold_len(quint16 channel, int s);
    void  set_pstIFMS1000MeasureNewLossMajorThreshold(quint16 channel, QString s);
    void  set_pstIFMS1000MeasureNewLossMajorThreshold_len(quint16 channel, int s);
    void  set_pstIFMS1000MeasureNewLossMinorThreshold(quint16 channel, QString s);
    void  set_pstIFMS1000MeasureNewLossMinorThreshold_len(quint16 channel, int s);
    void  set_pstIFMS1000MeasureOldLossCriticalThreshold(quint16 channel, QString s);
    void  set_pstIFMS1000MeasureOldLossCriticalThreshold_len(quint16 channel, int s);
    void  set_pstIFMS1000MeasureOldLossMajorThreshold(quint16 channel, QString s);
    void  set_pstIFMS1000MeasureOldLossMajorThreshold_len(quint16 channel, int s);
    void  set_pstIFMS1000MeasureOldLossMinorThreshold(quint16 channel, QString s);
    void  set_pstIFMS1000MeasureOldLossMinorThreshold_len(quint16 channel, int s);
    void  set_pstIFMS1000MeasureTempHighThreshold(quint16 channel, QString s);
    void  set_pstIFMS1000MeasureTempHighThreshold_len(quint16 channel, int s);
    void  set_pstIFMS1000MeasureTempLowThreshold(quint16 channel, QString s);
    void  set_pstIFMS1000MeasureTempLowThreshold_len(quint16 channel, int s);
    void  set_pstIFMS1000MeasureNumber(quint16 channel, QString s);
    void  set_pstIFMS1000MeasureNumber_len(quint16 channel, int s);
    void  set_pstIFMS1000MeasureNumberSORStoredEachChannel(quint16 channel, QString s);
    void  set_pstIFMS1000MeasureNumberSORStoredEachChannel_len(quint16 channel, int s); 

signals:

public slots:

private:
    QSettings    _ss;
};

#endif // QPSTPRODUCTPRIVATE_H
