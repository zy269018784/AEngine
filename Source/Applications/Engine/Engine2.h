#pragma once
/*
    : error: #error OpenGL header already included, remove this include, glad already provides it
 * */
#include "ES32RHI.h"
#include "Window/IWindow.h"

#include "RHI.h"
#ifdef PROJECT_USE_VULKAN
    #include "VulkanRHI.h"
#endif

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "Model/Model.h"

#define USE_RHI_VULKAN 1
/*
    spirv-cross.exe --version 460 Engine2.spv --output Engine2_vert.glsl
    spirv-cross.exe --version 460 Engine2.spv --output Engine2_frag.glsl
    glslangValidator.exe -V --glsl-version 460 -S vert Engine2_vert.glsl -o Engine2_vert.spv -e main
    glslangValidator.exe -V --glsl-version 460 -S frag Engine2_frag.glsl -o Engine2_frag.spv -e main
*/

class Engine2
{
public:
    Engine2(IWindow* InWindow = nullptr);
    ~Engine2();
    void Init();
    void Draw();
    void Run();
    void CreateVBO();
    void CreateEBO();
    void CreateUBO();
    void CreateTexture();
    void CreateSRB();
    void CreateVertexDescriptioin();
    void CreateGraphicsPipeline();
private:
    IWindow* Window = nullptr;
    RHIWindow* RHIWindow_ = nullptr;
    /*
        RHI
    */
    RHI* pRHI = nullptr;
    /*
        VBO
    */
    RHIBuffer* RHIVBO = nullptr;
    /*
        EBO
    */
    RHIBuffer* RHIEBO = nullptr;
    /*
        UBO
    */
    RHIBuffer* RHIUBO = nullptr;
    /*
        Pipeline
    */
    RHIGraphicsPipeline* GraphicsPipeline = nullptr;
    /*
       顶点输入
    */
    std::vector<RHICommandBuffer::VertexInput> VertexInputs;
    /*
        着色器资源绑定
    */
    RHIShaderResourceBindings* SRB = nullptr;

    RHIShader* VertexShader = nullptr;
    RHIShader* FragmengShader = nullptr;
    RHIShader* GeometryShader = nullptr;
    RHIShader* ComputeShader = nullptr;
    /*
        Texture
    */
    RHITexture* RHITexture2D = nullptr;
    RHISampler* RHISampler_ = nullptr;
};