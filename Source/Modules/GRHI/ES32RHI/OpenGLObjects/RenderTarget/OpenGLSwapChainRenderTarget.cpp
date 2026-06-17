#include "ES32RHI/OpenGLObjects/RenderTarget/OpenGLSwapChainRenderTarget.h"
#include "ES32RHI/OpenGLObjects/CommandBuffer/OpenGLCommandBuffer.h"
#include "ES32RHI/OpenGLObjects/CommandBuffer/OpenGL46CommandBuffer.h"
#include "ES32RHI/OpenGLObjects/CommandBuffer/OpenGL33CommandBuffer.h"
#include "ES32RHI/OpenGLObjects/CommandBuffer/ES32CommandBuffer.h"
#include "ES32RHI/OpenGLObjects/CommandBuffer/ES31CommandBuffer.h"
#include "ES32RHI/OpenGLObjects/CommandBuffer/ES30CommandBuffer.h"
#include "ES32RHI/ES32.h"
#include "ES32RHI/OpenGLObjects/Surface/OpenGLSurface.h"
#include <iostream>

OpenGLSwapChainRenderTarget::OpenGLSwapChainRenderTarget(RHIDevice *InDevice, RHISurface* InSurface)
    : RHISwapChainRenderTarget(InDevice, InSurface->GetWidth(), InSurface->GetHeight(), InSurface->GetRHIPixelFormat())
{

}

OpenGLSwapChainRenderTarget::~OpenGLSwapChainRenderTarget()
{

}

void OpenGLSwapChainRenderTarget::RHIBeginFrame()
{
    // 绑定默认帧缓冲
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void OpenGLSwapChainRenderTarget::RHIEndFrame()
{

}

void OpenGLSwapChainRenderTarget::RHIBeginRenderPass()
{

}

void OpenGLSwapChainRenderTarget::RHIEndRenderPass()
{

}

void OpenGLSwapChainRenderTarget::RHIBeginRenderPass2()
{

}

void OpenGLSwapChainRenderTarget::RHIEndRenderPass2()
{

}


void OpenGLSwapChainRenderTarget::GetExtent(float &x, float &y, float &w, float &h)
{
    GLint Viewport[4];
    glGetIntegerv(GL_VIEWPORT, Viewport);
    x = Viewport[0];
    y = Viewport[1];
    w = Viewport[2];
    h = Viewport[3];
}

void OpenGLSwapChainRenderTarget::Resize(float Width, float Height)
{
    glViewport(0, 0, Width, Height);
}

void OpenGLSwapChainRenderTarget::WaitDeviceIdle()
{
    glFinish();
}
