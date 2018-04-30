#include <QChar>

#include "qsorfilebase.h"

QSorFileBase::QSorFileBase(int channel, QObject *parent) : QObject(parent)
{
    _channel = channel;
}

BOOL QSorFileBase::parseData(BYTE fileData[],int len)
{
//    //清空其他OTDR设备厂商自定义的Block数据
//    for(int i=0;i<m_vUnknownParas.size();i++)//各个Block清空
//    {
//        m_vUnknownParas[i].clear();
//    }
//    m_vUnknownParas.clear();//本身清空
    int index=0;//文件下标
    //string temp;
    char* pChar;
    int IDLen=0;
    if(readMap(fileData))//查看是否为.sor文件格式，如果是，读取Map数据块
    {
        if (!checkSize(len))//文件大小和各个Block之和不一样，则认为文件无效,防止文件读取有bug.
        {
            //delete[] fileData;//删除临时变量2011.12.01
            return FALSE;
        }

        index += m_mapBlock.mapBlock.Size;//加上map Block的大小
        int count=m_mapBlock.blockCount-1;//总共有多少个Block,减去Map Block本身
        for (int i=0;i<count;i++)
        {
            //vchar2string(temp,m_mapBlock.vBlockInfo[i].ID);
            IDLen=m_mapBlock.vBlockInfo[i].ID.size();
            pChar=&m_mapBlock.vBlockInfo[i].ID[0];
            if (0 == strncmp(pChar,"GenParams",IDLen))//
            {
                readGeneralParas(fileData + index);
            }
            else if (0 == strncmp(pChar,"SupParams",IDLen))
            {
                readSuppliersParas(fileData + index);
            }
            else if (0 == strncmp(pChar,"FxdParams",IDLen))
            {
                readFixedParas(fileData + index);
            }
            else if (0 == strncmp(pChar,"KeyEvents",IDLen))
            {
                readKeyEvents(fileData + index);
            }
            else if (0 == strncmp(pChar,"LnkParams",IDLen))
            {
                readLinkParas(fileData + index);
            }
            else if (0 == strncmp(pChar,"DataPts",IDLen))
            {
                readDataPts(fileData + index);
            }
            else if(0 == strncmp(pChar, "UserName",IDLen))
            {
                readUserName(fileData + index);
            }
            else if (0 == strncmp(pChar,"Cksum",IDLen) || 0 == strncmp(pChar,"CKsum",IDLen))//标准应为Cksum,但是得力的用的是CKsum
            {
                readCKsum(fileData + index);
            }
//            else
//            {
//                vector<BYTE> vParams(fileData + index,fileData + index + m_mapBlock.vBlockInfo[i].Size);
//                m_vUnknownParas.push_back(vParams);
//            }////eif
            index += m_mapBlock.vBlockInfo[i].Size;
        }//efor
    }//eif
    return TRUE;
}

QFingerData *QSorFileBase::toFingerData()
{
   QFingerData  *temp = new QFingerData;
   int i = 0;
   temp->mChannel = _channel;
   temp->mIFMSFingerData.Channel = _channel;
   temp->mIFMSFingerData.GroupIndex = m_fixedParas.groupIndex;
   temp->mIFMSFingerData.NumberOfEvents = m_keyEvent.keyEventNum;

   IFMSEvent_t  ifmsEvent;
   for(i=0; i< m_keyEvent.keyEventNum; i++){

        ifmsEvent.EventCode1 = m_keyEvent.vEvent.at(i).code.at(1);
        ifmsEvent.EventCode0 = m_keyEvent.vEvent.at(i).code.at(0);
        ifmsEvent.EventLoss = m_keyEvent.vEvent.at(i).eventLoss;
        ifmsEvent.EventReflectance = m_keyEvent.vEvent.at(i).reflectance;
        ifmsEvent.EventNo = i;
        ifmsEvent.EventPosition = m_keyEvent.vEvent.at(i).propagationTime *( C_LIGHT_SPEED/ (m_fixedParas.groupIndex * pow(10.0,8)));

        temp->mIFMSFingerData.vIFMSEvents.push_back(ifmsEvent);
   }

   return temp;
}
///////////////////////////////////////////////////////////////////////////////////
//函数说明:读取MapBlock。
//入口参数:data:BYTE数组;
//出口参数:
//建立时间:2011.7.8
//Write By:wcq
////////////////////////////////////////////////////////////////////////////////////
INT QSorFileBase::readMap(BYTE data[])//
{
    vchar2string(m_mapBlock.mapBlock.ID,string("Map"));
    int blockLen=0;//block长度
    //Map标志
    //if(_T("Map")!=readString(data,0))//改为判断
    if('M'!=data[0] || 'a'!=data[1] || 'p'!=data[2] || '\0'!=data[3])
    {
        return FALSE;
    }
    //
    //m_parsePos=4;//修订版本号起始位置
    blockLen=4;
    memcpy(&m_mapBlock.mapBlock.RevisionNo, data+blockLen, sizeof(m_mapBlock.mapBlock.RevisionNo));
    //m_parsePos=6;//长度起始位置
    blockLen=6;
    m_mapBlock.mapBlock.Size=FOURINT(data,blockLen);
    //m_parsePos=10;//Block个数起始位置
    blockLen=10;//Block个数起始位置
    INT count=TWOINT(data,blockLen);//Block个数
    m_mapBlock.blockCount=count;
    count--;//减去Map Block本身
    MapBlock::blockInfo block;
    //m_parsePos=12;//第一个block位置
    blockLen=12;//第一个block位置
    m_mapBlock.vBlockInfo.clear();//清空以前的数据块记录
    int strLen=0;
    for (int i=0;i<count;i++)
    {//int readString(BYTE data[],vector<char> vChar)
        //block.ID=readString(data,m_parsePos);//名称
        strLen=readString(data+blockLen,block.ID);
        //m_parsePos+=block.ID.GetLength()+1;//修订版本号起始位置
        blockLen+=strLen+1;//修订版本号起始位置
        //block.RevisionNo=TWOINT(data,m_parsePos);
        block.RevisionNo=TWOINT(data,blockLen);
        //m_parsePos+=2;//长度起始位置
        blockLen+=2;//长度起始位置
        //block.Size=FOURINT(data,m_parsePos);
        block.Size=FOURINT(data,blockLen);
        //m_parsePos+=4;//
        blockLen+=4;//
        m_mapBlock.vBlockInfo.push_back(block);
    }
    return blockLen;
}

