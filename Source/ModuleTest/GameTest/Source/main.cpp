#include "GCore/GObject.h"
#include "GMath/Math.h"
#include "GCG/GVirtualGeometry/GVirtualGeometry.h"
#include "GGame/GGame.h"
#include "GGame/GFood.h"
#include <iostream>
#include "GDeviceDriver/OLED/SSD1306.h"
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
}