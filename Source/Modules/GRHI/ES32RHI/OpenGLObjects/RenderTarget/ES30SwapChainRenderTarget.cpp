#include "ES30SwapChainRenderTarget.h"
#include "ES32RHI/OpenGLObjects/CommandBuffer/ES30CommandBuffer.h"
#include "ES32RHI/ES32.h"
ES30SwapChainRenderTarget::ES30SwapChainRenderTarget(RHIDevice *InDevice, RHISurface* InSurface)
: OpenGLSwapChainRenderTarget(InDevice, InSurface)
{
    GraphicsCommandBuffers.resize(1);
    GraphicsCommandBuffers[0] = new ES30CommandBuffer();
}

ES30SwapChainRenderTarget::~ES30SwapChainRenderTarget()
{

}

void ES30SwapChainRenderTarget::CreateFramebuffer()
{

}

void ES30SwapChainRenderTarget::CreateRenderPass()
{

}

void ES30SwapChainRenderTarget::CreateCommandbuffer()
{
    GraphicsCommandBuffers.resize(1);
    GraphicsCommandBuffers[0] = new ES30CommandBuffer();
}