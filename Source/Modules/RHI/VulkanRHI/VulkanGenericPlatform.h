#pragma once
#include "Vulkan.h"
#include "VulkanObjects/Device/VulkanDevice.h"

class FVulkanGenericPlatform
{
public:
	// Allow the platform code to restrict the device features
	static void RestrictEnabledPhysicalDeviceFeatures(VkPhysicalDeviceFeatures& InOutFeaturesToEnable)
	{
		// Disable everything sparse-related
		InOutFeaturesToEnable.shaderResourceResidency = VK_FALSE;
		InOutFeaturesToEnable.shaderResourceMinLod = VK_FALSE;
		InOutFeaturesToEnable.sparseBinding = VK_FALSE;
		InOutFeaturesToEnable.sparseResidencyBuffer = VK_FALSE;
		InOutFeaturesToEnable.sparseResidencyImage2D = VK_FALSE;
		InOutFeaturesToEnable.sparseResidencyImage3D = VK_FALSE;
		InOutFeaturesToEnable.sparseResidency2Samples = VK_FALSE;
		InOutFeaturesToEnable.sparseResidency4Samples = VK_FALSE;
		InOutFeaturesToEnable.sparseResidency8Samples = VK_FALSE;
		InOutFeaturesToEnable.sparseResidencyAliased = VK_FALSE;
	}

	// Allow platforms to add extension features to the DeviceInfo pNext chain
	static void EnablePhysicalDeviceFeatureExtensions(VkDeviceCreateInfo& DeviceInfo, VulkanDevice& Device) {}
};