#include "Logger.hpp"

Logger::Logger() : settings() {
    canRewrite = false;
    rewriting = false;
    lastLength = 0;
}

Logger::Logger(Settings _settings) : settings(_settings) {
    canRewrite = false;
    rewriting = false;
    lastLength = 0;
}

Logger::Settings::Settings(){
    infoColor = "\e[37m";
    warningColor = "\e[33m";
    errorColor = "\e[31m";
}

void Logger::log(LogType type, std::string message){

    this->logNoEndl(type, message);
    this->finishLine();

    canRewrite = false;
}

void Logger::log(std::string message){
    this->log(Logger::LogType::Info, message);
}

void Logger::logNoEndl(LogType type, std::string message){
    if (canRewrite) this->finishLine();

    std::string output = "";
    std::size_t thisLength = message.length();
    switch (type) {
        case Logger::LogType::Info:
            output += settings.infoColor + "[INFO] ";
            thisLength += 7;
            break;
        case Logger::LogType::Warning:
            output += settings.warningColor + "[WARNING] ";
            thisLength += 10;
            break;
        case Logger::LogType::Error:
            output += settings.errorColor + "[ERROR] ";
            thisLength += 8;
            break;
        default:
            this->log(Logger::LogType::Error, "Log type not found");
            break;
    }

    output += message;

    if (rewriting && thisLength < lastLength){
        for (unsigned int i = 0; i < lastLength - thisLength; ++i){
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
    this->logNoEndl(Logger::LogType::Info, message);
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

    for (unsigned int i = 0; i < lastLength; ++i){
        std::cout << "\b";
    }
    std::cout.flush();

    canRewrite = false;
    rewriting = true;

    return true;
}

bool Logger::logrw(LogType type, std::string message){
    if (!this->clearLine()) return false;

    this->log(type, message);

    return true;
}

bool Logger::logrw(std::string message){
    return this->logrw(Logger::LogType::Info, message);
}

bool Logger::logrwNoEndl(LogType type, std::string message){
    if (!this->clearLine()) return false;

    this->logNoEndl(type, message);

    return true;
}

bool Logger::logrwNoEndl(std::string message){
    return this->logrwNoEndl(Logger::LogType::Info, message);
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
    std::cout << settings.infoColor << std::endl;
    currentLine = "";
}

std::string Logger::getInput(){
    return this->getInput("Please give an input: ");
}

std::string Logger::getInput(std::string prompt){
    this->logNoEndl(prompt);

    std::string output;
    std::getline(std::cin, output);

    canRewrite = false;

    return output;
}
