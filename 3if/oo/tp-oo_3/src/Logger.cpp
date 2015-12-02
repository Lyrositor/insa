#include <stdio.h>

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

void Logger::log (std::string message, std::ostream& out, TerminalColor color)
{
#ifdef COLORS
    if (color == NONE)
    {
#endif // COLORS
        printf("%s\n", message.c_str());
#ifdef COLORS
    }
    else
    {
        printf("\033[%dm%s\033[0m\n", 29 + color, message.c_str());
    }
#endif // COLORS
}
