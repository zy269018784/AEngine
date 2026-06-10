#pragma once
#include <GCore/GObject.h>
class GAbstractHttpServer : public GObject
{
public:
    GAbstractHttpServer(GObject *Parent = nullptr);
    virtual ~GAbstractHttpServer();
};


