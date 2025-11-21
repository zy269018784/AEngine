#pragma once
#include <RHIApplication.h>
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>

#include <RHI.h>
#include "RHIObjects/Resource/RHIBuffer.h"
#include "RHIObjects/Window/RHIWindow.h"


/*
    spirv-cross.exe --version 460 DrawTriangle_vert.spv --output DrawTriangle_vert.glsl
    spirv-cross.exe --version 460 DrawTriangle_frag.spv --output DrawTriangle_frag.glsl
    glslangValidator.exe -V --glsl-version 460 -S vert DrawTriangle_vert.glsl -o DrawTriangle_vert.spv -e main
    glslangValidator.exe -V --glsl-version 460 -S frag DrawTriangle_frag.glsl -o DrawTriangle_frag.spv -e main
*/

class RHIApplicationGeometryShader : public RHIApplication
{
public:
    RHIApplicationGeometryShader(GLFWwindow* Window);
private:
    virtual void Init();
    virtual void Draw();
    void CreateVBO();
    void CreateEBO();
    void CreateSRB();
    void CreateVertexDescriptioin();
    void CreateGraphicsPipeline();
};
