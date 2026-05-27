#include "RHIApplicationFramebuffer.h"
#include "RHI/RHIObjects/Core/RHIVertexInputLayout.h"
#include "RHI/RHIObjects/Pipeline/RHIGraphicsPipeline.h"
#include "RHI/RHIObjects/RenderTarget/RHIRenderTarget.h"
#include "RHI/RHIObjects/Shader/RHIShader.h"
#include "RHI/RHIObjects/Shader/RHIShaderResourceBinding.h"
#include "RHI/RHIObjects/Shader/RHIShaderResourceBindings.h"
#include "Vulkan/Common.h"
#if  1
#include <stb_image.h>
#endif
/*
    VBO1三角形: 红色和黄色
    VBO1三角形: 蓝色和绿色
*/
static float VertexAttributes[] = {
    -0.5f, -0.5f, 0.0f,  0.0f, 0.0f,
     0.5f, -0.5f, 0.0f,  1.0f, 0.0f,
     0.5f,  0.5f, 0.0f,  1.0f, 1.0f,
    -0.5f,  0.5f, 0.0f,  0.0f, 1.0f,
 };

static float VertexAttributes2[] = {
    -1.0f, -1.0f, 0.0f,  0.0f, 0.0f,
     1.0f, -1.0f, 0.0f,  1.0f, 0.0f,
     1.0f,  1.0f, 0.0f,  1.0f, 1.0f,
    -1.0f,  1.0f, 0.0f,  0.0f, 1.0f,
};


static unsigned int Index[] = {
    0, 1, 2,
    2, 3, 0
};

RHIApplicationFramebuffer::RHIApplicationFramebuffer()
    : RHIApplication()
{

}

RHIApplicationFramebuffer::~RHIApplicationFramebuffer()
{
    delete RHISampler_;
    delete RHITexture2D;
    return;
    delete RHIVBO;
    delete RHIEBO;
    delete RHITexture2D;
    delete VertexShader;
    delete FragmengShader;
    delete GraphicsPipeline;
    delete SRB;
    delete RHISampler_;
    delete RHISampler_;
    delete RHITexture2D;
}   

void RHIApplicationFramebuffer::Init()
{

    CreateVBO();
    CreateEBO();
    CreateTexture();

    CreateSRB();

    CreateVertexDescriptioin();

    CreateGraphicsPipeline();
    CreateGraphicsPipeline2();

}

void RHIApplicationFramebuffer::CreateVBO()
{
    RHIVBOs.push_back(pRHI->RHICreateBuffer(RHIBufferType::VertexBuffer, RHIBufferUsageFlag::VertexBuffer,
    sizeof(VertexAttributes), VertexAttributes));

    RHIVBOs.push_back(pRHI->RHICreateBuffer(RHIBufferType::VertexBuffer, RHIBufferUsageFlag::VertexBuffer,
        sizeof(VertexAttributes2), VertexAttributes2));
}

void RHIApplicationFramebuffer::CreateEBO()
{
    RHIEBO = pRHI->RHICreateBuffer(RHIBufferType::IndexBuffer, RHIBufferUsageFlag::IndexBuffer, sizeof(Index), Index);
}

