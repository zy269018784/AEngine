#include "ES31SwapChainRenderTarget.h"
#include "ES32RHI/OpenGLObjects/CommandBuffer/OpenGLCommandBuffer.h"
#include "ES32RHI/OpenGLObjects/CommandBuffer/OpenGL46CommandBuffer.h"
#include "ES32RHI/OpenGLObjects/CommandBuffer/OpenGL33CommandBuffer.h"
#include "ES32RHI/OpenGLObjects/CommandBuffer/ES32CommandBuffer.h"
#include "ES32RHI/OpenGLObjects/CommandBuffer/ES31CommandBuffer.h"
#include "ES32RHI/OpenGLObjects/CommandBuffer/ES30CommandBuffer.h"
#include "ES32RHI/OpenGLObjects/CommandBuffer/ES21CommandBuffer.h"
#include "ES32RHI/ES32.h"
ES31SwapChainRenderTarget::ES31SwapChainRenderTarget(OpenGLDevice *InDevice, OpenGLSurface* InSurface)
: OpenGLSwapChainRenderTarget(InDevice, InSurface)
{
    GraphicsCommandBuffers.resize(1);
    GraphicsCommandBuffers[0] = new ES31CommandBuffer();
}

ES31SwapChainRenderTarget::~ES31SwapChainRenderTarget()
{

}
#if 0
void ES31SwapChainRenderTarget::RHIBeginFrame() {

}

void ES31SwapChainRenderTarget::RHIEndFrame() {

}

void ES31SwapChainRenderTarget::RHIBeginRenderPass() {

}

void ES31SwapChainRenderTarget::RHIEndRenderPass() {

}
void ES31SwapChainRenderTarget::GetExtent(float &x, float &y, float &w, float &h)
{
    GLint Viewport[4];
    glGetIntegerv(GL_VIEWPORT, Viewport);
    x = Viewport[0];
    y = Viewport[1];
    w = Viewport[2];
    h = Viewport[3];
}

void ES31SwapChainRenderTarget::Resize(float Width, float Height) {

}
#endif