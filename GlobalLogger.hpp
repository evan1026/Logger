#ifndef GLOBAL_LOGGER_HPP
#define GLOBAL_LOGGER_HPP

#include "Logger.hpp"

// This file defines a global logger that anyone can use
// Include it in all the files you need and they'll share a logger

namespace Logger {
    Logger globalLogger;
}

#endif
