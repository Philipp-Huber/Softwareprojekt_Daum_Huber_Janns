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
    mymodel.cpp\
    bar.cpp\
    barcreator.cpp\
    barDelegate.cpp\
    bareditor.cpp\

HEADERS  += \
    mymodel.h\
    bar.h\
    barcreator.h\
    barDelegate.h\
    bareditor.h\

FORMS    += mainwindow.ui

QMAKE_LFLAGS += -no-pie
