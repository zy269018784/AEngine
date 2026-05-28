#include "ES32RHI/OpenGLObjects/RenderTarget/ES20TextureRenderTarget.h"
#include "ES32RHI/OpenGLObjects/Framebuffer/ES20Framebuffer.h"
#include "ES32RHI/OpenGLObjects/Texture/OpenGLTexture.h"
#include <iostream>

#include "ES32RHI/OpenGLObjects/Device/OpenGLDevice.h"

ES20TextureRenderTarget::ES20TextureRenderTarget(RHIDevice * InDevice, std::uint32_t InWidth, std::uint32_t InHeight)
    : OpenGLTextureRenderTarget(InDevice, InWidth, InHeight)
{

}

ES20TextureRenderTarget::~ES20TextureRenderTarget()
{

}

void ES20TextureRenderTarget::CreateFramebuffer()
{
    Framebuffer = new ES20Framebuffer(dynamic_cast<OpenGLDevice *>(Device), Width, Height, ColorAttachments, DepthStencilAttachments);
}

void ES20TextureRenderTarget::CreateRenderPass()
{

}

void ES20TextureRenderTarget::CreateCommandbuffer()
{

}
