#include "VulkanObjects/CommandBuffer/VulkanCommandBuffer.h"

/*
	Command Buffer
*/
VkResult VulkanCommandBuffer::BeginCommandBuffer(const VkCommandBufferBeginInfo* BeginInfo)
{
	return vkBeginCommandBuffer(Handle, BeginInfo);
}

VkResult VulkanCommandBuffer::EndCommandBuffer()
{
	return vkEndCommandBuffer(Handle);
}

VkResult VulkanCommandBuffer::ResetCommandBuffer(VkCommandBufferResetFlags Flags)
{
	return vkResetCommandBuffer(Handle, Flags);
}

/*
	Pipeline Barrier
*/
void VulkanCommandBuffer::CmdPipelineBarrier(VkPipelineStageFlags		 SrcStageMask,
	VkPipelineStageFlags         DstStageMask,
	VkDependencyFlags            DependencyFlags,
	uint32_t                     MemoryBarrierCount,
	const VkMemoryBarrier*		 MemoryBarriers,
	uint32_t                     BufferMemoryBarrierCount,
	const VkBufferMemoryBarrier* BufferMemoryBarriers,
	uint32_t                     ImageMemoryBarrierCount,
	const VkImageMemoryBarrier*  ImageMemoryBarriers)
{
	return vkCmdPipelineBarrier(Handle, SrcStageMask, DstStageMask, DependencyFlags, MemoryBarrierCount, MemoryBarriers, BufferMemoryBarrierCount, BufferMemoryBarriers, ImageMemoryBarrierCount, ImageMemoryBarriers);
}

void VulkanCommandBuffer::CmdPipelineBarrier2(const VkDependencyInfo* DependencyInfo)
{
	vkCmdPipelineBarrier2(Handle, DependencyInfo);
}

/*
	Render Pass
*/
void VulkanCommandBuffer::CmdBeginRenderPass(const VkRenderPassBeginInfo* RenderPassBegin, VkSubpassContents Contents)
{
	vkCmdBeginRenderPass(Handle, RenderPassBegin, Contents);
}

void VulkanCommandBuffer::CmdEndRenderPass()
{
	vkCmdEndRenderPass(Handle);
}

void VulkanCommandBuffer::CmdNextSubpass(VkSubpassContents Contents)
{
	vkCmdNextSubpass(Handle, Contents);
}

void VulkanCommandBuffer::CmdBeginRenderPass2(const VkRenderPassBeginInfo* RenderPassBegin, const VkSubpassBeginInfo* SubpassBeginInfo)
{
	vkCmdBeginRenderPass2(Handle, RenderPassBegin, SubpassBeginInfo);
}

void VulkanCommandBuffer::CmdEndRenderPass2(const VkSubpassEndInfo* SubpassEndInfo)
{
	vkCmdEndRenderPass2(Handle, SubpassEndInfo);
}

void VulkanCommandBuffer::CmdNextSubpass2(const VkSubpassBeginInfo* SubpassBeginInfo, const VkSubpassEndInfo* SubpassEndInfo)
{
	vkCmdNextSubpass2(Handle, SubpassBeginInfo, SubpassEndInfo);
}

// Provided by VK_KHR_dynamic_rendering
void VulkanCommandBuffer::CmdBeginRenderingKHR(const VkRenderingInfo* RenderingInfo)
{
	//vkCmdBeginRenderingKHR(Handle, RenderingInfo);
}

void VulkanCommandBuffer::CmdEndRenderingKHR()
{
	//vkCmdEndRenderingKHR(Handle);
}

void VulkanCommandBuffer::CmdBeginRenderPass2KHR(const VkRenderPassBeginInfo* RenderPassBegin, const VkSubpassBeginInfo* SubpassBeginInfo)
{
	//vkCmdBeginRenderPass2KHR(Handle, RenderPassBegin, SubpassBeginInfo);
}

void VulkanCommandBuffer::CmdEndRenderPass2KHR(const VkSubpassEndInfo* SubpassEndInfo)
{
	//vkCmdEndRenderPass2KHR(Handle, SubpassEndInfo);
}

void VulkanCommandBuffer::CmdNextSubpass2KHR(const VkSubpassBeginInfo* SubpassBeginInfo, const VkSubpassEndInfo* SubpassEndInfo)
{
	//vkCmdNextSubpass2KHR(Handle, SubpassBeginInfo, SubpassEndInfo);
}

/*
	Buffer
*/
void VulkanCommandBuffer::CmdFillBuffer(VkBuffer DstBuffer,
	VkDeviceSize DstOffset,
	VkDeviceSize Size,
	std::uint32_t Data)
{
	vkCmdFillBuffer(Handle, DstBuffer, DstOffset, Size, Data);
}

void VulkanCommandBuffer::CmdUpdateBuffer(VkBuffer DstBuffer,
	VkDeviceSize DstOffset,
	VkDeviceSize DataSize,
	const void* Data)
{
	vkCmdUpdateBuffer(Handle, DstBuffer, DstOffset, DataSize, Data);
}

