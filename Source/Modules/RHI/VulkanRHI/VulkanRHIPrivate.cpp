#include "VulkanRHI.h"
#include "VulkanObjects/Instance/VulkanInstance.h"
#include "VulkanObjects/Device/VulkanDevice.h"
#include <iostream>


void VulkanRHI::CreateInstance()
{
    /*
        待修改
    */
    std::vector<const char*> InstanceExtensions =
    {
        "VK_KHR_surface",
    };
#ifdef RHI_USE_XCB
    InstanceExtensions.emplace_back("VK_KHR_xcb_surface");
#endif

#ifdef RHI_USE_Xlib
    InstanceExtensions.emplace_back("VK_KHR_xlib_surface");
#endif

#ifdef RHI_USE_WIN32_KHR
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
