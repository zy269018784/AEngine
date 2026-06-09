#include <httplib.h>
/*
 * https://www.sojson.com/http/test.html
 */
int TestHttpServer(int argc, char **argv)
{
    // 创建服务器实例
    httplib::Server svr;

    // 注册路由：GET /hi
    svr.Get("/hi", [](const httplib::Request &req, httplib::Response &res) {
        res.set_content("Hello!", "text/plain");
    });

    // 可选：添加根路径路由
    svr.Get("/", [](const httplib::Request &req, httplib::Response &res) {
        res.set_content("Welcome to HTTP Server! Try /hi", "text/plain");
    });

    // 启动服务器，监听 localhost:8080
    std::cout << "Server is running at http://localhost:8080" << std::endl;
    std::cout << "Try: http://localhost:8080/hi" << std::endl;

    svr.listen("localhost", 8080);

    return 0;
}