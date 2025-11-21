#include "VulkanObjects/CommandBuffer/VulkanCommandBuffer.h"
#include "VulkanObjects/CommandBuffer/VulkanCommandPool.h"
#include "VulkanObjects/RenderPass/VulkanRenderPass.h"
#include "VulkanObjects/FrameBuffer/VulkanFrameBuffer.h"
#include "VulkanObjects/Resource/VulkanBuffer.h"
#include <VulkanObjects/Pipeline/VulkanGraphicsPipeline.h>
#include "VulkanObjects/Shader/VulkanShaderResourceBindings.h"
#include "VulkanObjects/Core/VulkanCore.h"
#include <stdexcept>
#include <iostream>


VulkanCommandBuffer::VulkanCommandBuffer(VulkanDevice* InDevice, VulkanCommandPool* InCommandPool)
	: Device(InDevice), CommandPool(InCommandPool)
{
	CommandPool->AllocateOneCommandBuffer(&Handle);
}

VulkanCommandBuffer::~VulkanCommandBuffer()
{
	CommandPool->FreeCommandBuffers(1, &Handle);
}

VkCommandBuffer VulkanCommandBuffer::GetHandle()
{
	return Handle;
}

VkResult VulkanCommandBuffer::BeginSingleTime()
{
	VkCommandBufferBeginInfo BeginInfo{};
	BeginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
	BeginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
	return BeginCommandBuffer(&BeginInfo);
}

// draw primitive
void VulkanCommandBuffer::RHIDrawPrimitive(std::uint32_t VertexCount, std::uint32_t InstanceCount, std::uint32_t FirstVertex, std::uint32_t FirstInstance)
{
	CmdDraw(VertexCount, InstanceCount, FirstVertex, FirstInstance);
}

// draw indexed primitive
void VulkanCommandBuffer::RHIDrawIndexedPrimitive(std::int32_t IndexCount, std::int32_t InstanceCount, std::int32_t FirstIndex, std::int32_t VertexOffset, std::int32_t FirstInstance)
{
	CmdDrawIndexed(IndexCount, InstanceCount, FirstIndex, VertexOffset, FirstInstance);
}

void VulkanCommandBuffer::RHISetViewport(const RHIViewport& viewport)
{
	VkViewport Viewport = { viewport.Viewport()[0], viewport.Viewport()[1], viewport.Viewport()[2], viewport.Viewport()[3] };
	CmdSetViewport(0, 1, &Viewport);
}

void VulkanCommandBuffer::RHIBeginRenderPass(RHIRenderPass* RenderPass)
{
	VkClearValue ClearColor = {
		// color
		{
			{ RenderPass->Color.R(), RenderPass->Color.R(), RenderPass->Color.R(), RenderPass->Color.R()}
		}
	};

	VkRenderPassBeginInfo RenderPassBeginInfo{};
	RenderPassBeginInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
	RenderPassBeginInfo.renderPass  = static_cast<VulkanRenderPass*>(RenderPass)->GetHandle();
	RenderPassBeginInfo.framebuffer = static_cast<VulkanFrameBuffer *>(RenderPass->pFrameBuffer)->GetHandle();
	RenderPassBeginInfo.renderArea.offset = { RenderPass->RenderArea.OffsetX(), RenderPass->RenderArea.OffsetY() };
	RenderPassBeginInfo.renderArea.extent = { RenderPass->RenderArea.Width(), RenderPass->RenderArea.Height() };
	RenderPassBeginInfo.clearValueCount = 1;
	RenderPassBeginInfo.pClearValues = &ClearColor;

	CmdBeginRenderPass(&RenderPassBeginInfo, VK_SUBPASS_CONTENTS_INLINE);
}

void VulkanCommandBuffer::RHIEndRenderPass(RHIRenderPass* RenderPass)
{
	CmdEndRenderPass();
}

void VulkanCommandBuffer::RHIBindIndexBuffer(RHIBuffer* IndexBuffer, std::uint32_t Offset, RHIIndexFormat RHIIndexFormat)
{
	VulkanBuffer* EBO = dynamic_cast<VulkanBuffer*>(IndexBuffer);
	CmdBindIndexBuffer(EBO->GetHandle(), Offset, ToVulkanIndexType(RHIIndexFormat));
}

