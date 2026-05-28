#include "ES32RHI/OpenGLObjects/RenderTarget/ES30TextureRenderTarget.h"

#include "ES32RHI/OpenGLObjects/Framebuffer/ES30Framebuffer.h"
#include "ES32RHI/OpenGLObjects/Texture/OpenGLTexture.h"
#include <iostream>

#include "ES32RHI/OpenGLObjects/Device/OpenGLDevice.h"

ES30TextureRenderTarget::ES30TextureRenderTarget(RHIDevice * InDevice, std::uint32_t InWidth, std::uint32_t InHeight)
    : OpenGLTextureRenderTarget(InDevice, InWidth, InHeight)
{

}

ES30TextureRenderTarget::~ES30TextureRenderTarget()
{

}

void ES30TextureRenderTarget::CreateFramebuffer()
{
    Framebuffer = new ES30Framebuffer(dynamic_cast<OpenGLDevice *>(Device), Width, Height, ColorAttachments, DepthStencilAttachments);
}

void ES30TextureRenderTarget::CreateRenderPass()
{

}

void ES30TextureRenderTarget::CreateCommandbuffer()
{

}
