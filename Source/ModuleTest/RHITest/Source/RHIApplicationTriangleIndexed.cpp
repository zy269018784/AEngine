#include "RHIApplicationTriangleIndexed.h"
#include "RHI/RHIObjects/Core/RHIVertexInputAttribute.h"
#include "RHI/RHIObjects/Pipeline/RHIGraphicsPipeline.h"
#include "RHI/RHIObjects/RenderTarget/RHIRenderTarget.h"
#include "RHI/RHIObjects/Shader/RHIShaderResourceBindings.h"
#include "Common.h"

/*
    VBO1三角形: 红色和黄色
    VBO1三角形: 蓝色和绿色

        4   3       2   
        5       0   1   
*/
#if 0
static float VertexAttributes[] = {
    // VBO1                                     // VBO2
    -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,       -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
     0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,        0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
     0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f,        0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
     0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f,        0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
    -0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f,       -0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
    -0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f,       -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
};·
#else

static float VertexAttributes[] = {
    // VBO1                                     // VBO2
    -0.5f, -0.5f, 0.4f, 1.0f, 0.0f, 0.0f, 0.0f,       -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,  0.0f,
     0.5f, -0.5f, 0.4f, 1.0f, 0.0f, 0.0f, 0.0f,        0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
     0.5f,  0.5f, 0.4f, 1.0f, 0.0f, 0.0f, 0.0f,        0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
     0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f,       0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
     0.5f,  0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f,      -0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
    -0.5f,  0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f,      -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
};
#endif


#if USE_RHI_VULKAN
static unsigned int Index[] = {
    5, 4, 3,
    2, 1, 0
};
#else
static unsigned int Index[] = {
    0, 1, 2,
    3, 4, 5
};
#endif

RHIApplicationTriangleIndexed::RHIApplicationTriangleIndexed()
    : RHIApplication()
{

}

void RHIApplicationTriangleIndexed::Init()
{
    /*
        创建VBO
    */
    CreateVBO();
    /*
        创建EBO
    */
    CreateEBO();
    /*
         创建顶点描述
     */
    CreateVertexDescriptioin();
    /*
        创建图形管线
    */
    CreateGraphicsPipeline();
}

void RHIApplicationTriangleIndexed::CreateVBO()
{
    RHIVBO = pRHI->RHICreateBuffer(RHIBufferType::VertexBuffer, RHIBufferUsageFlag::VertexBuffer, sizeof(VertexAttributes), VertexAttributes);
}

void RHIApplicationTriangleIndexed::CreateEBO()
{
    RHIEBO = pRHI->RHICreateBuffer(RHIBufferType::IndexBuffer, RHIBufferUsageFlag::IndexBuffer, sizeof(Index), Index);
}


void RHIApplicationTriangleIndexed::CreateSRB()
{
    SRB = pRHI->RHICreateShaderResourceBindings();
    SRB->Create();
}

void RHIApplicationTriangleIndexed::CreateVertexDescriptioin()
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
    VertexInputs.push_back(std::make_pair(RHIVBO, 6 * sizeof(float)));
#endif
}

void RHIApplicationTriangleIndexed::CreateGraphicsPipeline()
{
#if USE_RHI_VULKAN
    auto vertShaderCode = ReadFile("DrawTriangle_vert.spv");
    auto fragShaderCode = ReadFile("DrawTriangle_frag.spv");
    // 创建Shader
    VertexShader= pRHI->RHICreateShader(RHIShaderType::Vertex, (std::uint32_t*)vertShaderCode.data(), vertShaderCode.size());
    FragmengShader = pRHI->RHICreateShader(RHIShaderType::Fragment, (std::uint32_t*)fragShaderCode.data(), fragShaderCode.size());
#else
    auto vertShaderCode = ReadFile2("DrawTriangle_vert.glsl");
    auto fragShaderCode = ReadFile2("DrawTriangle_frag.glsl");
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
        { "",0, 1, RHIVertexInputAttribute::Format::Float4,  3 * sizeof(float), 0 },
        });
    /*
        std::uint32_t stride, RHIVertexInputBinding::Classification cls = PerVertex, std::uint32_t stepRate = 1
    */
    VertexInputLayout.SetBindings({
        { 14 * sizeof(float), RHIVertexInputBinding::Classification::PerVertex, 0 },
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
    GraphicsPipeline->SetFrontFace(RHIFrontFace::CCW);
    GraphicsPipeline->SetTopology(RHITopology::Triangles);
    GraphicsPipeline->SetVertexInputLayout(VertexInputLayout);
    GraphicsPipeline->SetShaderStages({ VertexShader , FragmengShader });
    GraphicsPipeline->Create();
}

void RHIApplicationTriangleIndexed::Draw()
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

    CommandBuffer->RHISetStencilTestEnable(false);

    CommandBuffer->RHISetVertexInput(0, VertexInputs.size(), VertexInputs.data(), RHIEBO, 0, RHIIndexFormat::IndexUInt32);

    CommandBuffer->RHIDrawIndexedPrimitive(6, 1, 0, 0, 0);
}
