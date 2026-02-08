#include "../D3D9CommandBuffer.h"
#include "D3D9Objects/Device/D3D9Device.h"
#include "D3D9Objects/CommandBuffer/D3D9CommandPool.h"
#include "D3D9Objects/Core/D3D9Core.h"

D3D9CommandBuffer::D3D9CommandBuffer(D3D9Device* InDevice, D3D9CommandPool* InCommandPool)
	: Device(InDevice), CommandPool(InCommandPool)
{
	if (FAILED(Device->CreateCommandList(0, D3D9_COMMAND_LIST_TYPE_DIRECT, CommandPool->GetHandle(), nullptr, IID_PPV_ARGS(&Handle)))) {
		
	}
}

D3D9CommandBuffer::~D3D9CommandBuffer()
{

}

ID3D9GraphicsCommandList* D3D9CommandBuffer::GetHandle()
{
	return Handle;
}

void D3D9CommandBuffer::RHISetPrimitiveTopology(RHITopology Topology)
{
	Handle->IASetPrimitiveTopology(ToD3D9Topology(Topology));
}

void D3D9CommandBuffer::RHIDrawPrimitive(std::uint32_t VertexCount, std::uint32_t InstanceCount, std::uint32_t FirstVertex, std::uint32_t FirstInstance)
{
	Handle->DrawInstanced(VertexCount, InstanceCount, FirstVertex, FirstInstance);
}

void D3D9CommandBuffer::RHIDrawIndexedPrimitive(std::int32_t IndexCount, std::int32_t InstanceCount, std::int32_t FirstIndex, std::int32_t VertexOffset, std::int32_t FirstInstance)
{
	Handle->DrawIndexedInstanced(IndexCount, InstanceCount, FirstIndex, VertexOffset, FirstInstance);
}

void D3D9CommandBuffer::RHIBeginRenderPass(RHIRenderPass* RenderPass)
{

}

void D3D9CommandBuffer::RHIEndRenderPass(RHIRenderPass* RenderPass)
{

}

void D3D9CommandBuffer::RHIBindIndexBuffer(RHIBuffer* IndexBuffer, std::uint32_t Offset, RHIIndexFormat RHIIndexFormat)
{

}

void D3D9CommandBuffer::RHISetGraphicsPipeline(RHIGraphicsPipeline* GraphicsPipeline)
{

}

void D3D9CommandBuffer::RHISetVertexInput(int FirstBinding, int BindingCount, const RHICommandBuffer::VertexInput* Bindings,
	RHIBuffer* RHIEBO, std::uint32_t IndexOffset, RHIIndexFormat RHIIndexFormat)
{

}


void D3D9CommandBuffer::RHISetViewport(const RHIViewport& InViewport)
{
	D3D9_VIEWPORT Viewport = { 0.0f, 0.0f, (float)InViewport.Width(), (float)InViewport.Height(), 0.0f, 1.0f };
	Handle->RSSetViewports(1, &Viewport);
}


void D3D9CommandBuffer::RHISetScissor(const RHIScissor& InScissor)
{
	D3D9_RECT scissorRect = { 0, 0, (LONG)InScissor.Width(), (LONG)InScissor.Height() };
	Handle->RSSetScissorRects(1, &scissorRect);
}


void D3D9CommandBuffer::RHISetStencilTestEnable(RHIBool32 Enable)
{

}

void D3D9CommandBuffer::RHISetStencilOp(RHIStencilFace FaceMask, RHIStencilOp FailOp, RHIStencilOp PassOp, RHIStencilOp DepthFailOp, RHICompareOp CompareOp)
{

}

void D3D9CommandBuffer::RHISetStencilWriteMask(RHIStencilFace FaceMask, uint32_t WriteMask)
{

}

void D3D9CommandBuffer::RHISetStencilReference(RHIStencilFace FaceMask, uint32_t Reference)
{

}

void D3D9CommandBuffer::RHISetDepthTestEnable(RHIBool32 Enable)
{

}

void D3D9CommandBuffer::RHISetDepthWriteEnable(RHIBool32 Enable)
{

}

void D3D9CommandBuffer::RHISetDepthCompareOp(RHICompareOp DepthCompareOp)
{

}

void D3D9CommandBuffer::RHISetDepthBoundsTestEnable(RHIBool32 Enable)
{

}

void D3D9CommandBuffer::RHISetDepthBounds(float MinDepthBounds, float MaxDepthBounds)
{

}

void D3D9CommandBuffer::RHICmdCopyBuffer(RHIBuffer* SrcBuffer, RHIBuffer* DstBuffer, std::uint32_t RegionCount, const RHIBufferCopy* Regions)
{

}

