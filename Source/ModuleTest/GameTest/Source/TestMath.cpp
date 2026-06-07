#include "GMath/Math.h"
#include <iostream>
#include <cstring>
#include <thread>
#include <chrono>
#include <Types/Vector2.h>
#include <Types/Vector3.h>
using namespace GMath;
int TestMath(int argc, char** argv)
{
    Vector2<float> v1(1, 2);
    Vector2<float> v2(3, 4);
    v1 += v2;
    std::cout << v1.x << " " << v1.y << std::endl;
    std::cout << MinComponentValue(v1) << " " << MinComponentIndex(v1) << std::endl;
    std::cout << MaxComponentValue(v1) << " " << MaxComponentIndex(v1) << std::endl;

    Vector3<float> v3(1, 2, 3);
    Vector3<float> v4(3, 4, 5);
    v3 += v4;
    std::cout << v3.x << " " << v3.y << " " << v3.z << std::endl;
    std::cout << MinComponentValue(v3) << " " << MinComponentIndex(v4) << std::endl;
    std::cout << MaxComponentValue(v3) << " " << MaxComponentIndex(v4) << std::endl;
    return 0;
}