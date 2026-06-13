#pragma once
#include <GHttp/GAbstractHttpServer.h>
#include <httplib.h>

class GHttpServer1 : public GAbstractHttpServer
{
public:
    GHttpServer1(GAbstractHttpServer *Parent = nullptr);
    virtual ~GHttpServer1();
    httplib::Server *GetHandle() const;
private:
    httplib::Server *Handle;
};


