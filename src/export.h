#if defined(WIN32) && !(defined(__GNUC__)  || defined(__GCCXML__)) && !defined(_RAKNET_LIB) && defined(_FRAME_DLL)
#define FRAME_DLL_EXPORT __declspec(dllexport)
#else
#define FRAME_DLL_EXPORT  
#endif