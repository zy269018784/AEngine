#pragma once

#if defined(_WIN32) || defined(_WIN64)
    #define RHIEXPORT __declspec(dllexport)
    #define RHIIMPORT __declspec(dllimport)
#elif defined(__linux__)
    #define RHIEXPORT __attribute__((visibility("default")))
    #define RHIIMPORT
#endif