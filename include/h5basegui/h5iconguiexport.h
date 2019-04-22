#ifndef H5ICONGUI_EXPORT_H
#define H5ICONGUI_EXPORT_H


#if defined(WIN32)
#if defined(H5BASEGUI_DLL)
    #define H5BASEGUI_EXPORT __declspec(dllexport)
#else
    #define H5BASEGUI_EXPORT __declspec(dllimport)
#endif
#else
    #define H5BASEGUI_EXPORT
#endif
//
#endif 
