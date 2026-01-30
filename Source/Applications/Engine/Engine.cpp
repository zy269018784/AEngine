#include "Engine.h"
#include "Window/GLFWWindow.h"
#include "Vulkan/Common.h"
#ifdef PROJECT_USE_STB
    #include <stb_image.h>
#endif
#include "CoordSystem.h"
#include <iostream>

/*
    VBO1三角形: 红色和黄色
    (0, 1)      (1, 1)
    (0, 0)      (1, 0)

    3   2
    0   1
    3   5
    0   4
*/
#if 1
static float VertexAttributes[] = {
    -50.0f, -50.0f,  -100.0f,  0.0f, 0.0f,
     50.0f, -50.0f,  -100.0f,  1.0f, 0.0f,
     50.0f,  50.0f,  -100.0f,  1.0f, 1.0f,
    -50.0f,  50.0f,  -100.0f,  0.0f, 1.0f,
    -50.0f, -50.0f,   -50.0f,  0.0f, 0.0f,
    -50.0f,  50.0f,   -50.0f,  0.0f, 0.0f,
};
static unsigned int Index[] = {
        0, 1, 2,
        2, 3, 0,
        3, 0, 4,
        4, 5, 3
};
#else
static float VertexAttributes[] = {
        // VBO1                                    // VBO2
         // pos               uv                    // pos              uv
#if 1
        -1.0f, -1.0f, 0.0f,  0.0f, 0.0f,
         1.0f, -1.0f, 0.0f,  1.0f, 0.0f,
         1.0f,  1.0f, 0.0f,  1.0f, 1.0f,
         1.0f,  1.0f, 0.0f,  1.0f, 1.0f,
        -1.0f,  1.0f, 0.0f,  0.0f, 1.0f,
        -1.0f, -1.0f, 0.0f,  0.0f, 0.0f,
#else
    -1.0f, -1.0f, 0.0f,  1.0f, 0.0f, 0.0f,
     1.0f, -1.0f, 0.0f,  0.0f, 1.0f, 0.0f,
     1.0f,  1.0f, 0.0f,  0.0f, 0.0f, 1.0f,
     1.0f,  1.0f, 0.0f,  0.0f, 0.0f, 0.0f,
    -1.0f,  1.0f, 0.0f,  1.0f, 1.0f, 0.0f,
    -1.0f, -1.0f, 0.0f,  1.0f, 0.0f, 0.0f,
#endif
};
static unsigned int Index[] = {
        0, 1, 2,
        3, 4, 5
};
#endif


glm::mat4 Projection;
glm::mat4 View;
glm::mat4 Model;
glm::mat4 MVP;
#if 0
glm::vec3 Eye    = glm::vec3(0, 150, 610);
glm::vec3 Target = glm::vec3(0, 150, 609);
#else
glm::vec3 Eye    = glm::vec3(0, 0, 1000);
glm::vec3 Target = glm::vec3(0, 0, -1);
#endif
#if USE_RHI_VULKAN
static glm::vec3 Up= glm::vec3(0.0, -1.0, 0.0);
#else
static glm::vec3 Up= glm::vec3(0.0, 1.0, 0.0);
#endif

RHIBuffer* RHIUBO_ = nullptr;
RHIWindow* RHIWindow2_ = nullptr;
sf::Music *pMusic;

static glm::mat4 VulkanPerspective(float fovY, float aspect, float near1, float far1) {
    float f = 1.0f / tan(fovY / 2.0f);

    return glm::mat4(
        f / aspect, 0.0f,  0.0f,                    0.0f,
        0.0f,       f,    0.0f,                    0.0f,
        0.0f,       0.0f,  far1 / (far1 - near1),      1.0f,
        0.0f,       0.0f, -far1 * near1 / (far1 - near1), 0.0f
    );
}

