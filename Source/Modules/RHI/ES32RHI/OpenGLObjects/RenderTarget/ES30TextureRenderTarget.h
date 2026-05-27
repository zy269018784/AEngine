#pragma once
#include "ES32RHI/OpenGLObjects/RenderTarget/OpenGLTextureRenderTarget.h"


class OpenGLTexture;
class ES30TextureRenderTarget : public OpenGLTextureRenderTarget
{
public:
    ES30TextureRenderTarget() = default;
    ES30TextureRenderTarget(RHIDevice * InDevice, std::uint32_t InWidth, std::uint32_t InHeight);
    virtual ~ES30TextureRenderTarget();
    virtual RHIAttachment *CreateAttachment(RHIAttachmentType Type, RHITexture *InTexture) override final;
    virtual void CreateFramebuffer() override final;
    virtual void CreateRenderPass()  override final;
    virtual void CreateCommandbuffer() override final;
};
