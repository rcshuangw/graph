#-------------------------------------------------
#
# Project created by QtCreator 2016-11-23T14:39:15
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Test
TEMPLATE = app
DEFINES += H5MAINWINDOW_DLL

SOURCES += main.cpp\
    hsystool.cpp \
    hclient.cpp \
    hclock.cpp \
    hmainwindow.cpp

HEADERS  += \
    hsystool.h \
    hclient.h \
    hclock.h \
    h5mainwindowexport.h \
    hmainwindow.h

FORMS    += mainwindow.ui

RESOURCES += \
    images.qrc
