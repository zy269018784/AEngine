#pragma once
#include "ES32RHI/OpenGLObjects/RenderTarget/OpenGLSwapChainRenderTarget.h"
class RHIDevice;
class RHISurface;
class ES31SwapChainRenderTarget : public OpenGLSwapChainRenderTarget
{
public:
    ES31SwapChainRenderTarget(RHIDevice *InDevice, RHISurface* InSurface);
    ~ES31SwapChainRenderTarget();
public:
    virtual void CreateFramebuffer() override final;
    virtual void CreateRenderPass()  override final;
    virtual void CreateCommandbuffer() override final;
};
