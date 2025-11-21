#include "WebSocketClient.h"
#include <iostream>
WebSocketClient::WebSocketClient()
	:   Context(),
        Handle(Context)
{
	boost::asio::ip::tcp::resolver* Resolver = new boost::asio::ip::tcp::resolver(Context);
}

WebSocketClient::~WebSocketClient()
{
	delete Resolver;
}

void handle_write(const boost::system::error_code& ec, std::size_t bytes_transferred) {
    if (!ec) {
        std::cout << "成功写入 " << bytes_transferred << " 字节" << std::endl;
    }
    else {
        std::cout << "写入错误: " << ec.message() << std::endl;
    }
}

bool WebSocketClient::Connect(const std::string& Host, const std::string& Port, const std::string& Path)
{
	auto const results = Resolver->resolve(Host, Port);

    // 建立 TCP 连接
    boost::asio::connect(Handle.next_layer(), results);

    
    // WebSocket 握手
    Handle.handshake(Host, Path);

    Handle.text(true);
    Handle.async_write_some(true, boost::asio::buffer("hello"), handle_write);
    std::cout << "Connected to " << Host << ":" << Port << Path << std::endl;
    return true;
}