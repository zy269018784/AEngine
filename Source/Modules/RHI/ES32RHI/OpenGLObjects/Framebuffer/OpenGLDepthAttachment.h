#pragma once
#include "RHI/RHIObjects/Core/RHICore.h"
#include "RHI/RHIObjects/FrameBuffer/RHIDepthAttachment.h"

class OpenGLDepthAttachment : public RHIDepthAttachment
{
public:
    OpenGLDepthAttachment(RHIDepthAttachmentType InType);
    ~OpenGLDepthAttachment();
};