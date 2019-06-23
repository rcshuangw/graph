TARGET = online
TEMPLATE = app

QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += qt warn_off thread exceptions
DESTDIR += ../../lib
#QMAKE_LFLAGS += /MANIFESTUAC:"level='requireAdministrator'uiAccess='false'"


INCLUDEPATH += \
          ../include \
    ../../include \
    ../../include/h5baselib \
    ../../include/h5basehelp \
    ../../include/h5basegui

HEADERS += \
    #honlineframe.h \
    ../include/honlineframe.h \
    ../include/honlinemgr.h \
    ../include/honlinedoc.h \
    honlinetreewidget.h \
    honlinescene.h \
    honlineview.h

SOURCES += \
    #honlineframe.cpp \
    honlinetreewidget.cpp \
    honlineframe.cpp \
    honlinescene.cpp \
    honlineview.cpp \
    honlinemgr.cpp \
    honlinedoc.cpp

FORMS += \
    onlineframe.ui
