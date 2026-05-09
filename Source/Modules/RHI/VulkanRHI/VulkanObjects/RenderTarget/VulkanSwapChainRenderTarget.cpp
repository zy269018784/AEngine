#include "VulkanSwapChainRenderTarget.h"
#include "VulkanRHI/VulkanObjects/SwapChain/VulkanSwapChain.h"
#include "VulkanRHI/VulkanObjects/Surface/VulkanSurface.h"
#include "VulkanRHI/VulkanObjects/Device/VulkanDevice.h"
#include "VulkanRHI/VulkanObjects/FrameBuffer/VulkanFrameBuffer.h"
#include "VulkanRHI/VulkanObjects/RenderPass/VulkanRenderPass.h"
#include "VulkanRHI/VulkanObjects/Window/VulkanFrame.h"
#include "VulkanRHI/VulkanObjects/CommandBuffer/VulkanCommandBuffer.h"
#include "VulkanRHI/VulkanObjects/FrameBuffer/VulkanAttachment.h"
#include "VulkanRHI/VulkanObjects/FrameBuffer/VulkanDepthAttachment.h"
#include "VulkanRHI/VulkanObjects/FrameBuffer/VulkanColorAttachment.h"
#include "VulkanRHI/VulkanObjects/Queue/VulkanQueue.h"
#include "VulkanRHI/VulkanObjects/Core/VulkanCore.h"
#include "VulkanRHI/VulkanObjects/Texture/VulkanTexture.h"
#include "VulkanRHI/VulkanObjects/Resource/VulkanImageView.h"
#include "RHI/RHIObjects/RenderTarget/RHIRenderTarget.h"
#include "RHI/RHIObjects/Core/RHICore.h"
#include <iostream>
#include <numbers>
#if 0
VulkanSwapChainRenderTarget::VulkanSwapChainRenderTarget(VulkanSwapChain *InSwapChain, VulkanDevice *InDevice)
    : SwapChain(InSwapChain),  VulkanRenderTarget(ToRHIPixelFormat(InSwapChain->GetFormat()), InDevice)
{
    ImageFormat				= SwapChain->GetFormat();
	Resolution           = { SwapChain->GetWidth(), SwapChain->GetHeight() };

    ImageViews = SwapChain->GetImageViews();

	std::cout << "SwapChain->GetImageCount() " << SwapChain->GetImageCount() << std::endl;
	/*
		1. 同步对象
	*/
	Frames.resize(SwapChain->GetImageCount());
    for (int i = 0; i < Frames.size(); i++)
        Frames[i] = new VulkanFrame(Device, true);

    /*
		2. 创建Render Pass
    */
	std::vector<RHIAttachment> InAttachments;
	InAttachments.emplace_back(RHIAttachment(RHIAttachmentType::Color1, RHIPixelFormat::PF_R8G8B8A8_UNORM));
	RenderPass = (RHIRenderPass *)new VulkanRenderPass(Device, ImageFormat, InAttachments, {RHIAttachmentType::DepthStencil, RHIPixelFormat::PF_R8G8B8A8_UNORM});

    /*
        3. 创建Frame Buffer
    */
    FrameBuffers.resize(ImageViews.size());
    for (int i = 0; i < FrameBuffers.size(); i++)
    {
    	VulkanTexture *Tex = new VulkanTexture(InDevice,
				RHITextureType::Texture2D,
				RHIPixelFormat::PF_DepthStencil,
				RHITextureUsageFlag::DepthStencilAttachment,
				RHIAttachmentType::DepthStencil,
				1,
				Resolution.width,
				Resolution.height,
				1,
				1);
    	Textures.emplace_back(Tex);

    	std::vector<VulkanAttachment> InVKAttachments;
		InVKAttachments.emplace_back(VulkanAttachment(RHIAttachmentType::Color1, RHIPixelFormat::PF_R8G8B8A8_UNORM, ImageViews[i]));
    	InVKAttachments.emplace_back(VulkanAttachment(RHIAttachmentType::DepthStencil, RHIPixelFormat::PF_R8G8B8A8_UNORM, Tex->ImageView->GetHandle()));

        FrameBuffers[i] = new VulkanFrameBuffer(Device, dynamic_cast<VulkanRenderPass *>(RenderPass), { Resolution.width, Resolution.height },  &InVKAttachments);
    }

	/*
		4. 创建command buffer
	 */
    GraphicsCommandBuffers.resize(SwapChain->GetImageCount());
    for (int i = 0; i < GraphicsCommandBuffers.size(); i++)
    {
        /*
            暂时用第0个Command Pool
        */
        GraphicsCommandBuffers[i] = Device->CreateCommandBuffer(Device->CommandPools[0]);
    }
}
#endif

