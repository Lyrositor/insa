set(TP-OO_2_SOURCES
        City.cpp
        Event.cpp
        EventLink.cpp
        HashTable.cpp
        Sensor.cpp
        SegmentedTable.cpp
)

set(TP-OO_2_HEADERS
        config.h
        City.h
        Event.h
        EventLink.h
        HashTable.h
        Sensor.h
        SegmentedTable.h
)

set(TP-OO_2_MAIN main.cpp)

add_library(tp-oo_2-lib STATIC ${TP-OO_2_SOURCES} ${TP-OO_2_HEADERS})
add_executable(tp-oo_2 ${TP-OO_2_MAIN})
target_link_libraries(tp-oo_2 tp-oo_2-lib)