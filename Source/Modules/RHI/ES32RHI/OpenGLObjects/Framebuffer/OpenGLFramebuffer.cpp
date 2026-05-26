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

}

OpenGLFramebuffer::~OpenGLFramebuffer()
{
    glDeleteFramebuffers(1, &Handle);
}

GLuint OpenGLFramebuffer::GetHandle() const
{
    return Handle;
}

void OpenGLFramebuffer::Bind() const
{
    glBindFramebuffer(GL_FRAMEBUFFER, Handle);
}

void OpenGLFramebuffer::Create()
{
   /*
     * 创建Framebuffer
     */
    glGenFramebuffers(1, &Handle);

    GLenum Target = GL_FRAMEBUFFER;
    GLenum Textarget = GL_TEXTURE_2D;
    GLenum Attachment;
    GLuint Texture;
    for (int i = 0; i < ColorAttachments.size(); i++)
    {
        Attachment = GL_COLOR_ATTACHMENT0 + i;

        Texture =  dynamic_cast<OpenGLTexture *>(ColorAttachments[i]->GetTexture())->GetHandle();
        /*
         * 关联纹理到Framebuffer
         */
        glFramebufferTexture2D(Target, Attachment, Textarget, Texture, 0);
    }


    for (int i = 0; i < DepthAttachments.size(); i++)
    {
        Attachment = GL_DEPTH_STENCIL_ATTACHMENT;

        switch (DepthAttachments[i]->GetAttachmentType())
        {
            case RHIAttachmentType::DepthStencil_D24_S8:
            case RHIAttachmentType::DepthStencil_D32_S8:
                Attachment = GL_DEPTH_STENCIL_ATTACHMENT;
                break;
            case RHIAttachmentType::DepthOnly_D32:
            case RHIAttachmentType::DepthOnly_D16:
                Attachment = GL_DEPTH_ATTACHMENT;
                break;
            default:
                break;
        }

        Texture =  dynamic_cast<OpenGLTexture *>(DepthAttachments[i]->GetTexture())->GetHandle();
        /*
         * 关联纹理到Framebuffer
         */
        glFramebufferTexture2D(Target, Attachment, Textarget, Texture, 0);
    }
}








