#pragma once
#include <GCore/GObject.h>
class GEXPORT GAbstractShape : public GObject
{
public:
    GAbstractShape(GObject *Parent = nullptr);
    virtual ~GAbstractShape();
};

