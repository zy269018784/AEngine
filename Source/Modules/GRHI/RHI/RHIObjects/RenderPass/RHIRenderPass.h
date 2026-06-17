#pragma once
#include "RHI/RHIExport.h"
#include "RHI/RHIObjects/RHIClearColor.h"
#include "RHI/RHIObjects/RHIRenderArea.h"
#include "RHI/RHIObjects/FrameBuffer/RHIAttachment.h"
#include <vector>
class RHIFrameBuffer;
class RHIDevice;
class RHIEXPORT RHIRenderPass
{
public:
	RHIRenderPass(RHIDevice* InDevice, std::vector<RHIAttachment *> InColorAttachments, std::vector<RHIAttachment *> InDepthAttachments);
	virtual ~RHIRenderPass();
	void SetClearColor(RHIClearColor &Color);
	void SetRendeArea(RHIRenderArea &RenderArea);
	RHIFrameBuffer *GetFramebuffer() const;
public:
	virtual void Create() = 0;

public:
	RHIClearColor Color;
	RHIRenderArea RenderArea;
protected:
	RHIDevice* Device = nullptr;
public:
	std::vector<RHIAttachment *> ColorAttachments;
	std::vector<RHIAttachment *> DepthAttachments;
};
