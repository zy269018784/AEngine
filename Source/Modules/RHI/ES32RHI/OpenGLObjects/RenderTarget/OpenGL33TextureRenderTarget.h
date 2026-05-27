#pragma once
#include "ES32RHI/OpenGLObjects/RenderTarget/OpenGLTextureRenderTarget.h"

class OpenGLTexture;
class OpenGL33TextureRenderTarget : public OpenGLTextureRenderTarget
{
public:
    OpenGL33TextureRenderTarget() = default;
    OpenGL33TextureRenderTarget(RHIDevice * InDevice, std::uint32_t InWidth, std::uint32_t InHeight);
    virtual ~OpenGL33TextureRenderTarget();
    virtual RHIAttachment *CreateAttachment(RHIAttachmentType Type, RHITexture *InTexture) override final;
    virtual void CreateFramebuffer() override final;
    virtual void CreateRenderPass()  override final;
    virtual void CreateCommandbuffer() override final;
};
