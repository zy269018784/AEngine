#pragma once
#include "RHI/RHIExport.h"
#include "RHI/RHIObjects/Core/RHICore.h"
class RHIEXPORT RHIAttachment
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

