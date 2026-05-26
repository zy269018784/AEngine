#include "RHITextureRenderTarget.h"

RHITextureRenderTarget::RHITextureRenderTarget()
{

}

RHITextureRenderTarget::~RHITextureRenderTarget() {
    for (std::uint32_t Index = 0; Index < ColorAttachments.size(); ++Index)
    {
        delete ColorAttachments[Index];
    }
    for (std::uint32_t Index = 0; Index < DepthStencilAttachments.size(); ++Index)
    {
        delete DepthStencilAttachments[Index];
    }
}