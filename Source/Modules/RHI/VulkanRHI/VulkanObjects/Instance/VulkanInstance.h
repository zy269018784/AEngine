#pragma once
#include "Vulkan.h"
#include <cstdint>
#include <vector>
class VulkanPhysicalDevice;
class VulkanInstance
{
public:
	VulkanInstance();
	VulkanInstance(std::vector<const char*> Extensions, std::vector<const char*> Layers);
	~VulkanInstance();
	void EnumeratePhysicalDevices();
	void EnumerateLayers();
	void EnumerateExtensions();
	VulkanPhysicalDevice* GetVulkanPhysicalDevice(uint32_t i) const;
	std::uint32_t GetVulkanPhysicalDeviceCount();
	VkInstance GetHandle();
	void SetHandle(VkInstance Instance);
public:
	/*
		Vulkan API Wapper
	*/
	/*
		Query the version of instance-level functionality supported by the implementation
	*/
	VkResult EnumerateInstanceVersion(uint32_t* pApiVersion);

	/*
		Query the available layers
	*/
	VkResult EnumerateInstanceLayerProperties(uint32_t* pPropertyCount, VkLayerProperties* pProperties);

	/*
		Query the available instance extensions
	*/
	VkResult EnumerateInstanceExtensionProperties(const char* pLayerName, uint32_t* pPropertyCount, VkExtensionProperties* pProperties);

	/*
		Retrieve a list of physical device objects representing the physical devices installed in the system
	*/
	VkResult EnumeratePhysicalDevices(std::uint32_t* PhysicalDeviceCount, VkPhysicalDevice* PhysicalDevices);

	/*
		Retrieve a list of the device groups present in the system
	*/
	VkResult EnumeratePhysicalDeviceGroups(std::uint32_t* PhysicalDeviceGroupCount, VkPhysicalDeviceGroupProperties* pPhysicalDeviceGroupProperties);

	void DestroySurfaceKHR(VkSurfaceKHR Surface, const VkAllocationCallbacks* Allocator = nullptr);
private:
	VkInstance Handle;
	/*
		所有的物理设备
	*/
	std::vector<VulkanPhysicalDevice*> PhysicalDevices;
	
	/*
		是否支持验证层
	*/
	bool SupportValidationLayer = false;
};
