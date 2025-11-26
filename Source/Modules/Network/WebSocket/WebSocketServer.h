#pragma once
#include <vector>
#include <thread>
#ifdef PROJECT_USE_BOOST
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
#ifdef PROJECT_USE_BOOST
	boost::asio::io_context Context;
	boost::asio::ip::tcp::acceptor Acceptor;
#endif
	std::vector<std::thread> Threads;
};
#endif