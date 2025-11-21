#pragma once
#include <RHIApplication.h>
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>

#include <RHI.h>
#include "RHIObjects/Resource/RHIBuffer.h"
#include "RHIObjects/Window/RHIWindow.h"
#include "RHIObjects/Texture/RHITexture2D.h"
#include "RHIObjects/Shader/RHIShader.h"


/*
    spirv-cross.exe --version 460 Texture2D.spv --output Texture2D_vert.glsl
    spirv-cross.exe --version 460 Texture2D.spv --output Texture2D_frag.glsl
    glslangValidator.exe -V --glsl-version 460 -S vert Texture2D_vert.glsl -o Texture2D_vert.spv -e main
    glslangValidator.exe -V --glsl-version 460 -S frag Texture2D_frag.glsl -o Texture2D_frag.spv -e main
*/

class RHIApplicationSamplerObject : public RHIApplication
{
public:
    RHIApplicationSamplerObject(GLFWwindow* Window);
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
