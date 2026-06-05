#pragma once
#include "GCore/GObject.h"
class GEXPORT GWebSocketServer : public GObject
{
public:
    GWebSocketServer(GObject* Parent = nullptr);
    virtual ~GWebSocketServer();
};



