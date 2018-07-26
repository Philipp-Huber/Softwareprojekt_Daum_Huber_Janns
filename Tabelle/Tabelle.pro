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
    booleaneditor.cpp\
    barDelegate.cpp\
    star.cpp \
    mzparser.cpp \
    peptideview.cpp \
    proteinview.cpp \
    mzfileloader.cpp \
    qcustomsortfilterproxymodel.cpp \
    markdelegate.cpp

HEADERS  += booleaneditor.h\
    barDelegate.h\
    star.h \
    mzparser.h \
    mzTabFile.h \
    mzfileloader.h \
    qcustomsortfilterproxymodel.h \
    peptideview.h \
    proteinview.h \
    markdelegate.h

FORMS    += mainwindow.ui

QMAKE_LFLAGS += -no-pie
