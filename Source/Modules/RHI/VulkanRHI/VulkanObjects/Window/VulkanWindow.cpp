#include "VulkanWindow.h"
#include "VulkanObjects/Queue/VulkanQueue.h"
#include "VulkanObjects/RenderPass/VulkanRenderPass.h"
#include "VulkanObjects/Window/VulkanFrame.h"
#include "VulkanObjects/RenderTarget/VulkanSwapChainRenderTarget.h"
#include  <iostream>
#include  <stdexcept>
#include <SFML/Window/Keyboard.hpp>

VulkanWindow::VulkanWindow(VulkanPhysicalDevice* InPhysicalDevice, VulkanDevice* InDevice, VulkanSurface* InSurface)
	: PhysicalDevice(InPhysicalDevice), Device(InDevice), Surface(InSurface)
{
	//PhysicalDevice->Query(Surface);
}

VulkanWindow::~VulkanWindow()
{
#if 0
	for (int i = 0; i < Frames.size(); i++)
		delete Frames[i];
#endif
	/*
		必须在Surface之前
		vkDestroySurfaceKHR(): called before its associated VkSwapchainKHR was destroyed.
		The Vulkan spec states: All VkSwapchainKHR objects created for surface must have been destroyed prior to destroying surface
		(https://vulkan.lunarg.com/doc/view/1.4.313.2/windows/antora/spec/latest/chapters/VK_KHR_surface/wsi.html#VUID-vkDestroySurfaceKHR-surface-01266)
	*/
	delete RenderTarget->SwapChain;

	std::cout << "VulkanWindow::~VulkanWindow() delete Surface " << std::endl;
	delete Surface;
}

void VulkanWindow::GetExtent(float& x, float& y, float& w, float& h)
{
	x = y = 0;
	w = RenderTarget->SwapChain->GetWidth();
	h = RenderTarget->SwapChain->GetHeight();
}

RHICommandBuffer* VulkanWindow::CurrentGraphicsCommandBuffer()
{
	return RenderTarget->GraphicsCommandBuffers[RenderTarget->CurrentImageIndex];
}

void VulkanWindow:: RHIBeginFrame()
{
	RenderTarget->RHIBeginFrame();

}

void VulkanWindow::RHIEndFrame()
{
	RenderTarget->RHIEndFrame();
}

void VulkanWindow::RHIBeginRenderPass()
{	
	RenderTarget->RHIBeginRenderPass();
	return;
	//VkClearValue ClearColor = { {{0.0f, 0.0f, 0.0f, 1.0f}} };
	VkClearValue ClearColor[2];
	ClearColor[0].color = {{0.0f, 0.0f, 0.0f, 1.0f}};
	ClearColor[1].depthStencil = {1.0f, 0};  // 深度清除为1.0（最远值

	VkRenderPassBeginInfo RenderPassInfo{};
	RenderPassInfo.sType				= VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
	//RenderPassInfo.renderPass			= SwapChain->RenderPass->GetHandle();
	RenderPassInfo.renderPass			= RenderTarget->RenderPass->GetHandle();
	//RenderPassInfo.framebuffer			= SwapChain->FrameBuffers[CurrentImageIndex]->GetHandle();
	RenderPassInfo.framebuffer			= RenderTarget->FrameBuffers[RenderTarget->CurrentImageIndex]->GetHandle();
	RenderPassInfo.renderArea.offset	= { 0, 0 };
	RenderPassInfo.renderArea.extent	= { RenderTarget->SwapChain->GetWidth(), RenderTarget->SwapChain->GetHeight() };
	RenderPassInfo.clearValueCount		= 2;
	RenderPassInfo.pClearValues			= ClearColor;

	RenderTarget->GraphicsCommandBuffers[RenderTarget->CurrentImageIndex]->CmdBeginRenderPass(&RenderPassInfo, VK_SUBPASS_CONTENTS_INLINE);
}

void VulkanWindow::RHIEndRenderPass()
{
	RenderTarget->RHIEndRenderPass();
	return;
	RenderTarget->GraphicsCommandBuffers[RenderTarget->CurrentImageIndex]->CmdEndRenderPass();
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
	RenderTarget->SwapChain->Resize(Width, Height);
	//delete SwapChain;
	//delete RenderPass;
}

void VulkanWindow::CreateSwapChain()
{
	RenderTarget = new VulkanSwapChainRenderTarget(Device, Surface);
	//RenderTarget->SwapChain = new VulkanSwapChain(Device, Surface);
	RenderTarget->SwapChain = RenderTarget->SwapChain;
}