VulkanSwapChainRenderTarget::VulkanSwapChainRenderTarget(VulkanDevice *InDevice, VulkanSurface* InSurface)
	: VulkanRenderTarget(ToRHIPixelFormat(InSurface->CurrentFormat.format), InDevice)
{
	SwapChain = new VulkanSwapChain(Device, InSurface);

	ImageFormat				= SwapChain->GetFormat();
	Resolution           = { SwapChain->GetWidth(), SwapChain->GetHeight() };



	ImageViews = SwapChain->GetImageViews();
	RHIPixelFormat SwapChainRHIPixelFormat = ToRHIPixelFormat(ImageFormat);
	std::cout << "VulkanSwapChainRenderTarget ImageFormat " << ImageFormat << " " << (int)SwapChainRHIPixelFormat << std::endl;

#if 1
	// AMD Radeon RX580 2048SP
	RHIDepthAttachmentType DepthStencilType = RHIDepthAttachmentType::DepthStencil_D32_S8;
	RHIPixelFormat  DepthStencilPixelFormat = RHIPixelFormat::PF_DepthStencil_D32_S8;
#else
	// 4060 support
	// AMD Radeon RX580 2048SP do not support
	RHIDepthAttachmentType DepthStencilType = RHIDepthAttachmentType::DepthStencil_D24_S8;
	RHIPixelFormat  DepthStencilPixelFormat = RHIPixelFormat::PF_DepthStencil_D24_S8;
#endif

	/*
		1. 同步对象
	*/
	Frames.resize(SwapChain->GetImageCount());
	for (int i = 0; i < Frames.size(); i++)
		Frames[i] = new VulkanFrame(Device, true);

	/*
		2. 创建Render Pass
	*/
	std::vector<RHIColorAttachment> ColorAttachments;
	ColorAttachments.emplace_back(RHIColorAttachment(RHIAttachmentType::Color1, SwapChainRHIPixelFormat));

	RHIDepthAttachment DepthAttachment(DepthStencilType);
	RenderPass = new VulkanRenderPass(Device, ImageFormat, ColorAttachments,DepthAttachment);

	/*
		3. 创建Frame Buffer
	*/

	FrameBuffers.resize(ImageViews.size());
	//SwapChain->FrameBuffers.resize(SwapChain->SwapChainImageViews.size());
	for (int i = 0; i < FrameBuffers.size(); i++)
	{
		VulkanTexture *Tex = new VulkanTexture(InDevice,
				RHITextureType::Texture2D,
				DepthStencilPixelFormat,
				RHITextureUsageFlag::DepthStencilAttachment,
				1,
				Resolution.width,
				Resolution.height,
				1,
				1);
		Textures.emplace_back(Tex);

		std::vector<RHIColorAttachment *> InColorAttachments;
		InColorAttachments.emplace_back(new VulkanColorAttachment(ImageViews[i], RHIAttachmentType::Color1, SwapChainRHIPixelFormat));

		std::vector<RHIDepthAttachment *> InDepthAttachments;
		InDepthAttachments.emplace_back(new VulkanDepthAttachment(Tex->ImageView->GetHandle(), DepthStencilType));

		FrameBuffers[i] = new VulkanFrameBuffer(Device, dynamic_cast<VulkanRenderPass *>(RenderPass),
								{ Resolution.width, Resolution.height },
												InColorAttachments, InDepthAttachments);
	}

	/*
		4. 创建command buffer
	 */
	GraphicsCommandBuffers.resize(SwapChain->GetImageCount());
	for (int i = 0; i < GraphicsCommandBuffers.size(); i++)
	{
		/*
			暂时用第0个Command Pool
		*/
		GraphicsCommandBuffers[i] = Device->CreateCommandBuffer(Device->CommandPools[0]);
	}
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
    if (SwapChain->AcquireNextImageKHR(UINT64_MAX, SwapchainImageAvailableSemaphore, VK_NULL_HANDLE, &CurrentImageIndex) != VK_SUCCESS)
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
	auto ret = Device->Queues[0]->QueueSubmit(1, &SubmitInfo, Fence);
	if (VK_SUCCESS != ret)
	{
		std::cout << "ret " << ret << std::endl;
		throw std::runtime_error("failed to submit draw command buffer!");
	}

	VkSwapchainKHR SwapChains[] = { SwapChain->GetHandle() };

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
	vkQueuePresentKHR(Device->PresentQueue, &PresentInfo);
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
    //VkClearValue ClearColor = { {{0.0f, 0.0f, 0.0f, 1.0f}} };
    VkClearValue ClearColor[2];
    ClearColor[0].color = {{0.0f, 0.0f, 0.0f, 1.0f}};
    ClearColor[1].depthStencil = {1.0f, 0};  // 深度清除为1.0（最远值

    VkRenderPassBeginInfo RenderPassInfo{};
    RenderPassInfo.sType				= VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    RenderPassInfo.renderPass			= (dynamic_cast<VulkanRenderPass *>(RenderPass))->GetHandle();
    RenderPassInfo.framebuffer			= FrameBuffers[CurrentImageIndex]->GetHandle();
    RenderPassInfo.renderArea.offset	= { 0, 0 };
    RenderPassInfo.renderArea.extent	= Resolution;
    RenderPassInfo.clearValueCount		= 2;
    RenderPassInfo.pClearValues			= ClearColor;

    dynamic_cast<VulkanCommandBuffer *>(GraphicsCommandBuffers[CurrentImageIndex])->CmdBeginRenderPass(&RenderPassInfo, VK_SUBPASS_CONTENTS_INLINE);
}

void VulkanSwapChainRenderTarget::RHIEndRenderPass()
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
	SwapChain->Resize(Width, Height);
}