#include <iostream>


int TcpClient();
int TcpServer();

int main(int argc, char* argv[])
{
    if (1 == argc)
        return TcpServer();
    else
        return TcpClient();
    return 0;
}