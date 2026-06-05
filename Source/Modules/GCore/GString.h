#pragma once
#include "GExport.h"
#include <string>
class GEXPORT GString
{
public:
    GString();
    GString(std::string InStr);
    GString(const char* InStr);
    /*
     * 拷贝构造函数
     */
    GString(const GString& InStr);

    GString &operator=(const GString &InStr);
    virtual ~GString();

    friend std::ostream& operator<<(std::ostream& os, const GString& InStr);
private:
    std::string Str;
};



