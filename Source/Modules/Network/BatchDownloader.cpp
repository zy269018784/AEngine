#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/asio.hpp>
#include <fstream>
#include <iostream>
#include <vector>
#include <thread>
#include <mutex>

namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;
using tcp = boost::asio::ip::tcp;

class BatchDownloader {
public:
    BatchDownloader(int thread_count = 4)
        : ioc_(), work_guard_(net::make_work_guard(ioc_)) {

        // 启动工作线程
        for (int i = 0; i < thread_count; ++i) {
            threads_.emplace_back([this]() { ioc_.run(); });
        }
    }

    ~BatchDownloader() {
        ioc_.stop();
        for (auto& thread : threads_) {
            if (thread.joinable()) {
                thread.join();
            }
        }
    }

    void add_download(const std::string& url, const std::string& output_path) {
        std::lock_guard<std::mutex> lock(mutex_);
        downloads_.emplace_back(url, output_path);
    }

    void start_downloads() {
        for (const auto& [url, output_path] : downloads_) {
            net::post(ioc_, [this, url, output_path]() {
                download_single_file(url, output_path);
                });
        }
    }

    void wait_for_completion() {
        // 等待所有任务完成
        std::unique_lock<std::mutex> lock(mutex_);
        cv_.wait(lock, [this]() {
            return completed_downloads_ == downloads_.size();
            });
    }

private:
    net::io_context ioc_;
    net::executor_work_guard<net::io_context::executor_type> work_guard_;
    std::vector<std::thread> threads_;
    std::vector<std::pair<std::string, std::string>> downloads_;
    std::mutex mutex_;
    std::condition_variable cv_;
    size_t completed_downloads_ = 0;

    void download_single_file(const std::string& url, const std::string& output_path) {
        try {
            auto [host, port, target] = parse_url(url);

            tcp::resolver resolver(ioc_);
            beast::tcp_stream stream(ioc_);

            auto const results = resolver.resolve(host, port);
            stream.connect(results);

            http::request<http::string_body> req{ http::verb::get, target, 11 };
            req.set(http::field::host, host);
            //req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);

            http::write(stream, req);

            beast::flat_buffer buffer;
            http::response<http::dynamic_body> res;
            http::read(stream, buffer, res);

            if (res.result() == http::status::ok) {
                std::ofstream file(output_path, std::ios::binary);
                if (file) {
                    auto& body = res.body();
                    for (auto const& chunk : body.data()) {
                        file.write(static_cast<const char*>(chunk.data()), chunk.size());
                    }
                    file.close();

                    std::lock_guard<std::mutex> lock(mutex_);
                    std::cout << "Downloaded: " << output_path << std::endl;
                }
            }

            beast::error_code ec;
            stream.socket().shutdown(tcp::socket::shutdown_both, ec);

        }
        catch (const std::exception& e) {
            std::lock_guard<std::mutex> lock(mutex_);
            std::cerr << "Failed to download " << url << ": " << e.what() << std::endl;
        }

        // 通知完成
        std::lock_guard<std::mutex> lock(mutex_);
        completed_downloads_++;
        if (completed_downloads_ == downloads_.size()) {
            cv_.notify_all();
        }
    }

    std::tuple<std::string, std::string, std::string> parse_url(const std::string& url) {
        // 简化的 URL 解析，实际使用时应该更健壮
        size_t protocol_end = url.find("://");
        size_t start = (protocol_end != std::string::npos) ? protocol_end + 3 : 0;

        size_t host_end = url.find('/', start);
        if (host_end == std::string::npos) {
            return { url.substr(start), "80", "/" };
        }

        std::string host = url.substr(start, host_end - start);
        std::string target = url.substr(host_end);

        size_t port_pos = host.find(':');
        if (port_pos != std::string::npos) {
            return { host.substr(0, port_pos), host.substr(port_pos + 1), target };
        }

        return { host, "80", target };
    }
};

int BatchDownloadermain() {
    try {
        BatchDownloader downloader(4); // 4个下载线程

        // 添加下载任务
        downloader.add_download("http://example.com/file1.txt", "file1.txt");
        downloader.add_download("http://example.com/file2.jpg", "file2.jpg");
        downloader.add_download("http://example.com/file3.pdf", "file3.pdf");

        std::cout << "Starting batch downloads..." << std::endl;
        downloader.start_downloads();
        downloader.wait_for_completion();
        std::cout << "All downloads completed!" << std::endl;

    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}