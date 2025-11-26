#pragma once
#include <RHIApplication.h>
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#ifdef PROJECT_USE_STB
    #include <stb_image.h>
#endif

#include <RHI.h>
#include <RHIObjects/Resource/RHIBuffer.h>
#include <RHIObjects/Window/RHIWindow.h>


/*
    spirv-cross.exe --version 460 UBO_vert.spv --output UBO_vert.glsl
    spirv-cross.exe --version 460 UBO_frag.spv --output UBO_frag.glsl
    glslangValidator.exe -V --glsl-version 460 -S vert UBO_vert.glsl -o UBO_vert.spv -e main
    glslangValidator.exe -V --glsl-version 460 -S frag UBO_frag.glsl -o UBO_frag.spv -e main
*/

class RHIApplicationPlayer : public RHIApplication
{
public:
    RHIApplicationPlayer(GLFWwindow* Window);
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
    glm::mat4 model;
    glm::mat4 view;
    glm::mat4 projection;
    glm::mat4 mvp;
    float fov;
#ifdef PROJECT_USE_STB
    stbi_uc* pixels;
#endif
};