void VulkanCommandBuffer::CmdCopyBuffer(VkBuffer SrcBuffer,
	VkBuffer DstBuffer,
	std::uint32_t RegionCount,
	const VkBufferCopy* Regions)
{
	vkCmdCopyBuffer(Handle, SrcBuffer, DstBuffer, RegionCount, Regions);
}

void VulkanCommandBuffer::CmdCopyBuffer2(const VkCopyBufferInfo2* CopyBufferInfo)
{
	vkCmdCopyBuffer2(Handle, CopyBufferInfo);
}

void VulkanCommandBuffer::CmdCopyBufferToImage(VkBuffer SrcBuffer,
	VkImage DstImage,
	VkImageLayout DstImageLayout,
	std::uint32_t RegionCount,
	const VkBufferImageCopy* Regions)
{
	vkCmdCopyBufferToImage(Handle, SrcBuffer, DstImage, DstImageLayout, RegionCount, Regions);
}

void VulkanCommandBuffer::CmdCopyBufferToImage2(const VkCopyBufferToImageInfo2* CopyBufferToImageInfo)
{
	vkCmdCopyBufferToImage2(Handle, CopyBufferToImageInfo);
}

/*
	Image
*/
void VulkanCommandBuffer::CmdClearColorImage(VkImage Image,
	VkImageLayout ImageLayout,
	const VkClearColorValue* Color,
	uint32_t RangeCount,
	const VkImageSubresourceRange* Ranges)
{
	vkCmdClearColorImage(Handle, Image, ImageLayout, Color, RangeCount, Ranges);
}

void VulkanCommandBuffer::CmdClearDepthStencilImage(VkImage Image,
	VkImageLayout ImageLayout,
	const VkClearDepthStencilValue* DepthStencil,
	std::uint32_t RangeCount,
	const VkImageSubresourceRange* Ranges)
{
	vkCmdClearDepthStencilImage(Handle, Image, ImageLayout, DepthStencil, RangeCount, Ranges);
}

void VulkanCommandBuffer::CmdClearAttachments(std::uint32_t AttachmentCount,
	const VkClearAttachment* Attachments,
	std::uint32_t RectCount,
	const VkClearRect* Rects)
{
	vkCmdClearAttachments(Handle, AttachmentCount, Attachments, RectCount, Rects);
}

void VulkanCommandBuffer::CmdCopyImage(VkImage SrcImage,
	VkImageLayout SrcImageLayout,
	VkImage DstImage,
	VkImageLayout DstImageLayout,
	std::uint32_t RegionCount,
	const VkImageCopy* Regions)
{
	vkCmdCopyImage(Handle, SrcImage, SrcImageLayout, DstImage, DstImageLayout, RegionCount, Regions);
}

void VulkanCommandBuffer::CmdCopyImage2(const VkCopyImageInfo2* CopyImageInfo)
{
	vkCmdCopyImage2(Handle, CopyImageInfo);
}

void VulkanCommandBuffer::CmdCopyImageToBuffer(VkImage SrcImage,
	VkImageLayout SrcImageLayout,
	VkBuffer DstBuffer,
	std::uint32_t RegionCount,
	const VkBufferImageCopy* Regions)
{
	vkCmdCopyImageToBuffer(Handle, SrcImage, SrcImageLayout, DstBuffer, RegionCount, Regions);
}

void VulkanCommandBuffer::CmdCopyImageToBuffer2(const VkCopyImageToBufferInfo2* CopyImageToBufferInfo)
{
	vkCmdCopyImageToBuffer2(Handle, CopyImageToBufferInfo);
}

void VulkanCommandBuffer::CmdBlitImage(VkImage SrcImage,
	VkImageLayout SrcImageLayout,
	VkImage DstImage,
	VkImageLayout DstImageLayout,
	std::uint32_t RegionCount,
	const VkImageBlit* Regions,
	VkFilter Filter)
{

}

void VulkanCommandBuffer::CmdBlitImage2(const VkBlitImageInfo2* BlitImageInfo)
{

}

void VulkanCommandBuffer::CmdResolveImage(VkImage SrcImage,
	VkImageLayout SrcImageLayout,
	VkImage DstImage,
	VkImageLayout DstImageLayout,
	std::uint32_t RegionCount,
	const VkImageResolve* Regions)
{
	vkCmdResolveImage(Handle, SrcImage, SrcImageLayout, DstImage, DstImageLayout, RegionCount, Regions);
}

void VulkanCommandBuffer::CmdResolveImage2(const VkResolveImageInfo2* ResolveImageInfo)
{
	vkCmdResolveImage2(Handle, ResolveImageInfo);
}

/*
	Draw Command
*/
void VulkanCommandBuffer::CmdDraw(std::uint32_t VertexCount,
								  std::uint32_t InstanceCount,
								  std::uint32_t FirstVertex,
								  std::uint32_t FirstInstance)
{
	vkCmdDraw(Handle, VertexCount, InstanceCount, FirstVertex, FirstInstance);
}

