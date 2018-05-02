#ifndef IFMSFINGER_H
#define IFMSFINGER_H
#include <vector>

using namespace std;
#pragma pack(push,1)

typedef struct _IFMSChannels
{
    union  {
        struct {
            unsigned char ch8 : 1;
            unsigned char ch7 : 1;
            unsigned char ch6 : 1;
            unsigned char ch5 : 1;
            unsigned char ch4 : 1;
            unsigned char ch3 : 1;
            unsigned char ch2 : 1;
            unsigned char ch1 : 1;
        } I;
        unsigned char  channels;
    } OTDRModule;

}__attribute__ ((packed)) IFMSChannels_t;

typedef struct _IFMSEvent{
    unsigned short  EventNo;
    float           EventPosition;
    short           EventLoss;
    qint32          EventReflectance;
    char            EventCode0;
    char            EventCode1;
}__attribute__ ((packed)) IFMSEvent_t;

typedef struct _IFMS_FINGER {
    unsigned short  Channel;
    unsigned int    GroupIndex;
    unsigned short  NumberOfEvents;

    std::vector<IFMSEvent_t> vIFMSEvents;
}__attribute__ ((packed)) IFMSFinger_t;

#pragma pack(pop)
#endif // IFMSFINGER_H
