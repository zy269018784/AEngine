#pragma once
#if 0
#if defined(_WIN32) || defined(_WIN64)
    #define WINDOWEXPORT __declspec(dllexport)
    #define WINDOWIMPORT __declspec(dllimport)
#elif defined(__linux__)
    #define WINDOWEXPORT __attribute__((visibility("default")))
    #define WINDOWIMPORT
#endif
#endif

#if OS_IS_WINDOWS
    #define WINDOWEXPORT __declspec(dllexport)
    #define WINDOWIMPORT __declspec(dllimport)
#elif OS_IS_LINUX
    #define WINDOWEXPORT __attribute__((visibility("default")))
    #define WINDOWIMPORT
#endif