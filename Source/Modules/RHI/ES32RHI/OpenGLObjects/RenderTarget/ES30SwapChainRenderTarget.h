#pragma once
#include "ES32RHI/OpenGLObjects/RenderTarget/OpenGLSwapChainRenderTarget.h"
class OpenGLDevice;
class OpenGLSurface;
class ES30SwapChainRenderTarget : public OpenGLSwapChainRenderTarget
{
public:
    ES30SwapChainRenderTarget(OpenGLDevice *InDevice, OpenGLSurface* InSurface);
    ~ES30SwapChainRenderTarget();
};
