#pragma once
#include <RHIApplication.h>
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>

#include <RHI.h>
#include "RHIObjects/Resource/RHIBuffer.h"
#include "RHIObjects/Window/RHIWindow.h"


/*
    spirv-cross.exe --version 460 SSBO_vert.spv --output SSBO_vert.glsl
    spirv-cross.exe --version 460 SSBO_frag.spv --output SSBO_frag.glsl
    glslangValidator.exe -V --glsl-version 460 -S vert SSBO_vert.glsl -o SSBO_vert.spv -e main
    glslangValidator.exe -V --glsl-version 460 -S frag SSBO_frag.glsl -o SSBO_frag.spv -e main
*/

class RHIApplicationSSBO : public RHIApplication
{
public:
    RHIApplicationSSBO(GLFWwindow* Window);
    ~RHIApplicationSSBO();
private:
    virtual void Init();
    virtual void Draw();
    void CreateVBO();
    void CreateEBO();
    void CreateSSBO();
    void CreateSRB();
    void CreateVertexDescriptioin();
    void CreateGraphicsPipeline();
private:

    RHIBuffer* RHISSBO[4];
    std::vector<RHICommandBuffer::VertexInput> VertexInputs;
  
};
