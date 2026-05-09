#if  PROJECT_USE_D3D12
#include <iostream>
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

#include <d3d9.h>
#include <wrl/client.h>

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "glfw3.lib")

using namespace Microsoft::WRL;

// 全局变量
ComPtr<IDirect3D9>             g_pD3D = nullptr;
ComPtr<IDirect3DDevice9>       g_pDevice = nullptr;
ComPtr<IDirect3DVertexBuffer9> g_pVertexBuffer = nullptr;

// 自定义顶点结构 - 使用 D3DFVF_TLVERTEX 格式
struct Vertex
{
    float x, y, z, rhw;    // 位置和RHW
    DWORD color;           // 颜色 (ARGB格式)
};

// 初始化 D3D9
bool InitD3D9(GLFWwindow* window, int width, int height)
{
    HRESULT hr;

    std::cout << "Initializing D3D9..." << std::endl;

    // 1. 创建 D3D9 对象
    g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
    if (!g_pD3D)
    {
        std::cerr << "Failed to create Direct3D9 object!" << std::endl;
        return false;
    }

    std::cout << "Direct3D9 object created successfully" << std::endl;

    // 2. 创建设备参数
    D3DPRESENT_PARAMETERS d3dpp = {};
    d3dpp.Windowed = TRUE;
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
    d3dpp.BackBufferWidth = width;
    d3dpp.BackBufferHeight = height;
    d3dpp.hDeviceWindow = glfwGetWin32Window(window);
    d3dpp.EnableAutoDepthStencil = FALSE;
    d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE; // 垂直同步

    // 3. 创建设备
    hr = g_pD3D->CreateDevice(
        D3DADAPTER_DEFAULT,          // 默认适配器
        D3DDEVTYPE_HAL,              // 硬件设备
        glfwGetWin32Window(window),  // 窗口句柄
        D3DCREATE_HARDWARE_VERTEXPROCESSING, // 创建标志
        &d3dpp,                      // 显示参数
        &g_pDevice                   // 设备指针
    );

    if (FAILED(hr))
    {
        std::cerr << "Failed to create D3D9 device! HRESULT: 0x"
                  << std::hex << hr << std::dec << std::endl;
        return false;
    }

    std::cout << "D3D9 device created successfully" << std::endl;

    return true;
}


// 设置渲染状态 - 修正后的版本
void SetupRenderStates()
{
    std::cout << "Setting up render states..." << std::endl;

    // 正确的函数名是 SetRenderState，不是 SetD3D9RenderState

    // 1. 关闭灯光（我们使用顶点颜色）
    g_pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

    // 2. 开启顶点颜色
    g_pDevice->SetRenderState(D3DRS_SPECULARENABLE, FALSE);
    g_pDevice->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_GOURAUD);

    // 3. 设置剔除模式
    g_pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

    // 4. 设置填充模式（实体填充）
    g_pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);

    // 5. 关闭深度测试（2D渲染不需要）
    g_pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);

    // 6. 关闭Alpha混合（简化版本）
    g_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);

    // 7. 设置纹理阶段状态（不使用纹理）
    g_pDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
    g_pDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_DIFFUSE);

    std::cout << "Render states set up successfully" << std::endl;
}
// 创建顶点缓冲区
bool D3D9CreateVertexBuffer()
{
    std::cout << "Creating vertex buffer..." << std::endl;

    // 1. 创建顶点缓冲区
    // 正确的函数名是 CreateVertexBuffer，不是 D3D9CreateVertexBuffer
    HRESULT hr = g_pDevice->CreateVertexBuffer(
        3 * sizeof(Vertex),          // 缓冲区大小（3个顶点）
        D3DUSAGE_WRITEONLY,          // 使用方式
        D3DFVF_XYZRHW | D3DFVF_DIFFUSE, // 顶点格式
        D3DPOOL_DEFAULT,             // 内存池
        &g_pVertexBuffer,            // 缓冲区指针
        nullptr                      // 共享句柄
    );

    if (FAILED(hr))
    {
        std::cerr << "Failed to create vertex buffer! HRESULT: 0x"
                  << std::hex << hr << std::dec << std::endl;
        return false;
    }

    // 2. 锁定并填充顶点数据
    Vertex* vertices = nullptr;
    hr = g_pVertexBuffer->Lock(0, 0, (void**)&vertices, 0);
    if (FAILED(hr))
    {
        std::cerr << "Failed to lock vertex buffer!" << std::endl;
        return false;
    }

    // 屏幕坐标说明：
    // x: 0=左边缘, 800=右边缘
    // y: 0=上边缘, 600=下边缘
    // z: 深度值（0.0-1.0），0.0最近
    // rhw: 1.0表示已经过透视除法
    // color: ARGB格式

    // 顶点1：顶部中心，红色
    vertices[0].x = 400.0f;     // 屏幕中心X
    vertices[0].y = 150.0f;     // 靠近顶部
    vertices[0].z = 0.0f;       // 最前面
    vertices[0].rhw = 1.0f;     // 已透视
    vertices[0].color = D3DCOLOR_XRGB(255, 0, 0); // 红色

    // 顶点2：右下角，绿色
    vertices[1].x = 600.0f;     // 靠右
    vertices[1].y = 450.0f;     // 靠下
    vertices[1].z = 0.0f;
    vertices[1].rhw = 1.0f;
    vertices[1].color = D3DCOLOR_XRGB(0, 255, 0); // 绿色

    // 顶点3：左下角，蓝色
    vertices[2].x = 200.0f;     // 靠左
    vertices[2].y = 450.0f;     // 靠下
    vertices[2].z = 0.0f;
    vertices[2].rhw = 1.0f;
    vertices[2].color = D3DCOLOR_XRGB(0, 0, 255); // 蓝色

    // 解锁缓冲区
    g_pVertexBuffer->Unlock();

    std::cout << "Vertex buffer created successfully" << std::endl;
    std::cout << "Triangle vertices (screen coordinates):" << std::endl;
    std::cout << "  1. (400, 150) - Red" << std::endl;
    std::cout << "  2. (600, 450) - Green" << std::endl;
    std::cout << "  3. (200, 450) - Blue" << std::endl;

    return true;
}

