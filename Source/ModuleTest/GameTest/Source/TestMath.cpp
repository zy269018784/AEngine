#include "GMath/Math.h"
#include <iostream>
#include <cstring>
#include <thread>
#include <chrono>
#include <Types/Vector2.h>
using namespace GMath;
int TestMath(int argc, char** argv)
{
    Vector2<float> v1(1, 2);
    Vector2<float> v2(3, 4);
    v1 += v2;
    std::cout << v1.x << " " << v1.y << std::endl;
    return 0;
}