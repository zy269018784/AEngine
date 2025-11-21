#include "VulkanObjects/FrameBuffer/VulkanFrameBuffer.h"
#include "VulkanObjects/RenderPass/VulkanRenderPass.h"
#include "VulkanObjects/Device/VulkanDevice.h"
#include <iostream>
#include <stdexcept>

VulkanFrameBuffer::VulkanFrameBuffer(VulkanDevice* InDevice, VulkanRenderPass* InRenderPass, VkExtent2D SwapChainExtent, VkImageView ImageView)
    : Device(InDevice)
{
    VkFramebufferCreateInfo CreateInfo{};
    CreateInfo.sType            = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
    CreateInfo.renderPass       = InRenderPass->GetHandle();
    CreateInfo.attachmentCount  = 1;
    CreateInfo.pAttachments     = &ImageView;
    CreateInfo.width            = SwapChainExtent.width;
    CreateInfo.height           = SwapChainExtent.height;
    CreateInfo.layers           = 1;
    VkResult Result = CreateFramebuffer(&CreateInfo, nullptr);
    if (Result != VK_SUCCESS)
    {
        throw std::runtime_error("failed to create framebuffer!");
    }
}

VulkanFrameBuffer::~VulkanFrameBuffer()
{
    std::cout << "~VulkanFrameBuffer() " << std::endl;
    DestroyFramebuffer(nullptr);
}

VkFramebuffer VulkanFrameBuffer::GetHandle()
{
    return Handle;
}

VkResult VulkanFrameBuffer::CreateFramebuffer(const VkFramebufferCreateInfo* CreateInfo, const VkAllocationCallbacks* Allocator)
{
    return Device->CreateFramebuffer(CreateInfo, Allocator, &Handle);
}

void VulkanFrameBuffer::DestroyFramebuffer(const VkAllocationCallbacks* Allocator)
{
    Device->DestroyFramebuffer(Handle, Allocator);
}