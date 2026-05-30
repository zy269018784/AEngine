// 1. 普通函数
int add(int a, int b) {
    return a + b;
}

 // 存储普通函数
std::function<int(int, int)> f1 = add;
std::cout << "add: " << f1(3, 4) << std::endl;

 // 存储lambda表达式
std::function<int(int, int)> f2 = [](int a, int b) {
    return a - b;
};
std::cout << "lambda: " << f2(7, 3) << std::endl;

// 存储std::bind结果
using namespace std::placeholders;
auto bound = std::bind(add, 10, _1);
std::function<int(int)> f4 = bound;
std::cout << "bind: " << f4(5) << std::endl;