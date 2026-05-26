#pragma once
#include "RHI/RHIExport.h"
#include "RHI/RHIObjects/Core/RHICore.h"
class RHITexture;
class RHIEXPORT RHIAttachment
{
public:
    RHIAttachment() = default;
    RHIAttachment(RHIAttachmentType InType, RHITexture *InTexture);
    /*
     * vulkan使用
     */
    RHIAttachment(RHIAttachmentType InType, RHIPixelFormat InFormat);
    RHIAttachment(const RHIAttachment& Other);
    virtual ~RHIAttachment();
    RHIAttachmentType GetAttachmentType() const;
    RHIPixelFormat GetRHIPixelFormat() const;
    RHITexture *GetTexture() const;
protected:
    RHIAttachmentType Type;
    RHITexture *Texture = nullptr;
    RHIPixelFormat Format;
};