////////////////////////////////////////////////////////////////////////////////////
//函数说明:读取GeneralParas Block。测试通过7.8
//入口参数:data:BYTE数组
//出口参数:
//建立时间:2011.7.8
//Write By:wcq
////////////////////////////////////////////////////////////////////////////////////
INT QSorFileBase::readGeneralParas(BYTE data[])
{
    vchar2string(m_generalParas.ID,string("GenParams"));
    int blockLen=0;//block长度
    int strLen=0;
    blockLen = 10;//语言编码起始位置,跳过GenParams\0
    m_generalParas.languageCode.clear();
    m_generalParas.languageCode.push_back(data[blockLen]);
    m_generalParas.languageCode.push_back(data[blockLen+1]);
    //m_parsePos+=2;//电缆编号起始位置
    blockLen += 2;//电缆编号起始位置

    //m_generalParas.cableID=readString(data,m_parsePos);//电缆编号
    strLen=readString(data + blockLen,m_generalParas.cableID);
    blockLen += strLen+1;//光纤编号起始位置

    //m_generalParas.fiberID=readString(data,m_parsePos);//光纤编号
    strLen=readString(data + blockLen,m_generalParas.fiberID);
    //m_parsePos+=m_generalParas.fiberID.GetLength()+1;//光纤编号起始位置
    blockLen += strLen+1;//光纤编号起始位置

    //m_generalParas.fiberType=TWOINT(data,m_parsePos);//光纤类型
    m_generalParas.fiberType=TWOINT(data,blockLen);//光纤类型

    //m_parsePos+=2;//额定波长起始位置
    blockLen+=2;//额定波长起始位置
    m_generalParas.nominalWaveLength=TWOINT(data,blockLen);//额定波长

    //m_parsePos+=2;//起始位置
    blockLen+=2;//起始位置
    //m_generalParas.OLocation=readString(data,m_parsePos);//Originating Location
    strLen=readString(data + blockLen,m_generalParas.OLocation);

    //m_parsePos+=m_generalParas.OLocation.GetLength()+1;//起始位置
    blockLen += strLen+1;//起始位置
    //m_generalParas.TLocation=readString(data,m_parsePos);//Terminating Location
    strLen=readString(data + blockLen,m_generalParas.TLocation);

    //m_parsePos+=m_generalParas.TLocation.GetLength()+1;//起始位置
    blockLen += strLen+1;//起始位置
    //m_generalParas.cableCode=readString(data,m_parsePos);//
    strLen=readString(data + blockLen,m_generalParas.cableCode);

    //m_parsePos+=m_generalParas.cableCode.GetLength()+1;//起始位置
    blockLen += strLen+1;//起始位置
    //temp.Format(_T("%C%C"),data[m_parsePos],data[m_parsePos+1]);
    //m_generalParas.currentDataFlag=temp;//Terminating Location
    m_generalParas.currentDataFlag.clear();
    m_generalParas.currentDataFlag.push_back(data[blockLen]);
    m_generalParas.currentDataFlag.push_back(data[blockLen+1]);

    //m_parsePos+=2;//起始位置
    blockLen += 2;//起始位置
    //m_generalParas.userOffset=FOURINT(data,m_parsePos);//
    m_generalParas.userOffset=FOURINT(data,blockLen);//

    //m_parsePos+=4;//起始位置
    blockLen += 4;//起始位置
    m_generalParas.uODistance=FOURINT(data,blockLen);//user Offset Distance

    //m_parsePos+=4;//操作人员起始位置
    blockLen += 4;//起始位置
    //m_generalParas.operater=readString(data,m_parsePos);//操作人员
    strLen=readString(data + blockLen,m_generalParas.operater);

    //m_parsePos+=m_generalParas.operater.GetLength()+1;//注释起始位置
    blockLen += strLen+1;//起始位置
    //m_generalParas.comment=readString(data,m_parsePos);//注释
    strLen=readString(data + blockLen,m_generalParas.comment);

    //m_parsePos+=m_generalParas.comment.GetLength()+1;//下一记录起始位置
    blockLen += strLen+1;//起始位置

    return blockLen;
}

