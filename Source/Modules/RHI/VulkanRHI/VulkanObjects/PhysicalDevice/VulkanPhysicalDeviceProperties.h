#pragma once
#include "VulkanRHI/Vulkan.h"
class VulkanPhysicalDevice;
class VulkanPhysicalDeviceProperties
{
public:
    VulkanPhysicalDeviceProperties(VulkanPhysicalDevice *InPhysicalDevice);
    ~VulkanPhysicalDeviceProperties();
private:
public:
    VulkanPhysicalDevice *PhysicalDevice;
    VkPhysicalDeviceProperties					Properties;
    VkPhysicalDeviceProperties2					Properties2;
    VkPhysicalDeviceMaintenance3PropertiesKHR	Maintenance3Properties;
    VkPhysicalDeviceMaintenance4PropertiesKHR	Maintenance4Properties;
    VkPhysicalDeviceMaintenance5PropertiesKHR	Maintenance5Properties;
    VkPhysicalDeviceMaintenance6PropertiesKHR	Maintenance6Properties;
    VkPhysicalDeviceMaintenance7PropertiesKHR	Maintenance7Properties;
    //VkPhysicalDeviceMaintenance9PropertiesKHR	Maintenance9Properties;
    /*
        物理设备支持的加速结构属性
    */
    VkPhysicalDeviceAccelerationStructurePropertiesKHR AccelerationStructureProperties{};
    /*
        物理设备支持的光追管线属性
    */
    VkPhysicalDeviceRayTracingPipelinePropertiesKHR  RayTracingPipelineProperties{};
};

