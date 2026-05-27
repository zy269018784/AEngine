#pragma once
#include "ES32RHI/OpenGLObjects/RenderTarget/OpenGLTextureRenderTarget.h"

class OpenGLTexture;
class ES32TextureRenderTarget : public OpenGLTextureRenderTarget
{
public:
    ES32TextureRenderTarget() = default;
    ES32TextureRenderTarget(RHIDevice * InDevice, std::uint32_t InWidth, std::uint32_t InHeight);
    virtual ~ES32TextureRenderTarget();
    virtual void CreateFramebuffer() override final;
    virtual void CreateRenderPass()  override final;
    virtual void CreateCommandbuffer() override final;
};
