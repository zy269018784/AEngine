#include "VulkanRenderPassCreateInfo.h"

VkRenderPassCreateInfo VulkanRenderPassCreateInfo::GetHandle() const
{
    return Handle;
}

bool VulkanRenderPassCreateInfo::CheckError() const {
    bool Result = true;
    return Result;
}