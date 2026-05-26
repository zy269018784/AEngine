#include "ES32RHI/OpenGLObjects/Framebuffer/OpenGLFramebuffer.h"
#include "ES32RHI/OpenGLObjects/Texture/OpenGLTexture.h"

/*
    void glBindFramebuffer(GLenum target, GLuint framebuffer);
        target:
          GL_DRAW_FRAMEBUFFER
          GL_READ_FRAMEBUFFER
          GL_FRAMEBUFFER

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
                          GL_TEXTURE_2D, colorAttachments[0], 0);
* */
OpenGLFramebuffer::OpenGLFramebuffer(RHIDevice *InDevice,  std::uint32_t InWidth, std::uint32_t InHeight,
                                std::vector<RHIAttachment *> &InColorAttachments,
                                std::vector<RHIAttachment *> &InDepthAttachments)
    :   Device(InDevice),
        Width(InWidth),
        Height(InHeight),
        ColorAttachments(InColorAttachments),
        DepthAttachments(InDepthAttachments)
{
    ColorTextures.resize(ColorAttachments.size());
    DepthTextures.resize(DepthAttachments.size());
}

OpenGLFramebuffer::~OpenGLFramebuffer()
{
    glDeleteFramebuffers(1, &Handle);
}

GLuint OpenGLFramebuffer::GetHandle() const
{
    return Handle;
}

void OpenGLFramebuffer::Create()
{
   /*
     * 创建Framebuffer
     */
    glGenFramebuffers(1, &Handle);

    GLenum Target = GL_FRAMEBUFFER;
    GLenum Textarget = GL_TEXTURE_2D;
    RHIPixelFormat PixelFormat = RHIPixelFormat::PF_Unknown;
    GLenum Attachment;
    GLuint Texture;
    for (int i = 0; i < ColorAttachments.size(); i++)
    {
        PixelFormat = ColorAttachments[i]->GetRHIPixelFormat();

        Attachment = GL_COLOR_ATTACHMENT0 + i;
        /*
         * 创建纹理
         */
        ColorTextures[i] = CreateTexture(Device, PixelFormat,  Width, Height);
        Texture =  ColorTextures[i]->GetHandle();
        /*
         * 关联纹理到Framebuffer
         */
        glFramebufferTexture2D(Target, Attachment, Textarget, Texture, 0);
    }


    for (int i = 0; i < DepthAttachments.size(); i++)
    {
        PixelFormat = RHIPixelFormat::PF_Unknown;
        Attachment = GL_DEPTH_STENCIL_ATTACHMENT;

        switch (DepthAttachments[i]->GetAttachmentType()) {
            case RHIAttachmentType::DepthStencil_D24_S8:
                PixelFormat = RHIPixelFormat::PF_DepthStencil_D24_S8;
            case RHIAttachmentType::DepthStencil_D32_S8:
                PixelFormat = RHIPixelFormat::PF_DepthStencil_D32_S8;
                Attachment = GL_DEPTH_STENCIL_ATTACHMENT;
                break;
            case RHIAttachmentType::DepthOnly_D32:
                PixelFormat = RHIPixelFormat::PF_DepthOnly_D32;
            case RHIAttachmentType::DepthOnly_D16:
                PixelFormat = RHIPixelFormat::PF_DepthOnly_D16;
                Attachment = GL_DEPTH_ATTACHMENT;
                break;
            case RHIAttachmentType::Unknown:
                break;
            default:
                break;
        }
        /*
        * 创建纹理
        */
        DepthTextures[i] = CreateTexture(Device, PixelFormat,  Width, Height);
        Texture = DepthTextures[i]->GetHandle();
        /*
         * 关联纹理到Framebuffer
         */
        glFramebufferTexture2D(Target, Attachment, Textarget, Texture, 0);
    }
}








