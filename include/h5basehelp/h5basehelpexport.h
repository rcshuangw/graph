#ifndef H5BASEHELP_EXPORT_H
#define H5BASEHELP_EXPORT_H


#if defined(WIN32)
#if defined(H5BASEHELP_DLL)
    #define H5BASEHELP_EXPORT __declspec(dllexport)
#else
    #define H5BASEHELP_EXPORT __declspec(dllimport)
#endif
#else
    #define H5BASEHELP_EXPORT
#endif
//
#endif 
