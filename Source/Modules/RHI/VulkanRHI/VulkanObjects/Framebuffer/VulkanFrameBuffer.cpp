#include "VulkanRHI/VulkanObjects/Framebuffer/VulkanFrameBuffer.h"
#include "VulkanRHI/VulkanObjects/Framebuffer/VulkanAttachment.h"
#include "VulkanRHI/VulkanObjects/Device/VulkanDevice.h"
#include "VulkanRHI/VulkanObjects/PhysicalDevice/VulkanPhysicalDevice.h"
#include "VulkanRHI/VulkanObjects/RenderPass/VulkanRenderPass.h"
#include <iostream>
#include <stdexcept>

VulkanFrameBuffer::VulkanFrameBuffer(VulkanDevice* InDevice, VulkanRenderPass* InRenderPass, VkExtent2D SwapChainExtent,
   std::vector<RHIAttachment *> &InColorAttachments, std::vector<RHIAttachment *> &InDepthAttachments)
    : Device(InDevice)
{
    std::vector<VkImageView> attachments;
    for (int i = 0; i < InColorAttachments.size(); i++)
    {
        attachments.emplace_back(static_cast<VulkanAttachment *>(InColorAttachments[i])->GetHandle());
    }
    for (int i = 0; i < InDepthAttachments.size(); i++)
    {
        attachments.emplace_back(static_cast<VulkanAttachment *>(InDepthAttachments[i])->GetHandle());
    }
    std::cout << "VulkanFrameBuffer::VulkanFrameBuffer 2 "
    << InColorAttachments.size() << " "
    << InDepthAttachments.size() << std::endl;
    VkPhysicalDeviceLimits Limits = InDevice->GetPhysicalDevice()->GetPhysicalDeviceLimits();

    VkFramebufferCreateInfo CreateInfo{};
    CreateInfo.sType            = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;

    CreateInfo.renderPass       = InRenderPass->GetHandle();
    std::cout << "VulkanFrameBuffer::VulkanFrameBuffer 4 " << attachments.size() << std::endl;
    CreateInfo.width            = SwapChainExtent.width;
    CreateInfo.height           = SwapChainExtent.height;
    CreateInfo.layers           = 1;
    CreateInfo.attachmentCount  = attachments.size();
    CreateInfo.pAttachments     = attachments.data();

    /*
     *      • VUID-VkFramebufferCreateInfo-layers-00889
     *      layers must be greater than 0
     * */
    if (CreateInfo.layers <= 0)
    {
        CreateInfo.layers = 1;
    }
    /*
     *      • VUID-VkFramebufferCreateInfo-layers-00890
     *      layers must be less than or equal to maxFramebufferLayers
     * */
    if (Limits.maxFramebufferWidth < CreateInfo.layers)
    {
        CreateInfo.layers = Limits.maxFramebufferLayers;
    }
    /*
     *      • VUID-VkFramebufferCreateInfo-width-00885
     *      width must be greater than 0
     * */
    if (CreateInfo.width <= 0)
    {
        CreateInfo.width = 1;
    }
    /*
     *      • VUID-VkFramebufferCreateInfo-width-00886
     *      width must be less than or equal to maxFramebufferWidth
     * */
    if (Limits.maxFramebufferWidth < CreateInfo.width)
    {
        CreateInfo.width = Limits.maxFramebufferWidth;
    }
    /*
     *      • VUID-VkFramebufferCreateInfo-height-00887
     *      height must be greater than 0
     * */
    if (CreateInfo.height <= 0)
    {
        CreateInfo.height = 1;
    }
    /*
     *      • VUID-VkFramebufferCreateInfo-height-00888
     *      height must be less than or equal to maxFramebufferHeight
     * */
    if (Limits.maxFramebufferHeight < CreateInfo.height)
    {
        CreateInfo.height = Limits.maxFramebufferHeight;
    }
    std::cout << "VulkanFrameBuffer::VulkanFrameBuffer 5" << std::endl;
    VkResult Result = CreateFramebuffer(&CreateInfo, nullptr);
    if (Result != VK_SUCCESS)
    {
        throw std::runtime_error("failed to create framebuffer!");
    }
    std::cout << "VulkanFrameBuffer::VulkanFrameBuffer 6" << std::endl;
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

void VulkanFrameBuffer::Bind() const {

}

VkResult VulkanFrameBuffer::CreateFramebuffer(const VkFramebufferCreateInfo* CreateInfo, const VkAllocationCallbacks* Allocator)
{
    return Device->CreateFramebuffer(CreateInfo, Allocator, &Handle);
}

void VulkanFrameBuffer::DestroyFramebuffer(const VkAllocationCallbacks* Allocator)
{
    Device->DestroyFramebuffer(Handle, Allocator);
}
