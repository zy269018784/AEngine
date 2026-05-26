#include "RHIAttachment.h"

#include "RHI/RHIObjects/Texture/RHITexture.h"

RHIAttachment::RHIAttachment(RHIAttachmentType InType, RHITexture *InTexture)
    : Type(InType), Texture(InTexture)
{

}

RHIAttachment::RHIAttachment(RHIAttachmentType InType, RHIPixelFormat InFormat)
    : Type(InType), Texture(nullptr), Format(InFormat)
{

}

RHIAttachment::RHIAttachment(const RHIAttachment& Other)
    : Type(Other.Type), Texture(Other.Texture)
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
    if (Texture)
        return Texture->GetFormat();
    return Format;
}