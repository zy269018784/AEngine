#pragma once
#if 0
#include "RHIObjects/RenderPass/RHIAttachment.h"
#include "VulkanObjects/Resource/VulkanImageView.h"

class VulkanAttachment
{
public:
    VulkanAttachment(VkImageView InImageView);
    ~VulkanAttachment();
    VkImageView GetHandle() const;
private:
    VkImageView ImageView;
};
#endif