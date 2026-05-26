#include "ES32RHI/OpenGLObjects/RenderTarget/ES20TextureRenderTarget.h"
#include "ES32RHI/OpenGLObjects/Texture/OpenGLTexture.h"

ES20TextureRenderTarget::ES20TextureRenderTarget(std::vector<OpenGLTexture *> ColorAttachments, std::vector<OpenGLTexture *> DepthAttachments)
{
    for (std::uint32_t Index = 0; Index < ColorAttachments.size(); ++Index)
    {

    }
}

ES20TextureRenderTarget::~ES20TextureRenderTarget()
{

}
