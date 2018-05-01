
INCLUDEPATH += $$PWD



#LIBS += -L /home/sunny/myir-buildroot/output/host/usr/arm-myir-linux-gnueabihf/sysroot/usr/lib -lpthread -ldbus-1 -lcjson -lxml2 -lnetsnmpmibs \
#        -lnetsnmpagent -lnetsnmp -ldl -lcrypto

win32: LIBS += -L$$PWD/../../../usr/lib/ -lnetsnmp -lnetsnmpagent -lnetsnmphelpers -lnetsnmpmibs -lnetsnmptrapd


unix:!macx: LIBS += -L$$PWD/../../../../../../usr/local/lib/ -lnetsnmp -lnetsnmpagent -lnetsnmphelpers -lnetsnmpmibs -lnetsnmptrapd

INCLUDEPATH += $$PWD/''
DEPENDPATH += $$PWD/''

unix:!macx: PRE_TARGETDEPS += $$PWD/../../../../../../usr/local/lib/libnetsnmp.a
unix:!macx: PRE_TARGETDEPS += $$PWD/../../../../../../usr/local/lib/libnetsnmpagent.a
unix:!macx: PRE_TARGETDEPS += $$PWD/../../../../../../usr/local/lib/libnetsnmphelpers.a
unix:!macx: PRE_TARGETDEPS += $$PWD/../../../../../../usr/local/lib/libnetsnmpmibs.a
unix:!macx: PRE_TARGETDEPS += $$PWD/../../../../../../usr/local/lib/libnetsnmptrapd.a
