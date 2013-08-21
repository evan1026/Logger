#include "Logger.hpp"

void Logger::log(int type, std::string message, bool color){
    switch (type) {
        case Logger::LOG_INFO:
            std::cout << "[INFO] ";
            break;
        case Logger::LOG_WARNING:
            std::cout << (color ? "\e[33m[WARNING] " : "[WARNING] ");
            break;
        case Logger::LOG_ERROR:
            std::cout << (color ?  "\e[31m[ERROR] " : "[ERROR] ");
            break;
        default:
            Logger::log(LOG_ERROR, "Log type not found");
            break;
    }
    std::cout << message << (color ? "\e[m" : "") << std::endl;
    prevLength = message.length() + (color ? 5 : 1);
}

void Logger::log(int type, std::string message){
    Logger::log(type, message, false);
}

void Logger::log(std::string message){
    Logger::log(Logger::LOG_INFO, message);
}

void Logger::logrw(int type, std::string message, bool color){
    Logger::eraseLast();
    Logger::log(type, message, color);
}

void Logger::logrw(int type, std::string message){
    Logger::logrw(type, message, false);
}

void Logger::logrw(std::string message){
    Logger::logrw(Logger::LOG_INFO, message);
}

void Logger::eraseLast(){
    for (int i = 0; i < Logger::prevLength; i++){
        std::cout << "\b";
    }
    std::cout.flush();
    prevLength = 0;
}
