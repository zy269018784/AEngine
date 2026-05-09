#pragma once
#include "RHI/RHIObjects/Core/RHICore.h"
class RHIDepthAttachment
{
public:
    RHIDepthAttachment(RHIDepthAttachmentType InType);
    virtual ~RHIDepthAttachment();
    RHIDepthAttachmentType GetAttachmentType() const;
private:
    RHIDepthAttachmentType Type;
};