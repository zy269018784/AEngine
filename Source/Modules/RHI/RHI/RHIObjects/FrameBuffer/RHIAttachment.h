#pragma once
#include "RHIObjects/Core/RHICore.h"
class RHIAttachment
{
public:
    RHIAttachment(RHIAttachmentType InType, RHIPixelFormat InPixelFormat);
    virtual ~RHIAttachment();
    RHIAttachmentType GetAttachmentType() const;
    RHIPixelFormat GetRHIPixelFormat() const;
private:
    RHIAttachmentType Type;
    RHIPixelFormat    PixelFormat;
};
