#-------------------------------------------------
#
# Project created by QtCreator 2017-09-19T09:21:00
#
#-------------------------------------------------

QT += xml
QT += gui
QT += widgets
TARGET = h5baselib
TEMPLATE = lib

DESTDIR += ../../../lib

DEFINES += H5BASELIB_DLL

INCLUDEPATH += \
               ../../include \
               ../../include/h5baselib

CONFIG += qt warn_off thread exceptions
SOURCES += \
        hbaseobj.cpp \
        hiconsymbol.cpp \
        hicontemplate.cpp \
        hiconshowpattern.cpp \
        hdynamicobj.cpp \
        h5graphicsitem.cpp \
        hrectangle.cpp \
        hiconobj.cpp \
        hshapeobj.cpp \
        hline.cpp \
        hlineobj.cpp \
        htempcontainer.cpp  \
        hcontainerobj.cpp \
        hgroup.cpp \
        hcircle.cpp \
        hellipse.cpp \
        htext.cpp \
        hpolygon.cpp \
        hpolyline.cpp \
        hmakeicon.cpp \
    hgraph.cpp \
    harc.cpp

HEADERS += \
    ../../include/hiconapi.h \
    ../../include/h5baselib/h5baselibexport.h \ 
    ../../include/h5baselib/h5graphicsitem.h \
    ../../include/h5baselib/hbaseobj.h \
    ../../include/h5baselib/hcontainerobj.h \
    ../../include/h5baselib/hdynamicobj.h \
    ../../include/h5baselib/hiconobj.h \
    ../../include/h5baselib/hiconshowpattern.h \
    ../../include/h5baselib/hiconsymbol.h \
    ../../include/h5baselib/hicontemplate.h \
    ../../include/h5baselib/hline.h \
    ../../include/h5baselib/hlineobj.h \
    ../../include/h5baselib/hrectangle.h \
    ../../include/h5baselib/hshapeobj.h \
    ../../include/h5baselib/htempcontainer.h \
    ../../include/h5baselib/hgroup.h \
    ../../include/h5baselib/hcircle.h \
    ../../include/h5baselib/hellipse.h \
    ../../include/h5baselib/htext.h \
    ../../include/h5baselib/hpolygon.h \
    ../../include/h5baselib/hpolyline.h \
    ../../include/h5baselib/hmakeicon.h \
    ../../include/h5baselib/hgraph.h \
    ../../include/h5baselib/harc.h


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
