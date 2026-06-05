#include "GString.h"

GString::GString() : Str()
{

}


GString::GString(std::string InStr) : Str(InStr) {

}

// 从 const char* 构造
GString::GString(const char* InStr) : Str(InStr ? InStr : "")
{

}

// 拷贝构造函数
GString::GString(const GString& InStr) : Str(InStr.Str)
{

}

// 析构函数
GString::~GString()
{

}

GString& GString::operator=(const GString& InStr)
{
    if (this != &InStr)
    {
        Str = InStr.Str;
    }
    return *this;
}

std::ostream& operator<<(std::ostream& os, const GString& InStr)
{
    os << InStr.Str;  // 友元函数可以直接访问私有成员
    return os;
}