#pragma once
#include <RHIObjects/RHIClearColor.h>
#include <RHIObjects/RHIRenderArea.h>
#include <RHIObjects/FrameBuffer/RHIFrameBuffer.h>
class RHIRenderPass
{
public:
	virtual ~RHIRenderPass();
	void SetClearColor(RHIClearColor &Color);
	void SetRendeArea(RHIRenderArea &RenderArea);
	void SetFrameBuffer(RHIFrameBuffer* pFrameBuffer);
public:
	RHIClearColor Color;
	RHIRenderArea RenderArea;
	RHIFrameBuffer* pFrameBuffer;
};
