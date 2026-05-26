#include "OpenGL33SwapChainRenderTarget.h"
#include "ES32RHI/OpenGLObjects/CommandBuffer/OpenGLCommandBuffer.h"
#include "ES32RHI/OpenGLObjects/CommandBuffer/OpenGL46CommandBuffer.h"
#include "ES32RHI/OpenGLObjects/CommandBuffer/OpenGL33CommandBuffer.h"
#include "ES32RHI/OpenGLObjects/CommandBuffer/ES32CommandBuffer.h"
#include "ES32RHI/OpenGLObjects/CommandBuffer/ES31CommandBuffer.h"
#include "ES32RHI/OpenGLObjects/CommandBuffer/ES30CommandBuffer.h"
#include "ES32RHI/OpenGLObjects/CommandBuffer/ES21CommandBuffer.h"
#include "ES32RHI/ES32.h"
OpenGL33SwapChainRenderTarget::OpenGL33SwapChainRenderTarget(OpenGLDevice *InDevice, OpenGLSurface* InSurface)
: OpenGLSwapChainRenderTarget(InDevice, InSurface)
{
    GraphicsCommandBuffers.resize(1);
    GraphicsCommandBuffers[0] = new OpenGL33CommandBuffer();
}

OpenGL33SwapChainRenderTarget::~OpenGL33SwapChainRenderTarget()
{

}
#if 0
void OpenGL33SwapChainRenderTarget::RHIBeginFrame() {

}

void OpenGL33SwapChainRenderTarget::RHIEndFrame() {

}

void OpenGL33SwapChainRenderTarget::RHIBeginRenderPass() {

}

void OpenGL33SwapChainRenderTarget::RHIEndRenderPass() {

}
void OpenGL33SwapChainRenderTarget::GetExtent(float &x, float &y, float &w, float &h)
{
    GLint Viewport[4];
    glGetIntegerv(GL_VIEWPORT, Viewport);
    x = Viewport[0];
    y = Viewport[1];
    w = Viewport[2];
    h = Viewport[3];
}

void OpenGL33SwapChainRenderTarget::Resize(float Width, float Height) {

}
#endif