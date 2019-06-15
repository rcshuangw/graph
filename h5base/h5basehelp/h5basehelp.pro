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
DESTDIR = ../../../lib

DEFINES += H5BASEHELP_DLL

INCLUDEPATH += \
    ../include \
    ../../include \
    ../../include/h5basehelp \
    ../../include/h5baselib \
    ../../include/h5basegui
	
CONFIG += qt thread all
SOURCES += \
    hdrawhelper.cpp \
    hanaloguepage.cpp \
    #hdatapropertydlg.cpp \
    hdigitalpage.cpp \
    hfonthelper.cpp \
    hgraphhelper.cpp \
    hgraphpage.cpp \
    hiconhelper.cpp \
    hiconproperty.cpp \
    hrelaypage.cpp \
    hstation.cpp
       

HEADERS +=\
    ../../include/h5basehelp/hdrawhelper.h \
    ../../include/h5basehelp/h5basehelpexport.h \
    ../../include/h5basehelp/hanaloguepage.h \
    #../../include/h5basehelp/hdatapropertydlg.h \
    ../../include/h5basehelp/hdigitalpage.h \
    ../../include/h5basehelp/hfonthelper.h \
    ../../include/h5basehelp/hgraphhelper.h \
    ../../include/h5basehelp/hgraphpage.h \
    ../../include/h5basehelp/hiconhelper.h \
    ../../include/h5basehelp/hiconproperty.h \
    ../../include/h5basehelp/hrelaypage.h \
    ../../include/h5basehelp/hstation.h
        
		  


LIBS += -L../../../lib -lh5baselib -ldatafile
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

SUBDIRS += \
    H5IconHelp.pro

RESOURCES += \
    images.qrc

FORMS += \
    UI/analoguepage.ui \
    UI/digitalpage.ui \
    UI/graphpage.ui \
    UI/iconproperty.ui \
    #UI/propertydlg.ui \
    UI/relaypage.ui

