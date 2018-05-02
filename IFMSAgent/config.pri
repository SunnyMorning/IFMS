
INCLUDEPATH += $$PWD

win32: LIBS += -L$$PWD/../../../usr/lib/ -lnetsnmp -lnetsnmpagent -lnetsnmphelpers -lnetsnmpmibs -lnetsnmptrapd

CONFIG(X86_64, ARM|X86_64) {
    unix:!macx: LIBS += -L$$PWD/../../../../../../usr/local/lib/ -lnetsnmp -lnetsnmpagent -lnetsnmphelpers -lnetsnmpmibs -lnetsnmptrapd

    INCLUDEPATH += $$PWD/''
    DEPENDPATH += $$PWD/''

    unix:!macx: PRE_TARGETDEPS += $$PWD/../../../../../../usr/local/lib/libnetsnmp.a
    unix:!macx: PRE_TARGETDEPS += $$PWD/../../../../../../usr/local/lib/libnetsnmpagent.a
    unix:!macx: PRE_TARGETDEPS += $$PWD/../../../../../../usr/local/lib/libnetsnmphelpers.a
    unix:!macx: PRE_TARGETDEPS += $$PWD/../../../../../../usr/local/lib/libnetsnmpmibs.a
    unix:!macx: PRE_TARGETDEPS += $$PWD/../../../../../../usr/local/lib/libnetsnmptrapd.a

    DEFINES += HAVE_SOR_FILES=1
} else {


    unix:!macx: LIBS += -L$$PWD/../../../myir-buildroot/output/host/usr/arm-myir-linux-gnueabihf/sysroot/usr/lib/ -lnetsnmp -lnetsnmpagent -lnetsnmphelpers -lnetsnmpmibs -lnetsnmptrapd

    INCLUDEPATH += $$PWD/../../../myir-buildroot/output/host/usr/arm-myir-linux-gnueabihf/sysroot/usr/include
    DEPENDPATH += $$PWD/../../../myir-buildroot/output/host/usr/arm-myir-linux-gnueabihf/sysroot/usr/include

    unix:!macx: PRE_TARGETDEPS += $$PWD/../../../myir-buildroot/output/host/usr/arm-myir-linux-gnueabihf/sysroot/usr/lib/libnetsnmp.a
    unix:!macx: PRE_TARGETDEPS += $$PWD/../../../myir-buildroot/output/host/usr/arm-myir-linux-gnueabihf/sysroot/usr/lib/libnetsnmpagent.a
    unix:!macx: PRE_TARGETDEPS += $$PWD/../../../myir-buildroot/output/host/usr/arm-myir-linux-gnueabihf/sysroot/usr/lib/libnetsnmphelpers.a
    unix:!macx: PRE_TARGETDEPS += $$PWD/../../../myir-buildroot/output/host/usr/arm-myir-linux-gnueabihf/sysroot/usr/lib/libnetsnmpmibs.a
    unix:!macx: PRE_TARGETDEPS += $$PWD/../../../myir-buildroot/output/host/usr/arm-myir-linux-gnueabihf/sysroot/usr/lib/libnetsnmptrapd.a
}

