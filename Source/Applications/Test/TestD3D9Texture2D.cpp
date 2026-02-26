#include <iostream>
#include <vector>
#include <string>
#include <windows.h>
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

// D3D9 必需的头文件
#include <d3d9.h>
#include <DirectXMath.h>

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dcompiler.lib")

using namespace DirectX;

// 窗口尺寸
static const UINT WIDTH = 800;
static const UINT HEIGHT = 600;

// 纹理参数
static const UINT TEXTURE_WIDTH = 256;
static const UINT TEXTURE_HEIGHT = 256;

// 全局 D3D9 对象 - 全部加上 static
static IDirect3D9* g_d3d = nullptr;
static IDirect3DDevice9* g_device = nullptr;
static IDirect3DTexture9* g_texture = nullptr;
static IDirect3DVertexBuffer9* g_vertexBuffer = nullptr;
static IDirect3DVertexDeclaration9* g_vertexDeclaration = nullptr;

// 顶点结构 - D3D9 使用 FVF 或顶点声明
struct Vertex {
    DirectX::XMFLOAT3 position;  // 位置
    DirectX::XMFLOAT2 texcoord;  // 纹理坐标 (uv)
};

// 顶点格式 - 用于 FVF
static const DWORD VERTEX_FVF = D3DFVF_XYZ | D3DFVF_TEX1;

// 检查 HRESULT 的辅助宏
#define CHECK_HR(hr) { if (FAILED(hr)) { std::cerr << "HRESULT failed at line " << __LINE__ << std::endl; return false; } }

// 创建纹理数据 - 彩色渐变纹理
static void CreateTextureData(std::vector<uint8_t>& data) {
    data.resize(TEXTURE_WIDTH * TEXTURE_HEIGHT * 4);

    for (UINT y = 0; y < TEXTURE_HEIGHT; ++y) {
        for (UINT x = 0; x < TEXTURE_WIDTH; ++x) {
            UINT index = (y * TEXTURE_WIDTH + x) * 4;

            // 创建彩色渐变：
            // 左上角红色，右上角绿色，左下角蓝色，右下角白色
            float nx = (float)x / (TEXTURE_WIDTH - 1);
            float ny = (float)y / (TEXTURE_HEIGHT - 1);

            data[index + 0] = (UINT8)(nx * 255);              // R 从左到右渐变
            data[index + 1] = (UINT8)(ny * 255);              // G 从上到下渐变
            data[index + 2] = (UINT8)((1.0f - nx) * 255);     // B 从右到左渐变
            data[index + 3] = 255;                              // Alpha
        }
    }
    std::cout << "2D texture data created with gradients" << std::endl;
}

// 初始化 D3D9
static bool InitD3D9(GLFWwindow* window) {
    std::cout << "Initializing D3D9..." << std::endl;

    // 创建 D3D9 对象
    g_d3d = Direct3DCreate9(D3D_SDK_VERSION);
    if (!g_d3d) {
        std::cerr << "Failed to create Direct3D9 object" << std::endl;
        return false;
    }

    // 获取窗口句柄
    HWND hwnd = glfwGetWin32Window(window);

    // 设置 D3D9 参数
    D3DPRESENT_PARAMETERS d3dpp = {};
    d3dpp.Windowed = TRUE;
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
    d3dpp.BackBufferWidth = WIDTH;
    d3dpp.BackBufferHeight = HEIGHT;
    d3dpp.hDeviceWindow = hwnd;
    d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE; // 启用垂直同步

    // 创建设备
    CHECK_HR(g_d3d->CreateDevice(
        D3DADAPTER_DEFAULT,
        D3DDEVTYPE_HAL,
        hwnd,
        D3DCREATE_HARDWARE_VERTEXPROCESSING,
        &d3dpp,
        &g_device
    ));

    std::cout << "D3D9 device created" << std::endl;

    // 设置渲染状态
    g_device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE); // 不剔除背面
    g_device->SetRenderState(D3DRS_LIGHTING, FALSE);       // 禁用光照
    g_device->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE); // 禁用Alpha混合

    // 设置纹理采样状态
    g_device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
    g_device->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
    g_device->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);
    g_device->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
    g_device->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);

    std::cout << "D3D9 initialized successfully" << std::endl;
    return true;
}

// 创建顶点缓冲区 - 一个大的三角形覆盖大部分屏幕
static bool CreateVertexBuffer() {
    std::cout << "Creating vertex buffer..." << std::endl;

    // 创建一个大的三角形，覆盖大部分屏幕
    // D3D9 使用屏幕坐标系：(-1,-1) 到 (1,1)
    Vertex vertices[] = {
        { { 0.0f, 0.8f, 0.0f }, { 0.5f, 0.0f } },     // 顶部中间
        { { 0.8f, -0.6f, 0.0f }, { 1.0f, 1.0f } },    // 右下
        { { -0.8f, -0.6f, 0.0f }, { 0.0f, 1.0f } },   // 左下
    };

    std::cout << "Triangle vertices:" << std::endl;
    for (int i = 0; i < 3; i++) {
        std::cout << "  Vertex " << i << ": pos("
                  << vertices[i].position.x << ", "
                  << vertices[i].position.y << ", "
                  << vertices[i].position.z << ") uv("
                  << vertices[i].texcoord.x << ", "
                  << vertices[i].texcoord.y << ")" << std::endl;
    }

    // 创建顶点缓冲区
    CHECK_HR(g_device->CreateVertexBuffer(
        sizeof(vertices),
        D3DUSAGE_WRITEONLY,
        VERTEX_FVF,
        D3DPOOL_DEFAULT,
        &g_vertexBuffer,
        nullptr
    ));

    // 填充顶点数据
    void* ptr;
    CHECK_HR(g_vertexBuffer->Lock(0, 0, &ptr, 0));
    memcpy(ptr, vertices, sizeof(vertices));
    g_vertexBuffer->Unlock();

    std::cout << "Vertex buffer created" << std::endl;
    return true;
}