void RHIApplicationFramebuffer::CreateTexture()
{
    RHISampler_ = pRHI->RHICreateSampler(RHIFilter::NEAREST, RHIFilter::NEAREST);
    int texWidth, texHeight, texChannels;
#if  1
    /*
        STBI_rgb_alpha统一转成4通道
    */
    //stbi_uc* pixels = stbi_load("textures/texture.png", &texWidth, &texHeight, &texChannels, STBI_rgb_alpha);
    stbi_uc* pixels = stbi_load("textures/asuka.jpg", &texWidth, &texHeight, &texChannels, STBI_rgb_alpha);
    auto imageSize = texWidth * texHeight * 4;
    std::cout 
        << "texWidth "   << texWidth   << " "
        << "texHeight  " << texHeight  << " "
        << "texChannels  " << texChannels << " "
        << "pixels  " << (unsigned int)pixels[(texHeight * texWidth / 2 + texWidth / 2) * 4] << " "
        << std::endl;
    if (!pixels) {
        throw std::runtime_error("failed to load texture image!");
    }

    RHITexture2D = pRHI->RHICreateTexture2D(RHIPixelFormat::PF_R8G8B8A8_UNORM, 1, texWidth, texHeight, pixels);

#endif
    RHIColorAttachments.resize(3);
    RHIColorAttachments[0] = pRHI->RHICreateTexture2D(RHIPixelFormat::PF_R8G8B8A8_UNORM, 1, texWidth, texHeight, nullptr);
    RHIColorAttachments[1] = pRHI->RHICreateTexture2D(RHIPixelFormat::PF_R8G8B8A8_UNORM, 1, texWidth, texHeight, nullptr);
    RHIColorAttachments[2] = pRHI->RHICreateTexture2D(RHIPixelFormat::PF_R8G8B8A8_UNORM, 1, texWidth, texHeight, nullptr);

    RHIDepthAttachments.resize(0);

    RHISamplers.resize(3);
    RHISamplers[0] = pRHI->RHICreateSampler(RHIFilter::NEAREST, RHIFilter::NEAREST);
    RHISamplers[1] = pRHI->RHICreateSampler(RHIFilter::NEAREST, RHIFilter::NEAREST);
    RHISamplers[2] = pRHI->RHICreateSampler(RHIFilter::NEAREST, RHIFilter::NEAREST);

    this->TextureRenderTarget = pRHI->RHICreateTextureRenderTarget(RHIColorAttachments, RHIDepthAttachments);
}


void RHIApplicationFramebuffer::CreateSRB()
{
    SRB2 = pRHI->RHICreateShaderResourceBindings();
    SRB2->SetBindings({
        RHIShaderResourceBinding::SampledTexture(0, RHIShaderType::Fragment, RHIColorAttachments[0], RHISamplers[0]),
        RHIShaderResourceBinding::SampledTexture(1, RHIShaderType::Fragment, RHIColorAttachments[1], RHISamplers[1]),
        RHIShaderResourceBinding::SampledTexture(2, RHIShaderType::Fragment, RHIColorAttachments[2], RHISamplers[2]),
    });
    SRB2->Create();

    SRB = pRHI->RHICreateShaderResourceBindings();
    SRB->SetBindings({
            RHIShaderResourceBinding::SampledTexture(0, RHIShaderType::Fragment, RHITexture2D, RHISampler_)
    });
    SRB->Create();
}

void RHIApplicationFramebuffer::CreateVertexDescriptioin()
{
    VertexInputs.push_back( std::make_pair(RHIVBOs[0], 0 * sizeof(float)));
    VertexInputs2.push_back(std::make_pair(RHIVBOs[1], 0 * sizeof(float)));
}

void RHIApplicationFramebuffer::CreateGraphicsPipeline()
{
#if OS_IS_WINDOWS
    auto vertShaderCode = ReadFile("TextureRenderTarget_vert.spv");
    auto fragShaderCode = ReadFile("TextureRenderTarget_frag.spv");
    // 创建Shader
    VertexShader= pRHI->RHICreateShader(RHIShaderType::Vertex, (std::uint32_t*)vertShaderCode.data(), vertShaderCode.size());
    FragmengShader = pRHI->RHICreateShader(RHIShaderType::Fragment, (std::uint32_t*)fragShaderCode.data(), fragShaderCode.size());

#else
    auto vertShaderCode = ReadFile2("TextureRenderTarget_vert.glsl");
    auto fragShaderCode = ReadFile2("TextureRenderTarget_frag.glsl");
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
        { "",0, 1, RHIVertexInputAttribute::Format::Float2,  3 * sizeof(float), 0 },
    });
    /*
        std::uint32_t stride, RHIVertexInputBinding::Classification cls = PerVertex, std::uint32_t stepRate = 1
    */
    VertexInputLayout.SetBindings({
        { 5 * sizeof(float), RHIVertexInputBinding::Classification::PerVertex, 0 },
    });
    /*
        用于创建Descriptor Set Layout和Pipeline Layout
    */


    GraphicsPipeline = pRHI->RHICreateGraphicsPipeline(TextureRenderTarget->GetRenderPass());

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
    delete VertexShader;
    delete FragmengShader;
    VertexShader = nullptr;
    FragmengShader = nullptr;
}


