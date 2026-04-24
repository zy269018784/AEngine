#include "VulkanImageCreateInfo.h"
#include <iostream>

VkImageCreateInfo VulkanImageCreateInfo::GetHandle() const
{
    return Handle;
}

bool VulkanImageCreateInfo::CheckError() const {
    bool Result = true;

    /*
     *  • VUID-VkImageCreateInfo-extent-00944
     *  extent.width must be greater than 0
     */
    if (Handle.extent.width <= 0)
    {
        std::cout << "VUID-VkImageCreateInfo-extent-00944" << std::endl;
        Result = false;
    }
    /*
     *  • VUID-VkImageCreateInfo-extent-00945
     *  extent.height must be greater than 0
     */
    if (Handle.extent.height <= 0)
    {
        std::cout << "VUID-VkImageCreateInfo-extent-00945" << std::endl;
        Result = false;
    }
    /*
     *  • VUID-VkImageCreateInfo-extent-00946
     *  extent.depth must be greater than 0
     */
    if (Handle.extent.depth <= 0)
    {
        std::cout << "VUID-VkImageCreateInfo-extent-00946" << std::endl;
        Result = false;
    }
    /*
     *  • VUID-VkImageCreateInfo-mipLevels-00947
     *  mipLevels must be greater than 0
     */
    if (Handle.extent.mipLevels <= 0)
    {
        std::cout << "VUID-VkImageCreateInfo-mipLevels-00947" << std::endl;
        Result = false;
    }
    /*
     *  • VUID-VkImageCreateInfo-arrayLayers-00948
     *  arrayLayers must be greater than 0
     */
    if (Handle.extent.arrayLayers <= 0)
    {
        std::cout << "VUID-VkImageCreateInfo-arrayLayers-00948" << std::endl;
        Result = false;
    }
    return Result;
}