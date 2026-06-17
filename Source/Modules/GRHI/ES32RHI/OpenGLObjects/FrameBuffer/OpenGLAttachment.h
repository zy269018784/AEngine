#pragma once
#include "RHI/RHIObjects/Core/RHICore.h"
#include "RHI/RHIObjects/FrameBuffer/RHIAttachment.h"

class OpenGLAttachment : public RHIAttachment
{
public:
    OpenGLAttachment(RHIAttachmentType InType, RHITexture *InTexture, RHIAttachmentLoadOp InLoadOp,        RHIAttachmentStoreOp InStoreOp,
RHIAttachmentLoadOp InStencilLoadOp, RHIAttachmentStoreOp InStencilStoreOp);
    ~OpenGLAttachment();
};

