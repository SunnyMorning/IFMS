#ifndef QPSTPRODUCTPRIVATE_H
#define QPSTPRODUCTPRIVATE_H


#include <QObject>
#include <QSettings>

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>

#define NUMBER_OF_MODULES           2
#define NUMBER_OF_CHANNES           8
#define CHANNELS_PER_MODULE         4

using namespace std;

typedef struct _pstIFMS1000PortInfoEntry
{
        long pstIFMS1000PortNum;
        char* pstIFMS1000PortRxPwr;
        char* pstIFMS1000PortTxPwr;
        long pstIFMS1000PortWorkMode;
        long pstIFMS1000PortActive;
        long pstIFMS1000PortFiberAppType;
        long pstIFMS1000PortRunningStatus;
}pstIFMS1000PortInfoEntry;
typedef struct _pstIFMS1000MeasureEntry
    {
        long pstIFMS1000MTPortNum;
        char* pstIFMS1000MeasureStartPosition;
        char* pstIFMS1000MeasureEndPosition;
        char* pstIFMS1000MeasureRefIndex;
        char* pstIFMS1000MeasureResolution;
        long pstIFMS1000MeasureStatus;
        long pstIFMS1000MeasureAction;
        vector<char> pstIFMS1000MeasureResultFile;
        vector<char>  pstIFMS1000MeasureResultRawDataFile;
        long pstIFMS1000MeasureProgressStatus;
        vector<char>  pstIFMS1000MeasureResultRawPointFile;
}pstIFMS1000MeasureEntry;
typedef struct _pstIFMS1000FingerEntry
{
        long pstIFMS1000FTPortNum;
        char* pstIFMS1000FingerStartPosition;
        char* pstIFMS1000FingerEndPosition;
        char* pstIFMS1000FingerRefIndex;
        char* pstIFMS1000FingerResolution;
        char* pstIFMS1000FingerCreateTime;
        long pstIFMS1000FingerFileStatus;
        long pstIFMS1000FingerAction;
        long pstIFMS1000FingerActionStatus;
        char* pstIFMS1000FingerSavedFileName;
        char* pstIFMS1000FingerCurrentFileName;
}pstIFMS1000FingerEntry;
typedef struct _pstIFMS1000DiffTotalEntry
{
        long pstIFMS1000DtPortNum;
        long pstIFMS1000DtTotalNum;
}pstIFMS1000DiffTotalEntry;
typedef struct _pstIFMS1000DiffInfoEntry
{
        long pstIFMS1000DiffInfoPortNum;
        long pstIFMS1000DiffInfoPortItemIndex;
        char* pstIFMS1000DiffInfoDistance;
        char* pstIFMS1000DiffInfoNVal;
        char* pstIFMS1000DiffInfodBVal;
        long pstIFMS1000DiffInfoDiffType;
        unsigned long pstIFMS1000DiffInfoPointId;
}pstIFMS1000DiffInfoEntry;

typedef struct _pstIFMS1000PortLedEntry
{
        long pstIFMS1000PortLedPortNum;
        long pstIFMS1000PortLedStatus;

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

//typedef struct _pstIFMS1000{
//        vector<pstIFMS1000PortInfoEntry>  PortInfoTable;
//        vector<pstIFMS1000MeasureEntry>   MeasureTable;
//        vector<pstIFMS1000FingerEntry>  FingerTable;
//        pstIFMS1000DiffInfo DiffInfo;
//        pstIFMS1000LedStatus LedStatus;
//}pstIFMS1000;

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
    void setModuleMeasuringProgess(quint16 module, quint16 progress);
signals:

public slots:
};

#endif // QPSTPRODUCTPRIVATE_H
