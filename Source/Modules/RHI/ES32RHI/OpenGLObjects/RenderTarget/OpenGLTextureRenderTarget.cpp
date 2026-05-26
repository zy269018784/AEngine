#include "ES32RHI/OpenGLObjects/RenderTarget/OpenGLTextureRenderTarget.h"
#include "ES32RHI/OpenGLObjects/Texture/OpenGLTexture.h"



OpenGLTextureRenderTarget::~OpenGLTextureRenderTarget()
{

}


void OpenGLTextureRenderTarget::WaitDeviceIdle()
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