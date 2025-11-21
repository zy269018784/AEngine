#include "RHIApplicationModel.h"
#include "Vulkan/Common.h"
#include "Model/Model.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

/*
    VBO1三角形: 红色和黄色
    VBO1三角形: 蓝色和绿色

        4   3       2
        5       0   1
*/
std::vector<float> VBOData = {
    -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
     0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
     0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
     0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f,
    -0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f,
    -0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f,
};

std::vector<unsigned int> EBOData = {
     0, 1, 2,
    3, 4, 5
};

 Model model;

RHIApplicationModel::RHIApplicationModel(GLFWwindow* InWindow)
    : RHIApplication(InWindow)
{

}

void RHIApplicationModel::Init()
{
   
    model.LoadModel("Television_01_4k/Television_01_4k.gltf");


    // view/projection transformations
    glm::mat4 projection = glm::perspective(glm::radians(45.f), (float)800 / (float)600, 0.1f, 100.0f);
    glm::mat4 view      = glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
    model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));

    //glm::mat4 mvp = model * view * projection;

    glm::mat4 mvp = projection * view * model;

    /*
        创建VBO
    */
    CreateVBO();
    CreateEBO();
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

void RHIApplicationModel::CreateVBO()
{
#if 1
    RHIVBO = pRHI->RHICreateBuffer(RHIBuffer::RHIBufferType::VertexBuffer, RHIBuffer::RHIBufferUsageFlag::Static, VBOData.size() * sizeof(float), VBOData.data());
#else
    RHIVBO = pRHI->RHICreateBuffer(RHIBuffer::RHIBufferType::VertexBuffer, RHIBuffer::RHIBufferUsageFlag::Static, model.VBOData.size() * sizeof(float), model.VBOData.data());
#endif
}

void RHIApplicationModel::CreateEBO()
{
#if 1
    RHIEBO = pRHI->RHICreateBuffer(RHIBuffer::RHIBufferType::IndexBuffer, RHIBuffer::RHIBufferUsageFlag::Static, EBOData.size() * sizeof(unsigned int), EBOData.data());
#else
    RHIEBO = pRHI->RHICreateBuffer(RHIBuffer::RHIBufferType::IndexBuffer, RHIBuffer::RHIBufferUsageFlag::Static, model.EBOData.size() * sizeof(unsigned int), model.EBOData.data());
#endif
}


void RHIApplicationModel::CreateSRB()
{
    SRB = pRHI->RHICreateShaderResourceBindings();
    SRB->Create();
}

void RHIApplicationModel::CreateVertexDescriptioin()
{
    VertexInputs.push_back(std::make_pair(RHIVBO, 0 * sizeof(float)));
}

void RHIApplicationModel::CreateGraphicsPipeline()
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
        { 6 * sizeof(float), RHIVertexInputBinding::Classification::PerVertex, 0 },
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

    /*
        vulkan要求删除
    */
    delete VertexShader;
    delete FragmengShader;
}

void RHIApplicationModel::Draw()
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
    CommandBuffer->RHISetVertexInput(0, VertexInputs.size(), VertexInputs.data(), RHIEBO, 0, RHIIndexFormat::IndexUInt32);
    CommandBuffer->RHIDrawIndexedPrimitive(6, 1, 0, 0, 0);
}