void VulkanCommandBuffer::CmdDrawIndexed(std::uint32_t IndexCount,
										 std::uint32_t InstanceCount,
										 std::uint32_t FirstIndex,
										 std::int32_t  VertexOffset,
										 std::uint32_t FirstInstance)
{
	vkCmdDrawIndexed(Handle, IndexCount, InstanceCount, FirstIndex, VertexOffset, FirstInstance);
}

void VulkanCommandBuffer::CmdDrawIndirect(VkBuffer Buffer,
										  VkDeviceSize Offset,
										  std::uint32_t DrawCount,
										  std::uint32_t Stride)
{
	vkCmdDrawIndirect(Handle, Buffer, Offset, DrawCount, Stride);
}

void VulkanCommandBuffer::CmdDrawIndexedIndirect(VkBuffer Buffer,
	VkDeviceSize Offset,
	std::uint32_t DrawCount,
	std::uint32_t Stride)
{
	vkCmdDrawIndexedIndirect(Handle, Buffer, Offset, DrawCount, Stride);
}

void VulkanCommandBuffer::CmdDispatch(std::uint32_t GroupCountX,
									  std::uint32_t GroupCountY,
									  std::uint32_t GroupCountZ)
{
	vkCmdDispatch(Handle, GroupCountX, GroupCountY, GroupCountZ);
}

/*
	Pipeline
*/
void VulkanCommandBuffer::CmdBindPipeline(VkPipelineBindPoint PipelineBindPoint,
	VkPipeline Pipeline)
{
	vkCmdBindPipeline(Handle, PipelineBindPoint, Pipeline);
}

void VulkanCommandBuffer::CmdBindDescriptorSets(VkPipelineBindPoint PipelineBindPoint,
	VkPipelineLayout Layout,
	std::uint32_t FirstSet,
	std::uint32_t DescriptorSetCount,
	const VkDescriptorSet* DescriptorSets,
	std::uint32_t DynamicOffsetCount,
	const std::uint32_t* DynamicOffsets)
{
	vkCmdBindDescriptorSets(Handle, PipelineBindPoint, Layout, FirstSet, DescriptorSetCount, DescriptorSets, DynamicOffsetCount, DynamicOffsets);
}

/* Depth Test */
void VulkanCommandBuffer::CmdSetDepthTestEnable(VkBool32 DepthTestEnable)
{
	vkCmdSetDepthTestEnable(Handle, DepthTestEnable);
}

void VulkanCommandBuffer::CmdSetDepthCompareOp(VkCompareOp DepthCompareOp)
{
	vkCmdSetDepthCompareOp(Handle, DepthCompareOp);
}

void VulkanCommandBuffer::CmdSetDepthWriteEnable(VkBool32 DepthWriteEnable)
{
	vkCmdSetDepthWriteEnable(Handle, DepthWriteEnable);
}

void VulkanCommandBuffer::CmdSetDepthBoundsTestEnable(VkBool32 DepthBoundsTestEnable)
{
	vkCmdSetDepthBoundsTestEnable(Handle, DepthBoundsTestEnable);
}

void VulkanCommandBuffer::CmdSetDepthBounds(float MinDepthBounds, float MaxDepthBounds)
{
	vkCmdSetDepthBounds(Handle, MinDepthBounds, MaxDepthBounds);
}

void VulkanCommandBuffer::CmdSetStencilTestEnable(VkBool32 StencilTestEnable)
{
	vkCmdSetStencilTestEnable(Handle, StencilTestEnable);
}

/* Scissor Test */
void VulkanCommandBuffer::CmdSetScissor(std::uint32_t FirstScissor,
				   std::uint32_t ScissorCount,
				   const VkRect2D* Scissors)
{
	vkCmdSetScissor(Handle, FirstScissor, ScissorCount, Scissors);
}

void VulkanCommandBuffer::CmdSetScissorWithCount(std::uint32_t ScissorCount, const VkRect2D* Scissors)
{
	vkCmdSetScissorWithCount(Handle, ScissorCount, Scissors);
}

/* Rasterizer */
void VulkanCommandBuffer::CmdSetCullMode(VkCullModeFlags RHICullMode)
{

}

void VulkanCommandBuffer::CmdSetFrontFace(VkFrontFace RHIFrontFace)
{

}

/* Viewport */
void VulkanCommandBuffer::CmdSetViewport(std::uint32_t FirstViewport,
	std::uint32_t ViewportCount,
	const VkViewport* Viewports)
{
	vkCmdSetViewport(Handle, FirstViewport, ViewportCount, Viewports);
}

/* 绑定VBO */
void VulkanCommandBuffer::CmdBindVertexBuffers(std::uint32_t FirstBinding,
	std::uint32_t BindingCount,
	const VkBuffer* Buffers,
	const VkDeviceSize* Offsets)
{
	vkCmdBindVertexBuffers(Handle, FirstBinding, BindingCount, Buffers, Offsets);
}

/* 绑定EBO */
void VulkanCommandBuffer::CmdBindIndexBuffer(VkBuffer Buffer,
	VkDeviceSize Offset,
	VkIndexType IndexType)
{
	vkCmdBindIndexBuffer(Handle, Buffer, Offset, IndexType);
}
