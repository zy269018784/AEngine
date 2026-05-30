#include "VulkanRHI/VulkanObjects//RenderPass/VulkanRenderPass.h"
#include "VulkanRHI/VulkanObjects//Device/VulkanDevice.h"
#include "VulkanRHI/VulkanObjects//Core/VulkanCore.h"
#include <iostream>


VulkanRenderPass::VulkanRenderPass(RHIDevice* InDevice,
    std::vector<RHIAttachment *> InColorAttachments, std::vector<RHIAttachment *> InDepthAttachments)
    : RHIRenderPass(InDevice, InColorAttachments, InDepthAttachments)
{
    std::cout << "VulkanRenderPass " << InColorAttachments.size() << " " << InDepthAttachments.size() << std::endl;
    std::vector<VkAttachmentDescription> AttachmentDescriptions;
    /*
     * 1. Color Attachments
     */
    std::vector<VkAttachmentReference> ColorAttachmentRefs;
    for (int i = 0; i < InColorAttachments.size(); i++)
    {
        VkAttachmentDescription ColorAttachment{};
        ColorAttachment.format                  = ToVkFormat(InColorAttachments[i]->GetRHIPixelFormat());
        ColorAttachment.samples                 = VK_SAMPLE_COUNT_1_BIT;
        ColorAttachment.loadOp                  = VK_ATTACHMENT_LOAD_OP_CLEAR;
        ColorAttachment.storeOp                 = VK_ATTACHMENT_STORE_OP_STORE;
        ColorAttachment.stencilLoadOp           = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
        ColorAttachment.stencilStoreOp          = VK_ATTACHMENT_STORE_OP_DONT_CARE;
        ColorAttachment.initialLayout           = VK_IMAGE_LAYOUT_UNDEFINED;
        ColorAttachment.finalLayout             = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
        AttachmentDescriptions.emplace_back(ColorAttachment);

        VkAttachmentReference ColorAttachmentRef{};
        ColorAttachmentRef.attachment           = i;
        ColorAttachmentRef.layout               = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
        ColorAttachmentRefs.emplace_back(ColorAttachmentRef);
    }

    /*
     * 2. Depth Attachments
     */
    VkAttachmentDescription DepthAttachment{};
    DepthAttachment.format                  = ToVkFormat(InDepthAttachments[0]->GetAttachmentType());
    DepthAttachment.samples                 = VK_SAMPLE_COUNT_1_BIT;
    DepthAttachment.loadOp                  = VK_ATTACHMENT_LOAD_OP_CLEAR;    // 重要：清除深度
    DepthAttachment.storeOp                 = VK_ATTACHMENT_STORE_OP_DONT_CARE;
    DepthAttachment.stencilLoadOp           = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    DepthAttachment.stencilStoreOp          = VK_ATTACHMENT_STORE_OP_DONT_CARE;
    DepthAttachment.initialLayout           = VK_IMAGE_LAYOUT_UNDEFINED;
    DepthAttachment.finalLayout             = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
    AttachmentDescriptions.emplace_back(DepthAttachment);

    VkAttachmentReference DepthAttachmentRef{};
    DepthAttachmentRef.attachment           = ColorAttachmentRefs.size();
    DepthAttachmentRef.layout               = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

    /*
     * 3
     */
    VkSubpassDescription Subpass{};
    /*
     *  to do: 只支持图像管线, 不支持其他管线
     */
    Subpass.pipelineBindPoint               = VK_PIPELINE_BIND_POINT_GRAPHICS;
    Subpass.colorAttachmentCount            = ColorAttachmentRefs.size();
    std::cout << "Subpass.colorAttachmentCount " << Subpass.colorAttachmentCount << std::endl;
    Subpass.pColorAttachments               = ColorAttachmentRefs.data();
    Subpass.pDepthStencilAttachment         = &DepthAttachmentRef;

    VkRenderPassCreateInfo CreateInfo{};
    CreateInfo.sType                        = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
    CreateInfo.attachmentCount              = AttachmentDescriptions.size();
    CreateInfo.pAttachments                 = AttachmentDescriptions.data();
    CreateInfo.subpassCount                 = 1;
    CreateInfo.pSubpasses                   = &Subpass;
    VkResult Result = dynamic_cast<VulkanDevice *>(Device)->CreateRenderPass(&CreateInfo, nullptr, &Handle);
    if (VK_SUCCESS != Result)
    {
        std::cout << "vkCreateRenderPass failed" << std::endl;
        return;
    }
    std::cout << "vkCreateRenderPass ok " << Handle << std::endl;
}

VulkanRenderPass::~VulkanRenderPass()
{
    std::cout << __FUNCTION__ << " " << Handle << std::endl;
     dynamic_cast<VulkanDevice *>(Device)->DestroyRenderPass(Handle, nullptr);
}

VkRenderPass VulkanRenderPass::GetHandle()
{
    return Handle;
}