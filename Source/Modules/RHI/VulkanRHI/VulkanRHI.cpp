#include "VulkanRHI.h"
#include "VulkanObjects/Shader/VulkanShader.h"
#include "VulkanObjects/Shader/VulkanShaderResourceBindings.h"
#include "VulkanObjects/Queue/VulkanQueue.h"
#include "VulkanObjects/Resource/VulkanBuffer.h"
#include "VulkanObjects/Texture/VulkanTexture1D.h"
#include <VulkanObjects/Texture/VulkanTexture2D.h>
#include "VulkanObjects/Texture/VulkanTexture3D.h"
#include "VulkanObjects/Texture/VulkanTextureCubeMap.h"
#include "VulkanObjects/Texture/VulkanTextureCubeMapArray.h"
#include "VulkanObjects/Texture/VulkanTexture1DArray.h"
#include "VulkanObjects/Texture/VulkanTexture2DArray.h"
#include "VulkanObjects/Resource/VulkanSampler.h"



#include <iostream>
VulkanRHI::VulkanRHI()
{
	/*
		创建Instance
	*/
	CreateInstance();
	CreateDevice();
	CreateCommandPool();
#if RHI_USE_PLATFORM_WIN32_KHR
	vkCreateWin32SurfaceKHR = reinterpret_cast<PFN_vkCreateWin32SurfaceKHR>(vkGetInstanceProcAddr(Instance->GetHandle(), "vkCreateWin32SurfaceKHR"));
#endif
#if RHI_USE_PLATFORM_WAYLAND_KHR
	PFN_vkCreateWaylandSurfaceKHR = reinterpret_cast<PFN_vkCreateWin32SurfaceKHR>(vkGetInstanceProcAddr(Instance->GetHandle(), "vkCreateWaylandSurfaceKHR"));
#endif
}


VulkanRHI::~VulkanRHI()
{
	std::cout << "~VulkanRHI() " << std::endl;
	for (int i = 0; i < Devices.size(); i++)
	{
		delete Devices[i];
	}

	delete Instance;
}

void VulkanRHI::RHIUseGPU(std::uint32_t InGPUIndex)
{
	GPUIndex = InGPUIndex;
}

//RHIWindow* VulkanRHI::RHICreateWindow(GLFWwindow* Window)
//{
//	std::cout << "RHICreateWindow" << std::endl;
//
//	if (!Instance)
//	{
//		std::cout << "Instance is nullptr" << std::endl;
//		return nullptr;
//	}	
//	/**/
//	VkSurfaceKHR Handle;
//#if RHI_USE_PLATFORM_WIN32_KHR
//	HWND hwnd = glfwGetWin32Window(Window);
//	HINSTANCE instacne = (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE);
//	VkWin32SurfaceCreateInfoKHR CreateInfo{};
//	CreateInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
//	CreateInfo.hwnd = hwnd;
//	CreateInfo.hinstance = instacne;				
//	vkCreateWin32SurfaceKHR(Instance->GetHandle(), &CreateInfo, nullptr, &Handle);
//#elif def RHI_USE_PLATFORM_WAYLAND_KHR
//	struct wl_display* display = glfwGetWaylandDisplay();
//	struct wl_surface* wayland_surface = glfwGetWaylandWindow(window);
//	VkWaylandSurfaceCreateInfoKHR CreateInfo{};
//	CreateInfo.sType = VK_STRUCTURE_TYPE_WAYLAND_SURFACE_CREATE_INFO_KHR;
//	CreateInfo.display = display;
//	CreateInfo.surface = wayland_surface;
//#else
//	VkResult Result = glfwCreateWindowSurface(Instance->GetHandle(), Window, nullptr, &Handle);
//	if (VK_SUCCESS != Result)
//	{
//		std::cout << "glfwCreateWindowSurface failed " << Result << std::endl;
//		throw std::runtime_error("failed to create window surface!");
//	}
//#endif
//	VulkanSurface *Surface = new VulkanSurface(Instance, Handle);
//	//Surface->GLFWWindow = Window;
//
//	Surface->Query(*Instance->GetVulkanPhysicalDevice(GPUIndex));
//
//	Instance->GetVulkanPhysicalDevice(GPUIndex)->Query(Surface);
//
//	/**/
//
//	VulkanPhysicalDevice* PhysicalDevice = Instance->GetVulkanPhysicalDevice(GPUIndex);
//	VulkanDevice* Device = Devices[GPUIndex];
//
//	VulkanWindow* NewVulkanWindow = new VulkanWindow(PhysicalDevice, Device, Surface);	
//	std::cout << "RHICreateWindow 1" << std::endl;
//	NewVulkanWindow->CreateSwapChain();
//	std::cout << "RHICreateWindow 2" << std::endl;
//	NewVulkanWindow->CreateRenderPass();
//	NewVulkanWindow->CreateFrameBuffer();
//	NewVulkanWindow->CreateCommandBuffer();
//	NewVulkanWindow->CreateSyncObject();
//	return NewVulkanWindow;
//}

