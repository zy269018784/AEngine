#include "RHIApplication2.h"
#include "glad/glad.h"
#include "RHI/RHIObjects/RenderTarget/RHIRenderTarget.h"
#if defined(_WIN32) || defined(__CYGWIN__)
#else
    #include <dlfcn.h>
#endif
#include <RHIApplication.h>

#include "RHI/RHIObjects/Pipeline/RHIGraphicsPipeline.h"
#include "RHI/RHIObjects/Resource/RHIBuffer.h"
#include "RHI/RHIObjects/Shader/RHIShader.h"
#include "RHI/RHIObjects/Shader/RHIShaderResourceBindings.h"
#include "RHI/RHIObjects/Surface/RHISurface.h"

#if  PROJECT_USE_XCB
#include <xcb/xcb.h>
#include <X11/Xlib-xcb.h>
#endif

#include "GLFWWindow/GLFWWindow.h"

#include <stb_image.h>

#include "Common.h"
/*
    VBO1三角形: 红色和黄色
    VBO1三角形: 蓝色和绿色
*/
static float VertexAttributes[] = {
    -0.5f, -0.5f, 0.0f,  0.0f, 0.0f,
     0.5f, -0.5f, 0.0f,  1.0f, 0.0f,
     0.5f,  0.5f, 0.0f,  1.0f, 1.0f,
    -0.5f,  0.5f, 0.0f,  0.0f, 1.0f,
 };

static float VertexAttributes2[] = {
    -1.0f, -1.0f, 0.0f,  0.0f, 0.0f,
     1.0f, -1.0f, 0.0f,  1.0f, 0.0f,
     1.0f,  1.0f, 0.0f,  1.0f, 1.0f,
    -1.0f,  1.0f, 0.0f,  0.0f, 1.0f,
};


static unsigned int Index[] = {
    0, 1, 2,
    2, 3, 0
};


RHIApplication2::RHIApplication2()
{
    RHIIndex = 0;
    if (0 == RHIIndex)
    {
        Window = CreateGLFWWindow(IWindow::Vulkan);
        //glfwSetWindowCloseCallback(((GLFWWindow *)Window)->GetHandle(), window_close_callback);

        pRHI = CreateRHI(GraphicsAPI::Vulkan);
    }
    else if (1 == RHIIndex)
    {
        pRHI = CreateRHI(GraphicsAPI::D3D12);
    }
    else if (2 == RHIIndex)
    {
#if 1
        GLFWWindow *tmpWin = new GLFWWindow(IWindow::OpenGL46);
        tmpWin->MakeContextCurrent();
        pRHI = CreateRHI(GraphicsAPI::OpenGL46);
#else
        GLFWWindow *tmpWin = new GLFWWindow(IWindow::ES20);
        tmpWin->MakeContextCurrent();

        if (!gladLoadGLES2Loader((GLADloadproc)glfwGetProcAddress)) {
            printf("Failed to load GLES2\n");
            return ;
        }

        pRHI = CreateRHI(GraphicsAPI::ES20);
#endif

        Window = tmpWin;
    }
    pRHI->RHIUseGPU(0);

#if OS_IS_LINUX
    int backend = 1;
    switch (backend)
    {
        case 0:
            Surface = pRHI->RHICreateSurface(Window->GetXCBConnection(), Window->GetXCBWindow());
            break;
        case 1:
            Surface = pRHI->RHICreateSurface(Window->GetXlibDisplay(), Window->GetXlibWindow());
            break;
        case 2:
            Surface = pRHI->RHICreateSurface( Window->GetWLDisplay(),  Window->GetWLSurface());
            break;
        default:
            break;
    }
#elif OS_IS_WINDOWS
    auto GLFWHandle = (dynamic_cast<GLFWWindow *>(Window))->GetHandle();

    HWND hwnd = glfwGetWin32Window(GLFWHandle);
    HINSTANCE instacne = (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE);

    Surface = pRHI->RHICreateSurface(instacne, hwnd);
#endif

    /*
     * 创建交换链
     */
    this->RenderTarget = pRHI->RHICreateSwapchainRenderTarget(Surface);
}

RHIApplication2::~RHIApplication2()
{

}

void RHIApplication2::Run()
{
    Init();

    auto glfwWin = ((GLFWWindow *)Window)->GetHandle();
    while (!glfwWindowShouldClose(glfwWin))
    {
        if (TextureRenderTarget) {


            RHIColorAttachments[0]->TransitionTo(RHIImageLayout::RHI_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL);
          //  RHIColorAttachments[1]->TransitionTo(RHIImageLayout::RHI_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL);
          //  RHIColorAttachments[2]->TransitionTo(RHIImageLayout::RHI_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL);

            TextureRenderTarget->RHIBeginFrame();

            TextureRenderTarget->RHIBeginRenderPass();
            Draw2();
            TextureRenderTarget->RHIEndRenderPass();
            TextureRenderTarget->RHIEndFrame();
        }

        RHIColorAttachments[0]->TransitionTo(RHIImageLayout::RHI_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);
       // RHIColorAttachments[1]->TransitionTo(RHIImageLayout::RHI_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);
      //  RHIColorAttachments[2]->TransitionTo(RHIImageLayout::RHI_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);

        RenderTarget->RHIBeginFrame();


        RenderTarget->RHIBeginRenderPass();
        Draw();
        RenderTarget->RHIEndRenderPass();
        RenderTarget->RHIEndFrame();


        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        if (2 == RHIIndex)
            glfwSwapBuffers(glfwWin);
        glfwPollEvents();


    }


    RenderTarget->WaitDeviceIdle();

    std::cout << "RHIApplication::Run end" << std::endl;
}