void RHIApplicationFramebuffer::CreateGraphicsPipeline2()
{
#if OS_IS_WINDOWS
    auto vertShaderCode = ReadFile("RT_Texture2D_vert.spv");
    auto fragShaderCode = ReadFile("RT_Texture2D_frag.spv");
    // 创建Shader
    VertexShader= pRHI->RHICreateShader(RHIShaderType::Vertex, (std::uint32_t*)vertShaderCode.data(), vertShaderCode.size());
    FragmengShader = pRHI->RHICreateShader(RHIShaderType::Fragment, (std::uint32_t*)fragShaderCode.data(), fragShaderCode.size());

#else
    auto vertShaderCode = ReadFile2("RT_Texture2D_vert.glsl");
    auto fragShaderCode = ReadFile2("RT_Texture2D_frag.glsl");
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
        { "",0, 1, RHIVertexInputAttribute::Format::Float2,  3 * sizeof(float), 0 },
       // { 0, 2, RHIVertexInputAttribute::Format::Float2,  6 * sizeof(float), 0 }
    });
    /*
        std::uint32_t stride, RHIVertexInputBinding::Classification cls = PerVertex, std::uint32_t stepRate = 1
    */
    VertexInputLayout.SetBindings({
        { 5 * sizeof(float), RHIVertexInputBinding::Classification::PerVertex, 0 },
    });
    /*
        用于创建Descriptor Set Layout和Pipeline Layout
    */

#if USE_RHIWindow
    GraphicsPipeline2 = pRHI->RHICreateGraphicsPipeline(RHIWindow_);
#else
    GraphicsPipeline2 = pRHI->RHICreateGraphicsPipeline(RenderTarget->GetRenderPass());
#endif
    GraphicsPipeline2->SetShaderResourceBindings(SRB2);
    GraphicsPipeline2->SetPolygonMode(RHIPolygonMode::Fill);
    GraphicsPipeline2->SetCullMode(RHICullMode::CullModeNone);
#if USE_RHI_VULKAN
    GraphicsPipeline->SetFrontFace(RHIFrontFace::CW);
#else
    GraphicsPipeline2->SetFrontFace(RHIFrontFace::CCW);
#endif
    GraphicsPipeline2->SetTopology(RHITopology::Triangles);
    GraphicsPipeline2->SetVertexInputLayout(VertexInputLayout);
    GraphicsPipeline2->SetShaderStages({ VertexShader , FragmengShader });
    GraphicsPipeline2->Create();
    delete VertexShader;
    delete FragmengShader;
    VertexShader = nullptr;
    FragmengShader = nullptr;
}

void RHIApplicationFramebuffer::Draw()
{
    float x = 0;
    float y = 0;
    float w = 0;
    float h = 0;

#if USE_RHIWindow
    auto CommandBuffer = RHIWindow_->CurrentGraphicsCommandBuffer();
    RHIWindow_->GetExtent(x, y, w, h);
#else
    auto CommandBuffer = TextureRenderTarget->CurrentGraphicsCommandBuffer();
    TextureRenderTarget->GetExtent(x, y, w, h);
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



void RHIApplicationFramebuffer::Draw2()
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

    CommandBuffer->RHISetGraphicsPipeline(GraphicsPipeline2);

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


    CommandBuffer->RHISetVertexInput(0, VertexInputs2.size(), VertexInputs2.data(), RHIEBO, 0, RHIIndexFormat::IndexUInt32);

    CommandBuffer->RHIDrawIndexedPrimitive(6, 1, 0, 0, 0);
}