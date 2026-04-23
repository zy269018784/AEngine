#pragma once
#include "Vulkan.h"
class VulkanImage;
class VulkanImageMemoryBarrier
{
public:
    VkImageMemoryBarrier GetHandle() const;
    bool CheckError() const;
private:
    bool CheckNewLayout() const;
    bool CheckSubresourceRange() const;
private:
    VkImageMemoryBarrier Handle;
    VulkanImage *Image;
};

