#include "RHIApplicationTextureRenderTarget.h"

#include "RHI/RHIObjects/RenderTarget/RHIRenderTarget.h"
#include "Common.h"
#if  1
#include <stb_image.h>
#endif
#include "RHI/RHIObjects/Core/RHIVertexInputAttribute.h"
#include "RHI/RHIObjects/Pipeline/RHIGraphicsPipeline.h"
#include "RHI/RHIObjects/Shader/RHIShaderResourceBinding.h"
#include "RHI/RHIObjects/Shader/RHIShaderResourceBindings.h"
#include "RHI/RHIObjects/Texture/RHITexture.h"
#include "GLFWWindow/GLFWWindow.h"
static float VertexAttributes2[] = {
    // pos               uv
    -0.5f, -0.5f, 0.0f,  0.0f, 0.0f,
     0.5f, -0.5f, 0.0f,  1.0f, 0.0f,
     0.5f,  0.5f, 0.0f,  1.0f, 1.0f,
    -0.5f,  0.5f, 0.0f,  0.0f, 1.0f,
};

static float VertexAttributes[] = {
    // pos               uv
    -1.0f, -1.0f, 0.0f,  0.0f, 0.0f,
     1.0f, -1.0f, 0.0f,  1.0f, 0.0f,
     1.0f,  1.0f, 0.0f,  1.0f, 1.0f,
    -1.0f,  1.0f, 0.0f,  0.0f, 1.0f,
};

static unsigned int Index[] = {
    0, 1, 2,
    2, 3, 0
};

static unsigned int Index2[] = {
    0, 1, 2,
    2, 3, 0
};

RHIApplicationTextureRenderTarget::RHIApplicationTextureRenderTarget()
{
   // return;
    std::cout << "RHIApplication 1" << std::endl;
    RHIIndex = 0;
    if (0 == RHIIndex)
    {
        Window = CreateGLFWWindow(IWindow::Vulkan);
        Window->SetGeometry(400, 300, 800, 600);

        pRHI = CreateRHI(GraphicsAPI::Vulkan);

    }
    else if (1 == RHIIndex)
    {
#if  PROJECT_USE_D3D12
        pRHI = new D3D12RHI();
#endif
    }
    else if (2 == RHIIndex)
    {
#if  PROJECT_USE_GLFW
        GLFWWindow *tmpWin = new GLFWWindow(IWindow::OpenGL46);
        tmpWin->MakeContextCurrent();

        Window = tmpWin;
#endif
        /*
            opengl需要
        */
       // glfwMakeContextCurrent(InWindow);
        //pRHI = new ES32RHI();
    }
    std::cout << "pRHI " << pRHI  << std::endl;
    pRHI->RHIUseGPU(0);



#if  PROJECT_USE_XCB1
    //Display* Display = glfwGetX11Display();
    //xcb_connection_t* connection = XGetXCBConnection(Display);
    //xcb_window_t xcb_window = glfwGetX11Window(InWindow);


    xcb_window_t xcb_window =  Window->GetXCBWindow();
    xcb_connection_t* connection = Window->GetXCBConnection();
    if (!connection || xcb_window == XCB_NONE) {
        std::cerr << "Failed to get XCB connection/window" << std::endl;
        return;
    }
    RHIWindow_ = pRHI->RHICreateWindow(connection, xcb_window);
    Surface = pRHI->RHICreateSurface(connection, xcb_window);
    std::cout << "glfwGetX11Window" << std::endl;
#endif

#if  PROJECT_USE_Xlib
    Display *Disp = Window->GetXlibDisplay();
    ::Window Win = Window->GetXlibWindow();
    RHIWindow_ = pRHI->RHICreateWindow(Disp, Win);
    Surface = pRHI->RHICreateSurface(Disp, Win);
#endif


#if OS_IS_WINDOWS
    std::cout << "RHIApplication 1" << std::endl;
    HWND hwnd;HINSTANCE instacne;
//#if  PROJECT_USE_GLFW
    auto GLFWHandle = ((GLFWWindow *)Window)->GetHandle();

    hwnd = glfwGetWin32Window(GLFWHandle);

	instacne = (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE);
//#endif
    std::cout << "RHIApplication 2" << std::endl;
#if USE_RHIWindow
    RHIWindow_ = pRHI->RHICreateWindow(instacne, hwnd);
  //  this->RenderTarget = (RHIRenderTarget *)(((VulkanWindow *)RHIWindow_)->RenderTarget);
    this->RenderTarget = pRHI->RHICreateSwapchainRenderTarget(((VulkanWindow *)RHIWindow_)->Surface);
    ((VulkanWindow *)RHIWindow_)->RenderTarget = (VulkanSwapChainRenderTarget *)(this->RenderTarget);
#else
    Surface = pRHI->RHICreateSurface(instacne, hwnd);
    this->RenderTarget = pRHI->RHICreateSwapchainRenderTarget(Surface);

#endif
    std::cout << "RHIApplication 3" << std::endl;
#endif
    std::cout << "RHIApplication End" << std::endl;
}

