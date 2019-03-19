#ifndef H5ICONLIB_EXPORT_H
#define H5ICONLIB_EXPORT_H


#if defined(WIN32)
#if defined(H5ICONLIB_DLL)
    #define H5ICONLIB_EXPORT __declspec(dllexport)
#else
    #define H5ICONLIB_EXPORT __declspec(dllimport)
#endif
#else
    #define H5ICONLIB_EXPORT
#endif
//
#endif 
