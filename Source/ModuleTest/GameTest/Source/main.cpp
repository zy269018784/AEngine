#include "GCore/GObject.h"
#include "GMath/Math.h"
#include "GCG/GVirtualGeometry/GVirtualGeometry.h"
#include "GGame/GGame.h"
#include <iostream>


int main(int argc, char **argv)
{
    GGame game;
    game.SetName("hello GGame");
    std::cout << game.GetName() << std::endl;
}