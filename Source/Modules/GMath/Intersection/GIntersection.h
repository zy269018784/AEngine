#pragma once
#include <Types/GTypes.h>
#include <Intersection/GSurfaceInteraction.h>
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
        GPoint3f pObj;
        Float phi;
    };
}