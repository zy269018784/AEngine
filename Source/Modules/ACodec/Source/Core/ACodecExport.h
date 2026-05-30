#pragma once

#if defined(_WIN32) || defined(_WIN64)
    #define ACODECEXPORT __declspec(dllexport)
    #define ACODECIMPORT __declspec(dllimport)
#elif defined(__linux__)
    #define ACODECEXPORT __attribute__((visibility("default")))
    #define ACODECIMPORT
#endif