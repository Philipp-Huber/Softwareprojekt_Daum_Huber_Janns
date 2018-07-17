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
    protein.cpp \
    peptide.cpp \
    star.cpp \
    mzparser.cpp \
    peptideview.cpp \
    proteinview.cpp
    mzfileloader.cpp \
    qcustomsortfilterproxymodel.cpp

HEADERS  += \
    booleaneditor.h\
    barDelegate.h\
    protein.h \
    peptide.h \
    star.h \
    mzparser.h \
    mzTabFile.h \
    mzfileloader.h \
    qcustomsortfilterproxymodel.h
    peptideview.h \
    proteinview.h

FORMS    += mainwindow.ui

QMAKE_LFLAGS += -no-pie
