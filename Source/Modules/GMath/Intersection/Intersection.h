#pragma once
#include <Types/Types.h>
#include <Intersection/SurfaceInteraction.h>
namespace GMath
{
    // ShapeIntersection Definition
    struct GShapeIntersection {
        GSurfaceInteraction intr;
        Float tHit;
    };
    // QuadricIntersection Definition
    struct GQuadricIntersection {
        Float tHit;
        Point3f pObj;
        Float phi;
    };
}