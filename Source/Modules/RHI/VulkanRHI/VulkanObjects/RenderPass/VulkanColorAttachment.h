#pragma once
#include "Vulkan.h"
#include "RHIObjects/RenderPass/RHIColorAttachment.h"

class VulkanColorAttachment : public RHIColorAttachment
{
public:
    VulkanColorAttachment(VkImageView InImageView, RHIAttachmentType InType, RHIPixelFormat InPixelFormat);
    ~VulkanColorAttachment();
    VkImageView GetHandle() const;
private:
    VkImageView ImageView;
};

