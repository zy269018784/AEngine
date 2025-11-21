#include "OpenGLWindow.h"
#include <OpenGL330.h>
OpenGLWindow::OpenGLWindow()
{
	CommandBuffer = new OpenGLCommandBuffer();
}

OpenGLWindow::~OpenGLWindow()
{
	delete CommandBuffer;
}

void OpenGLWindow::GetExtent(float& x, float& y, float& w, float& h)
{
	GLint Viewport[4];
	glGetIntegerv(GL_VIEWPORT, Viewport);
	x = Viewport[0];
	y = Viewport[1];
	w = Viewport[2];
	h = Viewport[3];
}

RHICommandBuffer* OpenGLWindow::CurrentGraphicsCommandBuffer()
{
	return CommandBuffer;
}

void OpenGLWindow::RHIBeginFrame()
{

}

void OpenGLWindow::RHIEndFrame()
{

}

void OpenGLWindow::RHIBeginRenderPass()
{

}

void OpenGLWindow::RHIEndRenderPass()
{

}

void OpenGLWindow::Draw()
{

}

void OpenGLWindow::WaitDeviceIdle()
{

}