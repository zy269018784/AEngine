#pragma once
#include "RHIObjects/Core/RHICore.h"
class RHIAttachment
{
public:
    RHIAttachment(RHIAttachmentType InType);
    virtual ~RHIAttachment();
private:
    RHIAttachmentType Type;
};
