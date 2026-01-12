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
class Engine
{
public:
    Engine(IWindow* InWindow = nullptr);
    ~Engine();
    void Init();
    void Draw();
    void Run();
    void CreateVBO();
    void CreateEBO();
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