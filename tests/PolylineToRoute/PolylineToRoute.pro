#-------------------------------------------------
#
# Project created by QtCreator 2018-03-12T21:54:40
#
#-------------------------------------------------

QT       += widgets testlib positioning location

QT       -= gui

TARGET = tst_polyline_to_route_test
CONFIG   += console
CONFIG   -= app_bundle
CONFIG   += C++14

TEMPLATE = app


SOURCES += \
    tst_polyline_to_route_test.cpp \
    ../../src/converter.cpp \
    ../../src/exceptions.cpp \
    ../../src/route.cpp \
    ../../src/point_table_model.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    ../../src/converter.h \
    ../../src/exceptions.h \
    ../../src/route.h \
    ../../src/point_table_model.h
