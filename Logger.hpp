#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <string>
#include <iostream>

struct Logger {
    static const int LOG_INFO    = 0;
    static const int LOG_WARNING = 1;
    static const int LOG_ERROR   = 2;

    Logger();
    
    void log(int type, std::string message, bool color);
    void log(int type, std::string message);
    void log(std::string message);
    
    void logNoEndl(int type, std::string message, bool color);
    void logNoEndl(int type, std::string message);
    void logNoEndl(std::string message);
    
    void pause();
};

#endif
