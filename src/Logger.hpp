#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <string>
#include <iostream>
#include <sstream>

struct Logger {

    enum LogType {
        Info,
        Warning,
        Error
    };

    struct Settings {

            std::string infoColor,
                        warningColor,
                        errorColor;

            Settings();
            Settings(std::string _infoColor, std::string _warningColor, std::string _errorColor) :
                    infoColor(_infoColor), warningColor(_warningColor), errorColor(_errorColor) {}

    };

    Settings settings;

    Logger();
    explicit Logger(Settings _settings);

    void log(LogType type, std::string message);
    void log(std::string message);

    void logNoEndl(LogType type, std::string message);
    void logNoEndl(std::string message);

    void pause();
    void pause(std::string message);

    bool clearLine();

    bool logrw(LogType type, std::string message);
    bool logrw(std::string message);

    bool logrwNoEndl(LogType type, std::string message);
    bool logrwNoEndl(std::string message);

    void continueln(std::string message);
    void continuelnNoEndl(std::string message);

    std::string getInput();
    std::string getInput(std::string prompt);

    template<class T>
    static std::string makeString(const T& thing){
        std::stringstream ss;
        ss << thing;
        return ss.str();
    }
    template<class T, class... Ts>
    static std::string makeString(const T& firstPart, Ts... otherParts){
        std::stringstream ss;
        ss << firstPart;
        return ss.str() + makeString(otherParts...);
    }

    template<class... Ts>
    void log(LogType type, Ts... parts){
        this->log(type, Logger::makeString(parts...));
    }
    template<class... Ts>
    void log(Ts... parts){
        this->log(Logger::makeString(parts...));
    }

    template<class... Ts>
    void logNoEndl(LogType type, Ts... parts){
        this->logNoEndl(type, Logger::makeString(parts...));
    }
    template<class... Ts>
    void logNoEndl(Ts... parts){
        this->logNoEndl(Logger::makeString(parts...));
    }

    template<class... Ts>
    void pause(Ts... parts){
        this->pause(Logger::makeString(parts...));
    }

    template<class... Ts>
    bool logrw(LogType type, Ts... parts){
        return this->logrw(type, Logger::makeString(parts...));
    }
    template<class... Ts>
    bool logrw(Ts... parts){
        return this->logrw(Logger::makeString(parts...));
    }

    template<class... Ts>
    bool logrwNoEndl(LogType type, Ts... parts){
        return this->logrwNoEndl(type, Logger::makeString(parts...));
    }
    template<class... Ts>
    bool logrwNoEndl(Ts... parts){
        return this->logrwNoEndl(Logger::makeString(parts...));
    }

    template<class... Ts>
    void continueln(Ts... parts){
        this->continueln(Logger::makeString(parts...));
    }
    template<class... Ts>
    void continuelnNoEndl(Ts... parts){
        this->continuelnNoEndl(Logger::makeString(parts...));
    }

    template<class... Ts>
    std::string getInput(Ts... parts){
        return this->getInput(Logger::makeString(parts...));
    }

    private:
        bool canRewrite;
        bool rewriting;
        std::size_t lastLength;
        std::string currentLine;

        void finishLine();

};

namespace LogColor {
    static const std::string Black   = "\e[30m";
    static const std::string Red     = "\e[31m";
    static const std::string Green   = "\e[32m";
    static const std::string Yellow  = "\e[33m";
    static const std::string Blue    = "\e[34m";
    static const std::string Magenta = "\e[35m";
    static const std::string Cyan    = "\e[36m";
    static const std::string White   = "\e[37m";

};

#endif
