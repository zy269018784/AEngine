#include "VulkanWindow.h"
#include "VulkanObjects/Queue/VulkanQueue.h"
#include "VulkanObjects/RenderPass/VulkanRenderPass.h"
#include "VulkanObjects/Window/VulkanFrame.h"
#include  <iostream>
#include  <stdexcept>

VulkanWindow::VulkanWindow(VulkanPhysicalDevice* InPhysicalDevice, VulkanDevice* InDevice, VulkanSurface* InSurface)
	: PhysicalDevice(InPhysicalDevice), Device(InDevice), Surface(InSurface)
{

}

VulkanWindow::~VulkanWindow()
{
	for (int i = 0; i < Frames.size(); i++)
		delete Frames[i];

	/*
		必须在Surface之前
		vkDestroySurfaceKHR(): called before its associated VkSwapchainKHR was destroyed.
		The Vulkan spec states: All VkSwapchainKHR objects created for surface must have been destroyed prior to destroying surface
		(https://vulkan.lunarg.com/doc/view/1.4.313.2/windows/antora/spec/latest/chapters/VK_KHR_surface/wsi.html#VUID-vkDestroySurfaceKHR-surface-01266)
	*/
	delete SwapChain;	
	
	//delete SwapChain->RenderPass;
	std::cout << "VulkanWindow::~VulkanWindow() delete Surface " << std::endl;
	delete Surface;
}

void VulkanWindow::GetExtent(float& x, float& y, float& w, float& h)
{
	x = y = 0;
	w = SwapChain->GetWidth();
	h = SwapChain->GetHeight();
}

RHICommandBuffer* VulkanWindow::CurrentGraphicsCommandBuffer()
{
	return GraphicsCommandBuffers[CurrentImageIndex];
}

/*
	
    std::vector<VkCommandBuffer> commandBuffers;			// 3 == swapChainImages.size()
	std::vector<VkFramebuffer> swapChainFramebuffers;		// 3 == swapChainImages.size()
    std::vector<VkSemaphore> imageAvailableSemaphores;		// 2
    std::vector<VkSemaphore> renderFinishedSemaphores;		// 2
    std::vector<VkFence> inFlightFences;					// 2
    std::vector<VkFence> imagesInFlight;					// 3 == swapChainImages.size()
    size_t currentFrame = 0; [0, 1]
	imageIndex: [0, 2]

		imagesInFlight[0] = NULL
	imagesInFlight[1] = NULL
	imagesInFlight[2] = NULL
	inFlightFences[0] signaled
	inFlightFences[1] signaled

Frame 0:
	currentFrame 	= 0
	imageIndex		= 0
	wait inFlightFences[0] 变为signaled
	imagesInFlight[0] == NULL
	imagesInFlight[0] = inFlightFences[0];

	reset inFlightFences[0] 变为unsignaled
	vkQueueSubmit 提交到commandBuffers[0], inFlightFences[0] 变为signaled (提交frame 0)

	imagesInFlight[0] = inFlightFences[0];	image 0
	imagesInFlight[1] = NULL
	imagesInFlight[2] = NULL
	inFlightFences[0] unsignaled			frame 0
	inFlightFences[1] signaled

Frame 1:
	currentFrame 	= 1
	imageIndex		= 1
	wait inFlightFences[1]变为signaled
	imagesInFlight[1] == NULL
	imagesInFlight[1] = inFlightFences[1];

	commandBuffers[0]

	reset inFlightFences[1] 变为unsignaled
	vkQueueSubmit 提交到commandBuffers[1], inFlightFences[1] 变为signaled (提交frame 1)

	imagesInFlight[0] = inFlightFences[0];
	imagesInFlight[1] = inFlightFences[1];	image 1
	imagesInFlight[2] = NULL
	inFlightFences[0] unsignaled
	inFlightFences[1] unsignaled 			frame 1

Frame 2:
	currentFrame 	= 0
	imageIndex		= 2
	wait inFlightFences[0]变为signaled (frame 0渲染完)
	imagesInFlight[2] == NULL
	imagesInFlight[2] = inFlightFences[0];

	reset inFlightFences[0] 变为unsignaled
	vkQueueSubmit 提交到commandBuffers[2], inFlightFences[0] 变为signaled (提交frame 2)

	imagesInFlight[0] = inFlightFences[0];
	imagesInFlight[1] = inFlightFences[1];
	imagesInFlight[2] = inFlightFences[0];	image 2
	inFlightFences[0] unsignaled		frame 2
	inFlightFences[1] unsignaled

Frame 3:
	currentFrame 	= 1
	imageIndex		= 0
	wait inFlightFences[1]变为signaled (frame 1渲染完)
	vkAcquireNextImageKHR (frame 0呈现完)
	imagesInFlight[0] != NULL
		wait imagesInFlight[0]变为signaled  (frame 2渲染完)
	imagesInFlight[0] = inFlightFences[1];

	reset inFlightFences[1] 变为unsignaled
	vkQueueSubmit 提交到commandBuffers[0], inFlightFences[1] 变为signaled	(提交frame 3)

	imagesInFlight[0] = inFlightFences[1];	image 0
	imagesInFlight[1] = inFlightFences[1];
	imagesInFlight[2] = inFlightFences[0];
	inFlightFences[0] signaled
	inFlightFences[1] unsignaled		frame 3

Frame 4:
	currentFrame 	= 0
	imageIndex		= 1
	wait inFlightFences[0]变为signaled
	imagesInFlight[1] != NULL
		wait imagesInFlight[1]变为signaled (frame 3渲染完)
	imagesInFlight[1] = inFlightFences[0];

	reset inFlightFences[0] 变为unsignaled
	vkQueueSubmit 提交到commandBuffers[1], inFlightFences[0] 变为signaled	(提交frame 4)

	imagesInFlight[0] = inFlightFences[1];
	imagesInFlight[1] = inFlightFences[0];	image 1
	imagesInFlight[2] = inFlightFences[0];
	inFlightFences[0] unsignaled
	inFlightFences[1] signaled

Frame 5:
	currentFrame 	= 1
	imageIndex		= 2
	wait inFlightFences[1]变为signaled (frame 3渲染完)
	imagesInFlight[1] != NULL
		wait imagesInFlight[2]变为signaled (frame 4渲染完)
	imagesInFlight[2] = inFlightFences[1];

	reset inFlightFences[0] 变为unsignaled
	vkQueueSubmit 提交到commandBuffers[2], inFlightFences[1] 变为signaled	(提交frame 4)

	imagesInFlight[0] = inFlightFences[1];
	imagesInFlight[1] = inFlightFences[1];
	imagesInFlight[2] = inFlightFences[0];
	inFlightFences[0] signaled
	inFlightFences[1] unsignaled
7:

8:

*/

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
void VulkanWindow::RHIBeginFrame()
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

