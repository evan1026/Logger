#include <iostream>
#include <thread>
#include <chrono>

#include "Logger.hpp"

int main() {
    Logger log;

    log.log("Hello world!");
    log.info("Here's some info");
    log.warn("Here's a warning");
    log.error("Here's an error");

    log.log("Here's some info with ", 1, " number in it");
    log.warn("Here's a warning with some ", "extra info");
    log.error("Here's an error", " split in two");
}
