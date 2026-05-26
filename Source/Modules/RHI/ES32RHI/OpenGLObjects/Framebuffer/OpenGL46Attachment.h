#pragma once
#include "RHI/RHIObjects/Core/RHICore.h"
#include "RHI/RHIObjects/FrameBuffer/RHIAttachment.h"

class OpenGL46Attachment : public RHIAttachment
{
public:
    OpenGL46Attachment(RHIAttachmentType InType, RHITexture *InTexture);
    ~OpenGL46Attachment();
};

