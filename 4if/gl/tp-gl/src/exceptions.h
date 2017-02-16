#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <string>
#include <stdexcept>

class GlException : public std::runtime_error
{
public:
    GlException(std::string what) : std::runtime_error(what) {}
};

#endif // EXCEPTIONS_H
