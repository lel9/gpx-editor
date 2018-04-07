#-------------------------------------------------
#
# Project created by QtCreator 2018-03-12T13:02:21
#
#-------------------------------------------------

QT       += widgets testlib positioning location

QT       -= gui

TARGET = tst_route_to_polyline_test
CONFIG   += console
CONFIG   += C++14
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += tst_route_to_polyline_test.cpp \
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
