#pragma once
#include <GCore/GObject.h>
#include <Types/Types.h>
namespace GMath
{
    class GEXPORT GAbstractShape : public GObject
    {
    public:
        GAbstractShape(GObject *Parent = nullptr);
        virtual ~GAbstractShape();
    public:
        virtual Bounds3f Bounds() const = 0;
    };
}

