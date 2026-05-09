#include "VulkanImageMemoryBarrier.h"
#include "VulkanRHI/VulkanObjects//Resource/VulkanImage.h"
#include "VulkanRHI/VulkanObjects//Core/VulkanCore.h"
VkImageMemoryBarrier VulkanImageMemoryBarrier::GetHandle() const
{
    return Handle;
}

bool VulkanImageMemoryBarrier::CheckError() const
{
    bool Result = true;
    Result = (CheckNewLayout() && Result);
    return Result;
}

/*
 * • VUID-VkImageMemoryBarrier-newLayout-01198
 * If layouts are not ignored, newLayout must not be VK_IMAGE_LAYOUT_UNDEFINED or
 * VK_IMAGE_LAYOUT_ZERO_INITIALIZED_EXT or VK_IMAGE_LAYOUT_PREINITIALIZED
 */
bool VulkanImageMemoryBarrier::CheckNewLayout() const
{
    if (Handle.newLayout == VK_IMAGE_LAYOUT_UNDEFINED)
        return false;

    if (Handle.newLayout == VK_IMAGE_LAYOUT_ZERO_INITIALIZED_EXT)
        return false;

    if (Handle.newLayout == VK_IMAGE_LAYOUT_PREINITIALIZED)
        return false;

    return true;
}

bool VulkanImageMemoryBarrier::CheckSubresourceRange() const
{
    VkImageCreateInfo CreateInfo = Image->GetCreateInfo();
    /*
     * • VUID-VkImageMemoryBarrier-subresourceRange-01486
     * subresourceRange.baseMipLevel must be less than the mipLevels specified in
     * VkImageCreateInfo when image was created
     */
    if (Handle.subresourceRange.baseMipLevel >= CreateInfo.mipLevels)
        return false;
    /*
    * • VUID-VkImageMemoryBarrier-subresourceRange-01724
    * If subresourceRange.levelCount is not VK_REMAINING_MIP_LEVELS,
    * subresourceRange.baseMipLevel + subresourceRange.levelCount must be less than or equal
    * to the mipLevels specified in VkImageCreateInfo when image was created
    */
    if (Handle.subresourceRange.baseMipLevel + Handle.subresourceRange.levelCount >= CreateInfo.mipLevels)
        return false;

    /*
     * • VUID-VkImageMemoryBarrier-image-09241
     * If image has a color format that is single-plane, then the aspectMask member of
     * subresourceRange must be VK_IMAGE_ASPECT_COLOR_BIT
    */
    if (IsSinglePlane(CreateInfo.format))
    {
        if (Handle.subresourceRange.aspectMask !=  VK_IMAGE_ASPECT_COLOR_BIT)
            return false;
    }
    /*
     * • VUID-VkImageMemoryBarrier-image-09242
     * If image has a color format and is not disjoint, then the aspectMask member of
     * subresourceRange must be VK_IMAGE_ASPECT_COLOR_BIT
     */
    bool IsColorFormat_ = IsColorFormat(CreateInfo.format);
    bool IsDisjoint = ((CreateInfo.flags & VK_IMAGE_CREATE_DISJOINT_BIT) != 0);
    if (IsColorFormat_ && !IsDisjoint)
    {
        if (Handle.subresourceRange.aspectMask != VK_IMAGE_ASPECT_COLOR_BIT)
            return false;
    }

    return true;
}

