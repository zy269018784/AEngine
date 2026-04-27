#include "OpenGLFramebuffer.h"

/*
* void glBindFramebuffer(GLenum target, GLuint framebuffer);
* target:
*   GL_DRAW_FRAMEBUFFER
*   GL_READ_FRAMEBUFFER
*   GL_FRAMEBUFFER
*
*
*
*
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








