//#include "RHIApplicationTexture1DArray.h"
//#include "Common.h"
//#include <stb_image.h>
///*
//    VBO1三角形: 红色和黄色
//    VBO1三角形: 蓝色和绿色
//*/
//static float VertexAttributes[] = {
//    // VBO1                                                      // VBO2
//    // pos              color              uv                    // pos              color              uv
//    -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,  0.0f, 0.0f,           -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,  0.0f, 0.0f,
//     0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,  1.0f, 0.0f,            0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,  1.0f, 0.0f,
//     0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f,  1.0f, 1.0f,            0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 0.0f,  1.0f, 1.0f,
//
//     0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f,  1.0f, 1.0f,            0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f,  1.0f, 1.0f,
//    -0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f,  0.0f, 1.0f,           -0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f,  0.0f, 1.0f,
//    -0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f,  0.0f, 0.0f,           -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,  0.0f, 0.0f
//};
//
////static float VertexAttributes[] = {
////    // VBO1                                                    
////    // pos              color              uv                  
////    -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,  0.0f, 0.0f,         
////     0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,  1.0f, 0.0f,         
////     0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f,  1.0f, 1.0f,         
////
////     0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f,  1.0f, 1.0f,         
////    -0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f,  0.0f, 1.0f,         
////    -0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f,  0.0f, 0.0f,         
////};
//
//
//static unsigned int Index[] = {
//    0, 1, 2,
//    3, 4, 5
//};
//
//RHIApplicationTexture1DArray::RHIApplicationTexture1DArray(GLFWwindow* InWindow)
//    : RHIApplication(InWindow)
//{
//
//}
//
//RHIApplicationTexture1DArray::~RHIApplicationTexture1DArray()
//{
//    delete RHIVBO;
//    delete RHIEBO;
//    delete RHITexture2D;
//    delete VertexShader;
//    delete FragmengShader;
//    delete GraphicsPipeline;
//    delete SRB;
//    delete RHISampler1DArray;
//    delete RHISampler2D_;
//}   
//
//void RHIApplicationTexture1DArray::Init()
//{
//    CreateVBO();
//    CreateEBO();
//    CreateTexture();
//    std::cout << "CreateSRB " << std::endl;
//    CreateSRB();
//    std::cout << "CreateVertexDescriptioin " << std::endl;
//    CreateVertexDescriptioin();
//    std::cout << "CreateGraphicsPipeline " << std::endl;
//    CreateGraphicsPipeline();
//    std::cout << "CreateGraphicsPipeline end" << std::endl;
//}
//
//void RHIApplicationTexture1DArray::CreateVBO()
//{
//    RHIVBO = pRHI->RHICreateBuffer(RHIBuffer::RHIBufferType::VertexBuffer, RHIBuffer::RHIBufferUsageFlag::Static, sizeof(VertexAttributes), VertexAttributes);
//}
//
//void RHIApplicationTexture1DArray::CreateEBO()
//{
//    RHIEBO = pRHI->RHICreateBuffer(RHIBuffer::RHIBufferType::IndexBuffer, RHIBuffer::RHIBufferUsageFlag::Static, sizeof(Index), Index);
//}
//
//void RHIApplicationTexture1DArray::CreateTexture()
//{
//    RHISampler2D_ = pRHI->RHICreateSampler(RHIFilter::NEAREST, RHIFilter::NEAREST);
//    RHISampler1DArray = pRHI->RHICreateSampler(RHIFilter::NEAREST, RHIFilter::NEAREST);
//    int texWidth, texHeight, texChannels;
//    /*
//        STBI_rgb_alpha统一转成4通道
//    */
//    stbi_uc* pixels = stbi_load("textures/texture.png", &texWidth, &texHeight, &texChannels, STBI_rgb_alpha);
//    VkDeviceSize imageSize = texWidth * texHeight * 4;
//    std::cout 
//        << "texWidth "   << texWidth   << " "
//        << "texHeight  " << texHeight  << " "
//        << "texChannels  " << texChannels << " "
//        << std::endl;
//    if (!pixels) {
//        throw std::runtime_error("failed to load texture image!");
//    }
//
//    RHITexture2D = pRHI->RHICreateTexture2D(RHIPixelFormat::PF_R8G8B8A8_SRGB, 1, texWidth, texHeight);
//
//    pRHI->RHIUpdateTexture(RHITexture2D, pixels, imageSize);
//
//    /*
//        1D Texture Array:
//            3 Layers
//            1 Layers  = 1个1D纹理
//            1个1D纹理 = 3个像素
//            1个像素   = 4个uint8即4个字节
//    */
//    unsigned char RGBA[]= {
//        // 像素1                        // 像素2              // 像素3
//        255,      0,      0,     0,     0,   0,  0,  0,       0,   255,       0,     0,
//          0,    255,      0,     0,     0,   0,  0,  0,       0,     0,     255,     0,
//          0,      0,    255,     0,     0,   0,  0,  0,     255,     0,       0,     0,
//    };
//    /*
//        NumMips大于1报错:
//            Validation Error: [ VUID-vkCmdDraw-None-09600 ] | MessageID = 0x46582f7b
//            vkQueueSubmit(): pSubmits[0].pCommandBuffers[0] command buffer VkCommandBuffer 0x21a03f80c50 expects VkImage 0x270000000027 (subresource: aspectMask = VK_IMAGE_ASPECT_COLOR_BIT, mipLevel = 1, arrayLayer = 0) to be in layout VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL--instead, current layout is VK_IMAGE_LAYOUT_UNDEFINED.
//            The Vulkan spec states: If a descriptor with type equal to any of VK_DESCRIPTOR_TYPE_SAMPLE_WEIGHT_IMAGE_QCOM, VK_DESCRIPTOR_TYPE_BLOCK_MATCH_IMAGE_QCOM, VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE, VK_DESCRIPTOR_TYPE_STORAGE_IMAGE, or VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT is accessed as a result of this command, all image subresources identified by that descriptor must be in the image layout identified when the descriptor was written (https://vulkan.lunarg.com/doc/view/1.4.313.2/windows/antora/spec/latest/chapters/drawing.html#VUID-vkCmdDraw-None-09600)
//    */
//    std::uint32_t NumMips = 1;       
//    std::uint32_t SizeX = 3;
//    std::uint32_t ArraySize = 3;
//    std::uint32_t PixelSize = 4; // PF_R8G8B8A8_UBYTE 是4个字节
//    std::uint32_t TotalSize = NumMips * SizeX * ArraySize * PixelSize;
//    RHITexture1DArray = pRHI->RHICreateTexture1DArray(RHIPixelFormat::PF_R8G8B8A8_UINT, NumMips, SizeX, ArraySize);
//
//    pRHI->RHIUpdateTexture(RHITexture1DArray, RGBA, TotalSize);
//}
//
//
//void RHIApplicationTexture1DArray::CreateSRB()
//{
//    SRB = pRHI->RHICreateShaderResourceBindings();
//    SRB->SetBindings({
//            RHIShaderResourceBinding::SampledTexture(0, RHIShaderResourceBinding::StageFlags::FragmentStage, RHITexture1DArray, RHISampler1DArray),
//            RHIShaderResourceBinding::SampledTexture(1, RHIShaderResourceBinding::StageFlags::FragmentStage, RHITexture2D, RHISampler2D_)       
//    });
//    SRB->Create();
//}
//
//void RHIApplicationTexture1DArray::CreateVertexDescriptioin()
//{
//#if 1
//    /*
//        使用VBO1
//    */
//    VertexInputs.push_back(std::make_pair(RHIVBO, 0 * sizeof(float)));
//#else
//    /*
//        使用VBO2
//    */
//    VertexInputs.push_back(std::make_pair(RHIVBO, 8 * sizeof(float)));
//#endif
//}
//
//void RHIApplicationTexture1DArray::CreateGraphicsPipeline()
//{
//    auto vertShaderCode = ReadFile("Texture1DArray_vert.spv");
//    auto fragShaderCode = ReadFile("Texture1DArray_frag.spv");
//
//    // 创建Shader
//    VertexShader = pRHI->RHICreateShader(RHIShaderType::Vertex, (std::uint32_t*)vertShaderCode.data(), vertShaderCode.size());
//    FragmengShader = pRHI->RHICreateShader(RHIShaderType::Fragment, (std::uint32_t*)fragShaderCode.data(), fragShaderCode.size());
//
//    RHIVertexInputLayout VertexInputLayout;
//    /*
//        int binding, int location, RHIVertexInputAttribute::Format format, std::uint32_t offset, int matrixSlice = -1
//    */
//    VertexInputLayout.SetAttributes({
//        { 0, 0, RHIVertexInputAttribute::Format::Float3,  0 * sizeof(float), 0 },
//        { 0, 1, RHIVertexInputAttribute::Format::Float3,  3 * sizeof(float), 0 },
//        { 0, 2, RHIVertexInputAttribute::Format::Float2,  6 * sizeof(float), 0 }
//    });
//    /*
//        std::uint32_t stride, RHIVertexInputBinding::Classification cls = PerVertex, std::uint32_t stepRate = 1
//    */
//    VertexInputLayout.SetBindings({
//        { 16 * sizeof(float), RHIVertexInputBinding::Classification::PerVertex, 0 },
//    });
//
//    /*
//        用于创建Descriptor Set Layout和Pipeline Layout
//    */
//    GraphicsPipeline = pRHI->RHICreateGraphicsPipeline(RHIWindow_);
//    GraphicsPipeline->SetShaderResourceBindings(SRB);
//    GraphicsPipeline->SetPolygonMode(RHIPolygonMode::Fill);
//    GraphicsPipeline->SetCullMode(RHICullMode::Front);
//    GraphicsPipeline->SetFrontFace(RHIFrontFace::CCW);
//    GraphicsPipeline->SetTopology(RHITopology::Triangles);
//    GraphicsPipeline->SetVertexInputLayout(VertexInputLayout);
//    GraphicsPipeline->SetShaderStages({ VertexShader , FragmengShader });
//    GraphicsPipeline->Create();
//}
//
//void RHIApplicationTexture1DArray::Draw()
//{
//    auto CommandBuffer = RHIWindow_->CurrentGraphicsCommandBuffer();
//
//    float x = 0;
//    float y = 0;
//    float w = 0;
//    float h = 0;
//    RHIWindow_->GetExtent(x, y, w, h);
//
//    RHIViewport Viewport(0, 0, w, h);
//    CommandBuffer->RHISetViewport(Viewport);
//
//    RHIScissor Scissor(0, 0, w, h);
//    CommandBuffer->RHISetScissor(Scissor);
//
//    CommandBuffer->RHISetGraphicsPipeline(GraphicsPipeline);
//
//    CommandBuffer->RHISetVertexInput(0, VertexInputs.size(), VertexInputs.data(), RHIEBO, 0, RHIIndexFormat::IndexUInt32);
//    CommandBuffer->RHIDrawIndexedPrimitive(6, 1, 0, 0, 0);
//}
