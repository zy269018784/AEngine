#include "GGame/GFood.h"

GFood::GFood(GObject *Parent)
    : GObject(Parent)
{
    SetPrice(0);
}

GFood::GFood(float InPrice, GObject *Parent)
    : GObject(Parent)
{
    SetPrice(InPrice);
}


GFood::GFood(GString InName, float InPrice, GObject *Parent)
    : GObject(Parent)
{
    SetPrice(InPrice);
    SetName(InName);
}



GFood::~GFood() {

}

// Getter 实现
float GFood::GetPrice() const
{
    return Price;
}

// Setter 实现
void GFood::SetPrice(float InPrice)
{
    Price = InPrice;
}