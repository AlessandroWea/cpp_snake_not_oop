#pragma once
#include <iostream>

class Log
{
public:

    enum class level
    {
        INFO,
        ERROR
    };

    static void info(const char *msg)
    {
        std::cout << "info::" << msg << std::endl;
    }
};
