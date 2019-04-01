TEMPLATE = app
LANGUAGE = c++
CONFIG += qt warn_off thread exceptions
TARGET = icon

INCLUDEPATH += \
    ../include \
    ../include/h5iconlib \
    ../include/h5icongui

HEADERS       = \
    hiconmainwindow.h \
    hframe.h \
    hicontreewidget.h \
    #hiconsymbol.h \
    #hicontemplate.h \
    hicondocument.h \
    hiconpreview.h \
    #hiconshowpattern.h \
    hiconcommand.h \
    habout.h \
    hiconeditorframe.h \
    hiconeditorwidget.h \
    hicondocument.h \
    hiconmainwindow.h \
    hiconeditormgr.h \
    hiconeditorop.h \
    hiconeditorscene.h \
    #hiconselectmanager.h \
    hicondrawtoolmanager.h \
    hiconselecttoolmanager.h

SOURCES       = main.cpp \
    hiconmainwindow.cpp \
    hframe.cpp \
    hicontreewidget.cpp \
    #hiconsymbol.cpp \
    #hicontemplate.cpp \
    hicondocument.cpp \
    hiconpreview.cpp \
    #hiconshowpattern.cpp \
    hiconcommand.cpp \
    habout.cpp \
    hiconmainwindowactions.cpp \
    hiconeditorframe.cpp \
    hiconeditorwidget.cpp \
    hicondocument.cpp \
    hiconmainwindow.cpp \
    hiconmainwindowactions.cpp \
    hiconeditormgr.cpp \
    hiconeditorop.cpp \
    hiconeditorscene.cpp \
    #hiconselectmanager.cpp \
    hicondrawtoolmanager.cpp \
    hiconselecttoolmanager.cpp

RESOURCES     = \
    icon.qrc \
    qmres.qrc \
    qss.qrc


FORMS += \
    #UI/propertydlg.ui \
    UI/iconpreview.ui \
    UI/about.ui

LIBS += -L../lib -lH5IconGui -lH5IconHelp -ldatafile
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



