#include "Engine.h"
#include "Window/GLFWWindow.h"
#include "Vulkan/Common.h"
#ifdef PROJECT_USE_STB
    #include <stb_image.h>
#endif

#include <iostream>
/*
    VBO1三角形: 红色和黄色
    VBO1三角形: 蓝色和绿色
*/
#if 1
static float VertexAttributes[] = {
    -50.0f,-50.0f, -50.0f,  0.0f, 0.0f,
    50.0f,-50.0f, -50.0f,  1.0f, 0.0f,
    50.0f,50.0f, -50.0f,  1.0f, 1.0f,
    50.0f,  50.0f, -50.0f,  1.0f, 1.0f,
    -50.0f,  50.0f, -50.0f,  0.0f, 1.0f,
    -50.0f, -50.0f, -50.0f,  0.0f, 0.0f,
};
#else
static float VertexAttributes[] = {
        // VBO1                                    // VBO2
        // pos               uv                    // pos              uv
        -50.0f,-50.0f, 0.0f,  0.0f, 0.0f,
        50.0f,-50.0f, 0.0f,  1.0f, 0.0f,
        50.0f,50.0f, 0.0f,  1.0f, 1.0f,

        50.0f,  50.0f, 0.0f,  1.0f, 1.0f,
        -50.0f,  50.0f, 0.0f,  0.0f, 1.0f,
        -50.0f, -50.0f, 0.0f,  0.0f, 0.0f,
};
#endif
static unsigned int Index[] = {
        0, 1, 2,
        3, 4, 5
};

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    // Adjust viewport to match new window dimensions
    glViewport(0, 0, width, height);

    // You might also want to update projection matrices here
    printf("Window resized to %dx%d\n", width, height);
}

Engine::Engine(IWindow* InWindow)
    : Window(InWindow)
{
#if USE_RHI_VULKAN
    #ifdef PROJECT_USE_VULKAN
    pRHI = new VulkanRHI();

#endif

#else
    /*
        opengl需要
    */
    // glfwMakeContextCurrent(InWindow);
    pRHI = new ES32RHI();
#endif
    pRHI->RHIUseGPU(0);
    std::cout << "debug 1" << std::endl;
#ifdef PROJECT_USE_XCB1
    xcb_window_t xcb_window =  Window->GetXCBWindow();
    xcb_connection_t* connection = Window->GetXCBConnection();
    if (!connection || xcb_window == XCB_NONE) {
        std::cerr << "Failed to get XCB connection/window" << std::endl;
        return;
    }
    RHIWindow_ = pRHI->RHICreateWindow(connection, xcb_window);
    std::cout << "glfwGetX11Window" << std::endl;
#endif
    std::cout << "debug 2" << std::endl;

#ifdef PROJECT_USE_Xlib
    Display *Disp = Window->GetXlibDisplay();
    ::Window Win = Window->GetXlibWindow();
    RHIWindow_ = pRHI->RHICreateWindow(Disp, Win);
#endif
    std::cout << "debug 3" << std::endl;

#ifdef OS_IS_WINDOWS
    std::cout << "RHIApplication 1" << std::endl;
    auto GLFWHandle = ((GLFWWindow *)Window)->GetHandle();

   	HWND hwnd = glfwGetWin32Window(GLFWHandle);

	HINSTANCE instacne = (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE);
    std::cout << "RHIApplication 2" << std::endl;
    RHIWindow_ = pRHI->RHICreateWindow(instacne, hwnd);
    std::cout << "RHIApplication 3" << std::endl;
#endif
}

Engine::~Engine()
{
    delete VertexShader;
    delete FragmengShader;
    delete GeometryShader;
    delete ComputeShader;
    delete RHIVBO;
    delete RHIEBO;
    delete SRB;
    delete GraphicsPipeline;
    delete pRHI;
}

void Engine::Init()
{
    CreateVBO();
    CreateEBO();
    CreateUBO();
    CreateTexture();
    CreateSRB();
    CreateVertexDescriptioin();
    CreateGraphicsPipeline();
}

void Engine::Draw()
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

