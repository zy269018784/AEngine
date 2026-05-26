#pragma once
#include "ES32RHI/OpenGLObjects/RenderTarget/OpenGLSwapChainRenderTarget.h"
class OpenGLDevice;
class OpenGLSurface;
class OpenGL33SwapChainRenderTarget : public OpenGLSwapChainRenderTarget
{
public:
    OpenGL33SwapChainRenderTarget(OpenGLDevice *InDevice, OpenGLSurface* InSurface);
    ~OpenGL33SwapChainRenderTarget();
};
