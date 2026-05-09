#pragma once
#include "RHI/RHIObjects/Core/RHICore.h"
class RHIAttachment
{
public:
    RHIAttachment();
    RHIAttachment(RHIAttachmentType InType, RHIPixelFormat InPixelFormat);
    RHIAttachment(const RHIAttachment& Other);
    virtual ~RHIAttachment();
    RHIAttachmentType GetAttachmentType() const;
    RHIPixelFormat GetRHIPixelFormat() const;
private:
    RHIAttachmentType Type;
    RHIPixelFormat    PixelFormat;
};

