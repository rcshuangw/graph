#-------------------------------------------------
#
# Project created by QtCreator 2017-09-19T09:21:00
#
#-------------------------------------------------

QT += xml
QT += gui
QT += widgets
TARGET = h5basegui
TEMPLATE = lib

DESTDIR += ../../../lib

DEFINES += H5BASEGUI_DLL

INCLUDEPATH += \
           ../../include \
           ../../include/h5baselib \
           ../../include/h5basehelp \
           ../../include/h5basegui

CONFIG += qt warn_off thread exceptions
SOURCES += \
    h5event.cpp \
    h5drawtool.cpp \
    hrecttool.cpp \
    hlinetool.cpp \
    harctool.cpp \
    hpolylinetool.cpp \
    #hdrawtoolmanager.cpp \
    #hselectmanager.cpp \
    hdrawmanager.cpp \
    hselectedmgr.cpp \
    #hselecttool.cpp
    hframe.cpp

HEADERS +=\
    ../../include/hiconapi.h \
    ../../include/h5basegui/h5iconguiexport.h \
    ../../include/h5basegui/h5event.h \
    ../../include/h5basegui/h5drawtool.h \
    ../../include/h5basegui/hrecttool.h \
    ../../include/h5basegui/hlinetool.h \
    ../../include/h5basegui/harctool.h \
    ../../include/h5basegui/hpolylinetool.h \
    #../../include/h5basegui/hdrawtoolmanager.h \
    #../../include/h5basegui/hselectmanager.h \
    ../../include/h5basegui/hdrawmanager.h \
    ../../include/h5basegui/hselectedmgr.h \
    #../../include/h5basegui/hselecttool.h
    ../../include/h5basegui/hframe.h
   
LIBS += -L../../../lib -lh5baselib -lh5basehelp
unix{
    UI_DIR = temp/ui
    MOC_DIR = temp/moc
    OBJECTS_DIR	= temp/obj
    LIBS += \

}

win32{
    UI_DIR = temp/ui
    MOC_DIR = temp/moc
    OBJECTS_DIR	= temp/obj
    LIBS += \
}
