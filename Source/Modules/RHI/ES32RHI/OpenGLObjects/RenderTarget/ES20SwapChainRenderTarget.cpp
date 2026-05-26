#include "ES20SwapChainRenderTarget.h"
#include "ES32RHI/OpenGLObjects/CommandBuffer/OpenGLCommandBuffer.h"
#include "ES32RHI/OpenGLObjects/CommandBuffer/OpenGL46CommandBuffer.h"
#include "ES32RHI/OpenGLObjects/CommandBuffer/OpenGL33CommandBuffer.h"
#include "ES32RHI/OpenGLObjects/CommandBuffer/ES32CommandBuffer.h"
#include "ES32RHI/OpenGLObjects/CommandBuffer/ES31CommandBuffer.h"
#include "ES32RHI/OpenGLObjects/CommandBuffer/ES30CommandBuffer.h"
#include "ES32RHI/OpenGLObjects/CommandBuffer/ES21CommandBuffer.h"
#include "ES32RHI/OpenGLObjects/CommandBuffer/ES20CommandBuffer.h"
#include "ES32RHI/ES32.h"
ES20SwapChainRenderTarget::ES20SwapChainRenderTarget(OpenGLDevice *InDevice, OpenGLSurface* InSurface)
    : OpenGLSwapChainRenderTarget(InDevice, InSurface)
{
    GraphicsCommandBuffers.resize(1);
    GraphicsCommandBuffers[0] = new ES20CommandBuffer();
}

ES20SwapChainRenderTarget::~ES20SwapChainRenderTarget()
{

}
#if 0
void ES20SwapChainRenderTarget::RHIBeginFrame() {

}

void ES20SwapChainRenderTarget::RHIEndFrame() {

}

void ES20SwapChainRenderTarget::RHIBeginRenderPass() {

}

void ES20SwapChainRenderTarget::RHIEndRenderPass() {

}
void ES20SwapChainRenderTarget::GetExtent(float &x, float &y, float &w, float &h)
{
    GLint Viewport[4];
    glGetIntegerv(GL_VIEWPORT, Viewport);
    x = Viewport[0];
    y = Viewport[1];
    w = Viewport[2];
    h = Viewport[3];
}

void ES20SwapChainRenderTarget::Resize(float Width, float Height) {

}
#endif