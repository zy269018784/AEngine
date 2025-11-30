#include <RHIApplication.h>
#ifdef PROJECT_USE_X11
#include <xcb/xcb.h>
#include <X11/Xlib-xcb.h>
#endif
RHIApplication::RHIApplication(GLFWwindow* InWindow)
    : Window(InWindow)
{
   // return;
    std::cout << "RHIApplication" << std::endl;
#if USE_RHI_VULKAN
#ifdef PROJECT_USE_VULKAN
    pRHI = new VulkanRHI();
#endif

#else
    /*
        opengl需要
    */
    glfwMakeContextCurrent(InWindow);
    pRHI = new ES32RHI();
#endif
#ifdef PROJECT_USE_X11
    Display* Display = glfwGetX11Display();
    xcb_connection_t* connection = XGetXCBConnection(Display);
    xcb_window_t xcb_window = glfwGetX11Window(InWindow);

    if (!connection || xcb_window == XCB_NONE) {
        std::cerr << "Failed to get XCB connection/window" << std::endl;
        return;
    }
    RHIWindow_ = pRHI->RHICreateWindow(connection, xcb_window);
    std::cout << "glfwGetX11Window" << std::endl;
#endif

#ifdef OS_IS_WINDOWS
   	HWND hwnd = glfwGetWin32Window(Window);
	HINSTANCE instacne = (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE);

    RHIWindow_ = pRHI->RHICreateWindow(instacne, hwnd);
#endif

    std::cout << "RHIApplication End" << std::endl;
}

RHIApplication::~RHIApplication()
{
    delete VertexShader; 
    delete FragmengShader; 
    delete GeometryShader; 
    delete ComputeShader; 
    delete RHIVBO;
    delete RHIEBO;
    delete SRB;
    delete GraphicsPipeline;
    delete RHIWindow_;
    delete pRHI;
}

void RHIApplication::Run()
{
    Init();
#if 1
    while (!glfwWindowShouldClose(Window))
    {
        RHIWindow_->RHIBeginFrame();
        RHIWindow_->RHIBeginRenderPass();
        Draw();
        RHIWindow_->RHIEndRenderPass();
        RHIWindow_->RHIEndFrame();
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(Window);
        glfwPollEvents();
    }
    RHIWindow_->WaitDeviceIdle();

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
    glfwSetWindowSize(Window, w, h);
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