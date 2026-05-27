#include "ES32SwapChainRenderTarget.h"
#include "ES32RHI/OpenGLObjects/CommandBuffer/ES32CommandBuffer.h"
#include "ES32RHI/ES32.h"
ES32SwapChainRenderTarget::ES32SwapChainRenderTarget(RHIDevice *InDevice, RHISurface* InSurface)
: OpenGLSwapChainRenderTarget(InDevice, InSurface)
{
    GraphicsCommandBuffers.resize(1);
    GraphicsCommandBuffers[0] = new ES32CommandBuffer();
}

ES32SwapChainRenderTarget::~ES32SwapChainRenderTarget()
{

}
#if 0
void ES32SwapChainRenderTarget::RHIBeginFrame() {

}

void ES32SwapChainRenderTarget::RHIEndFrame() {

}

void ES32SwapChainRenderTarget::RHIBeginRenderPass() {

}

void ES32SwapChainRenderTarget::RHIEndRenderPass() {

}
void ES32SwapChainRenderTarget::GetExtent(float &x, float &y, float &w, float &h)
{
    GLint Viewport[4];
    glGetIntegerv(GL_VIEWPORT, Viewport);
    x = Viewport[0];
    y = Viewport[1];
    w = Viewport[2];
    h = Viewport[3];
}

void ES32SwapChainRenderTarget::Resize(float Width, float Height) {

}
#endif