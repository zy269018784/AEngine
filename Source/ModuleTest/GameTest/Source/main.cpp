#include "GCore/GObject.h"
#include "GMath/Math.h"
#include "GCG/GVirtualGeometry/GVirtualGeometry.h"
#include "GGame/GGame.h"
#include "GGame/GFood.h"
#include <QApplication>
#include "GWindow/QTWindow/QTWindow.h"
#include "GDeviceDriver/OLED/SSD1306.h"
#include "GWindow/FLTKWindow/FLTKWindow.h"
#include "GWindow/GLFWWindow/GLFWWindow.h"
#include "GWindow/SDLWindow/SDL3Window.h"
#include "GWindow/X11Window/X11Window.h"


#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <iostream>
#include <vector>
//int cef_main(int argc, char **argv);
int main(int argc, char **argv)
{
    //return cef_main(argc, argv);
    std::vector<GFood> Foods = {
    {"包菜", 2.0},
    {"香蕉", 2.0},
    {"鸡翅", 8.0},
    {"豆肠", 1.0},
    {"鸡柳", 3.0},
    };

    for (int i = 0; i < Foods.size(); ++i) {
        std::cout << Foods[i].GetName() << " " <<  Foods[i].GetPrice() << std::endl;
    }
    //wxFrame* window = new wxFrame(NULL, wxID_ANY, "这是一个测试窗口", wxDefaultPosition, wxSize(600, 400));
    //window->SetSizer(sizer);
    //window->Show();

    IWindow *win = nullptr;
    int Index =  2;
    QApplication *app;
    switch (Index)
    {
    case 0:
        glfwInit();
        win = new GLFWWindow(IWindow::GraphicsAPI::OpenGL46, nullptr);
        break;
    case 1:
        win = new FLTKWindow(IWindow::GraphicsAPI::OpenGL46, nullptr);
        break;
    case 2:
        if (!SDL_Init(SDL_INIT_VIDEO)) {
            SDL_Log("SDL_Init 失败: %s", SDL_GetError());
            return -1;
        }
        win = new SDL3Window(IWindow::GraphicsAPI::OpenGL46, nullptr);
        break;
    case 3:
        win = new X11Window(IWindow::GraphicsAPI::OpenGL46, nullptr);
        break;
    case 4:
        app = new QApplication(argc, argv);
        win = new QTWindow(IWindow::GraphicsAPI::OpenGL46, nullptr);
        break;
    default:
        break;
    }

    win->SetTitle("Hello IWindow");
    win->SetGeometry(1920 - 400, 1080 - 300, 800, 600);
    win->SetGeometry(960, 0, 960, 540);
    win->SetVisible(true);
    win->Run();
    delete win;

    // 结束
    switch (Index)
    {
    case 0:

        break;
    case 1:

        break;
    case 2:
        SDL_Quit();
        break;
    case 4:
        return app->exec();
    default:
        break;
    }
}


#if 0
#include "include/cef_app.h"
#include "include/cef_browser.h"
#include "include/cef_client.h"
#include <X11/Xlib.h>
#include <thread>

// 简单处理器：处理浏览器生命周期
class SimpleHandler : public CefClient, public CefLifeSpanHandler {
public:
    void OnBeforeClose(CefRefPtr<CefBrowser> browser) override {
        CefQuitMessageLoop();
    }

    CefRefPtr<CefLifeSpanHandler> GetLifeSpanHandler() override {
        return this;
    }

private:
    IMPLEMENT_REFCOUNTING(SimpleHandler);
};

// 主应用：创建浏览器
class SimpleApp : public CefApp, public CefBrowserProcessHandler {
public:
    void OnContextInitialized() override {
        // 1. 创建 X11 窗口
        Display* dpy = XOpenDisplay(nullptr);
        int screen = DefaultScreen(dpy);
        Window parent = XCreateSimpleWindow(dpy, RootWindow(dpy, screen),
                                            0, 0, 1024, 768, 1,
                                            BlackPixel(dpy, screen),
                                            WhitePixel(dpy, screen));
        XStoreName(dpy, parent, "CEF Browser");
        XSelectInput(dpy, parent, StructureNotifyMask);
        XMapWindow(dpy, parent);
        XFlush(dpy);

        // 2. 配置 CEF 窗口信息
        CefWindowInfo window_info;
        window_info.SetAsChild(parent, CefRect(0, 0, 1024, 768));

        // 3. 创建浏览器
        CefBrowserSettings browser_settings;
        CefRefPtr<SimpleHandler> handler(new SimpleHandler());
        CefBrowserHost::CreateBrowser(window_info, handler.get(),
                                      "https://www.google.com",
                                      browser_settings, nullptr, nullptr);

        // 4. 保存 display 用于后续事件循环（简化版跳过）
    }

    CefRefPtr<CefBrowserProcessHandler> GetBrowserProcessHandler() override {
        return this;
    }

private:
    IMPLEMENT_REFCOUNTING(SimpleApp);
};

// 入口函数
int cef_main(int argc, char* argv[]) {
    CefMainArgs main_args(argc, argv);
    CefRefPtr<SimpleApp> app(new SimpleApp());

    int exit_code = CefExecuteProcess(main_args, app.get(), nullptr);
    if (exit_code >= 0) {
        return exit_code;
    }

    CefSettings settings;
    settings.no_sandbox = true;

    CefInitialize(main_args, settings, app.get(), nullptr);
    CefRunMessageLoop();
    CefShutdown();

    return 0;
}
#endif