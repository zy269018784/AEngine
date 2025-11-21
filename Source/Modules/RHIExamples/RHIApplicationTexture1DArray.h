#pragma once
#include <RHIApplication.h>
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>

#include <RHI.h>
#include "RHIObjects/Resource/RHIBuffer.h"
#include "RHIObjects/Window/RHIWindow.h"
#include "RHIObjects/Shader/RHIShader.h"


/*
    spirv-cross.exe --version 460 Texture2D.spv --output Texture2D_vert.glsl
    spirv-cross.exe --version 460 Texture2D.spv --output Texture2D_frag.glsl
    glslangValidator.exe -V --glsl-version 460 -S vert Texture2D_vert.glsl -o Texture2D_vert.spv -e main
    glslangValidator.exe -V --glsl-version 460 -S frag Texture2D_frag.glsl -o Texture2D_frag.spv -e main
*/

class RHIApplicationTexture1DArray : public RHIApplication
{
public:
    RHIApplicationTexture1DArray(GLFWwindow* Window);
    ~RHIApplicationTexture1DArray();
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
    RHITexture* RHITexture1DArray = nullptr;
    RHISampler* RHISampler1DArray = nullptr;

    RHIShader* VertexShader = nullptr;
    RHIShader* FragmengShader = nullptr;
};
