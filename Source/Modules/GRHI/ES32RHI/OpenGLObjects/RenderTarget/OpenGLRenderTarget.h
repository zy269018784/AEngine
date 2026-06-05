#if 0
#pragma once
#include "RHI/RHIObjects/Core/RHICore.h"
#include "RHI/RHIObjects/RenderTarget/RHIRenderTarget.h"
class RHIRenderTarget;
class OpenGLRenderTarget : public RHIRenderTarget
{
public:
    OpenGLRenderTarget(RHIPixelFormat InPixelFormat);
    virtual void WaitDeviceIdle() final override;
};


#endif