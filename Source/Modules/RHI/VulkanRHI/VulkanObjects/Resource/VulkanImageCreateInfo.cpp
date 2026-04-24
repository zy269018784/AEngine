#include "VulkanImageCreateInfo.h"


VkImageCreateInfo VulkanImageCreateInfo::GetHandle() const
{
    return Handle;
}

bool VulkanImageCreateInfo::CheckError() const {
    bool Result = true;
    return Result;
}