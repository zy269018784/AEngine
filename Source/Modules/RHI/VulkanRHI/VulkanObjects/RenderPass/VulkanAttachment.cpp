#include "VulkanAttachment.h"

VulkanAttachment::VulkanAttachment(RHIAttachmentType InType, RHIPixelFormat InPixelFormat,  VkImageView InImageView)
    : RHIAttachment(InType, InPixelFormat), ImageView(InImageView)
{

}

VulkanAttachment::~VulkanAttachment()
{

}

VkImageView VulkanAttachment::GetHandle() const
{
    return ImageView;
}