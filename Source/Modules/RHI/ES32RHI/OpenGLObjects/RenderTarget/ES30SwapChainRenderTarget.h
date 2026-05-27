#pragma once
#include "ES32RHI/OpenGLObjects/RenderTarget/OpenGLSwapChainRenderTarget.h"
class RHIDevice;
class RHISurface;
class ES30SwapChainRenderTarget : public OpenGLSwapChainRenderTarget
{
public:
    ES30SwapChainRenderTarget(RHIDevice *InDevice, RHISurface* InSurface);
    ~ES30SwapChainRenderTarget();
};
