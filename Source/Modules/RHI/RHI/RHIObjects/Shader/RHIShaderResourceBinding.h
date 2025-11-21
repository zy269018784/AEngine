#pragma once
#include "RHIObjects/Resource/RHIBuffer.h"
#include "RHIObjects/Texture/RHITexture.h"
#include "RHIObjects/Resource/RHISampler.h"

class RHIShaderResourceBinding
{
public:
	enum class StageFlags
    {
		VertexStage, 
        TessellationControlStage, 
        TessellationEvaluationStage, 
        FragmentStage, 
        ComputeStage, 
        GeometryStage
	};

    enum class Type 
    {
        UniformBuffer,          // Uniform Buffer Object            (UBO)
        DynamicUniformBuffer,   // Dynamic Uniform Buffer Object    (DUBO)
        StorageBuffer,          // Storage Buffer Object            (SSBO)
        DynamicStorageBuffer,   // Dynamic Storage Buffer Object    (DSSBO)
        UniformTexelBuffer,     // Uniform Texel Buffer
        StorageTexelBuffer,     // Storage Texel Buffer 
        Sampler,                // Sampler
        SampledImage,           // Sampled Image
        CombinedImageSampler,   // Combined Image Sampler
        StorageImage,           // Storage Image                    
    };   
    
    struct TextureAndSampler {
        RHITexture* tex;
        RHISampler* sampler;
    };
	/*
		UBO
	*/
	static RHIShaderResourceBinding UniformBuffer(int binding, RHIShaderResourceBinding::StageFlags stage, RHIBuffer* buf);
	static RHIShaderResourceBinding UniformBuffer(int binding, RHIShaderResourceBinding::StageFlags stage, RHIBuffer* buf, std::uint32_t offset, std::uint32_t size);
	/*
		SSBO
	*/
	static RHIShaderResourceBinding StorageBuffer(int binding, RHIShaderResourceBinding::StageFlags stage, RHIBuffer* buf);
	static RHIShaderResourceBinding StorageBuffer(int binding, RHIShaderResourceBinding::StageFlags stage, RHIBuffer* buf, std::uint32_t offset, std::uint32_t size);
    /*
        Texture
    */
    static RHIShaderResourceBinding Texture(int binding,  RHIShaderResourceBinding::StageFlags stage, RHITexture* tex);
    static RHIShaderResourceBinding Textures(int binding, RHIShaderResourceBinding::StageFlags stage, int count, RHITexture** tex);
    /*
        Sampled Texture
    */
    static RHIShaderResourceBinding SampledTexture(int binding, RHIShaderResourceBinding::StageFlags stage, RHITexture* tex, RHISampler* sampler);
    static RHIShaderResourceBinding SampledTextures(int binding, RHIShaderResourceBinding::StageFlags stage, int count, const RHIShaderResourceBinding::TextureAndSampler* texSamplers);
    /*
        Storage Image
    */
    static RHIShaderResourceBinding ImageStore(int binding, RHIShaderResourceBinding::StageFlags stage, RHITexture* tex, int level);

    struct Data
    {
        /*
            绑定点
        */
        int binding;
        /*
            Shader Stage
        */
        RHIShaderResourceBinding::StageFlags stage;
        /*
            资源类型
        */
        RHIShaderResourceBinding::Type type;
        struct UniformBufferData 
        {
            RHIBuffer* buf;
            std::uint32_t offset;
            std::uint32_t maybeSize;
            bool hasDynamicOffset;
        };   
        struct StorageBufferData 
        {
            RHIBuffer* buf;
            std::uint32_t offset;
            std::uint32_t maybeSize;
        };
        static constexpr int MAX_TEX_SAMPLER_ARRAY_SIZE = 16;
        struct TextureAndOrSamplerData 
        {
            int count;
            TextureAndSampler texSamplers[MAX_TEX_SAMPLER_ARRAY_SIZE];
        };
        struct StorageImageData 
        {
            RHITexture* tex;
            int level;
        };

        union {
            UniformBufferData       ubuf;
            StorageBufferData       sbuf;
            StorageImageData        simage;
            TextureAndOrSamplerData stex;   
        } u;

        int arraySize() const
        {
            return 1;
            //return type == RHIShaderResourceBinding::SampledTexture || type == RHIShaderResourceBinding::Texture
            //    ? u.stex.count
            //    : 1;
        }
    };
public:
     Data d;
};