//
// Created by 26901 on 2026/4/23.
//

#ifndef ENGINE_VKBUFFERMEMORYBARRIER2_H
#define ENGINE_VKBUFFERMEMORYBARRIER2_H

/*
 * Vulkan 1.3 Core          VK_KHR_synchronization2
 */
/*
* typedef struct VkBufferMemoryBarrier2 {
    VkStructureType sType;
    const void* pNext;
    VkPipelineStageFlags2 srcStageMask;
    VkAccessFlags2 srcAccessMask;
    VkPipelineStageFlags2 dstStageMask;
    VkAccessFlags2 dstAccessMask;
    uint32_t srcQueueFamilyIndex;
    uint32_t dstQueueFamilyIndex;
    VkBuffer buffer;
    VkDeviceSize offset;
    VkDeviceSize size;
} VkBufferMemoryBarrier2;
 */
class VkBufferMemoryBarrier2 {

};



#endif //ENGINE_VKBUFFERMEMORYBARRIER2_H
