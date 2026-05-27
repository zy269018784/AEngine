#pragma once
#include "ES32RHI/OpenGLObjects/RenderTarget/OpenGLSwapChainRenderTarget.h"
class RHIDevice;
class RHISurface;
class OpenGL46SwapChainRenderTarget : public OpenGLSwapChainRenderTarget
{
public:
    OpenGL46SwapChainRenderTarget(RHIDevice *InDevice, RHISurface* InSurface);
    ~OpenGL46SwapChainRenderTarget();
};
