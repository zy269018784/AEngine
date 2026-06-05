#pragma once
#include "GCore/GObject.h"
class GRegister32 : public GObject
{
public:
    GRegister32(GObject* Parent = nullptr);
    void SetBits(int Index);
    void ClearBits(int Index);
};

