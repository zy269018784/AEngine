#include "VulkanObjects/FrameBuffer/VulkanFrameBuffer.h"
#include <array>

#include "VulkanObjects/RenderPass/VulkanRenderPass.h"
#include "VulkanObjects/Device/VulkanDevice.h"
#include <iostream>
#include <stdexcept>

VulkanFrameBuffer::VulkanFrameBuffer(VulkanDevice* InDevice, VulkanRenderPass* InRenderPass, VkExtent2D SwapChainExtent, VkImageView ImageView)
    : Device(InDevice)
{
    CreateDepthBuffer(SwapChainExtent.width, SwapChainExtent.height);

    std::array<VkImageView, 2> attachments = {
        ImageView,  // 颜色附件
        ImageViewDepthBuffer           // 深度附件 ← 使用上面创建的深度图像视图
    };

    VkFramebufferCreateInfo CreateInfo{};
    CreateInfo.sType            = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
    CreateInfo.renderPass       = InRenderPass->GetHandle();
    CreateInfo.attachmentCount  = 1;
    CreateInfo.pAttachments     = &ImageView;
    CreateInfo.width            = SwapChainExtent.width;
    CreateInfo.height           = SwapChainExtent.height;
    CreateInfo.layers           = 1;

    CreateInfo.attachmentCount  = 2;
    CreateInfo.pAttachments     = attachments.data();

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

void VulkanFrameBuffer::CreateDepthBuffer(std::uint32_t Width, std::uint32_t Height)
{
    VkFormat depthFormat = VK_FORMAT_D24_UNORM_S8_UINT;
    // 2. 创建深度图像
    VkImageCreateInfo imageInfo{};
    imageInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
    imageInfo.imageType = VK_IMAGE_TYPE_2D;
    imageInfo.extent = { Width, Height, 1};
    imageInfo.mipLevels = 1;
    imageInfo.arrayLayers = 1;
    imageInfo.format = depthFormat;
    imageInfo.tiling = VK_IMAGE_TILING_OPTIMAL;
    imageInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    imageInfo.usage = VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT; // 关键！
    imageInfo.samples = VK_SAMPLE_COUNT_1_BIT;
    imageInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

    if (Device->CreateImage(&imageInfo, nullptr, &depthImage) != VK_SUCCESS) {
        throw std::runtime_error("");
    }

    // 3. 分配内存
    VkMemoryRequirements memRequirements;
    Device->GetImageMemoryRequirements(depthImage, &memRequirements);

    VkMemoryAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    allocInfo.allocationSize = memRequirements.size;
    allocInfo.memoryTypeIndex = 1;

    if (Device->AllocateMemory(&allocInfo, nullptr, &depthImageMemory) != VK_SUCCESS) {
        throw std::runtime_error("");
    }

    Device->BindImageMemory(depthImage, depthImageMemory, 0);

    // 4. 创建图像视图
    VkImageViewCreateInfo viewInfo{};
    viewInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
    viewInfo.image = depthImage;
    viewInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
    viewInfo.format = depthFormat;
    viewInfo.components = {
        VK_COMPONENT_SWIZZLE_IDENTITY,
        VK_COMPONENT_SWIZZLE_IDENTITY,
        VK_COMPONENT_SWIZZLE_IDENTITY,
        VK_COMPONENT_SWIZZLE_IDENTITY
    };
    viewInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT; // 关键！
    viewInfo.subresourceRange.baseMipLevel = 0;
    viewInfo.subresourceRange.levelCount = 1;
    viewInfo.subresourceRange.baseArrayLayer = 0;
    viewInfo.subresourceRange.layerCount = 1;

    if (Device->CreateImageView(&viewInfo, nullptr, &ImageViewDepthBuffer) != VK_SUCCESS) {
        throw std::runtime_error("");
    }
}