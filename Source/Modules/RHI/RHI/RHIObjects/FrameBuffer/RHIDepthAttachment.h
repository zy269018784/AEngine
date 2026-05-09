#pragma once
#include "RHI/RHIExport.h"
#include "RHI/RHIObjects/Core/RHICore.h"
class RHIEXPORT RHIDepthAttachment
{
public:
    RHIDepthAttachment(RHIDepthAttachmentType InType);
    virtual ~RHIDepthAttachment();
    RHIDepthAttachmentType GetAttachmentType() const;
private:
    RHIDepthAttachmentType Type;
};