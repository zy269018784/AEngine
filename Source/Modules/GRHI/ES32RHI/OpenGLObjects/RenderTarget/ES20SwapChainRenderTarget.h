#pragma once
#include "ES32RHI/OpenGLObjects/RenderTarget/OpenGLSwapChainRenderTarget.h"
class RHIDevice;
class RHISurface;
class ES20SwapChainRenderTarget : public OpenGLSwapChainRenderTarget
{
public:
    ES20SwapChainRenderTarget(RHIDevice *InDevice, RHISurface* InSurface);
    ~ES20SwapChainRenderTarget();
public:
    virtual void CreateFramebuffer() override final;
    virtual void CreateRenderPass()  override final;
    virtual void CreateCommandbuffer() override final;
};
