#include "RHIApplicationTextureCubeMapArray.h"
#include "Vulkan/Common.h"
#ifdef PROJECT_USE_STB
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


RHIApplicationTextureCubeMapArray::RHIApplicationTextureCubeMapArray(GLFWwindow* InWindow)
    : RHIApplication(InWindow)
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
    RHIVBO = pRHI->RHICreateBuffer(RHIBuffer::RHIBufferType::VertexBuffer, RHIBuffer::RHIBufferUsageFlag::Static, sizeof(VertexAttributes), VertexAttributes);
}

void RHIApplicationTextureCubeMapArray::CreateEBO()
{
    RHIEBO = pRHI->RHICreateBuffer(RHIBuffer::RHIBufferType::IndexBuffer, RHIBuffer::RHIBufferUsageFlag::Static, sizeof(Index), Index);
}

void RHIApplicationTextureCubeMapArray::CreateTexture()
{
    RHISampler_ = pRHI->RHICreateSampler(RHIFilter::NEAREST, RHIFilter::NEAREST);

#ifdef PROJECT_USE_STB
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

    VkDeviceSize imageSize = texWidth * texHeight * 4;
    std::cout 
        << "texWidth "   << texWidth   << " "
        << "texHeight  " << texHeight  << " "
        << "texChannels  " << texChannels << " "
        << std::endl;

#if 1
    RHITextureCubeMapArray = pRHI->RHICreateTextureCubeArray(RHIPixelFormat::PF_R8G8B8A8_UNORM, 1, texWidth, texHeight, 2);

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
#else
    RHITextureCubeMapArray = pRHI->RHICreateTextureCube(RHIPixelFormat::PF_R8G8B8A8_UNORM, 1, texWidth, texHeight);
    RHITextureCubeMapArray->Update(0, 0, 0, (int)RHICubeMapFace::CUBE_MAP_POSITIVE_X, texWidth, texHeight, 1, pixels);
    RHITextureCubeMapArray->Update(0, 0, 0, (int)RHICubeMapFace::CUBE_MAP_NEGATIVE_X, texWidth, texHeight, 1, pixels);
    RHITextureCubeMapArray->Update(0, 0, 0, (int)RHICubeMapFace::CUBE_MAP_POSITIVE_Y, texWidth, texHeight, 1, pixels);
    RHITextureCubeMapArray->Update(0, 0, 0, (int)RHICubeMapFace::CUBE_MAP_NEGATIVE_Y, texWidth, texHeight, 1, pixels);
    RHITextureCubeMapArray->Update(0, 0, 0, (int)RHICubeMapFace::CUBE_MAP_POSITIVE_Z, texWidth, texHeight, 1, pixels);
    RHITextureCubeMapArray->Update(0, 0, 0, (int)RHICubeMapFace::CUBE_MAP_NEGATIVE_Z, texWidth, texHeight, 1, pixels);
#endif
    //pRHI->RHIUpdateTexture(RHITexture2D, pixels, imageSize);
#endif
}


void RHIApplicationTextureCubeMapArray::CreateSRB()
{
    SRB = pRHI->RHICreateShaderResourceBindings();
    SRB->SetBindings({
            RHIShaderResourceBinding::SampledTexture(0, RHIShaderResourceBinding::StageFlags::FragmentStage, RHITextureCubeMapArray, RHISampler_)
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
        { 0, 0, RHIVertexInputAttribute::Format::Float3,  0 * sizeof(float), 0 },
        { 0, 1, RHIVertexInputAttribute::Format::Float3,  3 * sizeof(float), 0 },
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
    GraphicsPipeline = pRHI->RHICreateGraphicsPipeline(RHIWindow_);
    GraphicsPipeline->SetShaderResourceBindings(SRB);
    GraphicsPipeline->SetPolygonMode(RHIPolygonMode::Fill);
    GraphicsPipeline->SetCullMode(RHICullMode::Back);
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
    auto CommandBuffer = RHIWindow_->CurrentGraphicsCommandBuffer();

    float x = 0;
    float y = 0;
    float w = 0;
    float h = 0;
    RHIWindow_->GetExtent(x, y, w, h);

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
