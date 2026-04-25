#pragma once
#include "RHIObjects/Core/RHICore.h"
class RHIColorAttachment
{
public:
    RHIColorAttachment(RHIAttachmentType InType, RHIPixelFormat InPixelFormat);
    virtual ~RHIColorAttachment();
    RHIPixelFormat GetRHIPixelFormat() const;
private:
    RHIPixelFormat    PixelFormat;
    RHIAttachmentType Type;
};