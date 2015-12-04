cmake_minimum_required(VERSION 2.8.4)
project(tp-oo_1 CXX)

# Set project properties
set(TP-OO1_BIN tp-oo_1)
set(TP-OO1_BIN_DIR bin)
set(TP-OO1_FLAGS)
set(TP-OO1_MAIN src/main.cpp)
set(TP-OO1_SOURCES
        src/CollectionEntiers.cpp)

# Configure the executable's compilation
add_executable(tp-oo_1 ${TP-OO1_MAIN} ${TP-OO1_SOURCES})
set(TP-OO1_BIN_DIR_FULL ${CMAKE_CURRENT_SOURCE_DIR}/${TP-OO1_BIN_DIR})
set_target_properties(tp-oo_1 PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${TP-OO1_BIN_DIR_FULL}
        RUNTIME_OUTPUT_DIRECTORY_RELEASE ${TP-OO1_BIN_DIR_FULL}
        RUNTIME_OUTPUT_DIRECTORY_DEBUG ${TP-OO1_BIN_DIR_FULL}
        RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO ${TP-OO1_BIN_DIR_FULL}
        RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL ${TP-OO1_BIN_DIR_FULL})
if (TP-OO1_FLAGS)
    target_compile_options(${TP-OO1_BIN} PRIVATE ${TP-OO1_FLAGS})
endif (TP-OO1_FLAGS)
