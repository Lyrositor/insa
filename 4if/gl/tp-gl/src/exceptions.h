#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <string>
#include <stdexcept>

class GlException : public std::runtime_error
{
public:
    GlException(std::string w) : std::runtime_error(w) {}
};

#endif // EXCEPTIONS_H
