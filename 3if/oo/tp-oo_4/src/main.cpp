#include <exception>
#include <iostream>

#include "Editor.h"

int main(int argc, char* argv[])
{
    std::ios_base::sync_with_stdio(false);

    Editor editor;
    try {
        editor.run();
    } catch (std::exception e) {
        std::cerr << "[FATAL] " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
