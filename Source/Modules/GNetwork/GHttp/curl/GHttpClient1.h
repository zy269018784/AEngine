#pragma once
#include <GHttp/GAbstractHttpClient.h>


class GHttpClient1 : public GAbstractHttpClient
{
public:
    GHttpClient1(GAbstractHttpClient *Parent = nullptr);
    virtual ~GHttpClient1();
private:

};


