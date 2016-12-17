#include "Logger.hpp"
#include "GlobalLogger.hpp"

namespace Logger {
    namespace Levels {
        Level Info   ("[INFO]  ", Color::NoColor);
        Level Warning("[WARN]  ", Color::Yellow);
        Level Error  ("[ERROR] ", Color::Red);
    }
    Logger globalLogger;
}
