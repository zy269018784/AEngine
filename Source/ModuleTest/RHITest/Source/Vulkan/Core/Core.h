#pragma once
#include <vulkan/vulkan.h>
#include <vector>
#include <iostream>
VkInstance CreateInstance();
std::vector<VkPhysicalDevice> EnumeratePhysicalDevices();
void VulkanInit();

extern VkInstance Instance;
extern std::vector<VkPhysicalDevice> PhysicalDevices;