////////////////////////////////////////////////////////////////////////////////////
//函数说明:读取SuppliersParas Block。测试通过7.8
//入口参数:data:BYTE数组
//出口参数:
//建立时间:2011.7.8
//Write By:wcq
////////////////////////////////////////////////////////////////////////////////////
INT QSorFileBase::readSuppliersParas(BYTE data[])
{
    vchar2string(m_suppliersParas.ID,string("SupParams"));
    int blockLen=0;//block长度
    int strLen=0;
    blockLen+=10;//厂商名称起始位置,跳过SupParams\0
    strLen=readString(data + blockLen,m_suppliersParas.name);

    blockLen+=strLen+1;//主面板型号起始位置
    strLen=readString(data + blockLen,m_suppliersParas.mainframeID);//主面板型号

    blockLen+=strLen+1;//主面板序列号起始位置
    strLen=readString(data + blockLen,m_suppliersParas.mainframeSn);//主面板序列号

    blockLen+=strLen+1;//插件模板号起始位置
    strLen=readString(data + blockLen,m_suppliersParas.moduleID);//插件模板号

    blockLen+=strLen+1;//插件（plug-in）序列号起始位置
    strLen=readString(data + blockLen,m_suppliersParas.moduleSn);//插件（plug-in）序列号

    blockLen+=strLen+1;//软硬件版本号起始位置
    strLen=readString(data + blockLen,m_suppliersParas.softVersion);//软硬件版本号

    blockLen+=strLen+1;//其它信息起始位置
    strLen=readString(data + blockLen,m_suppliersParas.other);//其它信息

    blockLen+=strLen+1;//下一记录起始位置
    return blockLen;
    //m_parsePos+=10;//厂商名称起始位置,跳过SupParams\0
    //m_suppliersParas.name=readString(data,m_parsePos);//厂商名称

    //m_parsePos+=m_suppliersParas.name.GetLength()+1;//主面板型号起始位置
    //m_suppliersParas.mainframeID=readString(data,m_parsePos);//主面板型号

    //m_parsePos+=m_suppliersParas.mainframeID.GetLength()+1;//主面板序列号起始位置
    //m_suppliersParas.mainframeSn=readString(data,m_parsePos);//主面板序列号

    //m_parsePos+=m_suppliersParas.mainframeSn.GetLength()+1;//插件模板号起始位置
    //m_suppliersParas.moduleID=readString(data,m_parsePos);//插件模板号

    //m_parsePos+=m_suppliersParas.moduleID.GetLength()+1;//插件（plug-in）序列号起始位置
    //m_suppliersParas.moduleSn=readString(data,m_parsePos);//插件（plug-in）序列号

    //m_parsePos+=m_suppliersParas.moduleSn.GetLength()+1;//软硬件版本号起始位置
    //m_suppliersParas.softVersion=readString(data,m_parsePos);//软硬件版本号

    //m_parsePos+=m_suppliersParas.softVersion.GetLength()+1;//其它信息起始位置
    //m_suppliersParas.other=readString(data,m_parsePos);//其它信息

    //m_parsePos+=m_suppliersParas.other.GetLength()+1;//下一记录起始位置

    //return TRUE;
}

