#pragma once
#include "RHI/RHIExport.h"
#include "RHI/RHIObjects/RHIClearColor.h"
#include "RHI/RHIObjects/RHIRenderArea.h"

class RHIFrameBuffer;

class RHIEXPORT RHIRenderPass
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