RHIApplicationTextureRenderTarget::~RHIApplicationTextureRenderTarget()
{
    delete RHIVBO;
    delete RHIEBO;
    delete RHITexture2D;
    delete VertexShader;
    delete FragmengShader;
    delete GraphicsPipeline;
    delete SRB;
    delete RHISampler_;
}   

void RHIApplicationTextureRenderTarget::Run()
{
    std::cout << "Run 1" << std::endl;
    Init();
    std::cout << "Run 2" << std::endl;
#if 1
    auto glfwWin = ((GLFWWindow *)Window)->GetHandle();
    while (!glfwWindowShouldClose(glfwWin))
    {
        std::cout << "loop " << std::endl;
#if USE_RHIWindow
        RHIWindow_->RHIBeginFrame();
        RHIWindow_->RHIBeginRenderPass();
        Draw();
        RHIWindow_->RHIEndRenderPass();
        RHIWindow_->RHIEndFrame();
#else
#if 1
        std::cout << "test 1 " << std::endl;
        RHITextureRT->TransitionTo(RHIImageLayout::RHI_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL);
        std::cout << "test 2 " << std::endl;
        TextureRenderTarget->RHIBeginFrame();
        TextureRenderTarget->RHIBeginRenderPass();
        Draw2();
        TextureRenderTarget->RHIEndRenderPass();
        TextureRenderTarget->RHIEndFrame();
#endif
#if 1
        RHITextureRT->TransitionTo(RHIImageLayout::RHI_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);
        RenderTarget->RHIBeginFrame();
        RenderTarget->RHIBeginRenderPass();
        Draw();
        RenderTarget->RHIEndRenderPass();
        RenderTarget->RHIEndFrame();

#endif
#endif
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(glfwWin);
        glfwPollEvents();
    }
     RenderTarget->WaitDeviceIdle();

#else
    while (!glfwWindowShouldClose(Window))
    {
        glfwPollEvents();
        //Render();

        RHIWindow_->RHIBeginFrame();
        RHIWindow_->RHIBeginRenderPass();
        Draw();
        RHIWindow_->RHIEndRenderPass();
        RHIWindow_->RHIEndFrame();

    }
    RHIWindow_->WaitDeviceIdle();
#endif
}

void RHIApplicationTextureRenderTarget::Resize(int w, int h)
{
    Window->Resize(w, h);
    //glfwSetWindowSize(Window, w, h);
}

void RHIApplicationTextureRenderTarget::Init()
{
	std::cout << "Init start" << std::endl;
    CreateVBO();
    CreateEBO();
    std::cout << "CreateTexture start" << std::endl;
    CreateTexture();
    std::cout << "CreateTextureRT start" << std::endl;
	CreateTextureRT();
    std::cout << "CreateSRB start" << std::endl;
    CreateSRB();
    std::cout << "CreateVertexDescriptioin start" << std::endl;
    CreateVertexDescriptioin();
	std::cout << "hello 2" << std::endl;
    CreateGraphicsPipeline();
    std::cout << "CreateGraphicsPipeline ok" << std::endl;
	CreateGraphicsPipeline2();
	std::cout << "CreateGraphicsPipeline2 ok" << std::endl;
    std::cout << "Init end" << std::endl;
}

