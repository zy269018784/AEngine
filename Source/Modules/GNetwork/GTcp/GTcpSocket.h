#pragma once
#include "GCore/GObject.h"
class GEXPORT GTcpSocket : public GObject
{
public:
    GTcpSocket(GObject* Parent = nullptr);
    virtual ~GTcpSocket();
};



