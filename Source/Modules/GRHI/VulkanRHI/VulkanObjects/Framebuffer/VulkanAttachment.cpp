#include "VulkanRHI/VulkanObjects/Framebuffer/VulkanAttachment.h"
#include "VulkanRHI/VulkanObjects/Texture/VulkanTexture.h"

VulkanAttachment::VulkanAttachment(RHIAttachmentType InType, RHITexture *InTexture, RHIAttachmentLoadOp InLoadOp, RHIAttachmentStoreOp InStoreOp,
    RHIAttachmentLoadOp InStencilLoadOp, RHIAttachmentStoreOp InStencilStoreOp, RHIImageLayout InInitialLayout, RHIImageLayout InFinalLayout)
    : RHIAttachment(InType, InTexture, InLoadOp, InStoreOp, InStencilLoadOp, InStencilStoreOp, InInitialLayout, InFinalLayout)
{

}

VulkanAttachment::VulkanAttachment(RHIAttachmentType InType, RHIPixelFormat InFormat, RHIAttachmentLoadOp InLoadOp, RHIAttachmentStoreOp InStoreOp,
    RHIAttachmentLoadOp InStencilLoadOp, RHIAttachmentStoreOp InStencilStoreOp, RHIImageLayout InInitialLayout, RHIImageLayout InFinalLayout)
    : RHIAttachment(InType, InFormat, InLoadOp, InStoreOp, InStencilLoadOp, InStencilStoreOp, InInitialLayout, InFinalLayout)
{

}

VulkanAttachment::VulkanAttachment(RHIAttachmentType InType, RHIPixelFormat InFormat, VkImageView InImageView, RHIAttachmentLoadOp InLoadOp, RHIAttachmentStoreOp InStoreOp,
    RHIAttachmentLoadOp InStencilLoadOp, RHIAttachmentStoreOp InStencilStoreOp, RHIImageLayout InInitialLayout, RHIImageLayout InFinalLayout)
    : RHIAttachment(InType, InFormat, InLoadOp, InStoreOp, InStencilLoadOp, InStencilStoreOp, InInitialLayout, InFinalLayout), ImageView(InImageView)
{

}

VulkanAttachment::~VulkanAttachment()
{

}

VkImageView VulkanAttachment::GetHandle() const
{
    if (Texture)
        return (dynamic_cast<VulkanTexture *>(Texture))->GetImageView();
    return ImageView;
}
