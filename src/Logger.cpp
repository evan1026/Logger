#include "Logger.hpp"

Logger::Logger(bool _color){
    canRewrite = false;
    rewriting = false;
    lastLength = 0;
    color = _color;
}

void Logger::log(int type, std::string message){
    
    this->logNoEndl(type, message);
    this->finishLine();

    canRewrite = false;
}

void Logger::log(std::string message){
    this->log(Logger::LOG_INFO, message);
}

void Logger::logNoEndl(int type, std::string message){
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

bool Logger::logrw(int type, std::string message){
    if (!this->clearLine()) return false;

    this->log(type, message);

    return true;
}

bool Logger::logrw(std::string message){
    return this->logrw(Logger::LOG_INFO, message);
}

bool Logger::logrwNoEndl(int type, std::string message){
    if (!this->clearLine()) return false;

    this->logNoEndl(type, message);
    
    return true;
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
    std::cout << (color ? "\e[m" : "") << std::endl;
    currentLine = "";
}

