#include "ES32RHI/OpenGLObjects/FrameBuffer/OpenGLAttachment.h"

OpenGLAttachment::OpenGLAttachment(RHIAttachmentType InType, RHITexture *InTexture,
    RHIAttachmentLoadOp InLoadOp,        RHIAttachmentStoreOp InStoreOp,
    RHIAttachmentLoadOp InStencilLoadOp, RHIAttachmentStoreOp InStencilStoreOp)
    : RHIAttachment(InType, InTexture, InLoadOp, InStoreOp, InStencilLoadOp, InStencilStoreOp)
{

}

OpenGLAttachment::~OpenGLAttachment()
{

}





