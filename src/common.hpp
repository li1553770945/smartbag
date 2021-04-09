//用于实现一些公共函数
#pragma once
#include <string>
#include <sstream>
std::string to_string(float number)
{
    std::stringstream oss;
    oss << number;
    std::string str(oss.str());
    return str;
}