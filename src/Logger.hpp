#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <string>
#include <iostream>
#include <sstream>

struct Logger {
    static const int LOG_INFO    = 0;
    static const int LOG_WARNING = 1;
    static const int LOG_ERROR   = 2;

    Logger(bool _color);
    
    void log(int type, std::string message);
    void log(std::string message);
    
    void logNoEndl(int type, std::string message);
    void logNoEndl(std::string message);
    
    void pause();
    void pause(std::string message);

    bool clearLine();

    bool logrw(int type, std::string message);
    bool logrw(std::string message);

    bool logrwNoEndl(int type, std::string message);
    bool logrwNoEndl(std::string message);

    void continueln(std::string message);
    void continuelnNoEndl(std::string message);

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
    void log(int type, Ts... parts){
        this->log(type, Logger::makeString(parts...));
    }
    template<class... Ts>
    void log(Ts... parts){
        this->log(Logger::makeString(parts...));
    }
    
    template<class... Ts>
    void logNoEndl(int type, Ts... parts){
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
    bool logrw(int type, Ts... parts){
        this->logrw(type, Logger::makeString(parts...));
    }
    template<class... Ts>
    bool logrw(Ts... parts){
        this->logrw(Logger::makeString(parts...));
    }

    template<class... Ts>
    bool logrwNoEndl(int type, Ts... parts){
        this->logrwNoEndl(type, Logger::makeString(parts...));
    }
    template<class... Ts>
    bool logrwNoEndl(Ts... parts){
        this->logrwNoEndl(Logger::makeString(parts...));
    }

    template<class... Ts>
    void continueln(Ts... parts){
        this->continueln(Logger::makeString(parts...));
    }
    template<class... Ts>
    void continuelnNoEndl(Ts... parts){
        this->continuelnNoEndl(Logger::makeString(parts...));
    }

    private:
        bool canRewrite;
        bool rewriting;
        bool color;
        std::size_t lastLength;
        std::string currentLine;

        void finishLine();
};

#endif
