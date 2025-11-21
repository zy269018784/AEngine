#include "RHIApplicationDepthTest.h"
#include "Vulkan/Common.h"

/*
    VBO1三角形: 红色和黄色
    VBO1三角形: 蓝色和绿色

        4   3       2   
        5       0   1   
*/
static float VertexAttributes[] = {
    // VBO1                                     // VBO2
    -0.5f, -0.5f, 0.4f, 1.0f, 0.0f, 0.0f,       -0.5f, -0.5f, 0.4f, 0.0f, 1.0f, 0.0f,
     0.5f, -0.5f, 0.4f, 1.0f, 0.0f, 0.0f,        0.5f, -0.5f, 0.4f, 0.0f, 1.0f, 0.0f,
    -0.5f,  0.5f, 0.4f, 1.0f, 0.0f, 0.0f,       -0.5f,  0.5f, 0.4f, 0.0f, 1.0f, 0.0f,

    -0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 0.0f,       -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
     0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 0.0f,        0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
     0.5f,  0.5f, 0.5f, 1.0f, 1.0f, 0.0f,        0.5f,  0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
};
#if USE_RHI_VULKAN
static unsigned int Index[] = { 
    2, 1, 0,
    5, 4, 3
};
#else
static unsigned int Index[] = {
    0, 1, 2,
    3, 4, 5
};
#endif

RHIApplicationDepthTest::RHIApplicationDepthTest(GLFWwindow* InWindow)
    : RHIApplication(InWindow)
{

}

void RHIApplicationDepthTest::Init()
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

void RHIApplicationDepthTest::CreateVBO()
{
    RHIVBO = pRHI->RHICreateBuffer(RHIBuffer::RHIBufferType::VertexBuffer, RHIBuffer::RHIBufferUsageFlag::Static, sizeof(VertexAttributes), VertexAttributes);
}

void RHIApplicationDepthTest::CreateEBO()
{
    RHIEBO = pRHI->RHICreateBuffer(RHIBuffer::RHIBufferType::IndexBuffer, RHIBuffer::RHIBufferUsageFlag::Static, sizeof(Index), Index);
}


void RHIApplicationDepthTest::CreateSRB()
{
    SRB = pRHI->RHICreateShaderResourceBindings();
    SRB->Create();
}

void RHIApplicationDepthTest::CreateVertexDescriptioin()
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

void RHIApplicationDepthTest::CreateGraphicsPipeline()
{
#if USE_RHI_VULKAN
    auto vertShaderCode = ReadFile("DrawTriangle_vert.spv");
    auto fragShaderCode = ReadFile("DrawTriangle_frag.spv");
    // 创建Shader
    VertexShader= pRHI->RHICreateShader(RHIShaderType::Vertex, (std::uint32_t*)vertShaderCode.data(), vertShaderCode.size());
    FragmengShader = pRHI->RHICreateShader(RHIShaderType::Fragment, (std::uint32_t*)fragShaderCode.data(), fragShaderCode.size());
#else
    auto vertShaderCode = ReadFile2("DrawTriangle.vert");
    auto fragShaderCode = ReadFile2("DrawTriangle.frag");
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
    GraphicsPipeline->SetCullMode(RHICullMode::Back);
    GraphicsPipeline->SetFrontFace(RHIFrontFace::CCW);
    GraphicsPipeline->SetTopology(RHITopology::Triangles);
    GraphicsPipeline->SetVertexInputLayout(VertexInputLayout);
    GraphicsPipeline->SetShaderStages({ VertexShader , FragmengShader });
    GraphicsPipeline->Create();
}

void RHIApplicationDepthTest::Draw()
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
    

    CommandBuffer->RHISetDepthTestEnable(true);

    CommandBuffer->RHISetDepthWriteEnable(true);

    CommandBuffer->RHISetDepthCompareOp(RHICompareOp::Less);


    //// 清除深度附件
    //VkClearAttachment clearAttachment = {};
    //clearAttachment.aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT;
    //clearAttachment.clearValue.depthStencil.depth = 1.0f;  // 通常清除为 1.0（远平面）

    //VkClearRect clearRect = {};
    //clearRect.rect.offset = { 0, 0 };
    //clearRect.rect.extent = { (unsigned int)w, (unsigned int)h };
    //clearRect.baseArrayLayer = 0;
    //clearRect.layerCount = 1;

    //vkCmdClearAttachments(
    //    ((VulkanCommandBuffer *)CommandBuffer)->GetHandle(),
    //    1, &clearAttachment,
    //    1, &clearRect
    //);

    CommandBuffer->RHISetStencilTestEnable(false);

    CommandBuffer->RHISetGraphicsPipeline(GraphicsPipeline);

    CommandBuffer->RHISetVertexInput(0, VertexInputs.size(), VertexInputs.data(), RHIEBO, 0, RHIIndexFormat::IndexUInt32);

    CommandBuffer->RHIDrawIndexedPrimitive(6, 1, 0, 0, 0);
}
