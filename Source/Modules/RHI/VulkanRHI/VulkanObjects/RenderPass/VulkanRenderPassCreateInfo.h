#pragma once
#include "Vulkan.h"
class VulkanRenderPassCreateInfo
{
public:
    VkRenderPassCreateInfo GetHandle() const;
    bool CheckError() const;
private:
    VkRenderPassCreateInfo Handle;
};


