#include "VulkanSwapChainRenderTarget.h"
#include "VulkanRHI/VulkanObjects/SwapChain/VulkanSwapChain.h"
#include "VulkanRHI/VulkanObjects/Surface/VulkanSurface.h"
#include "VulkanRHI/VulkanObjects/Device/VulkanDevice.h"
#include "VulkanRHI/VulkanObjects/Framebuffer/VulkanFrameBuffer.h"
#include "VulkanRHI/VulkanObjects/RenderPass/VulkanRenderPass.h"
#include "VulkanRHI/VulkanObjects/Window/VulkanFrame.h"
#include "VulkanRHI/VulkanObjects/CommandBuffer/VulkanCommandBuffer.h"
#include "VulkanRHI/VulkanObjects/Framebuffer/VulkanAttachment.h"
#include "VulkanRHI/VulkanObjects/Queue/VulkanQueue.h"
#include "VulkanRHI/VulkanObjects/Core/VulkanCore.h"
#include "VulkanRHI/VulkanObjects/Texture/VulkanTexture.h"
#include "VulkanRHI/VulkanObjects/Resource/VulkanImageView.h"
#include "VulkanRHI/VulkanObjects/Surface/VulkanSurface.h"

#include "RHI/RHIObjects/RenderTarget/RHIRenderTarget.h"
#include "RHI/RHIObjects/FrameBuffer/RHIAttachment.h"
#include "RHI/RHIObjects/Device/RHIDevice.h"
#include "RHI/RHIObjects/Core/RHICore.h"
#include <iostream>
#include <numbers>

VulkanSwapChainRenderTarget::VulkanSwapChainRenderTarget(VulkanDevice *InDevice, VulkanSurface* InSurface)
	//: VulkanRenderTarget(ToRHIPixelFormat(InSurface->CurrentFormat.format), InDevice)
	: RHISwapChainRenderTarget(InDevice, InSurface->GetWidth(), InSurface->GetHeight(), InSurface->GetRHIPixelFormat())
{
	/*
	 * 创建交换链
	 */
	SwapChain = new VulkanSwapChain(InDevice, InSurface);


	/*
		1. 同步对象
	*/
	Frames.resize(dynamic_cast<VulkanSwapChain *>(SwapChain)->GetImageCount());
	for (int i = 0; i < Frames.size(); i++)
		Frames[i] = new VulkanFrame(dynamic_cast<VulkanDevice *>(Device), true);

	ImageViews = dynamic_cast<VulkanSwapChain *>(SwapChain)->GetImageViews();
}

VulkanSwapChainRenderTarget::~VulkanSwapChainRenderTarget()
{
	for (int i = 0; i < Textures.size(); i++)
		delete Textures[i];

	for (int i = 0; i < Frames.size(); i++)
		delete Frames[i];

	delete SwapChain;
}

/*
	3个image:
		计算中
		计算完成
		呈现
	2个CommandBuffer:
	2个Frame:

	初始状态:
		Fence[0] unsignaled
		Fence[1] signaled
		Current Frame = 1
		LastImageIndex = 2
	第1帧:
		Fence[2] wait
		GraphicsCommandBuffers[0];
	Begin Frame
*/
void VulkanSwapChainRenderTarget::RHIBeginFrame()
{
	//std::cout << "Frame Index " << FrameIndex << " " << Frames.size() << std::endl;
    VulkanFrame* Frame = Frames[FrameIndex];
    /*
		等待QueueSubmit把Frames[FrameIndex]->ImageFence变为signaled状态)
		Frames[FrameIndex]->ImageFence：   			 		signaled   ->  unsignaled
    */
    Frame->ImageFence->Wait();
	/*
	 *  Frames[FrameIndex]->ImageFence：   			 		signaled   ->  unsignaled
	 */
    Frame->ImageFence->Reset();
    VkSemaphore SwapchainImageAvailableSemaphore = Frame->ImageAvailableSemaphore->GetHandle();
    /*
        acquire next image
		Frames[FrameIndex]->ImageAvailableSemaphore: 		unsignaled ->  signaled
    */
    if (dynamic_cast<VulkanSwapChain *>(SwapChain)->AcquireNextImageKHR(UINT64_MAX, SwapchainImageAvailableSemaphore, VK_NULL_HANDLE, &CurrentImageIndex) != VK_SUCCESS)
    {
        throw std::runtime_error("failed to acquire next image\n");
    }
	//std::cout << "Frame Index " << FrameIndex << " CurrentImageIndex " << CurrentImageIndex << std::endl;

    /*
        current command buffer
    */
    VulkanCommandBuffer* CommandBuffer = dynamic_cast<VulkanCommandBuffer *>(GraphicsCommandBuffers[FrameIndex]);
    /*
        reset command buffer
    */
    if (CommandBuffer->ResetCommandBuffer(0) != VK_SUCCESS)
    {
        throw std::runtime_error("failed to reset command buffer!");
    }

    /*
        begin recording a command buffer,
    */
    VkCommandBufferBeginInfo BeginInfo{};
    BeginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    if (CommandBuffer->BeginCommandBuffer(&BeginInfo) != VK_SUCCESS)
    {
        throw std::runtime_error("failed to begin recording command buffer!");
    }
}

