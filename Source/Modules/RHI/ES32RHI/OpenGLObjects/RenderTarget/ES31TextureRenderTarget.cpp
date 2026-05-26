#include "ES32RHI/OpenGLObjects/RenderTarget/ES31TextureRenderTarget.h"
#include "ES32RHI/OpenGLObjects/Texture/OpenGLTexture.h"

ES31TextureRenderTarget::ES31TextureRenderTarget(std::vector<OpenGLTexture *> ColorAttachments, std::vector<OpenGLTexture *> DepthAttachments)
{
    for (std::uint32_t Index = 0; Index < ColorAttachments.size(); ++Index)
    {

    }
}

ES31TextureRenderTarget::~ES31TextureRenderTarget()
{

}
