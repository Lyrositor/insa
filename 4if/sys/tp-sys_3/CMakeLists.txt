cmake_minimum_required(VERSION 2.8.4)
project(tp-sys_3 C)

# Set project properties
set(TP-SYS3_BIN_DIR bin)

# Configure the executable's compilation
add_executable(tp-sys_3 main.c)
set(TP-SYS3_BIN_DIR_FULL ${CMAKE_CURRENT_SOURCE_DIR}/${TP-SYS3_BIN_DIR})
set_target_properties(tp-sys_3 PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${TP-SYS3_BIN_DIR_FULL}
        RUNTIME_OUTPUT_DIRECTORY_RELEASE ${TP-SYS3_BIN_DIR_FULL}
        RUNTIME_OUTPUT_DIRECTORY_DEBUG ${TP-SYS3_BIN_DIR_FULL}
        RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO ${TP-SYS3_BIN_DIR_FULL}
        RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL ${TP-SYS3_BIN_DIR_FULL})

# Add flags and definitions
if (TP-SYS3_FLAGS)
    target_compile_options(tp-sys_3 PRIVATE ${TP-SYS3_FLAGS})
endif (TP-SYS3_FLAGS)
