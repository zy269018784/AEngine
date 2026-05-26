#pragma once
#include "RHI/RHIObjects/RenderTarget/RHITextureRenderTarget.h"
#include "ES32RHI/OpenGLObjects/RenderTarget/ES20TextureRenderTarget.h"

class OpenGLTexture;
class ES20TextureRenderTarget : public RHITextureRenderTarget
{
public:
    ES20TextureRenderTarget() = default;
    ES20TextureRenderTarget(std::vector<OpenGLTexture *> ColorAttachments, std::vector<OpenGLTexture *> DepthAttachments);
    virtual ~ES20TextureRenderTarget();
};
