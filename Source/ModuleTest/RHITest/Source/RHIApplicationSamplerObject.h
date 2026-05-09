#pragma once
#include <RHIApplication.h>
#if  PROJECT_USE_VULKAN
#define GLFW_INCLUDE_VULKAN
#endif
#if  PROJECT_USE_GLFW
#include <GLFW/glfw3.h>
#endif

#include <iostream>

#include "RHI/rhi.h"
#include "Rhi/RHIObjects/Resource/RHIBuffer.h"
#include "Rhi/RHIObjects/Shader/RHIShader.h"


/*
    spirv-cross.exe --version 460 Texture2D.spv --output Texture2D_vert.glsl
    spirv-cross.exe --version 460 Texture2D.spv --output Texture2D_frag.glsl
    glslangValidator.exe -V --glsl-version 460 -S vert Texture2D_vert.glsl -o Texture2D_vert.spv -e main
    glslangValidator.exe -V --glsl-version 460 -S frag Texture2D_frag.glsl -o Texture2D_frag.spv -e main
*/

class RHIApplicationSamplerObject : public RHIApplication
{
public:
    RHIApplicationSamplerObject();
    ~RHIApplicationSamplerObject();
private:
    virtual void Init();
    virtual void Draw();
    void CreateVBO();
    void CreateEBO();
    void CreateTexture();
    void CreateSRB();
    void CreateVertexDescriptioin();
    void CreateGraphicsPipeline();
private:
    RHIBuffer* RHIVBO = nullptr;   
    RHIBuffer* RHIEBO = nullptr;
    RHITexture* RHITextures[4];
    RHISampler* RHISamplers[4];
    RHIShader* VertexShader = nullptr;
    RHIShader* FragmengShader = nullptr;
    //std::vector<RHICommandBuffer::VertexInput> VertexInputs;
    //RHIShaderResourceBindings* SRB = nullptr;
    //RHIGraphicsPipeline* GraphicsPipeline = nullptr;
};
