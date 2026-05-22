#pragma once
#include "OpenGLRenderTarget.h"
class OpenGLDevice;
class OpenGLSurface;
class OpenGL33SwapChainRenderTarget : public OpenGLRenderTarget
{
public:
    OpenGL33SwapChainRenderTarget(OpenGLDevice *InDevice, OpenGLSurface* InSurface);
    ~OpenGL33SwapChainRenderTarget();
    virtual void RHIBeginRenderPass() override final;
    virtual void RHIEndRenderPass() override final;
    virtual void RHIBeginFrame() override final;
    virtual void RHIEndFrame() override final;
    virtual void GetExtent(float &x, float &y, float &w, float &h) override final;
    virtual void Resize(float Width, float Height) final override;
};
