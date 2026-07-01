#if 0
#include "GMath/Math.h"
#include <iostream>
#include <cstring>
#include <thread>
#include <chrono>
#include <GMath/Types/GVector2.h>
#include <GMath/Types/GVector3.h>
#include <GMath/Types/GBounds2.h>
#include <GMath/Types/GBounds3.h>
#include <GMath/Types/GNormal2.h>
#include <GMath/Types/GNormal3.h>
#include <GMath/Types/GPoint2.h>
#include <GMath/Types/GPoint3.h>
#include <GMath/Shapes/GTriangle.h>
#include <GMath/Shapes/GAbstractShape.h>
using namespace GMath;

int TestGTriangle()
{
    GPoint3f p0(0, 0,     0);
    GPoint3f p1(100, 0,   100);
    GPoint3f p2(100, 100, 0);
    GPoint2f uv0(0.3, 0.2);
    GPoint2f uv1(0.8, 0.6);
    GPoint2f uv2(0.1, 0.98);
    GAbstractShape *Shape = new GTriangle(&p0, &p1, &p2, &uv0, &uv1, &uv2);
    auto Bounds = Shape->Bounds();
    std::cout << Bounds.pMin.x << ", " << Bounds.pMin.y << ", " << Bounds.pMin.z << std::endl;
    std::cout << Bounds.pMax.x << ", " << Bounds.pMax.y << ", " << Bounds.pMax.z << std::endl;

    GRay ray;
    Shape->Intersect(ray);
    return 0;
}

int TestMath(int argc, char** argv)
{
    return TestGTriangle();
    std::cout << "========== GVector2 测试 ==========" << std::endl;
    GVector2<float> v1(1, 2);
    GVector2<float> v2(3, 4);
    v1 += v2;
    std::cout << "v1 += v2 -> v1 = (" << v1.x << ", " << v1.y << ")" << std::endl;
    std::cout << "MinComponentValue(v1) = " << MinComponentValue(v1) << ", MinComponentIndex(v1) = " << MinComponentIndex(v1) << std::endl;
    std::cout << "MaxComponentValue(v1) = " << MaxComponentValue(v1) << ", MaxComponentIndex(v1) = " << MaxComponentIndex(v1) << std::endl;

    std::cout << "\n========== GVector3 测试 ==========" << std::endl;
    GVector3<float> v3(1, 2, 3);
    GVector3<float> v4(3, 4, 5);
    v3 += v4;
    std::cout << "v3 += v4 -> v3 = (" << v3.x << ", " << v3.y << ", " << v3.z << ")" << std::endl;
    std::cout << "MinComponentValue(v3) = " << MinComponentValue(v3) << ", MinComponentIndex(v4) = " << MinComponentIndex(v4) << std::endl;
    std::cout << "MaxComponentValue(v3) = " << MaxComponentValue(v3) << ", MaxComponentIndex(v4) = " << MaxComponentIndex(v4) << std::endl;

    std::cout << "\n========== GPoint2 测试 ==========" << std::endl;
    GPoint2<float> p1(1, 2);
    GPoint2<float> p2(3, 4);
    p1 += GVector2<float>(3, 4);
    std::cout << "p1 += GVector2(3,4) -> p1 = (" << p1.x << ", " << p1.y << ")" << std::endl;
    std::cout << "MinComponentValue(p1) = " << MinComponentValue(p1) << ", MinComponentIndex(p1) = " << MinComponentIndex(p1) << std::endl;
    std::cout << "MaxComponentValue(p1) = " << MaxComponentValue(p1) << ", MaxComponentIndex(p1) = " << MaxComponentIndex(p1) << std::endl;

    std::cout << "\n========== GPoint3 测试 ==========" << std::endl;
    GPoint3<float> p3(1, 2, 3);
    GPoint3<float> p4(3, 4, 5);
    p3 += GVector3<float>(3, 4, 5);
    std::cout << "p3 += GVector3(3,4,5) -> p3 = (" << p3.x << ", " << p3.y << ", " << p3.z << ")" << std::endl;
    std::cout << "MinComponentValue(p3) = " << MinComponentValue(p3) << ", MinComponentIndex(p4) = " << MinComponentIndex(p4) << std::endl;
    std::cout << "MaxComponentValue(p3) = " << MaxComponentValue(p3) << ", MaxComponentIndex(p4) = " << MaxComponentIndex(p4) << std::endl;

    std::cout << "\n========== GNormal2 测试 ==========" << std::endl;
    GNormal2<float> n1(1, 2);
    GNormal2<float> n2(3, 4);
    n1 += n2;
    std::cout << "n1 += n2 -> n1 = (" << n1.x << ", " << n1.y << ")" << std::endl;
    std::cout << "MinComponentValue(n1) = " << MinComponentValue(n1) << ", MinComponentIndex(n1) = " << MinComponentIndex(n1) << std::endl;
    std::cout << "MaxComponentValue(n1) = " << MaxComponentValue(n1) << ", MaxComponentIndex(n1) = " << MaxComponentIndex(n1) << std::endl;

    std::cout << "\n========== GNormal3 测试 ==========" << std::endl;
    GNormal3<float> n3(1, 2, 3);
    GNormal3<float> n4(3, 4, 5);
    n3 += n4;
    std::cout << "n3 += n4 -> n3 = (" << n3.x << ", " << n3.y << ", " << n3.z << ")" << std::endl;
    std::cout << "MinComponentValue(n3) = " << MinComponentValue(n3) << ", MinComponentIndex(n4) = " << MinComponentIndex(n4) << std::endl;
    std::cout << "MaxComponentValue(n3) = " << MaxComponentValue(n3) << ", MaxComponentIndex(n4) = " << MaxComponentIndex(n4) << std::endl;

    return 0;
}
#endif