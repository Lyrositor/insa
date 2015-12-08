cmake_minimum_required(VERSION 2.8.4)
project(tp-oo_3 CXX)

# Set project properties
set(TP-OO3_BIN tp-oo_3)
set(TP-OO3_BIN_DIR bin)
set(TP-OO3_DEFINITIONS)
set(TP-OO3_FLAGS ${CC_COMMON_FLAGS} ${CXX_COMMON_FLAGS})
set(TP-OO3_INCLUDES include)
set(TP-OO3_MAIN src/main.cpp)
set(TP-OO3_SOURCES
        src/ConfigReader.cpp
        src/Document.cpp
        src/DotFileWriter.cpp
        src/HistoryManager.cpp
        src/Logger.cpp
        src/LogEntry.cpp
        src/LogReader.cpp)

# Make the use of colors in terminal output optional
option(TP-OO3_COLORS "Use colors in output" ON)
if (TP-OO3_COLORS)
    list(APPEND TP-OO3_DEFINITIONS -DCOLORS)
endif (TP-OO3_COLORS)
if (TP-OO_MAP)
    list(APPEND TP-OO3_DEFINITIONS -DMAP)
endif (TP-OO_MAP)

# Configure the executable's compilation
add_executable(${TP-OO3_BIN} ${TP-OO3_MAIN} ${TP-OO3_SOURCES})
set(TP-OO3_BIN_DIR_FULL ${CMAKE_CURRENT_SOURCE_DIR}/${TP-OO3_BIN_DIR})
set_target_properties(${TP-OO3_BIN} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${TP-OO3_BIN_DIR_FULL}
        RUNTIME_OUTPUT_DIRECTORY_RELEASE ${TP-OO3_BIN_DIR_FULL}
        RUNTIME_OUTPUT_DIRECTORY_DEBUG ${TP-OO3_BIN_DIR_FULL}
        RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO ${TP-OO3_BIN_DIR_FULL}
        RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL ${TP-OO3_BIN_DIR_FULL}
        CXX_STANDARD 11)

# Find the Boost.Regex library and link it
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost 1.50.0 REQUIRED COMPONENTS regex)
if (Boost_FOUND)
    list(APPEND TP-OO3_DEFINITIONS -DUSE_BOOST)
    include_directories(${Boost_INCLUDE_DIRS})
    target_link_libraries(${TP-OO3_BIN} ${Boost_LIBRARIES})
endif(Boost_FOUND)

# Add flags and definitions
if (TP-OO3_DEFINITIONS)
    target_compile_definitions(${TP-OO3_BIN} PRIVATE ${TP-OO3_DEFINITIONS})
endif (TP-OO3_DEFINITIONS)
if (TP-OO3_FLAGS)
    target_compile_options(${TP-OO3_BIN} PRIVATE ${TP-OO3_FLAGS})
endif (TP-OO3_FLAGS)
if (TP-OO3_INCLUDES)
    include_directories(${TP-OO3_INCLUDES})
endif (TP-OO3_INCLUDES)

# Generate a simple makefile for non-CMake compilation
if (COMMAND create_makefile)
    create_makefile(${CMAKE_CURRENT_SOURCE_DIR}/Makefile
            ${TP-OO3_BIN}
            ${TP-OO3_BIN_DIR}
            "${TP-OO3_SOURCES}"
            ${TP-OO3_MAIN}
            "-std=gnu++11;-O3;${TP-OO3_FLAGS}"
            "${TP-OO3_DEFINITIONS}"
            "${TP-OO3_INCLUDES}"
            "-lboost_regex"
            ${CMAKE_CURRENT_SOURCE_DIR})
endif (COMMAND create_makefile)

# Add test target
add_custom_target(tp-oo_3-test
    COMMAND ./mktest.sh
    DEPENDS ${TP-OO3_BIN}
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/tests)
