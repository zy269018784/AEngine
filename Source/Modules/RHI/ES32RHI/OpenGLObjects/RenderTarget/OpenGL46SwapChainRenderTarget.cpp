#include "OpenGL46SwapChainRenderTarget.h"
#include "ES32RHI/OpenGLObjects/CommandBuffer/OpenGL46CommandBuffer.h"
#include "ES32RHI/ES32.h"
OpenGL46SwapChainRenderTarget::OpenGL46SwapChainRenderTarget(RHIDevice *InDevice, RHISurface* InSurface)
    : OpenGLSwapChainRenderTarget(InDevice, InSurface)
{

}

OpenGL46SwapChainRenderTarget::~OpenGL46SwapChainRenderTarget()
{
    delete GraphicsCommandBuffers[0];
}

void OpenGL46SwapChainRenderTarget::CreateFramebuffer()
{

}

void OpenGL46SwapChainRenderTarget::CreateRenderPass()
{

}

void OpenGL46SwapChainRenderTarget::CreateCommandbuffer()
{
    GraphicsCommandBuffers.resize(1);
    GraphicsCommandBuffers[0] = new OpenGL46CommandBuffer();
}