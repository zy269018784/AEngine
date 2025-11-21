#include <curl/curl.h>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include "http.h"
int http_main(int argc, char** argv)
{
    try {
        if (argc != 4) {
            std::cerr << "Usage: " << argv[0] << " <address> <port> <doc_root>\n";
            return 1;
        }

        auto const address = net::ip::make_address(argv[1]);
        auto const port = static_cast<unsigned short>(std::atoi(argv[2]));
        auto const doc_root = std::string(argv[3]);

        net::io_context ioc{ 1 };

        FileServer server{ ioc, {address, port}, doc_root };
        server.start_accept();

        std::cout << "File server running on " << address << ":" << port
            << "\nDocument root: " << doc_root << std::endl;

        ioc.run();
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}