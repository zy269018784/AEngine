#include "VulkanColorAttachment.h"

VulkanColorAttachment::VulkanColorAttachment(VkImageView InImageView, RHIAttachmentType InType, RHIPixelFormat InPixelFormat)
    : ImageView(InImageView), RHIColorAttachment(InType, InPixelFormat)
{

}

VulkanColorAttachment::~VulkanColorAttachment()
{

}


VkImageView VulkanColorAttachment::GetHandle() const
{
    return ImageView;
}