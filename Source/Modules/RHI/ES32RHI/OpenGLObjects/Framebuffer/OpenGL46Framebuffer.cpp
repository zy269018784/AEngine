#include "OpenGL46Framebuffer.h"
#include "ES32RHI/OpenGLObjects/Framebuffer/OpenGLColorAttachment.h"
#include "ES32RHI/OpenGLObjects/Framebuffer/OpenGLDepthAttachment.h"
#include "ES32RHI/OpenGLObjects/Texture/OpenGL46Texture.h"
#include "ES32RHI/OpenGLObjects/Device/OpenGLDevice.h"

/*
    void glBindFramebuffer(GLenum target, GLuint framebuffer);
        target:
          GL_DRAW_FRAMEBUFFER
          GL_READ_FRAMEBUFFER
          GL_FRAMEBUFFER

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
                          GL_TEXTURE_2D, colorAttachments[0], 0);
* */


OpenGL46Framebuffer::OpenGL46Framebuffer(OpenGLDevice *InDevice, std::uint32_t Width, std::uint32_t Height,
                                std::vector<RHIColorAttachment *> &InColorAttachments,
                                std::vector<RHIDepthAttachment *> &InDepthAttachments)
    : OpenGLFramebuffer(InDevice, Width, Height, InColorAttachments, InDepthAttachments)
{
    glGenFramebuffers(1, &Handle);
    glBindFramebuffer(GL_FRAMEBUFFER, Handle);

    ColorTextures.resize(InColorAttachments.size());
    for (int i = 0; i < InColorAttachments.size(); i++)
    {
        auto PixelFormat = InColorAttachments[i]->GetRHIPixelFormat();
        GLenum Target = GL_FRAMEBUFFER;
        GLenum Attachment = GL_COLOR_ATTACHMENT0 + i;
        GLenum Textarget = GL_TEXTURE_2D;
        ColorTextures[i] = new OpenGL46Texture(dynamic_cast<RHIDevice *>(InDevice), RHITextureType::Texture2D, PixelFormat, 1, 1, Width, Height, 1, nullptr);
        GLuint Texture =  ColorTextures[i]->GetHandle();
        glFramebufferTexture2D(Target, Attachment, Textarget, Texture, 0);
    }

    DepthTextures.resize(InDepthAttachments.size());
    for (int i = 0; i < InDepthAttachments.size(); i++)
    {
        RHIPixelFormat PixelFormat = RHIPixelFormat::PF_Unknown;
        GLenum Target = GL_FRAMEBUFFER;
        GLenum Attachment = GL_DEPTH_STENCIL_ATTACHMENT;
        GLenum Textarget = GL_TEXTURE_2D;

        switch (InDepthAttachments[i]->GetAttachmentType()) {
            case RHIDepthAttachmentType::DepthStencil_D24_S8:
                PixelFormat = RHIPixelFormat::PF_DepthStencil_D24_S8;
            case RHIDepthAttachmentType::DepthStencil_D32_S8:
                PixelFormat = RHIPixelFormat::PF_DepthStencil_D32_S8;
                Attachment = GL_DEPTH_STENCIL_ATTACHMENT;
                break;
            case RHIDepthAttachmentType::DepthOnly_D32:
                PixelFormat = RHIPixelFormat::PF_DepthOnly_D32;
            case RHIDepthAttachmentType::DepthOnly_D16:
                PixelFormat = RHIPixelFormat::PF_DepthOnly_D16;
                Attachment = GL_DEPTH_ATTACHMENT;
                break;
            case RHIDepthAttachmentType::Unknown:
                break;
            default:
                break;
        }
        DepthTextures[i] = new OpenGL46Texture(dynamic_cast<RHIDevice *>(InDevice), RHITextureType::Texture2D, PixelFormat, 1, 1, Width, Height, 1, nullptr);

        GLuint Texture = DepthTextures[i]->GetHandle();
        glFramebufferTexture2D(Target, Attachment, Textarget, Texture, 0);
    }
}

OpenGL46Framebuffer::~OpenGL46Framebuffer()
{
    glDeleteFramebuffers(1, &Handle);
}






