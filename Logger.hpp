#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <string>
#include <iostream>

struct Logger {
    static const int LOG_INFO    = 0;
    static const int LOG_WARNING = 1;
    static const int LOG_ERROR   = 2;

    private int prevLength = 0;

    static void log(int type, std::string message, bool color);
    static void log(int type, std::string message);
    static void log(std::string message);
    
    static void logrw(int type, std::string message, bool color);
    static void logrw(int type, std::string message);
    static void logrw(std::string message);

    static void eraseLast();
};

#endif
