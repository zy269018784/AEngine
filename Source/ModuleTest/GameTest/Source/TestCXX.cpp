#include <iostream>
#include <memory>

class Test
{
public:
    Test(int x, int y) : a(x), b(y) {}

    //Test(const Test&) = delete;
public:
    int a;
    int b;
};

int TestCXX(int argc, char **argv)
{

    Test A(190, 32);

    Test B(A);

    Test C(std::move(A));

    std::cout << A.a  << " "  <<  A.b << std::endl;
    std::cout << B.a  << " "  <<  B.b << std::endl;
    std::cout << C.a  << " "  <<  C.b << std::endl;
    return 0;
}