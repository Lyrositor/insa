cmake_minimum_required(VERSION 2.8.4)
project(tp-gl CXX)

# Set project properties
set(TP-GL_BIN tp-gl)
set(TP-GL_BIN_DIR bin)
set(TP-GL_DEFINITIONS)
set(TP-GL_FLAGS ${CC_COMMON_FLAGS} ${CXX_COMMON_FLAGS})
set(TP-GL_INCLUDES)
set(TP-GL_MAIN src/main.cpp)
set(TP-GL_SOURCES
        src/lexer.cpp
        src/parser.cpp
        src/states.cpp
        src/tokens.cpp)

# Configure the executable's compilation
add_executable(${TP-GL_BIN} ${TP-GL_MAIN} ${TP-GL_SOURCES})
set(TP-GL_BIN_DIR_FULL ${CMAKE_CURRENT_SOURCE_DIR}/${TP-GL_BIN_DIR})
set_target_properties(${TP-GL_BIN} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${TP-GL_BIN_DIR_FULL}
        RUNTIME_OUTPUT_DIRECTORY_RELEASE ${TP-GL_BIN_DIR_FULL}
        RUNTIME_OUTPUT_DIRECTORY_DEBUG ${TP-GL_BIN_DIR_FULL}
        RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO ${TP-GL_BIN_DIR_FULL}
        RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL ${TP-GL_BIN_DIR_FULL}
        CXX_STANDARD 11)

# Add flags and definitions
if (TP-GL_DEFINITIONS)
    target_compile_definitions(${TP-GL_BIN} PRIVATE ${TP-GL_DEFINITIONS})
endif (TP-GL_DEFINITIONS)
if (TP-GL_FLAGS)
    target_compile_options(${TP-GL_BIN} PRIVATE ${TP-GL_FLAGS})
endif (TP-GL_FLAGS)
if (TP-GL_INCLUDES)
    include_directories(${TP-GL_INCLUDES})
endif (TP-GL_INCLUDES)

# Generate a simple makefile for non-CMake compilation
if (COMMAND create_makefile)
    create_makefile(${CMAKE_CURRENT_SOURCE_DIR}/Makefile
            ${TP-GL_BIN}
            ${TP-GL_BIN_DIR}
            "${TP-GL_SOURCES}"
            ${TP-GL_MAIN}
            "-std=gnu++11;-O3;${TP-GL_FLAGS}"
            "${TP-GL_DEFINITIONS}"
            "${TP-GL_INCLUDES}"
            ""
            ${CMAKE_CURRENT_SOURCE_DIR})
endif (COMMAND create_makefile)