void RHIApplication2::Resize(int w, int h)
{

}

void RHIApplication2::Init()
{
    CreateVBO();
    CreateEBO();
    CreateTexture();
    CreateSRB();
    CreateVertexDescriptioin();
    std::cout << "CreateGraphicsPipeline" << std::endl;
    CreateGraphicsPipeline();
    std::cout << "CreateGraphicsPipeline2" << std::endl;
    CreateGraphicsPipeline2();
    std::cout << "Init OK" << std::endl;
}



void RHIApplication2::CreateVBO()
{
    RHIVBOs.push_back(pRHI->RHICreateBuffer(RHIBufferType::VertexBuffer, RHIBufferUsageFlag::VertexBuffer,
    sizeof(VertexAttributes), VertexAttributes));

    RHIVBOs.push_back(pRHI->RHICreateBuffer(RHIBufferType::VertexBuffer, RHIBufferUsageFlag::VertexBuffer,
        sizeof(VertexAttributes2), VertexAttributes2));
}

void RHIApplication2::CreateEBO()
{
    RHIEBO = pRHI->RHICreateBuffer(RHIBufferType::IndexBuffer, RHIBufferUsageFlag::IndexBuffer, sizeof(Index), Index);
}

void RHIApplication2::CreateTexture()
{
    RHISampler_ = pRHI->RHICreateSampler(RHIFilter::NEAREST, RHIFilter::NEAREST);
    int texWidth, texHeight, texChannels;
#if  1
    /*
        STBI_rgb_alpha统一转成4通道
    */
    //stbi_uc* pixels = stbi_load("textures/texture.png", &texWidth, &texHeight, &texChannels, STBI_rgb_alpha);
    stbi_uc* pixels = stbi_load("textures/asuka.jpg", &texWidth, &texHeight, &texChannels, STBI_rgb_alpha);
    auto imageSize = texWidth * texHeight * 4;
    std::cout 
        << "texWidth "   << texWidth   << " "
        << "texHeight  " << texHeight  << " "
        << "texChannels  " << texChannels << " "
        << "pixels  " << (unsigned int)pixels[(texHeight * texWidth / 2 + texWidth / 2) * 4] << " "
        << std::endl;
    if (!pixels) {
        throw std::runtime_error("failed to load texture image!");
    }

    RHITexture2D = pRHI->RHICreateTexture2D(RHIPixelFormat::PF_R8G8B8A8_UNORM, RHITextureUsageFlag::SampledTexture, RHIImageLayout::RHI_IMAGE_LAYOUT_UNDEFINED, 1, texWidth, texHeight, pixels);

#endif
    RHIColorAttachments.resize(3);
    RHIColorAttachments[0] = pRHI->RHICreateTexture2D(RHIPixelFormat::PF_R8G8B8A8_UNORM, RHITextureUsageFlag::ColorAttachment, RHIImageLayout::RHI_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,1, 800, 600, pixels);
    RHIColorAttachments[1] = pRHI->RHICreateTexture2D(RHIPixelFormat::PF_R8G8B8A8_UNORM, RHITextureUsageFlag::ColorAttachment, RHIImageLayout::RHI_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,1, 800, 600, pixels);
    RHIColorAttachments[2] = pRHI->RHICreateTexture2D(RHIPixelFormat::PF_R8G8B8A8_UNORM, RHITextureUsageFlag::ColorAttachment, RHIImageLayout::RHI_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,1, 800, 600, pixels);

    RHIDepthAttachments.resize(1);
    std::cout << "PF_DepthStencil_D32_S8 textrue start" << std::endl;
    RHIDepthAttachments[0] = pRHI->RHICreateTexture2D(RHIPixelFormat::PF_DepthStencil_D32_S8,  RHITextureUsageFlag::DepthStencilAttachment, RHIImageLayout::RHI_IMAGE_LAYOUT_DEPTH_ATTACHMENT_OPTIMAL, 1, 800, 600, nullptr);
    std::cout  << "PF_DepthStencil_D32_S8 textrue end" << std::endl;
    RHISamplers.resize(3);
    RHISamplers[0] = pRHI->RHICreateSampler(RHIFilter::NEAREST, RHIFilter::NEAREST);
    RHISamplers[1] = pRHI->RHICreateSampler(RHIFilter::NEAREST, RHIFilter::NEAREST);
    RHISamplers[2] = pRHI->RHICreateSampler(RHIFilter::NEAREST, RHIFilter::NEAREST);
    std::cout << "RHICreateTextureRenderTarget start" << std::endl;
    this->TextureRenderTarget = pRHI->RHICreateTextureRenderTarget(RHIColorAttachments, RHIDepthAttachments);
    std::cout << "RHICreateTextureRenderTarget end" << std::endl;
}


