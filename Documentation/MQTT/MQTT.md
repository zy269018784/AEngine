https://mqtt.org/getting-started/

https://mqtt.org/mqtt-specification/
https://www.mqtt.cn/mqtt-tutorial/hivemq
https://eclipse.dev/paho/
https://docs.oasis-open.org/mqtt/mqtt/v3.1.1/os/mqtt-v3.1.1-os.pdf
https://docs.oasis-open.org/mqtt/mqtt/v5.0/mqtt-v5.0.pdf

MQTT Version:
    5
    3.1.1

Core:
    MQTT Clients 
    MQTT Broker 
    Topic

HIVEMQ:


MQTT offers several key benefits:
    Lightweight and efficient: Requires minimal device resources and network bandwidth
    Bidirectional communication: Enables communication between devices and servers, supporting publishing and subscribing. It also allows broadcasting messages to groups of devices
    Scalability: Supports millions of connected devices in IoT/IIoT systems
    Quality of Service (QoS) levels: Ensures reliable message delivery
    Persistent sessions: Reduces reconnection time over unreliable networks
    Security features: Supports TLS encryption for message confidentiality and authentication protocols for client verification.


MQTT Control Packet

MQTT Control Packet type


    

Client(Publish)                                  Server                                 Client(subscriber)
            CONNECT     ->
        <-  CONNACK 

            PUBLISH     ->                                          PUBLISH     ->        
        <-  PUBACK                                              <-  PUBACK
            PUBREL      ->                                          PUBREL      ->
        <-  PUBCOMP                                             <-  PUBCOMP

                                                                <-  SUBSCRIBE   
                                                                    SUBACK      ->
                                                                
                                                                <-  UNSUBSCRIBE
                                                                    UNSUBACK    ->

            DISCONNECT  ->