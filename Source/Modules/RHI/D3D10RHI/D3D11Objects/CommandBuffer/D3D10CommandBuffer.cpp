#include "D3D10CommandBuffer.h"
#include "D3D10Objects/Device/D3D10Device.h"
#include "D3D10Objects/CommandBuffer/D3D10CommandPool.h"
#include "D3D10Objects/Core/D3D10Core.h"

D3D10CommandBuffer::D3D10CommandBuffer(D3D10Device* InDevice, D3D10CommandPool* InCommandPool)
	: Device(InDevice), CommandPool(InCommandPool)
{
	if (FAILED(Device->CreateCommandList(0, D3D10_COMMAND_LIST_TYPE_DIRECT, CommandPool->GetHandle(), nullptr, IID_PPV_ARGS(&Handle)))) {
		
	}
}

D3D10CommandBuffer::~D3D10CommandBuffer()
{

}

ID3D10GraphicsCommandList* D3D10CommandBuffer::GetHandle()
{
	return Handle;
}

void D3D10CommandBuffer::RHISetPrimitiveTopology(RHITopology Topology)
{
	Handle->IASetPrimitiveTopology(ToD3D10Topology(Topology));
}

void D3D10CommandBuffer::RHIDrawPrimitive(std::uint32_t VertexCount, std::uint32_t InstanceCount, std::uint32_t FirstVertex, std::uint32_t FirstInstance)
{
	Handle->DrawInstanced(VertexCount, InstanceCount, FirstVertex, FirstInstance);
}

void D3D10CommandBuffer::RHIDrawIndexedPrimitive(std::int32_t IndexCount, std::int32_t InstanceCount, std::int32_t FirstIndex, std::int32_t VertexOffset, std::int32_t FirstInstance)
{
	Handle->DrawIndexedInstanced(IndexCount, InstanceCount, FirstIndex, VertexOffset, FirstInstance);
}

void D3D10CommandBuffer::RHIBeginRenderPass(RHIRenderPass* RenderPass)
{

}

void D3D10CommandBuffer::RHIEndRenderPass(RHIRenderPass* RenderPass)
{

}

void D3D10CommandBuffer::RHIBindIndexBuffer(RHIBuffer* IndexBuffer, std::uint32_t Offset, RHIIndexFormat RHIIndexFormat)
{

}

void D3D10CommandBuffer::RHISetGraphicsPipeline(RHIGraphicsPipeline* GraphicsPipeline)
{

}

void D3D10CommandBuffer::RHISetVertexInput(int FirstBinding, int BindingCount, const RHICommandBuffer::VertexInput* Bindings,
	RHIBuffer* RHIEBO, std::uint32_t IndexOffset, RHIIndexFormat RHIIndexFormat)
{

}


void D3D10CommandBuffer::RHISetViewport(const RHIViewport& InViewport)
{
	D3D10_VIEWPORT Viewport = { 0.0f, 0.0f, (float)InViewport.Width(), (float)InViewport.Height(), 0.0f, 1.0f };
	Handle->RSSetViewports(1, &Viewport);
}


void D3D10CommandBuffer::RHISetScissor(const RHIScissor& InScissor)
{
	D3D10_RECT scissorRect = { 0, 0, (LONG)InScissor.Width(), (LONG)InScissor.Height() };
	Handle->RSSetScissorRects(1, &scissorRect);
}


void D3D10CommandBuffer::RHISetStencilTestEnable(RHIBool32 Enable)
{

}

void D3D10CommandBuffer::RHISetStencilOp(RHIStencilFace FaceMask, RHIStencilOp FailOp, RHIStencilOp PassOp, RHIStencilOp DepthFailOp, RHICompareOp CompareOp)
{

}

void D3D10CommandBuffer::RHISetStencilWriteMask(RHIStencilFace FaceMask, uint32_t WriteMask)
{

}

void D3D10CommandBuffer::RHISetStencilReference(RHIStencilFace FaceMask, uint32_t Reference)
{

}

void D3D10CommandBuffer::RHISetDepthTestEnable(RHIBool32 Enable)
{

}

void D3D10CommandBuffer::RHISetDepthWriteEnable(RHIBool32 Enable)
{

}

void D3D10CommandBuffer::RHISetDepthCompareOp(RHICompareOp DepthCompareOp)
{

}

void D3D10CommandBuffer::RHISetDepthBoundsTestEnable(RHIBool32 Enable)
{

}

void D3D10CommandBuffer::RHISetDepthBounds(float MinDepthBounds, float MaxDepthBounds)
{

}

void D3D10CommandBuffer::RHICmdCopyBuffer(RHIBuffer* SrcBuffer, RHIBuffer* DstBuffer, std::uint32_t RegionCount, const RHIBufferCopy* Regions)
{

}

