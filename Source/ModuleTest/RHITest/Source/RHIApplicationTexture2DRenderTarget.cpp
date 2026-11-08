#include "RHIApplicationTexture2DRenderTarget.h"
#include "RHI/RHIObjects/Core/RHIVertexInputLayout.h"
#include "RHI/RHIObjects/Pipeline/RHIGraphicsPipeline.h"
#include "RHI/RHIObjects/RenderTarget/RHIRenderTarget.h"
#include "RHI/RHIObjects/Shader/RHIShader.h"
#include "RHI/RHIObjects/Shader/RHIShaderResourceBinding.h"
#include "RHI/RHIObjects/Shader/RHIShaderResourceBindings.h"
#include "Common.h"

#include <stb_image.h>

/*
    VBO1三角形: 红色和黄色
    VBO1三角形: 蓝色和绿色
*/
static float VertexAttributes[] = {
    // VBO1                                    // VBO2
    // pos               uv                    // pos              uv
    -0.5f, -0.5f, 0.0f,  0.0f, 0.0f,           -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
     0.5f, -0.5f, 0.0f,  1.0f, 0.0f,            0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
     0.5f,  0.5f, 0.0f,  1.0f, 1.0f,            0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
                        
     0.5f,  0.5f, 0.0f,  1.0f, 1.0f,            0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
    -0.5f,  0.5f, 0.0f,  0.0f, 1.0f,           -0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
    -0.5f, -0.5f, 0.0f,  0.0f, 0.0f,           -0.5f, -0.5f, 0.0f, 0.0f, 0.0f
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

RHIApplicationTexture2DRenderTarget::RHIApplicationTexture2DRenderTarget()
    : RHIApplication()
{

}

RHIApplicationTexture2DRenderTarget::~RHIApplicationTexture2DRenderTarget()
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

void RHIApplicationTexture2DRenderTarget::Init()
{
    CreateVBO();
    CreateEBO();
    CreateTexture();

    CreateSRB2();
    CreateTextureRenderTarget();
    CreateVertexDescriptioin();
    CreateSRB();
    CreateGraphicsPipeline();
    CreateGraphicsPipeline2();
}

void RHIApplicationTexture2DRenderTarget::CreateVBO()
{
    RHIVBO = pRHI->RHICreateBuffer(RHIBufferType::VertexBuffer, RHIBufferUsageFlag::VertexBuffer, sizeof(VertexAttributes), VertexAttributes);
}

void RHIApplicationTexture2DRenderTarget::CreateEBO()
{
    RHIEBO = pRHI->RHICreateBuffer(RHIBufferType::IndexBuffer, RHIBufferUsageFlag::IndexBuffer, sizeof(Index), Index);
}

void RHIApplicationTexture2DRenderTarget::CreateTexture()
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

    std::cout << "RHICreateTexture2D 1" << std::endl;
    RHITexture2D = pRHI->RHICreateTexture2D(RHIPixelFormat::PF_R8G8B8A8_UNORM, RHITextureUsageFlag::SampledTexture,
        RHIImageLayout::RHI_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL, 1, texWidth, texHeight, pixels);
    std::cout << "RHICreateTexture2D 2" << std::endl;
#endif
}


void RHIApplicationTexture2DRenderTarget::CreateSRB()
{
    SRB = pRHI->RHICreateShaderResourceBindings();
    SRB->SetBindings({
            RHIShaderResourceBinding::SampledTexture(0, RHIShaderType::Fragment, RHITextureRT, RHISampler_)
    });
    SRB->Create();
}

void RHIApplicationTexture2DRenderTarget::CreateSRB2()
{
    SRB2 = pRHI->RHICreateShaderResourceBindings();
    SRB2->SetBindings({
            RHIShaderResourceBinding::SampledTexture(0, RHIShaderType::Fragment, RHITexture2D, RHISampler_)
    });
    SRB2->Create();
}

void RHIApplicationTexture2DRenderTarget::CreateVertexDescriptioin()
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
    VertexInputs.push_back(std::make_pair(RHIVBO, 5 * sizeof(float)));
#endif
}

void RHIApplicationTexture2DRenderTarget::CreateGraphicsPipeline()
{
    auto vertShaderCode = ReadFile("RT_Texture2D_vert.spv");
    auto fragShaderCode = ReadFile("RT_Texture2D_frag.spv");
    // 创建Shader
    VertexShader = pRHI->RHICreateShader(RHIShaderType::Vertex, (std::uint32_t*)vertShaderCode.data(), vertShaderCode.size());
    FragmengShader = pRHI->RHICreateShader(RHIShaderType::Fragment, (std::uint32_t*)fragShaderCode.data(), fragShaderCode.size());


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
        { 10 * sizeof(float), RHIVertexInputBinding::Classification::PerVertex, 0 },
    });
    /*
        用于创建Descriptor Set Layout和Pipeline Layout
    */


    GraphicsPipeline = pRHI->RHICreateGraphicsPipeline(RenderTarget->GetRenderPass());
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


