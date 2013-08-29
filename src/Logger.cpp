#include "Logger.hpp"

Logger::Logger(){
    canRewrite = false;
    rewriting = false;
    lastLength = 0;
}

void Logger::log(int type, std::string message, bool color){
    this->logNoEndl(type, message, color);
    std::cout << std::endl;

    canRewrite = false;
}

void Logger::log(int type, std::string message){
    this->log(type, message, false);
}

void Logger::log(std::string message){
    this->log(Logger::LOG_INFO, message);
}

void Logger::logNoEndl(int type, std::string message, bool color){
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
    output += message + (color ? "\e[m" : "");

    if (rewriting && thisLength < lastLength){
        for (int i = 0; i < lastLength - thisLength; i++){
            output += " ";
        }
        thisLength = lastLength;
    }

    lastLength = thisLength;

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
