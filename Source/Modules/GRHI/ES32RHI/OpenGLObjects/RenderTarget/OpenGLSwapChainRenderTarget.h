#pragma once
#include "RHI/RHIObjects/RenderTarget/RHISwapChainRenderTarget.h"
class RHIDevice;
class RHISurface;
class OpenGLSwapChainRenderTarget : public RHISwapChainRenderTarget
{
public:
    OpenGLSwapChainRenderTarget(RHIDevice *InDevice, RHISurface* InSurface);
    ~OpenGLSwapChainRenderTarget();
public:
    virtual void RHIBeginRenderPass() override final;
    virtual void RHIEndRenderPass() override final;
    virtual void RHIBeginRenderPass2() override final;
    virtual void RHIEndRenderPass2() override final;
    virtual void RHIBeginFrame() override final;
    virtual void RHIEndFrame() override final;
    virtual void GetExtent(float &x, float &y, float &w, float &h) override final;
    virtual void Resize(float Width, float Height) final override;
    virtual void WaitDeviceIdle() final override;
};
