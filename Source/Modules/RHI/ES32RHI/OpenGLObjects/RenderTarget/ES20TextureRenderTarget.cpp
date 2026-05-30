#include "ES32RHI/OpenGLObjects/RenderTarget/ES20TextureRenderTarget.h"
#include "ES32RHI/OpenGLObjects/FrameBuffer/ES20Framebuffer.h"
#include "ES32RHI/OpenGLObjects/CommandBuffer/ES20CommandBuffer.h"
#include "ES32RHI/OpenGLObjects/Device/OpenGLDevice.h"
#include <iostream>


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
    GraphicsCommandBuffers.resize(1);
    GraphicsCommandBuffers[0] = new ES20CommandBuffer();
}
