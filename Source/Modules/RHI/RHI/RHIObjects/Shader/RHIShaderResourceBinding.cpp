#include "RHIObjects/Shader/RHIShaderResourceBinding.h"


/*
	UBO
*/
RHIShaderResourceBinding RHIShaderResourceBinding::UniformBuffer(int binding, RHIShaderResourceBinding::StageFlags stage, RHIBuffer* buf)
{
    RHIShaderResourceBinding b;
    b.d.binding = binding;
    b.d.stage = stage;
    b.d.type = RHIShaderResourceBinding::Type::UniformBuffer;
    b.d.u.ubuf.buf = buf;
    b.d.u.ubuf.offset = 0;
    b.d.u.ubuf.maybeSize = 0; // entire buffer
    b.d.u.ubuf.hasDynamicOffset = false;
    return b;
}

RHIShaderResourceBinding RHIShaderResourceBinding::UniformBuffer(int binding, RHIShaderResourceBinding::StageFlags stage, RHIBuffer* buf, std::uint32_t offset, std::uint32_t size)
{
    RHIShaderResourceBinding b;
    b.d.binding = binding;
    b.d.stage = stage;
    b.d.type = RHIShaderResourceBinding::Type::UniformBuffer;
    b.d.u.ubuf.buf = buf;
    b.d.u.ubuf.offset = offset;
    b.d.u.ubuf.maybeSize = size;
    b.d.u.ubuf.hasDynamicOffset = false;
    return b;
}

/*
	SSBO
*/
RHIShaderResourceBinding RHIShaderResourceBinding::StorageBuffer(int binding, RHIShaderResourceBinding::StageFlags stage, RHIBuffer* buf)
{
    RHIShaderResourceBinding b;
    b.d.binding = binding;
    b.d.stage = stage;
    b.d.type = RHIShaderResourceBinding::Type::StorageBuffer;
    b.d.u.sbuf.buf = buf;
    b.d.u.sbuf.offset = 0;
    b.d.u.sbuf.maybeSize = 0; // entire buffer
    return b;
}

RHIShaderResourceBinding RHIShaderResourceBinding::StorageBuffer(int binding, RHIShaderResourceBinding::StageFlags stage, RHIBuffer* buf, std::uint32_t offset, std::uint32_t size)
{
    RHIShaderResourceBinding b;
    b.d.binding = binding;
    b.d.stage = stage;
    b.d.type = RHIShaderResourceBinding::Type::StorageBuffer;
    b.d.u.sbuf.buf = buf;
    b.d.u.sbuf.offset = offset;
    b.d.u.sbuf.maybeSize = size;
    return b;
}

/*
    Texture
*/
RHIShaderResourceBinding RHIShaderResourceBinding::Texture(int binding, RHIShaderResourceBinding::StageFlags stage, RHITexture* tex)
{
    RHIShaderResourceBinding b;
    b.d.binding = binding;
    b.d.stage = stage;
    b.d.type = RHIShaderResourceBinding::Type::SampledImage;
    b.d.u.stex.count = 1;
    b.d.u.stex.texSamplers[0] = { tex, nullptr };
    return b;
}

RHIShaderResourceBinding RHIShaderResourceBinding::Textures(int binding, RHIShaderResourceBinding::StageFlags stage, int count, RHITexture** tex)
{
    RHIShaderResourceBinding b;
    b.d.binding = binding;
    b.d.stage = stage;
    b.d.type = RHIShaderResourceBinding::Type::SampledImage;
    b.d.u.stex.count = count;
    for (int i = 0; i < count; ++i) {
        if (tex)
            b.d.u.stex.texSamplers[i] = { tex[i], nullptr };
        else
            b.d.u.stex.texSamplers[i] = { nullptr, nullptr };
    }
    return b;
}

/*
    Sampled Texture
*/
RHIShaderResourceBinding RHIShaderResourceBinding::SampledTexture(int binding, RHIShaderResourceBinding::StageFlags stage, RHITexture* tex, RHISampler* sampler)
{
    RHIShaderResourceBinding b;
    b.d.binding = binding;
    b.d.stage = stage;
    b.d.type = RHIShaderResourceBinding::Type::CombinedImageSampler;
    b.d.u.stex.count = 1;
    b.d.u.stex.texSamplers[0] = { tex, sampler };
    return b;
}

RHIShaderResourceBinding RHIShaderResourceBinding::SampledTextures(int binding, RHIShaderResourceBinding::StageFlags stage, int count, const RHIShaderResourceBinding::TextureAndSampler* texSamplers)
{
    RHIShaderResourceBinding b;
    b.d.binding = binding;
    b.d.stage = stage;
    b.d.type = RHIShaderResourceBinding::Type::CombinedImageSampler;
    b.d.u.stex.count = count;
    for (int i = 0; i < count; ++i) {
        if (texSamplers)
            b.d.u.stex.texSamplers[i] = texSamplers[i];
        else
            b.d.u.stex.texSamplers[i] = { nullptr, nullptr };
    }
    return b;
}

/*
    Storage Image
*/
RHIShaderResourceBinding RHIShaderResourceBinding::ImageStore(int binding, RHIShaderResourceBinding::StageFlags stage, RHITexture* tex, int level)
{
    RHIShaderResourceBinding b;
    b.d.binding = binding;
    b.d.stage = stage;
    b.d.type = RHIShaderResourceBinding::Type::StorageImage;
    b.d.u.simage.tex = tex;
    b.d.u.simage.level = level;
    return b;
}