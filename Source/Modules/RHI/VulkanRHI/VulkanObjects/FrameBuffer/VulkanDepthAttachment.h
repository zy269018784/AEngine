#pragma once
#include "Vulkan.h"
#include "../../../RHI/RHIObjects/FrameBuffer/RHIDepthAttachment.h"
class VulkanDepthAttachment : public RHIDepthAttachment
{
public:
    VulkanDepthAttachment(VkImageView InImageView, RHIDepthAttachmentType InType);
    virtual ~VulkanDepthAttachment();
    VkImageView GetHandle() const;
private:
    VkImageView ImageView;
};