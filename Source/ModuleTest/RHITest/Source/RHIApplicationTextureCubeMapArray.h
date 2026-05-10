#pragma once
#include <RHIApplication.h>
#include "RHI/RHI.h"
#include "RHI/RHIObjects/Shader/RHIShader.h"


/*
    spirv-cross.exe --version 460 Texture2D.spv --output Texture2D_vert.glsl
    spirv-cross.exe --version 460 Texture2D.spv --output Texture2D_frag.glsl
    glslangValidator.exe -V --glsl-version 460 -S vert Texture2D_vert.glsl -o Texture2D_vert.spv -e main
    glslangValidator.exe -V --glsl-version 460 -S frag Texture2D_frag.glsl -o Texture2D_frag.spv -e main
*/

class RHIApplicationTextureCubeMapArray : public RHIApplication
{
public:
    RHIApplicationTextureCubeMapArray();
    ~RHIApplicationTextureCubeMapArray();
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
    RHITexture* RHITextureCubeMapArray = nullptr;
    RHISampler* RHISampler_ = nullptr;
    RHIShader* VertexShader = nullptr;
    RHIShader* FragmengShader = nullptr;
};
