#include "RHIApplicationTexture2DArray.h"
#include "Common.h"
#if  1
#include <stb_image.h>
#endif

#include "RHI/RHIObjects/Core/RHIVertexInputLayout.h"
#include "RHI/RHIObjects/Pipeline/RHIGraphicsPipeline.h"
#include "RHI/RHIObjects/RenderTarget/RHIRenderTarget.h"
#include "RHI/RHIObjects/Shader/RHIShaderResourceBinding.h"
#include "RHI/RHIObjects/Shader/RHIShaderResourceBindings.h"
/*
    VBO1三角形: 红色和黄色
    VBO1三角形: 蓝色和绿色
*/
static float VertexAttributes[] = {
    // VBO1                                                      // VBO2
    // pos              color              uv                    // pos              color              uv
    -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,  0.0f, 0.0f,           -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,  0.0f, 0.0f,
     0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,  1.0f, 0.0f,            0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,  1.0f, 0.0f,
     0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f,  1.0f, 1.0f,            0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 0.0f,  1.0f, 1.0f,

     0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f,  1.0f, 1.0f,            0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f,  1.0f, 1.0f,
    -0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f,  0.0f, 1.0f,           -0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f,  0.0f, 1.0f,
    -0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f,  0.0f, 0.0f,           -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,  0.0f, 0.0f
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

RHIApplicationTexture2DArray::RHIApplicationTexture2DArray()
    : RHIApplication()
{

}

RHIApplicationTexture2DArray::~RHIApplicationTexture2DArray()
{
    delete RHITexture2DArray;
    delete RHISampler2DArray;
    delete VertexShader;
    delete FragmengShader;
}   

void RHIApplicationTexture2DArray::Init()
{
    CreateVBO();
    CreateEBO();
    CreateTexture();
    CreateSRB();
    CreateVertexDescriptioin();
    CreateGraphicsPipeline();
}

void RHIApplicationTexture2DArray::CreateVBO()
{
    RHIVBO = pRHI->RHICreateBuffer(RHIBufferType::VertexBuffer, RHIBufferUsageFlag::VertexBuffer, sizeof(VertexAttributes), VertexAttributes);
}

void RHIApplicationTexture2DArray::CreateEBO()
{
    RHIEBO = pRHI->RHICreateBuffer(RHIBufferType::IndexBuffer, RHIBufferUsageFlag::IndexBuffer, sizeof(Index), Index);
}

void RHIApplicationTexture2DArray::CreateTexture()
{
    //RHISampler_ = pRHI->RHICreateSampler(RHIFilter::NEAREST, RHIFilter::NEAREST);

    int texWidth, texHeight, texChannels;
    int texWidth2, texHeight2, texChannels2;
#if  1
    /*
        STBI_rgb_alpha统一转成4通道,
        有些vulkan设备不支持R8G8B8
    */
    stbi_uc* pixels  = stbi_load("textures/TextureArray_1.jpg", &texWidth, &texHeight, &texChannels, STBI_rgb_alpha);
    stbi_uc* pixels2 = stbi_load("textures/TextureArray_2.jpg", &texWidth2, &texHeight2, &texChannels2, STBI_rgb_alpha);
    std::uint32_t TextureSize = texWidth * texHeight * 4;
    std::vector<std::uint8_t> ImageArrayData(TextureSize * 2);

    std::memcpy(ImageArrayData.data(), pixels, TextureSize);                    // 拷贝第一个纹理
    std::memcpy(ImageArrayData.data() + TextureSize, pixels2, TextureSize);    // 拷贝第二个纹理

    //VkDeviceSize imageSize = texWidth * texHeight * 4;
    std::cout 
        << "texWidth "   << texWidth   << " "
        << "texHeight  " << texHeight  << " "
        << "texChannels  " << texChannels << " "
        << std::endl;
    if (!pixels) {
        throw std::runtime_error("failed to load texture image!");
    }
    RHIPixelFormat PF = RHIPixelFormat::PF_R8G8B8A8_UNORM;

    //RHITexture2D = pRHI->RHICreateTexture2D(PF, 1, texWidth, texHeight);

    //pRHI->RHIUpdateTexture(RHITexture2D, pixels2, imageSize);

    RHISampler2DArray = pRHI->RHICreateSampler(RHIFilter::NEAREST, RHIFilter::NEAREST);

    RHITexture2DArray = pRHI->RHICreateTexture2DArray(PF,
        RHITextureUsageFlag::SampledTexture,
        RHIImageLayout::RHI_IMAGE_LAYOUT_UNDEFINED,
        1, texWidth, texHeight, 2, ImageArrayData.data());
   // RHITexture2DArray->Update(0, 0, 0, 0, 1024, 1024, 1, pixels);
   // RHITexture2DArray->Update(0, 0, 0, 1, 1024, 1024, 1, pixels2);
#endif
}


void RHIApplicationTexture2DArray::CreateSRB()
{
    SRB = pRHI->RHICreateShaderResourceBindings();
    SRB->SetBindings({
         //   RHIShaderResourceBinding::SampledTexture(0, RHIShaderType::Fragment, RHITexture2D, RHISampler_),
            RHIShaderResourceBinding::SampledTexture(0, RHIShaderType::Fragment, RHITexture2DArray, RHISampler2DArray)
    });
    SRB->Create();
}

void RHIApplicationTexture2DArray::CreateVertexDescriptioin()
{
#if 1
    /*
        使用VBO1
    */
    VertexInputs.push_back(std::make_pair(RHIVBO, 0 * sizeof(float)));
#else
    /*
        使用VBO2
    */
    VertexInputs.push_back(std::make_pair(RHIVBO, 8 * sizeof(float)));
#endif
}

void RHIApplicationTexture2DArray::CreateGraphicsPipeline()
{
#if OS_IS_WINDOWS
    auto vertShaderCode = ReadFile("Texture2DArray_vert.spv");
    auto fragShaderCode = ReadFile("Texture2DArray_frag.spv");
    // 创建Shader
    VertexShader= pRHI->RHICreateShader(RHIShaderType::Vertex,   (std::uint32_t*)vertShaderCode.data(), vertShaderCode.size());
    FragmengShader = pRHI->RHICreateShader(RHIShaderType::Fragment, (std::uint32_t*)fragShaderCode.data(), fragShaderCode.size());
#else
    auto vertShaderCode = ReadFile2("Texture2DArray_vert.glsl");
    auto fragShaderCode = ReadFile2("Texture2DArray_frag.glsl");
    const char* p1 = vertShaderCode.c_str();
    const char* p2 = fragShaderCode.c_str();
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
        { "",0, 2, RHIVertexInputAttribute::Format::Float2,  6 * sizeof(float), 0 }
    });
    /*
        std::uint32_t stride, RHIVertexInputBinding::Classification cls = PerVertex, std::uint32_t stepRate = 1
    */
    VertexInputLayout.SetBindings({
        { 16 * sizeof(float), RHIVertexInputBinding::Classification::PerVertex, 0 },
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

void RHIApplicationTexture2DArray::Draw()
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
