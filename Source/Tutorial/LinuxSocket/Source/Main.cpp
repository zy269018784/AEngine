#include <iostream>


int TcpClient(int argc, char* argv[]);
int TcpServer(int argc, char* argv[]);

int main(int argc, char* argv[])
{
    if (1 == argc)
        return TcpServer(argc, argv);
    else
        return TcpClient(argc, argv);
    return 0;
}