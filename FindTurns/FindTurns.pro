#-------------------------------------------------
#
# Project created by QtCreator 2018-05-06T00:07:29
#
#-------------------------------------------------

QT       -= gui

TARGET = FindTurns
TEMPLATE = lib

DEFINES += FINDTURNS_LIBRARY

SOURCES += findturns.cpp

HEADERS += findturns.h\
        findturns_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
