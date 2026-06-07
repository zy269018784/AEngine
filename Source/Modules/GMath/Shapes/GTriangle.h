#pragma once
#include <Shapes/GAbstractShape.h>

class GEXPORT GTriangle : public GAbstractShape
{
public:
    GTriangle(GAbstractShape *Parent = nullptr);
    virtual ~GTriangle();
};