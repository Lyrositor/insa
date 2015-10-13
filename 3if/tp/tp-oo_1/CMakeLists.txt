set(TP-OO_1_SOURCES
    src/Collection.cpp
    src/main.cpp)

set(TP-OO_1_HEADERS
    src/Collection.h)

source_group("Source Files" FILES ${BLABL_SOURCES})
source_group("Header Files" FILES ${BLABL_HEADERS})

add_executable(tp-oo_1 ${TP-OO_1_SOURCES} ${TP-OO_1_HEADERS})