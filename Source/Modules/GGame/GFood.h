#pragma once
#include "GCore/GObject.h"
class GEXPORT GFood : public GObject
{
public:
    GFood(GObject *Parent = nullptr);
    GFood(float InPrice, GObject *Parent = nullptr);
    GFood(GString InName, float InPrice, GObject *Parent = nullptr);
    virtual ~GFood();
    // Getter
    float GetPrice() const;

    // Setter
    void SetPrice(float InPrice);
private:
    float Price;
};