void Engine::Run()
{
    Init();
    auto glfwWin = ((GLFWWindow *)Window)->GetHandle();
    glfwSetFramebufferSizeCallback(glfwWin, framebuffer_size_callback);
    while (!glfwWindowShouldClose(glfwWin))
    {
        RHIWindow_->RHIBeginFrame();
        RHIWindow_->RHIBeginRenderPass();
        Draw();
        RHIWindow_->RHIEndRenderPass();
        RHIWindow_->RHIEndFrame();
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(glfwWin);
        glfwPollEvents();
    }
    RHIWindow_->WaitDeviceIdle();
}


void Engine::CreateVBO()
{
    RHIVBO = pRHI->RHICreateBuffer(RHIBuffer::RHIBufferType::VertexBuffer, RHIBuffer::RHIBufferUsageFlag::Static, sizeof(VertexAttributes), VertexAttributes);
}

void Engine::CreateEBO()
{
    RHIEBO = pRHI->RHICreateBuffer(RHIBuffer::RHIBufferType::IndexBuffer, RHIBuffer::RHIBufferUsageFlag::Static, sizeof(Index), Index);
}

void Engine::CreateUBO()
{
    glm::vec4 p;
    Model = glm::mat4(1.0);
    View = glm::lookAt(glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 0.0, -100.0), glm::vec3(0.0, 1.0, 0.0));

    p = View * glm::vec4(0, 0, 1000, 0.0);
    std::cout << "p " << p.x << " "<< p.y << " "<< p.z << " "<< p.w << " " << std::endl;

    p = View * glm::vec4(0, 0, 1000, 1.0);
    std::cout << "p " << p.x << " "<< p.y << " "<< p.z << " "<< p.w << " " << std::endl;

    Projection = glm::perspective(glm::radians(90.0f), 800.0f / 600.0f, 0.001f, 1000.0f);
    MVP = Projection * View * Model;
    p = MVP * glm::vec4(0, 0, 1000, 0.0);
    std::cout << "p " << p.x << " "<< p.y << " "<< p.z << " "<< p.w << " " << std::endl;

    p = MVP * glm::vec4(0, 0, 1000, 1.0);
    std::cout << "p " << p.x << " "<< p.y << " "<< p.z << " "<< p.w << " " << std::endl;
    //MVP = glm::mat4(1.0);
    //MVP = glm::mat4(1.0, 0.0, 0.0, 0.0,
    //                0.0, 1.0, 0.0, 0.0,
    //                0.0, 0.0, 1.0, 0.0,
    //                0.0, 0.0, 0.0, 1.0);
    RHIUBO = pRHI->RHICreateBuffer(RHIBuffer::RHIBufferType::UniformBuffer, RHIBuffer::RHIBufferUsageFlag::Static, sizeof(MVP), &MVP);
}


void Engine::CreateTexture()
{
    RHISampler_ = pRHI->RHICreateSampler(RHIFilter::NEAREST, RHIFilter::NEAREST);

    int texWidth, texHeight, texChannels;
#ifdef PROJECT_USE_STB
    /*
        STBI_rgb_alpha统一转成4通道
    */
    //stbi_uc* pixels = stbi_load("textures/texture.png", &texWidth, &texHeight, &texChannels, STBI_rgb_alpha);
    stbi_uc* pixels = stbi_load("textures/1.jpg", &texWidth, &texHeight, &texChannels, STBI_rgb_alpha);
    VkDeviceSize imageSize = texWidth * texHeight * 4;
    std::cout
            << "texWidth "   << texWidth   << " "
            << "texHeight  " << texHeight  << " "
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


void Engine::CreateSRB()
{
    SRB = pRHI->RHICreateShaderResourceBindings();
    SRB->SetBindings({
                             RHIShaderResourceBinding::SampledTexture(0, RHIShaderResourceBinding::StageFlags::FragmentStage, RHITexture2D, RHISampler_),
                             RHIShaderResourceBinding::UniformBuffer(0, RHIShaderResourceBinding::StageFlags::VertexStage, RHIUBO)
                     });
    SRB->Create();
}

void Engine::CreateVertexDescriptioin()
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

void Engine::CreateGraphicsPipeline()
{
#if 1
    auto vertShaderCode = ReadFile("Engine_vert.spv");
    auto fragShaderCode = ReadFile("Engine_frag.spv");
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
    delete VertexShader;
    delete FragmengShader;
}