#if RHI_USE_PLATFORM_WIN32_KHR 
RHIWindow* VulkanRHI::RHICreateWindow(HINSTANCE Hinstance, HWND Hwnd)
{
	if (!Instance)
	{
		std::cout << "Instance is nullptr" << std::endl;
		return nullptr;
	}

	VkSurfaceKHR Handle;
	VkWin32SurfaceCreateInfoKHR CreateInfo{};
	CreateInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
	CreateInfo.hwnd = Hwnd;
	CreateInfo.hinstance = Hinstance;
	vkCreateWin32SurfaceKHR(Instance->GetHandle(), &CreateInfo, nullptr, &Handle);

	VulkanSurface* Surface = new VulkanSurface(Instance, Handle);

	Surface->Query(*Instance->GetVulkanPhysicalDevice(GPUIndex));

	Instance->GetVulkanPhysicalDevice(GPUIndex)->Query(Surface);

	/**/

	VulkanPhysicalDevice* PhysicalDevice = Instance->GetVulkanPhysicalDevice(GPUIndex);
	VulkanDevice* Device = Devices[GPUIndex];

	VulkanWindow* NewVulkanWindow = new VulkanWindow(PhysicalDevice, Device, Surface);
	std::cout << "RHICreateWindow 1" << std::endl;
	NewVulkanWindow->CreateSwapChain();
	std::cout << "RHICreateWindow 2" << std::endl;
	NewVulkanWindow->CreateRenderPass();
	NewVulkanWindow->CreateFrameBuffer();
	NewVulkanWindow->CreateCommandBuffer();
	NewVulkanWindow->CreateSyncObject();
	return NewVulkanWindow;
}
#endif

#if RHI_USE_PLATFORM_WAYLAND_KHR 
RHIWindow* VulkanRHI::RHICreateWindow(struct wl_display* display, struct wl_surface* wayland_surface)
{
	return nullptr;
}
#endif

#if RHI_USE_PLATFORM_XCB_KHR  
RHIWindow* VulkanRHI::RHICreateWindow(xcb_connection_t* Connection, xcb_window_t Window)
{
	return nullptr;
}
#endif

RHIBuffer* VulkanRHI::RHICreateBuffer(RHIBuffer::RHIBufferType InType, RHIBuffer::RHIBufferUsageFlag InUsage, std::uint32_t InSize)
{
	VulkanBuffer* Buffer = new VulkanBuffer(Devices[GPUIndex], InType, InUsage, InSize, nullptr);

	return Buffer;
}

RHIBuffer* VulkanRHI::RHICreateBuffer(RHIBuffer::RHIBufferType InType, RHIBuffer::RHIBufferUsageFlag InUsage, std::uint32_t InSize, const void* InData)
{
	VulkanBuffer* Buffer = new VulkanBuffer(Devices[GPUIndex], InType, InUsage, InSize, InData);

	return Buffer;
}

RHIGraphicsPipeline* VulkanRHI::RHICreateGraphicsPipeline()
{
	VulkanGraphicsPipeline* Pipeline = new VulkanGraphicsPipeline(Devices[GPUIndex], nullptr);
	return Pipeline;
}

RHIGraphicsPipeline* VulkanRHI::RHICreateGraphicsPipeline(RHIWindow* Window)
{
	VulkanGraphicsPipeline* Pipeline = new VulkanGraphicsPipeline(Devices[GPUIndex], ((VulkanWindow*)Window)->SwapChain->RenderPass);
	return Pipeline;
}

RHIShader* VulkanRHI::RHICreateShader(RHIShaderType Type, std::uint32_t* Code, size_t CodeSize)
{
	VulkanShader* Shader = new VulkanShader(Devices[GPUIndex], Type, Code, CodeSize);
	return Shader;
}


