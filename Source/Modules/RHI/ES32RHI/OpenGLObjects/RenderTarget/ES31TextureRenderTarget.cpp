#include "ES32RHI/OpenGLObjects/RenderTarget/ES31TextureRenderTarget.h"
#include "ES32RHI/OpenGLObjects/Framebuffer/ES31Attachment.h"
#include "ES32RHI/OpenGLObjects/Framebuffer/ES31Framebuffer.h"
#include "ES32RHI/OpenGLObjects/Texture/OpenGLTexture.h"
#include <iostream>

#include "ES32RHI/OpenGLObjects/Device/OpenGLDevice.h"

ES31TextureRenderTarget::ES31TextureRenderTarget(RHIDevice * InDevice, std::uint32_t InWidth, std::uint32_t InHeight)
    : OpenGLTextureRenderTarget(InDevice, InWidth, InHeight)
{
#if 0
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
        DepthStencilAttachments[Index] = new ES31Attachment(Type, InDepthAttachments[Index]);
    }
#endif
}

ES31TextureRenderTarget::~ES31TextureRenderTarget()
{

}

void ES31TextureRenderTarget::CreateFramebuffer()
{
    Framebuffer = new ES31Framebuffer(dynamic_cast<OpenGLDevice *>(Device), Width, Height, ColorAttachments, DepthStencilAttachments);
}

void ES31TextureRenderTarget::CreateRenderPass()
{

}

void ES31TextureRenderTarget::CreateCommandbuffer()
{

}

RHIAttachment *ES31TextureRenderTarget::CreateAttachment(RHIAttachmentType Type, RHITexture *InTexture)
{
    return new ES31Attachment(Type, InTexture);
}