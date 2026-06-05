#include "ES32RHI/OpenGLObjects/RenderTarget/OpenGL33TextureRenderTarget.h"
#include "ES32RHI/OpenGLObjects/FrameBuffer/OpenGL33Framebuffer.h"
#include "ES32RHI/OpenGLObjects/CommandBuffer/OpenGL33CommandBuffer.h"
#include "ES32RHI/OpenGLObjects/Device/OpenGLDevice.h"
#include <iostream>

OpenGL33TextureRenderTarget::OpenGL33TextureRenderTarget(RHIDevice * InDevice, std::uint32_t InWidth, std::uint32_t InHeight)
    : OpenGLTextureRenderTarget(InDevice, InWidth, InHeight)
{

}

OpenGL33TextureRenderTarget::~OpenGL33TextureRenderTarget()
{

}

void OpenGL33TextureRenderTarget::CreateFramebuffer()
{
    Framebuffer = new OpenGL33Framebuffer(dynamic_cast<OpenGLDevice *>(Device), Width, Height, ColorAttachments, DepthStencilAttachments);
}

void OpenGL33TextureRenderTarget::CreateRenderPass()
{

}

void OpenGL33TextureRenderTarget::CreateCommandbuffer()
{
    GraphicsCommandBuffers.resize(1);
    GraphicsCommandBuffers[0] = new OpenGL33CommandBuffer();
}
