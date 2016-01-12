cmake_minimum_required(VERSION 2.8.4)
project(tp-oo_4 CXX)

# Set project properties
set(TP-OO4_BIN tp-oo_4)
set(TP-OO4_BIN_DIR bin)
set(TP-OO4_DEFINITIONS)
set(TP-OO4_FLAGS ${CC_COMMON_FLAGS} ${CXX_COMMON_FLAGS})
set(TP-OO4_INCLUDES include)
set(TP-OO4_MAIN src/main.cpp)
set(TP-OO4_SOURCES
        src/Canvas.cpp
        src/ConvexPolygon.cpp
        src/Editor.cpp
        src/Figure.cpp
        src/FigureGroup.cpp
        src/HistoryManager.cpp
        src/Intersection.cpp
        src/Polygon.cpp
        src/Rectangle.cpp
        src/Segment.cpp
        src/Union.cpp
        src/Vector2D.cpp)

# Make the use of colors in terminal output optional
if (TP-OO_MAP)
    list(APPEND TP-OO4_DEFINITIONS -DMAP)
endif (TP-OO_MAP)

# Configure the executable's compilation
add_executable(${TP-OO4_BIN} ${TP-OO4_MAIN} ${TP-OO4_SOURCES})
set(TP-OO4_BIN_DIR_FULL ${CMAKE_CURRENT_SOURCE_DIR}/${TP-OO4_BIN_DIR})
set_target_properties(${TP-OO4_BIN} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${TP-OO4_BIN_DIR_FULL}
        RUNTIME_OUTPUT_DIRECTORY_RELEASE ${TP-OO4_BIN_DIR_FULL}
        RUNTIME_OUTPUT_DIRECTORY_DEBUG ${TP-OO4_BIN_DIR_FULL}
        RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO ${TP-OO4_BIN_DIR_FULL}
        RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL ${TP-OO4_BIN_DIR_FULL}
        CXX_STANDARD 11)

# Add flags and definitions
if (TP-OO4_DEFINITIONS)
    target_compile_definitions(${TP-OO4_BIN} PRIVATE ${TP-OO4_DEFINITIONS})
endif (TP-OO4_DEFINITIONS)
if (TP-OO4_FLAGS)
    target_compile_options(${TP-OO4_BIN} PRIVATE ${TP-OO4_FLAGS})
endif (TP-OO4_FLAGS)
if (TP-OO4_INCLUDES)
    include_directories(${TP-OO4_INCLUDES})
endif (TP-OO4_INCLUDES)

# Generate a simple makefile for non-CMake compilation
if (COMMAND create_makefile)
    create_makefile(${CMAKE_CURRENT_SOURCE_DIR}/Makefile
            ${TP-OO4_BIN}
            ${TP-OO4_BIN_DIR}
            "${TP-OO4_SOURCES}"
            ${TP-OO4_MAIN}
            "-std=gnu++11;-O3;${TP-OO4_FLAGS}"
            "${TP-OO4_DEFINITIONS}"
            "${TP-OO4_INCLUDES}"
            ""
            ${CMAKE_CURRENT_SOURCE_DIR})
endif (COMMAND create_makefile)
