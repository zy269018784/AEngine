#include "VulkanRHI/VulkanObjects/SwapChain/VulkanSwapChain.h"
#include "VulkanRHI/VulkanObjects/Device/VulkanDevice.h"

VkResult VulkanSwapChain::AcquireNextImageKHR(uint64_t Timeout, VkSemaphore  Semaphore, VkFence Fence, uint32_t* ImageIndex)
{
    return dynamic_cast<VulkanDevice *>(Device)->AcquireNextImageKHR(Handle, Timeout, Semaphore, Fence, ImageIndex);
}

VkResult VulkanSwapChain::GetSwapchainImagesKHR(uint32_t* SwapchainImageCount, VkImage* SwapchainImages)
{
    return dynamic_cast<VulkanDevice *>(Device)->GetSwapchainImagesKHR(Handle, SwapchainImageCount, SwapchainImages);
}





