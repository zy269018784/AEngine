#include "VulkanObjects/Instance/VulkanInstance.h"

/*
    Query the version of instance-level functionality supported by the implementation
*/
VkResult VulkanInstance::EnumerateInstanceVersion(uint32_t* pApiVersion)
{
    return vkEnumerateInstanceVersion(pApiVersion);
}

/*
    Query the available layers
*/
VkResult VulkanInstance::EnumerateInstanceLayerProperties(uint32_t* pPropertyCount, VkLayerProperties* pProperties)
{
    return vkEnumerateInstanceLayerProperties(pPropertyCount, pProperties);
}

/*
    Query the available instance extensions
*/
VkResult VulkanInstance::EnumerateInstanceExtensionProperties(const char* pLayerName, uint32_t* pPropertyCount, VkExtensionProperties* pProperties)
{
    return vkEnumerateInstanceExtensionProperties(pLayerName, pPropertyCount, pProperties);
}

/*
    Query the available instance extensions
*/
VkResult VulkanInstance::EnumeratePhysicalDevices(std::uint32_t* PhysicalDeviceCount, VkPhysicalDevice* PhysicalDevices)
{
    return vkEnumeratePhysicalDevices(Handle, PhysicalDeviceCount, PhysicalDevices);
}

/*
    Retrieve a list of the device groups present in the system
*/
VkResult VulkanInstance::EnumeratePhysicalDeviceGroups(std::uint32_t* PhysicalDeviceGroupCount, VkPhysicalDeviceGroupProperties* PhysicalDeviceGroupProperties)
{
    return vkEnumeratePhysicalDeviceGroups(Handle, PhysicalDeviceGroupCount, PhysicalDeviceGroupProperties);
}

void VulkanInstance::DestroySurfaceKHR(VkSurfaceKHR Surface, const VkAllocationCallbacks* Allocator)
{
    vkDestroySurfaceKHR(Handle, Surface, Allocator);
}

