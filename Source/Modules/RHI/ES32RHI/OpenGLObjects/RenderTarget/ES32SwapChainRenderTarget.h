#pragma once
#include "ES32RHI/OpenGLObjects/RenderTarget/OpenGLSwapChainRenderTarget.h"
class RHIDevice;
class RHISurface;
class ES32SwapChainRenderTarget : public OpenGLSwapChainRenderTarget
{
public:
    ES32SwapChainRenderTarget(RHIDevice *InDevice, RHISurface* InSurface);
    ~ES32SwapChainRenderTarget();
};
