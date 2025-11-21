#pragma once
#include "RHIObjects/CommandBuffer/RHICommandBuffer.h"
struct GLFWwindow;
class RHIWindow
{
public:
	RHIWindow() = default;
	//RHIWindow(GLFWwindow* Window);
	virtual ~RHIWindow();
	virtual RHICommandBuffer* CurrentGraphicsCommandBuffer() = 0;
	virtual void RHIBeginFrame() = 0;
	virtual void RHIEndFrame() = 0;
	virtual void RHIBeginRenderPass() = 0;
	virtual void RHIEndRenderPass() = 0;
	virtual void Draw() = 0;
	virtual void GetExtent(float &x, float &y, float &w, float &h) = 0;
	virtual void WaitDeviceIdle() = 0;
//public:
//	GLFWwindow* GLFWWindow;
};