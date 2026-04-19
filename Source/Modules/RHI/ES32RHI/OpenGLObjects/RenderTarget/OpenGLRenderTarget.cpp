#include "OpenGLRenderTarget.h"
#include "RHIObjects/RenderTarget/RHIRenderTarget.h"
OpenGLRenderTarget::OpenGLRenderTarget(RHIPixelFormat InPixelFormat)
    : RHIRenderTarget(InPixelFormat)
{

}

void OpenGLRenderTarget::WaitDeviceIdle()
{

}
