#-------------------------------------------------
#
# Project created by QtCreator 2018-05-20T22:59:12
#
#-------------------------------------------------

QT       += testlib positioning printsupport
QT       -= gui

CONFIG += C++14

TARGET = tst_addroutetest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += tst_addroutetest.cpp \
    ../../src/presenter.cpp \
    ../../src/route.cpp \
    ../../src/table_index.cpp \
    ../../src/visitor_manager.cpp \
    ../data_struct.cpp \
    ../testview.cpp \
    ../../src/command_manager.cpp \
    ../../src/route_table_model.cpp \
    ../../src/add_point_command.cpp \
    ../../src/add_route_command.cpp \
    ../../src/command.cpp \
    ../../src/edit_point_command.cpp \
    ../../src/remove_point_command.cpp \
    ../../src/remove_route_command.cpp \
    ../../src/qcustomplot/qcustomplot.cpp \
    ../../src/converter.cpp \
    ../../src/exceptions.cpp \
    ../../src/graphplot.cpp \
    ../../src/model_index_iterator.cpp \
    ../../src/point_table_model.cpp \
    ../../src/route_loader.cpp \
    ../../src/route_saver.cpp \
    ../../src/table_point_item_delegate.cpp \
    ../../src/tablewidget.cpp \
    ../route_factory.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    ../../src/baseview.h \
    ../../src/presenter.h \
    ../../src/route.h \
    ../../src/table_index.h \
    ../../src/visitor.h \
    ../../src/visitor_manager.h \
    ../data_struct.h \
    ../testview.h \
    ../../src/command_manager.h \
    ../../src/route_table_model.h \
    ../../src/add_point_command.h \
    ../../src/add_route_command.h \
    ../../src/command.h \
    ../../src/edit_point_command.h \
    ../../src/remove_point_command.h \
    ../../src/remove_route_command.h \
    ../../src/qcustomplot/qcustomplot.h \
    ../../src/converter.h \
    ../../src/enum_insert_point.h \
    ../../src/exceptions.h \
    ../../src/graphplot.h \
    ../../src/model_index_iterator.h \
    ../../src/point_table_model.h \
    ../../src/route_loader.h \
    ../../src/route_saver.h \
    ../../src/table_point_item_delegate.h \
    ../../src/tablewidget.h \
    ../route_factory.h
