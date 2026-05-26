#pragma once
#include "RHI/RHIObjects/Core/RHICore.h"
#include "RHI/RHIObjects/FrameBuffer/RHIAttachment.h"

class ES32Attachment : public RHIAttachment
{
public:
    ES32Attachment(RHIAttachmentType InType, RHITexture *InTexture);
    ~ES32Attachment();
};

