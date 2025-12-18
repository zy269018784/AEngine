#include <mqtt/mqtt.h>
#include <stdio.h>
#include <string.h>
// 错误处理回调
bool on_error(MQTTHandle *handle, MQTTConfig *config,
             MQTTErrorCode code) {

    printf("连接错误: 代码=%d\n", code);

    // 修改配置并尝试重连
    if (code == MQTT_Error_Connection_Refused && config->port == 1883) {
        printf("尝试使用 TLS 端口 8883\n");
        config->port = 8883;  // 改为 TLS 端口
        return false;  // 保持句柄，库会尝试重连
    }

    return true;  // 释放句柄，不再重连
}

// 消息接收回调
void on_message(MQTTHandle *handle, char *topic, char *payload)
{
    printf("收到消息: topic=%s, payload=%s\n", topic, payload);
}


void on_connected(MQTTHandle *handle, void *context)
{
    printf("连接成功！上下文: %s\n", (char *)context);

    // 订阅主题
    mqtt_subscribe(handle, "test/topic", MQTT_QOS_1, on_message);

    // 发布欢迎消息
    mqtt_publish(handle, "test/topic", "Hello MQTT!",
                 MQTT_QOS_1, NULL);
}


int MQTTMain()
{
    MQTTConfig config = {0};
    config.hostname = strdup("test.mosquitto.org");
    config.port = 1883;  // 非加密端口
    config.client_id = strdup("my_client_001");
    config.clean_session = true;
    config.username = NULL;  // 匿名连接
    config.password = NULL;

    // 遗愿配置
    config.last_will_topic = strdup("clients/my_client_001/status");
    config.last_will_message = strdup("disconnected");
    config.last_will_retain = true;
    char *context = "这是一个测试客户端";
    MQTTHandle *Handle = mqtt_connect(&config, on_connected, context, on_error);

    if (!Handle) {
        printf("无法创建 MQTT 连接\n");
        return 1;
    }

    printf("连接已启动，等待事件...\n");

    while (1);

    // 清理
    if (Handle)
    {
        mqtt_disconnect(Handle, NULL, NULL);
    }

    return 0;
}