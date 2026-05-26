#pragma once
#include "ES32RHI/OpenGLObjects/RenderTarget/OpenGLSwapChainRenderTarget.h"
class OpenGLDevice;
class OpenGLSurface;
class OpenGL46SwapChainRenderTarget : public OpenGLSwapChainRenderTarget
{
public:
    OpenGL46SwapChainRenderTarget(OpenGLDevice *InDevice, OpenGLSurface* InSurface);
    ~OpenGL46SwapChainRenderTarget();
};
