#include "ES32SwapChainRenderTarget.h"
#include "ES32RHI/OpenGLObjects/CommandBuffer/ES32CommandBuffer.h"
#include "ES32RHI/ES32.h"
ES32SwapChainRenderTarget::ES32SwapChainRenderTarget(RHIDevice *InDevice, RHISurface* InSurface)
: OpenGLSwapChainRenderTarget(InDevice, InSurface)
{
    GraphicsCommandBuffers.resize(1);
    GraphicsCommandBuffers[0] = new ES32CommandBuffer();
}

ES32SwapChainRenderTarget::~ES32SwapChainRenderTarget()
{

}

void ES32SwapChainRenderTarget::CreateFramebuffer()
{

}

void ES32SwapChainRenderTarget::CreateRenderPass()
{

}

void ES32SwapChainRenderTarget::CreateCommandbuffer()
{
    GraphicsCommandBuffers.resize(1);
    GraphicsCommandBuffers[0] = new ES32CommandBuffer();
}