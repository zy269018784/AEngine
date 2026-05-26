#include "ES32RHI/OpenGLObjects/RenderTarget/OpenGL46TextureRenderTarget.h"

#include <iostream>
#include <ostream>

#include "ES32RHI/OpenGLObjects/Texture/OpenGL46Texture.h"
#include "ES32RHI/OpenGLObjects/Framebuffer/OpenGL46Attachment.h"

OpenGL46TextureRenderTarget::OpenGL46TextureRenderTarget(std::vector<OpenGLTexture *> InColorAttachments, std::vector<OpenGLTexture *> InDepthAttachments)
    : OpenGLTextureRenderTarget()
{
    if (InColorAttachments.size() > 16)
    {
        std::cout << "greater than 16" << std::endl;
    }
    ColorAttachments.resize(InColorAttachments.size());
    for (std::uint32_t Index = 0; Index < ColorAttachments.size(); ++Index)
    {
        ColorAttachments[Index] = new OpenGL46Attachment(RHIAttachmentType::Color1 + Index, InColorAttachments[Index]);
    }

    DepthStencilAttachments.resize(InDepthAttachments.size());
    for (std::uint32_t Index = 0; Index < DepthStencilAttachments.size(); ++Index)
    {
        RHIAttachmentType Type;
        switch (InDepthAttachments[Index]->GetFormat())
        {
            case RHIPixelFormat::PF_DepthOnly_D16:
                Type = RHIAttachmentType::DepthOnly_D16;
                break;
            case RHIPixelFormat::PF_DepthOnly_D32:
                Type = RHIAttachmentType::DepthOnly_D32;
                break;
            case RHIPixelFormat::PF_DepthStencil_D24_S8:
                Type = RHIAttachmentType::DepthStencil_D24_S8;
                break;
            case RHIPixelFormat::PF_DepthStencil_D32_S8:
                Type = RHIAttachmentType::DepthStencil_D32_S8;
                break;
        }
        ColorAttachments[Index] = new OpenGL46Attachment(Type, InColorAttachments[Index]);
    }
}

OpenGL46TextureRenderTarget::~OpenGL46TextureRenderTarget()
{

}