////////////////////////////////////////////////////////////////////////////////////
//函数说明:读取FxdParams Block。
//入口参数:data:BYTE数组
//出口参数:
//建立时间:2011.7.8
//Write By:wcq
////////////////////////////////////////////////////////////////////////////////////
INT QSorFileBase::readFixedParas(BYTE data[])
{
    vchar2string(m_fixedParas.ID,std::string("FxdParams"));
    int blockLen=0;//block长度
    int strLen=0;
    blockLen+=10;//时间起始位置,跳过FxdParams\0
    m_fixedParas.timestamp=FOURINT(data,blockLen);//

    blockLen+=4;//单位起始位置
    m_fixedParas.distanceUnit.clear();
    m_fixedParas.distanceUnit.push_back(data[blockLen]);
    m_fixedParas.distanceUnit.push_back(data[blockLen+1]);

    blockLen+=2;//实际测量波长起始位置
    m_fixedParas.actualWavelength=TWOINT(data,blockLen);//

    blockLen+=2;//acquisition Offset波长起始位置
    m_fixedParas.acquisitionOffset=FOURINT(data,blockLen);//

    blockLen+=4;//acquisition Offset Distance起始位置
    m_fixedParas.AODistance=FOURINT(data,blockLen);//

    blockLen+=4;//脉宽个数起始位置
    int itemp=TWOINT(data,blockLen);
    m_fixedParas.pulseWidthNum=itemp;//

    blockLen+=2;//起始位置
    m_fixedParas.vPulseWidth.clear();
    for(int i=0;i<itemp;i++)
    {
        m_fixedParas.vPulseWidth.push_back(TWOINT(data,blockLen));
        blockLen+=2;//下一个位置
    }

    //blockLen+=2;//已在上面循环了加过
    //不同脉宽，10000个数据点时间起始位置
    m_fixedParas.vDataSpacing.clear();
    for(int i=0;i<itemp;i++)
    {
        m_fixedParas.vDataSpacing.push_back(FOURINT(data,blockLen));
        blockLen+=4;//下一个位置
    }

    //blockLen+=4;//已在上面循环了加过
    //每个脉宽数据点个数 起始位置
    m_fixedParas.vDataPointsEach.clear();
    for(int i=0;i<itemp;i++)
    {
        m_fixedParas.vDataPointsEach.push_back(FOURINT(data,blockLen));
        blockLen+=4;//下一个位置
    }

    //blockLen+=4;//group Index已在上面循环中加过.起始位置
    m_fixedParas.groupIndex=FOURINT(data,blockLen);

    blockLen+=4;//backscatter 起始位置
    m_fixedParas.backscatter=TWOINT(data,blockLen);

    blockLen+=2;//average number起始位置
    m_fixedParas.avgNum=FOURINT(data,blockLen);

    blockLen+=4;//average time 起始位置
    m_fixedParas.avgTime=TWOINT(data,blockLen);

    blockLen+=2;//acquisitionRange起始位置
    m_fixedParas.acquisitionRange=FOURINT(data,blockLen);

    blockLen+=4;//acquisitionRange distance起始位置
    m_fixedParas.ARDistance=FOURINT(data,blockLen);

    blockLen+=4;//front Panel Offset起始位置
    m_fixedParas.frontPanelOff=FOURINT(data,blockLen);

    blockLen+=4;//noise Floor Level 起始位置
    m_fixedParas.noiseFloorLevel=TWOINT(data,blockLen);

    blockLen+=2;//噪声级别系数 起始位置
    m_fixedParas.noiseFloorFactor=TWOINT(data,blockLen);

    blockLen+=2;//power offset first point起始位置
    m_fixedParas.powerOff=TWOINT(data,blockLen);

    blockLen+=2;//loss Threshold起始位置
    m_fixedParas.lossThreshold=TWOINT(data,blockLen);

    blockLen+=2;//反射域起始位置
    m_fixedParas.reflectanceThreshod=TWOINT(data,blockLen);

    blockLen+=2;//end-of-fiber threshold起始位置
    m_fixedParas.eofThreshold=TWOINT(data,blockLen);

    blockLen+=2;//trace Type追踪类型起始位置,标准上说是string，实际上是string 固定2字节，后面没\0
    //m_fixedParas.traceType=readString(data,blockLen);//
    m_fixedParas.traceType.clear();
    m_fixedParas.traceType.push_back(data[blockLen]);
    m_fixedParas.traceType.push_back(data[blockLen+1]);

    blockLen+=2;//window coordinates起始位置
    m_fixedParas.windowCoor1=FOURINT(data,blockLen);
    blockLen+=4;//
    m_fixedParas.windowCoor2=FOURINT(data,blockLen);
    blockLen+=4;//
    m_fixedParas.windowCoor3=FOURINT(data,blockLen);
    blockLen+=4;//
    m_fixedParas.windowCoor4=FOURINT(data,blockLen);


    blockLen+=4;//下一记录起始位置

    return blockLen;

    //CString temp;
    //m_parsePos+=10;//时间起始位置,跳过FxdParams\0
    //m_fixedParas.timestamp=FOURINT(data,m_parsePos);//

    //m_parsePos+=4;//单位起始位置
    //temp.Format(_T("%C%C"),data[m_parsePos],data[m_parsePos+1]);
    //m_fixedParas.distanceUnit=temp;//单位

    //m_parsePos+=2;//实际测量波长起始位置
    //m_fixedParas.actualWavelength=TWOINT(data,m_parsePos);//

    //m_parsePos+=2;//acquisition Offset波长起始位置
    //m_fixedParas.acquisitionOffset=FOURINT(data,m_parsePos);//

    //m_parsePos+=4;//acquisition Offset Distance起始位置
    //m_fixedParas.AODistance=FOURINT(data,m_parsePos);//

    //m_parsePos+=4;//脉宽个数起始位置
    //int itemp=TWOINT(data,m_parsePos);
    //m_fixedParas.pulseWidthNum=itemp;//

    //m_parsePos+=2;//起始位置
    //m_fixedParas.vPulseWidth.clear();
    //for(int i=0;i<itemp;i++)
    //{
    //	m_fixedParas.vPulseWidth.push_back(TWOINT(data,m_parsePos));
    //	m_parsePos+=2;//下一个位置
    //}

    ////m_parsePos+=2;//已在上面循环了加过
    ////不同脉宽，10000个数据点时间起始位置
    //m_fixedParas.vDataSpacing.clear();
    //for(int i=0;i<itemp;i++)
    //{
    //	m_fixedParas.vDataSpacing.push_back(FOURINT(data,m_parsePos));
    //	m_parsePos+=4;//下一个位置
    //}

    ////m_parsePos+=4;//已在上面循环了加过
    ////每个脉宽数据点个数 起始位置
    //m_fixedParas.vDataPointsEach.clear();
    //for(int i=0;i<itemp;i++)
    //{
    //	m_fixedParas.vDataPointsEach.push_back(FOURINT(data,m_parsePos));
    //	m_parsePos+=4;//下一个位置
    //}

    ////m_parsePos+=4;//group Index已在上面循环中加过.起始位置
    //m_fixedParas.groupIndex=FOURINT(data,m_parsePos);

    //m_parsePos+=4;//backscatter 起始位置
    //m_fixedParas.backscatter=TWOINT(data,m_parsePos);

    //m_parsePos+=2;//average number起始位置
    //m_fixedParas.avgNum=FOURINT(data,m_parsePos);

    //m_parsePos+=4;//average time 起始位置
    //m_fixedParas.avgTime=TWOINT(data,m_parsePos);

    //m_parsePos+=2;//acquisitionRange起始位置
    //m_fixedParas.acquisitionRange=FOURINT(data,m_parsePos);

    //m_parsePos+=4;//acquisitionRange distance起始位置
    //m_fixedParas.ARDistance=FOURINT(data,m_parsePos);

    //m_parsePos+=4;//front Panel Offset起始位置
    //m_fixedParas.frontPanelOff=FOURINT(data,m_parsePos);

    //m_parsePos+=4;//noise Floor Level 起始位置
    //m_fixedParas.noiseFloorLevel=TWOINT(data,m_parsePos);

    //m_parsePos+=2;//噪声级别系数 起始位置
    //m_fixedParas.noiseFloorFactor=TWOINT(data,m_parsePos);

    //m_parsePos+=2;//power offset first point起始位置
    //m_fixedParas.powerOff=TWOINT(data,m_parsePos);

    //m_parsePos+=2;//loss Threshold起始位置
    //m_fixedParas.lossThreshold=TWOINT(data,m_parsePos);

    //m_parsePos+=2;//反射域起始位置
    //m_fixedParas.reflectanceThreshod=TWOINT(data,m_parsePos);

    //m_parsePos+=2;//end-of-fiber threshold起始位置
    //m_fixedParas.eofThreshold=TWOINT(data,m_parsePos);

    //m_parsePos+=2;//trace Type追踪类型起始位置
    //m_fixedParas.traceType=readString(data,m_parsePos);//

    //m_parsePos+=m_fixedParas.traceType.GetLength()+1;//window coordinates起始位置
    //m_fixedParas.windowCoor1=FOURINT(data,m_parsePos);
    //m_parsePos+=4;//
    //m_fixedParas.windowCoor2=FOURINT(data,m_parsePos);
    //m_parsePos+=4;//
    //m_fixedParas.windowCoor3=FOURINT(data,m_parsePos);
    //m_parsePos+=4;//
    //m_fixedParas.windowCoor4=FOURINT(data,m_parsePos);


    //m_parsePos+=4;//下一记录起始位置

    //return TRUE;
}

