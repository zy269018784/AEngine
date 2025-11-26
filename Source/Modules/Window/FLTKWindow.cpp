#include "FLTKWindow.h"

FLTKWindow::FLTKWindow()
{
#ifdef PROJECT_USE_FTLK
    Handle = new Fl_Window(400, 300, "FLTK Input Example");
    //Handle->end();
#endif
}

FLTKWindow::~FLTKWindow() {
#ifdef PROJECT_USE_FTLK
   delete Handle;
#endif
}









