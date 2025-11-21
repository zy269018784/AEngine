#pragma once
#include "RHIObjects/Window//RHIWindow.h"
#include <OpenGLObjects/CommandBuffer/OpenGLCommandBuffer.h>
#include <vector>
class OpenGLWindow : public RHIWindow
{
public:
	OpenGLWindow();
	~OpenGLWindow();
	virtual void GetExtent(float& x, float& y, float& w, float& h) final override;
	virtual RHICommandBuffer* CurrentGraphicsCommandBuffer() final override;
	virtual void RHIBeginFrame()  final override;
	virtual void RHIEndFrame() final override;
	virtual void RHIBeginRenderPass() final override;
	virtual void RHIEndRenderPass() final override;
	virtual void Draw() final override;
	virtual void WaitDeviceIdle() final override;
private:
	OpenGLCommandBuffer* CommandBuffer;
};