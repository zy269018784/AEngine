#pragma once
#include "RHI/RHIObjects/RenderTarget/RHITextureRenderTarget.h"
#include "ES32RHI/OpenGLObjects/RenderTarget/ES32TextureRenderTarget.h"

class OpenGLTexture;
class ES32TextureRenderTarget : public RHITextureRenderTarget
{
public:
    ES32TextureRenderTarget() = default;
    ES32TextureRenderTarget(std::vector<OpenGLTexture *> ColorAttachments, std::vector<OpenGLTexture *> DepthAttachments);
    virtual ~ES32TextureRenderTarget();
};
