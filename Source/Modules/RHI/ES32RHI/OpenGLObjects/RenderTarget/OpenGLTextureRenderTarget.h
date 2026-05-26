#pragma once
#include "RHI/RHIObjects/RenderTarget/RHITextureRenderTarget.h"
class OpenGLTextureRenderTarget : public RHITextureRenderTarget
{
public:
    OpenGLTextureRenderTarget() = default;
    virtual ~OpenGLTextureRenderTarget();
public:
    virtual void WaitDeviceIdle() override final;
    virtual void RHIBeginRenderPass() override final;
    virtual void RHIEndRenderPass() override final;
    virtual void RHIBeginFrame() override final;
    virtual void RHIEndFrame() override final;
};
