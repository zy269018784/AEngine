#include "RHIApplicationSamplerObject.h"
#include "Vulkan/Common.h"
#ifdef PROJECT_USE_STB
#include <stb_image.h>
#endif
/*
    VBO1三角形: 红色和黄色
    VBO1三角形: 蓝色和绿色
*/
static float VertexAttributes[] = {
    // VBO1                        
    // pos               uv                 texture id
    /*
        Left Top: 
    */
    -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,       0.0f,
     0.0f,  0.0f,  0.0f,  2.0f,  0.0f,       0.0f,
     0.0f,  1.0f,  0.0f,  2.0f,  2.0f,       0.0f,
                                            
     0.0f,  1.0f,  0.0f,  2.0f,  2.0f,       0.0f,
    -1.0f,  1.0f,  0.0f,  0.0f,  2.0f,       0.0f,
    -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,       0.0f,

    /*
        Right Top
    */
     0.0f,  0.0f,  0.0f, 0.0f,  0.0f,       1.0f,
     1.0f,  0.0f,  0.0f, 2.0f,  0.0f,       1.0f,
     1.0f,  1.0f,  0.0f, 2.0f,  2.0f,       1.0f,

     1.0f,  1.0f,  0.0f, 2.0f,  2.0f,       1.0f,
     0.0f,  1.0f,  0.0f, 0.0f,  2.0f,       1.0f,
     0.0f,  0.0f,  0.0f, 0.0f,  0.0f,       1.0f,

     /*
         Left Bottom
     */
     -1.0f, -1.0f, 0.0f,  0.0f, 0.0f,       2.0f,
      0.0f, -1.0f, 0.0f,  2.0f, 0.0f,       2.0f,
      0.0f,  0.0f, 0.0f,  2.0f, 2.0f,       2.0f,

      0.0f,  0.0f, 0.0f,  2.0f, 2.0f,       2.0f,
     -1.0f,  0.0f, 0.0f,  0.0f, 2.0f,       2.0f,
     -1.0f, -1.0f, 0.0f,  0.0f, 0.0f,       2.0f,

     /*
         Right Bottom
     */
      0.0f,  -1.0f, 0.0f,  0.0f, 0.0f,      3.0f,
      1.0f,  -1.0f, 0.0f,  2.0f, 0.0f,      3.0f,
      1.0f,   0.0f, 0.0f,  2.0f, 2.0f,      3.0f,

      1.0f,  0.0f, 0.0f,   2.0f, 2.0f,      3.0f,
      0.0f,  0.0f, 0.0f,   0.0f, 2.0f,      3.0f,
      0.0f, -1.0f, 0.0f,   0.0f, 0.0f,      3.0f,

};

//static float VertexAttributes[] = {
//    // VBO1                                                    
//    // pos              color              uv                  
//    -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,  0.0f, 0.0f,         
//     0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,  1.0f, 0.0f,         
//     0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f,  1.0f, 1.0f,         
//
//     0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f,  1.0f, 1.0f,         
//    -0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f,  0.0f, 1.0f,         
//    -0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f,  0.0f, 0.0f,         
//};


static unsigned int Index[] = {
    0, 1, 2,
    3, 4, 5
};

RHIApplicationSamplerObject::RHIApplicationSamplerObject(GLFWwindow* InWindow)
    : RHIApplication(InWindow)
{

}

RHIApplicationSamplerObject::~RHIApplicationSamplerObject()
{
    delete RHIVBO;
    delete RHIEBO;
    //delete RHITexture2D;
    delete VertexShader;
    delete FragmengShader;
    delete GraphicsPipeline;
    delete SRB;
    //delete RHISampler_;
}   

void RHIApplicationSamplerObject::Init()
{
    CreateVBO();
    CreateEBO();
    CreateTexture();
    CreateSRB();
    CreateVertexDescriptioin();
    CreateGraphicsPipeline();
}

void RHIApplicationSamplerObject::CreateVBO()
{
    RHIVBO = pRHI->RHICreateBuffer(RHIBuffer::RHIBufferType::VertexBuffer, RHIBuffer::RHIBufferUsageFlag::Static, sizeof(VertexAttributes), VertexAttributes);
}

void RHIApplicationSamplerObject::CreateEBO()
{
    RHIEBO = pRHI->RHICreateBuffer(RHIBuffer::RHIBufferType::IndexBuffer, RHIBuffer::RHIBufferUsageFlag::Static, sizeof(Index), Index);
}

