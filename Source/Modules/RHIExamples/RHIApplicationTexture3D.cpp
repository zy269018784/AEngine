#include "RHIApplicationTexture3D.h"
#include "Vulkan/Common.h"
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

RHIApplicationTexture3D::RHIApplicationTexture3D(GLFWwindow* InWindow)
    : RHIApplication(InWindow)
{

}

RHIApplicationTexture3D::~RHIApplicationTexture3D()
{
    delete RHIVBO;
    delete RHIEBO;
    delete RHITexture2D;
    delete VertexShader;
    delete FragmengShader;
    delete GraphicsPipeline;
    delete SRB;
    delete RHISampler_;
}   

void RHIApplicationTexture3D::Init()
{
    CreateVBO();
    CreateEBO();
    CreateTexture();
    CreateSRB();
    CreateVertexDescriptioin();
    CreateGraphicsPipeline();
}

void RHIApplicationTexture3D::CreateVBO()
{
    RHIVBO = pRHI->RHICreateBuffer(RHIBuffer::RHIBufferType::VertexBuffer, RHIBuffer::RHIBufferUsageFlag::Static, sizeof(VertexAttributes), VertexAttributes);
}

void RHIApplicationTexture3D::CreateEBO()
{
    RHIEBO = pRHI->RHICreateBuffer(RHIBuffer::RHIBufferType::IndexBuffer, RHIBuffer::RHIBufferUsageFlag::Static, sizeof(Index), Index);
}

void RHIApplicationTexture3D::CreateTexture()
{
    RHISampler_ = pRHI->RHICreateSampler(RHIFilter::LINEAR, RHIFilter::LINEAR);

    int texWidth, texHeight, texChannels;
    ///*
    //    STBI_rgb_alpha统一转成4通道
    //*/
    //stbi_uc* pixels = stbi_load("textures/texture.png", &texWidth, &texHeight, &texChannels, STBI_rgb_alpha);
    //VkDeviceSize imageSize = texWidth * texHeight * 4;
    //std::cout 
    //    << "texWidth "   << texWidth   << " "
    //    << "texHeight  " << texHeight  << " "
    //    << "texChannels  " << texChannels << " "
    //    << "pixels  " << (unsigned int)pixels[(texHeight * texWidth / 2 + texWidth / 2) * 4] << " "
    //    << std::endl;
    //if (!pixels) {
    //    throw std::runtime_error("failed to load texture image!");
    //}

    std::uint8_t* pixels = new std::uint8_t[32 * 32 * 32 * 4];


    std::cout << "aaaa 1" << std::endl;
    //RHITexture2D = pRHI->RHICreateTexture2D(RHIPixelFormat::PF_R8G8B8A8_SRGB, 1, texWidth, texHeight);
    RHITexture2D = pRHI->RHICreateTexture3D(RHIPixelFormat::PF_R8G8B8A8_UNORM, 1, 32, 32, 32);
    for (int layer = 0; layer < 32; layer++)
    {
        for (int col = 0; col < 32; col++)
        {
            for (int row = 0; row < 32; row++)
            {
                int offset = 4 * (layer * 32 * 32 + 32 * row + col);
                pixels[offset + 0] = 255;
                pixels[offset + 1] = 255;
                pixels[offset + 2] = 0;
                pixels[offset + 3] = 255;

                if (layer == 0)
                {
                    pixels[offset + 0] = 255;
                    pixels[offset + 1] = 0;
                    pixels[offset + 2] = 0;
                    pixels[offset + 3] = 255;
                }

                if (layer == 1)
                {
                    pixels[offset + 0] = 0;
                    pixels[offset + 1] = 255;
                    pixels[offset + 2] = 0;
                    pixels[offset + 3] = 255;
                }

                if (layer == 2)
                {
                    pixels[offset + 0] = 0;
                    pixels[offset + 1] = 0;
                    pixels[offset + 2] = 255;
                    pixels[offset + 3] = 255;
                }
            }
        }
    }
    RHITexture2D->Update(0, 0, 0, 0, 32, 32, 32, pixels);
    std::cout << "aaaa 2" << std::endl;
    //pRHI->RHIUpdateTexture(RHITexture2D, pixels, imageSize);

}


void RHIApplicationTexture3D::CreateSRB()
{
    SRB = pRHI->RHICreateShaderResourceBindings();
    SRB->SetBindings({
            RHIShaderResourceBinding::SampledTexture(0, RHIShaderResourceBinding::StageFlags::FragmentStage, RHITexture2D, RHISampler_)
    });
    SRB->Create();
}

void RHIApplicationTexture3D::CreateVertexDescriptioin()
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

void RHIApplicationTexture3D::CreateGraphicsPipeline()
{
#if 1
    auto vertShaderCode = ReadFile("Texture3D_vert.spv");
    auto fragShaderCode = ReadFile("Texture3D_frag.spv");
    // 创建Shader
    VertexShader= pRHI->RHICreateShader(RHIShaderType::Vertex, (std::uint32_t*)vertShaderCode.data(), vertShaderCode.size());
    FragmengShader = pRHI->RHICreateShader(RHIShaderType::Fragment, (std::uint32_t*)fragShaderCode.data(), fragShaderCode.size());
#else
    auto vertShaderCode = ReadFile2("Texture2D_vert.glsl");
    auto fragShaderCode = ReadFile2("Texture2D_frag.glsl");
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
        { 0, 1, RHIVertexInputAttribute::Format::Float2,  3 * sizeof(float), 0 },
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

void RHIApplicationTexture3D::Draw()
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
