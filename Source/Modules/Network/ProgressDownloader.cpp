#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio.hpp>
#include <fstream>
#include <iostream>
#include <string>
#include <iomanip>
#include <chrono>

namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;
using tcp = boost::asio::ip::tcp;

class ProgressDownloader {
public:
    ProgressDownloader(net::io_context& ioc) : ioc_(ioc) {}

    bool download_with_progress(const std::string& url, const std::string& output_path) {
        try {
            auto [host, port, target] = parse_url(url);

            tcp::resolver resolver(ioc_);
            beast::tcp_stream stream(ioc_);

            auto const results = resolver.resolve(host, port);
            stream.connect(results);

            http::request<http::string_body> req{ http::verb::get, target, 11 };
            req.set(http::field::host, host);
            req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);

            http::write(stream, req);

            beast::flat_buffer buffer;
            http::response<http::dynamic_body> res;

            // 读取完整响应
            http::read(stream, buffer, res);

            if (res.result() != http::status::ok) {
                std::cerr << "HTTP error: " << res.result() << std::endl;
                return false;
            }

            // 获取内容长度
            size_t content_length = 0;
            auto cl_it = res.find(http::field::content_length);
            if (cl_it != res.end()) {
                try {
                    content_length = std::stoul(std::string(cl_it->value()));
                }
                catch (const std::exception& e) {
                    std::cerr << "Warning: Invalid Content-Length" << std::endl;
                }
            }

            // 获取实际数据大小
            size_t actual_size = res.body().size();

            std::cout << "Content-Length: " << content_length << std::endl;
            std::cout << "Actual data size: " << actual_size << std::endl;

            // 写入文件
            std::ofstream file(output_path, std::ios::binary);
            if (!file) {
                std::cerr << "Cannot create file: " << output_path << std::endl;
                return false;
            }

            // 直接写入整个响应体
            for (auto const& chunk : res.body().data()) {
                file.write(static_cast<const char*>(chunk.data()), chunk.size());
            }
            file.close();

            // 验证文件
            std::ifstream check_file(output_path, std::ios::binary | std::ios::ate);
            size_t file_size = check_file.tellg();
            check_file.close();

            std::cout << "File size: " << file_size << " bytes" << std::endl;

            if (content_length > 0 && file_size != content_length) {
                std::cout << "Warning: File size mismatch (expected: " << content_length
                    << ", actual: " << file_size << ")" << std::endl;
            }

            // 关闭连接
            beast::error_code ec;
            stream.socket().shutdown(tcp::socket::shutdown_both, ec);

            std::cout << "Download completed: " << output_path << std::endl;
            return true;

        }
        catch (const std::exception& e) {
            std::cerr << "Download failed: " << e.what() << std::endl;
            return false;
        }
    }

