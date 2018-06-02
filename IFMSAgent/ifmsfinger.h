#ifndef IFMSFINGER_H
#define IFMSFINGER_H
#include <vector>

#define 	EVENT_TYPE_INIT						0x0000
#define 	EVENT_TYPE_OLD						0x0001
#define 	EVENT_TYPE_DISAPPEAR				0x0002
#define 	EVENT_TYPE_NEW_CRITICAL				0x0004
#define 	EVENT_TYPE_NEW_MAIN					0x0008
#define 	EVENT_TYPE_NEW_MINOR				0x0010
#define		EVENT_TYPE_NEW						0x0020
#define 	EVENT_TYPE_CHANGE_CRITICAL			0x0040
#define 	EVENT_TYPE_CHANGE_MAIN				0x0080
#define 	EVENT_TYPE_CHANGE_MINOR				0x0100
#define 	EVENT_TYPE_CHANGE_LITTLE			0x0200

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
    unsigned int    EventPosition;
    short           EventLoss;
    int             EventReflectance;
    char            EventCode0;
    char            EventCode1;
	unsigned short	EventType;
	
}__attribute__ ((packed)) IFMSEvent_t;

typedef struct _IFMS_FINGER {
    unsigned short  Channel;
    unsigned int    GroupIndex;
    unsigned short  NumberOfEvents;

    std::vector<IFMSEvent_t> vIFMSEvents;
    qint32			EndtoEndLoss;
}__attribute__ ((packed)) IFMSFinger_t;

#pragma pack(pop)
#endif // IFMSFINGER_H
