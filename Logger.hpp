#include <iostream>
#include <vector>
#include <memory>
#include <sstream>

class Logger {

    public:
        struct Color {
            static const std::string Black;
            static const std::string Red;
            static const std::string Green;
            static const std::string Yellow;
            static const std::string Blue;
            static const std::string Magenta;
            static const std::string Cyan;
            static const std::string White;
            static const std::string NoColor;
        };
        struct Level {
            static Level Info;
            static Level Warning;
            static Level Error;

            std::string prefix, color;
            Level(std::string p, std::string c) : prefix(p), color(c) {}
        };

    private:
        std::vector<std::shared_ptr<std::ostream>> outStreams;

        void addStreams(std::ostream& o) {
            outStreams.push_back(std::shared_ptr<std::ostream>(&o, [](std::ostream*){}));
        }

        template<typename... Streams>
        void addStreams(std::ostream& o, Streams&... s) {
            addStreams(o);
            addStreams(s...);
        }

        std::string makeString(const Level& l) {
            std::stringstream ss;
            ss << l.color << l.prefix;
            return ss.str();
        }

        template <typename T>
        std::string makeString(const T& t) {
            std::stringstream ss;
            ss << t;
            return ss.str();
        }

        template <typename T, typename... Ts>
        std::string makeString(const T& t, const Ts&... ts) {
            return makeString(t) + makeString(ts...);
        }

    public:
        template <typename... Streams>
        Logger(Streams&... s) {
            addStreams(s...);
        }
        Logger() : Logger(std::cout) {}
        ~Logger() {
            print(Color::NoColor);
        }

        template <typename... Args>
        void print(const Args&... args) {
            std::string line = makeString(args...);
            for (auto _stream : outStreams) {
                *_stream << line;
            }
        }

        template <typename... Args>
        void println(const Args&... args) {
            print(args...);
            for (auto _stream : outStreams) {
                *_stream << std::endl;
            }
        }

        template <typename... Args>
        void log(const Args&... args) {
            println(Level::Info, args...);
        }

        template <typename... Args>
        void info(const Args&... args) {
            println(Level::Info, args...);
        }

        template <typename... Args>
        void warn(const Args&... args) {
            println(Level::Warning, args...);
        }

        template <typename... Args>
        void warning(const Args&... args) {
            println(Level::Warning, args...);
        }

        template <typename... Args>
        void error(const Args&... args) {
            println(Level::Error, args...);
        }
};

const std::string Logger::Color::Black    = "\e[30m";
const std::string Logger::Color::Red      = "\e[31m";
const std::string Logger::Color::Green    = "\e[32m";
const std::string Logger::Color::Yellow   = "\e[33m";
const std::string Logger::Color::Blue     = "\e[34m";
const std::string Logger::Color::Magenta  = "\e[35m";
const std::string Logger::Color::Cyan     = "\e[36m";
const std::string Logger::Color::White    = "\e[37m";
const std::string Logger::Color::NoColor  = "\e[0m";

Logger::Level Logger::Level::Info   ("[INFO]  ", Logger::Color::NoColor);
Logger::Level Logger::Level::Warning("[WARN]  ", Logger::Color::Yellow);
Logger::Level Logger::Level::Error  ("[ERROR] ", Logger::Color::Red);
