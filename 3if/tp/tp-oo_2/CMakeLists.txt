set(TP-OO_2_SOURCES
        src/main.cpp)

set(TP-OO_2_HEADERS)

source_group("Source Files" FILES ${TP-OO_2_SOURCES})
source_group("Header Files" FILES ${TP-OO_2_HEADERS})

add_executable(tp-oo_2 ${TP-OO_2_SOURCES} ${TP-OO_2_HEADERS})