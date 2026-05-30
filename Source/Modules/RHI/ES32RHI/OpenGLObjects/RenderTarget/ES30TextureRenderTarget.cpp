#include "ES32RHI/OpenGLObjects/RenderTarget/ES30TextureRenderTarget.h"
#include "ES32RHI/OpenGLObjects/FrameBuffer/ES30Framebuffer.h"
#include "ES32RHI/OpenGLObjects/CommandBuffer/ES30CommandBuffer.h"
#include "ES32RHI/OpenGLObjects/Device/OpenGLDevice.h"
#include <iostream>

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
    GraphicsCommandBuffers.resize(1);
    GraphicsCommandBuffers[0] = new ES30CommandBuffer();
}
