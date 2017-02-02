#include "Logger.hpp"
#include "GlobalLogger.hpp"

namespace Logger {
    namespace Levels {
        /*! Level representing messages meant to inform */
        Level Info   ("[INFO]  ", Color::NoColor);
        /*! Level representing messages meant to warn */
        Level Warning("[WARN]  ", Color::Yellow);
        /*! Level representing messages displaying an error */
        Level Error  ("[ERROR] ", Color::Red);
    }
    /*! Logger that is defined globally by default to make it easy to use across files */
    Logger globalLogger;
}
