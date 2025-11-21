#pragma once
#include <boost/beast.hpp>
#include <boost/asio.hpp>

class WebSocketServer
{
public:
	WebSocketServer(unsigned short port);
	~WebSocketServer();
	void Run();
private:
	void DoAsyncAccept();
private:
	boost::asio::io_context Context;
	boost::asio::ip::tcp::acceptor Acceptor;

	std::vector<std::thread> Threads;
};