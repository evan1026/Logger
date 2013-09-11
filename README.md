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

    Logger logger(bool color); //true if you want unix-style color in the outputs
    
And you have access to its functions:

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
    
I've also provided a static function `Logger::makeString` that takes in any number of parameters and combines them all into a single string (assumming they all have the `<<` 
operator defined). Usage is as follows:

    logger.log(Logger::makeString(5, " is a number and ", 6 , "is too."));

which prints:
    
    5 is a number and 6 is too.

Each of the functions that takes a message also has a variant that takes a variable number of parameters just like `makeString` (see [Example Usage](#example-usage)).

Explaination
------------

The string is the message you want to log, the type is one of three types of output:

    Logger::LOG_INFO
    Logger::LOG_WARNING
    Logger::LOG_ERROR
    
The default type when not given is `LOG_INFO`.

The commands ending in `NoEndl` do not add a newline (`\n`) at the end of the line. This allows for the current line to be rewritten using the `rw` varieties. The line can also be cleared with `clearLine()`.

Where applicable, functions returning a boolean return whether or not the command was successful. An error indicates that the command could not be carried out (for instance, when clearing/rewriting a line that had a newline (i.e. clearing/rewriting even though previous command was not a `NoEndl` (p.s. nested parentheses ftw))).

`pause` outputs `Press enter to continue...` (unless another message is supplied) and then waits for the user to press enter before returning and allowing the program to continue.

The `continueln` commands continue a line, meaning they output to stdout without the type tag. This can be exploited to have clean outputs without the tags or to end a line that has been started but not finished. If you are using this library, please use these functions for that purpose and not cout, as they also take care of some behind-the-scenes work that keeps everything working smoothly.

Example Usage
-------------

    #include <Logger/Logger.hpp>
    Logger logger(true);
    logger.log("This is a normal message");
    logger.log(Logger::LOG_WARNING, "This one is a warning.");
    logger.log(Logger::LOG_ERROR, "This one is an error.");
    logger.pause("Now I'm going to wait until you press enter.");
    logger.logNoEndl("I think this line has a tipo.");
    logger.logrw("I can correct it though."); //Note: if you actually use it to correct typos, you should maybe get your head examined
    logger.logNoEndl("I don't ");
    logger.continuelnNoEndl("need to");
    logger.continuelnNoEndl(" do outputs in all one line.");
    logger.log("The level of fun using variatic templates is over ", 9000, "!!!");
    logger.log(Logger::LOG_WARNING, "The level should always go first!");
    logger.log("Otherwise it looks like this ->", Logger::LOG_WARNING);
    logger.log(Logger::makeString("Logger::makeString will", " make strings ", "for you..."));
    logger.log("But the ", "provided functions ", "are easier and ", "more readable.");

This is what all of that looks like at the end:

![awesomeness](https://dl.dropboxusercontent.com/u/16835571/Pictures/loggerScreenshot.png)

Credits
-------

The variatic template stuff was not my idea, merely my implementation (although it's barely even mine there too). [Joe](https://github.com/ginto8) was the one who thought it up,
and I saw it through his [logger project](https://github.com/Ginto8/log.hpp) which, in turn, was inspired by this project. Go check his stuff out and whatnot.
