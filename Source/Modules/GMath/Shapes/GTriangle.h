#pragma once
#include <Shapes/GAbstractShape.h>
namespace GMath
{
    class GEXPORT GTriangle : public GAbstractShape
    {
    public:
        GTriangle(GAbstractShape *Parent = nullptr);
        virtual ~GTriangle();
    public:
        virtual Bounds3f Bounds() const override final;
    private:
        Point3f p0;
        Point3f p1;
        Point3f p2;
    };
}