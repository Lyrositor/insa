#include "Logger.h"

void Logger::error (std::string message)
{
    log("Error: " + message, std::cerr, RED);
}

void Logger::info (std::string message)
{
    log(message, std::cout);
}

void Logger::warning (std::string message)
{
    log("Warning: " + message, std::cerr, YELLOW);
}

void Logger::log (std::string message, std::ostream & out, TerminalColor color)
{
#ifdef COLORS
    if (color == NONE)
    {
#endif // COLORS
        std::cout << message << std::endl;
#ifdef COLORS
    }
    else
    {
        std::string p = "\033[";
        std::cout << p << 29+color << "m" << message << p << "0m" << std::endl;
    }
#endif // COLORS
}
