#include "ES32RHI/OpenGLObjects/RenderTarget/ES30TextureRenderTarget.h"
#include "ES32RHI/OpenGLObjects/Texture/OpenGLTexture.h"

ES30TextureRenderTarget::ES30TextureRenderTarget(std::vector<OpenGLTexture *> ColorAttachments, std::vector<OpenGLTexture *> DepthAttachments)
{
    for (std::uint32_t Index = 0; Index < ColorAttachments.size(); ++Index)
    {

    }
}

ES30TextureRenderTarget::~ES30TextureRenderTarget()
{

}
