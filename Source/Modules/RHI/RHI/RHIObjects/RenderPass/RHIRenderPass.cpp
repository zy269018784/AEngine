#include "RHIObjects/RenderPass/RHIRenderPass.h"
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

void RHIRenderPass::SetFrameBuffer(RHIFrameBuffer* pFrameBuffer)
{
	this->pFrameBuffer = pFrameBuffer;
}