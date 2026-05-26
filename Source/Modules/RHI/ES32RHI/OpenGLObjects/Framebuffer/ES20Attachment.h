#pragma once
#include "RHI/RHIObjects/Core/RHICore.h"
#include "RHI/RHIObjects/FrameBuffer/RHIAttachment.h"

class ES20Attachment : public RHIAttachment
{
public:
    ES20Attachment(RHIAttachmentType InType, RHITexture *InTexture);
    ~ES20Attachment();
};

