#include "RHIAttachment.h"

#include "RHI/RHIObjects/Texture/RHITexture.h"
#include <iostream>
RHIAttachment::RHIAttachment(RHIAttachmentType InType, RHITexture *InTexture,
                            RHIAttachmentLoadOp InLoadOp,        RHIAttachmentStoreOp InStoreOp,
                            RHIAttachmentLoadOp InStencilLoadOp, RHIAttachmentStoreOp InStencilStoreOp,
                            RHIImageLayout InInitialLayout, RHIImageLayout InFinalLayout)
    : Type(InType), Texture(InTexture),
        LoadOp(InLoadOp), StoreOp(InStoreOp), StencilLoadOp(InStencilLoadOp), StencilStoreOp(InStencilStoreOp),
        InitialLayout(InInitialLayout), FinalLayout(InFinalLayout)
{

}

RHIAttachment::RHIAttachment(RHIAttachmentType InType, RHIPixelFormat InFormat,
                            RHIAttachmentLoadOp InLoadOp,        RHIAttachmentStoreOp InStoreOp,
                            RHIAttachmentLoadOp InStencilLoadOp, RHIAttachmentStoreOp InStencilStoreOp,
                            RHIImageLayout InInitialLayout, RHIImageLayout InFinalLayout)
    : Type(InType), Texture(nullptr), Format(InFormat),
        LoadOp(InLoadOp), StoreOp(InStoreOp), StencilLoadOp(InStencilLoadOp), StencilStoreOp(InStencilStoreOp),
        InitialLayout(InInitialLayout), FinalLayout(InFinalLayout)
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
