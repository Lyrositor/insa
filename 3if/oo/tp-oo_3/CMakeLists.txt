set(TP-OO_3_SOURCES
        src/ArgumentParser.cpp
)

set(TP-OO_3_HEADERS
        src/ArgumentParser.h
)

set(TP-OO_3_MAIN src/main.cpp)

add_executable(tp-oo_3 ${TP-OO_3_MAIN} ${TP-OO_3_SOURCES} ${TP-OO_3_HEADERS})
