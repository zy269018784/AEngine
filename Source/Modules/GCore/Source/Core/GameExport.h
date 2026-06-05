#pragma once

#if defined(_WIN32) || defined(_WIN64)
    #define GAMEEXPORT __declspec(dllexport)
    #define GAMEIMPORT __declspec(dllimport)
#elif defined(__linux__)
    #define GAMEEXPORT __attribute__((visibility("default")))
    #define GAMEIMPORT
#endif