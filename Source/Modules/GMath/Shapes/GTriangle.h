#pragma once
#include <Shapes/GAbstractShape.h>
namespace GMath
{
    class GEXPORT GTriangle : public GAbstractShape
    {
    public:
        GTriangle(GAbstractShape *Parent = nullptr);
        GTriangle(const Point3f& p0, const Point3f& p1, const Point3f& p2, GAbstractShape *Parent = nullptr);
        virtual ~GTriangle();
    public:
        Bounds3f Bounds() const override final;
        GOptional<ShapeIntersection> Intersect(const Ray& ray, Float tMax = Infinity) const override final;
    private:
        Point3f p0;
        Point3f p1;
        Point3f p2;
    };
}