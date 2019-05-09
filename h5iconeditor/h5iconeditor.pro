TEMPLATE = app
CONFIG += qt warn_off thread exceptions
TARGET = icon
DESTDIR += ../../lib
INCLUDEPATH += \
           ../include \
           ../include/h5baselib \
           ../include/h5basehelp \
           ../include/h5basegui

HEADERS       = \
    hiconmainwindow.h \
    #hframe.h \
    hicontreewidget.h \
    #hiconsymbol.h \
    #hicontemplate.h \
    #hicondocument.h \
    #hiconpreview.h \
    #hiconshowpattern.h \
    hiconcommand.h \
    #habout.h \
    hiconeditorframe.h \
    hiconeditorwidget.h \
    #hicondocument.h \
    hiconeditormgr.h \
    hiconeditorop.h \
    hiconeditorscene.h \
    #hiconselectmanager.h \
    #hiconselecttoolmanager.h \
    hiconeditordoc.h \
    hiconeditorwidget.h \
    hiconeditorselecttool.h \
    hiconeditordrawtoolmgr.h \
    hicontreewidget.h \
    hiconcommand.h

SOURCES       = main.cpp \
    hiconmainwindow.cpp \
    #hframe.cpp \
    hicontreewidget.cpp \
    #hiconsymbol.cpp \
    #hicontemplate.cpp \
    #hicondocument.cpp \
    #hiconpreview.cpp \
    #hiconshowpattern.cpp \
    hiconcommand.cpp \
    #habout.cpp \
    hiconmainwindowactions.cpp \
    hiconeditorframe.cpp \
    hiconeditorwidget.cpp \
    #hicondocument.cpp \
    hiconeditormgr.cpp \
    hiconeditorop.cpp \
    hiconeditorscene.cpp \
    #hiconselectmanager.cpp \
    #hiconselecttoolmanager.cpp \
    hiconeditordoc.cpp \
    hiconeditorselecttool.cpp \
    hiconeditordrawtoolmgr.cpp

RESOURCES     = \
    icon.qrc \
    qmres.qrc \
    qss.qrc


FORMS += \
    #UI/propertydlg.ui \
    UI/iconpreview.ui \
    UI/about.ui

LIBS += -L../../lib -lh5basehelp -lh5basegui -lh5baselib

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

QT += widgets
QT += xml



