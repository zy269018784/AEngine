#include "OpenGL33SwapChainRenderTarget.h"
#include "ES32RHI/OpenGLObjects/CommandBuffer/OpenGL33CommandBuffer.h"
#include "ES32RHI/ES32.h"
OpenGL33SwapChainRenderTarget::OpenGL33SwapChainRenderTarget(RHIDevice *InDevice, RHISurface* InSurface)
: OpenGLSwapChainRenderTarget(InDevice, InSurface)
{
    GraphicsCommandBuffers.resize(1);
    GraphicsCommandBuffers[0] = new OpenGL33CommandBuffer();
}

OpenGL33SwapChainRenderTarget::~OpenGL33SwapChainRenderTarget()
{

}

void OpenGL33SwapChainRenderTarget::CreateFramebuffer()
{

}

void OpenGL33SwapChainRenderTarget::CreateRenderPass()
{

}

void OpenGL33SwapChainRenderTarget::CreateCommandbuffer()
{
    GraphicsCommandBuffers.resize(1);
    GraphicsCommandBuffers[0] = new OpenGL33CommandBuffer();
}