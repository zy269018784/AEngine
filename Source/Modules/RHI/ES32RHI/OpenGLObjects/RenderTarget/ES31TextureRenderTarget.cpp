#include "ES3RHI/OpenGLObjects/RenderTarget/ES31TextureRenderTarget.h"
#include "ES32RHI/OpenGLObjects/Framebuffer/ES31Attachment.h"
#include <iostream>

ES31TextureRenderTarget::ES31TextureRenderTarget(std::vector<OpenGLTexture *> InColorAttachments, std::vector<OpenGLTexture *> InDepthAttachments)
    : OpenGLTextureRenderTarget()
{
    if (InColorAttachments.size() > 16)
    {
        std::cout << "greater than 16" << std::endl;
    }
    RHIAttachmentType Type;

    ColorAttachments.resize(InColorAttachments.size());
    for (std::uint32_t Index = 0; Index < ColorAttachments.size(); ++Index)
    {
        Type = RHIAttachmentType::Color1 + Index;
        ColorAttachments[Index] = new ES31Attachment(Type, InColorAttachments[Index]);
    }

    DepthStencilAttachments.resize(InDepthAttachments.size());
    for (std::uint32_t Index = 0; Index < DepthStencilAttachments.size(); ++Index)
    {
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
            default:
                Type = RHIAttachmentType::DepthStencil_D32_S8;
                break;
        }
        DepthStencilAttachments[Index] = new ES31Attachment(Type, InColorAttachments[Index]);
    }
}

ES31TextureRenderTarget::~ES31TextureRenderTarget()
{

}
