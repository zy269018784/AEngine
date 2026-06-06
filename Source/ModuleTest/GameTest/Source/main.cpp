#include "GCore/GObject.h"
#include "GMath/Math.h"
#include "GCG/GVirtualGeometry/GVirtualGeometry.h"
#include "GGame/GGame.h"
#include "GGame/GFood.h"
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

int main(int argc, char **argv)
{
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


    IWindow *win = nullptr;
    int Index = 2;
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
    default:
        break;
    }

   // win->SetTitle("Hello IWindow");
    win->SetGeometry(1920 - 400, 1080 - 300, 800, 600);
   // win->SetGeometry(0, 1080 - 300, 800, 600);
    win->Show();
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
    default:
        break;
    }
}