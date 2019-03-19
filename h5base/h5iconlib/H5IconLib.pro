#-------------------------------------------------
#
# Project created by QtCreator 2017-09-19T09:21:00
#
#-------------------------------------------------

QT += xml
QT += gui
QT += widgets
TARGET = H5IconLib
TEMPLATE = lib

DESTDIR += ../lib

DEFINES += H5ICONLIB_DLL

INCLUDEPATH += \
               ../../include \
               ../../include/h5iconlib

CONFIG += qt warn_off thread exceptions
SOURCES += \
      h5graphicsitem.cpp \
      hbaseobj.cpp

HEADERS +=\
    ../../include/hiconapi.h \
    ../../include/h5iconlib/h5iconlibexport.h \
    ../../include/h5iconlib/h5graphicsitem.h \
    ../../include/h5iconlib/hbaseobj.h

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
