#include "VulkanObjects/RenderPass/VulkanRenderPass.h"
#include "VulkanObjects/Device/VulkanDevice.h"
#include <iostream>

VulkanRenderPass::VulkanRenderPass()
{

}

//VulkanRenderPass::VulkanRenderPass(VulkanDevice *InDevice, VulkanSwapChain& SwapChain)
//    : Device(InDevice)
//{
//    VkAttachmentDescription ColorAttachment{};
//    ColorAttachment.format              = SwapChain.GetFormat();
//    ColorAttachment.samples             = VK_SAMPLE_COUNT_1_BIT;
//    ColorAttachment.loadOp              = VK_ATTACHMENT_LOAD_OP_CLEAR;
//    ColorAttachment.storeOp             = VK_ATTACHMENT_STORE_OP_STORE;
//    ColorAttachment.stencilLoadOp       = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
//    ColorAttachment.stencilStoreOp      = VK_ATTACHMENT_STORE_OP_DONT_CARE;
//    ColorAttachment.initialLayout       = VK_IMAGE_LAYOUT_UNDEFINED;
//    ColorAttachment.finalLayout         = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
//
//    VkAttachmentReference ColorAttachmentRef{};
//    ColorAttachmentRef.attachment       = 0;
//    ColorAttachmentRef.layout           = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
//
//    VkSubpassDescription Subpass{};
//    Subpass.pipelineBindPoint           = VK_PIPELINE_BIND_POINT_GRAPHICS;
//    Subpass.colorAttachmentCount        = 1;
//    Subpass.pColorAttachments           = &ColorAttachmentRef;
//
//    VkRenderPassCreateInfo CreateInfo{};
//    CreateInfo.sType                    = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
//    CreateInfo.attachmentCount          = 1;
//    CreateInfo.pAttachments             = &ColorAttachment;
//    CreateInfo.subpassCount             = 1;
//    CreateInfo.pSubpasses               = &Subpass;
//
//    VkResult Result =  Device->CreateRenderPass(&CreateInfo, nullptr, &Handle);
//    if (VK_SUCCESS != Result)
//    {
//        std::cout << "vkCreateRenderPass failed" << std::endl;
//        return;
//    }
//    std::cout << "vkCreateRenderPass ok " << Handle << std::endl;
//}

VulkanRenderPass::VulkanRenderPass(VulkanDevice* InDevice, VkFormat InFormat)
    : Device(InDevice)
{
    VkAttachmentDescription ColorAttachment{};
    ColorAttachment.format                  = InFormat;
    ColorAttachment.samples                 = VK_SAMPLE_COUNT_1_BIT;
    ColorAttachment.loadOp                  = VK_ATTACHMENT_LOAD_OP_CLEAR;
    ColorAttachment.storeOp                 = VK_ATTACHMENT_STORE_OP_STORE;
    ColorAttachment.stencilLoadOp           = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    ColorAttachment.stencilStoreOp          = VK_ATTACHMENT_STORE_OP_DONT_CARE;
    ColorAttachment.initialLayout           = VK_IMAGE_LAYOUT_UNDEFINED;
    ColorAttachment.finalLayout             = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

    VkAttachmentReference ColorAttachmentRef{};
    ColorAttachmentRef.attachment           = 0;
    ColorAttachmentRef.layout               = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

    VkSubpassDescription Subpass{};
    Subpass.pipelineBindPoint               = VK_PIPELINE_BIND_POINT_GRAPHICS;
    Subpass.colorAttachmentCount            = 1;
    Subpass.pColorAttachments               = &ColorAttachmentRef;

    VkRenderPassCreateInfo CreateInfo{};
    CreateInfo.sType                        = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
    CreateInfo.attachmentCount              = 1;
    CreateInfo.pAttachments                 = &ColorAttachment;
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