#pragma once
#include "../../../RHI/RHIObjects/RenderPass/RHIAttachment.h"
class VulkanAttachment : public RHIAttachment
{
public:
    VulkanAttachment(RHIAttachmentType InType, RHIPixelFormat InPixelFormat);
    ~VulkanAttachment();
};

