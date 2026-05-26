#pragma once
#include "RHI/RHIObjects/RenderTarget/RHITextureRenderTarget.h"
#include "ES32RHI/OpenGLObjects/RenderTarget/OpenGLTextureRenderTarget.h"

class OpenGLTexture;
class OpenGL46TextureRenderTarget : public OpenGLTextureRenderTarget
{
public:
    OpenGL46TextureRenderTarget() = delete;
    OpenGL46TextureRenderTarget(std::vector<OpenGLTexture *> ColorAttachments, std::vector<OpenGLTexture *> DepthAttachments);
    virtual ~OpenGL46TextureRenderTarget();
};
