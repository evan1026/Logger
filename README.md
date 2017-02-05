Logger
======

A simple logging tool written in c++.

Installation is easy, just include the headers in the files you need to use
them and make sure the .cpp file gets built with the rest of your project.

Usage
=====

To get started, all you need to do is include the header:

    #include "Logger.hpp"

and create an instance of the logger:

    Logger::Logger log;

From there, there are a number of functions you have access to:

`log.print`: Prints stuff to the output. Takes an arbitrary number of arguments
and prints them each to the output stream. Accepts any type of arguments as
long as they have a &lt;&lt; operator defined. <br>
Example usage: `logger.print(Levels::Info, "These ", "will ", "be ", "one ", "message.");` <br>
Note: You don't have to include a level, but if you want it to print the info
associated with the level, it has to be there.

`log.println`: Same as `log.print`, but prints a newline at the end.

`log.log`: calls `log.print` with `Levels::Info`.

`log.info`: same as `log.log`.

`log.warn`: calls `log.print` with `Levels::Warning`.

`log.warning`: same as `log.warn`.

`log.error`: calls `log.print` with `Levels::Error`

As for the levels, there are three that are included, `Info`, `Warning`, and
`Error`. You can make your own levels if you want. Just instantiate a new
`Logger::Level`. <br>
Example: `Logger::Level debug("[DEBUG] ", Logger::Color::Blue)`. <br>
The first argument is the prefix string. This is output before each line of
that level. The second argument is the color string. It gets output before
every line if colors are enabled. Colors are enabled on linux and MacOS and
they can be explicitly enabled or disabled per-stream. You can even add your
custom level object to the `Logger::Levels` namespace to keep everything together.

I mentioned colors being per-stream, so I should probably explain that too. The
`Logger` object has the ability to output to multiple streams. It supports any
object that is a decendant of `std::ostream`. The default constructor
instantiates a `Logger` to print to `std::cout` with colors enabled, but you can
change that:

    std::ofstream test("test.txt")
    Logger::Logger log(test, false); //Logger will print to test.txt without colors

From there, you can add more streams:

    log.addStream(std::cout, true); //Logger will now print to both test.txt (without color) and cout (with color)

Lastly, for the sake of convenience, I've created a global logger object. It can be
obtained in the header `GlobalLogger.hpp`, and is called `Logger::globalLogger`.
This way, you can just have one global logger across the entire project without
having to worry about reinstantiation across multiple files.
