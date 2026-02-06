#pragma once
#include "RHIObjects/FrameBuffer/RHIAttachment.h"
class VulkanAttachment : public RHIAttachment
{
public:
    VulkanAttachment(RHIAttachmentType InType);
    ~VulkanAttachment();
};

