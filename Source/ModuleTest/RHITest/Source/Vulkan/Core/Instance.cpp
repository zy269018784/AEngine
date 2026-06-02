#include "Core.h"

VkInstance CreateInstance()
{
    VkInstance Handle;
    std::vector<const char*> InstanceExtensions =
    {
        "VK_KHR_surface",
    };
    InstanceExtensions.emplace_back("VK_KHR_win32_surface");
    std::vector<const char*> InstanceLayers =
    {
        "VK_LAYER_KHRONOS_validation"
   };
    VkApplicationInfo AppInfo{};
    AppInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    AppInfo.pApplicationName = "Hello Triangle";
    AppInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    AppInfo.pEngineName = "No Engine";
    AppInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    // AppInfo.apiVersion = VK_API_VERSION_1_0;
    /*
        1.3 动态状态
        https://vulkan.lunarg.com/doc/view/1.4.321.1/windows/antora/spec/latest/chapters/pipelines.html#VUID-VkGraphicsPipelineCreateInfo-pDynamicStates-03378
    */
    AppInfo.apiVersion = VK_MAKE_API_VERSION(0, 1, 3, 0);
    std::cout << "VulkanInstance " << std::endl;
    VkInstanceCreateInfo CreateInfo{};
    CreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    CreateInfo.pApplicationInfo = &AppInfo;
    CreateInfo.enabledExtensionCount = InstanceExtensions.size();
    CreateInfo.ppEnabledExtensionNames = InstanceExtensions.data();
    CreateInfo.enabledLayerCount = InstanceLayers.size();
    CreateInfo.ppEnabledLayerNames = InstanceLayers.data();
    CreateInfo.pNext = nullptr;

    VkResult ret = vkCreateInstance(&CreateInfo, nullptr, &Handle);
    if (ret != VK_SUCCESS)
    {
        std::cout << "vkCreateInstance ret " << ret << std::endl;
        throw std::runtime_error("failed to create instance!");
    }
    return Handle;
}