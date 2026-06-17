#include "ES32RHI/OpenGLObjects/FrameBuffer/OpenGLAttachment.h"

OpenGLAttachment::OpenGLAttachment(RHIAttachmentType InType, RHITexture *InTexture,
    RHIAttachmentLoadOp InLoadOp,        RHIAttachmentStoreOp InStoreOp,
    RHIAttachmentLoadOp InStencilLoadOp, RHIAttachmentStoreOp InStencilStoreOp,
    RHIImageLayout InInitialLayout, RHIImageLayout InFinalLayout)
    : RHIAttachment(InType, InTexture,
            InLoadOp, InStoreOp,
            InStencilLoadOp, InStencilStoreOp,
            InInitialLayout, InFinalLayout)
{

}

OpenGLAttachment::~OpenGLAttachment()
{

}





