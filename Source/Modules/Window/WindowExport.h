#pragma once

#if defined(_WIN32) || defined(_WIN64)
    #define WINDOWEXPORT __declspec(dllexport)
    #define WINDOWIMPORT __declspec(dllimport)
#elif defined(__linux__)
    #define WINDOWEXPORT __attribute__((visibility("default")))
    #define WINDOWIMPORT
#endif