#include "RHIAttachment.h"

#include "RHI/RHIObjects/Texture/RHITexture.h"
#include <iostream>
RHIAttachment::RHIAttachment(RHIAttachmentType InType, RHITexture *InTexture,
        RHIAttachmentLoadOp InLoadOp,        RHIAttachmentStoreOp InStoreOp,
        RHIAttachmentLoadOp InStencilLoadOp, RHIAttachmentStoreOp InStencilStoreOp)
    : Type(InType), Texture(InTexture),
        LoadOp(InLoadOp), StoreOp(InStoreOp), StencilLoadOp(InStencilLoadOp), StencilStoreOp(InStencilStoreOp)
{

}

RHIAttachment::RHIAttachment(RHIAttachmentType InType, RHIPixelFormat InFormat,
RHIAttachmentLoadOp InLoadOp,        RHIAttachmentStoreOp InStoreOp,
RHIAttachmentLoadOp InStencilLoadOp, RHIAttachmentStoreOp InStencilStoreOp)
    : Type(InType), Texture(nullptr), Format(InFormat),
        LoadOp(InLoadOp), StoreOp(InStoreOp), StencilLoadOp(InStencilLoadOp), StencilStoreOp(InStencilStoreOp)
{

}

RHIAttachment::RHIAttachment(const RHIAttachment& Other)
    : Type(Other.Type), Texture(Other.Texture), Format(Other.Format)
{
}

RHIAttachment::~RHIAttachment()
{

}

RHIPixelFormat RHIAttachment::GetRHIPixelFormat() const
{
    if (Texture)
        return Texture->GetFormat();
    return Format;
}
