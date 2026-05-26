#pragma once
#include "RHI/RHIObjects/RenderTarget/RHISwapChainRenderTarget.h"
class OpenGLDevice;
class OpenGLSurface;
class OpenGLSwapChainRenderTarget : public RHISwapChainRenderTarget
{
public:
    OpenGLSwapChainRenderTarget(OpenGLDevice *InDevice, OpenGLSurface* InSurface);
    ~OpenGLSwapChainRenderTarget();
    virtual void RHIBeginRenderPass() override final;
    virtual void RHIEndRenderPass() override final;
    virtual void RHIBeginFrame() override final;
    virtual void RHIEndFrame() override final;
    virtual void GetExtent(float &x, float &y, float &w, float &h) override final;
    virtual void Resize(float Width, float Height) final override;
    virtual void WaitDeviceIdle() final override;
};
