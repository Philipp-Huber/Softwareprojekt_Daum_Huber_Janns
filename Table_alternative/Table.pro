#-------------------------------------------------
#
# Project created by QtCreator 2018-06-03T20:53:46
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Table
TEMPLATE = app


SOURCES += main.cpp \
    dialog.cpp \
    checkboxdelegate.cpp \
    tablemodel.cpp

HEADERS  += \
    dialog.h \
    checkboxdelegate.h \
    tablemodel.h

FORMS    += dialog.ui

QMAKE_LFLAGS += -no-pie
