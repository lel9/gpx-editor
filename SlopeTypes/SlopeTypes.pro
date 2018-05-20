#-------------------------------------------------
#
# Project created by QtCreator 2018-05-20T03:50:14
#
#-------------------------------------------------

QT       -= gui
QT       += positioning
CONFIG   += C++14

TARGET = SlopeTypes
TEMPLATE = lib

DEFINES += SLOPETYPES_LIBRARY

SOURCES += slopetypes.cpp

HEADERS += slopetypes.h\
        slopetypes_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
