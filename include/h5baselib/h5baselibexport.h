#ifndef H5BASELIB_EXPORT_H
#define H5BASELIB_EXPORT_H


#if defined(WIN32)
#if defined(H5BASELIB_DLL)
    #define H5BASELIB_EXPORT __declspec(dllexport)
#else
    #define H5BASELIB_EXPORT __declspec(dllimport)
#endif
#else
    #define H5ICONLIB_EXPORT
#endif
//
#endif 
