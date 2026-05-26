#pragma once
#include "ES32RHI/OpenGLObjects/RenderTarget/OpenGLSwapChainRenderTarget.h"
class OpenGLDevice;
class OpenGLSurface;
class ES32SwapChainRenderTarget : public OpenGLSwapChainRenderTarget
{
public:
    ES32SwapChainRenderTarget(OpenGLDevice *InDevice, OpenGLSurface* InSurface);
    ~ES32SwapChainRenderTarget();
};
