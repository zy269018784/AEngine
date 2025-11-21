#include "RHIApplicationSSBO.h"
#include "Vulkan/Common.h"
  
/*
    VBO1三角形: 红色和黄色
    VBO1三角形: 蓝色和绿色
*/
static float VertexAttributes[] = {
    // VBO1                                     // VBO2
    -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,       -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
     0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,        0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
     0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f,        0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
     0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f,        0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
    -0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f,       -0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
    -0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f,       -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
};

static float SSBOData[][4] = {
    /*
        红
    */
    { 1.0f, 0.0f, 0.0f, 0.0f },
    /*
        绿
    */
    { 0.0f, 1.0f, 0.0f, 0.0f },
    /*
        蓝
    */
    { 0.0f, 0.0f, 1.0f, 0.0f },
    /*
        黄
    */
    { 1.0f, 1.0f, 0.0f, 0.0f }
};

static unsigned int Index[] = {
    0, 1, 2,
    3, 4, 5
};

RHIApplicationSSBO::RHIApplicationSSBO(GLFWwindow* InWindow)
    : RHIApplication(InWindow)
{

}

RHIApplicationSSBO::~RHIApplicationSSBO()
{
    for (int i = 0; i < 4; i++)
    {
        delete RHISSBO[i];
    }
}

void RHIApplicationSSBO::Init()
{
    CreateVBO();
    CreateEBO();
    std::cout << "RHIApplicationSSBO::Init 1" << std::endl;
    CreateSSBO();
    std::cout << "RHIApplicationSSBO::Init 2" << std::endl;
    CreateSRB();
    std::cout << "RHIApplicationSSBO::Init 3" << std::endl;
    CreateVertexDescriptioin();
    std::cout << "RHIApplicationSSBO::Init 4" << std::endl;
    CreateGraphicsPipeline();
    std::cout << "RHIApplicationSSBO::Init ok" << std::endl;
}

void RHIApplicationSSBO::CreateVBO()
{
    RHIVBO = pRHI->RHICreateBuffer(RHIBuffer::RHIBufferType::VertexBuffer, RHIBuffer::RHIBufferUsageFlag::Static, sizeof(VertexAttributes), VertexAttributes);
}

void RHIApplicationSSBO::CreateEBO()
{
    RHIEBO = pRHI->RHICreateBuffer(RHIBuffer::RHIBufferType::IndexBuffer, RHIBuffer::RHIBufferUsageFlag::Static, sizeof(Index), Index);
}

void RHIApplicationSSBO::CreateSSBO()
{
    for (int i = 0; i < 4; i++)
    {
        RHISSBO[i] = pRHI->RHICreateBuffer(RHIBuffer::RHIBufferType::StorageBuffer, RHIBuffer::RHIBufferUsageFlag::Static, sizeof(SSBOData[i]), SSBOData[i]);
    }
}

void RHIApplicationSSBO::CreateSRB()
{
    SRB = pRHI->RHICreateShaderResourceBindings();
    SRB->SetBindings(
        {
            RHIShaderResourceBinding::StorageBuffer(0, RHIShaderResourceBinding::StageFlags::FragmentStage, RHISSBO[0]),
            RHIShaderResourceBinding::StorageBuffer(1, RHIShaderResourceBinding::StageFlags::FragmentStage, RHISSBO[1]),
            RHIShaderResourceBinding::StorageBuffer(2, RHIShaderResourceBinding::StageFlags::FragmentStage, RHISSBO[2]),
            RHIShaderResourceBinding::StorageBuffer(3, RHIShaderResourceBinding::StageFlags::FragmentStage, RHISSBO[3]),
        }
    );
    SRB->Create();
}

void RHIApplicationSSBO::CreateVertexDescriptioin()
{
#if 0
    /*
        使用VBO1
    */
    //VertexInputs.push_back(std::make_pair(RHIVBO, 0 * sizeof(float)));
#else
    /*
        使用VBO2
    */
    VertexInputs.push_back(std::make_pair(RHIVBO, 6 * sizeof(float)));
#endif
}

void RHIApplicationSSBO::CreateGraphicsPipeline()
{
#if USE_RHI_VULKAN
    auto vertShaderCode = ReadFile("SSBO_vert.spv");
    auto fragShaderCode = ReadFile("SSBO_frag.spv");
    // 创建Shader
    VertexShader= pRHI->RHICreateShader(RHIShaderType::Vertex, (std::uint32_t*)vertShaderCode.data(), vertShaderCode.size());
    FragmengShader = pRHI->RHICreateShader(RHIShaderType::Fragment, (std::uint32_t*)fragShaderCode.data(), fragShaderCode.size());
#else
    auto vertShaderCode = ReadFile2("SSBO_vert.glsl");
    auto fragShaderCode = ReadFile2("SSBO_frag.glsl");
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
        { 12 * sizeof(float), RHIVertexInputBinding::Classification::PerVertex, 0 },
        });
    /*
        用于创建Descriptor Set Layout和Pipeline Layout
    */
    GraphicsPipeline = pRHI->RHICreateGraphicsPipeline(RHIWindow_);
    GraphicsPipeline->SetShaderResourceBindings(SRB);
    GraphicsPipeline->SetPolygonMode(RHIPolygonMode::Fill);
    GraphicsPipeline->SetCullMode(RHICullMode::Front);
    GraphicsPipeline->SetFrontFace(RHIFrontFace::CCW);
    GraphicsPipeline->SetTopology(RHITopology::Triangles);
    GraphicsPipeline->SetVertexInputLayout(VertexInputLayout);
    GraphicsPipeline->SetShaderStages({ VertexShader , FragmengShader });
    GraphicsPipeline->Create();

    /*
        vulkan要求删除
    */
    delete VertexShader;
    delete FragmengShader;
}

void RHIApplicationSSBO::Draw()
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
