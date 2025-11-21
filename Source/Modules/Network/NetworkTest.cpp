#include "Network/WebSocket/WebSocketServer.h"
#include "Network/WebSocket/WebSocketClient.h"
#include <thread>
int NetworkTest(int argc, char** argv)
{
    return 0;
}

int WebSocketServerTest(int argc, char** argv)
{
    WebSocketServer Server(std::stoi(argv[1]));
    Server.Run();
    return 0;
}

int WebSocketClientTest(int argc, char** argv)
{
    WebSocketClient Client;
    Client.Connect(argv[1], argv[2], argv[3]);
    std::this_thread::sleep_for(std::chrono::seconds(20));
    return 0;
}
