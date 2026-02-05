#include "VulkanSwapChainRenderTarget.h"
#include "VulkanObjects/SwapChain/VulkanSwapChain.h"
#include "VulkanObjects/Surface/VulkanSurface.h"
#include "VulkanObjects/Device/VulkanDevice.h"
#include "VulkanObjects/FrameBuffer/VulkanFrameBuffer.h"
#include "VulkanObjects/RenderPass/VulkanRenderPass.h"
#include "VulkanObjects/Window/VulkanFrame.h"
#include "VulkanObjects/CommandBuffer/VulkanCommandBuffer.h"
#include "VulkanObjects/Device/VulkanDevice.h"
#include "VulkanObjects/Queue/VulkanQueue.h"
#include <iostream>

VulkanSwapChainRenderTarget::VulkanSwapChainRenderTarget(VulkanDevice *InDevice, VulkanSurface* InSurface)
    : Device(InDevice), Surface(InSurface)
{
    SwapChain = new VulkanSwapChain(Device, Surface);

    ImageFormat    = Surface->CurrentFormat.format;
    SwapChainClorSpace      = Surface->CurrentFormat.colorSpace;
    Resolution              = Surface->CurrentExtent;
    SwapChainPresentMode    = Surface->CurrentPresentMode;

    ImageViews = SwapChain->SwapChainImageViews;

    Frames.resize(SwapChain->GetImageCount());
    for (int i = 0; i < Frames.size(); i++)
        Frames[i] = new VulkanFrame(Device, true);
#if 1
    /*
        创建Render Pass
    */
     RenderPass = new VulkanRenderPass(Device, ImageFormat);
     //SwapChain->RenderPass = RenderPass;
#else
     RenderPass = SwapChain->RenderPass;
#endif

#if 1
    /*
        创建Frame Buffer
    */
    std::cout << "SwapChainImageViews.size() " << SwapChain->SwapChainImageViews.size()  << std::endl;
    FrameBuffers.resize(SwapChain->SwapChainImageViews.size());
    //SwapChain->FrameBuffers.resize(SwapChain->SwapChainImageViews.size());
    for (int i = 0; i < FrameBuffers.size(); i++)
    {
        auto Handle = SwapChain->SwapChainImageViews[i];
        FrameBuffers[i] = new VulkanFrameBuffer(Device, RenderPass, { Resolution.width, Resolution.height }, Handle);
        //SwapChain->FrameBuffers[i] = FrameBuffers[i];
    }
#endif

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

}

void VulkanSwapChainRenderTarget::RHIBeginRenderPass()
{
    //VkClearValue ClearColor = { {{0.0f, 0.0f, 0.0f, 1.0f}} };
    VkClearValue ClearColor[2];
    ClearColor[0].color = {{0.0f, 0.0f, 0.0f, 1.0f}};
    ClearColor[1].depthStencil = {1.0f, 0};  // 深度清除为1.0（最远值

    VkRenderPassBeginInfo RenderPassInfo{};
    RenderPassInfo.sType				= VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    RenderPassInfo.renderPass			= RenderPass->GetHandle();
    RenderPassInfo.framebuffer			= FrameBuffers[CurrentImageIndex]->GetHandle();
    RenderPassInfo.renderArea.offset	= { 0, 0 };
    RenderPassInfo.renderArea.extent	= Resolution;
    RenderPassInfo.clearValueCount		= 2;
    RenderPassInfo.pClearValues			= ClearColor;

    GraphicsCommandBuffers[CurrentImageIndex]->CmdBeginRenderPass(&RenderPassInfo, VK_SUBPASS_CONTENTS_INLINE);
}

void VulkanSwapChainRenderTarget::RHIEndRenderPass()
{
    GraphicsCommandBuffers[CurrentImageIndex]->CmdEndRenderPass();
}

void VulkanSwapChainRenderTarget::RHIBeginFrame()
{
    //std::cout << "Frame Index " << FrameIndex << std::endl;
    VulkanFrame* Frame = Frames[FrameIndex];

    /*
        等待fence变为signaled(RHIEndFrame中QueueSubmit把该fence变为signaled状态)
    */
    Frame->ImageFence->Wait();
    Frame->ImageFence->Reset();

    //VkSemaphore SwapchainImageAvailableSemaphore = frameRes[LastImageIndex].SwapchainImageAvailableSemaphore->GetHandle();
    VkSemaphore SwapchainImageAvailableSemaphore = Frame->ImageAvailableSemaphore->GetHandle();
    /*
        acquire next image
        SwapchainImageAvailableSemaphore变为Signaled状态
    */
    if (SwapChain->AcquireNextImageKHR(UINT64_MAX, SwapchainImageAvailableSemaphore, VK_NULL_HANDLE, &CurrentImageIndex) != VK_SUCCESS)
    {
        throw std::runtime_error("failed to acquire next image\n");
    }

    /*
        current command buffer
    */
    VulkanCommandBuffer* CommandBuffer = GraphicsCommandBuffers[FrameIndex];
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
	VulkanCommandBuffer* CommandBuffer = GraphicsCommandBuffers[FrameIndex];
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
		提交到队列, signal fence
		等待SwapchainImageAvailableSemaphore变为Signaled状态
		command buffer执行完后, 将GraphicsPipelineCompleteSemaphore变为Signaled状态
	*/
	//std::cout << " Device->Queues[0] " << Device->Queues[0]->GetHandle() << std::endl;
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
		等待GraphicsPipelineCompleteSemaphore变为Signaled状态
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
	FrameIndex = (FrameIndex + 1) % 3;
}