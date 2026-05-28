#include "ES32RHI/OpenGLObjects/RenderTarget/OpenGL46TextureRenderTarget.h"
#include "ES32RHI/OpenGLObjects/Framebuffer/OpenGL46Framebuffer.h"
#include "ES32RHI/OpenGLObjects/Texture/OpenGLTexture.h"
#include <iostream>

#include "ES32RHI/OpenGLObjects/Device/OpenGLDevice.h"

OpenGL46TextureRenderTarget::OpenGL46TextureRenderTarget(RHIDevice * InDevice, std::uint32_t InWidth, std::uint32_t InHeight)
    : OpenGLTextureRenderTarget(InDevice, InWidth, InHeight)
{

}

OpenGL46TextureRenderTarget::~OpenGL46TextureRenderTarget()
{

}


void OpenGL46TextureRenderTarget::CreateFramebuffer()
{
    OpenGL46Framebuffer *FB = new OpenGL46Framebuffer(dynamic_cast<OpenGLDevice *>(Device), Width, Height, ColorAttachments, DepthStencilAttachments);
    FB->Create();
    Framebuffer = FB;
}

void OpenGL46TextureRenderTarget::CreateRenderPass()
{

}

void OpenGL46TextureRenderTarget::CreateCommandbuffer()
{

}
