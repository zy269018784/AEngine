#pragma once
#include "RHI.h"
#include "RHIPlatform.h"
#include "Vulkan.h"
#include "VulkanObjects/Device/VulkanDevice.h"
#include "VulkanObjects/Instance/VulkanInstance.h"
#include "VulkanObjects/Surface/VulkanSurface.h"
#include "VulkanObjects/Device/VulkanDevice.h"
#include "VulkanObjects/SwapChain/VulkanSwapChain.h"
#include "VulkanObjects/FrameBuffer/VulkanFrameBuffer.h"
#include "VulkanObjects/RenderPass/VulkanRenderPass.h"
#include "VulkanObjects/CommandBuffer/VulkanCommandPool.h"
#include "VulkanObjects/CommandBuffer/VulkanCommandBuffer.h"
#include <VulkanObjects/Pipeline/VulkanGraphicsPipeline.h>
#include "VulkanObjects/Synchronization/VulkanFence.h"
#include "VulkanObjects/Synchronization/VulkanSemaphore.h"
#include "VulkanObjects/Window/VulkanWindow.h"
//#include <vector>

class VulkanRHI : public RHI
{
public:
	VulkanRHI();
	~VulkanRHI();

	VkCommandBuffer beginSingleTimeCommands();
	void endSingleTimeCommands(VkCommandBuffer commandBuffer);
	void transitionImageLayout(VkImage image, VkFormat format, VkImageLayout OldLayout, VkImageLayout NewLayout);

public:
	/*
		选择GPU
	*/
	/**
		@brief 选择GPU
		@return
	*/
	virtual void RHIUseGPU(std::uint32_t GPUIndex) final override;
	/*
		窗口Windows
	*/
	/*
		Win32
	*/
#if RHI_USE_PLATFORM_WIN32_KHR 
	virtual RHIWindow* RHICreateWindow(HINSTANCE Hinstance, HWND Hwnd) final override;
#endif
	/*
		Wayland
	*/
#if RHI_USE_PLATFORM_WAYLAND_KHR 
	virtual RHIWindow* RHICreateWindow(struct wl_display* display, struct wl_surface* wayland_surface) final override;
#endif
	/*
		X11
	*/
#if RHI_USE_PLATFORM_XCB_KHR  
	virtual RHIWindow* RHICreateWindow(xcb_connection_t* Connection, xcb_window_t Window) final override;
#endif

	virtual RHIGraphicsPipeline* RHICreateGraphicsPipeline() final override;
	virtual RHIGraphicsPipeline* RHICreateGraphicsPipeline(RHIWindow* Window) final override;

	virtual RHIShaderResourceBindings* RHICreateShaderResourceBindings() final override;



	virtual RHIBuffer* RHICreateBuffer(RHIBuffer::RHIBufferType InType, RHIBuffer::RHIBufferUsageFlag InUsage, std::uint32_t InSize)  final override;
	virtual RHIBuffer* RHICreateBuffer(RHIBuffer::RHIBufferType InType, RHIBuffer::RHIBufferUsageFlag InUsage, std::uint32_t InSize, const void* InData)  final override;
	virtual RHIShader* RHICreateShader(RHIShaderType Type, std::uint32_t* Code, size_t CodeSize) final override;

