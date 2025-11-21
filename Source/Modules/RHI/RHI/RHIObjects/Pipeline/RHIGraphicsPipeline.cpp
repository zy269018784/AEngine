#include "RHIObjects/Pipeline/RHIGraphicsPipeline.h"
#include <iostream>
RHIGraphicsPipeline::RHIGraphicsPipeline()
{
	ShaderResourceBindings = nullptr;
	LineWidth = 1.0f;
}

RHIGraphicsPipeline::~RHIGraphicsPipeline()
{
	std::cout << "~RHIGraphicsPipeline()" << std::endl;
}

/*
	Assembly of primitives
*/
void RHIGraphicsPipeline::SetTopology(RHITopology RHITopology)
{
	Topology = RHITopology;
}

RHITopology RHIGraphicsPipeline::GetTopology() const
{
	return Topology;
}


/*
	Vertex
*/
void RHIGraphicsPipeline::SetVertexInputLayout(const RHIVertexInputLayout& InVertexInputLayout)
{
	VertexInputLayout = InVertexInputLayout;
	//std::cout 
	//	<< "SetVertexInputLayout " << VertexInputLayout.Attributes.size() << " "
	//	<< "GetBinding " << VertexInputLayout.Attributes[0].GetBinding() << " "
	//	<< "GetLocation " << VertexInputLayout.Attributes[0].GetLocation() << " "
	//	<< std::endl;
}

RHIVertexInputLayout RHIGraphicsPipeline::GetVertexInputLayout() const
{
	return VertexInputLayout;
}

/*
	Rasterization
*/
void RHIGraphicsPipeline::SetCullMode(RHICullMode RHICullMode)
{
	CullMode = RHICullMode;
}

RHICullMode RHIGraphicsPipeline::GetCullMode() const
{
	return CullMode;
}

void RHIGraphicsPipeline::SetPolygonMode(RHIPolygonMode RHIPolygonMode)
{
	PolygonMode = RHIPolygonMode;
}

RHIPolygonMode RHIGraphicsPipeline::GetPolygonMode() const
{
	return PolygonMode;
}

void RHIGraphicsPipeline::SetFrontFace(RHIFrontFace RHIFrontFace)
{
	FrontFace = RHIFrontFace;
}

RHIFrontFace RHIGraphicsPipeline::GetFrontFace() const
{
	return FrontFace;
}

void RHIGraphicsPipeline::SetLineWidth(float Width)
{
	LineWidth = Width;
}

float RHIGraphicsPipeline::GetLineWidth() const
{
	return LineWidth;
}


/*
	Depth Test
*/
void RHIGraphicsPipeline::SetDepthOp(RHICompareOp RHICompareOp)
{
	DepthCompareOp = RHICompareOp;
}

RHICompareOp RHIGraphicsPipeline::GetDepthOp() const
{
	return DepthCompareOp;
}

void RHIGraphicsPipeline::SetDepthTest(bool enable)
{
	DepthTestEnable = enable;
}

bool RHIGraphicsPipeline::GetDepthTest() const
{
	return DepthTestEnable;
}

void RHIGraphicsPipeline::SetDepthWrite(bool enable)
{
	DepthWriteEnable = enable;
}

bool RHIGraphicsPipeline::GetDepthWrite() const
{
	return DepthWriteEnable;
}

/*
	Multisample
*/
void RHIGraphicsPipeline::SetSampleCount(int s)
{
	SampleCount = s;
}

int RHIGraphicsPipeline::GetSampleCount() const
{
	return SampleCount;
}

/*
	Render Pass
*/
//void RHIGraphicsPipeline::SetRenderPass(RHIRenderPass* RenderPass)
//{
//	RenderPass_ = RenderPass;
//}
//
//RHIRenderPass* RHIGraphicsPipeline::GetRenderPass() const
//{
//	return RenderPass_;
//}