void VulkanWindow::RHIEndFrame()
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

void VulkanWindow::RHIBeginRenderPass()
{	
	
	VkClearValue ClearColor = { {{0.0f, 0.0f, 0.0f, 1.0f}} };


	VkRenderPassBeginInfo RenderPassInfo{};
	RenderPassInfo.sType				= VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
	RenderPassInfo.renderPass			= SwapChain->RenderPass->GetHandle();
	RenderPassInfo.framebuffer			= SwapChain->FrameBuffers[CurrentImageIndex]->GetHandle();
	RenderPassInfo.renderArea.offset	= { 0, 0 };
	RenderPassInfo.renderArea.extent	= { SwapChain->GetWidth(), SwapChain->GetHeight() };
	RenderPassInfo.clearValueCount		= 1;
	RenderPassInfo.pClearValues			= &ClearColor;

	GraphicsCommandBuffers[CurrentImageIndex]->CmdBeginRenderPass(&RenderPassInfo, VK_SUBPASS_CONTENTS_INLINE);
}

void VulkanWindow::RHIEndRenderPass()
{
	GraphicsCommandBuffers[CurrentImageIndex]->CmdEndRenderPass();
}

void VulkanWindow::Draw()
{

}

void VulkanWindow::WaitDeviceIdle()
{
	Device->DeviceWaitIdle();
}

/*
	Resize Swap Chain
		Resize Image View
	Resize Frame Buffer
*/
void VulkanWindow::Resize(float Width, float Height)
{
	//delete SwapChain;
	//delete RenderPass;
}

void VulkanWindow::CreateSwapChain()
{
	SwapChain = new VulkanSwapChain(Device, Surface);
}

void VulkanWindow::CreateRenderPass()
{
	//SwapChain->RenderPass = new VulkanRenderPass(Device, SwapChain->GetFormat());
}

void VulkanWindow::CreateFrameBuffer()
{
	//auto ImageViews = SwapChain->GetImageViews();
	//SwapChain->FrameBuffers.resize(SwapChain->GetImageCount());
	//for (int i = 0; i < SwapChain->FrameBuffers.size(); i++)
	//{
	//	auto Handle = ImageViews[i];
	//	SwapChain->FrameBuffers[i] = new VulkanFrameBuffer(Device, SwapChain->RenderPass, { SwapChain->GetWidth(), SwapChain->GetHeight()}, Handle);
	//}
}

void VulkanWindow::CreateCommandBuffer()
{
	GraphicsCommandBuffers.resize(SwapChain->GetImageCount());
	//GraphicsCommandBuffers.resize(2);
	for (int i = 0; i < GraphicsCommandBuffers.size(); i++)
	{
		/*
			暂时用第0个Command Pool
		*/
		GraphicsCommandBuffers[i] = Device->CreateCommandBuffer(Device->CommandPools[0]);
	}

	/*
		暂时用第0个Command Pool
	*/
	ComputeCommandBuffer = Device->CreateCommandBuffer(Device->CommandPools[0]);
}

void VulkanWindow::CreateSyncObject()
{
	Frames.resize(SwapChain->GetImageCount());
	for (int i = 0; i < Frames.size(); i++)
		Frames[i] = new VulkanFrame(Device, true);
}

