#include "D3D12CommandBuffer.h"
#include "D3D12Objects/Device/D3D12Device.h"
#include "D3D12Objects/CommandBuffer/D3D12CommandPool.h"
#include "D3D12Objects/Pipeline/D3D12GraphicsPipeline.h"
#include "D3D12Objects/Core/D3D12Core.h"

D3D12CommandBuffer::D3D12CommandBuffer(D3D12Device* InDevice, D3D12CommandPool* InCommandPool)
	: Device(InDevice), CommandPool(InCommandPool)
{
	if (FAILED(Device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, CommandPool->GetHandle(), nullptr, IID_PPV_ARGS(&Handle)))) {
		
	}
}

D3D12CommandBuffer::~D3D12CommandBuffer()
{

}

ID3D12GraphicsCommandList* D3D12CommandBuffer::GetHandle()
{
	return Handle;
}

void D3D12CommandBuffer::RHISetPrimitiveTopology(RHITopology Topology)
{
	IASetPrimitiveTopology(ToD3D12Topology(Topology));
}

void D3D12CommandBuffer::RHIDrawPrimitive(std::uint32_t VertexCount, std::uint32_t InstanceCount, std::uint32_t FirstVertex, std::uint32_t FirstInstance)
{
	DrawInstanced(VertexCount, InstanceCount, FirstVertex, FirstInstance);
}

void D3D12CommandBuffer::RHIDrawIndexedPrimitive(std::int32_t IndexCount, std::int32_t InstanceCount, std::int32_t FirstIndex, std::int32_t VertexOffset, std::int32_t FirstInstance)
{
	DrawIndexedInstanced(IndexCount, InstanceCount, FirstIndex, VertexOffset, FirstInstance);
}

void D3D12CommandBuffer::RHIBeginRenderPass(RHIRenderPass* RenderPass)
{

}

void D3D12CommandBuffer::RHIEndRenderPass(RHIRenderPass* RenderPass)
{

}

void D3D12CommandBuffer::RHIBindIndexBuffer(RHIBuffer* IndexBuffer, std::uint32_t Offset, RHIIndexFormat RHIIndexFormat)
{
	D3D12_INDEX_BUFFER_VIEW View;
	View.BufferLocation = 0;
	View.Format;
	View.SizeInBytes = 0;
	IASetIndexBuffer(&View);
}

void D3D12CommandBuffer::RHISetGraphicsPipeline(RHIGraphicsPipeline* GraphicsPipeline)
{
	D3D12GraphicsPipeline* pGraphicsPipeline = dynamic_cast<D3D12GraphicsPipeline*>(GraphicsPipeline);
    Handle->Reset(CommandPool->GetHandle(), pGraphicsPipeline->GetHandle());
}

void D3D12CommandBuffer::RHISetVertexInput(int FirstBinding, int BindingCount, const RHICommandBuffer::VertexInput* Bindings,
	RHIBuffer* RHIEBO, std::uint32_t IndexOffset, RHIIndexFormat RHIIndexFormat)
{

}


void D3D12CommandBuffer::RHISetViewport(const RHIViewport& InViewport)
{
	D3D12_VIEWPORT Viewport = { 0.0f, 0.0f, (float)InViewport.Width(), (float)InViewport.Height(), 0.0f, 1.0f };
	RSSetViewports(1, &Viewport);
}


void D3D12CommandBuffer::RHISetScissor(const RHIScissor& InScissor)
{
	D3D12_RECT scissorRect = { 0, 0, (LONG)InScissor.Width(), (LONG)InScissor.Height() };
	RSSetScissorRects(1, &scissorRect);
}


void D3D12CommandBuffer::RHISetStencilTestEnable(RHIBool32 Enable)
{

}

void D3D12CommandBuffer::RHISetStencilOp(RHIStencilFace FaceMask, RHIStencilOp FailOp, RHIStencilOp PassOp, RHIStencilOp DepthFailOp, RHICompareOp CompareOp)
{

}

void D3D12CommandBuffer::RHISetStencilWriteMask(RHIStencilFace FaceMask, uint32_t WriteMask)
{

}

void D3D12CommandBuffer::RHISetStencilReference(RHIStencilFace FaceMask, uint32_t Reference)
{

}

void D3D12CommandBuffer::RHISetDepthTestEnable(RHIBool32 Enable)
{

}

void D3D12CommandBuffer::RHISetDepthWriteEnable(RHIBool32 Enable)
{

}

void D3D12CommandBuffer::RHISetDepthCompareOp(RHICompareOp DepthCompareOp)
{

}

void D3D12CommandBuffer::RHISetDepthBoundsTestEnable(RHIBool32 Enable)
{

}

void D3D12CommandBuffer::RHISetDepthBounds(float MinDepthBounds, float MaxDepthBounds)
{

}

void D3D12CommandBuffer::RHICmdCopyBuffer(RHIBuffer* SrcBuffer, RHIBuffer* DstBuffer, std::uint32_t RegionCount, const RHIBufferCopy* Regions)
{

}

