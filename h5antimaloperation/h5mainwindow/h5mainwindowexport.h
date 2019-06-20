#ifndef H5MAINWINDOWEXPORT_H
#define H5MAINWINDOWEXPORT_H


#if defined(WIN32)
#if defined(H5MAINWINDOW_DLL)
    #define H5MAINWINDOW_EXPORT __declspec(dllexport)
#else
    #define H5MAINWINDOW_EXPORT __declspec(dllimport)
#endif
#else
    #define H5MAINWINDOW_EXPORT
#endif

#endif // H5MAINWINDOWEXPORT_H
