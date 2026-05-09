#pragma once
#if 0
#include "RHI/RHIObjects/RenderPass/RHIAttachment.h"
#include "VulkanRHI/VulkanObjects//Resource/VulkanImageView.h"

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