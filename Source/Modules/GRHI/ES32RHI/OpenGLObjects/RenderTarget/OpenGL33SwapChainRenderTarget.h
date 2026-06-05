#pragma once
#include "ES32RHI/OpenGLObjects/RenderTarget/OpenGLSwapChainRenderTarget.h"
class RHIDevice;
class RHISurface;
class OpenGL33SwapChainRenderTarget : public OpenGLSwapChainRenderTarget
{
public:
    OpenGL33SwapChainRenderTarget(RHIDevice *InDevice, RHISurface* InSurface);
    ~OpenGL33SwapChainRenderTarget();
public:
    virtual void CreateFramebuffer() override final;
    virtual void CreateRenderPass()  override final;
    virtual void CreateCommandbuffer() override final;
};
