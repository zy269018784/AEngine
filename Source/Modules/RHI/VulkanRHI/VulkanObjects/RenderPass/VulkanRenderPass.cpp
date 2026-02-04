#include "VulkanObjects/RenderPass/VulkanRenderPass.h"
#include "VulkanObjects/Device/VulkanDevice.h"
#include <iostream>

VulkanRenderPass::VulkanRenderPass()
{

}


VulkanRenderPass::VulkanRenderPass(VulkanDevice* InDevice, VkFormat InFormat)
    : Device(InDevice)
{
    std::vector<VkAttachmentDescription> Attachments;

    VkAttachmentDescription ColorAttachment{};
    ColorAttachment.format                  = InFormat;
    ColorAttachment.samples                 = VK_SAMPLE_COUNT_1_BIT;
    ColorAttachment.loadOp                  = VK_ATTACHMENT_LOAD_OP_CLEAR;
    ColorAttachment.storeOp                 = VK_ATTACHMENT_STORE_OP_STORE;
    ColorAttachment.stencilLoadOp           = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    ColorAttachment.stencilStoreOp          = VK_ATTACHMENT_STORE_OP_DONT_CARE;
    ColorAttachment.initialLayout           = VK_IMAGE_LAYOUT_UNDEFINED;
    ColorAttachment.finalLayout             = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
    Attachments.emplace_back(ColorAttachment);

    VkAttachmentReference ColorAttachmentRef{};
    ColorAttachmentRef.attachment           = 0;
    ColorAttachmentRef.layout               = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;


    VkAttachmentDescription DepthAttachment{};
    DepthAttachment.format                  = VK_FORMAT_D24_UNORM_S8_UINT;
    DepthAttachment.samples                 = VK_SAMPLE_COUNT_1_BIT;
    DepthAttachment.loadOp                  = VK_ATTACHMENT_LOAD_OP_CLEAR;    // 重要：清除深度
    DepthAttachment.storeOp                 = VK_ATTACHMENT_STORE_OP_DONT_CARE;
    DepthAttachment.stencilLoadOp           = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    DepthAttachment.stencilStoreOp          = VK_ATTACHMENT_STORE_OP_DONT_CARE;
    DepthAttachment.initialLayout           = VK_IMAGE_LAYOUT_UNDEFINED;
    DepthAttachment.finalLayout             = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
    Attachments.emplace_back(DepthAttachment);

    VkAttachmentReference DepthAttachmentRef{};
    DepthAttachmentRef.attachment           = 1;  // 索引1（颜色是0）
    DepthAttachmentRef.layout               = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

    VkSubpassDescription Subpass{};
    Subpass.pipelineBindPoint               = VK_PIPELINE_BIND_POINT_GRAPHICS;
    Subpass.colorAttachmentCount            = 1;
    Subpass.pColorAttachments               = &ColorAttachmentRef;
    Subpass.pDepthStencilAttachment         = &DepthAttachmentRef;

    VkRenderPassCreateInfo CreateInfo{};
    CreateInfo.sType                        = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
    CreateInfo.attachmentCount              = Attachments.size();
    CreateInfo.pAttachments                 = Attachments.data();
    CreateInfo.subpassCount                 = 1;
    CreateInfo.pSubpasses                   = &Subpass;

    VkResult Result = Device->CreateRenderPass(&CreateInfo, nullptr, &Handle);
    if (VK_SUCCESS != Result)
    {
        std::cout << "vkCreateRenderPass failed" << std::endl;
        return;
    }
    std::cout << "vkCreateRenderPass ok " << Handle << std::endl;
}

VulkanRenderPass::~VulkanRenderPass()
{	
     Device->DestroyRenderPass(Handle, nullptr);
}

VkRenderPass VulkanRenderPass::GetHandle()
{
    return Handle;
}