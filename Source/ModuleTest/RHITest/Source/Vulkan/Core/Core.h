#pragma once
#include <vulkan/vulkan.h>
#include <vector>
#include <iostream>
void VulkanInit();
VkInstance CreateInstance();
std::vector<VkPhysicalDevice> EnumeratePhysicalDevices();
void CreateQueue();
void CreateDevices();

extern VkInstance Instance;
extern std::vector<VkPhysicalDevice> PhysicalDevices;
extern std::vector<VkQueueFamilyProperties> QueueFamilyProperties;
extern std::vector<VkDevice> Devices;


