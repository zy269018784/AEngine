#pragma once
#include "GExport.h"
#include "GString.h"
class GEXPORT GObject
{
public:
    GObject(GObject* Parent = nullptr);
    virtual ~GObject();
    GString GetName() const;
    void SetName(const GString& name);
private:
    GString Name;
    GObject* Parent;
};



