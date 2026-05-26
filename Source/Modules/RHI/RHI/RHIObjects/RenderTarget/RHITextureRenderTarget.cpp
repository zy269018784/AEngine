#include "RHITextureRenderTarget.h"
#include "RHI/RHIObjects/RenderPass/RHIRenderPass.h"

RHITextureRenderTarget::RHITextureRenderTarget(RHIPixelFormat InPixelFormat)
    : PixelFormat(InPixelFormat)
{

}

RHITextureRenderTarget::~RHITextureRenderTarget() {
    delete RenderPass;
}

RHIRenderPass *RHITextureRenderTarget::GetRenderPass() const
{
    return RenderPass;
}

RHICommandBuffer* RHITextureRenderTarget::CurrentGraphicsCommandBuffer() const
{
    return GraphicsCommandBuffers[CurrentImageIndex];
}