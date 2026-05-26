#pragma once
#include "RHI/RHIObjects/Core/RHICore.h"
#include "RHI/RHIObjects/FrameBuffer/RHIAttachment.h"

class OpenGL33Attachment : public RHIAttachment
{
public:
    OpenGL33Attachment(RHIAttachmentType InType, RHITexture *InTexture);
    ~OpenGL33Attachment();
};

