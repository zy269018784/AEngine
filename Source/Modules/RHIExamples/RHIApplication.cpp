#include <RHIApplication.h>

#include "VulkanObjects/RenderTarget/VulkanSwapChainRenderTarget.h"
#include "VulkanObjects/Window/VulkanWindow.h"
#ifdef PROJECT_USE_XCB
#include <xcb/xcb.h>
#include <X11/Xlib-xcb.h>
#endif
#include "Window/GLFWWindow.h"
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
    std::cout << "RHIApplication 1" << std::endl;
    RHIIndex = 0;
    if (0 == RHIIndex)
    {
        Window = new GLFWWindow(IWindow::Vulkan);
        glfwSetWindowCloseCallback(((GLFWWindow *)Window)->GetHandle(), window_close_callback);
        pApp = this;
        pRHI = new VulkanRHI();
    }
    else if (1 == RHIIndex)
    {
#ifdef PROJECT_USE_D3D12
        pRHI = new D3D12RHI();
#endif
    }
    else if (2 == RHIIndex)
    {
        GLFWWindow *tmpWin = new GLFWWindow(IWindow::OpenGL46);
        tmpWin->MakeContextCurrent();

        Window = tmpWin;
        /*
            opengl需要
        */
       // glfwMakeContextCurrent(InWindow);
        pRHI = new ES32RHI();
    }
    pRHI->RHIUseGPU(0);



#ifdef PROJECT_USE_XCB1
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

#ifdef PROJECT_USE_Xlib
    Display *Disp = Window->GetXlibDisplay();
    ::Window Win = Window->GetXlibWindow();
    RHIWindow_ = pRHI->RHICreateWindow(Disp, Win);
    Surface = pRHI->RHICreateSurface(Disp, Win);
#endif


#ifdef OS_IS_WINDOWS
    std::cout << "RHIApplication 1" << std::endl;
    auto GLFWHandle = ((GLFWWindow *)Window)->GetHandle();

   	HWND hwnd = glfwGetWin32Window(GLFWHandle);

	HINSTANCE instacne = (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE);
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


RHIApplication::~RHIApplication()
{
    std::cout << "~RHIApplication 1" << std::endl;
    delete VertexShader;
    std::cout << "~RHIApplication 2" << std::endl;
    delete FragmengShader; 
   //delete GeometryShader;
   //delete ComputeShader;
    std::cout << "~RHIApplication 3" << std::endl;
    delete RenderTarget;
    std::cout << "~RHIApplication 4" << std::endl;
    delete RHIVBO;
    std::cout << "~RHIApplication 5" << std::endl;
    delete RHIEBO;
    std::cout << "~RHIApplication 6" << std::endl;
    delete SRB;
    std::cout << "~RHIApplication 7" << std::endl;
    delete GraphicsPipeline;
    std::cout << "~RHIApplication 8" << std::endl;
#if 0
    delete RenderTarget;
    delete Surface;
#endif
    delete Surface;
    delete pRHI;
    std::cout << "~RHIApplication 9" << std::endl;
}

void RHIApplication::Run()
{
    Init();
#if 1
    auto glfwWin = ((GLFWWindow *)Window)->GetHandle();
    while (!glfwWindowShouldClose(glfwWin))
    {
#if USE_RHIWindow
        RHIWindow_->RHIBeginFrame();
        RHIWindow_->RHIBeginRenderPass();
        Draw();
        RHIWindow_->RHIEndRenderPass();
        RHIWindow_->RHIEndFrame();
#else
        RenderTarget->RHIBeginFrame();
        RenderTarget->RHIBeginRenderPass();
        Draw();
        RenderTarget->RHIEndRenderPass();
        RenderTarget->RHIEndFrame();
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

void RHIApplication::Resize(int w, int h)
{
    Window->Resize(w, h);
    //glfwSetWindowSize(Window, w, h);
}

void RHIApplication::Init()
{

}

void RHIApplication::Draw()
{

}

void RHIApplication::Render()
{

}