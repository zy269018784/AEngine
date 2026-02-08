#pragma once
#include "D3D10_Includes.h"
#include "RHIObjects/CommandBuffer/RHICommandBuffer.h"

class D3D10Device;
class D3D10CommandPool;
class D3D10CommandBuffer : public RHICommandBuffer
{
public:
	D3D10CommandBuffer(D3D10Device* InDevice, D3D10CommandPool* InCommandPool);
	~D3D10CommandBuffer();
public:
	/*
		RHI API
	*/
	/*
		primitive topology
	 */
	virtual void RHISetPrimitiveTopology(RHITopology Topology) final override;
	virtual void RHIDrawPrimitive(std::uint32_t VertexCount, std::uint32_t InstanceCount = 1, std::uint32_t FirstVertex = 0, std::uint32_t FirstInstance = 0)  final override;

	virtual void RHIDrawIndexedPrimitive(std::int32_t IndexCount, std::int32_t InstanceCount = 1, std::int32_t FirstIndex = 0, std::int32_t VertexOffset = 0, std::int32_t FirstInstance = 0) final override;

	virtual void RHIBeginRenderPass(RHIRenderPass* RenderPass) final override;

	virtual void RHIEndRenderPass(RHIRenderPass* RenderPass) final override;

	virtual void RHIBindIndexBuffer(RHIBuffer* IndexBuffer, std::uint32_t Offset, RHIIndexFormat RHIIndexFormat) final override;

	virtual void RHISetGraphicsPipeline(RHIGraphicsPipeline* GraphicsPipeline) final override;

	virtual void RHISetVertexInput(int FirstBinding, int BindingCount, const RHICommandBuffer::VertexInput* Bindings,
		RHIBuffer* RHIEBO, std::uint32_t IndexOffset, RHIIndexFormat RHIIndexFormat) final override;

	/*
		View Port
	*/
	virtual void RHISetViewport(const RHIViewport& viewport) final override;

	/*
		Scissor Test
	*/
	virtual void RHISetScissor(const RHIScissor& scissor) final override;

	/*
		Stencil	Test
	*/
	virtual void RHISetStencilTestEnable(RHIBool32 Enable) final override;

	virtual void RHISetStencilOp(RHIStencilFace FaceMask, RHIStencilOp FailOp, RHIStencilOp PassOp, RHIStencilOp DepthFailOp, RHICompareOp CompareOp) final override;

	virtual void RHISetStencilWriteMask(RHIStencilFace FaceMask, uint32_t WriteMask) final override;

	virtual void RHISetStencilReference(RHIStencilFace FaceMask, uint32_t Reference) final override;
	/*
		Depth Test
	*/
	virtual void RHISetDepthTestEnable(RHIBool32 Enable) final override;

	virtual void RHISetDepthWriteEnable(RHIBool32 Enable) final override;

	virtual void RHISetDepthCompareOp(RHICompareOp DepthCompareOp) final override;

	virtual void RHISetDepthBoundsTestEnable(RHIBool32 Enable) final override;

	virtual void RHISetDepthBounds(float MinDepthBounds, float MaxDepthBounds) final override;

	/*
		Copy Commands
	*/
	virtual void RHICmdCopyBuffer(RHIBuffer* SrcBuffer, RHIBuffer* DstBuffer, std::uint32_t RegionCount, const RHIBufferCopy* Regions) final override;
public:
	/*
		D3D10 API Wrapper
	*/

private:
	D3D10CommandPool* CommandPool = nullptr;
	D3D10Device* Device = nullptr;
};