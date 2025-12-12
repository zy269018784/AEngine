#include "RHIApplicationPlayer.h"
#include "Vulkan/Common.h"
#include "Model/Model.h"

#ifdef PROJECT_USE_STB_1
    #include <stb_image.h>
    static Model model1;
#endif
/*
    VBO1三角形: 红色和黄色
    VBO1三角形: 蓝色和绿色
*/
static float VertexAttributes[] = {
    // VBO1                    
    -100.0f, -100.0f,   -100.0f,    0.0f, 0.0f,
     100.0f, -100.0f,   -100.0f,    1.0f, 0.0f,
     100.0f,  100.0f,   -100.0f,    1.0f, 1.0f,
     100.0f,  100.0f,   -100.0f,    1.0f, 1.0f,
    -100.0f,  100.0f,   -100.0f,    0.0f, 1.0f,
    -100.0f, -100.0f,   -100.0f,    0.0f, 0.0f,
                         
    //-100.0f, -100.0f, -100.0f, 
    //-100.0f,  100.0f, -100.0f, 
    //-100.0f,  100.0f,  100.0f, 
    //-100.0f,  100.0f,  100.0f, 
    //-100.0f, -100.0f,  100.0f, 
    //-100.0f, -100.0f, -100.0f, 
};

static glm::mat4 UBOData = {
     1.0f, 0.0f, 0.0f, 0.0f,
     0.0f, 1.0f, 0.0f, 0.0f,
     0.0f, 0.0f, 1.0f, 0.0f,
     0.5f, 0.0f, 0.0f, 1.0f 
};

static unsigned int Index[] = {
    0, 1, 2,
    3, 4, 5,
    //6, 7, 8,
    //9, 10, 11
};

RHIApplicationPlayer::RHIApplicationPlayer(GLFWwindow* InWindow)
    : RHIApplication(InWindow)
{ 
   
}

RHIApplicationPlayer::~RHIApplicationPlayer()
{
    delete RHIUBO;
    delete RHITexture2D;
    delete RHISampler_;
}

void RHIApplicationPlayer::Init()
{
    fov = 90.f;
    //glm::vec3 eye = glm::vec3(0, 300, 590);
    //glm::vec3 lookat = glm::vec3(0, 300, -1);
    //glm::vec3 up = glm::vec3(0, -1, 0);


    //glm::vec3 eye = glm::vec3(0, 0.3, 0.590);
    //glm::vec3 lookat = glm::vec3(0, 0.3, -1);
    //glm::vec3 up = glm::vec3(0, -1, 0);

    glm::vec3 eye    = glm::vec3(0, 0, 0);
    glm::vec3 lookat = glm::vec3(0, 0, -1);
    glm::vec3 up     = glm::vec3(0, -1, 0);


    model = glm::mat4(1.0f);
    view = glm::mat4(1.0f);
    projection = glm::mat4(1.0f);

    view = glm::lookAtRH(eye, lookat, up);
    projection = glm::perspective(glm::radians(fov), 800.f / 600.f, 0.01f, 10000.f);
    mvp = projection * view * model;
  //  mvp = model * view * projection;

    auto a = mvp * glm::vec4(0, 0, -500, 1);
    a /= a.w;
    std::cout << "a " << a.x << " " << a.y << " " << a.z << " " << a.w << std::endl;

   // model1.LoadModel("Television_01_4k/Television_01_4k.gltf");

    CreateVBO();
    CreateEBO();
    CreateUBO();
    CreateTexture();
    std::cout << "debug 1 " << std::endl;
    CreateSRB();
    std::cout << "debug 2 " << std::endl;
    CreateVertexDescriptioin();
    std::cout << "debug 3 " << std::endl;
    CreateGraphicsPipeline();
    std::cout << "debug 4 " << std::endl;
}