void RHIApplication2::CreateSRB()
{

    SRB2 = pRHI->RHICreateShaderResourceBindings();
    SRB2->SetBindings({
#if 1
        RHIShaderResourceBinding::SampledTexture(0, RHIShaderType::Fragment, RHIColorAttachments[0], RHISamplers[0]),
      //  RHIShaderResourceBinding::SampledTexture(1, RHIShaderType::Fragment, RHIColorAttachments[1], RHISamplers[1]),
      //  RHIShaderResourceBinding::SampledTexture(2, RHIShaderType::Fragment, RHIColorAttachments[2], RHISamplers[2]),
#else
        RHIShaderResourceBinding::SampledTexture(0, RHIShaderType::Fragment, RHITexture2D, RHISampler_)
#endif
    });
    std::cout << "Create SRB2 begin" << std::endl;
    SRB2->Create();
    std::cout << "Create SRB begin" << std::endl;
    SRB = pRHI->RHICreateShaderResourceBindings();
    SRB->SetBindings({
            RHIShaderResourceBinding::SampledTexture(0, RHIShaderType::Fragment, RHITexture2D, RHISampler_)
    });
    SRB->Create();
    std::cout << "Create SRB end" << std::endl;
}

void RHIApplication2::CreateVertexDescriptioin()
{
    VertexInputs.push_back( std::make_pair(RHIVBOs[0], 0 * sizeof(float)));
    VertexInputs2.push_back(std::make_pair(RHIVBOs[1], 0 * sizeof(float)));
}

void RHIApplication2::CreateGraphicsPipeline()
{
#if 1
    auto vertShaderCode = ReadFile("TextureRenderTarget_vert.spv");
    auto fragShaderCode = ReadFile("TextureRenderTarget_frag.spv");
    // 创建Shader
    VertexShader= pRHI->RHICreateShader(RHIShaderType::Vertex, (std::uint32_t*)vertShaderCode.data(), vertShaderCode.size());
    FragmengShader = pRHI->RHICreateShader(RHIShaderType::Fragment, (std::uint32_t*)fragShaderCode.data(), fragShaderCode.size());

#else
    auto vertShaderCode = ReadFile2("TextureRenderTarget_vert.glsl");
    auto fragShaderCode = ReadFile2("TextureRenderTarget_frag.glsl");
    const char* p1 = vertShaderCode.c_str();
    const char* p2 = fragShaderCode.c_str();

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
    GraphicsPipeline = pRHI->RHICreateGraphicsPipeline(TextureRenderTarget->GetRenderPass());
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
    VertexShader = nullptr;
    FragmengShader = nullptr;
}


void RHIApplication2::CreateGraphicsPipeline2()
{
    std::cout << "GraphicsPipeline2 1" << std::endl;
#if 1
    auto vertShaderCode = ReadFile("RT_Texture2D_vert.spv");
    auto fragShaderCode = ReadFile("RT_Texture2D_frag.spv");
    // 创建Shader
    VertexShader= pRHI->RHICreateShader(RHIShaderType::Vertex, (std::uint32_t*)vertShaderCode.data(), vertShaderCode.size());
    FragmengShader = pRHI->RHICreateShader(RHIShaderType::Fragment, (std::uint32_t*)fragShaderCode.data(), fragShaderCode.size());

#else
    auto vertShaderCode = ReadFile2("RT_Texture2D_vert.glsl");
    auto fragShaderCode = ReadFile2("RT_Texture2D_frag.glsl");
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
    std::cout << "GraphicsPipeline2 2" << std::endl;
#if USE_RHIWindow
    GraphicsPipeline2 = pRHI->RHICreateGraphicsPipeline(RHIWindow_);
#else
    GraphicsPipeline2 = pRHI->RHICreateGraphicsPipeline(RenderTarget->GetRenderPass());
#endif
    GraphicsPipeline2->SetShaderResourceBindings(SRB2);
    GraphicsPipeline2->SetPolygonMode(RHIPolygonMode::Fill);
    GraphicsPipeline2->SetCullMode(RHICullMode::CullModeNone);
#if USE_RHI_VULKAN
    GraphicsPipeline->SetFrontFace(RHIFrontFace::CW);
#else
    GraphicsPipeline2->SetFrontFace(RHIFrontFace::CCW);
#endif
    GraphicsPipeline2->SetTopology(RHITopology::Triangles);
    GraphicsPipeline2->SetVertexInputLayout(VertexInputLayout);
    GraphicsPipeline2->SetShaderStages({ VertexShader , FragmengShader });
    std::cout << "GraphicsPipeline2->Create()" << std::endl;
    GraphicsPipeline2->Create();
    std::cout << "GraphicsPipeline2->Create() ok" << std::endl;
    delete VertexShader;
    delete FragmengShader;
    VertexShader = nullptr;
    FragmengShader = nullptr;
}

void RHIApplication2::Draw2()
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



void RHIApplication2::Draw()
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
