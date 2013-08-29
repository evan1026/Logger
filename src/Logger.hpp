#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <string>
#include <iostream>
#include <sstream>

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
    void pause(std::string message);

    bool clearLine();

    bool logrw(int type, std::string message, bool color);
    bool logrw(int type, std::string message);
    bool logrw(std::string message);

    bool logrwNoEndl(int type, std::string message, bool color);
    bool logrwNoEndl(int type, std::string message);
    bool logrwNoEndl(std::string message);

    private:
        bool canRewrite;
        bool rewriting;
        std::size_t lastLength;
};

#endif
