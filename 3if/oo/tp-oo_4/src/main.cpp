#include <exception>
#include <iostream>

#include "Editor.h"

int main(int argc, char* argv[])
{
    // Disable synchronization with the C IO library to speed up input and
    // output.
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
