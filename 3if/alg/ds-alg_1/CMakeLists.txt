cmake_minimum_required(VERSION 2.8.4)
project(ds-alg_1 CXX)

# Set project properties
set(DS-ALG1_BIN_DIR bin)
set(DS-ALG1_FLAGS ${CC_COMMON_FLAGS} ${CXX_COMMON_FLAGS})

# Configure the executable's compilation
add_executable(pbl1 pbl1.cpp)
add_executable(pbl2 pbl2.cpp)
add_executable(pbl3 pbl3.cpp)
set(DS-ALG1_BIN_DIR_FULL ${CMAKE_CURRENT_SOURCE_DIR}/${DS-ALG1_BIN_DIR})
set_target_properties(pbl1 pbl2 pbl3 PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${DS-ALG1_BIN_DIR_FULL}
        RUNTIME_OUTPUT_DIRECTORY_RELEASE ${DS-ALG1_BIN_DIR_FULL}
        RUNTIME_OUTPUT_DIRECTORY_DEBUG ${DS-ALG1_BIN_DIR_FULL}
        RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO ${DS-ALG1_BIN_DIR_FULL}
        RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL ${DS-ALG1_BIN_DIR_FULL}
        CXX_STANDARD 11)

# Add flags and definitions
if (DS-ALG1_FLAGS)
    target_compile_options(pbl1 PRIVATE ${DS-ALG1_FLAGS})
    target_compile_options(pbl2 PRIVATE ${DS-ALG1_FLAGS})
    target_compile_options(pbl3 PRIVATE ${DS-ALG1_FLAGS})
endif (DS-ALG1_FLAGS)
