#pragma once
#include "Vulkan.h"
#include "VulkanObjects/Instance/VulkanInstance.h"
#include "VulkanObjects/PhysicalDevice/VulkanPhysicalDevice.h"

class VulkanSurface
{
public:
	VulkanSurface();
	VulkanSurface(VulkanInstance* InInstance, VkSurfaceKHR Surface);
	~VulkanSurface();
	VkSurfaceKHR GetHandle() const;
	void Query(VulkanPhysicalDevice& PhysicalDevice);
private:
	/*
		Vulkan API Wrapper
	*/
	void DestroySurfaceKHR(const VkAllocationCallbacks* Allocator);
public:
	/*
		句柄
	*/
	VkSurfaceKHR Handle;
	/*
		Vulkan Instance
	*/
	VulkanInstance* Instance = nullptr;
	/*
		能力
	*/
	VkSurfaceCapabilitiesKHR				Capabilities;
	/*
		所有支持的像素格式和色彩空间
	*/
	std::vector<VkSurfaceFormatKHR>			Formats;
	/*
		像素格式和色彩空间
	*/
	VkSurfaceFormatKHR						CurrentFormat;
	/*
		所有Present Mode
	*/
	std::vector<VkPresentModeKHR>			PresentModes;
	/*
		当前Present Mode
	*/
	VkPresentModeKHR						CurrentPresentMode;
	/*
		宽和高
	*/
	VkExtent2D								CurrentExtent;
};