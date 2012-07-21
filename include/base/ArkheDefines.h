#ifndef __ARKHE_BASE_DEFINES_H__
#define __ARKHE_BASE_DEFINES_H__

#define WINDOWS

#ifdef EXPORT_DLL && WINDOWS
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT
#endif

#endif //__ARKHE_BASE_DEFINES_H__
