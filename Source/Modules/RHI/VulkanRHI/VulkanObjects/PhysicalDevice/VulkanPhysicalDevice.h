#pragma once
#include "Vulkan.h"
#include <optional>
#include <vector>
#include <cstdint>
#include "RHIObjects/PhysicalDevice/RHIPhysicalDevice.h"


class VulkanSurface;
class VulkanDevice;
class VulkanQueueFamily;


/*
	1. 检查物理设备扩展支持
	2. 每个物理设备的queue family 创建队列
*/
class VulkanPhysicalDevice : public RHIPhysicalDevice
{
public:
	VulkanPhysicalDevice();
	VulkanPhysicalDevice(VkPhysicalDevice h);
	~VulkanPhysicalDevice();
	virtual void QuerySupportedPixelFormats() override final;
	VkPhysicalDeviceLimits	GetPhysicalDeviceLimits() const;
protected:
	void InitFeatures() override final;
public:
	/*
		获取句柄
	*/
	VkPhysicalDevice GetHandle();

	VkPhysicalDeviceFeatures GetGeatures() const;
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
	 *  Lists physical device’s format capabilities
	 */
	void GetPhysicalDeviceFormatProperties(VkFormat format, VkFormatProperties*  pFormatProperties);
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
	void GetPhysicalDeviceFeatures2KHR(VkPhysicalDeviceFeatures2* Features);
	/*
		Get Physical Device Memory Properties
	*/
	void GetPhysicalDeviceMemoryProperties(VkPhysicalDeviceMemoryProperties* pMemoryProperties);
	void GetPhysicalDeviceFormatProperties2(VkFormat Format, VkFormatProperties2* FormatProperties);
	void GetPhysicalDeviceFormatProperties2KHR(VkFormat Format, VkFormatProperties2* FormatProperties);

	VkResult GetPhysicalDeviceImageFormatProperties(VkFormat format,
		VkImageType                                 type,
		VkImageTiling                               tiling,
		VkImageUsageFlags                           usage,
		VkImageCreateFlags                          flags,
		VkImageFormatProperties*                    pImageFormatProperties);

	VkResult GetPhysicalDeviceImageFormatProperties2(const VkPhysicalDeviceImageFormatInfo2* ImageFormatInfo,
		VkImageFormatProperties2*                   pImageFormatProperties);

	VkResult GetPhysicalDeviceImageFormatProperties2KHR(const VkPhysicalDeviceImageFormatInfo2* ImageFormatInfo,
		VkImageFormatProperties2* ImageFormatProperties);
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
	VkPhysicalDeviceProperties					PhysicalDeviceProperties;
	VkPhysicalDeviceProperties2					PhysicalDeviceProperties2;
	/*
	 * VK_KHR_maintenance3
	 */
	VkPhysicalDeviceMaintenance3PropertiesKHR	Maintenance3Properties;
	/*
	 * VK_KHR_maintenance4
	 */
	VkPhysicalDeviceMaintenance4PropertiesKHR	Maintenance4Properties;
	/*
	 * VK_KHR_maintenance5
	 */
	VkPhysicalDeviceMaintenance5PropertiesKHR	Maintenance5Properties;
	/*
	 * VK_KHR_maintenance6
	 */
	VkPhysicalDeviceMaintenance6PropertiesKHR	Maintenance6Properties;
	/*
	 * VK_KHR_maintenance7
	 */
	VkPhysicalDeviceMaintenance7PropertiesKHR	Maintenance7Properties;
	/*
	 * VK_KHR_maintenance9
	 */
	VkPhysicalDeviceMaintenance9PropertiesKHR	Maintenance9Properties;
	/*
		Features
	*/
	/*
	 *   Vulkan Core 1.1
	 */
	VkPhysicalDeviceVulkan11Features 		    Vulkan11Features;
	/*
	 *   Vulkan Core 1.2
	 */
	VkPhysicalDeviceVulkan12Features 		    Vulkan12Features;
	/*
	 *   Vulkan Core 1.3
	 */
	VkPhysicalDeviceVulkan13Features 		    Vulkan13Features;
	VkPhysicalDeviceFeatures					VulkanFeatures;
	VkPhysicalDeviceFeatures2					VulkanFeatures2;
	/*
	 * VK_KHR_maintenance4
	 */
	VkPhysicalDeviceMaintenance4FeaturesKHR		Maintenance4Features;
	/*
	 * VK_KHR_maintenance5
	 */
	VkPhysicalDeviceMaintenance5FeaturesKHR		Maintenance5Features;
	/*
	 * VK_KHR_maintenance6
	 */
	VkPhysicalDeviceMaintenance6FeaturesKHR		Maintenance6Features;
	/*
	 * VK_KHR_maintenance7
	 */
	VkPhysicalDeviceMaintenance7FeaturesKHR		Maintenance7Features;
	/*
	 * VK_KHR_maintenance8
	 */
	VkPhysicalDeviceMaintenance8FeaturesKHR		Maintenance8Features;

	/*
	 * VK_KHR_maintenance9
	 */
	VkPhysicalDeviceMaintenance9FeaturesKHR		Maintenance9Features;

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


	bool SupportedPixelFormatsLinearTilingFeatures[(int)RHIPixelFormat::PF_MAX_];

	bool SupportedPixelFormatsOptimalTilingFeatures[(int)RHIPixelFormat::PF_MAX_];
};
