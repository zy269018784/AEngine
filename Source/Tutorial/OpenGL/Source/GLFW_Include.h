#ifndef AENGINE_GLFW_INCLUDE_H
#define AENGINE_GLFW_INCLUDE_H

// glad
#include <glad/glad.h>

#ifndef NOMINMAX
#define NOMINMAX
#endif

//#define WIN32_LEAN_AND_MEAN  // 减少 Windows.h 的包含内容

#include <windows.h>
// glfw
#include <GLFW/glfw3.h>

// glfw native
#if OS_IS_LINUX
    #define GLFW_EXPOSE_NATIVE_X11
#endif

#if OS_IS_WINDOWS
    #define GLFW_EXPOSE_NATIVE_WIN32
#endif
#include <GLFW/glfw3native.h>

// glfw callback
#include "GlfwCallbacks.h"

#endif //AENGINE_GLFW_INCLUDE_H
