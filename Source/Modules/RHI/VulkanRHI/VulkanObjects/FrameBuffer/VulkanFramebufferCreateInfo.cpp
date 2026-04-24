#include "VulkanFramebufferCreateInfo.h"

VkFramebufferCreateInfo VulkanFramebufferCreateInfo::GetHandle() const
{
    return Handle;
}

bool VulkanFramebufferCreateInfo::CheckError() const
{
    if (Handle.sType != VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO)
        return false;
    return true;
}