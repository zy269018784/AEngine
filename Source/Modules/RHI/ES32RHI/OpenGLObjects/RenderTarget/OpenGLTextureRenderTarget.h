#ifndef MODULETEST_OPENGLTEXTURERENDERTARGET_H
#define MODULETEST_OPENGLTEXTURERENDERTARGET_H
#include "ES32RHI/OpenGLObjects/Core/OpenGLCore.h"
#include "ES32RHI/OpenGLObjects/RenderTarget/OpenGLTextureRenderTarget.h"
#include "RHI/RHIObjects/RenderTarget/RHITextureRenderTarget.h"
class OpenGLTexture;
class OpenGLTextureRenderTarget : public RHITextureRenderTarget
{
public:
    OpenGLTextureRenderTarget() = default;
    OpenGLTextureRenderTarget(OpenGLTexture *InTexture);
    virtual ~OpenGLTextureRenderTarget();
};


#endif