void VulkanSwapChainRenderTarget::RHIEndFrame()
{

	/*
		current frame's command buffer
	*/
	VulkanCommandBuffer* CommandBuffer = dynamic_cast<VulkanCommandBuffer *>(GraphicsCommandBuffers[FrameIndex]);
	VkCommandBuffer CommandBufferHandle = CommandBuffer->GetHandle();
	/*
		complete recording of a command buffer
	*/
	if (CommandBuffer->EndCommandBuffer() != VK_SUCCESS)
	{
		throw std::runtime_error("failed to record command buffer!");
	}
	/*
		等待上一帧Image有空
	*/
	VkSemaphore SwapchainImageAvailableSemaphore	= Frames[FrameIndex]->ImageAvailableSemaphore->GetHandle();
	VkSemaphore SwapchainImageDrawFinishedSemaphore = Frames[FrameIndex]->ImageDrawFinishedSemaphore->GetHandle();
	VkFence Fence								    = Frames[FrameIndex]->ImageFence->GetHandle();
	VkPipelineStageFlags WaitStages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };

	/*
		Frames[FrameIndex]->ImageAvailableSemaphore: 		signaled   ->  unsignaled
		Frames[FrameIndex]->ImageDrawFinishedSemaphore:		unsignaled ->  signaled
		Frames[FrameIndex]->ImageFence：   			 		unsignaled ->  signaled
	*/;
	VkSubmitInfo SubmitInfo{};
	SubmitInfo.sType				= VK_STRUCTURE_TYPE_SUBMIT_INFO;
	SubmitInfo.waitSemaphoreCount	= 1;
	SubmitInfo.pWaitSemaphores		= &SwapchainImageAvailableSemaphore;
	SubmitInfo.pWaitDstStageMask	= WaitStages;
	SubmitInfo.commandBufferCount	= 1;
	SubmitInfo.pCommandBuffers		= &CommandBufferHandle;
	SubmitInfo.signalSemaphoreCount = 1;
	SubmitInfo.pSignalSemaphores	= &SwapchainImageDrawFinishedSemaphore;
	auto ret = dynamic_cast<VulkanDevice *>(Device)->Queues[0]->QueueSubmit(1, &SubmitInfo, Fence);
	if (VK_SUCCESS != ret)
	{
		std::cout << "ret " << ret << std::endl;
		throw std::runtime_error("failed to submit draw command buffer!");
	}

	VkSwapchainKHR SwapChains[] = { dynamic_cast<VulkanSwapChain *>(SwapChain)->GetHandle() };

	/*
		Frames[FrameIndex]->ImageDrawFinishedSemaphore:		signaled    ->  unsignaled
	*/
	VkPresentInfoKHR PresentInfo{};
	PresentInfo.sType				= VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
	PresentInfo.waitSemaphoreCount	= 1;
	PresentInfo.pWaitSemaphores		= &SwapchainImageDrawFinishedSemaphore;
	PresentInfo.swapchainCount		= 1;
	PresentInfo.pSwapchains			= SwapChains;
	PresentInfo.pImageIndices		= &CurrentImageIndex;
	vkQueuePresentKHR(dynamic_cast<VulkanDevice *>(Device)->PresentQueue, &PresentInfo);
	/*
		更新上一帧索引
	*/
	//LastImageIndex = CurrentImageIndex;
	/*
		当前帧
	*/
	FrameIndex = (FrameIndex + 1) % Frames.size();
}

