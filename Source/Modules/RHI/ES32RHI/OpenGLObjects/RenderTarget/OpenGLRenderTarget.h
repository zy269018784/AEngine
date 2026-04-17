#pragma once
#include "RHIObjects/Core/RHICore.h"
#include "RHIObjects/RenderTarget/RHIRenderTarget.h"
class RHIRenderTarget;
class OpenGLRenderTarget : public RHIRenderTarget
{
public:
    OpenGLRenderTarget(RHIPixelFormat InPixelFormat);
};


