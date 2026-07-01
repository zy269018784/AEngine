#pragma once
#include <GCore/GObject.h>
#include <GCore/GExport.h>
class GEXPORT GAbstractHttpClient : public GObject
{
public:
    GAbstractHttpClient(GObject *Parent = nullptr);
    virtual ~GAbstractHttpClient();
};


