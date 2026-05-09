#pragma once
#if 0
#include <RHIApplication.h>
#define GLFW_INCLUDE_VULKAN
#if  PROJECT_USE_GLFW
#include <GLFW/glfw3.h>
#endif

#include <iostream>
#if  PROJECT_USE_GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#endif

#if  PROJECT_USE_STB
    #include <stb_image.h>
#endif

#include "RHI/RHI.h"
#include "RHI/RHIObjects/Resource/RHIBuffer.h"


/*
    spirv-cross.exe --version 460 UBO_vert.spv --output UBO_vert.glsl
    spirv-cross.exe --version 460 UBO_frag.spv --output UBO_frag.glsl
    glslangValidator.exe -V --glsl-version 460 -S vert UBO_vert.glsl -o UBO_vert.spv -e main
    glslangValidator.exe -V --glsl-version 460 -S frag UBO_frag.glsl -o UBO_frag.spv -e main
*/

class RHIApplicationPlayer : public RHIApplication
{
public:
    RHIApplicationPlayer();
    ~RHIApplicationPlayer();
private:
    virtual void Init();
    virtual void Draw();
    void CreateVBO();
    void CreateEBO();
    void CreateUBO();
    void CreateTexture();
    void CreateSRB();
    void CreateVertexDescriptioin();
    void CreateGraphicsPipeline();
private:
    RHIBuffer* RHIUBO = nullptr;
    RHITexture* RHITexture2D = nullptr;
    RHISampler* RHISampler_ = nullptr;
#if  PROJECT_USE_GLM
    glm::mat4 model;
    glm::mat4 view;
    glm::mat4 projection;
    glm::mat4 mvp;
#endif
    float fov;
#if  PROJECT_USE_STB
    stbi_uc* pixels;
#endif
};
#endif