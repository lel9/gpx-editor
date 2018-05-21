#-------------------------------------------------
#
# Project created by QtCreator 2018-03-12T23:46:25
#
#-------------------------------------------------

QT       += testlib positioning printsupport

TARGET = tst_remove_route_test
CONFIG   += console
CONFIG   -= app_bundle

CONFIG += C++14

TEMPLATE = app


SOURCES += tst_remove_route_test.cpp \
    ../../src/exceptions.cpp \
    ../../src/route.cpp \
    ../../src/route_table_model.cpp \
    ../../src/converter.cpp \
    ../../src/route_loader.cpp \
    ../../src/route_saver.cpp \
    ../testview.cpp \
    ../../src/presenter.cpp \
    ../../src/graphplot.cpp \
    ../../src/tablewidget.cpp \
    ../../src/add_point_command.cpp \
    ../../src/add_route_command.cpp \
    ../../src/edit_point_command.cpp \
    ../../src/remove_point_command.cpp \
    ../../src/remove_route_command.cpp \
    ../../src/qcustomplot/qcustomplot.cpp \
    ../data_struct.cpp \
    ../../src/command_manager.cpp \
    ../../src/model_index_iterator.cpp \
    ../../src/table_index.cpp \
    ../../src/visitor_manager.cpp \
    ../route_factory.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    ../../src/exceptions.h \
    ../../src/route.h \
    ../../src/route_table_model.h \
    ../../src/converter.h \
    ../../src/route_loader.h \
    ../../src/route_saver.h \
    ../testview.h \
    ../../src/presenter.h \
    ../../src/baseview.h \
    ../../src/graphplot.h \
    ../../src/tablewidget.h \
    ../../src/add_point_command.h \
    ../../src/add_route_command.h \
    ../../src/edit_point_command.h \
    ../../src/remove_point_command.h \
    ../../src/remove_route_command.h \
    ../../src/qcustomplot/qcustomplot.h \
    ../data_struct.h \
    ../../src/command_manager.h \
    ../../src/model_index_iterator.h \
    ../../src/table_index.h \
    ../../src/visitor.h \
    ../../src/visitor_manager.h \
    ../route_factory.h
