#include "RHI/RHIObjects/RenderTarget/RHISwapChainRenderTarget.h"

#include <iostream>
#include <ostream>

RHISwapChainRenderTarget::RHISwapChainRenderTarget(RHIDevice *InDevice, std::uint32_t InWidth, std::uint32_t InHeight, RHIPixelFormat InPixelFormat)
    : RHIRenderTarget(InDevice, InWidth, InHeight), PixelFormat(InPixelFormat)
{

}

RHISwapChainRenderTarget::~RHISwapChainRenderTarget() {

}

void RHISwapChainRenderTarget::Create()
{
    CreateRenderPass();
    CreateFramebuffer();
    CreateCommandbuffer();
}