void VulkanSwapChainRenderTarget::RHIBeginRenderPass()
{
    VkClearValue ClearColor[2];
    ClearColor[0].color = {{0.0f, 0.0f, 0.0f, 1.0f}};
    ClearColor[1].depthStencil = {1.0f, 0};  // 深度清除为1.0（最远值

    VkRenderPassBeginInfo RenderPassInfo{};
    RenderPassInfo.sType				= VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    RenderPassInfo.renderPass			= (dynamic_cast<VulkanRenderPass *>(RenderPass))->GetHandle();
    RenderPassInfo.framebuffer			= FrameBuffers[CurrentImageIndex]->GetHandle();
    RenderPassInfo.renderArea.offset	= { 0, 0 };
    RenderPassInfo.renderArea.extent	= { SwapChain->GetWidth(), SwapChain->GetHeight() };
    RenderPassInfo.clearValueCount		= 2;
    RenderPassInfo.pClearValues			= ClearColor;

    dynamic_cast<VulkanCommandBuffer *>(GraphicsCommandBuffers[CurrentImageIndex])->CmdBeginRenderPass(&RenderPassInfo, VK_SUBPASS_CONTENTS_INLINE);
}

void VulkanSwapChainRenderTarget::RHIEndRenderPass()
{
    dynamic_cast<VulkanCommandBuffer *>(GraphicsCommandBuffers[CurrentImageIndex])->CmdEndRenderPass();
}

void VulkanSwapChainRenderTarget::RHIBeginRenderPass2()
{
	// ============================================================================
	// 1. 准备 VkClearValue 数组
	// ============================================================================
	VkClearValue ClearColor[2];
	ClearColor[0].color = {{0.0f, 0.0f, 0.0f, 1.0f}};      // 颜色清除值
	ClearColor[1].depthStencil = {1.0f, 0};                // 深度清除为1.0（最远值），模板为0

	// ============================================================================
	// 2. 准备 VkRenderPassBeginInfo (用于 vkCmdBeginRenderPass)
	// ============================================================================
	VkRenderPassBeginInfo RenderPassInfo{};
	RenderPassInfo.sType                    = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
	RenderPassInfo.pNext                    = nullptr;
	RenderPassInfo.renderPass               = (dynamic_cast<VulkanRenderPass *>(RenderPass))->GetHandle();
	RenderPassInfo.framebuffer              = FrameBuffers[CurrentImageIndex]->GetHandle();
	RenderPassInfo.renderArea.offset        = { 0, 0 };
	RenderPassInfo.renderArea.extent        = { SwapChain->GetWidth(), SwapChain->GetHeight() };
	RenderPassInfo.clearValueCount          = 2;
	RenderPassInfo.pClearValues             = ClearColor;

	VkSubpassBeginInfo SubpassBeginInfo{};
	SubpassBeginInfo.sType = VK_STRUCTURE_TYPE_SUBPASS_BEGIN_INFO;
	SubpassBeginInfo.pNext = nullptr;
	SubpassBeginInfo.contents = VK_SUBPASS_CONTENTS_INLINE;

	dynamic_cast<VulkanCommandBuffer *>(GraphicsCommandBuffers[CurrentImageIndex])->CmdBeginRenderPass2(&RenderPassInfo, &SubpassBeginInfo);
}

void VulkanSwapChainRenderTarget::RHIEndRenderPass2()
{
	dynamic_cast<VulkanCommandBuffer *>(GraphicsCommandBuffers[CurrentImageIndex])->CmdEndRenderPass();
}

void VulkanSwapChainRenderTarget::GetExtent(float &x, float &y, float &w, float &h)
{
	x = y = 0;
	w = SwapChain->GetWidth();
	h = SwapChain->GetHeight();
}

void VulkanSwapChainRenderTarget::Resize(float Width, float Height) {
	dynamic_cast<VulkanSwapChain *>(SwapChain)->Resize(Width, Height);
}

void VulkanSwapChainRenderTarget::WaitDeviceIdle()
{
	dynamic_cast<VulkanDevice *>(Device)->DeviceWaitIdle();
}

