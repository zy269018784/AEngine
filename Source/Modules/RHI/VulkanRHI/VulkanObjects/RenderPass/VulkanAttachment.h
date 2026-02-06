#pragma once
#include "../../../RHI/RHIObjects/RenderPass/RHIAttachment.h"
#include "VulkanObjects/Resource/VulkanImageView.h"

class VulkanAttachment : public RHIAttachment
{
public:
    VulkanAttachment(RHIAttachmentType InType, RHIPixelFormat InPixelFormat, VkImageView InImageView);
    ~VulkanAttachment();
    VkImageView GetHandle() const;
private:
    VkImageView ImageView;
};

