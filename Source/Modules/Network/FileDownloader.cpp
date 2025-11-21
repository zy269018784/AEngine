#define BOOST_ASIO_DISABLE_SSL

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio.hpp>
//#include <boost/asio/ssl.hpp>
#include <fstream>
#include <iostream>
#include <string>
#include <filesystem>

namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;
namespace ssl = net::ssl;
using tcp = boost::asio::ip::tcp;
namespace fs = std::filesystem;

class FileDownloader {
public:
    FileDownloader(net::io_context& ioc) : ioc_(ioc) {}

    // 同步下载文件
    bool download_file(const std::string& url, const std::string& output_path) {
        try {
            // 解析 URL
            auto [host, port, target] = parse_url(url);

            // 创建 TCP 解析器和流
            tcp::resolver resolver(ioc_);
            beast::tcp_stream stream(ioc_);

            // 解析域名
            auto const results = resolver.resolve(host, port);

            // 连接服务器
            stream.connect(results);

            // 设置 HTTP GET 请求
            http::request<http::string_body> req{ http::verb::get, target, 11 };
            req.set(http::field::host, host);
            req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);

            // 发送请求
            http::write(stream, req);

            // 接收响应
            beast::flat_buffer buffer;
            http::response<http::dynamic_body> res;
            http::read(stream, buffer, res);

            // 检查响应状态
            if (res.result() != http::status::ok) {
                std::cerr << "HTTP error: " << res.result() << std::endl;
                return false;
            }

            // 保存文件
            std::ofstream file(output_path, std::ios::binary);
            if (!file) {
                std::cerr << "Cannot create file: " << output_path << std::endl;
                return false;
            }

            // 写入文件
            auto& body = res.body();
            for (auto const& chunk : body.data()) {
                file.write(static_cast<const char*>(chunk.data()), chunk.size());
            }

            file.close();

            // 优雅关闭连接
            beast::error_code ec;
            stream.socket().shutdown(tcp::socket::shutdown_both, ec);
            if (ec && ec != beast::errc::not_connected) {
                throw beast::system_error{ ec };
            }

            std::cout << "File downloaded successfully: " << output_path << std::endl;
            return true;

        }
        catch (const std::exception& e) {
            std::cerr << "Download failed: " << e.what() << std::endl;
            return false;
        }
    }

private:
    net::io_context& ioc_;

    // 解析 URL，返回主机、端口和路径
    std::tuple<std::string, std::string, std::string> parse_url(const std::string& url) {
        std::string protocol, host, port, target;

        // 提取协议
        size_t protocol_end = url.find("://");
        if (protocol_end != std::string::npos) {
            protocol = url.substr(0, protocol_end);
            protocol_end += 3;
        }
        else {
            protocol_end = 0;
        }

        // 提取主机和路径
        size_t host_end = url.find('/', protocol_end);
        if (host_end == std::string::npos) {
            host = url.substr(protocol_end);
            target = "/";
        }
        else {
            host = url.substr(protocol_end, host_end - protocol_end);
            target = url.substr(host_end);
        }

        // 提取端口
        size_t port_start = host.find(':');
        if (port_start != std::string::npos) {
            port = host.substr(port_start + 1);
            host = host.substr(0, port_start);
        }
        else {
            port = (protocol == "https") ? "443" : "80";
        }

        return { host, port, target };
    }
};

int FileDownloader1(int argc, char** argv) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <url> <output_file>\n";
        return 1;
    }

    try {
        net::io_context ioc;
        FileDownloader downloader(ioc);

        if (downloader.download_file(argv[1], argv[2])) {
            std::cout << "Download completed successfully!" << std::endl;
        }
        else {
            std::cout << "Download failed!" << std::endl;
            return 1;
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}