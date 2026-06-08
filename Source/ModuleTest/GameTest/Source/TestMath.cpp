#include "GMath/Math.h"
#include <iostream>
#include <cstring>
#include <thread>
#include <chrono>
#include <Types/GVector2.h>
#include <Types/GVector3.h>
#include <Types/GBounds2.h>
#include <Types/GBounds3.h>
#include <Types/GNormal2.h>
#include <Types/GNormal3.h>
#include <Types/GPoint2.h>
#include <Types/GPoint3.h>
#include <Shapes/GTriangle.h>
using namespace GMath;

int TestGTriangle()
{
    Point3f p0(0, 0,     0);
    Point3f p1(100, 0,   100);
    Point3f p2(100, 100, 0);
    Point2f uv0(0.3, 0.2);
    Point2f uv1(0.8, 0.6);
    Point2f uv2(0.1, 0.98);
    GAbstractShape *Shape = new GTriangle(&p0, &p1, &p2, &uv0, &uv1, &uv2);
    auto Bounds = Shape->Bounds();
    std::cout << Bounds.pMin.x << ", " << Bounds.pMin.y << ", " << Bounds.pMin.z << std::endl;
    std::cout << Bounds.pMax.x << ", " << Bounds.pMax.y << ", " << Bounds.pMax.z << std::endl;

    Ray ray;
    Shape->Intersect(ray);
    return 0;
}

int TestMath(int argc, char** argv)
{
    return TestGTriangle();
    std::cout << "========== Vector2 测试 ==========" << std::endl;
    Vector2<float> v1(1, 2);
    Vector2<float> v2(3, 4);
    v1 += v2;
    std::cout << "v1 += v2 -> v1 = (" << v1.x << ", " << v1.y << ")" << std::endl;
    std::cout << "MinComponentValue(v1) = " << MinComponentValue(v1) << ", MinComponentIndex(v1) = " << MinComponentIndex(v1) << std::endl;
    std::cout << "MaxComponentValue(v1) = " << MaxComponentValue(v1) << ", MaxComponentIndex(v1) = " << MaxComponentIndex(v1) << std::endl;

    std::cout << "\n========== Vector3 测试 ==========" << std::endl;
    Vector3<float> v3(1, 2, 3);
    Vector3<float> v4(3, 4, 5);
    v3 += v4;
    std::cout << "v3 += v4 -> v3 = (" << v3.x << ", " << v3.y << ", " << v3.z << ")" << std::endl;
    std::cout << "MinComponentValue(v3) = " << MinComponentValue(v3) << ", MinComponentIndex(v4) = " << MinComponentIndex(v4) << std::endl;
    std::cout << "MaxComponentValue(v3) = " << MaxComponentValue(v3) << ", MaxComponentIndex(v4) = " << MaxComponentIndex(v4) << std::endl;

    std::cout << "\n========== Point2 测试 ==========" << std::endl;
    Point2<float> p1(1, 2);
    Point2<float> p2(3, 4);
    p1 += Vector2<float>(3, 4);
    std::cout << "p1 += Vector2(3,4) -> p1 = (" << p1.x << ", " << p1.y << ")" << std::endl;
    std::cout << "MinComponentValue(p1) = " << MinComponentValue(p1) << ", MinComponentIndex(p1) = " << MinComponentIndex(p1) << std::endl;
    std::cout << "MaxComponentValue(p1) = " << MaxComponentValue(p1) << ", MaxComponentIndex(p1) = " << MaxComponentIndex(p1) << std::endl;

    std::cout << "\n========== Point3 测试 ==========" << std::endl;
    Point3<float> p3(1, 2, 3);
    Point3<float> p4(3, 4, 5);
    p3 += Vector3<float>(3, 4, 5);
    std::cout << "p3 += Vector3(3,4,5) -> p3 = (" << p3.x << ", " << p3.y << ", " << p3.z << ")" << std::endl;
    std::cout << "MinComponentValue(p3) = " << MinComponentValue(p3) << ", MinComponentIndex(p4) = " << MinComponentIndex(p4) << std::endl;
    std::cout << "MaxComponentValue(p3) = " << MaxComponentValue(p3) << ", MaxComponentIndex(p4) = " << MaxComponentIndex(p4) << std::endl;

    std::cout << "\n========== Normal2 测试 ==========" << std::endl;
    Normal2<float> n1(1, 2);
    Normal2<float> n2(3, 4);
    n1 += n2;
    std::cout << "n1 += n2 -> n1 = (" << n1.x << ", " << n1.y << ")" << std::endl;
    std::cout << "MinComponentValue(n1) = " << MinComponentValue(n1) << ", MinComponentIndex(n1) = " << MinComponentIndex(n1) << std::endl;
    std::cout << "MaxComponentValue(n1) = " << MaxComponentValue(n1) << ", MaxComponentIndex(n1) = " << MaxComponentIndex(n1) << std::endl;

    std::cout << "\n========== Normal3 测试 ==========" << std::endl;
    Normal3<float> n3(1, 2, 3);
    Normal3<float> n4(3, 4, 5);
    n3 += n4;
    std::cout << "n3 += n4 -> n3 = (" << n3.x << ", " << n3.y << ", " << n3.z << ")" << std::endl;
    std::cout << "MinComponentValue(n3) = " << MinComponentValue(n3) << ", MinComponentIndex(n4) = " << MinComponentIndex(n4) << std::endl;
    std::cout << "MaxComponentValue(n3) = " << MaxComponentValue(n3) << ", MaxComponentIndex(n4) = " << MaxComponentIndex(n4) << std::endl;

    return 0;
}