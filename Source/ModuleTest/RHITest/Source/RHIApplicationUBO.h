#pragma once
#include <RHIApplication.h>
#define GLFW_INCLUDE_VULKAN
#if  PROJECT_USE_GLFW
#include <GLFW/glfw3.h>
#endif

#include <iostream>

#include "RHI/rhi.h"
#include "Rhi/RHIObjects/Resource/RHIBuffer.h"



/*
    spirv-cross.exe --version 460 UBO_vert.spv --output UBO_vert.glsl
    spirv-cross.exe --version 460 UBO_frag.spv --output UBO_frag.glsl
    glslangValidator.exe -V --glsl-version 460 -S vert UBO_vert.glsl -o UBO_vert.spv -e main
    glslangValidator.exe -V --glsl-version 460 -S frag UBO_frag.glsl -o UBO_frag.spv -e main
*/

class RHIApplicationUBO : public RHIApplication
{
public:
    RHIApplicationUBO();
private:
    virtual void Init();
    virtual void Draw();
    void CreateVBO();
    void CreateEBO();
    void CreateUBO();
    void CreateSRB();
    void CreateVertexDescriptioin();
    void CreateGraphicsPipeline();
private:
    RHIBuffer* RHIUBO[4];
};
