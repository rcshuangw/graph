#-------------------------------------------------
#
# Project created by QtCreator 2016-11-23T14:39:15
#
#-------------------------------------------------

QT       += core gui
QT += xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Test
TEMPLATE = app
DEFINES += H5MAINWINDOW_DLL

DESTDIR += ../../../lib
INCLUDEPATH += \
    ../../include \
    ../../include/h5baselib \
    ../../include/h5basehelp \
    ../../include/h5basegui

SOURCES += main.cpp\
    hsystool.cpp \
    hclient.cpp \
    hclock.cpp \
    #honlineframe.cpp \
    hantimalopdoc.cpp \
    hantimalopmgr.cpp \
    hgraphframe.cpp \
    hgraphscene.cpp \
    hgrapheview.cpp \
    hmainwindow.cpp \
    hgraphtreewidget.cpp \
    hframe.cpp \
    honlineframe.cpp \
    hbaseframe.cpp

HEADERS  += \
    hsystool.h \
    hclient.h \
    hmainwindow.h \
    h5mainwindowexport.h \
    hclock.h \
    hantimalopdoc.h \
    hgraphframe.h \
    hantimalopmgr.h \
    hgraphscene.h \
    hgraphview.h \
    hgraphtreewidget.h \
    hframe.h \
    honlineframe.h \
    hbaseframe.h

LIBS += -L../../../lib -lh5basehelp -lh5basegui -lh5baselib -ldatafile
FORMS    += mainwindow.ui

RESOURCES += \
    images.qrc
