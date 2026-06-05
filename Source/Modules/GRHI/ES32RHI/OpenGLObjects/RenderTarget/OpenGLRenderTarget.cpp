#if 0
#include "OpenGLRenderTarget.h"
#include "ES32RHI/ES32.h"
OpenGLRenderTarget::OpenGLRenderTarget(RHIPixelFormat InPixelFormat)
    : RHIRenderTarget(InPixelFormat)
{

}

void OpenGLRenderTarget::WaitDeviceIdle()
{
    glFinish();
}
#endif