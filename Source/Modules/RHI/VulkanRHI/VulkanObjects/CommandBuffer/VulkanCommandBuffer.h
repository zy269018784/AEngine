#pragma once
#include "Vulkan.h"
#include "VulkanObjects/Device/VulkanDevice.h"

#include "RHIObjects/Core/RHIViewport.h"
#include "RHIObjects/CommandBuffer/RHICommandBuffer.h"

#include <cstdint>

class VulkanCommandPool;
class VulkanCommandBuffer : public RHICommandBuffer
{;
public:
	VulkanCommandBuffer(VulkanDevice* InDevice, VulkanCommandPool* InCommandPool);
	~VulkanCommandBuffer();
	VkCommandBuffer GetHandle();
public:
	/*
		Begine Single Time
	*/
	VkResult BeginSingleTime();
public:
	/*
		RHI API
	*/
	// draw primitive
	virtual void RHIDrawPrimitive(std::uint32_t VertexCount, std::uint32_t InstanceCount = 1, std::uint32_t FirstVertex = 0, std::uint32_t FirstInstance = 0)  final override;
	// draw indexed primitive
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
		Vulkan API Wrapper
	*/
	/*
		Command Buffer
	*/	
	VkResult BeginCommandBuffer(const VkCommandBufferBeginInfo* BeginInfo);
	VkResult EndCommandBuffer();
	VkResult ResetCommandBuffer(VkCommandBufferResetFlags Flags);

	/*
		Pipeline Barrier
	*/
	void CmdPipelineBarrier(VkPipelineStageFlags		 SrcStageMask,
							VkPipelineStageFlags         DstStageMask,
							VkDependencyFlags            DependencyFlags,
							uint32_t                     MemoryBarrierCount,
							const VkMemoryBarrier*		 MemoryBarriers,
							uint32_t                     bufferMemoryBarrierCount,
							const VkBufferMemoryBarrier* BufferMemoryBarriers,
							uint32_t                     imageMemoryBarrierCount,
							const VkImageMemoryBarrier*  ImageMemoryBarriers);
	void CmdPipelineBarrier2(const VkDependencyInfo* DependencyInfo);

	/*
		Render Pass
	*/
	void CmdBeginRenderPass(const VkRenderPassBeginInfo* RenderPassBegin, VkSubpassContents Contents);
	void CmdEndRenderPass();
	void CmdNextSubpass(VkSubpassContents Contents);
	void CmdBeginRenderPass2(const VkRenderPassBeginInfo* RenderPassBegin, const VkSubpassBeginInfo* SubpassBeginInfo);
	void CmdEndRenderPass2(const VkSubpassEndInfo* SubpassEndInfo);
	void CmdNextSubpass2(const VkSubpassBeginInfo* SubpassBeginInfo, const VkSubpassEndInfo* SubpassEndInfo);
	// Provided by VK_KHR_dynamic_rendering
	void CmdBeginRenderingKHR(const VkRenderingInfo* RenderingInfo);
	void CmdEndRenderingKHR();
	void CmdBeginRenderPass2KHR(const VkRenderPassBeginInfo* RenderPassBegin, const VkSubpassBeginInfo* SubpassBeginInfo);
	void CmdEndRenderPass2KHR(const VkSubpassEndInfo* SubpassEndInfo);
	void CmdNextSubpass2KHR(const VkSubpassBeginInfo* SubpassBeginInfo, const VkSubpassEndInfo* SubpassEndInfo);
	
	/*
		Buffer
	*/
	void CmdFillBuffer(VkBuffer DstBuffer,
		VkDeviceSize DstOffset,
		VkDeviceSize Size,
		std::uint32_t Data);

	void CmdUpdateBuffer(VkBuffer DstBuffer,
		VkDeviceSize DstOffset,
		VkDeviceSize DataSize,
		const void* Data);

	void CmdCopyBuffer(VkBuffer SrcBuffer,
		VkBuffer DstBuffer,
		std::uint32_t RegionCount,
		const VkBufferCopy* Regions);

	void CmdCopyBuffer2(const VkCopyBufferInfo2* CopyBufferInfo);
	
	void CmdCopyBufferToImage(VkBuffer SrcBuffer,
		VkImage DstImage,
		VkImageLayout DstImageLayout,
		std::uint32_t RegionCount,
		const VkBufferImageCopy* Regions);

	void CmdCopyBufferToImage2(const VkCopyBufferToImageInfo2* CopyBufferToImageInfo);

	/*
		Image
	*/
	void CmdClearColorImage(VkImage Image,
		VkImageLayout ImageLayout,
		const VkClearColorValue* Color,
		std::uint32_t RangeCount,
		const VkImageSubresourceRange* Ranges);

	void CmdClearDepthStencilImage(VkImage Image,
		VkImageLayout ImageLayout,
		const VkClearDepthStencilValue* DepthStencil,
		std::uint32_t RangeCount,
		const VkImageSubresourceRange* Ranges);

