#include "RHIRenderTarget.h"
#include "RHI/RHIObjects/RenderPass/RHIRenderPass.h"
RHIRenderTarget::RHIRenderTarget(RHIPixelFormat InPixelFormat)
    : PixelFormat(InPixelFormat)
{

}

RHIRenderTarget::~RHIRenderTarget() {
    delete RenderPass;
}

RHIRenderPass *RHIRenderTarget::GetRenderPass() const
{
    return RenderPass;
}

RHICommandBuffer* RHIRenderTarget::CurrentGraphicsCommandBuffer() const
{
    return GraphicsCommandBuffers[CurrentImageIndex];
}