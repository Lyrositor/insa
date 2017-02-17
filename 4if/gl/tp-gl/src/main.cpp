#include <cstdlib>
#include <iostream>

#include "exceptions.h"
#include "parser.h"

/**
 * Main program entry-point.
 *
 * Prompts the user for an expression and returns the evaluated result.
 * @return EXIT_SUCCESS if successful, EXIT_FAILURE otherwise.
 */
int main ()
{
    Parser * parser = new Parser();

    // Read an input expression from stdin
    std::string input;
    getline(std::cin, input);
    if (input.empty())
    {
        return EXIT_SUCCESS;
    }

    // Parse the expression and display the result
    try
    {
        int result = parser->parse(input);
        std::cout << result << std::endl;
    } catch (const GlException & e) {
        std::cerr << "ERROR: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    delete parser;

    return EXIT_SUCCESS;
}