RHITexture* VulkanRHI::RHICreateTexture1D(RHIPixelFormat RHIPixelFormat, std::uint32_t NumMips, std::uint32_t SizeX)
{
	VulkanTexture* Texture =  new VulkanTexture1D(Devices[GPUIndex], RHIPixelFormat, NumMips, SizeX);
	Texture->CommandPool = GraphicsCommandPool;
	Texture->graphicsQueue = Devices[GPUIndex]->Queues[0]->GetHandle();

	Texture->Image->CommandPool = GraphicsCommandPool;
	Texture->Image->GraphicsQueue = Devices[GPUIndex]->Queues[0]->GetHandle();
	return Texture;
}

RHITexture* VulkanRHI::RHICreateTexture1DArray(RHIPixelFormat RHIPixelFormat, std::uint32_t NumMips, std::uint32_t SizeX, std::uint32_t ArraySize)
{
	VulkanTexture* Texture = new VulkanTexture1DArray(Devices[GPUIndex], RHIPixelFormat, NumMips, SizeX, ArraySize);
	Texture->CommandPool = GraphicsCommandPool;
	Texture->graphicsQueue = Devices[GPUIndex]->Queues[0]->GetHandle();

	Texture->Image->CommandPool = GraphicsCommandPool;
	Texture->Image->GraphicsQueue = Devices[GPUIndex]->Queues[0]->GetHandle();
	return Texture;

	//return new VulkanTexture1DArray(Devices[GPUIndex], RHIPixelFormat, NumMips, SizeX, ArraySize);
}

RHITexture* VulkanRHI::RHICreateTexture2D(RHIPixelFormat RHIPixelFormat, std::uint32_t NumMips, std::uint32_t SizeX, std::uint32_t SizeY)
{
	VulkanTexture *Texture = new VulkanTexture2D(Devices[GPUIndex], RHIPixelFormat, NumMips, SizeX, SizeY);
	Texture->CommandPool   = GraphicsCommandPool;
	Texture->graphicsQueue = Devices[GPUIndex]->Queues[0]->GetHandle();

	Texture->Image->CommandPool = GraphicsCommandPool;
	Texture->Image->GraphicsQueue = Devices[GPUIndex]->Queues[0]->GetHandle();
	return Texture;
}

RHITexture* VulkanRHI::RHICreateTexture2DArray(RHIPixelFormat RHIPixelFormat, std::uint32_t NumMips, std::uint32_t SizeX, std::uint32_t SizeY, std::uint32_t ArraySize)
{
	VulkanTexture* Texture = new VulkanTexture2DArray(Devices[GPUIndex], RHIPixelFormat, NumMips, SizeX, SizeY, ArraySize);

	Texture->CommandPool = GraphicsCommandPool;
	Texture->graphicsQueue = Devices[GPUIndex]->Queues[0]->GetHandle();

	Texture->Image->CommandPool = GraphicsCommandPool;
	Texture->Image->GraphicsQueue = Devices[GPUIndex]->Queues[0]->GetHandle();
	return Texture;
	
}

RHITexture* VulkanRHI::RHICreateTexture3D(RHIPixelFormat RHIPixelFormat, std::uint32_t NumMips, std::uint32_t SizeX, std::uint32_t SizeY, std::uint32_t SizeZ)
{
	VulkanTexture* Texture = new VulkanTexture3D(Devices[GPUIndex], RHIPixelFormat, NumMips, SizeX, SizeY, SizeZ);
	Texture->CommandPool = GraphicsCommandPool;
	Texture->graphicsQueue = Devices[GPUIndex]->Queues[0]->GetHandle();

	Texture->Image->CommandPool = GraphicsCommandPool;
	Texture->Image->GraphicsQueue = Devices[GPUIndex]->Queues[0]->GetHandle();
	return Texture;
}

RHITexture* VulkanRHI::RHICreateTextureCube(RHIPixelFormat RHIPixelFormat, std::uint32_t NumMips, std::uint32_t SizeX, std::uint32_t SizeY)
{
	VulkanTexture* Texture = new VulkanTextureCubeMap(Devices[GPUIndex], RHIPixelFormat, NumMips, SizeX, SizeY);
	Texture->CommandPool = GraphicsCommandPool;
	Texture->graphicsQueue = Devices[GPUIndex]->Queues[0]->GetHandle();

	Texture->Image->CommandPool = GraphicsCommandPool;
	Texture->Image->GraphicsQueue = Devices[GPUIndex]->Queues[0]->GetHandle();
	return Texture;
}

