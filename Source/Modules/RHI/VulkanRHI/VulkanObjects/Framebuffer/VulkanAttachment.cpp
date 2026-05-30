#include "VulkanRHI/VulkanObjects/Framebuffer/VulkanAttachment.h"
#include "VulkanRHI/VulkanObjects/Texture/VulkanTexture.h"

VulkanAttachment::VulkanAttachment(RHIAttachmentType InType, RHITexture *InTexture)
    : RHIAttachment(InType, InTexture)
{

}

VulkanAttachment::VulkanAttachment(RHIAttachmentType InType, RHIPixelFormat InFormat)
    : RHIAttachment(InType, InFormat)
{

}

VulkanAttachment::VulkanAttachment(RHIAttachmentType InType, RHIPixelFormat InFormat, VkImageView InImageView)
    : RHIAttachment(InType, InFormat), ImageView(InImageView)
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
