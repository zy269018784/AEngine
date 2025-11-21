#include "WebSocketServer.h"
#include <iostream>
WebSocketServer::WebSocketServer(unsigned short port)
    :   
        Context(),
        Acceptor(Context, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port))
{

}

WebSocketServer::~WebSocketServer()
{

}

void WebSocketServer::DoAsyncAccept()
{
    Acceptor.async_accept(
        [this](boost::beast::error_code ec, boost::asio::ip::tcp::socket socket) 
        {
            if (!ec) 
            {
                std::cout << "remote_endpoint " 
                    << socket.remote_endpoint().address().to_string() << " "
                    << socket.remote_endpoint().port() << " "
                    << std::endl;  
                
                char buffer[1024];
                boost::system::error_code ec;
                std::cout << "test 1" << std::endl;
                boost::beast::websocket::stream<boost::asio::ip::tcp::socket> WebSocket(std::move(socket));
                std::cout << "test 2" << std::endl;
                if (WebSocket.got_text()) 
                { 
                    std::cout << "test 3" << std::endl;
                    int n = WebSocket.read_some(boost::asio::buffer(buffer), ec);
                    std::cout << buffer << std::endl;
                    std::cout << "test 4 " << ec.message()  << " n " << n << std::endl;
                }
                else
                {

                    std::cout << "WebSocket.got_binary " << std::endl;
                }
                std::cout << "test 5" << std::endl;
            }
            DoAsyncAccept();
        }
    );
}

void WebSocketServer::Run()
{
    DoAsyncAccept();
    int n = std::thread::hardware_concurrency();
    Threads.reserve(std::thread::hardware_concurrency());
    for (int i = 0; i < n; ++i)
    {
        Threads.emplace_back([this] { Context.run(); });
    }

    std::cout << "WebSocket server running on port " << Acceptor.local_endpoint().port()
        << " with " << Threads.size() << " threads" << std::endl;

    for (auto& Thread : Threads) 
    {
        Thread.join();
    }
}