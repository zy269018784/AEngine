#include "VulkanRHI/VulkanObjects//RenderPass/VulkanRenderPass.h"
#include "VulkanRHI/VulkanObjects//Device/VulkanDevice.h"
#include "VulkanRHI/VulkanObjects//Core/VulkanCore.h"
#include <iostream>


VulkanRenderPass::VulkanRenderPass(RHIDevice* InDevice,
    std::vector<RHIAttachment *> InColorAttachments, std::vector<RHIAttachment *> InDepthAttachments)
    : RHIRenderPass(InDevice, InColorAttachments, InDepthAttachments)
{
#if 0
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
        ColorAttachment.loadOp                  = ToVkLoadOp(InColorAttachments[i]->GetLoadOp());
        ColorAttachment.storeOp                 = ToVkStoreOp(InColorAttachments[i]->GetStoreOp());
        ColorAttachment.stencilLoadOp           = ToVkLoadOp(InColorAttachments[i]->GetStencilLoadOp());
        ColorAttachment.stencilStoreOp          = ToVkStoreOp(InColorAttachments[i]->GetStencilStoreOp());
        ColorAttachment.initialLayout           = VK_IMAGE_LAYOUT_UNDEFINED;
        ColorAttachment.finalLayout             = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
        if (3 == InColorAttachments.size())
            ColorAttachment.finalLayout             = VK_IMAGE_LAYOUT_READ_ONLY_OPTIMAL;

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
#endif
}

VulkanRenderPass::~VulkanRenderPass()
{
    dynamic_cast<VulkanDevice *>(Device)->DestroyRenderPass(Handle, nullptr);
}

VkRenderPass VulkanRenderPass::GetHandle()
{
    return Handle;
}

