set(TP-OO_1_SOURCES
        src/CollectionEntiers.cpp
)

set(TP-OO_1_HEADERS
        src/CollectionEntiers.h
)

set(TP-OO_1_MAIN src/main.cpp)

add_executable(tp-oo_1 ${TP-OO_1_MAIN} ${TP-OO_1_SOURCES} ${TP-OO_1_HEADERS})
