#pragma once
#include "AL/al.h"
class ALListener{
public:
    ALListener();
    ~ALListener();
    void SetGain(float Value);
    void SetPosition(float X, float Y, float Z);
    void SetVelocity(float X, float Y, float Z);
    void SetOrientation(float AT_X, float AT_Y, float AT_Z, float UP_X, float UP_Y, float UP_Z);
};
