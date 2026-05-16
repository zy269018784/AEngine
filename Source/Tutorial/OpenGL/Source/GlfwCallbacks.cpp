#include <iostream>

void GLFWErrorCallback(int error, const char *desc)
{
    std::cout << "error " << error << " desc " << desc << std::endl;
}