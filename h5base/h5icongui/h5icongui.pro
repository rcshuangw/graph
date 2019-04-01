#-------------------------------------------------
#
# Project created by QtCreator 2017-09-19T09:21:00
#
#-------------------------------------------------

QT += xml
QT += gui
QT += widgets
TARGET = H5IconGui
TEMPLATE = lib

DESTDIR += ../lib

DEFINES += H5ICONGUI_DLL

INCLUDEPATH += \
               ../../include \
               ../../include/h5icongui

CONFIG += qt warn_off thread exceptions
SOURCES += \
    h5event.cpp \
    h5drawtool.cpp \
    hrecttool.cpp \
    hlinetool.cpp \
    harctool.cpp \
    hpolylinetool.cpp \
    hdrawtoolmanager.cpp \
    hselectmanager.cpp

HEADERS +=\
    ../../include/hiconapi.h \
    ../../include/h5icongui/h5iconguiexport.h \
    ../../include/h5icongui/h5event.h \
    ../../include/h5icongui/h5drawtool.h \
    ../../include/h5icongui/hrecttool.h \
    ../../include/h5icongui/hlinetool.h \
    ../../include/h5icongui/harctool.h \
    ../../include/h5icongui/hpolylinetool.h \
    ../../include/h5icongui/hdrawtoolmanager.h \
    ../../include/h5icongui/hselectmanager.h
   

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
