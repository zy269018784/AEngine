#pragma once
#include "ES32.h"
class OpenGLFramebuffer
{
public:
    OpenGLFramebuffer();
    ~OpenGLFramebuffer();
    GLuint GetHandle() const;
 private:
    GLuint Handle;
};