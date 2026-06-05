#include "RHIAttachment.h"

#include "RHI/RHIObjects/Texture/RHITexture.h"
#include <iostream>
RHIAttachment::RHIAttachment(RHIAttachmentType InType, RHITexture *InTexture)
    : Type(InType), Texture(InTexture)
{

}

RHIAttachment::RHIAttachment(RHIAttachmentType InType, RHIPixelFormat InFormat)
    : Type(InType), Texture(nullptr), Format(InFormat)
{

}

RHIAttachment::RHIAttachment(const RHIAttachment& Other)
    : Type(Other.Type), Texture(Other.Texture), Format(Other.Format)
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
    std::cout << "RHIAttachment::GetRHIPixelFormat " << (int)Format << " " << this  << std::endl;
    return Format;
}

RHITexture *RHIAttachment::GetTexture() const {
    return Texture;
}