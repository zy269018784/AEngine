#include "ES32RHI/OpenGLObjects/RenderTarget/ES32TextureRenderTarget.h"
#include "ES32RHI/OpenGLObjects/Framebuffer/ES32Framebuffer.h"
#include "ES32RHI/OpenGLObjects/CommandBuffer/ES32CommandBuffer.h"
#include "ES32RHI/OpenGLObjects/Device/OpenGLDevice.h"
#include <iostream>

ES32TextureRenderTarget::ES32TextureRenderTarget(RHIDevice * InDevice, std::uint32_t InWidth, std::uint32_t InHeight)
    : OpenGLTextureRenderTarget(InDevice, InWidth, InHeight)
{

}

ES32TextureRenderTarget::~ES32TextureRenderTarget()
{

}

void ES32TextureRenderTarget::CreateFramebuffer()
{
    Framebuffer = new ES32Framebuffer(dynamic_cast<OpenGLDevice *>(Device), Width, Height, ColorAttachments, DepthStencilAttachments);
}

void ES32TextureRenderTarget::CreateRenderPass()
{

}

void ES32TextureRenderTarget::CreateCommandbuffer()
{
    GraphicsCommandBuffers.resize(1);
    GraphicsCommandBuffers[0] = new ES32CommandBuffer();
}

