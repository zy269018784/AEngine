#pragma once
#include "RHIObjects/Pipeline/RHIPipeline.h"
#include "RHIObjects/Core/RHIVertexInputLayout.h"
#include "RHIObjects/RenderPass/RHIRenderPass.h"
#include "RHIObjects/Shader/RHIShader.h"
#include "RHIObjects/Shader/RHIShaderResourceBindings.h"
#include "RHIObjects/Core/RHICore.h"
#include <cstdint>

class RHIGraphicsPipeline : public RHIPipeline
{
public:

public:	
	RHIGraphicsPipeline();
	virtual ~RHIGraphicsPipeline();
	/*
		Assembly of primitives
	*/
	virtual void SetTopology(RHITopology t);
	virtual RHITopology GetTopology() const;

	/*
		Vertex
	*/
	virtual void SetVertexInputLayout(const RHIVertexInputLayout& layout);
	virtual RHIVertexInputLayout GetVertexInputLayout() const;

	/*
		Rasterization
	*/
	virtual void SetCullMode(RHICullMode mode);
	virtual RHICullMode GetCullMode() const;
	virtual void SetPolygonMode(RHIPolygonMode mode);
	virtual RHIPolygonMode GetPolygonMode() const;
	virtual void SetFrontFace(RHIFrontFace f);
	virtual RHIFrontFace GetFrontFace() const;
	virtual void SetLineWidth(float width);
	virtual float GetLineWidth() const;

	/* 
		Depth Test 
	*/
	virtual void SetDepthOp(RHICompareOp op);
	virtual RHICompareOp GetDepthOp() const;
	virtual void SetDepthTest(bool enable);
	virtual bool GetDepthTest() const;
	virtual void SetDepthWrite(bool enable);
	virtual bool GetDepthWrite() const;

	/*
		Multisample
	*/
	virtual void SetSampleCount(int s);
	virtual int GetSampleCount() const;
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
