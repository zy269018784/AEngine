#include "GCore/GObject.h"
#include "GMath/Math.h"
#include "GCG/GVirtualGeometry/GVirtualGeometry.h"
#include "GGame/GGame.h"
#include <iostream>
#include "GDeviceDriver/OLED/SSD1306.h"

int main(int argc, char **argv)
{
    GGame game;
    game.SetName("hello GGame");
    std::cout << game.GetName() << std::endl;

    SSD1306 oled1306(nullptr);
    oled1306.SetName("oled1306");
    std::cout << oled1306.GetName() << std::endl;
}