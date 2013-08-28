Logger
======

A simple logging tool written in c++.

//Just include the Logger.cpp file.
I'm working on making a library you can install with cmake, just give me some time.

Usage
=====

Just declare a logger:

    Logger logger;
    
And you have access to its functions:

    void log(int type, std::string message, bool color);
    void log(int type, std::string message);
    void log(std::string message);
    void logNoEndl(int type, std::string message, bool color);
    void logNoEndl(int type, std::string message);
    void logNoEndl(std::string message);
    void pause();

The string is the message you want to log, the type is one of three types of output:

    Logger::LOG_INFO
    Logger::LOG_WARNING
    Logger::LOG_ERROR
    
The default type when not given is `LOG_INFO`.

When `color` is true, Linux style color codes are used. `LOG_INFO` is white, `LOG_WARNING` is yellow, and `LOG_ERROR` is red.
It defaults to false.

`logNoEndl` is the same as `log`, except it does not add a newline (`\n`) at the end of the line. I have plans to allow this to have rewritable lines, but I'll get to that later.

`pause` outputs `Press enter to continue...` and then waits for the user to press enter before returning and allowing the program to continue.
