#include <iostream>

#include "Symbol.h"

void Symbol::print () const
{
    std::cout << static_cast<int>(ident);
}
