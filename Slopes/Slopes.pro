#-------------------------------------------------
#
# Project created by QtCreator 2018-05-20T03:36:10
#
#-------------------------------------------------

QT       -= gui
QT       += positioning

TARGET = Slopes
TEMPLATE = lib

DEFINES += SLOPES_LIBRARY

SOURCES += slopes.cpp

HEADERS += slopes.h\
        slopes_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
