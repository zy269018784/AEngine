#include "OpenGL33Framebuffer.h"
#include "ES32RHI/OpenGLObjects/Framebuffer/OpenGLColorAttachment.h"
#include "ES32RHI/OpenGLObjects/Framebuffer/OpenGLDepthAttachment.h"
/*
    void glBindFramebuffer(GLenum target, GLuint framebuffer);
        target:
          GL_DRAW_FRAMEBUFFER
          GL_READ_FRAMEBUFFER
          GL_FRAMEBUFFER

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
                          GL_TEXTURE_2D, colorAttachments[0], 0);
* */
OpenGL33Framebuffer::OpenGL33Framebuffer()
{
    glGenFramebuffers(1, &Handle);
}

OpenGL33Framebuffer::OpenGL33Framebuffer(std::uint32_t Width, std::uint32_t Height,
                                std::vector<RHIColorAttachment *> &InColorAttachments,
                                std::vector<RHIDepthAttachment *> &InDepthAttachments)
    : OpenGL33Framebuffer()
{
    glBindFramebuffer(GL_FRAMEBUFFER, Handle);

    for (int i = 0; i < InColorAttachments.size(); i++)
    {
        GLenum Target = GL_FRAMEBUFFER;
        GLenum Attachment = GL_COLOR_ATTACHMENT0 + i;
        GLenum Textarget = GL_TEXTURE_2D;
        GLuint Texture;// = dynamic_cast<OpenGLColorAttachment *>(InColorAttachments[i])->GetHandle();
        glFramebufferTexture2D(Target, Attachment, Textarget, Texture, 0);
    }

    for (int i = 0; i < InDepthAttachments.size(); i++)
    {
        GLenum Target = GL_FRAMEBUFFER;
        GLenum Attachment = GL_DEPTH_STENCIL_ATTACHMENT;
        GLenum Textarget = GL_TEXTURE_2D;
        GLuint Texture;// = dynamic_cast<OpenGLDepthAttachment *>(InDepthAttachments[i])->GetHandle();
        switch (InDepthAttachments[i]->GetAttachmentType()) {
            case RHIDepthAttachmentType::DepthStencil_D24_S8:
            case RHIDepthAttachmentType::DepthStencil_D32_S8:
                Attachment = GL_DEPTH_STENCIL_ATTACHMENT;
                break;
            case RHIDepthAttachmentType::DepthOnly_D32:
            case RHIDepthAttachmentType::DepthOnly_D16:
                Attachment = GL_DEPTH_ATTACHMENT;
                break;
            case RHIDepthAttachmentType::Unknown:
                break;
            default:
                break;
        }
        glFramebufferTexture2D(Target, Attachment, Textarget, Texture, 0);
    }
}

OpenGL33Framebuffer::~OpenGL33Framebuffer()
{
    glDeleteFramebuffers(1, &Handle);
}

GLuint OpenGL33Framebuffer::GetHandle() const
{
    return Handle;
}








