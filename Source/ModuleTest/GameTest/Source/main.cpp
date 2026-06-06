#include "GCore/GObject.h"
#include "GMath/Math.h"
#include "GCG/GVirtualGeometry/GVirtualGeometry.h"
#include "GGame/GGame.h"
#include "GGame/GFood.h"
#include "GDeviceDriver/OLED/SSD1306.h"
#include "GWindow/FLTKWindow/FLTKWindow.h"
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
#if 1
    FLTKWindow *win = new FLTKWindow();
    Fl_Window *window = win->GetHandle();
    win->Resize(800, 600);
    window->end();
    window->show(argc, argv);
    return Fl::run();
#else
    Fl_Window *window = new Fl_Window(340, 180);
#if 0
    Fl_Box *box = new Fl_Box(20, 40, 300, 100, "Hello, World!");
    box->box(FL_UP_BOX);
    box->labelfont(FL_BOLD + FL_ITALIC);
    box->labelsize(36);
    box->labeltype(FL_SHADOW_LABEL);
#endif
    window->end();
    window->show(argc, argv);
    return Fl::run();
#endif
}