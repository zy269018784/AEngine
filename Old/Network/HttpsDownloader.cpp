#if 0
#define BOOST_ASIO_DISABLE_S
S
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include <fstream>
#include <iostream>
#include <string>

namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;
namespace ssl = net::ssl;
using tcp = boost::asio::ip::tcp;

class HttpsDownloader {
public:
    HttpsDownloader(net::io_context& ioc, ssl::context& ctx)
        : ioc_(ioc), ctx_(ctx) {
    }

    bool download_file(const std::string& url, const std::string& output_path) {
        try {
            auto [host, port, target] = parse_url(url);

            // 创建 SSL 流
            beast::ssl_stream<beast::tcp_stream> stream(ioc_, ctx_);

            // 设置 SNI 主机名
            if (!SSL_set_tlsext_host_name(stream.native_handle(), host.c_str())) {
                beast::error_code ec{ static_cast<int>(::ERR_get_error()),
                                   net::error::get_ssl_category() };
                throw beast::system_error{ ec };
            }

            // 解析域名
            tcp::resolver resolver(ioc_);
            auto const results = resolver.resolve(host, port);

            // 建立 TCP 连接
            beast::get_lowest_layer(stream).connect(results);

            // SSL 握手
            stream.handshake(ssl::stream_base::client);

            // 设置 HTTP 请求
            http::request<http::string_body> req{ http::verb::get, target, 11 };
            req.set(http::field::host, host);
            req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);
            req.set(http::field::accept, "*/*");

            // 发送请求
            http::write(stream, req);

            // 接收响应
            beast::flat_buffer buffer;
            http::response<http::dynamic_body> res;
            http::read(stream, buffer, res);

            // 检查状态
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

            // 优雅关闭
            beast::error_code ec;
            stream.shutdown(ec);
            if (ec == net::ssl::error::stream_truncated) {
                // 这通常是可以的
            }
            else if (ec) {
                throw beast::system_error{ ec };
            }

            std::cout << "HTTPS file downloaded successfully: " << output_path << std::endl;
            return true;

        }
        catch (const std::exception& e) {
            std::cerr << "HTTPS download failed: " << e.what() << std::endl;
            return false;
        }
    }

private:
    net::io_context& ioc_;
    ssl::context& ctx_;

    std::tuple<std::string, std::string, std::string> parse_url(const std::string& url) {
        std::string protocol, host, port, target;

        size_t protocol_end = url.find("://");
        if (protocol_end == std::string::npos) {
            throw std::invalid_argument("Invalid URL format");
        }

        protocol = url.substr(0, protocol_end);
        protocol_end += 3;

        size_t host_end = url.find('/', protocol_end);
        if (host_end == std::string::npos) {
            host = url.substr(protocol_end);
            target = "/";
        }
        else {
            host = url.substr(protocol_end, host_end - protocol_end);
            target = url.substr(host_end);
        }

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

int main(int argc, char** argv) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <https_url> <output_file>\n";
        return 1;
    }

    try {
        net::io_context ioc;

        // SSL 上下文
        ssl::context ctx(ssl::context::tlsv12_client);
        ctx.set_default_verify_paths();

        HttpsDownloader downloader(ioc, ctx);

        if (downloader.download_file(argv[1], argv[2])) {
            std::cout << "HTTPS download completed successfully!" << std::endl;
        }
        else {
            std::cout << "HTTPS download failed!" << std::endl;
            return 1;
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
#endif