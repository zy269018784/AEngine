#include "RHIDepthAttachment.h"

RHIDepthAttachment::RHIDepthAttachment(RHIDepthAttachmentType InType)
    : Type(InType)
{

}

RHIDepthAttachment::~RHIDepthAttachment()
{

}

RHIDepthAttachmentType RHIDepthAttachment::GetAttachmentType() const
{
    return Type;
}