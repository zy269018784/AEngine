#pragma once
#include "ES32RHI/OpenGLObjects/RenderTarget/OpenGLTextureRenderTarget.h"

class OpenGLTexture;
class ES20TextureRenderTarget : public OpenGLTextureRenderTarget
{
public:
    ES20TextureRenderTarget() = default;
    ES20TextureRenderTarget(RHIDevice * InDevice, std::uint32_t InWidth, std::uint32_t InHeight);
    virtual ~ES20TextureRenderTarget();
    virtual RHIAttachment *CreateAttachment(RHIAttachmentType Type, RHITexture *InTexture) override final;
    virtual void CreateFramebuffer() override final;
    virtual void CreateRenderPass()  override final;
    virtual void CreateCommandbuffer() override final;
};