////////////////////////////////////////////////////////////////////////////////////
//函数说明:读取readKeyEvents Block。还没测试?????????????????????????????????????????????
//入口参数:data:BYTE数组
//出口参数:
//建立时间:2011.7.8
//Write By:wcq
////////////////////////////////////////////////////////////////////////////////////
INT QSorFileBase::readKeyEvents(BYTE data[])
{
    vchar2string(m_keyEvent.ID,string("KeyEvents"));
    int blockLen=0;//block长度
    int strLen=0;
    blockLen+=10;//事件个数起始位置,跳过KeyEvents\0
    int count=TWOINT(data,blockLen);
    m_keyEvent.keyEventNum=count;//

    KeyEvent::Event event;
    blockLen+=2;//第一个事件起始位置
    m_keyEvent.vEvent.clear();
    for (int i=0;i<count;i++)
    {
        event.eventNum=TWOINT(data,blockLen);//编号

        blockLen+=2;//连接后第一个e事件点时间起始位置
        event.propagationTime=FOURINT(data,blockLen);//

        blockLen+=4;//衰减系数 起始位置
        event.attenCoefficent=TWOINT(data,blockLen);//

        blockLen+=2;//事件损耗 起始位置
        event.eventLoss=TWOINT(data,blockLen);//

        blockLen+=2;//事件反射 起始位置
        event.reflectance=FOURINT(data,blockLen);//

        blockLen+=4;//事件标志 起始位置
        //temp.Format(_T("%C%C%C%C%C%C"),data[blockLen],data[blockLen+1],data[blockLen+2],data[blockLen+3],data[blockLen+4],data[blockLen+5]);
        event.code.clear();
        for (int i=0;i<6;i++)//6字节
        {
            event.code.push_back(data[blockLen+i]);
        }

        blockLen+=6;//loss Measurement Technique起始位置
        //temp.Format(_T("%C%C"),data[blockLen],data[blockLen+1]);//2字节
        event.lossMeasurement.clear();
        event.lossMeasurement.push_back(data[blockLen]);
        event.lossMeasurement.push_back(data[blockLen+1]);
        //event.lossMeasurement=temp;

        blockLen+=2;//marker Locations起始位置
        for (int j=0;j<5;j++)
        {
            event.markerLocations[j]=FOURINT(data,blockLen);//
            blockLen+=4;//注释 起始位置
        }

        //event.comment=readString(data,blockLen);//
        strLen=readString(data + blockLen,event.comment);//

        blockLen+=strLen+1;//下一记录起始位置

        m_keyEvent.vEvent.push_back(event);
    }//efor


    ///blockLen+=2;//已加过End-to-End Loss 起始位置
    m_keyEvent.eteLoss=FOURINT(data,blockLen);//

    blockLen+=4;//End-to-End Marker Positions Start 起始位置
    m_keyEvent.eteMarkerStart=FOURINT(data,blockLen);//

    blockLen+=4;//End-to-End Marker Positions Finish 起始位置
    m_keyEvent.eteMarkerFinish=FOURINT(data,blockLen);//

    blockLen+=4;//回损 起始位置
    m_keyEvent.returnLoss=TWOINT(data,blockLen);//

    blockLen+=2;//回损标志起点 起始位置
    m_keyEvent.RLMarkerStart=FOURINT(data,blockLen);//

    blockLen+=4;//回损标志结束点 起始位置
    m_keyEvent.RLMarkerFinish=FOURINT(data,blockLen);//

    blockLen+=4;//下一记录起始位置

    return blockLen;

    //m_parsePos+=10;//事件个数起始位置,跳过LnkParams\0
    //int count=TWOINT(data,m_parsePos);
    //m_keyEvent.keyEventNum=count;//

    //KeyEvent::Event event;
    //m_parsePos+=2;//第一个事件起始位置
    //CString temp;
    //m_keyEvent.vEvent.clear();
    //for (int i=0;i<count;i++)
    //{
    //	event.eventNum=TWOINT(data,m_parsePos);//编号

    //	m_parsePos+=2;//连接后第一个e事件点时间起始位置
    //	event.propagationTime=FOURINT(data,m_parsePos);//

    //	m_parsePos+=4;//衰减系数 起始位置
    //	event.attenCoefficent=TWOINT(data,m_parsePos);//

    //	m_parsePos+=2;//事件损耗 起始位置
    //	event.eventLoss=TWOINT(data,m_parsePos);//

    //	m_parsePos+=2;//事件反射 起始位置
    //	event.reflectance=FOURINT(data,m_parsePos);//

    //	m_parsePos+=4;//事件标志 起始位置
    //	temp.Format(_T("%C%C%C%C%C%C"),data[m_parsePos],data[m_parsePos+1],data[m_parsePos+2],data[m_parsePos+3],data[m_parsePos+4],data[m_parsePos+5]);
    //	event.code=temp;//6字节

    //	m_parsePos+=6;//loss Measurement Technique起始位置
    //	temp.Format(_T("%C%C"),data[m_parsePos],data[m_parsePos+1]);//2字节
    //	event.lossMeasurement=temp;

    //	m_parsePos+=2;//marker Locations起始位置
    //	event.markerLocations=FOURINT(data,m_parsePos);//

    //	m_parsePos+=4;//注释 起始位置
    //	event.comment=readString(data,m_parsePos);//

    //	m_parsePos+=event.comment.GetLength()+1;//下一记录起始位置

    //	m_keyEvent.vEvent.push_back(event);
    //}//efor


    /////m_parsePos+=2;//已加过End-to-End Loss 起始位置
    //m_keyEvent.eteLoss=FOURINT(data,m_parsePos);//

    //m_parsePos+=4;//End-to-End Marker Positions Start 起始位置
    //m_keyEvent.eteMarkerStart=FOURINT(data,m_parsePos);//

    //m_parsePos+=4;//End-to-End Marker Positions Finish 起始位置
    //m_keyEvent.eteMarkerFinish=FOURINT(data,m_parsePos);//

    //m_parsePos+=4;//回损 起始位置
    //m_keyEvent.eteLoss=TWOINT(data,m_parsePos);//

    //m_parsePos+=2;//回损标志起点 起始位置
    //m_keyEvent.RLMarkerStart=FOURINT(data,m_parsePos);//

    //m_parsePos+=4;//回损标志结束点 起始位置
    //m_keyEvent.RLMarkerFinish=FOURINT(data,m_parsePos);//

    //m_parsePos+=4;//下一记录起始位置

    //return TRUE;
}