glm::mat4 OpenGLPerspective(float fovY, float aspect, float near1, float far1) {
    float f = 1.0f / tan(fovY / 2.0f);

    return glm::mat4(
        f / aspect, 0.0f,  0.0f,                              0.0f,
        0.0f,       f,     0.0f,                              0.0f,
        0.0f,       0.0f, -(far1 + near1) / (far1 - near1),      -1.0f,
        0.0f,       0.0f, -2.0f * far1 * near1 / (far1 - near1),  0.0f
    );
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    // Adjust viewport to match new window dimensions
   // glViewport(0, 0, width, height);
    printf("Window resized to %dx%d\n", width, height);
#if USE_RHI_VULKAN
    RHIWindow2_->Resize(width, height);
#else
    glViewport(0, 0, width, height);
#endif
    // You might also want to update projection matrices here
    //printf("Window resized to %dx%d\n", width, height);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    float step = 20.f;
    switch (key)
    {
        case GLFW_KEY_W:
            Eye.z -= step;
            Target.z -= step;
            break;
        case GLFW_KEY_S:
            Eye.z += step;
            Target.z += step;
            break;
        case GLFW_KEY_Q:
            Eye.y -= step;
            Target.y -= step;
            break;
        case GLFW_KEY_E:
            Eye.y += step;
            Target.y += step;
            break;
        case GLFW_KEY_A:
            Eye.x -= step;
            Target.x -= step;
            break;
        case GLFW_KEY_D:
            Eye.x += step;
            Target.x += step;
            break;
        case GLFW_KEY_O:
            pMusic->play();
            break;
        case GLFW_KEY_P:
            pMusic->pause();
            break;
    }
    Model = glm::mat4(1.0);
    Projection = glm::perspective(glm::radians(90.0f), 800.0f / 600.0f, 0.001f, 10000.0f);
#if USE_RHI_VULKAN
    View = VulkanLeftHandedViewMatrix(Eye, Target, Up);
    //Projection = VulkanPerspective(glm::radians(90.0f), 800.0f / 600.0f, 0.001f, 100000.0f);
    Projection = glm::perspectiveLH_NO(glm::radians(90.0f), 800.0f / 600.0f, 0.001f, 10000.0f);
#else
    View = OpenGLLeftHandedViewMatrix(Eye, Target, Up);
#endif

    MVP = Projection * View * Model;

    //MVP = glm::mat4(1.0);
    RHIUBO_->Update(sizeof(MVP), &MVP);

    std::cout << "Eye " << Eye.x << " "<< Eye.y << " "<< Eye.z << " " << std::endl;
    std::cout << "Target " << Target.x << " "<< Target.y << " "<< Target.z << " " << std::endl;
}

Engine::Engine(IWindow* InWindow)
    : Window(InWindow)
{
    std::cout << "Engine start " << std::endl;
    model.LoadModel("periwinkle_plant_1k.gltf");
    std::cout << "Engine start 2" << std::endl;
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
    RHIWindow2_ = RHIWindow_;
    std::cout << "RHIApplication 3" << std::endl;
#endif
    Music = new sf::Music("1.ogg");
    Music->play();
    pMusic = Music;
    AddBox2(VBO, EBO,  glm::vec3(-100, -100, -200), glm::vec3(100, 100, -100));
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
#if 1
    //CommandBuffer->RHIDrawIndexedPrimitive(6, 1, 0, 0, 0);
    CommandBuffer->RHIDrawIndexedPrimitive(EBO.size(), 1, 0, 0, 0);
#else
    CommandBuffer->RHIDrawIndexedPrimitive(model.EBOData.size(), 1, 0, 0, 0);
#endif
}



