#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <string>

enum TerminalColor
{
    NONE = 0,
    BLACK,
    RED,
    GREEN,
    YELLOW,
    BLUE,
    MAGENTA,
    CYAN,
    WHITE
};

class Logger
{
public:
    template<typename ... ARGS> static void Error (ARGS ... args);
    template<typename ... ARGS> static void Info (ARGS ... args);
    template<typename ... ARGS> static void Warning (ARGS ... args);

protected:
    static constexpr char const * P = "\033[";

    template<typename ... ARGS> static void log (
            std::ostream & out, TerminalColor color,
            ARGS ... args
    );
    inline static void print (std::ostream & out);
    template<typename FIRST, typename ... ARGS> static void print (
            std::ostream & out, FIRST arg1, ARGS ... args
    );
};

#include "Logger.cpp"

#endif // LOGGER_H
