#pragma once
#include "RHI/RHIObjects/RenderTarget/RHITextureRenderTarget.h"
#include "ES32RHI/OpenGLObjects/RenderTarget/ES30TextureRenderTarget.h"

class OpenGLTexture;
class ES30TextureRenderTarget : public RHITextureRenderTarget
{
public:
    ES30TextureRenderTarget() = default;
    ES30TextureRenderTarget(std::vector<OpenGLTexture *> ColorAttachments, std::vector<OpenGLTexture *> DepthAttachments);
    virtual ~ES30TextureRenderTarget();
};
