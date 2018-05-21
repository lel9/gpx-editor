#-------------------------------------------------
#
# Project created by QtCreator 2018-05-21T02:29:38
#
#-------------------------------------------------

QT       += testlib positioning printsupport
QT       -= gui

CONFIG += C++14


TARGET = tst_addpointtest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += tst_addpointtest.cpp \
    ../../src/qcustomplot/qcustomplot.cpp \
    ../../src/add_point_command.cpp \
    ../../src/add_route_command.cpp \
    ../../src/command.cpp \
    ../../src/command_manager.cpp \
    ../../src/converter.cpp \
    ../../src/edit_point_command.cpp \
    ../../src/exceptions.cpp \
    ../../src/graphplot.cpp \
    ../../src/model_index_iterator.cpp \
    ../../src/point_table_model.cpp \
    ../../src/presenter.cpp \
    ../../src/remove_point_command.cpp \
    ../../src/remove_route_command.cpp \
    ../../src/route.cpp \
    ../../src/route_loader.cpp \
    ../../src/route_saver.cpp \
    ../../src/route_table_model.cpp \
    ../../src/table_index.cpp \
    ../../src/visitor_manager.cpp \
    ../data_struct.cpp \
    ../route_factory.cpp \
    ../testview.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    ../../src/qcustomplot/qcustomplot.h \
    ../../src/add_point_command.h \
    ../../src/add_route_command.h \
    ../../src/baseview.h \
    ../../src/command.h \
    ../../src/command_manager.h \
    ../../src/converter.h \
    ../../src/edit_point_command.h \
    ../../src/enum_insert_point.h \
    ../../src/exceptions.h \
    ../../src/graphplot.h \
    ../../src/model_index_iterator.h \
    ../../src/point_table_model.h \
    ../../src/presenter.h \
    ../../src/remove_point_command.h \
    ../../src/remove_route_command.h \
    ../../src/route.h \
    ../../src/route_loader.h \
    ../../src/route_saver.h \
    ../../src/route_table_model.h \
    ../../src/table_index.h \
    ../../src/visitor.h \
    ../../src/visitor_manager.h \
    ../data_struct.h \
    ../route_factory.h \
    ../testview.h
