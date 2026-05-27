#pragma once
#include "ES32RHI/OpenGLObjects/RenderTarget/OpenGLTextureRenderTarget.h"


class OpenGLTexture;
class ES31TextureRenderTarget : public OpenGLTextureRenderTarget
{
public:
    ES31TextureRenderTarget() = default;
    ES31TextureRenderTarget(RHIDevice * InDevice, std::uint32_t InWidth, std::uint32_t InHeight);
    virtual ~ES31TextureRenderTarget();
    virtual void CreateFramebuffer() override final;
    virtual void CreateRenderPass()  override final;
    virtual void CreateCommandbuffer() override final;
};
