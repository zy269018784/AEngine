#pragma once
#ifdef PROJECT_USE_FTLK
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#endif

class FLTKWindow {
public:
    FLTKWindow();
    ~FLTKWindow();
private:
#ifdef PROJECT_USE_FTLK
    Fl_Window *Handle;
#endif
};


