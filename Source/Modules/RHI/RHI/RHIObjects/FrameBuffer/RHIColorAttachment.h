#pragma once
#include "RHI/RHIExport.h"
#include "RHI/RHIObjects/Core/RHICore.h"
class RHIEXPORT RHIColorAttachment
{
public:
    RHIColorAttachment(RHIAttachmentType InType, RHIPixelFormat InPixelFormat);
    virtual ~RHIColorAttachment();
    RHIPixelFormat GetRHIPixelFormat() const;
    RHIAttachmentType GetAttachmentType() const;
private:
    RHIPixelFormat    PixelFormat;
    RHIAttachmentType Type;
};