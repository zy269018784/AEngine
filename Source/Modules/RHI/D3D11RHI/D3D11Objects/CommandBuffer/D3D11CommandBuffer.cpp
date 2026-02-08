#include "D3D11CommandBuffer.h"

#include "D3D11Objects/Core/D3D11Core.h"
//#include "D3D11Objects/Device/D3D11Device.h"
//#include "D3D11CommandPool.h"
//#include "D3D11RenderPass.h"
//#include "D3D11Pipeline.h"
//#include "D3D11Buffer.h"

D3D11CommandBuffer::D3D11CommandBuffer(D3D11Device* InDevice, D3D11CommandPool* InCommandPool)
	: Device(InDevice)
	, CommandPool(InCommandPool)
{
#if 0
	// 根据命令池的类型创建相应的设备上下文
	if (CommandPool->IsDeferred())
	{
		// 创建延迟上下文用于多线程录制
		HRESULT hr = Device->GetNativeDevice()->CreateDeferredContext(0, &DeferredContext);
		if (SUCCEEDED(hr))
		{
			Handle = DeferredContext;
			bIsDeferredContext = true;
		}
		else
		{
			// 回退到立即上下文
			Device->GetNativeDevice()->GetImmediateContext(&Handle);
		}
	}
	else
	{
		// 立即上下文
		Device->GetNativeDevice()->GetImmediateContext(&Handle);
	}
#endif
}

D3D11CommandBuffer::~D3D11CommandBuffer()
{

}

void D3D11CommandBuffer::RHISetPrimitiveTopology(RHITopology Topology)
{
	Handle->IASetPrimitiveTopology(ToD3D11Topology(Topology));
}

void D3D11CommandBuffer::RHIDrawPrimitive(std::uint32_t VertexCount, std::uint32_t InstanceCount,
	std::uint32_t FirstVertex, std::uint32_t FirstInstance)
{
	Handle->DrawInstanced(VertexCount, InstanceCount, FirstVertex, FirstInstance);
}

void D3D11CommandBuffer::RHIDrawIndexedPrimitive(std::int32_t IndexCount, std::int32_t InstanceCount,
	std::int32_t FirstIndex, std::int32_t VertexOffset, std::int32_t FirstInstance)
{
	Handle->DrawIndexedInstanced(IndexCount, InstanceCount, FirstIndex, VertexOffset, FirstInstance);
}

void D3D11CommandBuffer::RHIBeginRenderPass(RHIRenderPass* RenderPass)
{

}

void D3D11CommandBuffer::RHIEndRenderPass(RHIRenderPass* RenderPass)
{

}

void D3D11CommandBuffer::RHIBindIndexBuffer(RHIBuffer* IndexBuffer, std::uint32_t Offset, RHIIndexFormat IndexFormat)
{
#if 0
	D3D11Buffer* D3D11Buffer = static_cast<D3D11Buffer*>(IndexBuffer);
	if (D3D11Buffer)
	{
		Handle->IASetIndexBuffer(D3D11Buffer->GetNativeBuffer(), ConvertIndexFormat(IndexFormat), Offset);
	}
#endif
}

void D3D11CommandBuffer::RHISetGraphicsPipeline(RHIGraphicsPipeline* GraphicsPipeline)
{
#if 0
	D3D11GraphicsPipeline* D3D11Pipeline = static_cast<D3D11GraphicsPipeline*>(GraphicsPipeline);
	if (D3D11Pipeline)
	{
		// 设置流水线的各个状态
		// 这应该由流水线对象统一管理
		D3D11Pipeline->ApplyState(Handle.Get());

		// 更新当前状态
		CurrentInputLayout = D3D11Pipeline->GetInputLayout();
		CurrentVertexShader = D3D11Pipeline->GetVertexShader();
		CurrentPixelShader = D3D11Pipeline->GetPixelShader();
		CurrentRasterizerState = D3D11Pipeline->GetRasterizerState();
		CurrentDepthStencilState = D3D11Pipeline->GetDepthStencilState();
		CurrentBlendState = D3D11Pipeline->GetBlendState();
	}
#endif
}

