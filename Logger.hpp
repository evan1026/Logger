#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <string>
#include <iostream>

struct Logger {
    static const int LOG_INFO;
    static const int LOG_WARNING;
    static const int LOG_ERROR;

    static void log(int type, std::string message, bool color);
    static void log(int type, std::string message);
    static void log(std::string message);
};

#endif
