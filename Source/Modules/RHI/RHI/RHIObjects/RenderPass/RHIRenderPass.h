#pragma once
#include "RHI/RHIExport.h"
#include "RHI/RHIObjects/RHIClearColor.h"
#include "RHI/RHIObjects/RHIRenderArea.h"

class RHIFrameBuffer;
class RHIDevice;
class RHIEXPORT RHIRenderPass
{
public:
	RHIRenderPass(RHIDevice* InDevice = nullptr);
	virtual ~RHIRenderPass();
	void SetClearColor(RHIClearColor &Color);
	void SetRendeArea(RHIRenderArea &RenderArea);
	//void SetFrameBuffer(RHIFrameBuffer* pFrameBuffer);
	RHIFrameBuffer *GetFramebuffer() const;
public:
	RHIClearColor Color;
	RHIRenderArea RenderArea;
protected:
	RHIDevice* Device = nullptr;
	//RHIFrameBuffer* pFrameBuffer = nullptr;
};
