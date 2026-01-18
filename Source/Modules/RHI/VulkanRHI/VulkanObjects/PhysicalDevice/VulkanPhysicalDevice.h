#pragma once
#include "Vulkan.h"
#include <optional>
#include <vector>
#include <cstdint>



class VulkanSurface;
class VulkanDevice;
class VulkanQueueFamily;


/*
	1. 检查物理设备扩展支持
	2. 每个物理设备的queue family 创建队列
*/
class VulkanPhysicalDevice
{
public:
	VulkanPhysicalDevice();
	VulkanPhysicalDevice(VkPhysicalDevice h);
	~VulkanPhysicalDevice();
public:
	/*
		获取句柄
	*/
	VkPhysicalDevice GetHandle();
	/*
		获取Queue Family数量
	*/
	std::uint32_t GetQueueFamilyCount() const;
	/*
		获取VulkanQueueFamily
	*/
	VulkanQueueFamily *GetQueueFamily(std::uint32_t Index) const;

	std::uint32_t FindMemoryType(std::uint32_t TypeFilter, VkMemoryPropertyFlags InMemoryProperties);
	void PrintLayers();
	void PrintExtensions();
	void PrintProperties();
	void PrintQueueFamilyProperties();
	void PrintMemoryProperties();
	void PrintFeatures();
	void Query(const VulkanSurface* Surface);
	VulkanDevice* CreateDevice();
	VulkanDevice* CreateDevice2();

	bool CheckExtensionSupport(std::vector<const char*> RequiredExtensions);
public:
	/*
		Vulkan API Wrapper
	*/
	/*
		Enumerate device layers
	*/
	VkResult EnumerateDeviceLayerProperties(uint32_t* pPropertyCount, VkLayerProperties* pProperties);

	/*
		Query the extensions available to a given physical device,
	*/
	VkResult EnumerateDeviceExtensionProperties(const char* pLayerName, uint32_t* PropertyCount, VkExtensionProperties* Properties);

	/*
		Get Physical Device Properties
	*/
	void GetPhysicalDeviceProperties(VkPhysicalDeviceProperties* Properties);
	void GetPhysicalDeviceProperties2(VkPhysicalDeviceProperties2* Properties);

	/*
		Get Physical Device Queue Properties
	*/
	void GetPhysicalDeviceQueueFamilyProperties(std::uint32_t* QueueFamilyPropertyCount, VkQueueFamilyProperties* QueueFamilyProperties);
	void GetPhysicalDeviceQueueFamilyProperties2(std::uint32_t* QueueFamilyPropertyCount, VkQueueFamilyProperties2* QueueFamilyProperties);

	/*
		Get Physical Device Features
	*/
	void GetPhysicalDeviceFeatures(VkPhysicalDeviceFeatures* Features);
	void GetPhysicalDeviceFeatures2(VkPhysicalDeviceFeatures2* Features);

	/*
		Get Physical Device Memory Properties
	*/
	void GetPhysicalDeviceMemoryProperties(VkPhysicalDeviceMemoryProperties* pMemoryProperties);
	void GetPhysicalDeviceFormatProperties2(VkFormat Format, VkFormatProperties2* FormatProperties);

	/*
		Device
	*/
	VkResult CreateDevice(const VkDeviceCreateInfo* CreateInfo, const VkAllocationCallbacks* Allocator, VkDevice* Device);

	/*
		Surface
	*/
	VkResult GetPhysicalDeviceSurfaceCapabilitiesKHR(VkSurfaceKHR Surface, VkSurfaceCapabilitiesKHR* SurfaceCapabilities);
	VkResult GetPhysicalDeviceSurfaceFormatsKHR(VkSurfaceKHR Surface, uint32_t* SurfaceFormatCount, VkSurfaceFormatKHR* SurfaceFormats);
	VkResult GetPhysicalDeviceSurfacePresentModesKHR(VkSurfaceKHR Surface, uint32_t* PresentModeCount, VkPresentModeKHR* PresentModes);
	VkResult GetPhysicalDeviceSurfaceSupportKHR(std::uint32_t QueueFamilyIndex,VkSurfaceKHR Surface, VkBool32* Supported);
private:
	VkPhysicalDevice Handle;
	/*
		所有Layer Properties
	*/
	std::vector<VkLayerProperties>			LayerProperties;
	/*
		物理设备属性
	*/
	VkPhysicalDeviceProperties				PhysicalDeviceProperties;

	/*
		支持的扩展
	*/
	std::vector<VkExtensionProperties>		SupportedExtensions;

	/*
		待修改
	*/
	std::vector<std::uint32_t>				PresentQueueFamilyIndices;
	/*
		内存属性
	*/
	VkPhysicalDeviceMemoryProperties		MemoryProperties;
	/*
		Features
	*/
	VkPhysicalDeviceFeatures				Features;
	/*
		主机可见Memory Tyoe Indices
	*/
	std::vector<std::uint32_t>				HostVisibleMemoryTypeIndices;
	std::vector<std::uint32_t>				DeviceLocalMemoryTypeIndices;	
	/*
		Queue Families
	*/
	std::vector<VulkanQueueFamily*>			QueueFamilies;
public:
	std::uint32_t							HostVisibleIndex;	

	/*
		所有Queue Family Properties
	*/
	std::vector<VkQueueFamilyProperties>	QueueFamilyProperties;
};
