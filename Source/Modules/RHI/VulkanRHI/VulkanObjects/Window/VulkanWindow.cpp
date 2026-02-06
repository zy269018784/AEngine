#include "VulkanWindow.h"
#include "VulkanObjects/Queue/VulkanQueue.h"
#include "VulkanObjects/RenderPass/VulkanRenderPass.h"
#include "VulkanObjects/Window/VulkanFrame.h"
#include "VulkanObjects/RenderTarget/VulkanSwapChainRenderTarget.h"
#include "VulkanObjects/Core/VulkanCore.h"
#include  <iostream>
#include  <stdexcept>
#include <SFML/Window/Keyboard.hpp>

VulkanWindow::VulkanWindow(VulkanPhysicalDevice* InPhysicalDevice, VulkanDevice* InDevice, VulkanSurface* InSurface)
	: PhysicalDevice(InPhysicalDevice), Device(InDevice), Surface(InSurface)
{
	RenderTarget = new VulkanSwapChainRenderTarget(new VulkanSwapChain(Device, Surface), Device, Surface, ToRHIPixelFormat(Surface->CurrentFormat.format));
}

VulkanWindow::~VulkanWindow()
{
	/*
		必须在Surface之前
		vkDestroySurfaceKHR(): called before its associated VkSwapchainKHR was destroyed.
		The Vulkan spec states: All VkSwapchainKHR objects created for surface must have been destroyed prior to destroying surface
		(https://vulkan.lunarg.com/doc/view/1.4.313.2/windows/antora/spec/latest/chapters/VK_KHR_surface/wsi.html#VUID-vkDestroySurfaceKHR-surface-01266)
	*/
	delete RenderTarget->SwapChain;

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
}

void VulkanWindow::RHIEndRenderPass()
{
	RenderTarget->RHIEndRenderPass();
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
}