////////////////////////////////////////////////////////////////////////////////////
//函数说明:读取LinkParas Block。还没测试?????????????????????????????????????????????
//入口参数:data:BYTE数组
//出口参数:
//建立时间:2011.10.8
//Write By:wcq
////////////////////////////////////////////////////////////////////////////////////
INT QSorFileBase::readLinkParas(BYTE data[])
{
    vchar2string(m_linkParas.ID,string("LnkParams"));
    int blockLen=0;//block长度
    int strLen=0;
    blockLen+=10;//事件个数起始位置,跳过LnkParams\0
    int count=TWOINT(data,blockLen);
    m_linkParas.totalLandmarks=count;//地标个数

    LinkParas::Landmark landmark;
    blockLen+=2;//第一个事件起始位置,跳过地标个数
//    CString temp;
    m_linkParas.vLandmark.clear();
    for (int i=0;i<count;i++)
    {
        landmark.num=TWOINT(data,blockLen);//编号

        blockLen+=2;//地标类别码
        //temp.Format(_T("%C%C"),data[blockLen],data[blockLen+1]);
        //landmark.code=temp;//2字节
        landmark.code.clear();
        landmark.code.push_back(data[blockLen]);
        landmark.code.push_back(data[blockLen+1]);

        blockLen+=2;//location 4字节
        landmark.location=FOURINT(data,blockLen);//


        blockLen+=4;//related Event Number相应事件编号
        landmark.relatedEventNum=TWOINT(data,blockLen);//

        blockLen+=2;//GPS Information GPS信息 4字节//GPS经度
        landmark.GPSLongitude=FOURINT(data,blockLen);//

        blockLen+=4;//GPS纬度
        landmark.GPSLatitude=FOURINT(data,blockLen);//

        blockLen+=4;//Fiber Correction Factor Lead-in Fiber  2字节
        landmark.fiberCorrFactor = TWOINT(data,blockLen);//

        blockLen+=2;//Sheath Marker Entering LandMark 4字节
        landmark.sheathEntering=FOURINT(data,blockLen);//

        blockLen+=4;////Sheath Marker Leaving LandMark 4字节 路标后面的光纤外套上的数字
        landmark.sheathLeaving=FOURINT(data,blockLen);//

        blockLen+=4;//光纤外套上表示距离的单位 2字节 feet 或 meters
        //temp.Format(_T("%C%C"),data[blockLen],data[blockLen+1]);
        //landmark.SLUnit=temp;//
        landmark.SLUnit.clear();
        landmark.SLUnit.push_back(data[blockLen]);
        landmark.SLUnit.push_back(data[blockLen+1]);

        blockLen+=2;//Mode Field Diameter Leaving LandMark 放大率 2字节
        landmark.modeFieldDiameter=TWOINT(data,blockLen);//

        blockLen+=2;//Comment注释 string
        //landmark.comment=readString(data,blockLen);//
        strLen=readString(data + blockLen,landmark.comment);//

        blockLen+=strLen+1;//下一记录起始位置
        m_linkParas.vLandmark.push_back(landmark);
    }//efor

    return blockLen;

    //m_parsePos+=10;//事件个数起始位置,跳过KeyEvents\0
    //int count=TWOINT(data,m_parsePos);
    //m_linkParas.totalLandmarks=count;//地标个数

    //LinkParas::Landmark landmark;
    //m_parsePos+=2;//第一个事件起始位置,跳过地标个数
    //CString temp;
    //m_linkParas.vLandmark.clear();
    //for (int i=0;i<count;i++)
    //{
    //	landmark.num=TWOINT(data,m_parsePos);//编号

    //	m_parsePos+=2;//地标类别码
    //	temp.Format(_T("%C%C"),data[m_parsePos],data[m_parsePos+1]);
    //	landmark.code=temp;//2字节

    //	m_parsePos+=2;//location 4字节
    //	landmark.location=FOURINT(data,m_parsePos);//


    //	m_parsePos+=4;//related Event Number相应事件编号
    //	landmark.relatedEventNum=TWOINT(data,m_parsePos);//

    //	m_parsePos+=2;//GPS Information GPS信息 4字节//GPS经度
    //	landmark.GPSLongitude=FOURINT(data,m_parsePos);//

    //	m_parsePos+=4;//GPS纬度
    //	landmark.GPSLatitude=FOURINT(data,m_parsePos);//

    //	m_parsePos+=4;//Fiber Correction Factor Lead-in Fiber  2字节
    //	landmark.fiberCorrFactor = TWOINT(data,m_parsePos);//

    //	m_parsePos+=2;//Sheath Marker Entering LandMark 4字节
    //	landmark.sheathEntering=FOURINT(data,m_parsePos);//

    //	m_parsePos+=4;////Sheath Marker Leaving LandMark 4字节 路标后面的光纤外套上的数字
    //	landmark.sheathLeaving=FOURINT(data,m_parsePos);//

    //	m_parsePos+=4;//光纤外套上表示距离的单位 2字节 feet 或 meters
    //	temp.Format(_T("%C%C"),data[m_parsePos],data[m_parsePos+1]);
    //	landmark.SLUnit=temp;//

    //	m_parsePos+=2;//Mode Field Diameter Leaving LandMark 放大率 2字节
    //	landmark.modeFieldDiameter=FOURINT(data,m_parsePos);//

    //	m_parsePos+=2;//Comment注释 string
    //	landmark.comment=readString(data,m_parsePos);//

    //	m_parsePos+=landmark.comment.GetLength()+1;//下一记录起始位置
    //	m_linkParas.vLandmark.push_back(landmark);
    //}//efor

    //return TRUE;
}

