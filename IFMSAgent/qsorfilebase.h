#ifndef QSORFILEBASE_H
#define QSORFILEBASE_H

#include <QObject>
#include <QString>

#include <map>
#include <vector>
#include <string>

#include "qfingerdata.h"

using namespace std;

//#define FOURINT(DATA, IT)   ((DATA[IT+3]<<(8*3))+(DATA[IT+2]<<(8*2))+(DATA[IT+1]<<(8))+DATA[IT])
//#define TWOINT(DATA,IT) ((DATA[IT+1]<<(8))+DATA[IT])
#define MAX_STRING_LEN 1000
#define REVISION_NUM 200
#define C_LIGHT_SPEED 299792458.0
#define FLOAT   float
#define INT     qint32
#define UINT    quint32
#define BYTE    char
#define BOOL    bool
#define TRUE    true
#define FALSE   false

static qint16   TWOINT(char* data, int len)
{
    qint16  temp;
    memcpy(&temp, data+len, sizeof(temp));
    return temp;
}

static qint32  FOURINT(char* data, int len)
{
    qint32  temp;
    memcpy(&temp, data+len, sizeof(temp));
    return temp;
}

class QSorFileBase : public QObject
{
    Q_OBJECT
public:
    explicit QSorFileBase(int channel=1, QObject *parent = nullptr);

    quint16      _channel;

    struct  MapBlock
    {
        qint32  getsize();
        struct  blockInfo
        {
            vector<char>    ID;
            qint16  RevisionNo;
            qint32  Size;
        };
        blockInfo   mapBlock;
        short       blockCount;
        vector<blockInfo>   vBlockInfo;
    }m_mapBlock;

    struct  GeneralParas
    {
        qint32  getsize();
        vector<char>    ID;
        vector<char>    languageCode;
        vector<char>    cableID;
        vector<char>    fiberID;
        qint16          fiberType;
        qint16          nominalWaveLength;
        vector<char>    OLocation;
        vector<char>    TLocation;
        vector<char>    cableCode;
        vector<char>    currentDataFlag;
        qint32          userOffset;
        qint32          uODistance;
        vector<char>    operater;
        vector<char>    comment;
    }m_generalParas;

    struct  SuppliersParas
    {
        qint32 getsize();
        vector<char>    ID;
        vector<char> name;//厂商名称
        vector<char> mainframeID;//主面板型号
        vector<char> mainframeSn;//主面板序列号
        vector<char> moduleID;//插件模板号
        vector<char> moduleSn;//插件（plug-in）序列号
        vector<char> softVersion;//软硬件版本号
        vector<char> other;//其它信息
    }m_suppliersParas;

