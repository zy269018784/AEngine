#include "OpenGL46SwapChainRenderTarget.h"
#include "ES32RHI/OpenGLObjects/CommandBuffer/OpenGLCommandBuffer.h"
#include "ES32RHI/OpenGLObjects/CommandBuffer/OpenGL46CommandBuffer.h"
#include "ES32RHI/OpenGLObjects/CommandBuffer/OpenGL33CommandBuffer.h"
#include "ES32RHI/OpenGLObjects/CommandBuffer/ES32CommandBuffer.h"
#include "ES32RHI/OpenGLObjects/CommandBuffer/ES31CommandBuffer.h"
#include "ES32RHI/OpenGLObjects/CommandBuffer/ES30CommandBuffer.h"
#include "ES32RHI/OpenGLObjects/CommandBuffer/ES21CommandBuffer.h"
#include "ES32RHI/ES32.h"
OpenGL46SwapChainRenderTarget::OpenGL46SwapChainRenderTarget(OpenGLDevice *InDevice, OpenGLSurface* InSurface)
    : OpenGLRenderTarget((RHIPixelFormat)0)
{
    GraphicsCommandBuffers.resize(1);
    GraphicsCommandBuffers[0] = new OpenGL46CommandBuffer();
}

OpenGL46SwapChainRenderTarget::~OpenGL46SwapChainRenderTarget()
{
    delete GraphicsCommandBuffers[0];
}

void OpenGL46SwapChainRenderTarget::RHIBeginFrame() {

}

void OpenGL46SwapChainRenderTarget::RHIEndFrame() {

}

void OpenGL46SwapChainRenderTarget::RHIBeginRenderPass() {

}

void OpenGL46SwapChainRenderTarget::RHIEndRenderPass() {

}
void OpenGL46SwapChainRenderTarget::GetExtent(float &x, float &y, float &w, float &h)
{
    GLint Viewport[4];
    glGetIntegerv(GL_VIEWPORT, Viewport);
    x = Viewport[0];
    y = Viewport[1];
    w = Viewport[2];
    h = Viewport[3];
}

void OpenGL46SwapChainRenderTarget::Resize(float Width, float Height) {

}