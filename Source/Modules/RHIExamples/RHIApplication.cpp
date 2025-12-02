#include <RHIApplication.h>
#ifdef PROJECT_USE_X11
#include <xcb/xcb.h>
#include <X11/Xlib-xcb.h>
#endif
#include "Window/GLFWWindow.h"
RHIApplication::RHIApplication(IWindow* InWindow)
    : Window(InWindow)
{
   // return;
    std::cout << "RHIApplication 1" << std::endl;
#if USE_RHI_VULKAN
#ifdef PROJECT_USE_VULKAN
    pRHI = new VulkanRHI();
   // pRHI->RHIUseGPU(0);
#endif

#else
    /*
        opengl需要
    */
   // glfwMakeContextCurrent(InWindow);
    pRHI = new ES32RHI();
#endif
#ifdef PROJECT_USE_X11
    //Display* Display = glfwGetX11Display();
    //xcb_connection_t* connection = XGetXCBConnection(Display);
    //xcb_window_t xcb_window = glfwGetX11Window(InWindow);


    xcb_window_t xcb_window =  Window->GetWindow();
    xcb_connection_t* connection = Window->GetXCBConnection();
    if (!connection || xcb_window == XCB_NONE) {
        std::cerr << "Failed to get XCB connection/window" << std::endl;
        return;
    }
    RHIWindow_ = pRHI->RHICreateWindow(connection, xcb_window);
    std::cout << "glfwGetX11Window" << std::endl;
#endif

#ifdef OS_IS_WINDOWS
    std::cout << "RHIApplication 1" << std::endl;
    auto GLFWHandle = ((GLFWWindow *)Window)->GetHandle();

   	HWND hwnd = glfwGetWin32Window(GLFWHandle);

	HINSTANCE instacne = (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE);
    std::cout << "RHIApplication 2" << std::endl;
    RHIWindow_ = pRHI->RHICreateWindow(instacne, hwnd);
    std::cout << "RHIApplication 3" << std::endl;
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
    auto glfwWin = ((GLFWWindow *)Window)->GetHandle();
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