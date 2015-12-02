include_directories("include")

set(TP-OO_3_SOURCES
        src/ConfigReader.cpp
        src/Document.cpp
        src/DotFileWriter.cpp
        src/HistoryManager.cpp
        src/Logger.cpp
        src/LogReader.cpp
)

set(TP-OO_3_HEADERS
        src/ConfigReader.h
        src/Document.h
        src/DotFileWriter.h
        src/HistoryManager.h
        src/Logger.h
        src/LogReader.h
)

set(TP-OO_3_MAIN src/main.cpp)

option(TP-OO_3_COLORS "Use colors in output" ON)
if(TP-OO_3_COLORS)
    add_definitions(-DCOLORS)
endif(TP-OO_3_COLORS)

add_executable(tp-oo_3 ${TP-OO_3_MAIN} ${TP-OO_3_SOURCES} ${TP-OO_3_HEADERS})
add_custom_target(tp-oo_3-make
        COMMAND make
        DEPENDS tp-oo_3
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)