void RHIApplicationTexture2DRenderTarget::CreateGraphicsPipeline2()
{
    auto vertShaderCode = ReadFile("TextureRenderTarget_vert.spv");
    auto fragShaderCode = ReadFile("TextureRenderTarget_frag.spv");

    // 创建Shader
    VertexShader2 = pRHI->RHICreateShader(RHIShaderType::Vertex, (std::uint32_t*)vertShaderCode.data(), vertShaderCode.size());
    FragmengShader2 = pRHI->RHICreateShader(RHIShaderType::Fragment, (std::uint32_t*)fragShaderCode.data(), fragShaderCode.size());

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
        { 10 * sizeof(float), RHIVertexInputBinding::Classification::PerVertex, 0 },
    });
    /*
        用于创建Descriptor Set Layout和Pipeline Layout
    */
    GraphicsPipeline2 = pRHI->RHICreateGraphicsPipeline(TextureRenderTarget->GetRenderPass());
    GraphicsPipeline2->SetShaderResourceBindings(SRB2);
    GraphicsPipeline2->SetPolygonMode(RHIPolygonMode::Fill);
    GraphicsPipeline2->SetCullMode(RHICullMode::CullModeNone);
#if USE_RHI_VULKAN
    GraphicsPipeline2->SetFrontFace(RHIFrontFace::CW);
#else
    GraphicsPipeline2->SetFrontFace(RHIFrontFace::CCW);
#endif
    GraphicsPipeline2->SetTopology(RHITopology::Triangles);
    GraphicsPipeline2->SetVertexInputLayout(VertexInputLayout);
    GraphicsPipeline2->SetShaderStages({ VertexShader2 , FragmengShader2 });
    GraphicsPipeline2->Create();
    delete VertexShader2;
    delete FragmengShader2;
}

void RHIApplicationTexture2DRenderTarget::CreateTextureRenderTarget()
{
    RHISamplerRT = pRHI->RHICreateSampler(RHIFilter::NEAREST, RHIFilter::NEAREST);

    RHITextureRT = pRHI->RHICreateTexture2D(RHIPixelFormat::PF_R8G8B8A8_UNORM,
        RHITextureUsageFlag::ColorAttachment | RHITextureUsageFlag::SampledTexture,
        RHIImageLayout::RHI_IMAGE_LAYOUT_UNDEFINED, 1, 800, 600, nullptr);
    RHITexture * DepthTextureRT = pRHI->RHICreateTexture2D(RHIPixelFormat::PF_DepthStencil_D24_S8,
        RHITextureUsageFlag::DepthStencilAttachment,
        RHIImageLayout::RHI_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL, 1, 800, 600, nullptr);

    std::vector<RHITexture *> ColorAttachments;
    ColorAttachments.push_back(RHITextureRT);
    std::vector<RHITexture *> DepthAttachments;
    DepthAttachments.push_back(DepthTextureRT);
    TextureRenderTarget = pRHI->RHICreateTextureRenderTarget(ColorAttachments, DepthAttachments);
}
 
void RHIApplicationTexture2DRenderTarget::Draw()
{
    float x = 0;
    float y = 0;
    float w = 0;
    float h = 0;

    auto CommandBuffer = RenderTarget->CurrentGraphicsCommandBuffer();
    RenderTarget->GetExtent(x, y, w, h);

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

void RHIApplicationTexture2DRenderTarget::Draw2()
{
    float x = 0;
    float y = 0;
    float w = 0;
    float h = 0;

    auto CommandBuffer = TextureRenderTarget->CurrentGraphicsCommandBuffer();
    TextureRenderTarget->GetExtent(x, y, w, h);

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

    CommandBuffer->RHISetVertexInput(0, VertexInputs.size(), VertexInputs.data(), RHIEBO, 0, RHIIndexFormat::IndexUInt32);
    CommandBuffer->RHIDrawIndexedPrimitive(6, 1, 0, 0, 0);
}


void RHIApplicationTexture2DRenderTarget::Render()
{
    RHITextureRT->TransitionTo(RHIImageLayout::RHI_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL);

    TextureRenderTarget->RHIBeginFrame();
    TextureRenderTarget->RHIBeginRenderPass();
    Draw2();
    TextureRenderTarget->RHIEndRenderPass();
    TextureRenderTarget->RHIEndFrame();

    RHITextureRT->TransitionTo(RHIImageLayout::RHI_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);

    RenderTarget->RHIBeginFrame();
    RenderTarget->RHIBeginRenderPass();
    Draw();
    RenderTarget->RHIEndRenderPass();
    RenderTarget->RHIEndFrame();
}