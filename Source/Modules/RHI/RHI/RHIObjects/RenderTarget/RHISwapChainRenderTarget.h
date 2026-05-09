#pragma once
#include "RHI/RHIObjects/RenderTarget/RHIRenderTarget.h"

class RHISwapchainRenderTarget : public RHIRenderTarget
{
public:
    RHISwapchainRenderTarget(RHIPixelFormat InPixelFormat);
};