#include "ES32RHI/OpenGLObjects/RenderTarget/ES32TextureRenderTarget.h"
#include "ES32RHI/OpenGLObjects/Texture/OpenGLTexture.h"

ES32TextureRenderTarget::ES32TextureRenderTarget(std::vector<OpenGLTexture *> ColorAttachments, std::vector<OpenGLTexture *> DepthAttachments)
{
    for (std::uint32_t Index = 0; Index < ColorAttachments.size(); ++Index)
    {

    }
}

ES32TextureRenderTarget::~ES32TextureRenderTarget()
{

}
