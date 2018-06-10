#-------------------------------------------------
#
# Project created by QtCreator 2018-05-21T20:37:14
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Tabelle
TEMPLATE = app


SOURCES += main.cpp\
    booleaneditor.cpp

HEADERS  += \
    booleaneditor.h

FORMS    += mainwindow.ui

QMAKE_LFLAGS += -no-pie
