#include "ES32RHI/OpenGLObjects/RenderTarget/OpenGLTextureRenderTarget.h"
#include "ES32RHI/OpenGLObjects/Texture/OpenGLTexture.h"

OpenGLTextureRenderTarget::OpenGLTextureRenderTarget(OpenGLTexture *InTexture) : RHITextureRenderTarget(RHIPixelFormat::PF_Unknown) {
}

OpenGLTextureRenderTarget::~OpenGLTextureRenderTarget()
{

}
