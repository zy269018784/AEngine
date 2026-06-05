
#include "GCore/GObject.h"
#include "GMath/Math.h"
#include <iostream>
#include "GCG/GVirtualGeometry/GVirtualGeometry.h"

int main(int argc, char **argv)
{
    GObject obj;
    obj.SetName("Hello");
    std::cout << obj.GetName() << std::endl;

    GVirtualGeometry vg;
    vg.SetName("hello GVirtualGeometry");
    std::cout << vg.GetName() << std::endl;
    HelloMath();
}