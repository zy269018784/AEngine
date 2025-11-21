#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio.hpp>
#include <chrono>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>

namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;
using tcp = boost::asio::ip::tcp;
namespace fs = std::filesystem;

class FileSession : public std::enable_shared_from_this<FileSession> {
public:
    FileSession(tcp::socket socket, const std::string& doc_root)
        : socket_(std::move(socket))
        , doc_root_(doc_root) {
    }

    void start() {
        read_request();
    }

private:
    tcp::socket socket_;
    beast::flat_buffer buffer_{ 8192 };
    http::request<http::string_body> request_;
    http::response<http::dynamic_body> response_;
    std::string doc_root_;

    void read_request() {
        auto self = shared_from_this();

        http::async_read(
            socket_, buffer_, request_,
            [self](beast::error_code ec, std::size_t bytes_transferred) {
                if (!ec) {
                    self->process_request();
                }
            });
    }

    void process_request() {
        response_.version(request_.version());
        response_.keep_alive(false);

        // 只处理 GET 请求
        if (request_.method() != http::verb::get) {
            send_bad_response(http::status::bad_request, "Invalid method");
            return;
        }

        // 构建文件路径
        std::string path = path_cat(doc_root_, request_.target());
        if (path.back() == '/') {
            path += "index.html";
        }

        // 安全检查，防止路径遍历攻击
        if (path.find("..") != std::string::npos) {
            send_bad_response(http::status::forbidden, "Forbidden");
            return;
        }

        // 检查文件是否存在
        if (!fs::exists(path) || !fs::is_regular_file(path)) {
            send_bad_response(http::status::not_found, "File not found");
            return;
        }

        // 读取文件内容
        std::ifstream file(path, std::ios::binary);
        if (!file) {
            send_bad_response(http::status::internal_server_error, "Internal server error");
            return;
        }

        // 获取文件大小
        file.seekg(0, std::ios::end);
        size_t file_size = file.tellg();
        file.seekg(0, std::ios::beg);

        // 准备响应
        response_.result(http::status::ok);
        response_.set(http::field::server, "Boost Beast File Server");
        response_.set(http::field::content_type, mime_type(path));
        response_.content_length(file_size);

        // 读取文件到响应体
        beast::ostream(response_.body()) << file.rdbuf();

        send_response();
    }

    void send_bad_response(http::status status, const std::string& error) {
        response_.result(status);
        response_.set(http::field::server, "Boost Beast File Server");
        response_.set(http::field::content_type, "text/html");
        beast::ostream(response_.body()) << "<html><body><h1>" << error << "</h1></body></html>";
        response_.content_length(response_.body().size());

        send_response();
    }

    void send_response() {
        auto self = shared_from_this();

        response_.set(http::field::connection, "close");

        http::async_write(
            socket_, response_,
            [self](beast::error_code ec, std::size_t) {
                self->socket_.shutdown(tcp::socket::shutdown_send, ec);
            });
    }

    std::string path_cat(const std::string& base, const std::string& path) {
        if (base.empty()) return path;
        std::string result = base;
        if (result.back() == '/') result.pop_back();
        result += path;
        return result;
    }

    std::string mime_type(const std::string& path) {
        auto const ext = [&path] {
            auto pos = path.rfind(".");
            if (pos == std::string::npos) return std::string();
            return path.substr(pos);
            }();

        if (ext == ".htm" || ext == ".html") return "text/html";
        if (ext == ".css") return "text/css";
        if (ext == ".js") return "application/javascript";
        if (ext == ".json") return "application/json";
        if (ext == ".xml") return "application/xml";
        if (ext == ".txt") return "text/plain";
        if (ext == ".png") return "image/png";
        if (ext == ".jpg" || ext == ".jpeg") return "image/jpeg";
        if (ext == ".gif") return "image/gif";
        if (ext == ".pdf") return "application/pdf";
        if (ext == ".zip") return "application/zip";

        return "application/octet-stream";
    }
};

class FileServer {
public:
    FileServer(net::io_context& ioc, const tcp::endpoint& endpoint, const std::string& doc_root)
        : acceptor_(ioc)
        , doc_root_(doc_root) {
        beast::error_code ec;

        acceptor_.open(endpoint.protocol(), ec);
        if (ec) {
            fail(ec, "open");
            return;
        }

        acceptor_.set_option(net::socket_base::reuse_address(true), ec);
        if (ec) {
            fail(ec, "set_option");
            return;
        }

        acceptor_.bind(endpoint, ec);
        if (ec) {
            fail(ec, "bind");
            return;
        }

        acceptor_.listen(net::socket_base::max_listen_connections, ec);
        if (ec) {
            fail(ec, "listen");
            return;
        }
    }

    void start_accept() {
        acceptor_.async_accept(
            [this](beast::error_code ec, tcp::socket socket) {
                if (!ec) {
                    std::make_shared<FileSession>(std::move(socket), doc_root_)->start();
                }
                start_accept();
            });
    }

private:
    tcp::acceptor acceptor_;
    std::string doc_root_;

    void fail(beast::error_code ec, const char* what) {
        std::cerr << what << ": " << ec.message() << "\n";
    }
};

