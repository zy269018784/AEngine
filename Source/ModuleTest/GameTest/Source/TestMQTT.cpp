#include "GNetwork/GMQTT/GMqttClient.h"
#include <iostream>
#include <cstring>

#include <iostream>
#include <thread>
#include <chrono>
#if 0
static bool ErrorHandler(MQTTHandle *handle, MQTTConfig *config, MQTTErrorCode code)
{
  //  std::cout << "code " << code << std::endl;
    std::cout << "ErrorHandler " << std::endl;
}

/** Event handler callback */
static void EventHandler(MQTTHandle *handle, void *context)
{
    std::cout << "EventHandler " << std::endl;
}

static void PublishEventHandler(MQTTHandle *handle, char *topic, char *payload)
{
    //if (topic && payload && strlen(payload) > 0)
        std::cout << "PublishEventHandler " << std::endl;
}
#endif
int TestMQTT(int argc, char **argv)
{
#if 0
    GMqttClient *Client = new GMqttClient;
    MQTTConfig Config;
    Config.hostname = "localhost";
    Config.port = 1883;
    Config.username = NULL;
    Config.password = NULL;
    Config.client_id = "test_client";
    char *topic = new char[50];
    strcpy(topic, "test");

    std::string topic_str = "test";

    MQTTStatus status;
    std::cout << "debug 1" << std::endl;
    Client->Connect(&Config, EventHandler, nullptr, ErrorHandler);
    std::cout << "debug 2" << std::endl;
    status = Client->Subscribe(topic, MQTT_QOS_2, &PublishEventHandler);
    std::cout << "debug 3 " << status << std::endl;
   // delete Client;
    std::this_thread::sleep_for(std::chrono::seconds(1000));
#endif
    return 0;
}