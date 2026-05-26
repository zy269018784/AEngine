#pragma once
#include "RHI/RHIObjects/RenderTarget/RHITextureRenderTarget.h"
#include "ES32RHI/OpenGLObjects/RenderTarget/OpenGL33TextureRenderTarget.h"

class OpenGLTexture;
class OpenGL33TextureRenderTarget : public RHITextureRenderTarget
{
public:
    OpenGL33TextureRenderTarget() = default;
    OpenGL33TextureRenderTarget(std::vector<OpenGLTexture *> ColorAttachments, std::vector<OpenGLTexture *> DepthAttachments);
    virtual ~OpenGL33TextureRenderTarget();
};
