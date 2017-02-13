#include <iostream>

#include "Automaton.h"

int main ()
{
    Automaton * parser = new Automaton();

    for (;;)
    {
        // Read an input expression from stdin
        std::string input;
        std::cout << "Input expression: " << std::endl;
        std::cin >> input;
        if (input.empty())
        {
            break;
        }

        // Parse the expression and display the result
        try
        {
            int result = parser->parse(input);
            std::cout << "Result: " << result << std::endl;
        } catch (std::exception & e) {
            std::cout << "ERROR: " << e.what() << std::endl;
        }

    }

    delete parser;

    return 0;
}
