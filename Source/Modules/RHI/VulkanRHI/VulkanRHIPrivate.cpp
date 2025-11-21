#include <VulkanRHI.h>
#include <iostream>


void VulkanRHI::CreateInstance()
{
    /*
        待修改
    */
    std::vector<const char*> InstanceExtensions =
    {
        "VK_KHR_surface",
        //"VK_KHR_win32_surface",
        //"VK_KHR_xcb_surface"
    };
#ifdef OS_IS_LINUX
    InstanceExtensions.emplace_back("VK_KHR_xcb_surface");
#endif

#ifdef OS_IS_Windows
    InstanceExtensions.emplace_back("VK_KHR_win32_surface");
#endif



   std::vector<const char*> InstanceLayers = 
   {
        "VK_LAYER_KHRONOS_validation"
   };

    Instance = new VulkanInstance(InstanceExtensions, InstanceLayers);
    Instance->EnumerateExtensions();
    Instance->EnumerateLayers();
    Instance->EnumeratePhysicalDevices();
}

void VulkanRHI::CreateDevice()
{
   for (std::uint32_t  i = 0; i < Instance->GetVulkanPhysicalDeviceCount(); i++)
   {
       auto Device = Instance->GetVulkanPhysicalDevice(i)->CreateDevice();
       Devices.push_back(Device);
   }
}

void VulkanRHI::CreateCommandPool()
{
    Devices[GPUIndex]->CreateCommandPoolForAllQueueFamliy(Instance->GetVulkanPhysicalDevice(GPUIndex)->QueueFamilyProperties);
    std::cout << "Device->Device->CommandPools.size() " << Devices[GPUIndex]->CommandPools.size() << std::endl;

    GraphicsCommandPool = Devices[GPUIndex]->CommandPools[0];
    ComputeCommandPool  = Devices[GPUIndex]->CommandPools[0];
}
