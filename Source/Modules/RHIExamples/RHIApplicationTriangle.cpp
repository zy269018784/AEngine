#include "RHIApplicationTriangle.h"
#include "Vulkan/Common.h"


#if USE_RHI_VULKAN
/*
    VBO1三角形: 红色和黄色
    VBO1三角形: 蓝色和绿色
*/
static float VertexAttributes[] = {
    // VBO1                                     // VBO2 
     0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f,        0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
     0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,        0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
    -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,       -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,

    -0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f,       -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
    -0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f,       -0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
     0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f,        0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
};
#else
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
#endif

RHIApplicationTriangle::RHIApplicationTriangle(IWindow* InWindow)
    : RHIApplication(InWindow)
{

}

void RHIApplicationTriangle::Init()
{
    /*
        创建VBO
    */
    CreateVBO();
    /*
        创建顶点描述
    */
    CreateVertexDescriptioin();
    /*
        创建图形管线
    */
    CreateGraphicsPipeline();

    std::cout << "Init OK" << std::endl;
}

void RHIApplicationTriangle::CreateVBO()
{
    RHIVBO = pRHI->RHICreateBuffer(RHIBuffer::RHIBufferType::VertexBuffer, RHIBuffer::RHIBufferUsageFlag::Static, sizeof(VertexAttributes), VertexAttributes);
    std::cout << "CreateVBO OK" << std::endl;
}


void RHIApplicationTriangle::CreateSRB()
{
    SRB = pRHI->RHICreateShaderResourceBindings();
    SRB->Create();
    std::cout << "CreateSRB OK" << std::endl;
}

void RHIApplicationTriangle::CreateVertexDescriptioin()
{
#if 0
    /*
        使用VBO1
    */
    VertexInputs.push_back(std::make_pair(RHIVBO, 0 * sizeof(float)));
#else
    /*
        使用VBO2
    */
    VertexInputs.push_back(std::make_pair(RHIVBO, 6 * sizeof(float)));
#endif
}

void RHIApplicationTriangle::CreateGraphicsPipeline()
{
#if 1
    auto vertShaderCode = ReadFile("DrawTriangle_vert.spv");
    auto fragShaderCode = ReadFile("DrawTriangle_frag.spv");
    // 创建Shader
    VertexShader= pRHI->RHICreateShader(RHIShaderType::Vertex,   (std::uint32_t*)vertShaderCode.data(), vertShaderCode.size());
    FragmengShader = pRHI->RHICreateShader(RHIShaderType::Fragment, (std::uint32_t*)fragShaderCode.data(), fragShaderCode.size());
#else
    auto vertShaderCode = ReadFile2("DrawTriangle_vert.glsl");
    auto fragShaderCode = ReadFile2("DrawTriangle_frag.glsl");
    const char* p1 = vertShaderCode.c_str();
    const char* p2 = fragShaderCode.c_str();

     std::cout << p1 << std::endl;
     std::cout << p2 << std::endl;
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
    GraphicsPipeline->SetCullMode(RHICullMode::Back);
    GraphicsPipeline->SetFrontFace(RHIFrontFace::CCW);
    GraphicsPipeline->SetTopology(RHITopology::Triangles);
    GraphicsPipeline->SetVertexInputLayout(VertexInputLayout);
    GraphicsPipeline->SetShaderStages({ VertexShader , FragmengShader });
    GraphicsPipeline->Create();

    std::cout << "CreateGraphicsPipeline OK" << std::endl;

    /*
        vulkan要求删除
    */
    delete VertexShader;
    delete FragmengShader;
}

void RHIApplicationTriangle::Draw()
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
    CommandBuffer->RHISetVertexInput(0, VertexInputs.size(), VertexInputs.data(), nullptr, 0, RHIIndexFormat::IndexUInt32);
    CommandBuffer->RHIDrawPrimitive(6);
}
