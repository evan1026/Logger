#ifndef LOGGER_HPP
#define LOGGER_HPP

#if defined(linux) || defined(__linux) || defined(__linux__) || defined(Macintosh) || defined(macintosh) || (defined(__APPLE__) && defined(__MACH__))
    #define COLOR_SUPPORT
#endif

#include <iostream>
#include <vector>
#include <memory>
#include <sstream>

/*!
 * Container namspace for everything having to do with the logger
 */
namespace Logger {

    /*!
     * Namespace containing predefined colors. You can make your own too, but these are provided.
     *
     * Note that because of the way doxygen parses files, it will display the empty string versions
     * of these colors (for when color is not supported) even if colors are supported on your system.
     */
    namespace Color {
        #ifdef COLOR_SUPPORT
            /*! String corresponding to the unix code for black */
            const std::string Black   = "\e[30m";
            /*! String corresponding to the unix code for red */
            const std::string Red     = "\e[31m";
            /*! String corresponding to the unix code for green */
            const std::string Green   = "\e[32m";
            /*! String corresponding to the unix code for yellow */
            const std::string Yellow  = "\e[33m";
            /*! String corresponding to the unix code for blue */
            const std::string Blue    = "\e[34m";
            /*! String corresponding to the unix code for magenta */
            const std::string Magenta = "\e[35m";
            /*! String corresponding to the unix code for cyan */
            const std::string Cyan    = "\e[36m";
            /*! String corresponding to the unix code for white */
            const std::string White   = "\e[37m";
            /*! String corresponding to the unix code for the default color */
            const std::string NoColor = "\e[0m";
        #else
            /*! Empty string since color isn't supported */
            const std::string Black   = "";
            /*! Empty string since color isn't supported */
            const std::string Red     = "";
            /*! Empty string since color isn't supported */
            const std::string Green   = "";
            /*! Empty string since color isn't supported */
            const std::string Yellow  = "";
            /*! Empty string since color isn't supported */
            const std::string Blue    = "";
            /*! Empty string since color isn't supported */
            const std::string Magenta = "";
            /*! Empty string since color isn't supported */
            const std::string Cyan    = "";
            /*! Empty string since color isn't supported */
            const std::string White   = "";
            /*! Empty string since color isn't supported */
            const std::string NoColor = "";
        #endif
    };

    /*!
     * Simple data container for logging levels which are represented as a prefix and a color.
     *
     * So, for instance, the warning built-in level is ("[WARN]  ", Color::Yellow). This means
     * that every message with the waning level will be displayed in yellow (if supported) and
     * with have the prefix "[WARN]  " before the line.
     */
    struct Level {
        /*! The string representing the prefix to put before the line when logging with this level */
        std::string prefix;
        /*! The string representing the color to make the line if colors are being used */
        std::string color;

        /*! \callergraph
         *
         * Constructs a new level
         *
         * \p p - Prefix string    <br>
         * \p c - Color string     <br>
         */
        Level(std::string p, std::string c) : prefix(p), color(c) {}
    };

    /*!
     * Namespace containing the built-in levels
     */
    namespace Levels {
        extern Logger::Level Info;
        extern Logger::Level Warning;
        extern Logger::Level Error;
    };

    /*!
     * Logger class
     *
     * TODO better documentation
     */
    class Logger {

        struct Stream {
            std::shared_ptr<std::ostream> s;
            bool c;
        };

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

            /*! \callergraph
             *
             * Constructs a new logger
             *
             * \p o - std::ostream to print the data to                   <br>
             * \p color - Whether or not to print colors with the data    <br>
             */
            Logger(std::ostream& o, bool color) {
                addStream(o, color);
            }

            /*! \callergraph
             *
             * Default constructor which creates a logger that logs to std::cout with color
             */
            Logger() : Logger(std::cout, true) {}

            /*! \callergraph
             *
             * Adds a new std::ostream to the logger, so that you can output to multiple
             * streams at the same time
             *
             * \p o - std::ostream to print the data to                   <br>
             * \p color - Whether or not to print colors with the data    <br>
             */
            void addStream(std::ostream& o, bool color) {
                Stream s;
                s.s = std::shared_ptr<std::ostream>(&o, [](std::ostream*){});
                s.c = color;

                outStreams.push_back(s);
            }

            /*! \callergraph
             *
             * Prints stuff to the output. Takes an arbitrary number of arguments and
             * prints them each to the output stream. Accepts any type of arguments
             * as long as they have a << operator defined.
             *
             * Example usage:
             * logger.print(Levels::Info, "These ", "will ", "be ", "one ", "message.");
             *
             * \p l - Level to use for this line
             * \p args - Stuff to print
             */
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

            /*! \callergraph
             *
             * See docs for the other version of print()
             *
             * This version doesn't output anything having to do with the level,
             * so if no newline was used on the last call of print(), this version
             * can be used to continue writing to the line.
             */
            template <typename... Args>
            void print(const Args&... args) {
                std::string line = makeString(args...);
                for (auto _stream : outStreams) {
                    *_stream.s << line;
                }
            }

            /*! \callergraph
             *
             * Like print(), but inserts a newline afterward.
             *
             * Since this version takes care of colors as well, it should
             * be preferred over print().
             */
            template <typename... Args>
            void println(const Args&... args) {
                print(args...);
                for (auto _stream : outStreams) {
                    *_stream.s << std::endl;
                    if (_stream.c) {
                        *_stream.s << Color::NoColor;
                    }
                }
            }

            /*! \callergraph
             *
             * Calls println() with Levels::Info and whatever you send it
             */
            template <typename... Args>
            void log(const Args&... args) {
                println(Levels::Info, args...);
            }

            /*! \callergraph
             *
             * Same as log()
             */
            template <typename... Args>
            void info(const Args&... args) {
                println(Levels::Info, args...);
            }

            /*! \callergraph
             *
             * Calls println() with Levels::Warning and whatever you send it
             */
            template <typename... Args>
            void warn(const Args&... args) {
                println(Levels::Warning, args...);
            }

            /*! \callergraph
             *
             * Same as warn()
             */
            template <typename... Args>
            void warning(const Args&... args) {
                println(Levels::Warning, args...);
            }

            /*! \callergraph
             *
             * Calls println() with Levels::Error and whatever you send it
             */
            template <typename... Args>
            void error(const Args&... args) {
                println(Levels::Error, args...);
            }
    };
};

#endif
