#include "ES32RHI/OpenGLObjects/RenderTarget/ES31TextureRenderTarget.h"
#include "ES32RHI/OpenGLObjects/FrameBuffer/ES31Framebuffer.h"
#include "ES32RHI/OpenGLObjects/CommandBuffer/ES31CommandBuffer.h"
#include "ES32RHI/OpenGLObjects/Device/OpenGLDevice.h"
#include <iostream>

ES31TextureRenderTarget::ES31TextureRenderTarget(RHIDevice * InDevice, std::uint32_t InWidth, std::uint32_t InHeight)
    : OpenGLTextureRenderTarget(InDevice, InWidth, InHeight)
{

}

ES31TextureRenderTarget::~ES31TextureRenderTarget()
{

}

void ES31TextureRenderTarget::CreateFramebuffer()
{
    Framebuffer = new ES31Framebuffer(dynamic_cast<OpenGLDevice *>(Device), Width, Height, ColorAttachments, DepthStencilAttachments);
}

void ES31TextureRenderTarget::CreateRenderPass()
{

}

void ES31TextureRenderTarget::CreateCommandbuffer()
{
    GraphicsCommandBuffers.resize(1);
    GraphicsCommandBuffers[0] = new ES31CommandBuffer();
}

