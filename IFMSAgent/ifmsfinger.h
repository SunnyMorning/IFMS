#ifndef IFMSFINGER_H
#define IFMSFINGER_H
#include <vector>

using namespace std;
#pragma pack(push,1)

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
