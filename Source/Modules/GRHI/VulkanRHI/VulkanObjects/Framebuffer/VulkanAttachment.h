#pragma once
#include "RHI/RHIObjects/FrameBuffer/RHIAttachment.h"
#include "VulkanRHI/VulkanObjects//Resource/VulkanImageView.h"
class VulkanTexture;
class VulkanAttachment : public RHIAttachment
{
public:
    VulkanAttachment(RHIAttachmentType InType, RHITexture *InTexture,
        RHIAttachmentLoadOp InLoadOp,        RHIAttachmentStoreOp InStoreOp,
        RHIAttachmentLoadOp InStencilLoadOp, RHIAttachmentStoreOp InStencilStoreOp,
        RHIImageLayout InInitialLayout, RHIImageLayout InFinalLayout);

    VulkanAttachment(RHIAttachmentType InType, RHIPixelFormat InFormat,
        RHIAttachmentLoadOp InLoadOp,        RHIAttachmentStoreOp InStoreOp,
        RHIAttachmentLoadOp InStencilLoadOp, RHIAttachmentStoreOp InStencilStoreOp,
        RHIImageLayout InInitialLayout, RHIImageLayout InFinalLayout);

    VulkanAttachment(RHIAttachmentType InType, RHIPixelFormat InFormat, VkImageView InImageView,
        RHIAttachmentLoadOp InLoadOp,        RHIAttachmentStoreOp InStoreOp,
        RHIAttachmentLoadOp InStencilLoadOp, RHIAttachmentStoreOp InStencilStoreOp,
        RHIImageLayout InInitialLayout, RHIImageLayout InFinalLayout);
    ~VulkanAttachment();
    VkImageView GetHandle() const;
private:
    VkImageView ImageView;
};
