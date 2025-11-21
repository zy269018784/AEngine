#pragma once
#include "RHIObjects/CommandBuffer/RHICommandBuffer.h"
#include "D3D12Objects/Device/D3D12Device.h"
#include "D3D12Objects/CommandBuffer/D3D12CommandPool.h"
class D3D12CommandBuffer : public RHICommandBuffer
{
public:
	D3D12CommandBuffer(D3D12Device* InDevice, D3D12CommandPool* InCommandPool);
	~D3D12CommandBuffer();
	ID3D12GraphicsCommandList* GetHandle();
public:
	/*
		RHI API
	*/
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
		D3D12 API Wrapper
	*/
	void STDMETHODCALLTYPE ClearRenderTargetView(
		_In_  D3D12_CPU_DESCRIPTOR_HANDLE RenderTargetView,
		_In_  const FLOAT ColorRGBA[4],
		_In_  UINT NumRects,
		_In_reads_(NumRects)  const D3D12_RECT* pRects);

	void STDMETHODCALLTYPE OMSetRenderTargets(
		_In_  UINT NumRenderTargetDescriptors,
		_In_opt_  const D3D12_CPU_DESCRIPTOR_HANDLE* pRenderTargetDescriptors,
		_In_  BOOL RTsSingleHandleToDescriptorRange,
		_In_opt_  const D3D12_CPU_DESCRIPTOR_HANDLE* pDepthStencilDescriptor);

	void STDMETHODCALLTYPE SetGraphicsRootSignature(
		_In_opt_  ID3D12RootSignature* pRootSignature);


	void STDMETHODCALLTYPE RSSetViewports(
		_In_range_(0, D3D12_VIEWPORT_AND_SCISSORRECT_OBJECT_COUNT_PER_PIPELINE)  UINT NumViewports,
		_In_reads_(NumViewports)  const D3D12_VIEWPORT* pViewports);

	void STDMETHODCALLTYPE RSSetScissorRects(
		_In_range_(0, D3D12_VIEWPORT_AND_SCISSORRECT_OBJECT_COUNT_PER_PIPELINE)  UINT NumRects,
		_In_reads_(NumRects)  const D3D12_RECT* pRects);

	void STDMETHODCALLTYPE IASetPrimitiveTopology(
		_In_  D3D12_PRIMITIVE_TOPOLOGY PrimitiveTopology);

	void STDMETHODCALLTYPE IASetVertexBuffers(
		_In_  UINT StartSlot,
		_In_  UINT NumViews,
		_In_reads_opt_(NumViews)  const D3D12_VERTEX_BUFFER_VIEW* pViews);


	/*
		Draw 
	*/
	void STDMETHODCALLTYPE DrawInstanced(
		_In_  UINT VertexCountPerInstance,
		_In_  UINT InstanceCount,
		_In_  UINT StartVertexLocation,
		_In_  UINT StartInstanceLocation);

	void STDMETHODCALLTYPE DrawIndexedInstanced(
		_In_  UINT IndexCountPerInstance,
		_In_  UINT InstanceCount,
		_In_  UINT StartIndexLocation,
		_In_  INT BaseVertexLocation,
		_In_  UINT StartInstanceLocation);

	void STDMETHODCALLTYPE ResourceBarrier(
		_In_  UINT NumBarriers,
		_In_reads_(NumBarriers)  const D3D12_RESOURCE_BARRIER* pBarriers);

	HRESULT STDMETHODCALLTYPE Close(void);

	HRESULT STDMETHODCALLTYPE Reset(_In_  ID3D12CommandAllocator* pAllocator, _In_opt_  ID3D12PipelineState* pInitialState);

	void STDMETHODCALLTYPE ClearState(_In_opt_  ID3D12PipelineState* pPipelineState);
private:
	ID3D12GraphicsCommandList* Handle = nullptr;
	D3D12CommandPool* CommandPool = nullptr;
	D3D12Device* Device = nullptr;
};