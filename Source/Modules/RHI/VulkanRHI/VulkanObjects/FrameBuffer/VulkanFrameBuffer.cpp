#include "VulkanObjects/FrameBuffer/VulkanFrameBuffer.h"
#include  "VulkanObjects/PhysicalDevice/VulkanPhysicalDevice.h"
#include "VulkanObjects/Texture/VulkanTexture.h"
#include "VulkanObjects/RenderPass/VulkanAttachment.h"
#include "VulkanObjects/RenderPass/VulkanRenderPass.h"
#include "VulkanObjects/RenderPass/VulkanColorAttachment.h"
#include "VulkanObjects/RenderPass/VulkanDepthAttachment.h"
#include "VulkanObjects/Device/VulkanDevice.h"
#include <array>
#include <iostream>
#include <stdexcept>

VulkanFrameBuffer::VulkanFrameBuffer(VulkanDevice* InDevice, VulkanRenderPass* InRenderPass, VkExtent2D SwapChainExtent,
   std::vector<RHIColorAttachment *> &InColorAttachments, std::vector<RHIDepthAttachment *> &InDepthAttachments)
    : Device(InDevice)
{
    std::vector<VkImageView> attachments;
    for (int i = 0; i < InColorAttachments.size(); i++)
    {
        attachments.emplace_back(static_cast<VulkanColorAttachment *>(InColorAttachments[i])->GetHandle());
    }
    for (int i = 0; i < InDepthAttachments.size(); i++)
    {
        attachments.emplace_back(static_cast<VulkanDepthAttachment *>(InDepthAttachments[i])->GetHandle());
    }

    VkFramebufferCreateInfo CreateInfo{};
    CreateInfo.sType            = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
    CreateInfo.renderPass       = InRenderPass->GetHandle();
    CreateInfo.width            = SwapChainExtent.width;
    CreateInfo.height           = SwapChainExtent.height;
    CreateInfo.layers           = 1;
    CreateInfo.attachmentCount  = attachments.size();
    CreateInfo.pAttachments     = attachments.data();
    InDevice->GetPhysicalDevice();
    VkResult Result = CreateFramebuffer(&CreateInfo, nullptr);
    if (Result != VK_SUCCESS)
    {
        throw std::runtime_error("failed to create framebuffer!");
    }

    std::cout << "framebuffer " << Handle << std::endl;
}

VulkanFrameBuffer::~VulkanFrameBuffer()
{
    DestroyFramebuffer(nullptr);
}

VkFramebuffer VulkanFrameBuffer::GetHandle() const
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
