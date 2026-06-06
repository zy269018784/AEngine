#include "GMqttClient.h"

GMqttClient::GMqttClient(GObject* Parent)
    : GObject(Parent)
{

}

GMqttClient::~GMqttClient()
{

}
#if 0
MQTTStatus GMqttClient::Subscribe(GString Topic, MQTTQosLevel QosLevel, MQTTPublishEventHandler Callback)
{
    return mqtt_subscribe(Handle, Topic.Data(), QosLevel, Callback);
}

MQTTStatus GMqttClient::Publish(GString Topic, GString Payload, MQTTQosLevel QosLevel, MQTTPublishEventHandler Callback)
{
    return mqtt_publish(Handle, Topic.Data(), Payload.Data(), QosLevel, Callback);
}

MQTTStatus GMqttClient::Unsubscribe(GString Topic)
{
    return mqtt_unsubscribe(Handle, Topic.Data());
}

MQTTStatus GMqttClient::Disconnect(MQTTEventHandler Callback, void *CallbackContext)
{
    return mqtt_disconnect(Handle, Callback, CallbackContext);
}

void GMqttClient::Connect(MQTTConfig *Config, MQTTEventHandler Callback, void *CallbackContext, MQTTErrorHandler ErrorCallback)
{
    Handle = mqtt_connect(Config, Callback, CallbackContext, ErrorCallback);
}
#endif