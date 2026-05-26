#pragma once
#include "RHI/RHIExport.h"
#include "RHI/RHIObjects/RenderTarget/RHIRenderTarget.h"
#include "RHI/RHIObjects/FrameBuffer/RHIAttachment.h"
#include "RHI/RHIObjects/FrameBuffer/RHIFrameBuffer.h"
#include <vector>
class RHIEXPORT RHITextureRenderTarget : public RHIRenderTarget
{
public:
    RHITextureRenderTarget();
    virtual ~RHITextureRenderTarget();
public:
    virtual void GetExtent(float &x, float &y, float &w, float &h) = 0;
    virtual void Resize(float Width, float Height) = 0;
    virtual void WaitDeviceIdle() = 0;
    virtual void RHIBeginRenderPass() = 0;
    virtual void RHIEndRenderPass() = 0;
    virtual void RHIBeginFrame() = 0;
    virtual void RHIEndFrame() = 0;
protected:
    std::vector<RHIAttachment *> ColorAttachments;
    std::vector<RHIAttachment *> DepthStencilAttachments;
    RHIFrameBuffer *Framebuffer = nullptr;
};