    struct FixedParas//
    {
        INT getsize();//获取长度
        void write(vector<BYTE>& vData);
        //CString ID;//名称
        vector<char> ID;//名称
        UINT timestamp;//时间
        //CString distanceUnit;//单位 km,mt,ft,kf,mi 固定2字节
        vector<char> distanceUnit;//单位 km,mt,ft,kf,mi 固定2字节
        short actualWavelength;//实际测量波长
        INT acquisitionOffset;//???
        INT AODistance;//acquisition Offset Distance
        short pulseWidthNum;//Total Number of Pulse Widths Used脉宽个数
        vector<short> vPulseWidth;//Pulse Widths Used 使用的脉宽
        vector<INT> vDataSpacing;//不同脉宽，10000个数据点时间
        vector<INT> vDataPointsEach;//每个脉宽数据点个数,采样数wcq
        INT groupIndex;//自己测试得到是折射率wcq2011.10.18
        short backscatter;
        INT avgNum;//average number
        unsigned short avgTime;//average time
        INT acquisitionRange;
        INT ARDistance;//acquisitionRange distance
        INT frontPanelOff;
        unsigned short noiseFloorLevel;
        short noiseFloorFactor;//噪声级别系数
        unsigned short powerOff;//power offset first point
        unsigned short lossThreshold;
        unsigned short reflectanceThreshod;
        unsigned short eofThreshold;//end-of-fiber threshold
        //CString traceType;
        vector<char> traceType;//标准上说是string，实际上是string 固定2字节，后面没\0
        INT windowCoor1;//window coordinates左上右下坐标
        INT windowCoor2;//window coordinates
        INT windowCoor3;//window coordinates
        INT windowCoor4;//window coordinates
    }m_fixedParas;
    struct KeyEvent//
    {
        INT getsize();//获取长度
        void write(vector<BYTE>& vData);
        void clearEvent();//清空事件列表wcq2012.06.11
        //CString ID;//名称
        vector<char> ID;//名称
        short keyEventNum;//事件个数
        struct Event
        {
            short eventNum;//事件编号
            INT propagationTime;//连接后第一个e事件点时间
            short attenCoefficent;//衰减系数
            short eventLoss;//事件损耗
            INT   reflectance;//事件反射
            //CString code;//事件标志
            //CString lossMeasurement;
            vector<char> code;//事件标志固定6字节6
            vector<char> lossMeasurement;//固定2字节2
            INT markerLocations[5];//2011.10.11
            //	CString comment;//注释
            vector<char> comment;//注释
        };
        vector<Event> vEvent;//所有事件
        INT eteLoss;//End-to-End Loss
        INT eteMarkerStart;
        INT eteMarkerFinish;
        unsigned short returnLoss;//回损
        INT RLMarkerStart;
        INT RLMarkerFinish;
    }m_keyEvent;
    struct LinkParas//
    {
        INT getsize();//获取长度
        void write(vector<BYTE>& vData);
        //CString ID;//名称
        vector<char> ID;//名称
        short totalLandmarks;//lankmarks标志个数,默认和事件列表个数一样
        struct Landmark
        {
            short num;//编号
            //CString code;//编码2字节
            vector<char> code;//编码2字节固定2字节
            INT location;//
            short relatedEventNum;//相应的事件编号
            INT GPSLongitude;//GPS经度
            INT GPSLatitude;//GPS纬度
            short fiberCorrFactor;//
            INT   sheathEntering;
            INT   sheathLeaving;
            //	CString SLUnit;//Units of Sheath Marker Leaving Landmark
            vector<char> SLUnit;//Units of Sheath Marker Leaving Landmark 2字节固定2字节
            short modeFieldDiameter;
            //CString comment;
            vector<char> comment;
        };
        vector<Landmark> vLandmark;//所有事件
    }m_linkParas;
    struct DataPoints//
    {
        INT getsize();//获取长度
        void write(vector<BYTE>& vData);
        //CString ID;//名称
        vector<char> ID;//名称
        INT dataPointNum;//数据点个数
        short totalScaleFactors;//使用的扩展系数个数
        struct DataUseScaleFactor
        {
            INT count;//编号
            short scaleFactor;//编码2字节
            vector<unsigned short> vData;//
        };
        vector<DataUseScaleFactor> vAllData;//所有数据
    }m_dataPoints;

    struct UserName
    {
        INT getsize();
        void    write(vector<BYTE>& vData);
        vector<char>    ID;
        vector<char>    name;
    }m_userName;

    struct Checksum//
    {
        INT getsize();//获取长度
        void write(vector<BYTE>& vData);
        //CString ID;//名称
        vector<char> ID;//名称
        unsigned short checksum;//校验码
    }m_checksum;

    void vchar2string(vector<char> &t, string f)
    {
        t.assign(f.begin(),f.end());
    }


    bool        checkSize(qint32 fileLen);
    bool        parseData(BYTE data[], int len);
    QFingerData* toFingerData();
    quint16     crc16(qint8 d[], int len);
    int         readString(BYTE data[],vector<char>& vChar);
    QString     readString(BYTE data[],int startPos);

    INT         readMap(BYTE data[]);
    INT         readGeneralParas(BYTE data[]);//读取GeneralParas Block
    INT         readSuppliersParas(BYTE data[]);//读取SuppliersParas Block
    INT         readFixedParas(BYTE data[]);//读取FxdParams Block
    INT         readKeyEvents(BYTE data[]);//读取KeyEvent Block
    INT         readLinkParas(BYTE data[]);//读取LinkParas
    INT         readDataPts(BYTE data[]);//读取DataPts Block
    INT         readUserName(BYTE data[]);// 读取UserName Block
    INT         readCKsum(BYTE data[]);//读取CKsum Block

signals:

public slots:

private:

};

#endif // QSORFILEBASE_H
