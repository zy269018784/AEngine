#include "RHITextureRenderTarget.h"
#include "RHI/RHIObjects/RenderPass/RHIRenderPass.h"

RHITextureRenderTarget::RHITextureRenderTarget(RHIDevice * InDevice, std::uint32_t InWidth, std::uint32_t InHeight)
    : RHIRenderTarget(InDevice, InWidth, InHeight)
{

}

RHITextureRenderTarget::~RHITextureRenderTarget() {
    delete RenderPass;
}
