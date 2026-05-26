#pragma once
#include "ES32RHI/OpenGLObjects/RenderTarget/OpenGLSwapChainRenderTarget.h"
class OpenGLDevice;
class OpenGLSurface;
class ES21SwapChainRenderTarget : public OpenGLSwapChainRenderTarget
{
public:
    ES21SwapChainRenderTarget(OpenGLDevice *InDevice, OpenGLSurface* InSurface);
    ~ES21SwapChainRenderTarget();
};
