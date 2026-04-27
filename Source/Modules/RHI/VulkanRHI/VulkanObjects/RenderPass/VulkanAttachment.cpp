#if 0
#include "VulkanAttachment.h"

VulkanAttachment::VulkanAttachment(VkImageView InImageView)
    : ImageView(InImageView)
{

}

VulkanAttachment::~VulkanAttachment()
{

}

VkImageView VulkanAttachment::GetHandle() const
{
    return ImageView;
}
#endif