void RHIApplicationPlayer::CreateTexture()
{
    RHISampler_ = pRHI->RHICreateSampler(RHIFilter::NEAREST, RHIFilter::NEAREST);


    int texWidth, texHeight, texChannels;
#ifdef PROJECT_USE_STB
    /*
        STBI_rgb_alpha统一转成4通道
    */
    pixels = stbi_load("textures/texture.png", &texWidth, &texHeight, &texChannels, STBI_rgb_alpha);
    VkDeviceSize imageSize = texWidth * texHeight * 4;
    std::cout
        //<< "texture" << model1.Textures[0].c_str() << " "
        << "texWidth " << texWidth << " "
        << "texHeight  " << texHeight << " "
        << "texChannels  " << texChannels << " "
        << "pixels  " << (unsigned int)pixels[(texHeight * texWidth / 2 + texWidth / 2) * 4] << " "
        << std::endl;
    if (!pixels) {
        throw std::runtime_error("failed to load texture image!");
    }

    RHITexture2D = pRHI->RHICreateTexture2D(RHIPixelFormat::PF_R8G8B8A8_UNORM, 1, texWidth, texHeight);

    RHITexture2D->Update(0, 0, 0, 0, texWidth, texHeight, 1, pixels);
#endif
}

#define USE_MODEL 0
void RHIApplicationPlayer::CreateVBO()
{
#if USE_MODEL
    RHIVBO = pRHI->RHICreateBuffer(RHIBuffer::RHIBufferType::VertexBuffer, RHIBuffer::RHIBufferUsageFlag::Static, model1.VBOData.size() * sizeof(float), model1.VBOData.data());
    std::cout << "model1.VBOData.size() " << model1.VBOData.size() << std::endl;
#else
    RHIVBO = pRHI->RHICreateBuffer(RHIBuffer::RHIBufferType::VertexBuffer, RHIBuffer::RHIBufferUsageFlag::Static, sizeof(VertexAttributes), VertexAttributes); 
#endif
}

void RHIApplicationPlayer::CreateEBO()
{
#if USE_MODEL
    RHIEBO = pRHI->RHICreateBuffer(RHIBuffer::RHIBufferType::IndexBuffer, RHIBuffer::RHIBufferUsageFlag::Static, model1.EBOData.size() * sizeof(unsigned int), model1.EBOData.data());
    std::cout << "model1.EBOData.size() " << model1.EBOData.size() << std::endl;
#else
    RHIEBO = pRHI->RHICreateBuffer(RHIBuffer::RHIBufferType::IndexBuffer, RHIBuffer::RHIBufferUsageFlag::Static, sizeof(Index), Index);
#endif

}

void RHIApplicationPlayer::CreateUBO()
{
   // mvp = UBOData;
    RHIUBO = pRHI->RHICreateBuffer(RHIBuffer::RHIBufferType::UniformBuffer, RHIBuffer::RHIBufferUsageFlag::Static, sizeof(mvp), &mvp);
}

void RHIApplicationPlayer::CreateSRB()
{
    SRB = pRHI->RHICreateShaderResourceBindings();
    SRB->SetBindings(
        {
            RHIShaderResourceBinding::UniformBuffer(0, RHIShaderResourceBinding::StageFlags::VertexStage, RHIUBO),
            RHIShaderResourceBinding::SampledTexture(1, RHIShaderResourceBinding::StageFlags::FragmentStage, RHITexture2D, RHISampler_)
        }
        );
    SRB->Create();
}

void RHIApplicationPlayer::CreateVertexDescriptioin()
{
    VertexInputs.push_back(std::make_pair(RHIVBO, 0 * sizeof(float)));
}

void RHIApplicationPlayer::CreateGraphicsPipeline()
{
#if 1
    auto vertShaderCode = ReadFile("Player_vert.spv");
    auto fragShaderCode = ReadFile("Player_frag.spv");
    // 创建Shader
    VertexShader= pRHI->RHICreateShader(RHIShaderType::Vertex, (std::uint32_t*)vertShaderCode.data(), vertShaderCode.size());
    FragmengShader = pRHI->RHICreateShader(RHIShaderType::Fragment, (std::uint32_t*)fragShaderCode.data(), fragShaderCode.size());
#else
    auto vertShaderCode = ReadFile2("UBO_vert.glsl");
    auto fragShaderCode = ReadFile2("UBO_frag.glsl");
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
      // { 0, 2, RHIVertexInputAttribute::Format::Float,   5 * sizeof(float), 0 },
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

void RHIApplicationPlayer::Draw()
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
  
#if USE_MODEL
    CommandBuffer->RHIDrawIndexedPrimitive(model1.EBOData.size(), 1, 0, 0, 0);
#else
    CommandBuffer->RHIDrawIndexedPrimitive(6, 1, 0, 0, 0);
#endif
}
