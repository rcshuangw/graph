TARGET = online
TEMPLATE = app

CONFIG += qt warn_off thread exceptions
DESTDIR += ../../lib
#QMAKE_LFLAGS += /MANIFESTUAC:"level='requireAdministrator'uiAccess='false'"
QT += gui
QT += widgets
QT += xml

INCLUDEPATH += \
    ../../include \
    ../../include/h5baselib \
    ../../include/h5basehelp \
    ../../include/h5basegui

HEADERS += \
    honlineapi.h \
    #honlineframe.h \
    honlinetreewidget.h \
    honlineframe.h \
    honlinescene.h \
    honlineview.h \
    honlinemgr.h \
    honlinedoc.h

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
