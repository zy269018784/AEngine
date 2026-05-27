#pragma once
#include "ES32RHI/OpenGLObjects/RenderTarget/OpenGLSwapChainRenderTarget.h"
class RHIDevice;
class RHISurface;
class ES31SwapChainRenderTarget : public OpenGLSwapChainRenderTarget
{
public:
    ES31SwapChainRenderTarget(RHIDevice *InDevice, RHISurface* InSurface);
    ~ES31SwapChainRenderTarget();
};