void Engine::Run()
{
    Init();
    auto glfwWin = ((GLFWWindow *)Window)->GetHandle();
    glfwSetFramebufferSizeCallback(glfwWin, framebuffer_size_callback);
    glfwSetKeyCallback(glfwWin, key_callback);
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
#if 1
    //RHIVBO = pRHI->RHICreateBuffer(RHIBuffer::RHIBufferType::VertexBuffer, RHIBuffer::RHIBufferUsageFlag::Static, sizeof(VertexAttributes), VertexAttributes);
    RHIVBO = pRHI->RHICreateBuffer(RHIBuffer::RHIBufferType::VertexBuffer, RHIBuffer::RHIBufferUsageFlag::Static, VBO.size() * sizeof(glm::vec3), VBO.data());
#else
    RHIVBO = pRHI->RHICreateBuffer(RHIBuffer::RHIBufferType::VertexBuffer, RHIBuffer::RHIBufferUsageFlag::Static, model.VBOData.size() * sizeof(float), model.VBOData.data());
#endif
}

void Engine::CreateEBO()
{
#if 1
    //RHIEBO = pRHI->RHICreateBuffer(RHIBuffer::RHIBufferType::IndexBuffer, RHIBuffer::RHIBufferUsageFlag::Static, sizeof(Index), Index);
    RHIEBO = pRHI->RHICreateBuffer(RHIBuffer::RHIBufferType::IndexBuffer, RHIBuffer::RHIBufferUsageFlag::Static, EBO.size() * sizeof(glm::vec3), EBO.data());
#else
    RHIEBO = pRHI->RHICreateBuffer(RHIBuffer::RHIBufferType::IndexBuffer, RHIBuffer::RHIBufferUsageFlag::Static, model.EBOData.size() * sizeof(unsigned int), model.EBOData.data());
#endif
    std::cout << "model.EBOData.size() " << model.EBOData.size() << std::endl;
}

void Engine::CreateUBO()
{
    glm::vec4 p;
    Model = glm::mat4(1.0);

    Projection = glm::perspective(glm::radians(90.0f), 800.0f / 600.0f, 0.001f, 100000.0f);
#if USE_RHI_VULKAN
    View = VulkanLeftHandedViewMatrix(Eye, Target, Up);
   // Projection = VulkanPerspective(glm::radians(90.0f), 800.0f / 600.0f, 0.001f, 100000.0f);
  //  Projection = OpenGLPerspective(glm::radians(90.0f), 800.0f / 600.0f, 0.001f, 100000.0f);
    Projection = glm::perspectiveLH_NO(glm::radians(90.0f), 800.0f / 600.0f, 0.001f, 100000.0f);
#else
    View = OpenGLLeftHandedViewMatrix(Eye, Target, Up);
#endif

    MVP = Projection * View * Model;

    RHIUBO = pRHI->RHICreateBuffer(RHIBuffer::RHIBufferType::UniformBuffer, RHIBuffer::RHIBufferUsageFlag::Static, sizeof(MVP), &MVP);
    RHIUBO_ = RHIUBO;
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
                             RHIShaderResourceBinding::UniformBuffer(1, RHIShaderResourceBinding::StageFlags::VertexStage, RHIUBO)
                     });
    SRB->Create();
}

void Engine::CreateVertexDescriptioin()
{
    VertexInputs.push_back(std::make_pair(RHIVBO, 0 * sizeof(float)));
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
                                            { "", 0, 0, RHIVertexInputAttribute::Format::Float3,  0 * sizeof(float), 0 },
                                            { "", 0, 1, RHIVertexInputAttribute::Format::Float2,  3 * sizeof(float), 0 },
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
    GraphicsPipeline->SetCullMode(RHICullMode::CullModeNone);
    //GraphicsPipeline->SetCullMode(RHICullMode::Back);

#if USE_RHI_VULKAN
    GraphicsPipeline->SetFrontFace(RHIFrontFace::CW);
#else
    GraphicsPipeline->SetFrontFace(RHIFrontFace::CW);
#endif
    GraphicsPipeline->SetTopology(RHITopology::Triangles);
    GraphicsPipeline->SetVertexInputLayout(VertexInputLayout);
    GraphicsPipeline->SetShaderStages({ VertexShader , FragmengShader });
    GraphicsPipeline->Create();
    delete VertexShader;
    delete FragmengShader;
}
