//
// Created by 26901 on 2026/4/23.
//

#ifndef ENGINE_VKIMAGEMEMORYBARRIER2_H
#define ENGINE_VKIMAGEMEMORYBARRIER2_H


/*
 * Vulkan 1.3 Core          VK_KHR_synchronization2
 */
/*
*   typedef struct VkImageMemoryBarrier2 {
*       VkStructureType sType;
*       const void* pNext;
*       VkPipelineStageFlags2 srcStageMask;
*       VkAccessFlags2 srcAccessMask;
*       VkPipelineStageFlags2 dstStageMask;
*       VkAccessFlags2 dstAccessMask;
*       VkImageLayout oldLayout;
*       VkImageLayout newLayout;
*       uint32_t srcQueueFamilyIndex;
*       uint32_t dstQueueFamilyIndex;
*       VkImage image;
*       VkImageSubresourceRange subresourceRange;
*   } VkImageMemoryBarrier2;
 */
class VkImageMemoryBarrier2 {

};



#endif //ENGINE_VKIMAGEMEMORYBARRIER2_H
