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
RHIApplication *pApp;

void window_close_callback(GLFWwindow* window)
{
    // 用户尝试关闭窗口时调用
    printf("Window close requested!\n");

    // 可以在这里执行清理操作，或询问用户是否保存
    // 如果需要阻止窗口关闭，可以重新设置关闭标志
    // glfwSetWindowShouldClose(window, GLFW_FALSE);
}


RHIApplication::RHIApplication()
{
   // return;
    RHIIndex = 0 ;
    if (0 == RHIIndex)
    {
        Window = CreateGLFWWindow(IWindow::Vulkan);
        Window->SetGeometry(400, 300, 800, 600);
        //glfwSetWindowCloseCallback(((GLFWWindow *)Window)->GetHandle(), window_close_callback);
        pApp = this;
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
        /*
            opengl需要
        */
       // glfwMakeContextCurrent(InWindow);

    }
#if 0
    // 必须在 glfwInit() 之前调用
    if (glfwPlatformSupported(GLFW_PLATFORM_WAYLAND)) {
        glfwInitHint(GLFW_PLATFORM, GLFW_PLATFORM_WAYLAND);
        std::cout << "Using Wayland platform" << std::endl;
    } else if (glfwPlatformSupported(GLFW_PLATFORM_X11)) {
        glfwInitHint(GLFW_PLATFORM, GLFW_PLATFORM_X11);
        std::cout << "Using X11 platform" << std::endl;
    } else {
        std::cerr << "Error: No supported platform found for GLFW" << std::endl;
        abort();
    }
#endif
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
    std::cout << "RHICreateSwapchainRenderTarget 1" << std::endl;
    this->RenderTarget = pRHI->RHICreateSwapchainRenderTarget(Surface);
    std::cout << "RHICreateSwapchainRenderTarget 2" << std::endl;
}


RHIApplication::~RHIApplication()
{
    return;
    std::cout << "~RHIApplication 1" << std::endl;
   // delete VertexShader;
   // delete FragmengShader;
   //delete GeometryShader;
   //delete ComputeShader;
    std::cout << "~RHIApplication 2" << std::endl;
    //delete RenderTarget;
    std::cout << "~RHIApplication 3" << std::endl;
    delete RHIVBO;
    std::cout << "~RHIApplication 4" << std::endl;
    delete RHIEBO;
    std::cout << "~RHIApplication 5" << std::endl;
    delete SRB;
    std::cout << "~RHIApplication 6" << std::endl;
    delete GraphicsPipeline;
    std::cout << "~RHIApplication 7" << std::endl;
    delete Surface;
    std::cout << "~RHIApplication 8" << std::endl;
    delete pRHI;
    std::cout << "~RHIApplication 9" << std::endl;
}

void RHIApplication::Run()
{

    Init();


    auto glfwWin = ((GLFWWindow *)Window)->GetHandle();
    while (!glfwWindowShouldClose(glfwWin))
    {
        if (TextureRenderTarget) {

            TextureRenderTarget->RHIBeginFrame();
            TextureRenderTarget->RHIBeginRenderPass();
            Draw2();
            TextureRenderTarget->RHIEndRenderPass();
            TextureRenderTarget->RHIEndFrame();
        }
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

void RHIApplication::Resize(int w, int h)
{
    Window->Resize(w, h);
}

void RHIApplication::Init()
{

}

void RHIApplication::Draw()
{

}

void RHIApplication::Draw2()
{

}

void RHIApplication::Render()
{

}


