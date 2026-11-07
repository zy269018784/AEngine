#pragma once
#include <RHIApplication.h>
#include <iostream>
#include "RHI/RHI.h"



/*
    spirv-cross.exe --version 460 Texture2D.spv --output Texture2D_vert.glsl
    spirv-cross.exe --version 460 Texture2D.spv --output Texture2D_frag.glsl
    glslangValidator.exe -V --glsl-version 460 -S vert Texture2D_vert.glsl -o Texture2D_vert.spv -e main
    glslangValidator.exe -V --glsl-version 460 -S frag Texture2D_frag.glsl -o Texture2D_frag.spv -e main
*/

class RHIApplicationTexture2DRenderTarget : public RHIApplication
{
public:
    RHIApplicationTexture2DRenderTarget();
    ~RHIApplicationTexture2DRenderTarget();
private:
    virtual void Render() override final;
private:
    virtual void Init();
    virtual void Draw();
    virtual void Draw2();
    void CreateVBO();
    void CreateEBO();
    void CreateTexture();
    void CreateSRB();
    void CreateSRB2();
    void CreateVertexDescriptioin();
    void CreateGraphicsPipeline();
    void CreateGraphicsPipeline2();
    void CreateTextureRenderTarget();

private:
    RHITexture* RHITexture2D = nullptr;
    RHISampler* RHISampler_ = nullptr;
    RHITexture* RHITextureRT = nullptr;
    RHISampler* RHISamplerRT = nullptr;
};