void VulkanRenderPass::Create1_0()
{
    std::cout << "VulkanRenderPass " << ColorAttachments.size() << " " << DepthAttachments.size() << std::endl;
    std::vector<VkAttachmentDescription> AttachmentDescriptions;
    /*
     * 1. Color Attachments
     */
    std::vector<VkAttachmentReference> ColorAttachmentRefs;
    for (int i = 0; i < ColorAttachments.size(); i++)
    {
        VkAttachmentDescription ColorAttachment{};
        ColorAttachment.format                  = ToVkFormat(ColorAttachments[i]->GetRHIPixelFormat());
        ColorAttachment.samples                 = VK_SAMPLE_COUNT_1_BIT;
        ColorAttachment.loadOp                  = ToVkLoadOp(ColorAttachments[i]->GetLoadOp());
        ColorAttachment.storeOp                 = ToVkStoreOp(ColorAttachments[i]->GetStoreOp());
        ColorAttachment.stencilLoadOp           = ToVkLoadOp(ColorAttachments[i]->GetStencilLoadOp());
        ColorAttachment.stencilStoreOp          = ToVkStoreOp(ColorAttachments[i]->GetStencilStoreOp());
        ColorAttachment.initialLayout           = VK_IMAGE_LAYOUT_UNDEFINED;
        ColorAttachment.finalLayout             = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
        if (3 == ColorAttachments.size())
            ColorAttachment.finalLayout             = VK_IMAGE_LAYOUT_READ_ONLY_OPTIMAL;

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
    DepthAttachment.format                  = ToVkFormat(DepthAttachments[0]->GetAttachmentType());
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

void VulkanRenderPass::Create1_2()
{
    std::cout << "VulkanRenderPass " << ColorAttachments.size() << " " << DepthAttachments.size() << std::endl;
    std::vector<VkAttachmentDescription2> AttachmentDescriptions;

    /*
     * 1. Color Attachments
     */
    std::vector<VkAttachmentReference2> ColorAttachmentRefs;
    for (int i = 0; i < ColorAttachments.size(); i++)
    {
        VkAttachmentDescription2 ColorAttachment{};
        ColorAttachment.sType                   = VK_STRUCTURE_TYPE_ATTACHMENT_DESCRIPTION_2;
        ColorAttachment.pNext                   = nullptr;
        ColorAttachment.flags                   = 0;
        ColorAttachment.format                  = ToVkFormat(ColorAttachments[i]->GetRHIPixelFormat());
        ColorAttachment.samples                 = VK_SAMPLE_COUNT_1_BIT;
        ColorAttachment.loadOp                  = ToVkLoadOp(ColorAttachments[i]->GetLoadOp());
        ColorAttachment.storeOp                 = ToVkStoreOp(ColorAttachments[i]->GetStoreOp());
        ColorAttachment.stencilLoadOp           = ToVkLoadOp(ColorAttachments[i]->GetStencilLoadOp());
        ColorAttachment.stencilStoreOp          = ToVkStoreOp(ColorAttachments[i]->GetStencilStoreOp());
        ColorAttachment.initialLayout           = VK_IMAGE_LAYOUT_UNDEFINED;
        ColorAttachment.finalLayout             = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
        if (3 == ColorAttachments.size())
            ColorAttachment.finalLayout         = VK_IMAGE_LAYOUT_READ_ONLY_OPTIMAL;

        AttachmentDescriptions.emplace_back(ColorAttachment);

        VkAttachmentReference2 ColorAttachmentRef{};
        ColorAttachmentRef.sType                = VK_STRUCTURE_TYPE_ATTACHMENT_REFERENCE_2;
        ColorAttachmentRef.pNext                = nullptr;
        ColorAttachmentRef.attachment           = i;
        ColorAttachmentRef.layout               = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
        ColorAttachmentRef.aspectMask           = VK_IMAGE_ASPECT_COLOR_BIT;
        ColorAttachmentRefs.emplace_back(ColorAttachmentRef);
    }

    /*
     * 2. Depth Attachments
     */
    VkAttachmentDescription2 DepthAttachment{};
    DepthAttachment.sType                       = VK_STRUCTURE_TYPE_ATTACHMENT_DESCRIPTION_2;
    DepthAttachment.pNext                       = nullptr;
    DepthAttachment.flags                       = 0;
    DepthAttachment.format                      = ToVkFormat(DepthAttachments[0]->GetAttachmentType());
    DepthAttachment.samples                     = VK_SAMPLE_COUNT_1_BIT;
    DepthAttachment.loadOp                      = VK_ATTACHMENT_LOAD_OP_CLEAR;    // 重要：清除深度
    DepthAttachment.storeOp                     = VK_ATTACHMENT_STORE_OP_DONT_CARE;
    DepthAttachment.stencilLoadOp               = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    DepthAttachment.stencilStoreOp              = VK_ATTACHMENT_STORE_OP_DONT_CARE;
    DepthAttachment.initialLayout               = VK_IMAGE_LAYOUT_UNDEFINED;
    DepthAttachment.finalLayout                 = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
    AttachmentDescriptions.emplace_back(DepthAttachment);

    VkAttachmentReference2 DepthAttachmentRef{};
    DepthAttachmentRef.sType                    = VK_STRUCTURE_TYPE_ATTACHMENT_REFERENCE_2;
    DepthAttachmentRef.pNext                    = nullptr;
    DepthAttachmentRef.attachment               = static_cast<uint32_t>(ColorAttachmentRefs.size());
    DepthAttachmentRef.layout                   = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
    DepthAttachmentRef.aspectMask               = VK_IMAGE_ASPECT_DEPTH_BIT | VK_IMAGE_ASPECT_STENCIL_BIT;

    /*
     * 3. Subpass Description
     */
    VkSubpassDescription2 Subpass{};
    Subpass.sType                               = VK_STRUCTURE_TYPE_SUBPASS_DESCRIPTION_2;
    Subpass.pNext                               = nullptr;
    Subpass.flags                               = 0;
    Subpass.pipelineBindPoint                   = VK_PIPELINE_BIND_POINT_GRAPHICS;
    Subpass.viewMask                            = 0;  // 单视图渲染
    Subpass.inputAttachmentCount                = 0;
    Subpass.pInputAttachments                   = nullptr;
    Subpass.colorAttachmentCount                = static_cast<uint32_t>(ColorAttachmentRefs.size());
    Subpass.pColorAttachments                   = ColorAttachmentRefs.data();
    Subpass.pResolveAttachments                 = nullptr;
    Subpass.pDepthStencilAttachment             = &DepthAttachmentRef;
    Subpass.preserveAttachmentCount             = 0;
    Subpass.pPreserveAttachments                = nullptr;

    /*
     * 4. Subpass Dependencies (可选)
     * 如果需要外部依赖，可以添加
     */
    std::vector<VkSubpassDependency2> Dependencies;
    // 如果需要在RenderPass开始时等待外部操作完成，可以添加依赖
    // 例如等待之前的Compute Shader完成
    /*
    VkSubpassDependency2 ExternalDependency{};
    ExternalDependency.sType                    = VK_STRUCTURE_TYPE_SUBPASS_DEPENDENCY_2;
    ExternalDependency.pNext                    = nullptr;
    ExternalDependency.srcSubpass               = VK_SUBPASS_EXTERNAL;
    ExternalDependency.dstSubpass               = 0;
    ExternalDependency.srcStageMask             = VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT;
    ExternalDependency.dstStageMask             = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    ExternalDependency.srcAccessMask            = VK_ACCESS_SHADER_WRITE_BIT;
    ExternalDependency.dstAccessMask            = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
    ExternalDependency.dependencyFlags          = 0;
    ExternalDependency.viewOffset               = 0;
    Dependencies.emplace_back(ExternalDependency);
    */

    /*
     * 5. Create RenderPass with VkRenderPassCreateInfo2
     */
    VkRenderPassCreateInfo2 CreateInfo{};
    CreateInfo.sType                            = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO_2;
    CreateInfo.pNext                            = nullptr;
    CreateInfo.flags                            = 0;
    CreateInfo.attachmentCount                  = static_cast<uint32_t>(AttachmentDescriptions.size());
    CreateInfo.pAttachments                     = AttachmentDescriptions.data();
    CreateInfo.subpassCount                     = 1;
    CreateInfo.pSubpasses                       = &Subpass;
    CreateInfo.dependencyCount                  = static_cast<uint32_t>(Dependencies.size());
    CreateInfo.pDependencies                    = Dependencies.empty() ? nullptr : Dependencies.data();
    CreateInfo.correlatedViewMaskCount          = 0;  // 不使用多视图渲染
    CreateInfo.pCorrelatedViewMasks             = nullptr;

    // 使用 vkCreateRenderPass2 而不是 vkCreateRenderPass
    VkResult Result = dynamic_cast<VulkanDevice *>(Device)->CreateRenderPass2(&CreateInfo, nullptr, &Handle);
    if (VK_SUCCESS != Result)
    {
        std::cout << "vkCreateRenderPass2 failed" << std::endl;
        return;
    }
    std::cout << "vkCreateRenderPass2 ok " << Handle << std::endl;
}


void VulkanRenderPass::Create()
{
    Create1_2();
}