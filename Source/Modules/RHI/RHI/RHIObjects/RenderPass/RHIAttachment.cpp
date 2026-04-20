#include "RHIAttachment.h"

RHIAttachment::RHIAttachment()
: Type(RHIAttachmentType::Unknown), PixelFormat(RHIPixelFormat::PF_Unknown)
{

}


RHIAttachment::RHIAttachment(RHIAttachmentType InType, RHIPixelFormat InPixelFormat)
    : Type(InType), PixelFormat(InPixelFormat)
{

}

RHIAttachment::RHIAttachment(const RHIAttachment& Other)
    : Type(Other.Type), PixelFormat(Other.PixelFormat)
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

