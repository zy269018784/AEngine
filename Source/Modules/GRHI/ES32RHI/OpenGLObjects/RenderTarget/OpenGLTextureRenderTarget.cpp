#include "ES32RHI/OpenGLObjects/RenderTarget/OpenGLTextureRenderTarget.h"
#include "ES32RHI/OpenGLObjects/Texture/OpenGLTexture.h"
#include "ES32RHI/OpenGLObjects/FrameBuffer/OpenGLAttachment.h"
#include "RHI/RHIObjects/FrameBuffer/RHIFrameBuffer.h"
#include <iostream>

OpenGLTextureRenderTarget::OpenGLTextureRenderTarget(RHIDevice * InDevice,
                                                     std::uint32_t InWidth,
                                                     std::uint32_t InHeight)
    : RHITextureRenderTarget(InDevice, InWidth, InHeight)
{

}


OpenGLTextureRenderTarget::~OpenGLTextureRenderTarget()
{

}

void OpenGLTextureRenderTarget::Create(std::vector<RHITexture *> InColorTextures,
                                       std::vector<RHITexture *> InDepthTextures)
{
    CreateCommandbuffer();

    if (InColorTextures.size() > 16)
    {
        std::cout << "greater than 16" << std::endl;
    }
    RHIAttachmentType Type;

    ColorAttachments.resize(InColorTextures.size());
    for (std::uint32_t Index = 0; Index < ColorAttachments.size(); ++Index)
    {
        Type = ToRHIAttachmentType(Index);
        ColorAttachments[Index] = new OpenGLAttachment(Type, InColorTextures[Index],
            RHIAttachmentLoadOp::RHI_ATTACHMENT_LOAD_OP_CLEAR, RHIAttachmentStoreOp::RHI_ATTACHMENT_STORE_OP_STORE,
            RHIAttachmentLoadOp::RHI_ATTACHMENT_LOAD_OP_CLEAR, RHIAttachmentStoreOp::RHI_ATTACHMENT_STORE_OP_STORE,
            RHIImageLayout::RHI_IMAGE_LAYOUT_UNDEFINED, RHIImageLayout::RHI_IMAGE_LAYOUT_READ_ONLY_OPTIMAL);
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
        DepthStencilAttachments[Index] = new OpenGLAttachment(Type, InDepthTextures[Index],
            RHIAttachmentLoadOp::RHI_ATTACHMENT_LOAD_OP_CLEAR, RHIAttachmentStoreOp::RHI_ATTACHMENT_STORE_OP_STORE,
            RHIAttachmentLoadOp::RHI_ATTACHMENT_LOAD_OP_CLEAR, RHIAttachmentStoreOp::RHI_ATTACHMENT_STORE_OP_STORE,
            RHIImageLayout::RHI_IMAGE_LAYOUT_UNDEFINED, RHIImageLayout::RHI_IMAGE_LAYOUT_READ_ONLY_OPTIMAL);
    }

    CreateFramebuffer();
}

void OpenGLTextureRenderTarget::RHIBeginRenderPass()
{

}

void OpenGLTextureRenderTarget::RHIEndRenderPass()
{

}

void OpenGLTextureRenderTarget::RHIBeginRenderPass2()
{

}

void OpenGLTextureRenderTarget::RHIEndRenderPass2()
{

}

void OpenGLTextureRenderTarget::RHIBeginFrame()
{
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