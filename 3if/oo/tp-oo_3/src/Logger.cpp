#ifndef LOGGER_CPP
#define LOGGER_CPP

#include "Logger.h"

template<typename ... ARGS> void Logger::Error (ARGS ... args)
{
    log(std::cerr, RED, "Error: ", args...);
}

template<typename ... ARGS> void Logger::Info (ARGS ... args)
{
    log(std::cout, NONE, args...);
}

template<typename ... ARGS> void Logger::Warning (ARGS ... args)
{
    log(std::cerr, YELLOW, "Warning: ", args...);
}

template<typename ... ARGS>
void Logger::log (std::ostream & out, TerminalColor color, ARGS ... args)
{
#ifdef COLORS
    if (color == NONE)
    {
#endif // COLORS
        print(out, args...);
#ifdef COLORS
    }
    else
    {
        print(out, P, 29 + color, "m", args..., P, "0m");
    }
#endif // COLORS
}

void Logger::print (std::ostream & out)
{
    out << std::endl;
}

template<typename FIRST, typename ... ARGS>
void Logger::print (std::ostream & out, FIRST arg1, ARGS ... args)
{
    out << arg1;
    print(out, args...);
};

#endif // LOGGER_CPP
