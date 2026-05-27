#pragma once
#include "ES32RHI/OpenGLObjects/RenderTarget/OpenGLSwapChainRenderTarget.h"
class RHIDevice;
class RHISurface;
class OpenGL33SwapChainRenderTarget : public OpenGLSwapChainRenderTarget
{
public:
    OpenGL33SwapChainRenderTarget(RHIDevice *InDevice, RHISurface* InSurface);
    ~OpenGL33SwapChainRenderTarget();
};