void VulkanSwapChainRenderTarget::CreateFramebuffer()
{
	RHIPixelFormat SwapChainRHIPixelFormat = SwapChain->GetRHIPixelFormat();
	/*
		3. 创建Frame Buffer
	*/

	FrameBuffers.resize(ImageViews.size());
	for (int i = 0; i < FrameBuffers.size(); i++)
	{
		VulkanTexture *Tex = new VulkanTexture(dynamic_cast<VulkanDevice *>(Device),
				RHITextureType::Texture2D,
				DepthStencilPixelFormat,
				RHITextureUsageFlag::DepthStencilAttachment,
				RHIImageLayout::RHI_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL,
				1,
				SwapChain->GetWidth(),
				SwapChain->GetHeight(),
				1,
				1);
		Textures.emplace_back(Tex);

		std::vector<RHIAttachment *> InColorAttachments;
		InColorAttachments.emplace_back(new VulkanAttachment(RHIAttachmentType::Color1, SwapChainRHIPixelFormat, ImageViews[i],
		RHIAttachmentLoadOp::RHI_ATTACHMENT_LOAD_OP_CLEAR, RHIAttachmentStoreOp::RHI_ATTACHMENT_STORE_OP_STORE,
		RHIAttachmentLoadOp::RHI_ATTACHMENT_LOAD_OP_LOAD, RHIAttachmentStoreOp::RHI_ATTACHMENT_STORE_OP_STORE,
		RHIImageLayout::RHI_IMAGE_LAYOUT_UNDEFINED, RHIImageLayout::RHI_IMAGE_LAYOUT_PRESENT_SRC_KHR));

		std::vector<RHIAttachment *> InDepthAttachments;
		InDepthAttachments.emplace_back(new VulkanAttachment(DepthStencilType, DepthStencilPixelFormat, Tex->ImageView->GetHandle(),
		RHIAttachmentLoadOp::RHI_ATTACHMENT_LOAD_OP_LOAD, RHIAttachmentStoreOp::RHI_ATTACHMENT_STORE_OP_STORE,
		RHIAttachmentLoadOp::RHI_ATTACHMENT_LOAD_OP_LOAD, RHIAttachmentStoreOp::RHI_ATTACHMENT_STORE_OP_STORE,
		RHIImageLayout::RHI_IMAGE_LAYOUT_UNDEFINED, RHIImageLayout::RHI_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL));

		FrameBuffers[i] = new VulkanFrameBuffer(dynamic_cast<VulkanDevice *>(Device), dynamic_cast<VulkanRenderPass *>(RenderPass),
								{ SwapChain->GetWidth(), SwapChain->GetHeight() },
												InColorAttachments, InDepthAttachments);
	}

}

void VulkanSwapChainRenderTarget::CreateRenderPass()
{
	RHIPixelFormat SwapChainRHIPixelFormat = SwapChain->GetRHIPixelFormat();

	//VkFormat ImageFormat	= dynamic_cast<VulkanSwapChain *>(SwapChain)->GetFormat();
	/*
		2. 创建Render Pass
	*/
	std::vector<RHIAttachment *> ColorAttachments;
	ColorAttachments.emplace_back(new RHIAttachment(RHIAttachmentType::Color1, SwapChainRHIPixelFormat,
			RHIAttachmentLoadOp::RHI_ATTACHMENT_LOAD_OP_CLEAR, RHIAttachmentStoreOp::RHI_ATTACHMENT_STORE_OP_STORE,
			RHIAttachmentLoadOp::RHI_ATTACHMENT_LOAD_OP_CLEAR, RHIAttachmentStoreOp::RHI_ATTACHMENT_STORE_OP_STORE,
			RHIImageLayout::RHI_IMAGE_LAYOUT_UNDEFINED, RHIImageLayout::RHI_IMAGE_LAYOUT_PRESENT_SRC_KHR));

	std::vector<RHIAttachment *> DepthAttachments;
	DepthAttachments.emplace_back(new RHIAttachment(DepthStencilType, nullptr,
			RHIAttachmentLoadOp::RHI_ATTACHMENT_LOAD_OP_CLEAR, RHIAttachmentStoreOp::RHI_ATTACHMENT_STORE_OP_STORE,
			RHIAttachmentLoadOp::RHI_ATTACHMENT_LOAD_OP_CLEAR, RHIAttachmentStoreOp::RHI_ATTACHMENT_STORE_OP_STORE,
			RHIImageLayout::RHI_IMAGE_LAYOUT_UNDEFINED, RHIImageLayout::RHI_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL));
	/*
	 * 颜色附件索引
	 */
	std::vector< std::uint32_t> ColorAttachmentIndex;
	ColorAttachmentIndex.emplace_back(0);
	std::uint32_t InDepthAttachmentIndex = ColorAttachmentIndex.size();
	std::vector<RHISubPass *> SubPass;
	SubPass.push_back(new RHISubPass(ColorAttachmentIndex, InDepthAttachmentIndex));
	RenderPass = new VulkanRenderPass(dynamic_cast<VulkanDevice *>(Device), ColorAttachments,DepthAttachments, SubPass);
	RenderPass->Create();
}

void VulkanSwapChainRenderTarget::CreateCommandbuffer()
{
	/*
		4. 创建command buffer
	 */
	GraphicsCommandBuffers.resize(dynamic_cast<VulkanSwapChain *>(SwapChain)->GetImageCount());
	for (int i = 0; i < GraphicsCommandBuffers.size(); i++)
	{
		/*
			暂时用第0个Command Pool
		*/
		GraphicsCommandBuffers[i] = dynamic_cast<VulkanDevice *>(Device)->CreateCommandBuffer(dynamic_cast<VulkanDevice *>(Device)->CommandPools[0]);
	}
}