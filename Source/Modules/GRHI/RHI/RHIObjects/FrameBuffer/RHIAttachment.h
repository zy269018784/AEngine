#pragma once
#include "RHI/RHIExport.h"
#include "RHI/RHIObjects/Core/RHICore.h"
class RHITexture;
class RHIEXPORT RHIAttachment
{
public:
    RHIAttachment() = default;
    RHIAttachment(RHIAttachmentType InType, RHITexture *InTexture,
        RHIAttachmentLoadOp LoadOp, RHIAttachmentStoreOp StoreOp,
        RHIAttachmentLoadOp StencilLoadOp, RHIAttachmentStoreOp StencilStoreOp);
    /*
     * vulkan使用
     */
    RHIAttachment(RHIAttachmentType InType, RHIPixelFormat InFormat,
        RHIAttachmentLoadOp LoadOp, RHIAttachmentStoreOp StoreOp,
        RHIAttachmentLoadOp StencilLoadOp, RHIAttachmentStoreOp StencilStoreOp);
    RHIAttachment(const RHIAttachment& Other);
    virtual ~RHIAttachment();
    [[nodiscard]] RHIPixelFormat GetRHIPixelFormat() const;
    [[nodiscard]] RHIAttachmentType GetAttachmentType() const { return Type; };
    [[nodiscard]] RHITexture *GetTexture() const { return Texture; };
    [[nodiscard]] RHIAttachmentLoadOp GetLoadOp() const { return LoadOp; }
    [[nodiscard]] RHIAttachmentStoreOp GetStoreOp() const { return StoreOp; }
    [[nodiscard]] RHIAttachmentLoadOp GetStencilLoadOp() const { return StencilLoadOp; }
    [[nodiscard]] RHIAttachmentStoreOp GetStencilStoreOp() const { return StencilStoreOp; }
protected:
    RHIAttachmentType Type;
    RHITexture *Texture = nullptr;
    RHIPixelFormat Format;
    RHIAttachmentLoadOp LoadOp;
    RHIAttachmentStoreOp StoreOp;
    RHIAttachmentLoadOp StencilLoadOp;
    RHIAttachmentStoreOp StencilStoreOp;
};

