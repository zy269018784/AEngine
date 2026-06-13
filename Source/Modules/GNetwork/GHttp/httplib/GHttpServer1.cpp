#include "GHttpServer1.h"

GHttpServer1::GHttpServer1(GAbstractHttpServer *Parent)
    : GAbstractHttpServer(Parent)
{
    Handle = new httplib::Server;
}

GHttpServer1::~GHttpServer1()
{
    delete Handle;
}

httplib::Server *GHttpServer1::GetHandle() const
{
    return Handle;
}