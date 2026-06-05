#pragma once
#include "VulkanRHI/Vulkan.h"
class VulkanPhysicalDevice;
class VulkanPhysicalDeviceFeatures
{
public:
    VulkanPhysicalDeviceFeatures(VulkanPhysicalDevice *InPhysicalDevice);
    ~VulkanPhysicalDeviceFeatures();
    void Print(int Tabs);
private:
public:
    VulkanPhysicalDevice *PhysicalDevice;
    VkPhysicalDeviceFeatures					Features;
    VkPhysicalDeviceFeatures2					Features2;
    VkPhysicalDeviceVulkan11Features 		    Vulkan11Features;
    VkPhysicalDeviceVulkan12Features 		    Vulkan12Features;
    VkPhysicalDeviceVulkan13Features 		    Vulkan13Features;
    VkPhysicalDeviceMaintenance4FeaturesKHR		Maintenance4Features;
    VkPhysicalDeviceMaintenance5FeaturesKHR		Maintenance5Features;
    VkPhysicalDeviceMaintenance6FeaturesKHR		Maintenance6Features;
    //VkPhysicalDeviceMaintenance7FeaturesKHR		Maintenance7Features;
    //VkPhysicalDeviceMaintenance8FeaturesKHR		Maintenance8Features;
    //VkPhysicalDeviceMaintenance9FeaturesKHR		Maintenance9Features;

    /*
        物理设备支持的加速结构特性
    */
    VkPhysicalDeviceAccelerationStructureFeaturesKHR AccelerationStructureFeatures{};
};

