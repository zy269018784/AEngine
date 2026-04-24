#pragma once
#include "Vulkan.h"
class VulkanImageCreateInfo
{
public:
    VkImageCreateInfo GetHandle() const;
    bool CheckError() const;
private:
    VkImageCreateInfo Handle;
};