// 渲染函数
void D3D9Render()
{
    // 1. 清除屏幕为深蓝色
    g_pDevice->Clear(0, nullptr, D3DCLEAR_TARGET, D3DCOLOR_XRGB(25, 50, 100), 1.0f, 0);

    // 2. 开始场景
    if (SUCCEEDED(g_pDevice->BeginScene()))
    {
        // 3. 设置数据流和顶点格式
        g_pDevice->SetStreamSource(0, g_pVertexBuffer.Get(), 0, sizeof(Vertex));
        g_pDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE);

        // 4. 绘制三角形
        g_pDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 1); // 绘制1个三角形

        // 5. 结束场景
        g_pDevice->EndScene();
    }

    // 6. 呈现到屏幕
    g_pDevice->Present(nullptr, nullptr, nullptr, nullptr);
}

// 清理资源
void D3D9Cleanup()
{
    std::cout << "Cleaning up resources..." << std::endl;

    g_pVertexBuffer.Reset();
    g_pDevice.Reset();
    g_pD3D.Reset();

    std::cout << "Resources cleaned up" << std::endl;
}

// 主函数
int TestD3D9(int argc, char **argv)
{
    std::cout << "==========================================" << std::endl;
    std::cout << "D3D9 + GLFW Triangle Example (No Matrices)" << std::endl;
    std::cout << "==========================================" << std::endl;

    // 1. 初始化 GLFW
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW!" << std::endl;
        return -1;
    }
    std::cout << "GLFW initialized successfully" << std::endl;

    // 2. 创建 GLFW 窗口
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);  // 不使用 OpenGL
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);    // 固定大小（简化处理）

    GLFWwindow* window = glfwCreateWindow(800, 600, "D3D9 Simple Triangle", nullptr, nullptr);
    if (!window)
    {
        std::cerr << "Failed to create GLFW window!" << std::endl;
        glfwTerminate();
        return -1;
    }
    std::cout << "GLFW window created successfully (800x600)" << std::endl;

    // 3. 初始化 D3D9
    if (!InitD3D9(window, 800, 600))
    {
        std::cerr << "Failed to initialize D3D9!" << std::endl;
        glfwDestroyWindow(window);
        glfwTerminate();
        return -1;
    }

    // 4. 设置渲染状态
    SetupRenderStates();

    // 5. 创建顶点缓冲区
    if (!D3D9CreateVertexBuffer())
    {
        std::cerr << "Failed to create vertex buffer!" << std::endl;
        D3D9Cleanup();
        glfwDestroyWindow(window);
        glfwTerminate();
        return -1;
    }

    std::cout << std::endl;
    std::cout << "Application ready!" << std::endl;
    std::cout << "Controls:" << std::endl;
    std::cout << "  - ESC: Exit application" << std::endl;
    std::cout << std::endl;

    // 主循环
    while (!glfwWindowShouldClose(window))
    {
        // 处理事件
        glfwPollEvents();

        // 检查 ESC 键退出
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        {
            glfwSetWindowShouldClose(window, GLFW_TRUE);
        }

        // 渲染
        D3D9Render();
    }

    // 清理
    D3D9Cleanup();
    glfwDestroyWindow(window);
    glfwTerminate();
    
    std::cout << std::endl;
    std::cout << "Application terminated successfully" << std::endl;
    std::cout << "==========================================" << std::endl;
    
    return 0;
}
#endif