void VulkanCommandBuffer::RHISetGraphicsPipeline(RHIGraphicsPipeline* GraphicsPipeline)
{
	/*
		绑定pipeline
	*/
	VulkanGraphicsPipeline* pGraphicsPipeline = dynamic_cast<VulkanGraphicsPipeline*>(GraphicsPipeline);
	VkPipelineBindPoint PipelineBindPoint = pGraphicsPipeline->GetPipelineBindPoint();
	CmdBindPipeline(PipelineBindPoint, pGraphicsPipeline->GetHandle());

	if (pGraphicsPipeline->ShaderResourceBindings)
	{
		/*
			绑定描述符集合
		*/
		VulkanShaderResourceBindings* pSRB = dynamic_cast<VulkanShaderResourceBindings*>(pGraphicsPipeline->ShaderResourceBindings);
		VkDescriptorSet DescriptorSet = pSRB->GetDescriptorSet()->GetHandle();
		CmdBindDescriptorSets(PipelineBindPoint, ((VulkanGraphicsPipeline*)GraphicsPipeline)->GetPipelineLayout(), 0, 1, &DescriptorSet, 0, nullptr);
	}
}

void VulkanCommandBuffer::RHISetVertexInput(int FirstBinding, int BindingCount, const RHICommandBuffer::VertexInput* Bindings,
	RHIBuffer* RHIEBO, std::uint32_t IndexOffset, RHIIndexFormat RHIIndexFormat)
{

	if (Bindings)
	{
		std::vector<VkBuffer>           StreamBuffers;
		std::vector<VkDeviceSize>       StreamOffset;
		// VBO Stream
		for (int i = 0; i < BindingCount; i++)
		{
			RHIBuffer* Buffer = Bindings[i].first;
			VulkanBuffer *vkBuffer = dynamic_cast<VulkanBuffer*>(Buffer);

			StreamBuffers.emplace_back(vkBuffer->GetHandle());
			StreamOffset.emplace_back(Bindings[i].second);
		}
		CmdBindVertexBuffers(FirstBinding, StreamBuffers.size(), StreamBuffers.data(), StreamOffset.data());
	}

	// EBO
	if (RHIEBO)
	{
		auto VulkanIndexType = ToVulkanIndexType(RHIIndexFormat);
		VkBuffer EBOHandle = ((VulkanBuffer*)RHIEBO)->GetHandle();
		CmdBindIndexBuffer(EBOHandle, IndexOffset, VulkanIndexType);
	}
}

void VulkanCommandBuffer::RHISetScissor(const RHIScissor& scissor)
{
	VkRect2D rect{};
	rect.offset = { scissor.X(), scissor.Y() };
	rect.extent = { scissor.Width(), scissor.Height() };
	CmdSetScissor(0, 1, &rect);
}

void VulkanCommandBuffer::RHISetStencilTestEnable(RHIBool32 Enable)
{
	CmdSetStencilTestEnable(false);
}

void VulkanCommandBuffer::RHISetStencilOp(RHIStencilFace FaceMask, RHIStencilOp FailOp, RHIStencilOp PassOp, RHIStencilOp DepthFailOp, RHICompareOp CompareOp)
{

}

void VulkanCommandBuffer::RHISetStencilWriteMask(RHIStencilFace FaceMask, uint32_t WriteMask)
{

}

void VulkanCommandBuffer::RHISetStencilReference(RHIStencilFace FaceMask, uint32_t Reference)
{

}

void VulkanCommandBuffer::RHISetDepthTestEnable(RHIBool32 Enable)
{
	CmdSetDepthTestEnable(Enable);
}

void VulkanCommandBuffer::RHISetDepthWriteEnable(RHIBool32 Enable)
{
	CmdSetDepthWriteEnable(Enable);
}

void VulkanCommandBuffer::RHISetDepthCompareOp(RHICompareOp DepthCompareOp)
{
	CmdSetDepthCompareOp(ToVulkanCompareOp(DepthCompareOp));
}

void VulkanCommandBuffer::RHISetDepthBoundsTestEnable(RHIBool32 Enable)
{
	CmdSetDepthBoundsTestEnable(Enable);
}

void VulkanCommandBuffer::RHISetDepthBounds(float MinDepthBounds, float MaxDepthBounds)
{
	CmdSetDepthBounds(MinDepthBounds, MaxDepthBounds);
}

/*
	Copy Commands
*/
void VulkanCommandBuffer::RHICmdCopyBuffer(RHIBuffer* SrcBuffer, RHIBuffer* DstBuffer, std::uint32_t RegionCount, const RHIBufferCopy* Regions)
{
	VkBuffer SrcHandle = dynamic_cast<VulkanBuffer*>(SrcBuffer)->GetHandle();
	VkBuffer DstHandle = dynamic_cast<VulkanBuffer*>(SrcBuffer)->GetHandle();
	//VkBufferCopy* VkRegions = new VkBufferCopy[RegionCount];
	//std::memcpy(VkRegions, Regions, (const VkBufferCopy*)Regions);
	vkCmdCopyBuffer(Handle, SrcHandle, DstHandle, RegionCount, (const VkBufferCopy*)Regions);
}