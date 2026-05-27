#pragma once
#include "ES32RHI/OpenGLObjects/RenderTarget/OpenGLSwapChainRenderTarget.h"
class RHIDevice;
class RHISurface;
class ES21SwapChainRenderTarget : public OpenGLSwapChainRenderTarget
{
public:
    ES21SwapChainRenderTarget(RHIDevice *InDevice, RHISurface* InSurface);
    ~ES21SwapChainRenderTarget();
};
