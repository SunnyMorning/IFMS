
INCLUDEPATH += $$PWD



#LIBS += -L /home/sunny/myir-buildroot/output/host/usr/arm-myir-linux-gnueabihf/sysroot/usr/lib -lpthread -ldbus-1 -lcjson -lxml2 -lnetsnmpmibs \
#        -lnetsnmpagent -lnetsnmp -ldl -lcrypto

win32: LIBS += -L$$PWD/../../../usr/lib/ -lnetsnmp -lnetsnmpagent -lnetsnmphelpers -lnetsnmpmibs -lnetsnmptrapd

INCLUDEPATH += $$PWD/../../../usr/include
DEPENDPATH += $$PWD/../../../usr/include

#win32:!win32-g++: PRE_TARGETDEPS += $$PWD/../../../usr/lib/netsnmp.lib
#else:win32-g++: PRE_TARGETDEPS += $$PWD/../../../usr/lib/libnetsnmp.a
