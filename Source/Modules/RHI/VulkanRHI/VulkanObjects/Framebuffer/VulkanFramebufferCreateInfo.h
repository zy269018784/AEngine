#pragma once
#include "VulkanRHI/Vulkan.h"
class VulkanImage;
class VulkanFramebufferCreateInfo
{
public:
    VkFramebufferCreateInfo GetHandle() const;
    bool CheckError() const;
private:
    VkFramebufferCreateInfo Handle;
};