#include "GCore/GList.h"
#include "GCore/GQueue.h"
#include "GCore/GStack.h"
#include "GCore/GVector.h"
#include <iostream>

int TestGCore(int argc, char **argv)
{
   GVector<int> V1;                          // 空向量
    GVector<int> V2 = {1, 2, 3, 4, 5};        // 初始化列表
    GVector<std::string> Names;               // 字符串向量

    // ========== 添加元素 ==========
    V1.Append(10);
    V1.Append(20);
    V1.Append(30);
    V1.Prepend(0);                             // 在开头添加

    Names.Append("Alice");
    Names.Append("Bob");
    Names.Append("Charlie");

    // ========== 访问元素 ==========
    std::cout << "V1[0]: " << V1[0] << std::endl;
    std::cout << "V1 first: " << V1.First() << std::endl;
    std::cout << "V1 last: " << V1.Last() << std::endl;
    std::cout << "V1 size: " << V1.GetSize() << std::endl;

    // ========== 遍历 ==========
    std::cout << "V1 elements: ";
    for (const auto& Item : V1) {
        std::cout << Item << " ";
    }
    std::cout << std::endl;

    std::cout << "Names: ";
    for (const auto& Name : Names) {
        std::cout << Name << " ";
    }
    std::cout << std::endl;

    // ========== 插入和删除 ==========
    V1.Insert(2, 99);                          // 在索引2插入99
    std::cout << "After insert: ";
    for (const auto& Item : V1) {
        std::cout << Item << " ";
    }
    std::cout << std::endl;

    V1.RemoveAt(2);                           // 删除索引2的元素
    std::cout << "After remove: ";
    for (const auto& Item : V1) {
        std::cout << Item << " ";
    }
    std::cout << std::endl;

    V1.Remove(20);                            // 删除值为20的元素
    std::cout << "After remove 20: ";
    for (const auto& Item : V1) {
        std::cout << Item << " ";
    }
    std::cout << std::endl;

    // ========== 查找 ==========
    if (V1.Contains(10)) {
        std::cout << "Found 10 at index: " << V1.IndexOf(10) << std::endl;
    }

    // ========== 反转 ==========
    V1.Reverse();
    std::cout << "After reverse: ";
    for (const auto& Item : V1) {
        std::cout << Item << " ";
    }
    std::cout << std::endl;

    // ========== 清空 ==========
    V1.Clear();
    std::cout << "After clear, size: " << V1.GetSize() << std::endl;
    std::cout << "Is empty? " << (V1.IsEmpty() ? "Yes" : "No") << std::endl;

    // ========== 使用 STL 算法 ==========
    GVector<int> Numbers = {5, 2, 8, 1, 9, 3};

    // 排序
    std::sort(Numbers.Begin(), Numbers.End());
    std::cout << "Sorted: ";
    for (const auto& N : Numbers) {
        std::cout << N << " ";
    }
    std::cout << std::endl;

    // 查找
    auto It = std::find(Numbers.Begin(), Numbers.End(), 5);
    if (It != Numbers.End()) {
        std::cout << "Found 5" << std::endl;
    }

    // ========== 拷贝和移动 ==========
    GVector<int> V3 = {1, 2, 3};
    GVector<int> V4 = V3;                      // 拷贝构造
    GVector<int> V5 = std::move(V3);           // 移动构造

    std::cout << "V4: ";
    for (const auto& Item : V4) {
        std::cout << Item << " ";
    }
    std::cout << std::endl;

    std::cout << "V5: ";
    for (const auto& Item : V5) {
        std::cout << Item << " ";
    }
    std::cout << std::endl;

    std::cout << "V3 after move, size: " << V3.GetSize() << std::endl;


    return 0;
}