void RHIApplicationSamplerObject::CreateTexture()
{
    //RHISampler_ = pRHI->RHICreateSampler(RHIFilter::NEAREST, RHIFilter::NEAREST, RHIAddressMode::REPEAT, RHIAddressMode::CLAMP_TO_EDGE);

    RHISamplers[0] = pRHI->RHICreateSampler(RHIFilter::NEAREST, RHIFilter::NEAREST, RHIAddressMode::REPEAT, RHIAddressMode::REPEAT);
    RHISamplers[1] = pRHI->RHICreateSampler(RHIFilter::NEAREST, RHIFilter::NEAREST, RHIAddressMode::MIRRORED_REPEAT, RHIAddressMode::MIRRORED_REPEAT);
    RHISamplers[2] = pRHI->RHICreateSampler(RHIFilter::NEAREST, RHIFilter::NEAREST, RHIAddressMode::CLAMP_TO_EDGE, RHIAddressMode::CLAMP_TO_EDGE);
    RHISamplers[3] = pRHI->RHICreateSampler(RHIFilter::NEAREST, RHIFilter::NEAREST, RHIAddressMode::CLAMP_TO_BORDER, RHIAddressMode::CLAMP_TO_BORDER);

    int texWidth, texHeight, texChannels;
#ifdef PROJECT_USE_STB
    /*
        STBI_rgb_alpha统一转成4通道
    */
    stbi_uc* pixels = stbi_load("textures/texture.png", &texWidth, &texHeight, &texChannels, STBI_rgb_alpha);
    VkDeviceSize imageSize = texWidth * texHeight * 4;
    std::cout 
        << "texWidth "   << texWidth   << " "
        << "texHeight  " << texHeight  << " "
        << "texChannels  " << texChannels << " "
        << "pixels  " << (unsigned int)pixels[(texHeight * texWidth / 2 + texWidth / 2) * 4] << " "
        << std::endl;
    if (!pixels) {
        throw std::runtime_error("failed to load texture image!");
    }

    //RHITexture2D = pRHI->RHICreateTexture2D(RHIPixelFormat::PF_R8G8B8A8_UNORM, 1, texWidth, texHeight);
    //RHITexture2D->Update(0, 0, 0, 0, texWidth, texHeight, 1, pixels);
    //pRHI->RHIUpdateTexture(RHITexture2D, pixels, imageSize);

    for (int i = 0; i < 1; i++)
    {
        RHITextures[i] = pRHI->RHICreateTexture2D(RHIPixelFormat::PF_R8G8B8A8_UNORM, 1, texWidth, texHeight);
        RHITextures[i]->Update(0, 0, 0, 0, texWidth, texHeight, 1, pixels);
        pRHI->RHIUpdateTexture(RHITextures[i], pixels, imageSize);
    }
#endif
}


void RHIApplicationSamplerObject::CreateSRB()
{
    SRB = pRHI->RHICreateShaderResourceBindings();
    /*
        1   2
        3   4
    */
    SRB->SetBindings({
            RHIShaderResourceBinding::SampledTexture(0, RHIShaderResourceBinding::StageFlags::FragmentStage, RHITextures[0], RHISamplers[0]),
            RHIShaderResourceBinding::SampledTexture(1, RHIShaderResourceBinding::StageFlags::FragmentStage, RHITextures[0], RHISamplers[1]),
            RHIShaderResourceBinding::SampledTexture(2, RHIShaderResourceBinding::StageFlags::FragmentStage, RHITextures[0], RHISamplers[2]),
            RHIShaderResourceBinding::SampledTexture(3, RHIShaderResourceBinding::StageFlags::FragmentStage, RHITextures[0], RHISamplers[3]),
    });
    SRB->Create();
}

void RHIApplicationSamplerObject::CreateVertexDescriptioin()
{
    VertexInputs.push_back(std::make_pair(RHIVBO, 0 * sizeof(float)));
}

void RHIApplicationSamplerObject::CreateGraphicsPipeline()
{
//#if USE_RHI_VULKAN
#if 1
    auto vertShaderCode = ReadFile("SamplerObject_vert.spv");
    auto fragShaderCode = ReadFile("SamplerObject_frag.spv");
    // 创建Shader
    VertexShader= pRHI->RHICreateShader(RHIShaderType::Vertex, (std::uint32_t*)vertShaderCode.data(), vertShaderCode.size());
    FragmengShader = pRHI->RHICreateShader(RHIShaderType::Fragment, (std::uint32_t*)fragShaderCode.data(), fragShaderCode.size());
#else
    auto vertShaderCode = ReadFile2("SamplerObject_vert.glsl");
    auto fragShaderCode = ReadFile2("SamplerObject_frag.glsl");
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
       // { 0, 2, RHIVertexInputAttribute::Format::Float2,  6 * sizeof(float), 0 }
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
#if USE_RHI_VULKAN
    GraphicsPipeline->SetCullMode(RHICullMode::Front);
#else
    GraphicsPipeline->SetCullMode(RHICullMode::Back);
#endif
    GraphicsPipeline->SetFrontFace(RHIFrontFace::CCW);
    GraphicsPipeline->SetTopology(RHITopology::Triangles);
    GraphicsPipeline->SetVertexInputLayout(VertexInputLayout);
    GraphicsPipeline->SetShaderStages({ VertexShader , FragmengShader });
    GraphicsPipeline->Create();
}

void RHIApplicationSamplerObject::Draw()
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
#if 0
    CommandBuffer->RHISetVertexInput(0, VertexInputs.size(), VertexInputs.data(), RHIEBO, 0, RHIIndexFormat::IndexUInt32);
    CommandBuffer->RHIDrawIndexedPrimitive(6, 1, 0, 0, 0);
#else
    CommandBuffer->RHISetVertexInput(0, VertexInputs.size(), VertexInputs.data(), nullptr, 0, RHIIndexFormat::IndexUInt32);
    CommandBuffer->RHIDrawPrimitive(24);
#endif
}
