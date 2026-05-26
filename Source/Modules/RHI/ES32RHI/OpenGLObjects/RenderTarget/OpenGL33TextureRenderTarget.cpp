#include "ES32RHI/OpenGLObjects/RenderTarget/OpenGL33TextureRenderTarget.h"
#include "ES32RHI/OpenGLObjects/Texture/OpenGLTexture.h"

OpenGL33TextureRenderTarget::OpenGL33TextureRenderTarget(std::vector<OpenGLTexture *> ColorAttachments, std::vector<OpenGLTexture *> DepthAttachments)
{
    for (std::uint32_t Index = 0; Index < ColorAttachments.size(); ++Index)
    {

    }
}

OpenGL33TextureRenderTarget::~OpenGL33TextureRenderTarget()
{

}
