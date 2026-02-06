#pragma once
#include "RHIObjects/Core/RHICore.h"
class RHIRenderTarget
{
public:
    RHIRenderTarget(RHIPixelFormat InPixelFormat);
    virtual ~RHIRenderTarget() = default;
public:
    virtual void RHIBeginRenderPass() = 0;
    virtual void RHIEndRenderPass() = 0;
    virtual void RHIBeginFrame() = 0;
    virtual void RHIEndFrame() = 0;
protected:
    RHIPixelFormat PixelFormat;
};