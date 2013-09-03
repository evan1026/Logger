Logger
======

A simple logging tool written in c++.

Installation is easy:

    $ mkdir build
    $ cd build
    $ cmake ..
    $ make && sudo make install
    
That will install the necessary files. In order to use, just link up the header and library (found /usr/local/include/Logger and /usr/local/lib, respectively).

For CMake, you just need to add the module path:

    set(CMAKE_MODULE_PATH "/usr/local/share/Logger/;${CMAKE_MODULE_PATH}")

then add the library:

    find_package(Logger REQUIRED)
    target_link_libraries(${EXECUTABLE_NAME} Logger)

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
    void pause(std::string message);
    bool clearLine();
    bool logrw(int type, std::string message, bool color);
    bool logrw(int type, std::string message);
    bool logrw(std::string message);
    bool logrwNoEndl(int type, std::string message, bool color);
    bool logrwNoEndl(int type, std::string message);
    bool logrwNoEndl(std::string message);
    void continueln(std::string message);
    void continuelnNoEndl(std::string message);

As well as the operators it defines (note that the operators are non-member functions):

    std::string operator+(bool a, const std::string& b);
    std::string operator+(const std::string& a, bool b);
    std::string operator+(short a, const std::string& b);
    std::string operator+(const std::string& a, short b);
    std::string operator+(unsigned short a, const std::string& b);
    std::string operator+(const std::string& a, unsigned short b);
    std::string operator+(int a, const std::string& b);
    std::string operator+(const std::string& a, int b);
    std::string operator+(unsigned int a, const std::string& b);
    std::string operator+(const std::string& a, unsigned int b);
    std::string operator+(long a, const std::string& b);
    std::string operator+(const std::string& a, long b);
    std::string operator+(unsigned long a, const std::string& b);
    std::string operator+(const std::string& a, unsigned long b);
    std::string operator+(long long a, const std::string& b);
    std::string operator+(const std::string& a, long long b);
    std::string operator+(unsigned long long a, const std::string& b);
    std::string operator+(const std::string& a, unsigned long long b);
    std::string operator+(float a, const std::string& b);
    std::string operator+(const std::string& a, float b);
    std::string operator+(double a, const std::string& b);
    std::string operator+(const std::string& a, double b);
    std::string operator+(long double a, const std::string& b);
    std::string operator+(const std::string& a, long double b);

Note that since all of these take strings, the following code will not work as expected:

    logger.log(5 + " is a number.")

This is because the quoted text is of the type `char*`, `not std::string`, so rather than concatenating, it will advance the pointer by five and then output the remaining text
after that (which ends up being `" number."`). For obvious reasons, I can't redefine this operator (although I may make a new one in the future if I can think of one that makes
sense), so the best way to to what you want here is:

    logger.log(5 + std::string(" is a number."));

Explaination
------------

The string is the message you want to log, the type is one of three types of output:

    Logger::LOG_INFO
    Logger::LOG_WARNING
    Logger::LOG_ERROR
    
The default type when not given is `LOG_INFO`.

When `color` is true, Linux style color codes are used. `LOG_INFO` is white, `LOG_WARNING` is yellow, and `LOG_ERROR` is red.
It defaults to false.

The commands ending in `NoEndl` do not add a newline (`\n`) at the end of the line. This allows for the current line to be rewritten using the `rw` varieties. The line can also be cleared with `clearLine()`.

Where applicable, functions returning a boolean return whether or not the command was successful. An error indicates that the command could not be carried out (for instance, when clearing/rewriting a line that had a newline (i.e. clearing/rewriting even though previous command was not a `NoEndl` (p.s. nested parentheses ftw))).

`pause` outputs `Press enter to continue...` (unless another message is supplied) and then waits for the user to press enter before returning and allowing the program to continue.

The `continueln` commands continue a line, meaning they output to stdout without the type tag. This can be exploited to have clean outputs without the tags or to end a line that has been started but not finished. If you are using this library, please use these functions for that purpose and not cout, as they also take care of some behind-the-scenes work that keeps everything working smoothly.
