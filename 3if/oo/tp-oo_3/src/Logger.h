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
    static void error (std::string message);
    static void info (std::string message);
    static void warning (std::string message);

protected:
    static void log (
            std::string message, std::ostream& out, TerminalColor color = NONE
    );
};


#endif // LOGGER_H
