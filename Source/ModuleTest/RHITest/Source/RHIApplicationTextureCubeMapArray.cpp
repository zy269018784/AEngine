#include "RHIApplicationTextureCubeMapArray.h"
#include "RHI/RHIObjects/Shader/RHIShaderResourceBinding.h"
#include "RHI/RHIObjects/Shader/RHIShaderResourceBindings.h"
#include "Common.h"
#include "RHI/RHIObjects/Core/RHIVertexInputLayout.h"
#include "RHI/RHIObjects/Pipeline/RHIGraphicsPipeline.h"
#include "RHI/RHIObjects/RenderTarget/RHIRenderTarget.h"
#if  PROJECT_USE_STB
    #include <stb_image.h>
#endif

/*
    VBO1三角形: 红色和黄色
    VBO1三角形: 蓝色和绿色
*/
static float VertexAttributes[] = {
    // front
    // pos                uv         
    -1.0f, -1.0f, 0.0f,   -1.0f, -1.0f, 1.0f,
     1.0f, -1.0f, 0.0f,    1.0f, -1.0f, 1.0f,
     1.0f,  1.0f, 0.0f,    1.0f,  1.0f, 1.0f,

     1.0f,  1.0f, 0.0f,    1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, 0.0f,   -1.0f,  1.0f, -1.0f,
    -1.0f, -1.0f, 0.0f,   -1.0f, -1.0f, -1.0f,
};

static unsigned int Index[] = {
    0, 1, 2,
    3, 4, 5
};


RHIApplicationTextureCubeMapArray::RHIApplicationTextureCubeMapArray()
    : RHIApplication()
{

}

RHIApplicationTextureCubeMapArray::~RHIApplicationTextureCubeMapArray()
{
    delete RHIVBO;
    delete RHIEBO;
    delete RHITextureCubeMapArray;
    delete VertexShader;
    delete FragmengShader;
    delete GraphicsPipeline;
    delete SRB;
    delete RHISampler_;
}   

void RHIApplicationTextureCubeMapArray::Init()
{
    CreateVBO();
    CreateEBO();
    CreateTexture();
    CreateSRB();
    CreateVertexDescriptioin();
    CreateGraphicsPipeline();
}

void RHIApplicationTextureCubeMapArray::CreateVBO()
{
    RHIVBO = pRHI->RHICreateBuffer(RHIBufferType::VertexBuffer, RHIBufferUsageFlag::VertexBuffer, sizeof(VertexAttributes), VertexAttributes);
}

void RHIApplicationTextureCubeMapArray::CreateEBO()
{
    RHIEBO = pRHI->RHICreateBuffer(RHIBufferType::IndexBuffer, RHIBufferUsageFlag::IndexBuffer, sizeof(Index), Index);
}

