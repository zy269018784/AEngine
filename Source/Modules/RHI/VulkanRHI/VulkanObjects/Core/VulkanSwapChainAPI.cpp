#include "VulkanObjects/SwapChain/VulkanSwapChain.h"

VkResult VulkanSwapChain::AcquireNextImageKHR(uint64_t Timeout, VkSemaphore  Semaphore, VkFence Fence, uint32_t* ImageIndex)
{
    return Device->AcquireNextImageKHR(Handle, Timeout, Semaphore, Fence, ImageIndex);
}

VkResult VulkanSwapChain::GetSwapchainImagesKHR(uint32_t* SwapchainImageCount, VkImage* SwapchainImages)
{
    return Device->GetSwapchainImagesKHR(Handle, SwapchainImageCount, SwapchainImages);
}





