#pragma once
#include "RHI/RHIObjects/Core/RHICore.h"
#include "RHI/RHIObjects/Framebuffer/RHIAttachment.h"

class OpenGLAttachment : public RHIAttachment
{
public:
    OpenGLAttachment(RHIAttachmentType InType, RHITexture *InTexture);
    ~OpenGLAttachment();
};

