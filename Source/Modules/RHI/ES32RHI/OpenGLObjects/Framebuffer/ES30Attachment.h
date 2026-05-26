#pragma once
#include "RHI/RHIObjects/Core/RHICore.h"
#include "RHI/RHIObjects/FrameBuffer/RHIAttachment.h"

class ES30Attachment : public RHIAttachment
{
public:
    ES30Attachment(RHIAttachmentType InType, RHITexture *InTexture);
    ~ES30Attachment();
};

