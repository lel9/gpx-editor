#-------------------------------------------------
#
# Project created by QtCreator 2018-03-12T23:46:25
#
#-------------------------------------------------

QT       += widgets testlib positioning location

QT       -= gui

TARGET = tst_remove_route_test
CONFIG   += console
CONFIG   -= app_bundle

CONFIG += C++14

TEMPLATE = app


SOURCES += tst_remove_route_test.cpp \
    ../../src/exceptions.cpp \
    ../../src/point_table_model.cpp \
    ../../src/route.cpp \
    ../../src/route_table_model.cpp \
    random_route_factory.cpp \
    ../../src/converter.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    ../../src/exceptions.h \
    ../../src/point_table_model.h \
    ../../src/route.h \
    ../../src/route_table_model.h \
    random_route_factory.h \
    ../../src/converter.h
