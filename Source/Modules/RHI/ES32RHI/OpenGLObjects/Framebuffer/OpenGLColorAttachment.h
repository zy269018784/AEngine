#pragma once
#include "RHI/RHIObjects/Core/RHICore.h"
#include "RHI/RHIObjects/FrameBuffer/RHIColorAttachment.h"

class OpenGLColorAttachment : public RHIColorAttachment
{
public:
    OpenGLColorAttachment(RHIAttachmentType InType, RHIPixelFormat InPixelFormat);
    ~OpenGLColorAttachment();
};

