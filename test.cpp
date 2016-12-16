#include <iostream>
#include <thread>
#include <chrono>
#include <fstream>

#include "Logger.hpp"

int main() {
    Logger::Logger log;

    std::ofstream test("test.txt");
    log.addStream(test, false);

    log.log("Hello world!");
    log.info("Here's some info");
    log.warn("Here's a warning");
    log.error("Here's an error");

    log.log("Here's some info with ", 1, " number in it");
    log.warn("Here's a warning with some ", "extra info");
    log.error("Here's an error", " split in two");

    log.print("You can write raw stuff too if you want.");
    log.info("But be careful because it could get messy");
}
