#include "ES32RHI/OpenGLObjects/RenderTarget/OpenGLTextureRenderTarget.h"
#include "ES32RHI/OpenGLObjects/Texture/OpenGLTexture.h"
#include "RHI/RHIObjects/FrameBuffer/RHIFrameBuffer.h"
#include <iostream>

#include "ES32RHI/OpenGLObjects/CommandBuffer/OpenGL46CommandBuffer.h"

OpenGLTextureRenderTarget::OpenGLTextureRenderTarget(RHIDevice * InDevice,
                                                     std::uint32_t InWidth,
                                                     std::uint32_t InHeight)
    : RHITextureRenderTarget(InDevice, InWidth, InHeight)
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
        ColorAttachments[Index] = new OpenGL46Attachment(Type, InColorAttachments[Index]);
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
        //DepthStencilAttachments[Index] = new OpenGL46Attachment(Type, InDepthAttachments[Index]);

        DepthStencilAttachments[Index] =  CreateAttachment(Type, InDepthAttachments[Index]);
    }
#endif
}


OpenGLTextureRenderTarget::~OpenGLTextureRenderTarget()
{

}

void OpenGLTextureRenderTarget::Create(std::vector<RHITexture *> InColorTextures,
                                       std::vector<RHITexture *> InDepthTextures){
    GraphicsCommandBuffers.resize(1);
    GraphicsCommandBuffers[0] = new OpenGL46CommandBuffer();

    if (InColorTextures.size() > 16)
    {
        std::cout << "greater than 16" << std::endl;
    }
    RHIAttachmentType Type;

    ColorAttachments.resize(InColorTextures.size());
    for (std::uint32_t Index = 0; Index < ColorAttachments.size(); ++Index)
    {
        switch ((Index + 1)) {
            case 1:
                Type = RHIAttachmentType::Color1;
                break;
            case 2:
                Type = RHIAttachmentType::Color2;
                break;
            case 3:
                Type = RHIAttachmentType::Color3;
                break;
            case 4:
                Type = RHIAttachmentType::Color4;
                break;
            case 5:
                Type = RHIAttachmentType::Color5;
                break;
            case 6:
                Type = RHIAttachmentType::Color6;
                break;
            case 7:
                Type = RHIAttachmentType::Color7;
                break;
            case 8:
                Type = RHIAttachmentType::Color8;
                break;
            case 9:
                Type = RHIAttachmentType::Color9;
                break;
            case 10:
                Type = RHIAttachmentType::Color10;
                break;
            case 11:
                Type = RHIAttachmentType::Color11;
                break;
            case 12:
                Type = RHIAttachmentType::Color12;
                break;
            case 13:
                Type = RHIAttachmentType::Color13;
                break;
            case 14:
                Type = RHIAttachmentType::Color14;
                break;
            case 15:
                Type = RHIAttachmentType::Color15;
                break;
            case 16:
                Type = RHIAttachmentType::Color16;
                break;
        }
        std::cout << "Create Color " << (int)Type << " " << Index << std::endl;
        ColorAttachments[Index] =  CreateAttachment(Type, InColorTextures[Index]);
    }

    DepthStencilAttachments.resize(InDepthTextures.size());
    for (std::uint32_t Index = 0; Index < DepthStencilAttachments.size(); ++Index)
    {
        switch (InDepthTextures[Index]->GetFormat())
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
        //DepthStencilAttachments[Index] = new OpenGL46Attachment(Type, InDepthAttachments[Index]);

        DepthStencilAttachments[Index] =  CreateAttachment(Type, InDepthTextures[Index]);
    }

    CreateFramebuffer();
}

void OpenGLTextureRenderTarget::RHIBeginRenderPass()
{

}

void OpenGLTextureRenderTarget::RHIEndRenderPass()
{

}

void OpenGLTextureRenderTarget::RHIBeginFrame()
{
    //std::cout << "OpenGLTextureRenderTarget Framebuffer->Bind " << std::endl;
    Framebuffer->Bind();
}

void OpenGLTextureRenderTarget::RHIEndFrame()
{

}

void OpenGLTextureRenderTarget::GetExtent(float &x, float &y, float &w, float &h)
{
    GLint Viewport[4];
    glGetIntegerv(GL_VIEWPORT, Viewport);
    x = Viewport[0];
    y = Viewport[1];
    w = Viewport[2];
    h = Viewport[3];
}

void OpenGLTextureRenderTarget::Resize(float Width, float Height)
{
    glViewport(0, 0, Width, Height);
}

void OpenGLTextureRenderTarget::WaitDeviceIdle()
{
    glFinish();
}