// 创建2D纹理
static bool Create2DTexture() {
    std::cout << "Creating 2D texture..." << std::endl;

    std::vector<uint8_t> textureData;
    CreateTextureData(textureData);

    // 创建纹理
    CHECK_HR(g_device->CreateTexture(
        TEXTURE_WIDTH,
        TEXTURE_HEIGHT,
        1,  // mip levels
        0,  // usage
        D3DFMT_A8R8G8B8,
        D3DPOOL_MANAGED,
        &g_texture,
        nullptr
    ));

    // 锁定纹理并填充数据
    D3DLOCKED_RECT lockedRect;
    CHECK_HR(g_texture->LockRect(0, &lockedRect, nullptr, 0));

    // D3D9 使用 A8R8G8B8 格式，需要转换数据
    uint8_t* dest = (uint8_t*)lockedRect.pBits;
    for (UINT y = 0; y < TEXTURE_HEIGHT; ++y) {
        for (UINT x = 0; x < TEXTURE_WIDTH; ++x) {
            UINT srcIndex = (y * TEXTURE_WIDTH + x) * 4;
            UINT destIndex = y * lockedRect.Pitch + x * 4;

            // 从 R8G8B8A8 转换为 A8R8G8B8
            dest[destIndex + 0] = textureData[srcIndex + 2]; // B
            dest[destIndex + 1] = textureData[srcIndex + 1]; // G
            dest[destIndex + 2] = textureData[srcIndex + 0]; // R
            dest[destIndex + 3] = textureData[srcIndex + 3]; // A
        }
    }

    g_texture->UnlockRect(0);

    std::cout << "2D texture created with size " << TEXTURE_WIDTH << "x" << TEXTURE_HEIGHT << std::endl;
    return true;
}

// 渲染循环 - D3D9 版本
static void Render() {
    if (!g_device || !g_vertexBuffer) {
        std::cerr << "Missing render resources" << std::endl;
        return;
    }

    // 清屏为深灰色
    g_device->Clear(0, nullptr, D3DCLEAR_TARGET, D3DCOLOR_XRGB(25, 25, 25), 1.0f, 0);

    // 开始场景
    g_device->BeginScene();

    // 设置顶点流
    g_device->SetStreamSource(0, g_vertexBuffer, 0, sizeof(Vertex));
    g_device->SetFVF(VERTEX_FVF);

    // 设置纹理
    g_device->SetTexture(0, g_texture);

    // 绘制三角形
    g_device->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 1);

    // 结束场景
    g_device->EndScene();

    // 呈现
    g_device->Present(nullptr, nullptr, nullptr, nullptr);

    static int frameCount = 0;
    frameCount++;
    if (frameCount % 60 == 0) {
        std::cout << "Rendered frame " << frameCount << std::endl;
    }
}

// 清理资源 - D3D9 版本
static void Cleanup() {
    std::cout << "Cleaning up..." << std::endl;

    if (g_texture) {
        g_texture->Release();
        g_texture = nullptr;
    }
    if (g_vertexBuffer) {
        g_vertexBuffer->Release();
        g_vertexBuffer = nullptr;
    }
    if (g_vertexDeclaration) {
        g_vertexDeclaration->Release();
        g_vertexDeclaration = nullptr;
    }
    if (g_device) {
        g_device->Release();
        g_device = nullptr;
    }
    if (g_d3d) {
        g_d3d->Release();
        g_d3d = nullptr;
    }

    std::cout << "Cleanup complete" << std::endl;
}

// 主函数
int TestD3D9Texture2D(int argc, char **argv) {
    std::cout << "Starting D3D9 2D Texture Test..." << std::endl;
    std::cout << "Window size: " << WIDTH << "x" << HEIGHT << std::endl;

    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "D3D9 2D Texture", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create window" << std::endl;
        glfwTerminate();
        return -1;
    }

    std::cout << "Window created successfully" << std::endl;

    if (!InitD3D9(window)) {
        std::cerr << "Failed to initialize D3D9" << std::endl;
        Cleanup();
        glfwDestroyWindow(window);
        glfwTerminate();
        return -1;
    }

    if (!CreateVertexBuffer()) {
        std::cerr << "Failed to create vertex buffer" << std::endl;
        Cleanup();
        glfwDestroyWindow(window);
        glfwTerminate();
        return -1;
    }

    if (!Create2DTexture()) {
        std::cerr << "Failed to create 2D texture" << std::endl;
        Cleanup();
        glfwDestroyWindow(window);
        glfwTerminate();
        return -1;
    }

    std::cout << "All resources created successfully" << std::endl;
    std::cout << "Entering main loop..." << std::endl;

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        Render();
    }

    std::cout << "Exiting main loop..." << std::endl;

    Cleanup();
    glfwDestroyWindow(window);
    glfwTerminate();

    std::cout << "Test completed successfully" << std::endl;
    return 0;
}
