#pragma once
#include "GCore/GObject.h"
class GEXPORT GUdpSocket : public GObject
{
public:
    GUdpSocket(GObject* Parent = nullptr);
    virtual ~GUdpSocket();
};



