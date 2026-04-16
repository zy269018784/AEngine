#include "RHIRenderTarget.h"

RHIRenderTarget::RHIRenderTarget(RHIPixelFormat InPixelFormat)
    : PixelFormat(InPixelFormat)
{

}

RHIRenderPass *RHIRenderTarget::GetRenderPass() const
{
    return RenderPass;
}

RHICommandBuffer* RHIRenderTarget::CurrentGraphicsCommandBuffer() const
{
    return GraphicsCommandBuffers[CurrentImageIndex];
}