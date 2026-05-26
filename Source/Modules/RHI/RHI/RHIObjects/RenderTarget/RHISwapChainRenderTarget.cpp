#include "RHISwapChainRenderTarget.h"
#include "RHI/RHIObjects/RenderPass/RHIRenderPass.h"
RHISwapChainRenderTarget::RHISwapChainRenderTarget(RHIPixelFormat InPixelFormat)
    : PixelFormat(InPixelFormat)
{

}

RHISwapChainRenderTarget::~RHISwapChainRenderTarget() {
  delete RenderPass;
}

RHIRenderPass *RHISwapChainRenderTarget::GetRenderPass() const
{
  return RenderPass;
}

RHICommandBuffer* RHISwapChainRenderTarget::CurrentGraphicsCommandBuffer() const
{
  return GraphicsCommandBuffers[CurrentImageIndex];
}