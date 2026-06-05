#include "ES20SwapChainRenderTarget.h"
#include "ES32RHI/OpenGLObjects/CommandBuffer/ES20CommandBuffer.h"
#include "ES32RHI/ES32.h"
ES20SwapChainRenderTarget::ES20SwapChainRenderTarget(RHIDevice *InDevice, RHISurface* InSurface)
    : OpenGLSwapChainRenderTarget(InDevice, InSurface)
{
    GraphicsCommandBuffers.resize(1);
    GraphicsCommandBuffers[0] = new ES20CommandBuffer();
}

ES20SwapChainRenderTarget::~ES20SwapChainRenderTarget()
{

}

void ES20SwapChainRenderTarget::CreateFramebuffer()
{

}

void ES20SwapChainRenderTarget::CreateRenderPass()
{

}

void ES20SwapChainRenderTarget::CreateCommandbuffer()
{
    GraphicsCommandBuffers.resize(1);
    GraphicsCommandBuffers[0] = new ES20CommandBuffer();
}