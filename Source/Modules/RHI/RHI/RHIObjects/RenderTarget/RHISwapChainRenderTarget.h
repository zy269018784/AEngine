#pragma once
#include "RHI/RHIExport.h"
#include "RHI/RHIObjects/RenderTarget/RHIRenderTarget.h"

class RHIEXPORT RHISwapchainRenderTarget : public RHIRenderTarget
{
public:
    RHISwapchainRenderTarget(RHIPixelFormat InPixelFormat);
};