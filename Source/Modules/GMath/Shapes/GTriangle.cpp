#include <Shapes/GTriangle.h>
#include <Math.h>
namespace GMath
{
    GTriangle:: GTriangle(GAbstractShape *Parent) : GAbstractShape(Parent)
    {

    }

    GTriangle::~ GTriangle()
    {

    }

    Bounds3f GTriangle::Bounds() const
    {
        return Union(Bounds3f(p0, p1), p2);
    }
}