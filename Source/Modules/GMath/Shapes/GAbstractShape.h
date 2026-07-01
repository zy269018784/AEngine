#pragma once
#include <GCore/GObject.h>
#include <GCore/GOptional.h>
#include <GMath/Intersection/GIntersection.h>
#include <GMath/Types/GTypes.h>
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
        virtual GBounds3f Bounds() const = 0;
        virtual GOptional<GShapeIntersection> Intersect(const GRay& ray, Float tMax = Infinity) const = 0;
    };
}