void RHIApplicationTextureRenderTarget::CreateVBO()
{
    RHIVBO = pRHI->RHICreateBuffer(RHIBufferType::VertexBuffer, RHIBufferUsageFlag::VertexBuffer, sizeof(VertexAttributes), VertexAttributes);
    RHIVBO2 = pRHI->RHICreateBuffer(RHIBufferType::VertexBuffer, RHIBufferUsageFlag::VertexBuffer, sizeof(VertexAttributes2), VertexAttributes2);
}

void RHIApplicationTextureRenderTarget::CreateEBO()
{
    RHIEBO = pRHI->RHICreateBuffer(RHIBufferType::IndexBuffer, RHIBufferUsageFlag::IndexBuffer, sizeof(Index), Index);
}

void RHIApplicationTextureRenderTarget::CreateTexture()
{
    RHISampler_ = pRHI->RHICreateSampler(RHIFilter::NEAREST, RHIFilter::NEAREST);

    int texWidth, texHeight, texChannels;
#if  1
    /*
        STBI_rgb_alpha统一转成4通道
    */
    //stbi_uc* pixels = stbi_load("textures/texture.png", &texWidth, &texHeight, &texChannels, STBI_rgb_alpha);
    stbi_uc* pixels = stbi_load("textures/asuka.jpg", &texWidth, &texHeight, &texChannels, STBI_rgb_alpha);
    size_t imageSize = texWidth * texHeight * 4;

    if (!pixels) {
        throw std::runtime_error("failed to load texture image!");
    }

    RHITexture2D = pRHI->RHICreateTexture2D(RHIPixelFormat::PF_R8G8B8A8_UNORM,
        RHITextureUsageFlag::ColorAttachment,
        RHIImageLayout::RHI_IMAGE_LAYOUT_ATTACHMENT_OPTIMAL,
        1,
        texWidth,
        texHeight,
        pixels);
    std::cout
        << "RHITexture2D " << RHITexture2D << " "
        << "texWidth "   << texWidth   << " "
        << "texHeight  " << texHeight  << " "
        << "texChannels  " << texChannels << " "
        << "pixels  " << (unsigned int)pixels[(texHeight * texWidth / 2 + texWidth / 2) * 4] << " "
        << std::endl;
   // RHITexture2D->Update(0, 0, 0, 0, texWidth, texHeight, 1, pixels);
#endif
}
void RHIApplicationTextureRenderTarget::CreateTextureRT()
{
	RHISamplerRT = pRHI->RHICreateSampler(RHIFilter::NEAREST, RHIFilter::NEAREST);
    RHITextureRT = pRHI->RHICreateTexture2D(RHIPixelFormat::PF_R8G8B8A8_UNORM,
        RHITextureUsageFlag::SampledTexture,
        RHIImageLayout::RHI_IMAGE_LAYOUT_UNDEFINED, 1, 800, 600, nullptr);
    RHITexture * DepthTextureRT = pRHI->RHICreateTexture2D(RHIPixelFormat::PF_DepthStencil_D24_S8,
        RHITextureUsageFlag::DepthStencilAttachment,
        RHIImageLayout::RHI_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL, 1, 800, 600, nullptr);

    std::vector<RHITexture *> ColorAttachments;
    ColorAttachments.push_back(RHITextureRT);
    std::vector<RHITexture *> DepthAttachments;
    DepthAttachments.push_back(DepthTextureRT);
    TextureRenderTarget = pRHI->RHICreateTextureRenderTarget(ColorAttachments, DepthAttachments);
}


void RHIApplicationTextureRenderTarget::CreateSRB()
{
    SRB = pRHI->RHICreateShaderResourceBindings();
    SRB->SetBindings({
            RHIShaderResourceBinding::SampledTexture(0, RHIShaderType::Fragment, RHITextureRT, RHISamplerRT)
    });
    std::cout << "SRB 1-1" << std::endl;
    SRB->Create();
    std::cout << "SRB 1-2" << std::endl;

    SRB2 = pRHI->RHICreateShaderResourceBindings();
    SRB2->SetBindings({
            RHIShaderResourceBinding::SampledTexture(0, RHIShaderType::Fragment, RHITexture2D, RHISampler_)
    });
    std::cout << "SRB 2-1" << std::endl;
    SRB2->Create();
    std::cout << "SRB 2-2" << std::endl;
}

