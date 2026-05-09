#pragma once
#include "VulkanRHI/Vulkan.h"
#include "../../../RHI/RHIObjects/FrameBuffer/RHIColorAttachment.h"

class VulkanColorAttachment : public RHIColorAttachment
{
public:
    VulkanColorAttachment(VkImageView InImageView, RHIAttachmentType InType, RHIPixelFormat InPixelFormat);
    ~VulkanColorAttachment();
    VkImageView GetHandle() const;
private:
    VkImageView ImageView;
};

