#pragma once
#include "GCore/GObject.h"
class GEXPORT GTcpServer : public GObject
{
public:
    GTcpServer(GObject* Parent = nullptr);
    virtual ~GTcpServer();
};



