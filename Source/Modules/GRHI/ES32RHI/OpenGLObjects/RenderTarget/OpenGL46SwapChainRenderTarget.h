#pragma once
#include "ES32RHI/OpenGLObjects/RenderTarget/OpenGLSwapChainRenderTarget.h"
class RHIDevice;
class RHISurface;
class OpenGL46SwapChainRenderTarget : public OpenGLSwapChainRenderTarget
{
public:
    OpenGL46SwapChainRenderTarget(RHIDevice *InDevice, RHISurface* InSurface);
    ~OpenGL46SwapChainRenderTarget();
public:
    virtual void CreateFramebuffer() override final;
    virtual void CreateRenderPass()  override final;
    virtual void CreateCommandbuffer() override final;
};
