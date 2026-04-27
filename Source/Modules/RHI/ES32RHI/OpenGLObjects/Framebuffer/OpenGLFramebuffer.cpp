#include "OpenGLFramebuffer.h"

/*
    void glBindFramebuffer(GLenum target, GLuint framebuffer);
        target:
          GL_DRAW_FRAMEBUFFER
          GL_READ_FRAMEBUFFER
          GL_FRAMEBUFFER

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
                          GL_TEXTURE_2D, colorAttachments[0], 0);


* */

OpenGLFramebuffer::OpenGLFramebuffer()
{
    glGenFramebuffers(1, &Handle);
}

OpenGLFramebuffer::~OpenGLFramebuffer()
{
    glDeleteFramebuffers(1, &Handle);
}

GLuint OpenGLFramebuffer::GetHandle() const
{
    return Handle;
}








