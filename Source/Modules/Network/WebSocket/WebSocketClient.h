#pragma once
#include <string>
#ifdef PROJECT_USE_BOOST
	#include <boost/beast.hpp>
	#include <boost/asio.hpp>

class WebSocketClient
{
public:
	WebSocketClient();
	~WebSocketClient();
	bool Connect(const std::string& Host, const std::string& Port, const std::string& Path = "/");
private:

	boost::asio::io_context Context;
	boost::asio::ip::tcp::resolver* Resolver;
	boost::beast::websocket::stream<boost::asio::ip::tcp::socket> Handle;

};
#endif