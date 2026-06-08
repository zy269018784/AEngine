std::promise	异步结果的写入端








# std::promise 和 std::future 示例

```cpp
#include <iostream>
#include <future>
#include <thread>

int TestCXX(int argc, char **argv) 
{
    // 1. 创建 promise 和 future
    std::promise<int> promise;
    std::future<int> future = promise.get_future();

    // 2. 在另一个线程中设置值
    std::thread t([&promise]() {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        promise.set_value(42);  // 设置值，唤醒等待的线程
    });

    // 3. 在主线程中等待并获取值
    std::cout << "Waiting for value..." << std::endl;
    int result = future.get();  // 阻塞直到 promise.set_value()
    std::cout << "Got: " << result << std::endl;

    t.join();
    return 0;
}