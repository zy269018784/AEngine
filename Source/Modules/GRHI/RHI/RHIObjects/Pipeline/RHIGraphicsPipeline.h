#pragma once
#include "RHI/RHIExport.h"
#include "RHI/RHIObjects/Pipeline/RHIPipeline.h"
#include "RHI/RHIObjects/Core/RHIVertexInputLayout.h"
#include "RHI/RHIObjects/Core/RHICore.h"

class RHIRenderPass;
class RHIEXPORT RHIGraphicsPipeline : public RHIPipeline
{
public:	
	RHIGraphicsPipeline();
	~RHIGraphicsPipeline() ;
public:
	/*
		Assembly of primitives
	*/
	void SetTopology(RHITopology t);
	RHITopology GetTopology() const;

	/*
		Vertex
	*/
	void SetVertexInputLayout(const RHIVertexInputLayout& layout);
	RHIVertexInputLayout GetVertexInputLayout() const;

	/*
		Rasterization
	*/
	void SetCullMode(RHICullMode mode);
	RHICullMode GetCullMode() const;
	void SetPolygonMode(RHIPolygonMode mode);
	RHIPolygonMode GetPolygonMode() const;
	void SetFrontFace(RHIFrontFace f);
	RHIFrontFace GetFrontFace() const;
	void SetLineWidth(float width);
	float GetLineWidth() const;

	/* 
		Depth Test 
	*/
	void SetDepthOp(RHICompareOp op);
	RHICompareOp GetDepthOp() const;
	void SetDepthTest(bool enable);
	bool GetDepthTest() const;
	void SetDepthWrite(bool enable);
	bool GetDepthWrite() const;

	/*
		Multisample
	*/
	void SetSampleCount(int s);
	int GetSampleCount() const;
protected:
	/*
		Assembly of primitives
	*/
	RHITopology						Topology;

	/*
		Vertex
	*/ 
	RHIVertexInputLayout			VertexInputLayout;


	/*
		Rasterization
	*/
	RHICullMode						CullMode;
	RHIFrontFace					FrontFace;
	RHIPolygonMode					PolygonMode;
	float							LineWidth;
	
	/*
		Depth Test
	*/
	RHICompareOp					DepthCompareOp;
	bool							DepthTestEnable;
	bool							DepthWriteEnable;

	/*
		Multisample
	*/
	int								SampleCount;
public:
	/*
		Render Pass
	*/
	RHIRenderPass					*RenderPass;
};