void RHIApplicationTextureCubeMapArray::CreateTexture()
{
    RHISampler_ = pRHI->RHICreateSampler(RHIFilter::NEAREST, RHIFilter::NEAREST);
#if  PROJECT_USE_STB
    /*
        STBI_rgb_alpha统一转成4通道
    */    
    int texWidth, texHeight, texChannels;
    stbi_uc* pixels1 = stbi_load("textures/skybox/right.jpg", &texWidth, &texHeight, &texChannels, STBI_rgb_alpha);
    stbi_uc* pixels2 = stbi_load("textures/skybox/left.jpg", &texWidth, &texHeight, &texChannels, STBI_rgb_alpha);
    stbi_uc* pixels3 = stbi_load("textures/skybox/top.jpg", &texWidth, &texHeight, &texChannels, STBI_rgb_alpha);
    stbi_uc* pixels4 = stbi_load("textures/skybox/bottom.jpg", &texWidth, &texHeight, &texChannels, STBI_rgb_alpha);
    stbi_uc* pixels5 = stbi_load("textures/skybox/front.jpg", &texWidth, &texHeight, &texChannels, STBI_rgb_alpha);
    stbi_uc* pixels6 = stbi_load("textures/skybox/back.jpg", &texWidth, &texHeight, &texChannels, STBI_rgb_alpha);

    int texWidth2, texHeight2, texChannels2;
    stbi_uc* skybox2_right  = stbi_load("textures/Storforsen2/posx.jpg", &texWidth, &texHeight, &texChannels, STBI_rgb_alpha);
    stbi_uc* skybox2_left   = stbi_load("textures/Storforsen2/negx.jpg", &texWidth, &texHeight, &texChannels, STBI_rgb_alpha);
    stbi_uc* skybox2_top    = stbi_load("textures/Storforsen2/posy.jpg", &texWidth, &texHeight, &texChannels, STBI_rgb_alpha);
    stbi_uc* skybox2_bottom = stbi_load("textures/Storforsen2/negy.jpg", &texWidth, &texHeight, &texChannels, STBI_rgb_alpha);
    stbi_uc* skybox2_front  = stbi_load("textures/Storforsen2/posz.jpg", &texWidth, &texHeight, &texChannels, STBI_rgb_alpha);
    stbi_uc* skybox2_back   = stbi_load("textures/Storforsen2/negz.jpg", &texWidth, &texHeight, &texChannels, STBI_rgb_alpha);

    std::uint32_t TextureSize = texWidth * texHeight * 4;
    std::vector<std::uint8_t> TextureData(12 * TextureSize);

    std::memcpy(TextureData.data() +  0 * TextureSize, pixels1, TextureSize);    // 拷贝第一个纹理
    std::memcpy(TextureData.data() +  1 * TextureSize, pixels2, TextureSize);    // 拷贝第二个纹理
    std::memcpy(TextureData.data() +  2 * TextureSize, pixels3, TextureSize);    // 拷贝第一个纹理
    std::memcpy(TextureData.data() +  3 * TextureSize, pixels4, TextureSize);    // 拷贝第二个纹理
    std::memcpy(TextureData.data() +  4 * TextureSize, pixels5, TextureSize);    // 拷贝第一个纹理
    std::memcpy(TextureData.data() +  5 * TextureSize, pixels6, TextureSize);    // 拷贝第二个纹理
    std::memcpy(TextureData.data() +  6 * TextureSize, skybox2_right, TextureSize);    // 拷贝第一个纹理
    std::memcpy(TextureData.data() +  7 * TextureSize, skybox2_left, TextureSize);    // 拷贝第二个纹理
    std::memcpy(TextureData.data() +  8 * TextureSize, skybox2_top, TextureSize);    // 拷贝第一个纹理
    std::memcpy(TextureData.data() +  9 * TextureSize, skybox2_bottom, TextureSize);    // 拷贝第二个纹理
    std::memcpy(TextureData.data() + 10 * TextureSize, skybox2_front, TextureSize);    // 拷贝第一个纹理
    std::memcpy(TextureData.data() + 11 * TextureSize, skybox2_back, TextureSize);    // 拷贝第二个纹理
 //  VkDeviceSize imageSize = texWidth * texHeight * 4;

    RHITextureCubeMapArray = pRHI->RHICreateTextureCubeArray(RHIPixelFormat::PF_R8G8B8A8_UNORM, 1, texWidth, texHeight, 2, TextureData.data());
#endif

    #if 0
    RHITextureCubeMapArray->Update(0, 0, 0, (int)RHICubeMapFace::CUBE_MAP_POSITIVE_X, texWidth, texHeight, 1, pixels1);
    RHITextureCubeMapArray->Update(0, 0, 0, (int)RHICubeMapFace::CUBE_MAP_NEGATIVE_X, texWidth, texHeight, 1, pixels2);
    RHITextureCubeMapArray->Update(0, 0, 0, (int)RHICubeMapFace::CUBE_MAP_POSITIVE_Y, texWidth, texHeight, 1, pixels3);
    RHITextureCubeMapArray->Update(0, 0, 0, (int)RHICubeMapFace::CUBE_MAP_NEGATIVE_Y, texWidth, texHeight, 1, pixels4);
    RHITextureCubeMapArray->Update(0, 0, 0, (int)RHICubeMapFace::CUBE_MAP_POSITIVE_Z, texWidth, texHeight, 1, pixels5);
    RHITextureCubeMapArray->Update(0, 0, 0, (int)RHICubeMapFace::CUBE_MAP_NEGATIVE_Z, texWidth, texHeight, 1, pixels6);

    RHITextureCubeMapArray->Update(0, 0, 0, 6 + (int)RHICubeMapFace::CUBE_MAP_POSITIVE_X, texWidth, texHeight, 1, skybox2_right );
    RHITextureCubeMapArray->Update(0, 0, 0, 6 + (int)RHICubeMapFace::CUBE_MAP_NEGATIVE_X, texWidth, texHeight, 1, skybox2_left  );
    RHITextureCubeMapArray->Update(0, 0, 0, 6 + (int)RHICubeMapFace::CUBE_MAP_POSITIVE_Y, texWidth, texHeight, 1, skybox2_top   );
    RHITextureCubeMapArray->Update(0, 0, 0, 6 + (int)RHICubeMapFace::CUBE_MAP_NEGATIVE_Y, texWidth, texHeight, 1, skybox2_bottom);
    RHITextureCubeMapArray->Update(0, 0, 0, 6 + (int)RHICubeMapFace::CUBE_MAP_POSITIVE_Z, texWidth, texHeight, 1, skybox2_front );
    RHITextureCubeMapArray->Update(0, 0, 0, 6 + (int)RHICubeMapFace::CUBE_MAP_NEGATIVE_Z, texWidth, texHeight, 1, skybox2_back  );
#endif
}


void RHIApplicationTextureCubeMapArray::CreateSRB()
{
    SRB = pRHI->RHICreateShaderResourceBindings();
    SRB->SetBindings({
            RHIShaderResourceBinding::SampledTexture(0, RHIShaderType::Fragment, RHITextureCubeMapArray, RHISampler_)
    });
    SRB->Create();
}

