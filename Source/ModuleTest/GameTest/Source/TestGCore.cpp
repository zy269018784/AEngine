#include "GCore/GList.h"
#include "GCore/GQueue.h"
#include <iostream>

int TestGCore(int argc, char **argv)
{
    GQueue<std::string> Queue;
    Queue.Enqueue("Apple");
    Queue.Enqueue("Banana");
    Queue.Enqueue("Cherry");
    Queue.Enqueue("Date");
    Queue.Enqueue("Elderberry");

    // 范围 for 循环
    std::cout << "Range-based for: ";
    for (const auto& Item : Queue) {
        std::cout << Item << " ";
    }
    std::cout << std::endl;


    return 0;
}