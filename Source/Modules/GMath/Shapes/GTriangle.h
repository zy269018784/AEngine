#pragma once
#include <GMath/Shapes/GAbstractShape.h>
namespace GMath
{
    struct Triangle
    {
    public:
        GPoint3f* p0 = nullptr;
        GPoint3f* p1 = nullptr;
        GPoint3f* p2 = nullptr;
        GPoint2f* uv0 = nullptr;
        GPoint2f* uv1 = nullptr;
        GPoint2f* uv2 = nullptr;
    };
    class GEXPORT GTriangle : public GAbstractShape
    {

    public:
        GTriangle(GAbstractShape *Parent = nullptr);
        GTriangle(const GPoint3f* p0,  const GPoint3f* p1,  const GPoint3f* p2,
                  const GPoint2f* uv0 = nullptr, const GPoint2f* uv1 = nullptr, const GPoint2f* uv2 = nullptr,
                  GAbstractShape *Parent = nullptr);
        virtual ~GTriangle();
    public:
        GBounds3f Bounds() const override final;
        GOptional<GShapeIntersection> Intersect(const GRay& ray, Float tMax = Infinity) const override final;
    private:
        GPoint3f p0;
        GPoint3f p1;
        GPoint3f p2;
        GPoint2f uv0;
        GPoint2f uv1;
        GPoint2f uv2;
        //
        GVector3f dp02;
        GVector3f dp12;
        // 几何法线
        GNormal3f g_n;
        GVector3f g_dpdu, g_dpdv;
        GNormal3f g_dndu, g_dndv;
        // 着色法线
        GNormal3f s_n;
        GVector3f s_dpdu, s_dpdv;
        GNormal3f s_dndu, s_dndv;
    };
}