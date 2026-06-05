#pragma once
#include "RHI/RHIObjects/FrameBuffer/RHIAttachment.h"
#include "VulkanRHI/VulkanObjects//Resource/VulkanImageView.h"
class VulkanTexture;
class VulkanAttachment : public RHIAttachment
{
public:
    VulkanAttachment(RHIAttachmentType InType, RHITexture *InTexture);
    VulkanAttachment(RHIAttachmentType InType, RHIPixelFormat InFormat);
    VulkanAttachment(RHIAttachmentType InType, RHIPixelFormat InFormat, VkImageView InImageView);
    ~VulkanAttachment();
    VkImageView GetHandle() const;
private:
    VkImageView ImageView;
};
