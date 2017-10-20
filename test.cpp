#include <fstream>

#include "GlobalLogger.hpp"

auto& _log = Logger::globalLogger;

namespace Logger {
    namespace Levels {
        Level Custom("[Custom] ", Color::Green);
    }
}

int main() {
    std::ofstream file_with_color, file_without_color;

    file_with_color.open("With_Color.txt");
    file_without_color.open("Without_Color.txt");

    _log.addStream(file_with_color, true);
    _log.addStream(file_without_color, false);

    _log.info("This is info log");
    _log.warn("This is warning log");
    _log.error("This is error log");

    _log.info("This ", "info ", "has ", 5, " parts.");
    _log.warn("This ", "warning ", "has ", 5, " parts.");
    _log.error("This ", "error ", "has ", 5, " parts.");

    _log.println("This is a raw println");
    _log.println("This is a raw println with ", 3, " parts.");
    _log.println(Logger::Levels::Error, "This is a println with a level before it");
    _log.println(Logger::Levels::Custom, "This is a println with a custom level.");

    _log.print("This is a raw print with a newline added by me\n");
    _log.print("This is a raw print with ", 3, " parts and a newline\n");
    _log.print(Logger::Levels::Custom, "This is a raw print with a custom level and a newline\n");

    file_with_color.close();
    file_without_color.close();
}
