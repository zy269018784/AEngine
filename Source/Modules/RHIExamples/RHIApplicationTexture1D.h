#pragma once
#include <RHIApplication.h>
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>

#include <RHI.h>
#include "RHIObjects/Resource/RHIBuffer.h"
#include "RHIObjects/Window/RHIWindow.h"
#include "RHIObjects/Texture/RHITexture1D.h"
#include "RHIObjects/Texture/RHITexture2D.h"
#include "RHIObjects/Shader/RHIShader.h"


/*
    spirv-cross.exe --version 460 Texture1D.spv --output Texture1D_vert.glsl
    spirv-cross.exe --version 460 Texture1D.spv --output Texture1D_frag.glsl
    glslangValidator.exe -V --glsl-version 460 -S vert Texture1D_vert.glsl -o Texture1D_vert.spv -e main
    glslangValidator.exe -V --glsl-version 460 -S frag Texture1D_frag.glsl -o Texture1D_frag.spv -e main
*/

class RHIApplicationTexture1D : public RHIApplication
{
public:
    RHIApplicationTexture1D(GLFWwindow* Window);
    ~RHIApplicationTexture1D();
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
    RHITexture* RHITexture2D = nullptr;
    RHITexture* RHITexture1D = nullptr;
    RHISampler* RHISampler1D_ = nullptr;
    RHISampler* RHISampler2D_ = nullptr;
    RHIShader* VertexShader = nullptr;
    RHIShader* FragmengShader = nullptr;
    std::vector<RHICommandBuffer::VertexInput> VertexInputs;
    RHIShaderResourceBindings* SRB = nullptr;
    RHIGraphicsPipeline* GraphicsPipeline = nullptr;
};
