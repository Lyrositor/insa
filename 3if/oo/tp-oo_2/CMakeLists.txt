cmake_minimum_required(VERSION 2.8.4)
project(tp-oo_2 CXX)

# Set project properties
set(TP-OO2_BIN tp-oo_2)
set(TP-OO2_BIN_DIR bin)
set(TP-OO2_FLAGS ${CC_COMMON_FLAGS} ${CXX_COMMON_FLAGS})
set(TP-OO2_MAIN src/main.cpp)
set(TP-OO2_SOURCES
        src/City.cpp
        src/Event.cpp
        src/EventLink.cpp
        src/HashTable.cpp
        src/SegmentedTable.cpp
        src/Sensor.cpp)

# Configure the executable's compilation
add_executable(${TP-OO2_BIN} ${TP-OO2_MAIN} ${TP-OO2_SOURCES})
set(TP-OO2_BIN_DIR_FULL ${CMAKE_CURRENT_SOURCE_DIR}/${TP-OO2_BIN_DIR})
set_target_properties(${TP-OO2_BIN} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${TP-OO2_BIN_DIR_FULL}
        RUNTIME_OUTPUT_DIRECTORY_RELEASE ${TP-OO2_BIN_DIR_FULL}
        RUNTIME_OUTPUT_DIRECTORY_DEBUG ${TP-OO2_BIN_DIR_FULL}
        RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO ${TP-OO2_BIN_DIR_FULL}
        RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL ${TP-OO2_BIN_DIR_FULL})
if (TP-OO2_FLAGS)
    target_compile_options(${TP-OO2_BIN} PRIVATE ${TP-OO2_FLAGS})
endif (TP-OO2_FLAGS)
