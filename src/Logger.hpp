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

    void continueln(std::string message);
    void continuelnNoEndl(std::string message);

    private:
        bool canRewrite;
        bool rewriting;
        std::size_t lastLength;
        std::string currentLine;

        void finishLine();
};

std::string operator+(bool a, const std::string& b);
std::string operator+(const std::string& a, bool b);

std::string operator+(short a, const std::string& b);
std::string operator+(const std::string& a, short b);

std::string operator+(unsigned short a, const std::string& b);
std::string operator+(const std::string& a, unsigned short b);

std::string operator+(int a, const std::string& b);
std::string operator+(const std::string& a, int b);

std::string operator+(unsigned int a, const std::string& b);
std::string operator+(const std::string& a, unsigned int b);

std::string operator+(long a, const std::string& b);
std::string operator+(const std::string& a, long b);

std::string operator+(unsigned long a, const std::string& b);
std::string operator+(const std::string& a, unsigned long b);

std::string operator+(long long a, const std::string& b);
std::string operator+(const std::string& a, long long b);

std::string operator+(unsigned long long a, const std::string& b);
std::string operator+(const std::string& a, unsigned long long b);

std::string operator+(float a, const std::string& b);
std::string operator+(const std::string& a, float b);

std::string operator+(double a, const std::string& b);
std::string operator+(const std::string& a, double b);

std::string operator+(long double a, const std::string& b);
std::string operator+(const std::string& a, long double b);

#endif