private:
    net::io_context& ioc_;

    std::tuple<std::string, std::string, std::string> parse_url(const std::string& url) {
        std::string protocol, host, port, target;

        size_t protocol_end = url.find("://");
        if (protocol_end != std::string::npos) {
            protocol = url.substr(0, protocol_end);
            protocol_end += 3;
        }
        else {
            protocol_end = 0;
        }

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


class ProgressDownloaderWithProgress {
public:
    ProgressDownloaderWithProgress(net::io_context& ioc) : ioc_(ioc) {}

    bool download_with_progress(const std::string& url, const std::string& output_path) {
        try {
            auto [host, port, target] = parse_url(url);

            tcp::resolver resolver(ioc_);
            beast::tcp_stream stream(ioc_);

            auto const results = resolver.resolve(host, port);
            stream.connect(results);

            http::request<http::string_body> req{ http::verb::get, target, 11 };
            req.set(http::field::host, host);
            req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);

            http::write(stream, req);

            beast::flat_buffer buffer;

            // 创建解析器并设置更大的body限制
            http::response_parser<http::dynamic_body> parser;

            // 关键修复：正确设置body大小限制
            // 使用无符号64位整数作为参数
            parser.body_limit(std::numeric_limits<std::uint64_t>::max()); // 最大限制

            // 读取响应头
            http::read_header(stream, buffer, parser);

            auto& res = parser.get();
            if (res.result() != http::status::ok) {
                std::cerr << "HTTP error: " << res.result() << std::endl;
                return false;
            }

            // 获取内容长度
            size_t content_length = 0;
            auto cl_it = res.find(http::field::content_length);
            if (cl_it != res.end()) {
                try {
                    content_length = std::stoul(std::string(cl_it->value()));
                    std::cout << "Content-Length: " << content_length << " bytes" << std::endl;
                }
                catch (const std::exception& e) {
                    std::cerr << "Warning: Invalid Content-Length" << std::endl;
                }
            }

            std::ofstream file(output_path, std::ios::binary);
            if (!file) {
                std::cerr << "Cannot create file: " << output_path << std::endl;
                return false;
            }

            size_t total_received = 0;
            auto last_update = std::chrono::steady_clock::now();

            // 读取响应体并显示进度
            while (!parser.is_done()) {
                beast::error_code ec;

                // 读取一些数据
                http::read_some(stream, buffer, parser, ec);

                if (ec) {
                    if (ec == http::error::end_of_chunk ||
                        ec == http::error::end_of_stream ||
                        ec == beast::http::error::partial_message) {
                        break; // 正常结束
                    }
                    if (ec == http::error::need_buffer) {
                        continue; // 需要更多缓冲区，继续读取
                    }
                    std::cerr << "Read error: " << ec.message() << std::endl;
                    return false;
                }

                // 获取消息体
                auto& body = parser.get().body();
                size_t chunk_size = 0;

                // 将数据写入文件
                auto body_buf = body.data();
                for (auto it = body_buf.begin(); it != body_buf.end(); ++it) {
                    auto chunk = *it;
                    file.write(static_cast<const char*>(chunk.data()), chunk.size());
                    chunk_size += chunk.size();
                }

                total_received += chunk_size;

                // 清空已写入的数据
                body.clear();

                // 消费缓冲区中的数据
                if (chunk_size > 0) {
                    buffer.consume(buffer.size());
                }

                // 显示进度
                auto now = std::chrono::steady_clock::now();
                if (now - last_update > std::chrono::milliseconds(100) || parser.is_done()) {
                    if (content_length > 0) {
                        double progress = (static_cast<double>(total_received) / content_length) * 100.0;
                        if (progress > 100.0) progress = 100.0;
                        std::cout << "\rProgress: " << std::fixed << std::setprecision(1)
                            << progress << "% (" << total_received << "/"
                            << content_length << " bytes)" << std::flush;
                    }
                    else {
                        std::cout << "\rReceived: " << total_received << " bytes" << std::flush;
                    }
                    last_update = now;
                }
            }

            std::cout << std::endl;
            file.close();

            // 验证文件
            std::ifstream check_file(output_path, std::ios::binary | std::ios::ate);
            size_t file_size = check_file.tellg();
            check_file.close();

            std::cout << "Download completed: " << output_path << " (" << file_size << " bytes)" << std::endl;

            if (content_length > 0 && file_size != content_length) {
                std::cout << "Warning: File size (" << file_size
                    << ") differs from Content-Length (" << content_length << ")" << std::endl;
            }

            // 关闭连接
            beast::error_code ec;
            stream.socket().shutdown(tcp::socket::shutdown_both, ec);

            return true;

        }
        catch (const std::exception& e) {
            std::cerr << "Download failed: " << e.what() << std::endl;
            return false;
        }
    }

private:
    net::io_context& ioc_;

    std::tuple<std::string, std::string, std::string> parse_url(const std::string& url) {
        std::string protocol, host, port, target;

        size_t protocol_end = url.find("://");
        if (protocol_end != std::string::npos) {
            protocol = url.substr(0, protocol_end);
            protocol_end += 3;
        }
        else {
            protocol_end = 0;
        }

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
int ProgressDownloadermain(int argc, char** argv) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <url> <output_file>\n";
        return 1;
    }

    try {
        net::io_context ioc;

        // 先用简单版本测试文件是否正确
       // ProgressDownloader downloader(ioc);

        // 或者用带进度显示的版本
         ProgressDownloaderWithProgress downloader(ioc);

        if (downloader.download_with_progress(argv[1], argv[2])) {
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