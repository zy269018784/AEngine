#include "GObject.h"

GObject::GObject(GObject* Parent)
    : Parent(Parent)
{

}

GObject::~GObject()
{

}

GString GObject::GetName() const
{
    return Name;
}

void GObject::SetName(const GString& name)
{
    Name = name;
}