void D3D11CommandBuffer::RHISetVertexInput(int FirstBinding, int BindingCount,
	const RHICommandBuffer::VertexInput* Bindings,
	RHIBuffer* RHIEBO, std::uint32_t IndexOffset, RHIIndexFormat IndexFormat)
{
#if 0
	// 为每个绑定创建D3D11的顶点缓冲区视图
	std::vector<ID3D11Buffer*> buffers(BindingCount);
	std::vector<UINT> strides(BindingCount);
	std::vector<UINT> offsets(BindingCount);

	for (int i = 0; i < BindingCount; ++i)
	{
		D3D11Buffer* buffer = static_cast<D3D11Buffer*>(Bindings[i].Buffer);
		if (buffer)
		{
			buffers[i] = buffer->GetNativeBuffer();
			strides[i] = Bindings[i].Stride;
			offsets[i] = Bindings[i].Offset;
		}
	}

	IASetVertexBuffers(FirstBinding, BindingCount,
		buffers.data(), strides.data(), offsets.data());

	// 设置索引缓冲区
	if (RHIEBO)
	{
		RHIBindIndexBuffer(RHIEBO, IndexOffset, IndexFormat);
	}
#endif
}

void D3D11CommandBuffer::RHISetViewport(const RHIViewport& viewport)
{
#if 0
	D3D11_VIEWPORT d3dViewport;
	d3dViewport.TopLeftX = viewport.X;
	d3dViewport.TopLeftY = viewport.Y;
	d3dViewport.Width = viewport.Width;
	d3dViewport.Height = viewport.Height;
	d3dViewport.MinDepth = viewport.MinDepth;
	d3dViewport.MaxDepth = viewport.MaxDepth;

	RSSetViewports(1, &d3dViewport);
#endif
}

void D3D11CommandBuffer::RHISetScissor(const RHIScissor& scissor)
{
#if 0
	D3D11_RECT rect;
	rect.left = scissor.OffsetX;
	rect.top = scissor.OffsetY;
	rect.right = scissor.OffsetX + scissor.ExtentX;
	rect.bottom = scissor.OffsetY + scissor.ExtentY;

	RSSetScissorRects(1, &rect);
#endif
}

// 模板测试相关
void D3D11CommandBuffer::RHISetStencilTestEnable(RHIBool32 Enable)
{
	// 这部分应该在深度模板状态中设置
	// 这里只是标记，实际应用在流水线状态中
}

void D3D11CommandBuffer::RHISetStencilOp(RHIStencilFace FaceMask, RHIStencilOp FailOp,
	RHIStencilOp PassOp, RHIStencilOp DepthFailOp, RHICompareOp CompareOp)
{
	// 这部分应该在深度模板状态中设置
}

void D3D11CommandBuffer::RHISetStencilWriteMask(RHIStencilFace FaceMask, uint32_t WriteMask)
{
	// D3D11通过OMSetDepthStencilState设置
}

void D3D11CommandBuffer::RHISetStencilReference(RHIStencilFace FaceMask, uint32_t Reference)
{
	// 设置模板参考值
	//Handle->OMSetDepthStencilState(CurrentDepthStencilState.Get(), Reference);
}

// 深度测试相关
void D3D11CommandBuffer::RHISetDepthTestEnable(RHIBool32 Enable)
{
	// 在流水线状态中设置
}

void D3D11CommandBuffer::RHISetDepthWriteEnable(RHIBool32 Enable)
{
	// 在流水线状态中设置
}

void D3D11CommandBuffer::RHISetDepthCompareOp(RHICompareOp DepthCompareOp)
{
	// 在流水线状态中设置
}

void D3D11CommandBuffer::RHISetDepthBoundsTestEnable(RHIBool32 Enable)
{
	// D3D11不支持深度边界测试
}

void D3D11CommandBuffer::RHISetDepthBounds(float MinDepthBounds, float MaxDepthBounds)
{
	// D3D11不支持深度边界测试
}

void D3D11CommandBuffer::RHICmdCopyBuffer(RHIBuffer* SrcBuffer, RHIBuffer* DstBuffer,
	std::uint32_t RegionCount, const RHIBufferCopy* Regions)
{
#if 0
	D3D11Buffer* src = static_cast<D3D11Buffer*>(SrcBuffer);
	D3D11Buffer* dst = static_cast<D3D11Buffer*>(DstBuffer);

	if (src && dst)
	{
		// D3D11中复制缓冲区通常使用CopyResource或CopySubresourceRegion
		for (uint32_t i = 0; i < RegionCount; ++i)
		{
			const RHIBufferCopy& region = Regions[i];
			Handle->CopySubresourceRegion(
				dst->GetNativeBuffer(), 0, region.DstOffset, 0, 0,
				src->GetNativeBuffer(), 0,
				reinterpret_cast<const D3D11_BOX*>(&region.SrcOffset));
		}
	}
#endif
}



