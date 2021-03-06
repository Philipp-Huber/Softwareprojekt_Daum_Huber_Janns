#-------------------------------------------------
#
# Project created by QtCreator 2018-05-21T20:37:14
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = "Proteomics Data Viewer"
TEMPLATE = app


SOURCES += main.cpp\
    barDelegate.cpp\
    star.cpp \
    mzparser.cpp \
    peptideview.cpp \
    proteinview.cpp \
    mzfileloader.cpp \
    qcustomsortfilterproxymodel.cpp \
    markdelegate.cpp \
    multbardelegate.cpp

HEADERS  +=\
    barDelegate.h\
    star.h \
    mzparser.h \
    mzTabFile.h \
    mzfileloader.h \
    qcustomsortfilterproxymodel.h \
    peptideview.h \
    proteinview.h \
    markdelegate.h \
    multbardelegate.h

FORMS    += mainwindow.ui

QMAKE_LFLAGS += -no-pie