////////////////////////////////////////////////////////////////////////////////////
//函数说明:读取DataPts Block。测试通过7.8
//入口参数:data:BYTE数组
//出口参数:
//建立时间:2011.7.8
//Write By:wcq
////////////////////////////////////////////////////////////////////////////////////
INT QSorFileBase::readDataPts(BYTE data[])
{
    vchar2string(m_dataPoints.ID,string("DataPts"));
    int blockLen=0;//block长度
    //int strLen=0;
    blockLen+=8;//事件个数起始位置,跳过DataPts\0
    int count=FOURINT(data,blockLen);
    m_dataPoints.dataPointNum=count;//

    blockLen+=4;//使用的扩展系数个数 起始位置
    count=TWOINT(data,blockLen);//
    m_dataPoints.totalScaleFactors=count;

    ///int itemp;
    blockLen+=2;//第一个扩展系数相关数据-总个数 起始位置
    DataPoints::DataUseScaleFactor dataFactor;
    int len;
    FLOAT factor;
    m_dataPoints.vAllData.clear();
    unsigned short* pUnShort;
    for (int i=0;i<count;i++)
    {
        len=FOURINT(data,blockLen);
        dataFactor.count=len;//使用当前系数的数据总个数

        blockLen += 4;//系数 起始位置
        dataFactor.scaleFactor=TWOINT(data,blockLen);//1000=1.0
        ////factor=dataFactor.scaleFactor/1000.0;//1000==1.0

        blockLen += 2;//具体数据 起始位置
        dataFactor.vData.clear();
        //for (int j=0;j<len;j++)//原来可以正常读取wcq2011.10.21
        //{
        //	////dataFactor.vData.push_back(TWOINT(data,blockLen)*factor);
        //	dataFactor.vData.push_back(TWOINT(data,blockLen));

        //	blockLen+=2;//下一个数据 起始位置
        //}//efor
        pUnShort = (unsigned short*)(data+blockLen);
        dataFactor.vData.assign(pUnShort,pUnShort+len);
        blockLen += len * 2;
        m_dataPoints.vAllData.push_back(dataFactor);
    }//efor

    ////blockLen+=2;//下一记录起始位置,已在前面循环加过

    return blockLen;

    //m_parsePos+=8;//事件个数起始位置,跳过DataPts\0
    //int count=FOURINT(data,m_parsePos);
    //m_dataPoints.dataPointNum=count;//

    //m_parsePos+=4;//使用的扩展系数个数 起始位置
    //count=TWOINT(data,m_parsePos);//
    //m_dataPoints.totalScaleFactors=count;

    /////int itemp;
    //m_parsePos+=2;//第一个扩展系数相关数据-总个数 起始位置
    //DataPoints::DataUseScaleFactor dataFactor;
    //int len;
    //FLOAT factor;
    //m_dataPoints.vAllData.clear();
    //for (int i=0;i<count;i++)
    //{
    //	len=FOURINT(data,m_parsePos);
    //	dataFactor.count=len;//使用当前系数的数据总个数

    //	m_parsePos+=4;//系数 起始位置
    //	dataFactor.scaleFactor=TWOINT(data,m_parsePos);//1000=1.0
    //	factor=dataFactor.scaleFactor/1000.0;//1000==1.0

    //	m_parsePos+=2;//具体数据 起始位置
    //	dataFactor.vData.clear();
    //	for (int j=0;j<len;j++)
    //	{
    //		dataFactor.vData.push_back(TWOINT(data,m_parsePos)*factor);
    //
    //		m_parsePos+=2;//下一个数据 起始位置
    //	}//efor
    //	m_dataPoints.vAllData.push_back(dataFactor);
    //}//efor

    //////m_parsePos+=2;//下一记录起始位置,已在前面循环加过

    //return TRUE;
}

