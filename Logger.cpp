#include "Logger.hpp"

Logger::Logger(){}

void Logger::log(int type, std::string message, bool color){
    Logger::logNoEndl(type, message, color);
    std::cout << std::endl;
}

void Logger::log(int type, std::string message){
    Logger::log(type, message, false);
}

void Logger::log(std::string message){
    Logger::log(Logger::LOG_INFO, message);
}

void Logger::logNoEndl(int type, std::string message, bool color){
    std::string output = "";
    switch (type) {
        case Logger::LOG_INFO:
            output += "[INFO] ";
            break;
        case Logger::LOG_WARNING:
            output += (color ? "\e[33m[WARNING] " : "[WARNING] ");
            break;
        case Logger::LOG_ERROR:
            output += (color ?  "\e[31m[ERROR] " : "[ERROR] ");
            break;
        default:
            Logger::log(LOG_ERROR, "Log type not found");
            break;
    }
    output += message + (color ? "\e[m" : "");

    std::cout << output;
    std::cout.flush();
}

void Logger::logNoEndl(int type, std::string message){
    Logger::logNoEndl(type, message, false);
}

void Logger::logNoEndl(std::string message){
    Logger::logNoEndl(Logger::LOG_INFO, message);
}

void Logger::pause(){
    Logger::pause("Press enter to continue...");
}

void Logger::pause(std::string message){
    Logger::logNoEndl(message);
    std::cin.get();
}
