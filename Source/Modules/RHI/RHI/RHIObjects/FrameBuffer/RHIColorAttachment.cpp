#include "RHIColorAttachment.h"

RHIColorAttachment::RHIColorAttachment(RHIAttachmentType InType, RHIPixelFormat InPixelFormat)
    : Type(InType), PixelFormat(InPixelFormat)
{

}

RHIColorAttachment::~RHIColorAttachment()
{

}

RHIPixelFormat RHIColorAttachment::GetRHIPixelFormat() const
{
    return PixelFormat;
}


RHIAttachmentType RHIColorAttachment::GetAttachmentType() const
{
    return Type;
}