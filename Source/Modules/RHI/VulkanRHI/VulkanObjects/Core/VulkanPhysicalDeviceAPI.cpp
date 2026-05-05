#include "VulkanObjects/PhysicalDevice/VulkanPhysicalDevice.h"
/*
	Enumerate device layers
*/
VkResult VulkanPhysicalDevice::EnumerateDeviceLayerProperties(uint32_t* pPropertyCount, VkLayerProperties* pProperties)
{
	return vkEnumerateDeviceLayerProperties(Handle, pPropertyCount, pProperties);
}

/*
	Query the extensions available to a given physical device,
*/
VkResult VulkanPhysicalDevice::EnumerateDeviceExtensionProperties(const char* pLayerName, uint32_t* PropertyCount, VkExtensionProperties* Properties)
{
	return vkEnumerateDeviceExtensionProperties(Handle, pLayerName, PropertyCount, Properties);
}

void VulkanPhysicalDevice::GetPhysicalDeviceFormatProperties(VkFormat format, VkFormatProperties*  pFormatProperties) {
	vkGetPhysicalDeviceFormatProperties(Handle, format, pFormatProperties);
}

/*
	Get Physical Device Properties
*/
void VulkanPhysicalDevice::GetPhysicalDeviceProperties(VkPhysicalDeviceProperties* Properties)
{
	vkGetPhysicalDeviceProperties(Handle, Properties);
}

void VulkanPhysicalDevice::GetPhysicalDeviceProperties2(VkPhysicalDeviceProperties2* Properties)
{
	vkGetPhysicalDeviceProperties2(Handle, Properties);
}

/*
	Get Physical Device Queue Properties
*/
void VulkanPhysicalDevice::GetPhysicalDeviceQueueFamilyProperties(std::uint32_t* QueueFamilyPropertyCount, VkQueueFamilyProperties* QueueFamilyProperties)
{
	vkGetPhysicalDeviceQueueFamilyProperties(Handle, QueueFamilyPropertyCount, QueueFamilyProperties);
}

void VulkanPhysicalDevice::GetPhysicalDeviceQueueFamilyProperties2(std::uint32_t* QueueFamilyPropertyCount, VkQueueFamilyProperties2* QueueFamilyProperties)
{
	vkGetPhysicalDeviceQueueFamilyProperties2(Handle, QueueFamilyPropertyCount, QueueFamilyProperties);
}

/*
	Get Physical Device Features
*/
void VulkanPhysicalDevice::GetPhysicalDeviceFeatures(VkPhysicalDeviceFeatures* Features)
{
	vkGetPhysicalDeviceFeatures(Handle, Features);
}

void VulkanPhysicalDevice::GetPhysicalDeviceFeatures2(VkPhysicalDeviceFeatures2* Features)
{
	vkGetPhysicalDeviceFeatures2(Handle, Features);
}

void VulkanPhysicalDevice::GetPhysicalDeviceFeatures2KHR(VkPhysicalDeviceFeatures2* Features)
{
	//vkGetPhysicalDeviceFeatures2KHR(Handle, Features);
}

/*
	Get Physical Device Memory Properties
*/
void VulkanPhysicalDevice::GetPhysicalDeviceMemoryProperties(VkPhysicalDeviceMemoryProperties* pMemoryProperties)
{
	vkGetPhysicalDeviceMemoryProperties(Handle, pMemoryProperties);
}

void VulkanPhysicalDevice::GetPhysicalDeviceFormatProperties2(VkFormat Format, VkFormatProperties2* FormatProperties)
{
	vkGetPhysicalDeviceFormatProperties2(Handle, Format, FormatProperties);
}


/*
	Get Physical Device Display Properties
 */
VkResult VulkanPhysicalDevice::GetPhysicalDeviceDisplayPropertiesKHR(uint32_t* PropertyCount, VkDisplayPropertiesKHR* Properties)
{
	return vkGetPhysicalDeviceDisplayPropertiesKHR(Handle, PropertyCount, Properties);
}

VkResult VulkanPhysicalDevice::GetPhysicalDeviceDisplayProperties2KHR(uint32_t* PropertyCount, VkDisplayProperties2KHR* Properties)
{
	return vkGetPhysicalDeviceDisplayProperties2KHR(Handle, PropertyCount, Properties);
}

/*
	Get	Physical Device	Image Format Properties
 */
VkResult VulkanPhysicalDevice::GetPhysicalDeviceImageFormatProperties(VkFormat format, VkImageType  type,
                                                                      VkImageTiling tiling, VkImageUsageFlags usage,
                                                                      VkImageCreateFlags flags, VkImageFormatProperties* pImageFormatProperties)
{
	return vkGetPhysicalDeviceImageFormatProperties(Handle, format, type, tiling, usage, flags, pImageFormatProperties);
}

VkResult VulkanPhysicalDevice::GetPhysicalDeviceImageFormatProperties2(const VkPhysicalDeviceImageFormatInfo2* ImageFormatInfo,
																	   VkImageFormatProperties2* pImageFormatProperties)
{
	return vkGetPhysicalDeviceImageFormatProperties2(Handle, ImageFormatInfo, pImageFormatProperties);
}

VkResult VulkanPhysicalDevice::GetPhysicalDeviceImageFormatProperties2KHR(const VkPhysicalDeviceImageFormatInfo2* ImageFormatInfo,
	                                                                      VkImageFormatProperties2* ImageFormatProperties)
{
	return vkGetPhysicalDeviceImageFormatProperties2(Handle, ImageFormatInfo, ImageFormatProperties);
}

/*
	Surface
*/
VkResult VulkanPhysicalDevice::GetPhysicalDeviceSurfaceCapabilitiesKHR(VkSurfaceKHR Surface, VkSurfaceCapabilitiesKHR* SurfaceCapabilities)
{
	return vkGetPhysicalDeviceSurfaceCapabilitiesKHR(Handle, Surface, SurfaceCapabilities);
}

VkResult VulkanPhysicalDevice::GetPhysicalDeviceSurfaceFormatsKHR(VkSurfaceKHR Surface, uint32_t* SurfaceFormatCount, VkSurfaceFormatKHR* SurfaceFormats)
{
	return vkGetPhysicalDeviceSurfaceFormatsKHR(Handle, Surface, SurfaceFormatCount, SurfaceFormats);
}

VkResult VulkanPhysicalDevice::GetPhysicalDeviceSurfacePresentModesKHR(VkSurfaceKHR Surface, uint32_t* PresentModeCount, VkPresentModeKHR* PresentModes)
{
	return vkGetPhysicalDeviceSurfacePresentModesKHR(Handle, Surface, PresentModeCount, PresentModes);
}

VkResult VulkanPhysicalDevice::GetPhysicalDeviceSurfaceSupportKHR(std::uint32_t QueueFamilyIndex, VkSurfaceKHR Surface, VkBool32* Supported)
{
	return vkGetPhysicalDeviceSurfaceSupportKHR(Handle, QueueFamilyIndex, Surface, Supported);
}

/*
	Device
*/
VkResult VulkanPhysicalDevice::CreateDevice(const VkDeviceCreateInfo* CreateInfo, const VkAllocationCallbacks* Allocator, VkDevice* Device)
{
	return vkCreateDevice(Handle, CreateInfo, Allocator, Device);
}