set(TP-OO_2_SOURCES
        src/City.cpp
        src/Event.cpp
        src/EventLink.cpp
        src/HashTable.cpp
        src/Sensor.cpp
        src/SegmentedTable.cpp
)

set(TP-OO_2_HEADERS
        src/config.h
        src/City.h
        src/Event.h
        src/EventLink.h
        src/HashTable.h
        src/Sensor.h
        src/SegmentedTable.h
)

set(TP-OO_2_MAIN src/main.cpp)

add_executable(tp-oo_2 ${TP-OO_2_MAIN} ${TP-OO_2_SOURCES} ${TP-OO_2_HEADERS})
