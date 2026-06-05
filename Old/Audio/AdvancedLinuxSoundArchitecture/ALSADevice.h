#pragma once
class ALSADevice
{
public:
    ALSADevice(int CardIndex = -1);
    ~ALSADevice();
    int GetHandle() const;
    char *GetName() const;
    char *GetLongName() const;
private:
    int Handle;
    char *Name;
    char *LongName;
};


