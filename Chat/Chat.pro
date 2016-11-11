#-------------------------------------------------
#
# Project created by QtCreator 2016-09-29T20:35:06
#
#-------------------------------------------------

QT       += core gui serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Chat
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    serial_port_reader.cpp \
    serial_port_writer.cpp \
    port_chooser_widget.cpp \
    room.cpp

HEADERS  += mainwindow.h \
    serial_port_reader.h \
    serial_port_writer.h \
    port_chooser_widget.h \
    room.h
