#pragma once
#include "RHI/RHIObjects/RenderTarget/RHITextureRenderTarget.h"
class OpenGLTexture;
class OpenGLTextureRenderTarget : public RHITextureRenderTarget
{
public:
    OpenGLTextureRenderTarget(RHIDevice * InDevice, std::uint32_t InWidth, std::uint32_t InHeight);
    virtual ~OpenGLTextureRenderTarget();
public:
    virtual void Create(std::vector<RHITexture *> InColorAttachments,
                        std::vector<RHITexture *> InDepthAttachments) override final;
    virtual void RHIBeginRenderPass() override final;
    virtual void RHIEndRenderPass() override final;
    virtual void RHIBeginFrame() override final;
    virtual void RHIEndFrame() override final;
    virtual void GetExtent(float &x, float &y, float &w, float &h) override final;
    virtual void Resize(float Width, float Height) final override;
    virtual void WaitDeviceIdle() final override;
};
