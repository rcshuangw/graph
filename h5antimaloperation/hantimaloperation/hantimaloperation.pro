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

INCLUDEPATH += \
          ../include
    ../../include \
    ../../include/h5baselib \
    ../../include/h5basehelp \
    ../../include/h5basegui

SOURCES += main.cpp\
    hsystool.cpp \
    hclient.cpp \
    hclock.cpp \
    hmainwindow.cpp

HEADERS  += \
    ../include/hsystool.h \
    ../include/hclient.h \
    ../include/hmainwindow.h \
    h5mainwindowexport.h \
    hclock.h

FORMS    += mainwindow.ui

RESOURCES += \
    images.qrc
