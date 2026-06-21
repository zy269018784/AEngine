#include "GCore/GList.h"
#include <iostream>

int TestGCore(int argc, char **argv)
{
    GList<int> list = {1, 2, 3, 4, 5};

    std::cout << "First: " << list.First() << std::endl;
    std::cout << "Last: " << list.Last() << std::endl;
    std::cout << "Size: " << list.GetSize() << std::endl;

    list.Append(6);
    list.Prepend(0);
    list.Insert(3, 99);

    if (list.Contains(99)) {
        auto it = list.Find(99);
        std::cout << "Found 99 at index: " << list.IndexOf(99) << std::endl;
    }

    list.RemoveAt(2);
    list.Remove(3);
    list.Reverse();

    // 使用范围 for 循环
    for (const auto& item : list) {
        std::cout << item << " ";
    }
    std::cout << std::endl;

    // ========== 方式二：begin()/end() 迭代器 ==========
    std::cout << "Iterator loop: ";
    for (auto It = list.begin(); It != list.end(); ++It) {
        std::cout << *It << " ";
    }
    std::cout << std::endl;

    // ========== 方式三：大写 Begin()/End() 迭代器 ==========
    std::cout << "Capital iterator loop: ";
    for (auto It = list.Begin(); It != list.End(); ++It) {
        std::cout << *It << " ";
    }
    std::cout << std::endl;

    list.Clear();
    std::cout << "Is empty? " << (list.IsEmpty() ? "Yes" : "No") << std::endl;



    return 0;
}