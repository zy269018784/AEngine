#pragma once
#include "RHI/RHIExport.h"
#include "RHI/RHIObjects/RenderTarget/RHIRenderTarget.h"

class RHIEXPORT RHITextureRenderTarget : public RHIRenderTarget
{
public:
    RHITextureRenderTarget(RHIPixelFormat InPixelFormat);
};