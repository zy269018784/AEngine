#pragma once
#include "RHI/RHIExport.h"
#include "RHI/RHIObjects/RenderTarget/RHIRenderTarget.h"
#include "RHI/RHIObjects/FrameBuffer/RHIAttachment.h"
#include <vector>
class RHIEXPORT RHITextureRenderTarget : public RHIRenderTarget
{
public:
    RHITextureRenderTarget();
    virtual ~RHITextureRenderTarget();
protected:
    std::vector<RHIAttachment *> ColorAttachments;
    std::vector<RHIAttachment *> DepthStencilAttachments;
};