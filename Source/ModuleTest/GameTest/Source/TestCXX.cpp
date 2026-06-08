#include <iostream>
#include <memory>

class Test {
public:
    int id;
    Test(int i) : id(i) { std::cout << "构造 " << id << "\n"; }
    ~Test() { std::cout << "析构 " << id << "\n"; }
    void hello() { std::cout << "Hello " << id << "\n"; }
};

int TestCXX(int argc, char **argv)
{
    // 1. 创建 shared_ptr
    auto p1 = std::make_shared<Test>(1);

    // 2. 访问成员
    p1->hello();
    (*p1).hello();

    // 3. 查看引用计数
    std::cout << "引用计数: " << p1.use_count() << "\n";

    // 4. 拷贝（共享所有权）
    auto p2 = p1;  // 引用计数 +1
    std::cout << "拷贝后引用计数: " << p1.use_count() << "\n";

    // 5. 获取裸指针
    Test* raw = p1.get();
    std::cout << "裸指针地址: " << raw << "\n";

    // 6. 重置
    p2.reset();  // p2 释放，引用计数 -1
    std::cout << "p2 reset 后引用计数: " << p1.use_count() << "\n";

    // 7. 使用别名构造（共享同一个控制块，但指向不同成员）
    auto p3 = std::make_shared<Test>(2);
    std::shared_ptr<int> p4(p3, &p3->id);  // 指向 id 成员
    std::cout << "p3 引用计数: " << p3.use_count() << "\n";

    return 0;
}