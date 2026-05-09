#include <RHIApplication.h>

#include "Rhi/RHIObjects/Resource/RHIBuffer.h"
#include "Rhi/RHIObjects/Shader/RHIShader.h"
#include "Rhi/RHIObjects/Shader/RHIShaderResourceBindings.h"
#include "Rhi/RHIObjects/Surface/RHISurface.h"
#ifdef PROJECT_USE_XCB
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
    std::cout << "RHIApplication 1" << std::endl;
    RHIIndex = 0;
    if (0 == RHIIndex)
    {
        Window = CreateGLFWWindow(IWindow::Vulkan);
        //glfwSetWindowCloseCallback(((GLFWWindow *)Window)->GetHandle(), window_close_callback);

        pApp = this;
        pRHI = CreateVulkanRHI();
#ifdef PROJECT_USE_VULKAN
        pRHI = new VulkanRHI();
#endif

    }
    else if (1 == RHIIndex)
    {
        pRHI = CreateD3D12RHI();
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
        //pRHI = new ES32RHI();
        pRHI = CreateES32RHI();
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
#ifdef PROJECT_USE_GLFW
    auto GLFWHandle = ((GLFWWindow *)Window)->GetHandle();
   	HWND hwnd = glfwGetWin32Window(GLFWHandle);
	HINSTANCE instacne = (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE);
    Surface = pRHI->RHICreateSurface(instacne, hwnd);
#endif

#endif

    this->RenderTarget = pRHI->RHICreateSwapchainRenderTarget(Surface);
}


RHIApplication::~RHIApplication()
{
    delete VertexShader;
    delete FragmengShader; 
   //delete GeometryShader;
   //delete ComputeShader;
    delete RenderTarget;
    delete RHIVBO;
    delete RHIEBO;
    delete SRB;
    delete GraphicsPipeline;
    delete Surface;
    delete pRHI;
}

void RHIApplication::Run()
{
    Init();
#ifdef PROJECT_USE_GLFW
    auto glfwWin = ((GLFWWindow *)Window)->GetHandle();
    while (!glfwWindowShouldClose(glfwWin))
    {

        RenderTarget->RHIBeginFrame();
        RenderTarget->RHIBeginRenderPass();
        Draw();
        RenderTarget->RHIEndRenderPass();
        RenderTarget->RHIEndFrame();
#ifdef PROJECT_USE_GLFW
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(glfwWin);
        glfwPollEvents();
#endif

    }
#endif

    RenderTarget->WaitDeviceIdle();
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

void RHIApplication::Render()
{

}
//#endif