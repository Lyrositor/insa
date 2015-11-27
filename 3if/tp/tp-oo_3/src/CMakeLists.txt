set(TP-OO_3_SOURCES
        )

set(TP-OO_3_HEADERS
        )

set(TP-OO_3_MAIN main.cpp)

add_library(tp-oo_3-lib STATIC ${TP-OO_3_SOURCES} ${TP-OO_3_HEADERS})
add_executable(tp-oo_3 ${TP-OO_3_MAIN})
target_link_libraries(tp-oo_3 tp-oo_3-lib)