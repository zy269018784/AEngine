#include "Core.h"
VkInstance Instance;
std::vector<VkPhysicalDevice> PhysicalDevices;
void VulkanInit()
{
    Instance = CreateInstance();
    std::cout << "VkInstance " << Instance << std::endl;

    PhysicalDevices = EnumeratePhysicalDevices();
}