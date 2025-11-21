#include "X11Window.h"
#ifdef OS_IS_LINUX
#include <xcb/xcb.h>
#include <X11/Xlib-xcb.h>
#endif
X11Window::X11Window() {
#ifdef OS_IS_LINUX
     Display *Display = XOpenDisplay("hello x11");

     XCloseDisplay(Display);
#endif
}