RHITexture* VulkanRHI::RHICreateTextureCubeArray(RHIPixelFormat RHIPixelFormat, std::uint32_t NumMips, std::uint32_t SizeX, std::uint32_t SizeY, std::uint32_t ArraySize)
{
	VulkanTexture* Texture = new VulkanTextureCubeMapArray(Devices[GPUIndex], RHIPixelFormat, NumMips, SizeX, SizeY, ArraySize);
	Texture->CommandPool = GraphicsCommandPool;
	Texture->graphicsQueue = Devices[GPUIndex]->Queues[0]->GetHandle();

	Texture->Image->CommandPool = GraphicsCommandPool;
	Texture->Image->GraphicsQueue = Devices[GPUIndex]->Queues[0]->GetHandle();
	return Texture;
}

void VulkanRHI::RHIUpdateTexture(RHITexture* Texture, const void* InData, std::uint32_t InSize)
{
	VulkanTexture *VKTexture = ((VulkanTexture*)Texture);
	//VKTexture->Update(InData, InSize);
}

RHISampler* VulkanRHI::RHICreateSampler(RHIFilter MinFilter,
	RHIFilter MagFilter,
	RHIAddressMode AddressModeU,
	RHIAddressMode AddressModeV,
	RHIAddressMode AddressModeW)
{
	return new VulkanSampler(Devices[GPUIndex], MinFilter, MagFilter, AddressModeU, AddressModeV, AddressModeW);
}

RHIShaderResourceBindings* VulkanRHI::RHICreateShaderResourceBindings()
{
	return new VulkanShaderResourceBindings(Devices[GPUIndex]);
}

VkCommandBuffer VulkanRHI::beginSingleTimeCommands() {
	VkCommandBufferAllocateInfo allocInfo{};
	allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	allocInfo.commandPool = GraphicsCommandPool->GetHandle();
	allocInfo.commandBufferCount = 1;

	VkCommandBuffer commandBuffer;
	std::cout << "AllocateCommandBuffers start " << Devices[GPUIndex]->GetHandle() << std::endl;
	auto ret = Devices[GPUIndex]->AllocateCommandBuffers(&allocInfo, &commandBuffer);
	std::cout << "AllocateCommandBuffers end " << ret << std::endl;

	VkCommandBufferBeginInfo beginInfo{};
	beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
	beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

	std::cout << "vkBeginCommandBuffer start" << std::endl;
	ret = vkBeginCommandBuffer(commandBuffer, &beginInfo);
	std::cout << "vkBeginCommandBuffer end " << ret << std::endl;
	return commandBuffer;
}

void VulkanRHI::endSingleTimeCommands(VkCommandBuffer commandBuffer) {
	vkEndCommandBuffer(commandBuffer);

	VkSubmitInfo submitInfo{};
	submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
	submitInfo.commandBufferCount = 1;
	submitInfo.pCommandBuffers = &commandBuffer;

	//vkQueueSubmit(graphicsQueue, 1, &submitInfo, VK_NULL_HANDLE);
	//vkQueueWaitIdle(graphicsQueue);

	Devices[GPUIndex]->FreeCommandBuffers(GraphicsCommandPool->GetHandle(), 1, &commandBuffer);
}

void VulkanRHI::transitionImageLayout(VkImage image, VkFormat format, VkImageLayout OldLayout, VkImageLayout NewLayout)
{
	VkCommandBuffer commandBuffer = beginSingleTimeCommands();

	VkImageMemoryBarrier barrier{};
	barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
	barrier.oldLayout = OldLayout;
	barrier.newLayout = NewLayout;
	barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
	barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
	barrier.image = image;
	barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
	barrier.subresourceRange.baseMipLevel = 0;
	barrier.subresourceRange.levelCount = 1;
	barrier.subresourceRange.baseArrayLayer = 0;
	barrier.subresourceRange.layerCount = 1;

	VkPipelineStageFlags sourceStage;
	VkPipelineStageFlags destinationStage;

	if (OldLayout == VK_IMAGE_LAYOUT_UNDEFINED && NewLayout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL) {
		barrier.srcAccessMask = 0;
		barrier.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;

		sourceStage = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
		destinationStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
	}
	else if (OldLayout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL && NewLayout == VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL) {
		barrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
		barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;

		sourceStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
		destinationStage = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
	}
	else {
		//throw std::invalid_argument("unsupported layout transition!");
	}
	std::cout << "vkCmdPipelineBarrier start" << std::endl;
	vkCmdPipelineBarrier(
		commandBuffer,
		sourceStage, destinationStage,
		0,
		0, nullptr,
		0, nullptr,
		1, &barrier
	);
	std::cout << "vkCmdPipelineBarrier end" << std::endl;

	endSingleTimeCommands(commandBuffer);
}