INT QSorFileBase::readUserName(BYTE data[])
{
    vchar2string(m_userName.ID,string("UserName"));
    int blockLen=0;//block长度
    vchar2string(m_userName.name,string(""));

    return blockLen;
}
////////////////////////////////////////////////////////////////////////////////////
//函数说明:读取Cksum Block。校验码。从最后开始读取。测试通过7.8
//入口参数:data:BYTE数组,length:文件字节数
//出口参数:
//建立时间:2011.7.8
//Write By:wcq
////////////////////////////////////////////////////////////////////////////////////
INT QSorFileBase::readCKsum(BYTE data[])
{
    vchar2string(m_checksum.ID,string("Cksum"));
    int blockLen=0;//block长度
    blockLen+=6;//校验码 起始位置
    m_checksum.checksum=TWOINT(data,blockLen);//

    return blockLen;

    //m_parsePos=length-8;//事件个数起始位置,CKsum\0起始位置.CKsum总在文件的最后，所以从最后读取。
    //CString temp;
    //temp=readString(data,m_parsePos);//
    //if("CKsum"!=temp)
    //{
    //	return FALSE;
    //}

    //m_parsePos+=6;//校验码 起始位置
    //m_checksum.checksum=TWOINT(data,m_parsePos);//

    //return TRUE;
}
////////////////////////////////////////////////////////////////////////////////////
//函数说明:读取未知Block
//入口参数:data:BYTE数组,nextBlockID:下一个Block的ID，startPos:起始位置，maxLen文件最大长度
//出口参数:Block长度
//建立时间:2011.10.10
//Write By:wcq
////////////////////////////////////////////////////////////////////////////////////
////INT QSorFileBase::readUnknownParas(BYTE data[],vector<char> nextBlockID,int startPos,int maxLen)
////{
////	int blockLen=0;//block长度
////	int remainLen =maxLen - startPos;//
////	int strLen=nextBlockID.size();
////	//bool bContinue=true;
////	int j;
////	while(blockLen< remainLen)
////	{
////		if (nextBlockID[0] == data[blockLen])//和下一个block ID的第一个字符一样
////		{
////			for (j=0;j<strLen;j++)
////			{
////				if (nextBlockID[j] != data[blockLen + j])
////				{
////					break;
////				}
////			}
////			if (j == strLen)////所有字符都一样。到了下一个block
////			{
////				blockLen--;
////				break;
////			}
////		}
////		blockLen++;
////	}//eofwhile
////
////	//保存当前Block到m_vUnknownParas
////	vector<BYTE> vcParams(data,data+blockLen-1);
////	m_vUnknownParas.push_back(vcParams);
////
////	return blockLen;
////}
////////////////////////////////////////////////////////////////////////////////////
//函数说明://读取文件时检查各个block大小之和是否大于文件总大小
//入口参数:fileLen:文件总大小
//出口参数:
//建立时间:2011.10.11
//Write By:wcq
////////////////////////////////////////////////////////////////////////////////////
BOOL QSorFileBase::checkSize(int fileLen)
{
    int len=m_mapBlock.mapBlock.Size;
    int count=m_mapBlock.blockCount-1;//总共有多少个Block,减去Map Block本身
    for (int i=0;i<count;i++)
    {
        len += m_mapBlock.vBlockInfo[i].Size;
    }
    if (len != fileLen)
    {
        return FALSE;
    }
    return TRUE;
}
////////////////////////////////////////////////////////////////////////////////////
//函数说明:读取.sor文件,没考虑超出文件位置。以1000作为最大字符串长度.转化过程是否可优化**MM**
//入口参数:data:BYTE数组;startPos:起始位置
//出口参数:读到的字符串
//建立时间:2011.7.8
//Write By:wcq
////////////////////////////////////////////////////////////////////////////////////
QString QSorFileBase::readString(BYTE data[],int startPos)
{
    QString temp=QString("");

    int itemp=0;
    while('\0'!=data[startPos+itemp] && itemp<1000)//以1000作为最大字符串长度
    {
        temp.append(QChar(data[startPos+itemp]));
        itemp++;
    }
    return temp;
}
////////////////////////////////////////////////////////////////////////////////////
//函数说明:
//入口参数:vChar:存放返回结果,data:可能加了偏移。vChar:保存字符串
//出口参数:多少个字节
//建立时间:2011.10.9
//Write By:wcq
////////////////////////////////////////////////////////////////////////////////////
int QSorFileBase::readString(BYTE data[],vector<char>& vChar)
{
    int itemp=0;
    vChar.clear();
    while('\0'!=data[itemp] && itemp<MAX_STRING_LEN)//以1000作为最大字符串长度
    {
        vChar.push_back(data[itemp]);
        itemp++;
    }
    return vChar.size();
}

unsigned short QSorFileBase::crc16(qint8 d[], int len)
{
    qint8 b = 0;
    unsigned short crc = 0xffff;
    int i, j;
    for(i=0; i<len; i++)
    {
        for(j=0; j<8; j++)
        {
            b = ((d[i]<<j)&0x80) ^ ((crc&0x8000)>>8);
            crc<<=1;
            if(b!=0)crc^=0x1021;
        }
    }
    crc = ~crc;
    return crc;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////
//获取长度////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
//主要是用于保存新的文件，如果是加载，则不会改变，也不用重新计算.???????????????????????????
INT QSorFileBase::MapBlock::getsize()
{
    INT len;
    //len=4 + 6;//Map本身
    //len+= 2;//Block个数
    //len+= (10 + 6)*4;//GenParams/SupParams/FxdParams/KeyEvents/
    /////len+= 10 + 6;//LnkParams暂时不加
    //len+= 8 + 6;//DataPts
    /////Special Propritary暂时不加
    //len+= 6 + 6;//Cksum

    len=102;//如果添加新Block需要重新计算.???????????????????????????
    return len;
}
//主要是用于保存新的文件，如果是加载，则不会改变，也不用重新计算
INT QSorFileBase::GeneralParas::getsize()
{
    INT len = 10;//:GenParams本身
    len += 16;//不变的相加
    len += cableID.size()+1;
    len += fiberID.size()+1;
    len += OLocation.size()+1;
    len += TLocation.size()+1;
    len += cableCode.size()+1;
    len += operater.size()+1;
    len += comment.size()+1;
    return len;
}
INT QSorFileBase::SuppliersParas::getsize()
{
    INT len = 10;//:SupParams本身
    len += name.size()+1;
    len += mainframeID.size()+1;
    len += mainframeSn.size()+1;
    len += moduleID.size()+1;
    len += moduleSn.size()+1;
    len += softVersion.size()+1;
    len += other.size()+1;
    return len;
}
INT QSorFileBase::FixedParas::getsize()
{
    INT len = 10;//:FixedParas本身
    //len += 74;//
    len += 72;//
    len += pulseWidthNum * 10;
    return len;
}
INT QSorFileBase::KeyEvent::getsize()
{
    INT len = 10;//KeyEvents本身
    len += 24;//

    for (int i=0;i<keyEventNum;i++)
    {
        len += 42 + vEvent[i].comment.size()+1;
    }
    return len;
}
INT QSorFileBase::LinkParas::getsize()
{
    INT len = 10;//KeyEvents本身
    len += 2;//

    for (int i=0;i<totalLandmarks;i++)
    {
        len += 32 + vLandmark[i].comment.size()+1;
    }
    return len;
}
INT QSorFileBase::DataPoints::getsize()
{
    INT len = 8;//KeyEvents本身
    len += 6;//dataPointNum + totalScaleFactors

    //for (int i=0;i<totalScaleFactors;i++)
    for (int i=0;i<vAllData.size();i++)
    {
        len += 6 + vAllData[i].count * 2;
    }
    return len;
}
INT QSorFileBase::Checksum::getsize()
{
    return 8;
}
