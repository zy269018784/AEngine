#pragma once
#include <GCore/GObject.h>
#include <GCore/GExport.h>
class GEXPORT GAbstractHttpServer : public GObject
{
public:
    GAbstractHttpServer(GObject *Parent = nullptr);
    virtual ~GAbstractHttpServer();
};