void RHIApplicationTextureRenderTarget::CreateVertexDescriptioin()
{
    VertexInputs.push_back(std::make_pair(RHIVBO, 0 * sizeof(float)));
    VertexInputs2.push_back(std::make_pair(RHIVBO2, 0 * sizeof(float)));
}

void RHIApplicationTextureRenderTarget::CreateGraphicsPipeline()
{
#if 1
    auto vertShaderCode = ReadFile("Texture2D_vert.spv");
    auto fragShaderCode = ReadFile("Texture2D_frag.spv");
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
        { "",0, 0, RHIVertexInputAttribute::Format::Float3,  0 * sizeof(float), 0 },
        { "",0, 1, RHIVertexInputAttribute::Format::Float2,  3 * sizeof(float), 0 },
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
    GraphicsPipeline = pRHI->RHICreateGraphicsPipeline(RenderTarget->GetRenderPass());
    GraphicsPipeline->SetShaderResourceBindings(SRB);
    GraphicsPipeline->SetPolygonMode(RHIPolygonMode::Fill);
    GraphicsPipeline->SetCullMode(RHICullMode::CullModeNone);
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

void RHIApplicationTextureRenderTarget::CreateGraphicsPipeline2()
{
#if 1
    auto vertShaderCode = ReadFile("Texture2D_vert.spv");
    auto fragShaderCode = ReadFile("Texture2D_frag.spv");
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
        { "",0, 0, RHIVertexInputAttribute::Format::Float3,  0 * sizeof(float), 0 },
        { "",0, 1, RHIVertexInputAttribute::Format::Float2,  3 * sizeof(float), 0 },
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
    std::cout << "GraphicsPipeline2 TextureRenderTarget " << TextureRenderTarget << std::endl;
    GraphicsPipeline2 = pRHI->RHICreateGraphicsPipeline(TextureRenderTarget->GetRenderPass());
    GraphicsPipeline2->SetShaderResourceBindings(SRB2);
    GraphicsPipeline2->SetPolygonMode(RHIPolygonMode::Fill);
    GraphicsPipeline2->SetCullMode(RHICullMode::CullModeNone);
#if USE_RHI_VULKAN
    GraphicsPipeline2->SetFrontFace(RHIFrontFace::CW);
#else
    GraphicsPipeline2->SetFrontFace(RHIFrontFace::CCW);
#endif
    GraphicsPipeline2->SetTopology(RHITopology::Triangles);
    GraphicsPipeline2->SetVertexInputLayout(VertexInputLayout);
    GraphicsPipeline2->SetShaderStages({ VertexShader , FragmengShader });
    std::cout << "GraphicsPipeline2->Create start" << std::endl;
    GraphicsPipeline2->Create();
    std::cout << "GraphicsPipeline2->Create end" << std::endl;
    delete VertexShader;
    delete FragmengShader;
}

void RHIApplicationTextureRenderTarget::Draw2()
{
 	float x = 0;
    float y = 0;
    float w = 0;
    float h = 0;

#if USE_RHIWindow
    auto CommandBuffer = RHIWindow_->CurrentGraphicsCommandBuffer();
    RHIWindow_->GetExtent(x, y, w, h);
#else
    auto CommandBuffer = TextureRenderTarget->CurrentGraphicsCommandBuffer();
    TextureRenderTarget->GetExtent(x, y, w, h);
#endif

    RHIViewport Viewport(0, 0, w, h);
    CommandBuffer->RHISetViewport(Viewport);

    RHIScissor Scissor(0, 0, w, h);
    CommandBuffer->RHISetScissor(Scissor);

    CommandBuffer->RHISetGraphicsPipeline(GraphicsPipeline2);

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

    CommandBuffer->RHISetVertexInput(0, VertexInputs2.size(), VertexInputs2.data(), RHIEBO, 0, RHIIndexFormat::IndexUInt32);
    CommandBuffer->RHIDrawIndexedPrimitive(6, 1, 0, 0, 0);
}

void RHIApplicationTextureRenderTarget::Draw()
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
