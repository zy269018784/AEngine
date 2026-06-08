#pragma once
#include <Types/Types.h>
#include <Intersection/SurfaceInteraction.h>
namespace GMath
{
    // ShapeIntersection Definition
    struct ShapeIntersection {
        SurfaceInteraction intr;
        Float tHit;
    };
    // QuadricIntersection Definition
    struct QuadricIntersection {
        Float tHit;
        Point3f pObj;
        Float phi;
    };
}