#pragma once
#include "RHI/RHIObjects/Core/RHICore.h"
#include "RHI/RHIObjects/FrameBuffer/RHIAttachment.h"

class ES31Attachment : public RHIAttachment
{
public:
    ES31Attachment(RHIAttachmentType InType, RHITexture *InTexture);
    ~ES31Attachment();
};

