#include <httplib.h>
#include <GHttp/httplib/GHttpServer1.h>
/*
 * https://www.sojson.com/http/test.html
 */
int TestHttpServer(int argc, char **argv)
{
    GHttpServer1 Server;
    // 创建服务器实例
    httplib::Server *svr = Server.GetHandle();




    // 可选：添加根路径路由
    svr->Get("/", [](const httplib::Request &req, httplib::Response &res) {
        res.set_content("Welcome to HTTP Server! Try http://localhost:8080/hi", "text/plain");
    });

    // http://localhost:8080/hi?name=Alice
    svr->Get("/hi", [](const httplib::Request &req, httplib::Response &res) {
        // 检查参数是否存在
        if (req.has_param("name")) {
            std::string name = req.get_param_value("name");
            res.set_content("Hello, " + name + "!", "text/plain");
        } else {
            res.set_content("Hello, Guest!", "text/plain");
        }
    });

    // 启动服务器，监听 localhost:8080
    std::cout << "Server is running at http://localhost:8080" << std::endl;
    std::cout << "Try: http://localhost:8080/hi" << std::endl;

    svr->listen("localhost", 8080);

    return 0;
}