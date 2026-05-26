#include "ES32RHI/OpenGLObjects/RenderTarget/OpenGLTextureRenderTarget.h"
#include "ES32RHI/OpenGLObjects/Texture/OpenGLTexture.h"



OpenGLTextureRenderTarget::~OpenGLTextureRenderTarget()
{

}


void OpenGLTextureRenderTarget::RHIBeginRenderPass()
{

}

void OpenGLTextureRenderTarget::RHIEndRenderPass()
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
