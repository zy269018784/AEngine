#pragma once
#include "ES32RHI/OpenGLObjects/RenderTarget/OpenGLSwapChainRenderTarget.h"
class OpenGLDevice;
class OpenGLSurface;
class ES20SwapChainRenderTarget : public OpenGLSwapChainRenderTarget
{
public:
    ES20SwapChainRenderTarget(OpenGLDevice *InDevice, OpenGLSurface* InSurface);
    ~ES20SwapChainRenderTarget();
};
