#pragma once

#if defined(_WIN32) || defined(_WIN64)
    #define GEXPORT __declspec(dllexport)
    #define GIMPORT __declspec(dllimport)
#elif defined(__linux__)
    #define GEXPORT __attribute__((visibility("default")))
    #define GIMPORT
#endif

