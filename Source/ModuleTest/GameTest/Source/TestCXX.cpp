#include <iostream>
#include <cstring>
#include <thread>
#include <chrono>

int TestCXX(int argc, char** argv)
{
    std::optional<int> opt = 42;

    // 方法1：operator bool
    if (opt) {
        std::cout << "有值" << std::endl;
    }

    // 方法2：has_value()
    if (opt.has_value()) {
        std::cout << "有值" << std::endl;
    }

    // 方式1：空 optional
    std::optional<int> empty;                    // 包含 nullopt
    std::optional<int> empty2 = std::nullopt;    // 显式为空

    // 方式2：包含值
    std::optional<int> opt1 = 42;                // 包含值 42
    std::optional<int> opt2(42);                 // 同上
    std::optional<int> opt3 = std::make_optional(42);

    // 方式3：使用 std::in_place 构造复杂对象（避免拷贝）
    std::optional<std::string> opt4(std::in_place, "hello");
    std::optional<std::vector<int>> opt5(std::in_place, 10, 20);  // 10个20

    std::cout << "empty has_value: " << empty.has_value() << std::endl;
    std::cout << "empty2 has_value: " << empty2.has_value() << std::endl;
    std::cout << "opt1 has_value: " << opt1.has_value() << ", value: " << *opt1 << std::endl;
    std::cout << "opt2 has_value: " << opt2.has_value() << ", value: " << *opt2 << std::endl;
    std::cout << "opt3 has_value: " << opt3.has_value() << ", value: " << *opt3 << std::endl;
    std::cout << "opt4 has_value: " << opt4.has_value() << ", value: " << *opt4 << std::endl;
    std::cout << "opt5 has_value: " << opt5.has_value() << ", value: " << (*opt5)[0] << std::endl;

    return 0;
}