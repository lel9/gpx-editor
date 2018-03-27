#-------------------------------------------------
#
# Project created by QtCreator 2018-03-12T12:53:32
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets location positioning

CONFIG += C++14

TARGET = src
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    add_point_command.cpp \
    add_route_command.cpp \
    command.cpp \
    converter.cpp \
    edit_point_command.cpp \
    exceptions.cpp \
    point_table_model.cpp \
    remove_point_command.cpp \
    remove_route_command.cpp \
    route.cpp \
    route_loader.cpp \
    route_table_model.cpp \
    table_point_item_delegate.cpp \
    route_saver.cpp

HEADERS  += mainwindow.h \
    add_point_command.h \
    add_route_command.h \
    command.h \
    converter.h \
    edit_point_command.h \
    exceptions.h \
    point_table_model.h \
    remove_point_command.h \
    remove_route_command.h \
    route.h \
    route_loader.h \
    route_table_model.h \
    table_point_item_delegate.h \
    route_saver.h

FORMS    += mainwindow.ui
