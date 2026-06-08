#pragma once
#include <Shapes/GAbstractShape.h>
namespace GMath
{
    struct Triangle
    {
    public:
        Point3f* p0 = nullptr;
        Point3f* p1 = nullptr;
        Point3f* p2 = nullptr;
        Point2f* uv0 = nullptr;
        Point2f* uv1 = nullptr;
        Point2f* uv2 = nullptr;
    };
    class GEXPORT GTriangle : public GAbstractShape
    {

    public:
        GTriangle(GAbstractShape *Parent = nullptr);
        GTriangle(const Point3f* p0, const Point3f* p1, const Point3f* p2,
                  const Point2f* uv0 = nullptr, const Point2f* uv1 = nullptr, const Point2f* uv2 = nullptr,
                  GAbstractShape *Parent = nullptr);
        virtual ~GTriangle();
    public:
        Bounds3f Bounds() const override final;
        GOptional<ShapeIntersection> Intersect(const Ray& ray, Float tMax = Infinity) const override final;
    private:
        Point3f p0;
        Point3f p1;
        Point3f p2;
        Point2f uv0;
        Point2f uv1;
        Point2f uv2;
        //
        Vector3f dp02;
        Vector3f dp12;
        // 几何法线
        Normal3f g_n;
        Vector3f g_dpdu, g_dpdv;
        Normal3f g_dndu, g_dndv;
        // 着色法线
        Normal3f s_n;
        Vector3f s_dpdu, s_dpdv;
        Normal3f s_dndu, s_dndv;
    };
}