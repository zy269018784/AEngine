#include "RHIApplicationTexture1D.h"
#include "Vulkan/Common.h"
#ifdef PROJECT_USE_STB
#include <stb_image.h>
#endif
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

RHIApplicationTexture1D::RHIApplicationTexture1D(GLFWwindow* InWindow)
    : RHIApplication(InWindow)
{

}

RHIApplicationTexture1D::~RHIApplicationTexture1D()
{
    delete RHIVBO;
    delete RHIEBO;
    delete RHITexture2D;
    delete VertexShader;
    delete FragmengShader;
    delete GraphicsPipeline;
    delete SRB;
    delete RHISampler1D_;
    delete RHISampler2D_;
}   

void RHIApplicationTexture1D::Init()
{
    CreateVBO();
    CreateEBO();
    CreateTexture();
    CreateSRB();
    CreateVertexDescriptioin();
    CreateGraphicsPipeline();
}

void RHIApplicationTexture1D::CreateVBO()
{
    RHIVBO = pRHI->RHICreateBuffer(RHIBuffer::RHIBufferType::VertexBuffer, RHIBuffer::RHIBufferUsageFlag::Static, sizeof(VertexAttributes), VertexAttributes);
}

void RHIApplicationTexture1D::CreateEBO()
{
    RHIEBO = pRHI->RHICreateBuffer(RHIBuffer::RHIBufferType::IndexBuffer, RHIBuffer::RHIBufferUsageFlag::Static, sizeof(Index), Index);
}

void RHIApplicationTexture1D::CreateTexture()
{
#if 0
    RHISampler2D_ = pRHI->RHICreateSampler(RHIFilter::NEAREST, RHIFilter::NEAREST);
  
    int texWidth, texHeight, texChannels;
    /*
        STBI_rgb_alpha统一转成4通道
    */
    stbi_uc* pixels = stbi_load("textures/awesomeface.png", &texWidth, &texHeight, &texChannels, STBI_rgb_alpha);
    VkDeviceSize imageSize = texWidth * texHeight * 4;
    std::cout 
        << "texWidth "   << texWidth   << " "
        << "texHeight  " << texHeight  << " "
        << "texChannels  " << texChannels << " "
        << std::endl;
    if (!pixels) {
        throw std::runtime_error("failed to load texture image!");
    }

    RHITexture2D = pRHI->RHICreateTexture2D(RHIPixelFormat::PF_R8G8B8A8_UNORM, 1, texWidth, texHeight);

    pRHI->RHIUpdateTexture(RHITexture2D, pixels, imageSize);
#endif
    /*
        1D Texture
    */ 
    RHISampler1D_ = pRHI->RHICreateSampler(RHIFilter::NEAREST, RHIFilter::NEAREST);
    unsigned char RGBA[4] = { 0, 0, 255, 255 };
#if USE_RHI_VULKAN
     RHITexture1D = pRHI->RHICreateTexture1D(RHIPixelFormat::PF_R8_UINT, 1, 4);
    pRHI->RHIUpdateTexture(RHITexture1D, RGBA, 4);
#else   
    //RHITexture1D = pRHI->RHICreateTexture1D(RHIPixelFormat::PF_R8_UINT, 1, 4);
    //RHITexture1D->Update(0, 0, 0, 0, 4, 1, 1, RGBA);
    GLuint Texture1DHandle;
    glGenTextures(1, &Texture1DHandle);
    glBindTexture(GL_TEXTURE_1D, Texture1DHandle);
    glTexStorage1D(GL_TEXTURE_1D, 1, GL_R8, 4);
#if 0
    glTexSubImage1D(GL_TEXTURE_1D, 0, 0, 4, GL_RED, GL_UNSIGNED_BYTE, (const void*)&RGBA);
#else
    glTexSubImage2D(
        GL_TEXTURE_1D,      // 目标
        0,                  // 层级（Mipmap级别，0是基础级别）
        0,                  // x方向的偏移量（对应于1D纹理的索引）
        0,                  // y方向的偏移量！！！ 关键：必须为0，因为只有一行
        4,                   // 要更新的宽度
        1,                  // 要更新的高度！！！ 关键：必须为1
        GL_RED,            // 数据格式（必须与内部格式兼容）
        GL_UNSIGNED_BYTE,   // 数据类型
        (const void*)&RGBA      // 指向新数据的指针
    );
#endif
    glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // glTexParameteri(Target, GL_TEXTURE_WRAP_R, GL_REPEAT);

     // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glActiveTexture(GL_TEXTURE0);
    glActiveTexture(GL_TEXTURE1);
    glActiveTexture(GL_TEXTURE2);
#endif
}


void RHIApplicationTexture1D::CreateSRB()
{
    SRB = pRHI->RHICreateShaderResourceBindings();
    SRB->SetBindings({
           // RHIShaderResourceBinding::SampledTexture(1, RHIShaderResourceBinding::StageFlags::FragmentStage, RHITexture2D, RHISampler2D_),
            RHIShaderResourceBinding::SampledTexture(0, RHIShaderResourceBinding::StageFlags::FragmentStage, RHITexture1D, RHISampler1D_)
    });
    //SRB->Create();
}

void RHIApplicationTexture1D::CreateVertexDescriptioin()
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

void RHIApplicationTexture1D::CreateGraphicsPipeline()
{
#if 1
    auto vertShaderCode = ReadFile("Texture1D_vert.spv");
    auto fragShaderCode = ReadFile("Texture1D_frag.spv");
    // 创建Shader
    VertexShader= pRHI->RHICreateShader(RHIShaderType::Vertex, (std::uint32_t*)vertShaderCode.data(), vertShaderCode.size());
    FragmengShader = pRHI->RHICreateShader(RHIShaderType::Fragment, (std::uint32_t*)fragShaderCode.data(), fragShaderCode.size());
#else
    auto vertShaderCode = ReadFile2("Texture1D_vert.glsl");
    auto fragShaderCode = ReadFile2("Texture1D_frag.glsl");
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
        { 0, 2, RHIVertexInputAttribute::Format::Float2,  6 * sizeof(float), 0 }
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
    GraphicsPipeline = pRHI->RHICreateGraphicsPipeline(RHIWindow_);
    GraphicsPipeline->SetShaderResourceBindings(SRB);
    GraphicsPipeline->SetPolygonMode(RHIPolygonMode::Fill);
    GraphicsPipeline->SetCullMode(RHICullMode::Back);
    GraphicsPipeline->SetFrontFace(RHIFrontFace::CCW);
    GraphicsPipeline->SetTopology(RHITopology::Triangles);
    GraphicsPipeline->SetVertexInputLayout(VertexInputLayout);
    GraphicsPipeline->SetShaderStages({ VertexShader , FragmengShader });
    GraphicsPipeline->Create();
}

void RHIApplicationTexture1D::Draw()
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
