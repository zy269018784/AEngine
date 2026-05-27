#include "RHIRenderTarget.h"
#include "RHI/RHIObjects/RenderPass/RHIRenderPass.h"
RHIRenderTarget::RHIRenderTarget(RHIDevice * InDevice, std::uint32_t InWidth, std::uint32_t InHeight)
    : Device(InDevice), Width(InWidth), Height(InHeight)
{

}

RHIRenderTarget::~RHIRenderTarget()
{
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