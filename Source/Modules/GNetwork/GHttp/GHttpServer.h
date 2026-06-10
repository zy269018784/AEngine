#pragma once
#include <GHttp/GAbstractHttpServer.h>
#include <httplib.h>
class GHttpServer : public GAbstractHttpServer
{
public:
    GHttpServer(GAbstractHttpServer *Parent = nullptr);
    virtual ~GHttpServer();
private:
    httplib::Server Handle;
};
