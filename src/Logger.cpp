#include "Logger.hpp"

Logger::Logger(){
    canRewrite = false;
    rewriting = false;
    lastLength = 0;
}

void Logger::log(int type, std::string message, bool color){
    
    this->logNoEndl(type, message, color);
    this->finishLine();

    canRewrite = false;
}

void Logger::log(int type, std::string message){
    this->log(type, message, false);
}

void Logger::log(std::string message){
    this->log(Logger::LOG_INFO, message);
}

void Logger::logNoEndl(int type, std::string message, bool color){
    if (canRewrite) this->finishLine();

    std::string output = "";
    std::size_t thisLength = message.length();
    switch (type) {
        case Logger::LOG_INFO:
            output += "[INFO] ";
            thisLength += 7;
            break;
        case Logger::LOG_WARNING:
            output += (color ? "\e[33m[WARNING] " : "[WARNING] ");
            thisLength += 10;
            break;
        case Logger::LOG_ERROR:
            output += (color ?  "\e[31m[ERROR] " : "[ERROR] ");
            thisLength += 8;
            break;
        default:
            this->log(LOG_ERROR, "Log type not found");
            break;
    }

    output += message;

    if (rewriting && thisLength < lastLength){
        for (int i = 0; i < lastLength - thisLength; i++){
            output += " ";
        }
        thisLength = lastLength;
    }

    lastLength = thisLength;

    currentLine = output;

    std::cout << output;
    std::cout.flush();

    canRewrite = true;
    rewriting = false;
}

void Logger::logNoEndl(int type, std::string message){
    this->logNoEndl(type, message, false);
}

void Logger::logNoEndl(std::string message){
    this->logNoEndl(Logger::LOG_INFO, message);
}

void Logger::pause(){
    this->pause("Press enter to continue...");
}

void Logger::pause(std::string message){
    this->logNoEndl(message);
    std::cin.get();

    canRewrite = false;
}

bool Logger::clearLine(){
    if (!canRewrite) return false;

    for (int i = 0; i < lastLength; i++){
        std::cout << "\b";
    }
    std::cout.flush();
    
    canRewrite = false;
    rewriting = true;
    
    return true;
}

bool Logger::logrw(int type, std::string message, bool color){
    if (!this->clearLine()) return false;

    this->log(type, message, color);

    return true;
}

bool Logger::logrw(int type, std::string message){
    return this->logrw(type, message, false);
}

bool Logger::logrw(std::string message){
    return this->logrw(Logger::LOG_INFO, message);
}

bool Logger::logrwNoEndl(int type, std::string message, bool color){
    if (!this->clearLine()) return false;

    this->logNoEndl(type, message, color);
    
    return true;
}

bool Logger::logrwNoEndl(int type, std::string message){
    return this->logrwNoEndl(type, message, false);
}

bool Logger::logrwNoEndl(std::string message){
    return this->logrwNoEndl(Logger::LOG_INFO, message);
}

void Logger::continueln(std::string message){
    std::cout << message;
    this->finishLine();
    canRewrite = false;
}

void Logger::continuelnNoEndl(std::string message){
    std::cout << message;
    currentLine += message;
}

void Logger::finishLine(){
    bool color = (currentLine.find("\e") != std::string::npos);
    std::cout << (color ? "\e[m" : "") << std::endl;
    currentLine = "";
}

std::string operator+(bool a, const std::string& b){
    std::stringstream ss;
    ss << a << b;
    return ss.str();
}

std::string operator+(const std::string& a, bool b){
    std::stringstream ss;
    ss << a << b;
    return ss.str();
}

std::string operator+(short a, const std::string& b){
    std::stringstream ss;
    ss << a << b;
    return ss.str();
}

std::string operator+(const std::string& a, short b){
    std::stringstream ss;
    ss << a << b;
    return ss.str();
}

std::string operator+(unsigned short a, const std::string& b){
    std::stringstream ss;
    ss << a << b;
    return ss.str();
}

std::string operator+(const std::string& a, unsigned short b){
    std::stringstream ss;
    ss << a << b;
    return ss.str();
}

std::string operator+(int a, const std::string& b){
    std::stringstream ss;
    ss << a << b;
    return ss.str();
}

std::string operator+(const std::string& a, int b){
    std::stringstream ss;
    ss << a << b;
    return ss.str();
}

std::string operator+(unsigned int a, const std::string& b){
    std::stringstream ss;
    ss << a << b;
    return ss.str();
}

std::string operator+(const std::string& a, unsigned int b){
    std::stringstream ss;
    ss << a << b;
    return ss.str();
}

std::string operator+(long a, const std::string& b){
    std::stringstream ss;
    ss << a << b;
    return ss.str();
}

std::string operator+(const std::string& a, long b){
    std::stringstream ss;
    ss << a << b;
    return ss.str();
}

std::string operator+(unsigned long a, const std::string& b){
    std::stringstream ss;
    ss << a << b;
    return ss.str();
}

std::string operator+(const std::string& a, unsigned long b){
    std::stringstream ss;
    ss << a << b;
    return ss.str();
}

std::string operator+(long long a, const std::string& b){
    std::stringstream ss;
    ss << a << b;
    return ss.str();
}

std::string operator+(const std::string& a, unsigned long long b){
    std::stringstream ss;
    ss << a << b;
    return ss.str();
}

std::string operator+(float a, std::string& b){
    std::stringstream ss;
    ss << a << b;
    return ss.str();
}

std::string operator+(const std::string& a, float b){
    std::stringstream ss;
    ss << a << b;
    return ss.str();
}

std::string operator+(double a, const std::string& b){
    std::stringstream ss;
    ss << a << b;
    return ss.str();
}

std::string operator+(const std::string& a, double b){
    std::stringstream ss;
    ss << a << b;
    return ss.str();
}

std::string operator+(long double a, const std::string& b){
    std::stringstream ss;
    ss << a << b;
    return ss.str();
}

std::string operator+(const std::string& a, long double b){
    std::stringstream ss;
    ss << a << b;
    return ss.str();
}
