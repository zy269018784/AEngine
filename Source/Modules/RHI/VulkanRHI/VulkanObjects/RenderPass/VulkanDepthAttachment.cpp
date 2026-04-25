#include "VulkanDepthAttachment.h"

VulkanDepthAttachment::VulkanDepthAttachment(VkImageView InImageView, RHIDepthAttachmentType InType)
    : ImageView(InImageView), RHIDepthAttachment(InType)
{

}

VulkanDepthAttachment::~VulkanDepthAttachment()
{

}

VkImageView VulkanDepthAttachment::GetHandle() const
{
    return ImageView;
}