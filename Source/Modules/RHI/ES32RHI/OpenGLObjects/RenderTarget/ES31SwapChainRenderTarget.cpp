#include "ES31SwapChainRenderTarget.h"
#include "ES32RHI/OpenGLObjects/CommandBuffer/ES31CommandBuffer.h"
#include "ES32RHI/ES32.h"
ES31SwapChainRenderTarget::ES31SwapChainRenderTarget(RHIDevice *InDevice, RHISurface* InSurface)
: OpenGLSwapChainRenderTarget(InDevice, InSurface)
{
    GraphicsCommandBuffers.resize(1);
    GraphicsCommandBuffers[0] = new ES31CommandBuffer();
}

ES31SwapChainRenderTarget::~ES31SwapChainRenderTarget()
{

}

void ES31SwapChainRenderTarget::CreateFramebuffer()
{

}

void ES31SwapChainRenderTarget::CreateRenderPass()
{

}

void ES31SwapChainRenderTarget::CreateCommandbuffer()
{
    GraphicsCommandBuffers.resize(1);
    GraphicsCommandBuffers[0] = new ES31CommandBuffer();
}