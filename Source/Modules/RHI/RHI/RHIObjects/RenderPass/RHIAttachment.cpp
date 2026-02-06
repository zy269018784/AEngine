#include "RHIAttachment.h"

RHIAttachment::RHIAttachment(RHIAttachmentType InType, RHIPixelFormat InPixelFormat)
    : Type(InType), PixelFormat(InPixelFormat)
{

}

RHIAttachment::~RHIAttachment()
{

}

RHIAttachmentType RHIAttachment::GetAttachmentType() const
{
    return Type;
}

RHIPixelFormat RHIAttachment::GetRHIPixelFormat() const
{
    return PixelFormat;
}

