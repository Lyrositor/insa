#include <iostream>

#include "exceptions.h"
#include "parser.h"

/**
 * Main program entry-point.
 *
 * Prompts the user for an expression ad infinitum, until an empty expression
 * is provided.
 * @return
 */
int main ()
{
    Parser * parser = new Parser();

    for (;;)
    {
        // Read an input expression from stdin
        std::string input;
        std::cout << "> ";
        getline(std::cin, input);
        if (input.empty())
        {
            break;
        }

        // Parse the expression and display the result
        try
        {
            int result = parser->parse(input);
            std::cout << result << std::endl;
        } catch (const GlException & e) {
            std::cerr << "ERROR: " << e.what() << std::endl;
        }
    }

    delete parser;

    return 0;
}
