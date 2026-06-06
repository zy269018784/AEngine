#pragma once
#include "mqtt/mqtt.h"
#include "GCore/GObject.h"
#include "GCore/GString.h"
class GEXPORT GMqttClient : public GObject
{
public:
    GMqttClient(GObject* Parent = nullptr);
    virtual ~GMqttClient();
#if 0
    MQTTStatus Subscribe(GString Topic, MQTTQosLevel QosLevel, MQTTPublishEventHandler Callback);
    MQTTStatus Publish(GString Topic, GString Payload, MQTTQosLevel QosLevel, MQTTPublishEventHandler Callback);
    MQTTStatus Unsubscribe(GString Topic);
    MQTTStatus Disconnect(MQTTEventHandler Callback, void *CallbackContext);
    void Connect(MQTTConfig *Config, MQTTEventHandler Callback, void *CallbackContext, MQTTErrorHandler ErrorCallback);
#endif

private:
    MQTTHandle *Handle;
};

