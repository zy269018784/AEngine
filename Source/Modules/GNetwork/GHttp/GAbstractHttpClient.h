#pragma once
#include <GCore/GObject.h>
class GAbstractHttpClient : public GObject
{
public:
    GAbstractHttpClient(GObject *Parent = nullptr);
    virtual ~GAbstractHttpClient();
};


