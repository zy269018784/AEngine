#include "RHIApplicationTextureCubeMap.h"
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

RHIApplicationTextureCubeMap::RHIApplicationTextureCubeMap(GLFWwindow* InWindow)
    : RHIApplication(InWindow)
{

}

RHIApplicationTextureCubeMap::~RHIApplicationTextureCubeMap()
{
    delete RHIVBO;
    delete RHIEBO;
    delete RHITextureCubeMap;
    delete VertexShader;
    delete FragmengShader;
    delete GraphicsPipeline;
    delete SRB;
    delete RHISampler_;
}   

void RHIApplicationTextureCubeMap::Init()
{
    CreateVBO();
    CreateEBO();
    CreateTexture();
    CreateSRB();
    CreateVertexDescriptioin();
    CreateGraphicsPipeline();
}

void RHIApplicationTextureCubeMap::CreateVBO()
{
    RHIVBO = pRHI->RHICreateBuffer(RHIBuffer::RHIBufferType::VertexBuffer, RHIBuffer::RHIBufferUsageFlag::Static, sizeof(VertexAttributes), VertexAttributes);
}

void RHIApplicationTextureCubeMap::CreateEBO()
{
    RHIEBO = pRHI->RHICreateBuffer(RHIBuffer::RHIBufferType::IndexBuffer, RHIBuffer::RHIBufferUsageFlag::Static, sizeof(Index), Index);
}

void RHIApplicationTextureCubeMap::CreateTexture()
{
    RHISampler_ = pRHI->RHICreateSampler(RHIFilter::NEAREST, RHIFilter::NEAREST);

    int texWidth, texHeight, texChannels;
#ifdef PROJECT_USE_STB
    /*
        STBI_rgb_alpha统一转成4通道
    */
    stbi_uc* pixels1 = stbi_load("textures/skybox/right.jpg", &texWidth, &texHeight, &texChannels, STBI_rgb_alpha);
    stbi_uc* pixels2 = stbi_load("textures/skybox/left.jpg", &texWidth, &texHeight, &texChannels, STBI_rgb_alpha);
    stbi_uc* pixels3 = stbi_load("textures/skybox/top.jpg", &texWidth, &texHeight, &texChannels, STBI_rgb_alpha);
    stbi_uc* pixels4 = stbi_load("textures/skybox/bottom.jpg", &texWidth, &texHeight, &texChannels, STBI_rgb_alpha);
    stbi_uc* pixels5 = stbi_load("textures/skybox/front.jpg", &texWidth, &texHeight, &texChannels, STBI_rgb_alpha);
    stbi_uc* pixels6 = stbi_load("textures/skybox/back.jpg", &texWidth, &texHeight, &texChannels, STBI_rgb_alpha);
    VkDeviceSize imageSize = texWidth * texHeight * 4;
    std::cout 
        << "texWidth "   << texWidth   << " "
        << "texHeight  " << texHeight  << " "
        << "texChannels  " << texChannels << " "
        //<< "pixels  " << (unsigned int)pixels[(texHeight * texWidth / 2 + texWidth / 2) * 4] << " "
        << std::endl;
   //if (!pixels) {
   //    throw std::runtime_error("failed to load texture image!");
   //}

    //RHITexture2D = pRHI->RHICreateTexture2D(RHIPixelFormat::PF_R8G8B8A8_SRGB, 1, texWidth, texHeight);
    RHITextureCubeMap = pRHI->RHICreateTextureCube(RHIPixelFormat::PF_R8G8B8A8_UNORM, 1, texWidth, texHeight);

    RHITextureCubeMap->Update(0, 0, 0, (int)RHICubeMapFace::CUBE_MAP_POSITIVE_X, texWidth, texHeight, 1,  pixels1);
    RHITextureCubeMap->Update(0, 0, 0, (int)RHICubeMapFace::CUBE_MAP_NEGATIVE_X, texWidth, texHeight, 1,  pixels2);
    RHITextureCubeMap->Update(0, 0, 0, (int)RHICubeMapFace::CUBE_MAP_POSITIVE_Y, texWidth, texHeight, 1,  pixels3);
    RHITextureCubeMap->Update(0, 0, 0, (int)RHICubeMapFace::CUBE_MAP_NEGATIVE_Y, texWidth, texHeight, 1,  pixels4);
    RHITextureCubeMap->Update(0, 0, 0, (int)RHICubeMapFace::CUBE_MAP_POSITIVE_Z, texWidth, texHeight, 1,  pixels5);
    RHITextureCubeMap->Update(0, 0, 0, (int)RHICubeMapFace::CUBE_MAP_NEGATIVE_Z, texWidth, texHeight, 1,  pixels6);
    //pRHI->RHIUpdateTexture(RHITexture2D, pixels, imageSize);
#endif
}


void RHIApplicationTextureCubeMap::CreateSRB()
{
    SRB = pRHI->RHICreateShaderResourceBindings();
    SRB->SetBindings({
            RHIShaderResourceBinding::SampledTexture(0, RHIShaderResourceBinding::StageFlags::FragmentStage, RHITextureCubeMap, RHISampler_)
    });
    SRB->Create();
}

void RHIApplicationTextureCubeMap::CreateVertexDescriptioin()
{
    /*
        使用VBO1
    */
    VertexInputs.push_back(std::make_pair(RHIVBO, 0 * sizeof(float)));
}

void RHIApplicationTextureCubeMap::CreateGraphicsPipeline()
{
#if 1
    auto vertShaderCode = ReadFile("TextureCubeMap_vert.spv");
    auto fragShaderCode = ReadFile("TextureCubeMap_frag.spv");
    // 创建Shader
    VertexShader= pRHI->RHICreateShader(RHIShaderType::Vertex, (std::uint32_t*)vertShaderCode.data(), vertShaderCode.size());
    FragmengShader = pRHI->RHICreateShader(RHIShaderType::Fragment, (std::uint32_t*)fragShaderCode.data(), fragShaderCode.size());
#else
    auto vertShaderCode = ReadFile2("TextureCubeMap_vert.glsl");
    auto fragShaderCode = ReadFile2("TextureCubeMap_frag.glsl");
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

void RHIApplicationTextureCubeMap::Draw()
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
