#include "ES32RHI/OpenGLObjects/RenderTarget/OpenGLSwapChainRenderTarget.h"
#include "ES32RHI/OpenGLObjects/CommandBuffer/OpenGLCommandBuffer.h"
#include "ES32RHI/OpenGLObjects/CommandBuffer/OpenGL46CommandBuffer.h"
#include "ES32RHI/OpenGLObjects/CommandBuffer/OpenGL33CommandBuffer.h"
#include "ES32RHI/OpenGLObjects/CommandBuffer/ES32CommandBuffer.h"
#include "ES32RHI/OpenGLObjects/CommandBuffer/ES31CommandBuffer.h"
#include "ES32RHI/OpenGLObjects/CommandBuffer/ES30CommandBuffer.h"
#include "ES32RHI/OpenGLObjects/CommandBuffer/ES21CommandBuffer.h"
#include "ES32RHI/ES32.h"
#include "ES32RHI/OpenGLObjects/Surface/OpenGLSurface.h"

OpenGLSwapChainRenderTarget::OpenGLSwapChainRenderTarget(RHIDevice *InDevice, RHISurface* InSurface)
    : RHISwapChainRenderTarget(InDevice, InSurface->GetWidth(), InSurface->GetHeight(), InSurface->GetRHIPixelFormat())
{
    GraphicsCommandBuffers.resize(1);
    GraphicsCommandBuffers[0] = new ES30CommandBuffer();
}

OpenGLSwapChainRenderTarget::~OpenGLSwapChainRenderTarget()
{

}

void OpenGLSwapChainRenderTarget::RHIBeginFrame() {
    // 绑定默认帧缓冲
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void OpenGLSwapChainRenderTarget::RHIEndFrame() {

}

void OpenGLSwapChainRenderTarget::RHIBeginRenderPass() {

}

void OpenGLSwapChainRenderTarget::RHIEndRenderPass() {

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

void OpenGLSwapChainRenderTarget::CreateFramebuffer()
{

}

void OpenGLSwapChainRenderTarget::CreateRenderPass()
{

}

void OpenGLSwapChainRenderTarget::CreateCommandbuffer()
{

}