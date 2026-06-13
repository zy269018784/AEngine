#include <iostream>
#include <string>
#include <curl/curl.h>

// 回调函数：将响应数据写入 string
size_t WriteCallback(void *contents, size_t size, size_t nmemb, std::string *output) {
    size_t totalSize = size * nmemb;
    output->append((char*)contents, totalSize);
    return totalSize;
}

// 简单的 GET 请求示例
void HttpGet(const std::string &url) {
    CURL *curl = curl_easy_init();
    if (!curl) {
        std::cerr << "curl_easy_init failed" << std::endl;
        return;
    }

    std::string response;

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10L);  // 超时10秒

    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        std::cerr << "curl_easy_perform failed: " << curl_easy_strerror(res) << std::endl;
    } else {
        std::cout << "Response: " << response << std::endl;
    }

    curl_easy_cleanup(curl);
}

int TestHttpClient(int argc, char **argv)
{
    // 初始化 libcurl（全局一次）
    curl_global_init(CURL_GLOBAL_DEFAULT);

    // 测试根路径
    std::cout << "=== GET / ===" << std::endl;
    HttpGet("http://localhost:8080/");

    // 测试带参数的 /hi
    std::cout << "\n=== GET /hi?name=Alice ===" << std::endl;
    HttpGet("http://localhost:8080/hi?name=Alice");

    // 测试无参数 /hi
    std::cout << "\n=== GET /hi ===" << std::endl;
    HttpGet("http://localhost:8080/hi");

    // 清理全局资源
    curl_global_cleanup();
    return 0;
}