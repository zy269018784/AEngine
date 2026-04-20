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
#include "Window/IWindow.h"

/*
    spirv-cross.exe --version 460 Texture2D.spv --output Texture2D_vert.glsl
    spirv-cross.exe --version 460 Texture2D.spv --output Texture2D_frag.glsl
    glslangValidator.exe -V --glsl-version 460 -S vert Texture2D_vert.glsl -o Texture2D_vert.spv -e main
    glslangValidator.exe -V --glsl-version 460 -S frag Texture2D_frag.glsl -o Texture2D_frag.spv -e main
*/

class RHIApplicationTextureRenderTarget
{
public:
    RHIApplicationTextureRenderTarget();
    ~RHIApplicationTextureRenderTarget();
    void Run();
    void Resize(int w, int h);
private:
    void Init();
    void Draw();
	void Draw2();
    void CreateVBO();
    void CreateEBO();
    void CreateTexture();
    void CreateTextureRT();
    void CreateSRB();
    void CreateVertexDescriptioin();
    void CreateGraphicsPipeline();
    void CreateGraphicsPipeline2();
public:
    /*
     *  0:  vulkan
     *  1:  d3d
     *  2:  opengl
     */
    int RHIIndex = 0;
public:
    /*
        GLFW窗口
    */
    IWindow* Window = nullptr;
#if USE_RHIWindow
    RHIWindow* RHIWindow_ = nullptr;
    RHIRenderTarget *RenderTarget = nullptr;
#else
    RHISurface* Surface = nullptr;
    RHIRenderTarget *RenderTarget = nullptr;
    RHIRenderTarget *TextureRenderTarget = nullptr;
    RHITexture* RHITextureRT = nullptr;
    RHISampler* RHISamplerRT = nullptr;
#endif
    /*
        RHI
    */
    RHI* pRHI = nullptr;
private:
    RHIBuffer* RHIVBO = nullptr;   
    RHIBuffer* RHIEBO = nullptr;
    RHITexture* RHITexture2D = nullptr;
    RHISampler* RHISampler_ = nullptr;
    RHIShader* VertexShader = nullptr;
    RHIShader* FragmengShader = nullptr;
    std::vector<RHICommandBuffer::VertexInput> VertexInputs;
    RHIShaderResourceBindings* SRB = nullptr;
    RHIGraphicsPipeline* GraphicsPipeline = nullptr;
private:
    RHIBuffer* RHIVBO2 = nullptr;
    RHIBuffer* RHIEBO2 = nullptr;
    RHITexture* RHITexture2D2 = nullptr;
    RHISampler* RHISampler_2 = nullptr;
    RHIShader* VertexShader2 = nullptr;
    RHIShader* FragmengShader2 = nullptr;
    std::vector<RHICommandBuffer::VertexInput> VertexInputs2;
    RHIShaderResourceBindings* SRB2 = nullptr;
    RHIGraphicsPipeline* GraphicsPipeline2 = nullptr;
};
