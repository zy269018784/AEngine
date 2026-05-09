#include "OpenGLSwapChainRenderTarget.h"
#include "ES32RHI/OpenGLObjects/CommandBuffer/OpenGLCommandBuffer.h"
#include "ES32RHI/ES32.h"
OpenGLSwapChainRenderTarget::OpenGLSwapChainRenderTarget(OpenGLDevice *InDevice, OpenGLSurface* InSurface)
    : OpenGLRenderTarget((RHIPixelFormat)0)
{
    GraphicsCommandBuffers.resize(1);
    GraphicsCommandBuffers[0] = new OpenGLCommandBuffer();
}

OpenGLSwapChainRenderTarget::~OpenGLSwapChainRenderTarget()
{

}

void OpenGLSwapChainRenderTarget::RHIBeginFrame() {

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

void OpenGLSwapChainRenderTarget::Resize(float Width, float Height) {

}