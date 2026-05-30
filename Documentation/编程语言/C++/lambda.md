[capture list] (parameter list) -> return type { function body }

capture list 是捕获列表
parameter list 是参数列表
return type 是返回值类型
function body 是函数体

捕获方式:
    值捕获(capture by value)
        int x = 10;
        auto f = [x] (int y) -> int { return x + y; }; // 值捕获 x
        x = 20; // 修改外部的 x
        cout << f(5) << endl; // 输出 15，不受外部 x 的影响
    引用捕获(capture by reference)
        int x = 10;
        auto f = [&x] (int y) -> int { return x + y; }; // 引用捕获 x
        x = 20; // 修改外部的 x
        cout << f(5) << endl; // 输出 25，受外部 x 的影响
    隐式捕获(implicit capture): 在捕获列表中使用 = 或 &，表示按值或按引用捕获 Lambda 表达式中使用的所有外部变量。
        int x = 10;
        int y = 20;
        auto f = [=, &y] (int z) -> int { return x + y + z; }; // 隐式按值捕获 x，显式按引用捕获 y
        x = 30; // 修改外部的 x
        y = 40; // 修改外部的 y
        cout << f(5) << endl; // 输出 55，不受外部 x 的影响，受外部 y 的影响
    初始化捕获(init capture)
        int x = 10;
        auto f = [z = x + 5] (int y) -> int { return z + y; }; // 初始化捕获 z，相当于值捕获 x + 5
        x = 20; // 修改外部的 x
        cout << f(5) << endl; // 输出 20，不受外部 x 的影响
