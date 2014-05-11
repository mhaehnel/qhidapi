#-------------------------------------------------
#
# Project created by QtCreator 2014-05-11T20:47:11
#
#-------------------------------------------------

QT       -= gui

TARGET = qhidapi
TEMPLATE = lib

CONFIG += c++11

DEFINES += QHIDAPI_LIBRARY

SOURCES += qhidmanager.cpp \
    qhidevice.cpp

HEADERS += qhidmanager.h\
        qhidapi_global.h \
    qhidevice.h \
    qhidinfo.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
