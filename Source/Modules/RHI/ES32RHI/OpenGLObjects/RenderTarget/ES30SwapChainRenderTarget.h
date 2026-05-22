#pragma once
#include "OpenGLRenderTarget.h"
class OpenGLDevice;
class OpenGLSurface;
class ES30SwapChainRenderTarget : public OpenGLRenderTarget
{
public:
    ES30SwapChainRenderTarget(OpenGLDevice *InDevice, OpenGLSurface* InSurface);
    ~ES30SwapChainRenderTarget();
    virtual void RHIBeginRenderPass() override final;
    virtual void RHIEndRenderPass() override final;
    virtual void RHIBeginFrame() override final;
    virtual void RHIEndFrame() override final;
    virtual void GetExtent(float &x, float &y, float &w, float &h) override final;
    virtual void Resize(float Width, float Height) final override;
};