void RHIApplicationTextureCubeMapArray::CreateVertexDescriptioin()
{
    /*
        使用VBO1
    */
    VertexInputs.push_back(std::make_pair(RHIVBO, 0 * sizeof(float)));
}

void RHIApplicationTextureCubeMapArray::CreateGraphicsPipeline()
{
#if 1
   auto vertShaderCode = ReadFile("TextureCubeMapArray_vert.spv");
   auto fragShaderCode = ReadFile("TextureCubeMapArray_frag.spv");

    //auto vertShaderCode = ReadFile("TextureCubeMap_vert.spv");
    //auto fragShaderCode = ReadFile("TextureCubeMap_frag.spv");
    // 创建Shader
    VertexShader= pRHI->RHICreateShader(RHIShaderType::Vertex, (std::uint32_t*)vertShaderCode.data(), vertShaderCode.size());
    FragmengShader = pRHI->RHICreateShader(RHIShaderType::Fragment, (std::uint32_t*)fragShaderCode.data(), fragShaderCode.size());
#else
    auto vertShaderCode = ReadFile2("TextureCubeMapArray_vert.glsl");
    auto fragShaderCode = ReadFile2("TextureCubeMapArray_frag.glsl");
    const char* p1 = vertShaderCode.c_str();
    const char* p2 = fragShaderCode.c_str();

    // std::cout << p1 << std::endl;
    // std::cout << p2 << std::endl;
     // 创建Shader
    RHIShader* VertexShader = pRHI->RHICreateShader(RHIShaderType::Vertex, (std::uint32_t*)p1, vertShaderCode.size());
    RHIShader* FragmengShader = pRHI->RHICreateShader(RHIShaderType::Fragment, (std::uint32_t*)p2, fragShaderCode.size());
#endif

    RHIVertexInputLayout VertexInputLayout;
    /*
        int binding, int location, RHIVertexInputAttribute::Format format, std::uint32_t offset, int matrixSlice = -1
    */
    VertexInputLayout.SetAttributes({
        { "",0, 0, RHIVertexInputAttribute::Format::Float3,  0 * sizeof(float), 0 },
        { "",0, 1, RHIVertexInputAttribute::Format::Float3,  3 * sizeof(float), 0 },
    });
    /*
        std::uint32_t stride, RHIVertexInputBinding::Classification cls = PerVertex, std::uint32_t stepRate = 1
    */
    VertexInputLayout.SetBindings({
        { 6 * sizeof(float), RHIVertexInputBinding::Classification::PerVertex, 0 },
    });
    /*
        用于创建Descriptor Set Layout和Pipeline Layout
    */
#if USE_RHIWindow
    GraphicsPipeline = pRHI->RHICreateGraphicsPipeline(RHIWindow_);
#else
    GraphicsPipeline = pRHI->RHICreateGraphicsPipeline(RenderTarget->GetRenderPass());
#endif
    GraphicsPipeline->SetShaderResourceBindings(SRB);
    GraphicsPipeline->SetPolygonMode(RHIPolygonMode::Fill);
    GraphicsPipeline->SetCullMode(RHICullMode::CullModeNone);
#if USE_RHI_VULKAN
    GraphicsPipeline->SetFrontFace(RHIFrontFace::CW);
#else
    GraphicsPipeline->SetFrontFace(RHIFrontFace::CCW);
#endif
    GraphicsPipeline->SetTopology(RHITopology::Triangles);
    GraphicsPipeline->SetVertexInputLayout(VertexInputLayout);
    GraphicsPipeline->SetShaderStages({ VertexShader , FragmengShader });
    GraphicsPipeline->Create();
}

void RHIApplicationTextureCubeMapArray::Draw()
{
    float x = 0;
    float y = 0;
    float w = 0;
    float h = 0;

#if USE_RHIWindow
    auto CommandBuffer = RHIWindow_->CurrentGraphicsCommandBuffer();
    RHIWindow_->GetExtent(x, y, w, h);
#else
    auto CommandBuffer = RenderTarget->CurrentGraphicsCommandBuffer();
    RenderTarget->GetExtent(x, y, w, h);
#endif

    RHIViewport Viewport(0, 0, w, h);
    CommandBuffer->RHISetViewport(Viewport);

    RHIScissor Scissor(0, 0, w, h);
    CommandBuffer->RHISetScissor(Scissor);

    CommandBuffer->RHISetGraphicsPipeline(GraphicsPipeline);

    CommandBuffer->RHISetDepthTestEnable(true);
    CommandBuffer->RHISetDepthCompareOp(RHICompareOp::Less);
    CommandBuffer->RHISetDepthWriteEnable(true);
    /*
        开启深度测试, 这个也要开启
    */
    CommandBuffer->RHISetDepthBoundsTestEnable(true);
    /*

    */
    CommandBuffer->RHISetStencilTestEnable(false);

    CommandBuffer->RHISetVertexInput(0, VertexInputs.size(), VertexInputs.data(), RHIEBO, 0, RHIIndexFormat::IndexUInt32);
    CommandBuffer->RHIDrawIndexedPrimitive(6, 1, 0, 0, 0);
}
