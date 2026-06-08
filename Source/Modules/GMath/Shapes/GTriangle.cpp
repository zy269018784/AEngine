#include <Shapes/GTriangle.h>
#include <Types/Types.h>
#include <Math.h>
namespace GMath
{
    GTriangle:: GTriangle(GAbstractShape *Parent) : GAbstractShape(Parent)
    {

    }

    GTriangle::GTriangle(const Point3f* p0, const Point3f* p1, const Point3f* p2, const Point2f* uv0, const Point2f* uv1, const Point2f* uv2, GAbstractShape *Parent)
        : GAbstractShape(Parent), p0(*p0), p1(*p1), p2(*p2), uv0(*uv0), uv1(*uv1), uv2(*uv2)
    {
        dp02 = this->p0 - this->p2;
        dp12 = this->p1 - this->p2;
        // 着色法线 = 几何法线
        s_n = g_n = Normal3f(Normalize(Cross(dp02, dp12)));
    }

    GTriangle::~ GTriangle()
    {

    }

    Bounds3f GTriangle::Bounds() const
    {
        return Union(Bounds3f(p0, p1), p2);
    }

    GOptional<ShapeIntersection> GTriangle::Intersect(const Ray& ray, Float tMax) const
    {
        Vector3f dp02 = p0 - p2, dp12 = p1 - p2;
        Point2f uv0 = Point2f(0, 0), uv1 = Point2f(1, 0), uv2 = Point2f(1, 1);
        // 打印 dp02
        std::cout << "dp02 = (" << dp02.x << ", " << dp02.y << ", " << dp02.z << ")" << std::endl;

        // 打印 dp12
        std::cout << "dp12 = (" << dp12.x << ", " << dp12.y << ", " << dp12.z << ")" << std::endl;
        return {};
    }
}