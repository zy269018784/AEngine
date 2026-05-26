#pragma once
#include "RHI/RHIExport.h"
#include "RHI/RHIObjects/Core/RHICore.h"
#include <vector>

class RHIRenderPass;
class RHICommandBuffer;

class RHIEXPORT RHIRenderTarget
{
public:
    RHIRenderTarget() = default;
    RHIRenderTarget(RHIPixelFormat InPixelFormat);
    virtual ~RHIRenderTarget();
    virtual RHIRenderPass *GetRenderPass() const = 0;
    virtual RHICommandBuffer* CurrentGraphicsCommandBuffer() const = 0;
    virtual void GetExtent(float &x, float &y, float &w, float &h) = 0;
    virtual void Resize(float Width, float Height) = 0;
    virtual void WaitDeviceIdle() = 0;
public:
    virtual void RHIBeginRenderPass() = 0;
    virtual void RHIEndRenderPass() = 0;
    virtual void RHIBeginFrame() = 0;
    virtual void RHIEndFrame() = 0;
};