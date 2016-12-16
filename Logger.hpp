#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <iostream>
#include <vector>
#include <memory>
#include <sstream>

namespace Logger {

    namespace Color {
        const std::string Black   = "\e[30m";
        const std::string Red     = "\e[31m";
        const std::string Green   = "\e[32m";
        const std::string Yellow  = "\e[33m";
        const std::string Blue    = "\e[34m";
        const std::string Magenta = "\e[35m";
        const std::string Cyan    = "\e[36m";
        const std::string White   = "\e[37m";
        const std::string NoColor = "\e[0m";
    };

    struct Level {
        std::string prefix, color;
        Level(std::string p, std::string c) : prefix(p), color(c) {}
    };

    namespace Levels {
        static Logger::Level Info   ("[INFO]  ", Logger::Color::NoColor);
        static Logger::Level Warning("[WARN]  ", Logger::Color::Yellow);
        static Logger::Level Error  ("[ERROR] ", Logger::Color::Red);
    };

    class Logger {

        struct Stream {
            std::shared_ptr<std::ostream> s;
            bool c;
        };

        private:
            std::vector<Stream> outStreams;

            void makeString(std::stringstream& ss, const Level& l) {
                ss << l.prefix;
            }

            template <typename T>
            void makeString(std::stringstream& ss, const T& t) {
                ss << t;
            }

            template <typename T, typename... Ts>
            void makeString(std::stringstream& ss, const T& t, const Ts&... ts) {
                makeString(ss, t);
                makeString(ss, ts...);
            }

            template <typename... Ts>
            std::string makeString(const Ts&... ts) {
                std::stringstream ss;
                makeString(ss, ts...);
                return ss.str();
            }

        public:
            Logger(std::ostream& o, bool color) {
                addStream(o, color);
            }
            Logger() : Logger(std::cout, true) {}
            ~Logger() {
                print(Color::NoColor);
            }

            void addStream(std::ostream& o, bool color) {
                Stream s;
                s.s = std::shared_ptr<std::ostream>(&o, [](std::ostream*){});
                s.c = color;

                outStreams.push_back(s);
            }

            template <typename... Args>
            void print(const Level& l, const Args&... args) {
                std::string line = makeString(l, args...);
                for (auto _stream : outStreams) {
                    if (_stream.c) {
                        *_stream.s << l.color;
                    }
                    *_stream.s << line;
                }
            }

            template <typename... Args>
            void print(const Args&... args) {
                std::string line = makeString(args...);
                for (auto _stream : outStreams) {
                    *_stream.s << line;
                }
            }

            template <typename... Args>
            void println(const Args&... args) {
                print(args...);
                for (auto _stream : outStreams) {
                    *_stream.s << std::endl;
                }
            }

            template <typename... Args>
            void log(const Args&... args) {
                println(Levels::Info, args...);
            }

            template <typename... Args>
            void info(const Args&... args) {
                println(Levels::Info, args...);
            }

            template <typename... Args>
            void warn(const Args&... args) {
                println(Levels::Warning, args...);
            }

            template <typename... Args>
            void warning(const Args&... args) {
                println(Levels::Warning, args...);
            }

            template <typename... Args>
            void error(const Args&... args) {
                println(Levels::Error, args...);
            }
    };
};

#endif
