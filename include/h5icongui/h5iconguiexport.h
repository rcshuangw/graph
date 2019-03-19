#ifndef H5ICONGUI_EXPORT_H
#define H5ICONGUI_EXPORT_H


#if defined(WIN32)
#if defined(H5ICONGUI_DLL)
    #define H5ICONGUI_EXPORT __declspec(dllexport)
#else
    #define H5ICONGUI_EXPORT __declspec(dllimport)
#endif
#else
    #define H5ICONGUI_EXPORT
#endif
//
#endif 
