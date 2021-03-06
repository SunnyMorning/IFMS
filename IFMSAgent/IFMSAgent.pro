QT -= gui
QT += core dbus
QT += serialport network
CONFIG += c++11 console
CONFIG -= app_bundle

QMAKE_CXXFLAGS += -O0
QMAKE_CXXFLAGS -= -Os
QMAKE_CXXFLAGS -= -O2
QMAKE_CXXFLAGS -= -O3

QMAKE_CXXFLAGS += -Wno-deprecated

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# mount -o bind /usr/share/ifms  /home/ftp/nand
# mount -o bind /tmp/ifms /home/ftp/ram

D_DATA_DIR = /usr/share/ifms/
D_CACHE_DIR = /tmp/ifms/

#message(pwd=$(PWD))
#message("DATADIR="\"$${D_DATA_DIR}\")
#message("CACHEDIR="\"$${D_CACHE_DIR}\")

DEFINES += D_DATA_DIR=\\\"$${D_DATA_DIR}\\\"
DEFINES += D_CACHE_DIR=\\\"$${D_CACHE_DIR}\\\"

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

target.path = /usr/bin/
INSTALLS += target


include (./config.pri)
SOURCES += main.cpp \
    qagentapp.cpp \
    qotdrmodule.cpp \
    qfingerdata.cpp \
    qsorfilebase.cpp \
    qpstsystem.cpp \
    qpstproduct.cpp \
    qpst.cpp \
    qpstsystemprivate.cpp \
    qpstproductprivate.cpp \
    qcommander.cpp \
    qfancontrol.cpp \
    SysfsGPIO.cpp
HEADERS += \
    qagentapp.h \
    qcommander.h \
    qotdrmodule.h \
    qfingerdata.h \
    qsorfilebase.h \
    ifmsfinger.h \
    qpst.h \
    qpstsystem.h \
    qpstproduct.h \
    qpstsystemprivate.h \
    qpstproductprivate.h \
    qfancontrol.h \
    SysfsGPIO.h \
    gpio_ifms1000.h

DISTFILES += \
    pstRoot \
    ../PST-IFMS1000-MIB.my \
    ../PST-MIB.my \
    ../PST-SYSTEM-MIB.my \
    ../snmpd.conf
