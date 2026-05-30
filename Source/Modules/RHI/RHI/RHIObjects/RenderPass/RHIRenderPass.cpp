#include "RHI/RHIObjects/RenderPass/RHIRenderPass.h"
RHIRenderPass::RHIRenderPass(RHIDevice* InDevice, std::vector<RHIAttachment *> InColorAttachments, std::vector<RHIAttachment *> InDepthAttachments)
	: Device(InDevice), ColorAttachments(InColorAttachments), DepthAttachments(InDepthAttachments)
{

}

RHIRenderPass::~RHIRenderPass()
{

}

void RHIRenderPass::SetClearColor(RHIClearColor& Color)
{
	this->Color = Color;
}

void RHIRenderPass::SetRendeArea(RHIRenderArea& RenderArea)
{
	this->RenderArea = RenderArea;
}
#if 0
void RHIRenderPass::SetFrameBuffer(RHIFrameBuffer* pFrameBuffer)
{
	this->pFrameBuffer = pFrameBuffer;
}
#endif

RHIFrameBuffer *RHIRenderPass::GetFramebuffer() const {
	return nullptr;
	//return pFrameBuffer;
}