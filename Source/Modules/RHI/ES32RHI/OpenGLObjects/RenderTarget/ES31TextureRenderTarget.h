#pragma once
#include "RHI/RHIObjects/RenderTarget/RHITextureRenderTarget.h"
#include "ES32RHI/OpenGLObjects/RenderTarget/ES31TextureRenderTarget.h"

class OpenGLTexture;
class ES31TextureRenderTarget : public RHITextureRenderTarget
{
public:
    ES31TextureRenderTarget() = default;
    ES31TextureRenderTarget(std::vector<OpenGLTexture *> ColorAttachments, std::vector<OpenGLTexture *> DepthAttachments);
    virtual ~ES31TextureRenderTarget();
};
