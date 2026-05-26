#pragma once
#include "RHI/RHIObjects/RenderTarget/RHITextureRenderTarget.h"

class OpenGLTextureRenderTarget : public RHITextureRenderTarget
{
public:
    OpenGLTextureRenderTarget() = default;
    virtual ~OpenGLTextureRenderTarget();
};
