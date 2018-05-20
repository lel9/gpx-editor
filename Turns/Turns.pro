#-------------------------------------------------
#
# Project created by QtCreator 2018-05-19T21:03:21
#
#-------------------------------------------------

QT       -= gui

TARGET = Turns
TEMPLATE = lib

DEFINES += TURNS_LIBRARY

SOURCES += turns.cpp

HEADERS += turns.h\
        turns_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
