#-------------------------------------------------
#
# Project created by QtCreator 2017-09-19T09:21:00
#
#-------------------------------------------------

QT += xml
QT += gui
QT += widgets
TARGET = h5basehelp
TEMPLATE = lib
win32{
    DESTDIR = ../lib
}

unix{
DESTDIR = ../lib
}
DEFINES += H5BASEHELP_DLL

INCLUDEPATH += \
    ../../include \
    ../../include/h5basehelp \
    ../../include/h5baselib \
    ../../include/h5basegui
	
CONFIG += qt thread all
SOURCES += \
    hdrawhelper.cpp
       

HEADERS +=\
    ../../include/h5basehelp/hdrawhelper.h \
    ../../include/h5basehelp/h5basehelpexport.h
        
		  


LIBS += -L../lib
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

