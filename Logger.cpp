#include "Logger.hpp"

const int Logger::LOG_INFO    = 0;
const int Logger::LOG_WARNING = 1;
const int Logger::LOG_ERROR   = 2;

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
}

void Logger::log(int type, std::string message){
    Logger::log(type, message, false);
}

void Logger::log(std::string message){
    Logger::log(Logger::LOG_INFO, message);
}
