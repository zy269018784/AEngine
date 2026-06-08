#pragma once
#include <GCore/GObject.h>
#include <GCore/GOptional.h>
#include <Intersection/GIntersection.h>
#include <Types/Types.h>
#include <limits>
#include <cmath>
using namespace GCore;
namespace GMath
{
    class GEXPORT GAbstractShape : public GObject
    {
    public:
        GAbstractShape(GObject *Parent = nullptr);
        virtual ~GAbstractShape();
    public:
        virtual Bounds3f Bounds() const = 0;
        virtual GOptional<GShapeIntersection> Intersect(const Ray& ray, Float tMax = Infinity) const = 0;
    };
}

