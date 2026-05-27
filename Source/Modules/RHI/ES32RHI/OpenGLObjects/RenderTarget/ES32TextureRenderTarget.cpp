#include "ES32RHI/OpenGLObjects/RenderTarget/ES32TextureRenderTarget.h"
#include "ES32RHI/OpenGLObjects/Framebuffer/ES32Attachment.h"
#include "ES32RHI/OpenGLObjects/Framebuffer/ES32Framebuffer.h"
#include "ES32RHI/OpenGLObjects/Texture/OpenGLTexture.h"
#include <iostream>

#include "ES32RHI/OpenGLObjects/Device/OpenGLDevice.h"

ES32TextureRenderTarget::ES32TextureRenderTarget(RHIDevice * InDevice, std::uint32_t InWidth, std::uint32_t InHeight)
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
        ColorAttachments[Index] = new ES32Attachment(Type, InColorAttachments[Index]);
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
        DepthStencilAttachments[Index] = new ES32Attachment(Type, InDepthAttachments[Index]);
    }
#endif
}

ES32TextureRenderTarget::~ES32TextureRenderTarget()
{

}

void ES32TextureRenderTarget::CreateFramebuffer()
{
    Framebuffer = new ES32Framebuffer(dynamic_cast<OpenGLDevice *>(Device), Width, Height, ColorAttachments, DepthStencilAttachments);
}

void ES32TextureRenderTarget::CreateRenderPass()
{

}

void ES32TextureRenderTarget::CreateCommandbuffer()
{

}