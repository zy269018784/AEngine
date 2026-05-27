#pragma once
#include "VulkanRHI/Vulkan.h"
#include "RHI/RHIObjects/SwapChain/RHISwapChain.h"
#include <vector>
 
class VulkanDevice;
class VulkanRenderPass;
class VulkanSurface;
class VulkanImage;
class VulkanImageView;
class VulkanFrameBuffer;
class VulkanSwapChain : public RHISwapChain
{
public:
	VulkanSwapChain(VulkanDevice *InDevice, VulkanSurface* InSurface);
	~VulkanSwapChain();

	void CreateSwapChain();
    void CreateImageViews();
	void Resize(float Width, float Height);
	void Cleanup();
	VkSwapchainKHR GetHandle() const;
	VkFormat GetFormat() const;
	int GetImageCount() const;
	std::vector<VkImageView> GetImageViews() const;
public:
	/*
		Vulkan API Wrapper
	*/
	VkResult AcquireNextImageKHR(uint64_t Timeout, VkSemaphore  Semaphore, VkFence Fence, uint32_t* ImageIndex);
	VkResult GetSwapchainImagesKHR(uint32_t* SwapchainImageCount, VkImage* SwapchainImages);
protected:
    VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
    VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
    VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);

private:
	/*
		句柄
	*/
	VkSwapchainKHR							Handle;
	/*
		Image
	*/
	std::vector<VkImage>					SwapChainImages;
	/*
		Image View
	*/
	std::vector<VkImageView>				SwapChainImageViews;
};