	void CmdClearAttachments(uint32_t AttachmentCount,
		const VkClearAttachment* Attachments,
		std::uint32_t RectCount,
		const VkClearRect* Rects);

	void CmdCopyImage(VkImage SrcImage,
		VkImageLayout SrcImageLayout,
		VkImage DstImage,
		VkImageLayout DstImageLayout,
		std::uint32_t RegionCount,
		const VkImageCopy* Regions);

	void CmdCopyImage2(const VkCopyImageInfo2* CopyImageInfo);

	void CmdCopyImageToBuffer(VkImage SrcImage,
		VkImageLayout SrcImageLayout,
		VkBuffer DstBuffer,
		std::uint32_t RegionCount,
		const VkBufferImageCopy* Regions);

	void CmdCopyImageToBuffer2(const VkCopyImageToBufferInfo2* CopyImageToBufferInfo);

	void CmdBlitImage(VkImage SrcImage,
		VkImageLayout SrcImageLayout,
		VkImage DstImage,
		VkImageLayout DstImageLayout,
		std::uint32_t RegionCount,
		const VkImageBlit* Regions,
		VkFilter Filter);

	void CmdBlitImage2(const VkBlitImageInfo2* BlitImageInfo);

	void CmdResolveImage(VkImage srcImage,
		VkImageLayout SrcImageLayout,
		VkImage DstImage,
		VkImageLayout DstImageLayout,
		std::uint32_t RegionCount,
		const VkImageResolve* Regions);

	void CmdResolveImage2(const VkResolveImageInfo2* ResolveImageInfo);

	/*
		Draw Command
	*/
	void CmdDraw(std::uint32_t VertexCount,
				 std::uint32_t InstanceCount,
				 std::uint32_t FirstVertex,
				 std::uint32_t FirstInstance);

	void CmdDrawIndexed(std::uint32_t IndexCount,
						std::uint32_t InstanceCount,
						std::uint32_t FirstIndex,
						std::int32_t  VertexOffset,
						std::uint32_t FirstInstance);

	void CmdDrawIndirect(VkBuffer Buffer,
						 VkDeviceSize Offset,
						 std::uint32_t DrawCount,
						 std::uint32_t Stride);

	void CmdDrawIndexedIndirect(VkBuffer Buffer,
							    VkDeviceSize Offset,
							    std::uint32_t DrawCount,
							    std::uint32_t Stride);
	
	void CmdDispatch(std::uint32_t GroupCountX,
					 std::uint32_t GroupCountY,
					 std::uint32_t GroupCountZ);

	/*
		Pipeline
	*/
	void CmdBindPipeline(VkPipelineBindPoint PipelineBindPoint,
						 VkPipeline Pipeline);

	void CmdBindDescriptorSets(VkPipelineBindPoint PipelineBindPoint,
							   VkPipelineLayout Layout,
							   std::uint32_t FirstSet,
							   std::uint32_t DescriptorSetCount,
							   const VkDescriptorSet* DescriptorSets,
							   std::uint32_t DynamicOffsetCount,
							   const std::uint32_t* DynamicOffsets);



	/* 
		Depth Test 
	*/
	void CmdSetDepthTestEnable(VkBool32 DepthTestEnable);

	void CmdSetDepthCompareOp(VkCompareOp DepthCompareOp);

	void CmdSetDepthWriteEnable(VkBool32 DepthWriteEnable);

	void CmdSetDepthBoundsTestEnable(VkBool32 DepthBoundsTestEnable);

	void CmdSetDepthBounds(float MinDepthBounds,float MaxDepthBounds);

	/*
		
	*/
	void CmdSetStencilTestEnable(VkBool32 StencilTestEnable);
	/* 
		Scissor Test 
	*/
	void CmdSetScissor(std::uint32_t FirstScissor,
					   std::uint32_t ScissorCount,
					   const VkRect2D* Scissors);

	void CmdSetScissorWithCount(std::uint32_t ScissorCount, const VkRect2D* Scissors);

	/* 
		Rasterizer
	*/
	void CmdSetCullMode(VkCullModeFlags RHICullMode);

	void CmdSetFrontFace(VkFrontFace RHIFrontFace);

	/* 
		Viewport 
	*/
	void CmdSetViewport(std::uint32_t FirstViewport,
						std::uint32_t ViewportCount,
						const VkViewport* Viewports);

	/* 
		绑定VBO 
	*/
	void CmdBindVertexBuffers(std::uint32_t FirstBinding,
		std::uint32_t BindingCount,
		const VkBuffer* Buffers,
		const VkDeviceSize* Offsets);

	/* 
		绑定EBO
	*/
	void CmdBindIndexBuffer(VkBuffer Buffer,
		VkDeviceSize Offset,
		VkIndexType IndexType);
private:
	VkCommandBuffer		Handle = VK_NULL_HANDLE;
	VulkanDevice*		Device = nullptr;
	VulkanCommandPool*	CommandPool = nullptr;
};
