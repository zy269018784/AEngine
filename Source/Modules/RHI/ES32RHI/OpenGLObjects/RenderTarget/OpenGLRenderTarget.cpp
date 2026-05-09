#include "OpenGLRenderTarget.h"
#include "RHI/RHIObjects/RenderTarget/RHIRenderTarget.h"
OpenGLRenderTarget::OpenGLRenderTarget(RHIPixelFormat InPixelFormat)
    : RHIRenderTarget(InPixelFormat)
{

}

void OpenGLRenderTarget::WaitDeviceIdle()
{

}