	virtual RHITexture* RHICreateTexture1D(RHIPixelFormat RHIPixelFormat, std::uint32_t NumMips, std::uint32_t SizeX) final override;
	virtual RHITexture* RHICreateTexture1DArray(RHIPixelFormat RHIPixelFormat, std::uint32_t NumMips, std::uint32_t SizeX, std::uint32_t ArraySize) final override;
	virtual RHITexture* RHICreateTexture2D(RHIPixelFormat RHIPixelFormat, std::uint32_t NumMips, std::uint32_t SizeX, std::uint32_t SizeY) final override;
	virtual RHITexture* RHICreateTexture2DArray(RHIPixelFormat RHIPixelFormat, std::uint32_t NumMips, std::uint32_t SizeX, std::uint32_t SizeY, std::uint32_t ArraySize) final override;
	virtual RHITexture* RHICreateTexture3D(RHIPixelFormat RHIPixelFormat, std::uint32_t NumMips, std::uint32_t SizeX, std::uint32_t SizeY, std::uint32_t SizeZ) final override;
	virtual RHITexture* RHICreateTextureCube(RHIPixelFormat RHIPixelFormat, std::uint32_t NumMips, std::uint32_t SizeX, std::uint32_t SizeY) final override;
	virtual RHITexture* RHICreateTextureCubeArray(RHIPixelFormat RHIPixelFormat, std::uint32_t NumMips, std::uint32_t SizeX, std::uint32_t SizeY, std::uint32_t ArraySize) final override;
	virtual void RHIUpdateTexture(RHITexture* Texture, const void *InData, std::uint32_t InSize) final override;

	virtual RHISampler* RHICreateSampler(RHIFilter MinFilter = RHIFilter::NEAREST,
		RHIFilter MagFilter = RHIFilter::NEAREST,
		RHIAddressMode AddressModeU = RHIAddressMode::REPEAT,
		RHIAddressMode AddressModeV = RHIAddressMode::REPEAT,
		RHIAddressMode AddressModeW = RHIAddressMode::REPEAT)  final override;
private:
	void CreateInstance();
	void CreateDevice();
	void CreateCommandPool();
private:	
	std::uint32_t							GPUIndex = 0;
	VulkanInstance							*Instance = nullptr;			// 1个
	std::vector<VulkanDevice *>				Devices;						// 多个
	VulkanCommandPool						*GraphicsCommandPool = nullptr;	// 1个
	VulkanCommandPool						*ComputeCommandPool = nullptr;	// 1个
//private:
//	std::vector<const char*> PhysicalDeviceExtensions;
private:
#ifdef RHI_USE_PLATFORM_WIN32_KHR
	PFN_vkCreateWin32SurfaceKHR vkCreateWin32SurfaceKHR;
#endif
#ifdef RHI_USE_PLATFORM_WAYLAND_KHR
	PFN_vkCreateWaylandSurfaceKHR vkCreateWaylandSurfaceKHR;
#endif
};

/*
	RHI能力:
		PhysicalDeviceCount个物理设备

	用到Queue Family Index的地方:	
		Command Pool
		Swap Chain
	
	Physical Device:
		QueueFamilyCount个Queue Family

	Window:
		1个window对应1个Surface
		1个window对应1个Swap Chain
		1个window对应n个Frame Buffer
		1个Physical Device对应1个Window
	
	Swap Chain:
		1个Swap Chain对应1个Render Pass
		1个Swap Chain对应SwapChainImageCount个Frame Buffer

		像素格式	VK_FORMAT_B8G8R8A8_SRGB
		色彩空间	VK_COLOR_SPACE_SRGB_NONLINEAR_KHR
		图像尺寸
		需要指定Queue Famliy Index
	
	Command Buffer:
		用于多线程

	Render Pass:
		用到Swap Chain的SwapChainImageFormat

	VulkanRHI:	
		Instance
		PhysicalDeviceCount个Physical Devices
		PhysicalDeviceCount个Window
		
		最多创建n个Surface(与GLFWwindow关联)

		PhysicalDeviceCount个Device

		PhysicalDeviceCount个Swap Chain(与Surface关联)

		PhysicalDeviceCount个Render Pass

		(PhysicalDeviceCount * SwapChainImageCount)个Frame Buffer

		(PhysicalDeviceCount * QueueFamilyCount)个Command Pool

		(PhysicalDeviceCount * SwapChainImageCount)个Command Buffer
*/

/*
	窗口Resize:
		Swap chain  Resize
		Framebuffer Resize
*/
